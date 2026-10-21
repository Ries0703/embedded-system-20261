#include "main.h"

void HAL_MspInit(void)
{
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
}

void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
  GPIO_InitTypeDef gpio = {0};
  if (hspi->Instance == SPI4) {
    __HAL_RCC_SPI4_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    gpio.Pin = GPIO_PIN_2 | GPIO_PIN_5 | GPIO_PIN_6;
    gpio.Mode = GPIO_MODE_AF_PP;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio.Alternate = GPIO_AF5_SPI4;
    HAL_GPIO_Init(GPIOE, &gpio);
  }
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef gpio = {0};
  if (huart->Instance == USART1) {
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    gpio.Pin = GPIO_PIN_9 | GPIO_PIN_10;
    gpio.Mode = GPIO_MODE_AF_PP;
    gpio.Pull = GPIO_PULLUP;
    gpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &gpio);
  }
}
