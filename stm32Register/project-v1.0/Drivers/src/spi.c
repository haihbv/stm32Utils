#include "spi.h"
#include "rcc.h"
#include "gpio.h"

void SPI_Config(__IO SPI_TypeDef *SPIx)
{
	GPIO_InitTypeDef gpio;
	SPI_InitTypeDef spi;
	if (SPIx == SPI1)
	{
		RCC_APB2ClockCmd(RCC_APB2_SPI1 | RCC_APB2_GPIOA, ENABLE);
		RCC_APB2ClockCmd(RCC_APB2_GPIOB, ENABLE);

		// SCK and MOSI
		gpio.Pin = GPIO_PIN_5 | GPIO_PIN_7;
		gpio.Mode = GPIO_MODE_AF_PP;
		gpio.Speed = GPIO_SPEED_50MHZ;
		GPIO_Init(GPIOA, &gpio);

		// MISO
		gpio.Pin = GPIO_PIN_6;
		gpio.Mode = GPIO_MODE_INPUT;
		GPIO_Init(GPIOA, &gpio);

		// SS
		gpio.Pin = GPIO_PIN_0;
		gpio.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_Init(GPIOB, &gpio);
	}
	else if (SPIx == SPI2)
	{
		RCC_APB1ClockCmd(RCC_APB1_SPI2, ENABLE);
		RCC_APB2ClockCmd(RCC_APB2_GPIOB, ENABLE);

		// SCK and MOSI
		gpio.Pin = GPIO_PIN_13 | GPIO_PIN_15;
		gpio.Mode = GPIO_MODE_AF_PP;
		gpio.Speed = GPIO_SPEED_50MHZ;
		GPIO_Init(GPIOB, &gpio);

		// MISO
		gpio.Pin = GPIO_PIN_14;
		gpio.Mode = GPIO_MODE_INPUT;
		GPIO_Init(GPIOB, &gpio);

		// SS
		gpio.Pin = GPIO_PIN_12;
		gpio.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_Init(GPIOB, &gpio);
	}

	spi.mode = SPI_CR1_MSTR_MASTER;
	spi.baud_rate = SPI_CR1_BaudRate_128;
	spi.cpha = SPI_CR1_CPHA_1Edge;
	spi.cpol = SPI_CR1_CPOL_LOW;
	spi.ss = SPI_SSM_SSI_ENABLE_MASK;
	spi.data_size = SPI_CR1_DFF_8bit;
	spi.direction = SPI_CR1_FULL_DUPLEX;
	spi.first_bit = SPI_CR1_FIRST_MSB;
	SPI_Init(SPIx, &spi);
}

void SPI_Init(__IO SPI_TypeDef *SPIx, SPI_InitTypeDef *Init)
{
	if (Init == NULL)
	{
		return;
	}
	// Reset CR1
	SPIx->CR1 = 0;

	// Apply configuration
	SPIx->CR1 |= Init->mode |
				 Init->baud_rate |
				 Init->ss |
				 Init->cpol |
				 Init->cpha |
				 Init->first_bit |
				 Init->data_size |
				 Init->direction;

	// Enable SPI
	SPI_Cmd(SPIx, ENABLE);
}

void SPI_Cmd(__IO SPI_TypeDef *SPIx, FunctionalState state)
{
	if (state == SET)
	{
		SET_BIT(SPIx->CR1, SPI_CR1_SPE_ENABLE);
	}
	else if (state == RESET)
	{
		CLEAR_BIT(SPIx->CR1, SPI_CR1_SPE_ENABLE);
	}
}

void SPI_Transmit(__IO SPI_TypeDef *SPIx, uint8_t data)
{
	CS_OFF;
	while (READ_BIT(SPIx->SR, SPI_SR_FLAG_TXE) == BIT_RESET)
		;
	SPIx->DR = data;
	while (READ_BIT(SPIx->SR, SPI_SR_FLAG_BSY) == SET)
		;
	(void)SPIx->DR;
	CS_ON;
}

uint8_t SPI_TransmitReceive(__IO SPI_TypeDef *SPIx, uint8_t data)
{
	while (READ_BIT(SPIx->SR, SPI_SR_FLAG_TXE) == BIT_RESET)
		;
	SPIx->DR = data;
	while (READ_BIT(SPIx->SR, SPI_SR_FLAG_RXNE) == BIT_RESET)
		;
	while (READ_BIT(SPIx->SR, SPI_SR_FLAG_BSY) == SET)
		;
	return (uint8_t)SPIx->DR;
}

void SPI_SendCommand(__IO SPI_TypeDef *SPIx, uint8_t data)
{
	CS_OFF;
	SPI_TransmitReceive(SPIx, data);
	CS_ON;
}
