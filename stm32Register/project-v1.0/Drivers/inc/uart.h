#ifndef UART_H
#define UART_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32system.h"
	
#define USART_CR1_UE            (1U << 13)  // USART Enable
#define USART_CR1_M             (1U << 12)  // Word Length
#define USART_CR1_PCE           (1U << 10)  // Parity Control
#define USART_CR1_RXNEIE        (1U << 5)   // RXNE Interrupt Enable
#define USART_CR1_TE            (1U << 3)   // Transmitter Enable
#define USART_CR1_RE            (1U << 2)   // Receiver Enable
#define USART_CR1_ENABLE_MASK   (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE)
#define USART_CR1_IRQ_MASK      (USART_CR1_RXNEIE)

#define USART_CR2_STOP_1        (0U << 12)  // 1 Stop Bit
#define USART_CR2_STOP_2        (2U << 12)  // 2 Stop Bits

#define USART_SR_TXE            (1U << 7)   // Transmit Data Register Empty
#define USART_SR_RXNE           (1U << 5)   // Read Data Register Not Empty

#define USART_CLK_FRE_72Mhz     (72000000U) // Clock frequency for USART at 72MHz
#define USART_CLK_FRE_36Mhz     (36000000U) // Clock frequency for USART at 36MHz
#define USART_CLK_FRE_16Mhz     (16000000U) // Clock frequency for USART at 16MHz
#define USART_CLK_FRE_8Mhz      (8000000U)  // Clock frequency for USART at 8MHz


// USART baud rate definitions
#define USART_BRR_4800          (4800U)
#define USART_BRR_9600          (9600U)
#define USART_BRR_14400         (14400U)
#define USART_BRR_19200         (19200U)
#define USART_BRR_38400         (38400U)
#define USART_BRR_57600         (57600U)
#define USART_BRR_115200        (115200U)

typedef struct __attribute__((packed))
{
    __IO USART_TypeDef *USARTx; 
    uint32_t BaudRate;
    uint32_t WordLength; 
    uint32_t StopBits;
	FunctionalState IRQ_Enable;
} USART_HandleTypeDef;

uint16_t USART_GetBaudRate(uint32_t pclk, uint32_t baudrate);
extern void USART_GPIO_Config(__IO USART_TypeDef *USARTx);
void USART_Init(USART_HandleTypeDef *huart);
void USART_SendData(__IO USART_TypeDef *USARTx, uint16_t Data);
void USART_SendChar(__IO USART_TypeDef *USARTx, char c);
void USART_SendString(__IO USART_TypeDef *USARTx, const char *str);

void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
#ifdef __cplusplus
}
#endif

#endif /* UART_H */


