/***************************************************************
*	Includes
****************************************************************/
#include "stm32f10x.h"                  
#include "delay.h"
#include "uart.h"
#include <stdio.h>

/***************************************************************
*	Prototypes
****************************************************************/
void GPIO_Config(void);
void setup(void);
void loop(void);

int main()
{
	setup();
	uint32_t start = millis();
	
	while (1)
	{
		if (millis() - start > 500)
		{
			start = millis();
			GPIOC->ODR ^= GPIO_Pin_15;
		}
	}
}

/***************************************************************
*	APIs
****************************************************************/

void GPIO_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef gpio = {0};
	gpio.GPIO_Pin = GPIO_Pin_15;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &gpio);
}

void setup(void)
{
	SystemInit();
	SCB->VTOR = 0x08004000;
	Delay_Init();
	USART_Select(USART2);
	USART_Setup(115200);
	Delay_Ms(300);
	GPIO_Config();
	printf("Update Firmware thanh cong!\r\n");
}
