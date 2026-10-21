/* Exercise 2: provided L3GD20 driver, onboard SPI5 gyro, USART1 and LEDs. */
#include "main.h"
/* USER CODE BEGIN Includes */
#include "L3GD20.h"
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

SPI_HandleTypeDef hspi5;
UART_HandleTypeDef huart1;
/* USER CODE BEGIN PV */
volatile float gyro_x_dps, gyro_y_dps, gyro_z_dps;
volatile uint8_t gyro_id, gyro_calibrated;
volatile uint32_t gyro_samples, spi_errors, uart_errors;
/* USER CODE END PV */

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI5_Init(void);
static void MX_USART1_UART_Init(void);

/* USER CODE BEGIN 0 */
static void Serial_Print(const char *text)
{
  if (HAL_UART_Transmit(&huart1, (const uint8_t *)text,
                       (uint16_t)strlen(text), 100) != HAL_OK) uart_errors++;
}

static HAL_StatusTypeDef Gyro_ReadRegister(uint8_t address, uint8_t *value)
{
  uint8_t tx[2] = {(uint8_t)(address | 0x80), 0};
  uint8_t rx[2] = {0};
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
  HAL_StatusTypeDef status = HAL_SPI_TransmitReceive(&hspi5, tx, rx, 2, 50);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
  if (status == HAL_OK) *value = rx[1];
  else spi_errors++;
  return status;
}

static void Format_Rate(char *text, size_t capacity, float rate)
{
  /* Fixed-point output avoids requiring newlib's optional float printf. */
  long milli = (long)(rate * 1000.0f);
  const char *sign = milli < 0 ? "-" : "";
  if (milli < 0) milli = -milli;
  snprintf(text, capacity, "%s%ld.%03ld", sign, milli / 1000, milli % 1000);
}
/* USER CODE END 0 */

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_SPI5_Init();
  MX_USART1_UART_Init();

  /* USER CODE BEGIN 2 */
  char line[160], x_text[24], y_text[24], z_text[24];
  uint8_t identity = 0;
  Serial_Print("\r\nEx2 onboard gyroscope / SPI5 / USART1 115200 8N1\r\n");
  while (Gyro_ReadRegister(0x0F, &identity) != HAL_OK ||
         (identity != 0xD3 && identity != 0xD4 && identity != 0xD7)) {
    snprintf(line, sizeof(line), "Gyroscope not detected, WHO_AM_I=0x%02X\r\n", (unsigned)identity);
    Serial_Print(line);
    HAL_Delay(1000);
  }
  gyro_id = identity;
  snprintf(line, sizeof(line), "WHO_AM_I=0x%02X. Keep board STILL during calibration.\r\n", (unsigned)gyro_id);
  Serial_Print(line);
  L3GD20_Init();
  uint32_t last_sample = HAL_GetTick();
  uint32_t last_print = last_sample;
  /* USER CODE END 2 */

  /* USER CODE BEGIN WHILE */
  while (1) {
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
    uint32_t now = HAL_GetTick();
    if ((uint32_t)(now - last_sample) < 3) {
      HAL_Delay(1);
      continue;
    }
    last_sample = now;
    uint8_t sensor_status = 0;
    if (Gyro_ReadRegister(0x27, &sensor_status) != HAL_OK) {
      HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13 | GPIO_PIN_14, GPIO_PIN_RESET);
      Serial_Print("Gyroscope SPI read failed.\r\n");
      HAL_Delay(1000);
      continue;
    }
    if ((sensor_status & 0x08) == 0) continue; /* Wait for fresh XYZ data. */

    /* The supplied state machine needs one call to read and one to process. */
    L3GD20_loop();
    L3GD20_loop();
    gyro_samples++;

    if (!L3GD20_IsCalibrated()) {
      if ((uint32_t)(now - last_print) >= 1000) {
        Serial_Print("Calibrating... keep board still.\r\n");
        last_print = now;
      }
      continue;
    }
    if (!gyro_calibrated) {
      gyro_calibrated = 1;
      Serial_Print("Calibration complete. Rotate board to change X/Y/Z (deg/s).\r\n");
    }

    gyro_x_dps = get_Rate_X();
    gyro_y_dps = get_Rate_Y();
    gyro_z_dps = get_Rate_Z();
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, gyro_x_dps > 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, gyro_y_dps > 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);

    if ((uint32_t)(now - last_print) >= 100) {
      Format_Rate(x_text, sizeof(x_text), gyro_x_dps);
      Format_Rate(y_text, sizeof(y_text), gyro_y_dps);
      Format_Rate(z_text, sizeof(z_text), gyro_z_dps);
      snprintf(line, sizeof(line), "X = %s, Y = %s, Z = %s deg/s\r\n", x_text, y_text, z_text);
      Serial_Print(line);
      last_print = now;
    }
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

static void MX_SPI5_Init(void)
{
  hspi5.Instance = SPI5;
  hspi5.Init.Mode = SPI_MODE_MASTER;
  hspi5.Init.Direction = SPI_DIRECTION_2LINES;
  hspi5.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi5.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi5.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi5.Init.NSS = SPI_NSS_SOFT;
  hspi5.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi5.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi5.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi5.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi5.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi5) != HAL_OK) Error_Handler();
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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  /* Deselect gyro, LCD sharing SPI5, and optional RC522 still wired to SPI4. */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1 | GPIO_PIN_2, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13 | GPIO_PIN_14, GPIO_PIN_RESET);
  gpio.Mode = GPIO_MODE_OUTPUT_PP;
  gpio.Pull = GPIO_NOPULL;
  gpio.Speed = GPIO_SPEED_FREQ_LOW;
  gpio.Pin = GPIO_PIN_1 | GPIO_PIN_2;
  HAL_GPIO_Init(GPIOC, &gpio);
  gpio.Pin = GPIO_PIN_4;
  HAL_GPIO_Init(GPIOE, &gpio);
  gpio.Pin = GPIO_PIN_13 | GPIO_PIN_14;
  HAL_GPIO_Init(GPIOG, &gpio);
}

void Error_Handler(void)
{
  __disable_irq();
  while (1) {}
}
