/* Exercise 1: instructor MFRC522 driver + SPI4 + USART1 on STM32F429ZI. */
#include "main.h"
/* USER CODE BEGIN Includes */
#include "tm_stm32f4_mfrc522.h"
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

SPI_HandleTypeDef hspi4;
UART_HandleTypeDef huart1;
/* USER CODE BEGIN PV */
/* Watch these in CubeIDE when diagnosing wiring without a serial terminal. */
volatile uint8_t rfid_version;
volatile uint8_t last_card_id[5]; /* UID[0..3], XOR check byte[4]. */
volatile uint32_t cards_found;
volatile uint32_t uart_errors;
/* USER CODE END PV */

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI4_Init(void);
static void MX_USART1_UART_Init(void);

/* USER CODE BEGIN 0 */
static void Serial_Print(const char *text)
{
  if (HAL_UART_Transmit(&huart1, (const uint8_t *)text,
                        (uint16_t)strlen(text), 100) != HAL_OK) {
    uart_errors++;
  }
}
/* USER CODE END 0 */

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_SPI4_Init();
  MX_USART1_UART_Init();

  /* USER CODE BEGIN 2 */
  char buf[100];
  /* The supplied low-level driver can receive up to MFRC522_MAX_LEN bytes. */
  uint8_t CardID[MFRC522_MAX_LEN] = {0};
  HAL_Delay(50);
  Serial_Print("\r\nWelcome! Ex1 RC522 / SPI4 / USART1 115200 8N1\r\n");
  TM_MFRC522_Init();
  HAL_Delay(50);
  rfid_version = TM_MFRC522_ReadRegister(MFRC522_REG_VERSION);
  snprintf(buf, sizeof(buf), "RC522 VersionReg: 0x%02X\r\n", (unsigned)rfid_version);
  Serial_Print(buf);
  /* USER CODE END 2 */

  /* USER CODE BEGIN WHILE */
  while (1) {
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
    if (rfid_version == 0x00 || rfid_version == 0xFF) {
      HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);
      HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);
      Serial_Print("RC522 not responding: check 3V, GND, RST and SPI4 wiring.\r\n");
      HAL_Delay(1000);
      TM_MFRC522_Init();
      HAL_Delay(50);
      rfid_version = TM_MFRC522_ReadRegister(MFRC522_REG_VERSION);
      continue;
    }

    HAL_Delay(100);
    HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);
    if (TM_MFRC522_Check(CardID) == MI_OK) {
      for (unsigned i = 0; i < 5; ++i) {
        last_card_id[i] = CardID[i];
      }
      cards_found++;
      HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);
      snprintf(buf, sizeof(buf),
               "RFID Card Found!\r\nReading from card: %02X %02X %02X %02X (BCC %02X)\r\n",
               (unsigned)CardID[0], (unsigned)CardID[1], (unsigned)CardID[2],
               (unsigned)CardID[3], (unsigned)CardID[4]);
      Serial_Print(buf);
    } else {
      HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
      Serial_Print("RFID Card Not Found!\r\n");
    }
    HAL_Delay(300);
  }
  /* USER CODE END 3 */
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
