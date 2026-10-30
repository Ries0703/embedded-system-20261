/* Lab 2 exercises 3.6--3.8. RTC first; use UART commands to set time. */
#include "main.h"
#include "ds1307.h"
#include "SH1106.h"
#include "tm_stm32f4_mfrc522.h"
#include "card_presence.h"
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
static void ShowClock(void) {
  if (!oled_ready) return;
  Time t;
  char text[40];
  SH1106_Fill(SH1106_COLOR_BLACK);
  SH1106_GotoXY(0,0);
  SH1106_Puts("LAB2 3.8 RFID",&Font_7x10,SH1106_COLOR_WHITE);
  SH1106_GotoXY(0,13);
  SH1106_Puts(!rfid_ready ? "RC522 wiring error" : card_state.present ? "Card found" : "Present a card",&Font_7x10,SH1106_COLOR_WHITE);
  if (have_card) {
    snprintf(text,sizeof text,"%02X %02X %02X %02X %02X",card_state.code[0],card_state.code[1],card_state.code[2],card_state.code[3],card_state.code[4]);
    SH1106_GotoXY(0,26);SH1106_Puts(text,&Font_7x10,SH1106_COLOR_WHITE);
  }
  SH1106_GotoXY(0,40);
  if (GetTime(&t) == HAL_OK) {
    snprintf(text,sizeof text,"%02u:%02u:%02u",t.hour,t.min,t.sec);
    SH1106_Puts(text,&Font_7x10,SH1106_COLOR_WHITE);
    snprintf(text,sizeof text,"20%02u-%02u-%02u",t.year,t.month,t.day);
    SH1106_GotoXY(0,52);SH1106_Puts(text,&Font_7x10,SH1106_COLOR_WHITE);
  } else SH1106_Puts("RTC read error",&Font_7x10,SH1106_COLOR_WHITE);
  SH1106_UpdateScreen();
}
static void InitReader(void) {
  char text[48];
  TM_MFRC522_Init();
  rfid_version=TM_MFRC522_ReadRegister(MFRC522_REG_VERSION);
  rfid_ready=rfid_version != 0 && rfid_version != 0xFF;
  snprintf(text,sizeof text,"RC522 VersionReg: 0x%02X %s\r\n",rfid_version,rfid_ready ? "ready" : "NOT RESPONDING");
  Serial_Print(text);
}
static void PollRFID(void) {
  if (!rfid_ready) return;
  uint8_t code[MFRC522_MAX_LEN]={0};
  /* Wake halted cards, so holding a card does not look like removal. */
  TM_MFRC522_Status_t status=TM_MFRC522_Request(PICC_REQALL,code);
  if (status == MI_OK) status=TM_MFRC522_Anticoll(code);
  TM_MFRC522_Halt();
  CardEvent event=CardPresence_Update(&card_state,status == MI_OK ? code : NULL);
  if (event == CARD_PRESENTED) {
    char text[64];have_card=1;
    snprintf(text,sizeof text,"CARD %02X %02X %02X %02X %02X\r\n",code[0],code[1],code[2],code[3],code[4]);
    Serial_Print(text);ShowClock();
  } else if (event == CARD_REMOVED) { Serial_Print("CARD REMOVED\r\n");ShowClock(); }
  HAL_GPIO_WritePin(GPIOG,GPIO_PIN_13,card_state.present ? GPIO_PIN_SET : GPIO_PIN_RESET);
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
  if (!strcmp(cmd,"HELP")) Serial_Print("HELP | SCAN | RFID INIT | CARD LAST | TIME GET | TIME SET YYYY-MM-DD HH:MM:SS\r\n");
  else if (!strcmp(cmd,"SCAN")) ScanBus();
  else if (!strcmp(cmd,"RFID INIT")) InitReader();
  else if (!strcmp(cmd,"CARD LAST")) {
    char text[64];
    if (!have_card) Serial_Print("ERR NO_CARD\r\n");
    else { snprintf(text,sizeof text,"CARD %02X %02X %02X %02X %02X\r\n",card_state.code[0],card_state.code[1],card_state.code[2],card_state.code[3],card_state.code[4]);Serial_Print(text); }
  }
  else if (!strcmp(cmd,"TIME GET")) PrintTime();
  else if (!strncmp(cmd,"TIME SET ",9)) {
    unsigned y,m,d,h,mi,s; int end=0;
    if (sscanf(cmd+9,"%4u-%2u-%2u %2u:%2u:%2u%n",&y,&m,&d,&h,&mi,&s,&end) != 6 ||
        cmd[9+end] || y < 2000 || y > 2099 || m > 12 || d > 31 || h > 23 || mi > 59 || s > 59) {
      Serial_Print("ERR SYNTAX TIME SET YYYY-MM-DD HH:MM:SS\r\n"); return;
    }
    Time t={(uint8_t)s,(uint8_t)mi,(uint8_t)h,TimeWeekday(y,m,d),(uint8_t)d,(uint8_t)m,(uint8_t)(y-2000)};
    Serial_Print(SetTime(&t) == HAL_OK ? "OK TIME SET\r\n" : "ERR TIME SET invalid date or I2C failure\r\n");
    PrintTime();
  } else Serial_Print("ERR UNKNOWN COMMAND; type HELP\r\n");
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
  Serial_Print("\r\nLAB2 PERIPHERALS / EXERCISE 3.8 RFID OLED / USART1 115200 8N1\r\n");
  Serial_Print("Clock is NOT reset on boot. Type HELP.\r\n");
  ScanBus();
  oled_ready=SH1106_Init();
  Serial_Print(oled_ready ? "OLED initialized at 0x3C\r\n" : "ERR OLED not detected at 0x3C; check SCAN and wiring\r\n");
  InitReader();
  uint32_t next=HAL_GetTick(),next_card=HAL_GetTick();
  while (1) {
    PollConsole();
    if ((int32_t)(HAL_GetTick()-next_card) >= 0) { next_card=HAL_GetTick()+100;PollRFID(); }
    if ((int32_t)(HAL_GetTick()-next) >= 0) {
      next=HAL_GetTick()+1000;
      PrintTime(); ShowClock();
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
