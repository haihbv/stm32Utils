#include "stm32system.h"
#include "peripherals.h"

int main()
{
	RCC_Clock72MHz_HSE();
	SysTick_Init();
	SPI_Config(SPI1);
	while (1)
	{
		SPI_SendCommand(SPI1, 0xA3);
		delay_ms(1000);
	}
}
