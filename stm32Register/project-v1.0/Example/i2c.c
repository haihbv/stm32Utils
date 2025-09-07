#include "stm32system.h"
#include "peripherals.h"
#include "iic.h"

int main(void)
{
	RCC_Clock72MHz_HSE();
	SysTick_Init();
	I2C1_Init();
	while (1)
	{
		I2C1_Start();
		I2C1_WriteAddr(0x68, 0);
		I2C1_WriteData(0x0F);
		I2C1_Stop();
		delay_ms(1000);
	}
}
