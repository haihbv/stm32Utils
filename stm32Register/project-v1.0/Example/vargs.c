#include "peripherals.h"
#include "uart_vprintf.h"

static uint8_t buffer[128];

int main()
{
	UART1.Init(USART_BRR_9600);

	UART1.Print("UART1 Ready! Send something...\r\n");

	// UART1.Print("Char: %c, String: %s, Dec: %d, Hex: %h, Float: %f, Percent: %%\n", 'A', "hello", 123, 0xAB, 3.14);

	while (1)
	{
		if (UART1.Scan(buffer))
		{
			UART1.Print("\nChuoi nhan duoc la: %s\n", buffer);
		}
	}
}
