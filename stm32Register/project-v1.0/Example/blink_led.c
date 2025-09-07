#include "peripherals.h"
#include "stm32system.h"

void gpio_config()
{
    RCC_APB2ClockCmd(RCC_APB2_GPIOC, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Speed = GPIO_SPEED_50MHZ;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
}

int main()
{
    RCC_Clock(SYSCLK_FREQ_72MHZ);
    SysTick_Init();
    gpio_config();

    while (1)
    {
        GPIO_WritePin(GPIOC, GPIO_PIN_13, BIT_RESET);
        delay_ms(1000);
        GPIO_WritePin(GPIOC, GPIO_PIN_13, BIT_SET);
        delay_ms(1000);
    }
}
