#include "stm32system.h"
#include "peripherals.h"
#include "rgb.h"

#define BUTTON_PIN GPIO_PIN_0

int main()
{
	RCC_Clock(SYSCLK_FREQ_72MHZ);
	SysTick_Init();
	RCC_APB2ClockCmd(RCC_APB2_GPIOB | RCC_APB2_GPIOA, ENABLE);

	GPIO_InitTypeDef gpio;
	gpio.Mode = GPIO_MODE_INPUT_PU;
	gpio.Pin = BUTTON_PIN;
	gpio.Speed = GPIO_SPEED_50MHZ;
	GPIO_Init(GPIOA, &gpio);

	GPIO_Config();

	uint8_t last_button = 1;
	while (1)
	{
		uint8_t button = GPIO_ReadPin(GPIOA, BUTTON_PIN);
		if (last_button && !button)
		{
			delay_ms(25);
			if (!GPIO_ReadPin(GPIOA, BUTTON_PIN))
			{
				LED_RGB_SetCommand();
				while (!GPIO_ReadPin(GPIOA, BUTTON_PIN))
					;
				delay_ms(25);
			}
		}
		last_button = button;
	}
}
// ...existing code...