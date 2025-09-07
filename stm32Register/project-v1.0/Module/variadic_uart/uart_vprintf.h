#ifndef __UART_VPRINTF_H
#define __UART_VPRINTF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32system.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
typedef struct
{
	void (*Init)(uint32_t baudrate);
	void (*Print)(const char *str, ...);
	uint8_t (*Scan)(uint8_t *data);
} UART_TypeDefStruct;

extern UART_TypeDefStruct UART1;
extern UART_TypeDefStruct UART2;
extern UART_TypeDefStruct UART3;

#ifdef __cplusplus
}
#endif

#endif /* __UART_VPRINTF_H */
