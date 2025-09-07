#include "peripherals.h"
#include "ring_buffer.h"

#define UART_BUFFER_SIZE 128
static uint8_t uart_rx_data[UART_BUFFER_SIZE];
static ring_buffer_t uart_rx_buffer;

void USART1_Config(void);
void USART1_Polling(void);
int main()
{
	RCC_Clock72MHz_HSE();
	SysTick_Init();
	USART1_Config();
	ring_buffer_init(&uart_rx_buffer, uart_rx_data, UART_BUFFER_SIZE);

	while (1)
	{
		USART1_Polling();
		uint8_t data;
		if (ring_buffer_get(&uart_rx_buffer, &data))
		{
			USART_SendChar(USART1, data);
		}
	}
}

void USART1_Config(void)
{
	USART_HandleTypeDef uart;
	uart.USARTx = USART1;
	uart.BaudRate = USART_BRR_115200;
	uart.WordLength = USART_CR1_M;
	uart.StopBits = USART_CR2_STOP_1;
	uart.IRQ_Enable = DISABLE;
	USART_Init(&uart);
}

void USART1_Polling(void)
{
	if (READ_BIT(USART1->SR, USART_SR_RXNE))
	{
		uint8_t tmpreg = (uint8_t)(USART1->DR & 0xFF);
		ring_buffer_put(&uart_rx_buffer, tmpreg);
	}
}
