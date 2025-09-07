#include "adc.h"
#include "rcc.h"
#include "systick.h"
#include "gpio.h"

void ADC1_CHO_Init(void)
{
	GPIO_InitTypeDef gpio;
	gpio.Mode = GPIO_MODE_ANALOG;
	gpio.Pin = GPIO_PIN_0;
	gpio.Speed = GPIO_SPEED_50MHZ;
	GPIO_Init(GPIOA, &gpio);
	
	ADC1->SMPR2 &= ~(uint32_t)(0x07 << 0);
	ADC1->SMPR2 |= (1 << 1);
	
	ADC1->SQR3 = 0;
	
	ADC1->CR2 |= (1 << 1);
	ADC1->CR2 |= (1 << 0);
	delay_ms(1);
	ADC1->CR2 |= (1 << 0);
	
	ADC1->CR2 |= (1 << 3);
	while (ADC1->CR2 & (1 << 3));
	
	ADC1->CR2 |= (1 << 2);
	while (ADC1->CR2 & (1 << 2));
		
	ADC1->CR2 |= (1 << 22);
}
uint16_t ADC1_CHO_Read(void)
{
	while (!(ADC1->SR & (1 << 1)));
	return (uint16_t)(ADC1->DR & 0xFFFF);
}
