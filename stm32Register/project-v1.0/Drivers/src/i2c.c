#include "i2c.h"
#include "gpio.h"
#include "rcc.h"

void I2C1_Init(void)
{
	RCC_APB1ClockCmd(RCC_APB1_I2C1, ENABLE);
	RCC_APB2ClockCmd(RCC_APB2_GPIOB, ENABLE);

	GPIO_InitTypeDef gpio;
	gpio.Mode = GPIO_MODE_AF_OD;
	gpio.Pin = GPIO_PIN_6;
	gpio.Speed = GPIO_SPEED_50MHZ;
	GPIO_Init(GPIOB, &gpio);

	gpio.Pin = GPIO_PIN_7;
	GPIO_Init(GPIOB, &gpio);

	I2C1->CR1 &= ~(uint32_t)(1 << 0); // Disable I2C
	I2C1->CR2 = 36;					  // PCLK1 = 36MHz
	I2C1->CCR = 180;				  // 100kHz
	I2C1->TRISE = 37;				  // 36 + 1
	I2C1->CR1 |= (1 << 0);			  // Enable I2C
}

void I2C1_Start(void)
{
	I2C1->CR1 &= ~(uint32_t)(1 << 9); // Clear STOP if set
	I2C1->CR1 |= (1 << 8);			  // Generate START
	while (!(I2C1->SR1 & (1 << 0)))
		; // Wait for SB = 1 (Start bit sent)
}
void I2C1_Stop(void)
{
	I2C1->CR1 |= (1 << 9); // Generate STOP
}
void I2C1_WriteAddr(uint8_t addr, uint8_t is_read)
{
	I2C1->DR = (uint32_t)((addr << 1) | (is_read & 0x01));

	// Wait for ADDR flag or timeout
	uint32_t timeout = 100000;
	while (!(I2C1->SR1 & (1 << 1)))
	{
		if (--timeout == 0)
		{
			I2C1_Stop();
			return;
		}
	}

	// Clear ADDR by reading SR1 and SR2
	volatile uint32_t temp = I2C1->SR2;
	(void)temp;
}
uint8_t I2C1_WriteData(uint8_t data)
{
	I2C1->DR = data;

	while (!(I2C1->SR1 & (1 << 2)))
		; // Wait for BTF

	// Check for acknowledge failure
	if (I2C1->SR1 & (1 << 10))
	{
		I2C1->SR1 &= ~(uint32_t)(1 << 10); // Clear AF
		I2C1_Stop();
		return 1; // Failed
	}
	return 0; // Success
}

uint8_t I2C1_ReadData(uint8_t ack)
{
	if (ack)
	{
		I2C1->CR1 |= (1 << 10); // Enable ACK
	}
	else
	{
		I2C1->CR1 &= ~(uint32_t)(1 << 10); // Disable ACK
	}

	while (!(I2C1->SR1 & (1 << 6)))
		; // Wait for RxNE

	return (uint8_t)I2C1->DR;
}
