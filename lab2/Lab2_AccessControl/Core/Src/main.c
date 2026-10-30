/* Lab 2 exercise 3.9: RFID access control, UART configuration and RAM logs. */
#include "main.h"
#include "ds1307.h"
#include "SH1106.h"
#include "tm_stm32f4_mfrc522.h"
#include "card_presence.h"
#include "access_control.h"
#include <stdio.h>
#include <string.h>

SPI_HandleTypeDef hspi4;
UART_HandleTypeDef huart1;
I2C_HandleTypeDef hi2c3;
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI4_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_I2C3_Init(void);
static uint8_t rx_byte;
static volatile uint16_t rx_head, rx_tail;
static volatile uint8_t rx_overflow;
static uint8_t rx_ring[256];
static char line[96];
static unsigned line_len;
static uint8_t discard_line;
static uint8_t oled_ready;
static uint8_t rfid_ready, rfid_version, have_card;
static CardPresence card_state;
static AccessControl access;
static AccessDecision decision=ACCESS_REJECTED;
static uint8_t door_open, rtc_valid;
static AccessLog log_snapshot[AC_MAX_LOGS];
static unsigned snapshot_count, snapshot_index;
static uint8_t log_streaming;

static void Serial_Print(const char *text) {
  HAL_UART_Transmit(&huart1,(const uint8_t *)text,(uint16_t)strlen(text),100);
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *uart) {
  if (uart->Instance != USART1) return;
  uint16_t next=(rx_head+1)&255;
  if (next == rx_tail) rx_overflow=1;
  else { rx_ring[rx_head]=rx_byte; rx_head=next; }
  HAL_UART_Receive_IT(&huart1,&rx_byte,1);
}
void HAL_UART_ErrorCallback(UART_HandleTypeDef *uart) {
  if (uart->Instance == USART1) {
    rx_overflow=1;
    HAL_UART_Receive_IT(&huart1,&rx_byte,1);
  }
}
static void PrintTime(void) {
  Time t; char text[96];
  HAL_StatusTypeDef status=GetTime(&t);
  if (status != HAL_OK) {
    snprintf(text,sizeof text,"ERR RTC status=%u I2C=0x%08lX; check wiring or TIME SET\r\n",(unsigned)status,(unsigned long)HAL_I2C_GetError(&hi2c3));
  } else snprintf(text,sizeof text,"TIME 20%02u-%02u-%02u %02u:%02u:%02u weekday=%u\r\n",t.year,t.month,t.day,t.hour,t.min,t.sec,t.weekday);
  Serial_Print(text);
}
static void ApplyLEDs(void) {
  HAL_GPIO_WritePin(GPIOG,GPIO_PIN_13,card_state.present && rfid_ready ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOG,GPIO_PIN_14,door_open ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
static void ShowClock(void) {
  Time t;
  rtc_valid=GetTime(&t) == HAL_OK;
  if (!rtc_valid && door_open) {
    door_open=0;decision=ACCESS_CLOCK_ERROR;ApplyLEDs();
    Serial_Print("EVENT LOCKED RTC_ERROR\r\n");
  }
  if (!oled_ready) return;
  char text[48];
  SH1106_Fill(SH1106_COLOR_BLACK);
  SH1106_GotoXY(0,0);
  SH1106_Puts("LAB2 3.9 ACCESS",&Font_7x10,SH1106_COLOR_WHITE);
  SH1106_GotoXY(0,13);
  char *message=!rfid_ready ? "RFID error" : !rtc_valid ? "RTC error" :
    !card_state.present ? "Ready" : door_open ? "Welcome" : "Rejected";
  SH1106_Puts(message,&Font_11x18,SH1106_COLOR_WHITE);
  if (have_card) {
    snprintf(text,sizeof text,"%02X %02X %02X %02X %02X",card_state.code[0],card_state.code[1],card_state.code[2],card_state.code[3],card_state.code[4]);
    SH1106_GotoXY(0,34);SH1106_Puts(text,&Font_7x10,SH1106_COLOR_WHITE);
  }
  SH1106_GotoXY(0,50);
  if (rtc_valid) snprintf(text,sizeof text,"%02u:%02u:%02u Logs:%u",t.hour,t.min,t.sec,access.log_count);
  else snprintf(text,sizeof text,"Logs:%u",access.log_count);
  SH1106_Puts(text,&Font_7x10,SH1106_COLOR_WHITE);
  SH1106_UpdateScreen();
}
static void PrintLog(const AccessLog *log) {
  char text[112];const Time *t=&log->time;
  snprintf(text,sizeof text,"LOG %lu 20%02u-%02u-%02u %02u:%02u:%02u %02X%02X%02X%02X%02X\r\n",
    (unsigned long)log->sequence,t->year,t->month,t->day,t->hour,t->min,t->sec,
    log->code[0],log->code[1],log->code[2],log->code[3],log->code[4]);
  Serial_Print(text);
}
static void PollLogStream(void) {
  if (!log_streaming) return;
  if (snapshot_index < snapshot_count) PrintLog(&log_snapshot[snapshot_index++]);
  else { Serial_Print("LOG END\r\n");log_streaming=0; }
}
static void InitReader(void) {
  char text[48];
  door_open=0;have_card=0;memset(&card_state,0,sizeof card_state);
  TM_MFRC522_Init();
  rfid_version=TM_MFRC522_ReadRegister(MFRC522_REG_VERSION);
  rfid_ready=rfid_version != 0 && rfid_version != 0xFF;
  ApplyLEDs();
  snprintf(text,sizeof text,"RC522 VersionReg: 0x%02X %s\r\n",rfid_version,rfid_ready ? "ready" : "NOT RESPONDING");
  Serial_Print(text);
}
static void PollRFID(void) {
  if (!rfid_ready) return;
  uint8_t code[MFRC522_MAX_LEN]={0};
  TM_MFRC522_Status_t status=TM_MFRC522_Request(PICC_REQALL,code);
  if (status == MI_OK) status=TM_MFRC522_Anticoll(code);
  TM_MFRC522_Halt();
  CardEvent event=CardPresence_Update(&card_state,status == MI_OK ? code : NULL);
  if (event == CARD_PRESENTED) {
    char text[96];Time t;have_card=1;
    rtc_valid=GetTime(&t) == HAL_OK;
    decision=Access_Authorize(&access,code,rtc_valid ? &t : NULL);
    door_open=decision == ACCESS_GRANTED;
    ApplyLEDs();
    snprintf(text,sizeof text,"EVENT CARD %02X%02X%02X%02X%02X %s\r\n",code[0],code[1],code[2],code[3],code[4],
      door_open ? "WELCOME" : decision == ACCESS_CLOCK_ERROR ? "RTC_ERROR LOCKED" : "REJECTED");
    Serial_Print(text);
    if (door_open) PrintLog(Access_GetLog(&access,access.log_count-1));
    ShowClock();
  } else if (event == CARD_REMOVED) {
    door_open=0;ApplyLEDs();Serial_Print("EVENT CARD REMOVED; DOOR LOCKED\r\n");ShowClock();
  }
  ApplyLEDs();
}
static void CheckReaderHealth(void) {
  uint8_t version=TM_MFRC522_ReadRegister(MFRC522_REG_VERSION);
  if (version == 0 || version == 0xFF) {
    if (rfid_ready) Serial_Print("EVENT READER ERROR; DOOR LOCKED; use RFID INIT after repair\r\n");
    rfid_ready=0;door_open=0;card_state.present=0;ApplyLEDs();
  }
}
static void ScanBus(void) {
  char text[40]; unsigned found=0;
  Serial_Print("I2C3 scan at 100 kHz (7-bit addresses):\r\n");
  for (unsigned addr=8;addr<120;addr++) {
    if (HAL_I2C_IsDeviceReady(&hi2c3,addr << 1,1,5) == HAL_OK) {
      snprintf(text,sizeof text,"I2C ACK 0x%02X\r\n",addr); Serial_Print(text); found++;
    }
  }
  snprintf(text,sizeof text,"SCAN END count=%u\r\n",found); Serial_Print(text);
}
static void Command(char *cmd) {
  char text[128];uint8_t code[5];
  if (!strcmp(cmd,"HELP")) Serial_Print(
    "HELP | STATUS | SCAN | RFID INIT | CARD LAST\r\n"
    "TIME GET | TIME SET YYYY-MM-DD HH:MM:SS\r\n"
    "ALLOW ADD 10_HEX_DIGITS | ALLOW DEL 10_HEX_DIGITS | ALLOW LIST\r\n"
    "LOG LIST | LOG CLEAR\r\n"
    "End commands with Enter (CR, LF or CRLF). Logs and allowlist are RAM-only.\r\n");
  else if (!strcmp(cmd,"SCAN")) ScanBus();
  else if (!strcmp(cmd,"STATUS")) {
    Time t;
    snprintf(text,sizeof text,"STATUS reader=%s rtc=%s present=%u door=%s allowed=%u logs=%u/100\r\n",
      rfid_ready ? "OK" : "ERROR",GetTime(&t)==HAL_OK ? "OK" : "ERROR",card_state.present,door_open ? "OPEN" : "LOCKED",access.allowed_count,access.log_count);
    Serial_Print(text);
  }
  else if (!strcmp(cmd,"RFID INIT")) { InitReader();ShowClock(); }
  else if (!strcmp(cmd,"CARD LAST")) {
    if (!have_card) Serial_Print("ERR NO_CARD\r\n");
    else { snprintf(text,sizeof text,"CARD %02X%02X%02X%02X%02X\r\n",card_state.code[0],card_state.code[1],card_state.code[2],card_state.code[3],card_state.code[4]);Serial_Print(text); }
  }
  else if (!strcmp(cmd,"TIME GET")) PrintTime();
  else if (!strncmp(cmd,"TIME SET ",9)) {
    unsigned y,m,d,h,mi,s;int end=0;
    if (sscanf(cmd+9,"%4u-%2u-%2u %2u:%2u:%2u%n",&y,&m,&d,&h,&mi,&s,&end)!=6 ||
        cmd[9+end] || y<2000 || y>2099 || m>12 || d>31 || h>23 || mi>59 || s>59) {
      Serial_Print("ERR SYNTAX TIME SET YYYY-MM-DD HH:MM:SS\r\n");return;
    }
    Time t={(uint8_t)s,(uint8_t)mi,(uint8_t)h,TimeWeekday(y,m,d),(uint8_t)d,(uint8_t)m,(uint8_t)(y-2000)};
    Serial_Print(SetTime(&t)==HAL_OK ? "OK TIME SET\r\n" : "ERR TIME SET invalid date or I2C failure\r\n");
    PrintTime();ShowClock();
  }
  else if (!strcmp(cmd,"ALLOW LIST")) {
    snprintf(text,sizeof text,"ALLOW BEGIN count=%u\r\n",access.allowed_count);Serial_Print(text);
    for(unsigned i=0;i<access.allowed_count;i++) {
      uint8_t *c=access.allowed[i];snprintf(text,sizeof text,"ALLOW %02X%02X%02X%02X%02X\r\n",c[0],c[1],c[2],c[3],c[4]);Serial_Print(text);
    }
    Serial_Print("ALLOW END\r\n");
  }
  else if (!strncmp(cmd,"ALLOW ADD ",10) || !strncmp(cmd,"ALLOW DEL ",10)) {
    if (!Access_ParseCode(cmd+10,code)) { Serial_Print("ERR CARD use exactly 10 hex digits with valid fifth BCC byte\r\n");return; }
    if (cmd[6]=='A') {
      AccessResult result=Access_Add(&access,code);
      Serial_Print(result==AC_OK ? "OK ADDED; remove and present card to unlock\r\n" : result==AC_DUPLICATE ? "OK ALREADY_ALLOWED\r\n" : "ERR ALLOWLIST_FULL\r\n");
    } else {
      AccessResult result=Access_Delete(&access,code);
      Serial_Print(result==AC_OK ? "OK DELETED\r\n" : "ERR NOT_FOUND\r\n");
      if (card_state.present && !Access_IsAllowed(&access,card_state.code)) {
        door_open=0;decision=ACCESS_REJECTED;ApplyLEDs();ShowClock();
      }
    }
  }
  else if (!strcmp(cmd,"LOG LIST")) {
    snapshot_count=access.log_count;snapshot_index=0;
    for(unsigned i=0;i<snapshot_count;i++) log_snapshot[i]=*Access_GetLog(&access,i);
    log_streaming=1;
    snprintf(text,sizeof text,"LOG BEGIN count=%u\r\n",snapshot_count);Serial_Print(text);
  }
  else if (!strcmp(cmd,"LOG CLEAR")) {
    if(log_streaming) Serial_Print("LOG ABORTED\r\n");
    log_streaming=0;Access_ClearLogs(&access);Serial_Print("OK LOG CLEARED\r\n");ShowClock();
  }
  else Serial_Print("ERR UNKNOWN COMMAND; type HELP\r\n");
}
static void PollConsole(void) {
  if (rx_overflow) { rx_overflow=0; discard_line=1; }
  while (rx_tail != rx_head) {
    char c=(char)rx_ring[rx_tail]; rx_tail=(rx_tail+1)&255;
    if (c == '\r' || c == '\n') {
      if (discard_line) Serial_Print("ERR LINE_TOO_LONG_OR_RX_OVERFLOW\r\n");
      else if (line_len) { line[line_len]=0; Command(line); }
      line_len=0; discard_line=0;
    } else if (c == '\b' || c == 127) { if (line_len) line_len--; }
    else if (!discard_line && c >= 32 && c <= 126) {
      if (line_len < sizeof line-1) line[line_len++]=c;
      else discard_line=1;
    }
  }
}
int main(void) {
  HAL_Init(); SystemClock_Config(); MX_GPIO_Init(); MX_SPI4_Init();
  MX_USART1_UART_Init(); MX_I2C3_Init();
  HAL_UART_Receive_IT(&huart1,&rx_byte,1);
  HAL_Delay(50);
  Serial_Print("\r\nLAB2 ACCESS CONTROL / EXERCISE 3.9 / USART1 115200 8N1\r\n");
  Serial_Print("Clock is NOT reset on boot. Empty allowlist; door locked. Type HELP.\r\n");
  ScanBus();
  oled_ready=SH1106_Init();
  Serial_Print(oled_ready ? "OLED initialized at 0x3C\r\n" : "ERR OLED not detected at 0x3C; check SCAN and wiring\r\n");
  InitReader();
  uint32_t next=HAL_GetTick(),next_card=HAL_GetTick(),next_log=HAL_GetTick();
  while (1) {
    PollConsole();
    if ((int32_t)(HAL_GetTick()-next_log) >= 0) { next_log=HAL_GetTick()+10;PollLogStream(); }
    if ((int32_t)(HAL_GetTick()-next_card) >= 0) { next_card=HAL_GetTick()+100;PollRFID(); }
    if ((int32_t)(HAL_GetTick()-next) >= 0) {
      next=HAL_GetTick()+1000;
      CheckReaderHealth();ShowClock();
    }
  }
}
static void MX_I2C3_Init(void) {
  hi2c3.Instance=I2C3;
  hi2c3.Init.ClockSpeed=100000;
  hi2c3.Init.DutyCycle=I2C_DUTYCYCLE_2;
  hi2c3.Init.OwnAddress1=0;
  hi2c3.Init.AddressingMode=I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode=I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2=0;
  hi2c3.Init.GeneralCallMode=I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode=I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK) Error_Handler();
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef osc = {0};
  RCC_ClkInitTypeDef clk = {0};
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  osc.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  osc.HSEState = RCC_HSE_ON;
  osc.PLL.PLLState = RCC_PLL_ON;
  osc.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  osc.PLL.PLLM = 4;
  osc.PLL.PLLN = 180;
  osc.PLL.PLLP = RCC_PLLP_DIV2;
  osc.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&osc) != HAL_OK) Error_Handler();
  if (HAL_PWREx_EnableOverDrive() != HAL_OK) Error_Handler();
  clk.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                  RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  clk.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  clk.AHBCLKDivider = RCC_SYSCLK_DIV1;
  clk.APB1CLKDivider = RCC_HCLK_DIV4;
  clk.APB2CLKDivider = RCC_HCLK_DIV2;
  if (HAL_RCC_ClockConfig(&clk, FLASH_LATENCY_5) != HAL_OK) Error_Handler();
}

static void MX_SPI4_Init(void)
{
  hspi4.Instance = SPI4;
  hspi4.Init.Mode = SPI_MODE_MASTER;
  hspi4.Init.Direction = SPI_DIRECTION_2LINES;
  hspi4.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi4.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi4.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi4.Init.NSS = SPI_NSS_SOFT;
  hspi4.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64; /* 90 MHz / 64. */
  hspi4.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi4.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi4.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi4.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi4) != HAL_OK) Error_Handler();
}

static void MX_USART1_UART_Init(void)
{
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK) Error_Handler();
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef gpio = {0};
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13 | GPIO_PIN_14, GPIO_PIN_RESET);
  gpio.Pin = GPIO_PIN_4;
  gpio.Mode = GPIO_MODE_OUTPUT_PP;
  gpio.Pull = GPIO_NOPULL;
  gpio.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &gpio);
  gpio.Pin = GPIO_PIN_13 | GPIO_PIN_14;
  HAL_GPIO_Init(GPIOG, &gpio);
}

void Error_Handler(void)
{
  __disable_irq();
  while (1) {}
}
