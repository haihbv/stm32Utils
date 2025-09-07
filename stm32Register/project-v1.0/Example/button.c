#include "peripherals.h"
#include "stm32system.h"

static uint8_t last_button = 1, new_button = 1;

void Gpio_Init(void)
{
    RCC_APB2ClockCmd(RCC_APB2_GPIOC | RCC_APB2_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Speed = GPIO_SPEED_50MHZ;
    GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Mode = GPIO_MODE_INPUT_PU;
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

Bool Button_Read(void)
{
    static uint8_t last_state = 1;
    uint8_t curr_state = GPIO_ReadPin(GPIOA, GPIO_PIN_0);
    Bool pressed = FALSE;
    if (last_state && !curr_state)
    {
        delay_ms(20); // debounce
        if (!GPIO_ReadPin(GPIOA, GPIO_PIN_0))
        {
            pressed = TRUE;
        }
    }
    last_state = curr_state;
    return pressed;
}

int main()
{
    RCC_Clock(SYSCLK_FREQ_72MHZ);
    SysTick_Init();
    Gpio_Init();

    while (1)
    {
        if (Button_Read() == TRUE)
        {
            GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        }
    }
}
