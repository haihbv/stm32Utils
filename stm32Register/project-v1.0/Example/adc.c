#include "stm32system.h"
#include "peripherals.h"

uint16_t value = 0;
int main()
{
	RCC_Clock72MHz_HSE();
	SysTick_Init();
	ADC1_CHO_Init();
	while (1)
	{
		value = ADC1_CHO_Read();
		delay_ms(500);
	}
}
