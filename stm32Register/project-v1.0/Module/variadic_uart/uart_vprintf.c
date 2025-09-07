#include "uart_vprintf.h"
#include "rcc.h"
#include "uart.h"
#include "exti.h"

UART_TypeDefStruct UART1;
UART_TypeDefStruct UART2;
UART_TypeDefStruct UART3;

typedef enum
{
    U1 = 0x00,
    U2,
    U3
} UARTx_e;

static volatile uint8_t UARTx_dataReceived[3][130] = {0};
static volatile uint8_t UARTx_rx_flag[3] = {0, 0, 0};
static volatile uint8_t UARTx_idx[3] = {0, 0, 0};

void USART_GPIO_Config(__IO USART_TypeDef *USARTx);
void UARTx_Init(__IO USART_TypeDef *UART, uint32_t baudrate);
void UARTx_SendData(__IO USART_TypeDef *UART, const char *str, va_list args);
uint8_t UARTx_ReceiveData(UARTx_e Ux, uint8_t *data);
static void UARTx_IRQHandler_Handler(UARTx_e Ux, __IO USART_TypeDef *UART);

void UART1_Init(uint32_t baudrate);
void UART2_Init(uint32_t baudrate);
void UART3_Init(uint32_t baudrate);
void UART1_Print(const char *str, ...);
void UART2_Print(const char *str, ...);
void UART3_Print(const char *str, ...);
uint8_t UART1_Scan(uint8_t *data);
uint8_t UART2_Scan(uint8_t *data);
uint8_t UART3_Scan(uint8_t *data);

void UART_FirstInit(void) __attribute__((constructor));

void UART_FirstInit(void)
{
    UART1.Init = UART1_Init;
    UART1.Scan = UART1_Scan;
    UART1.Print = UART1_Print;

    UART2.Init = UART2_Init;
    UART2.Scan = UART2_Scan;
    UART2.Print = UART2_Print;

    UART3.Init = UART3_Init;
    UART3.Scan = UART3_Scan;
    UART3.Print = UART3_Print;
}

void UARTx_Init(__IO USART_TypeDef *UART, uint32_t baudrate)
{
    USART_HandleTypeDef UART_InitStruct;

    if (UART == USART1)
    {
        RCC_APB2ClockCmd(RCC_APB2_USART1 | RCC_APB2_GPIOA, ENABLE);
        USART_GPIO_Config(USART1);
        NVIC_EnableIRQ(USART1_IRQn);
    }
    else if (UART == USART2)
    {
        RCC_APB1ClockCmd(RCC_APB1_USART2, ENABLE);
        RCC_APB2ClockCmd(RCC_APB2_GPIOA, ENABLE);
        USART_GPIO_Config(USART2);

        NVIC_EnableIRQ(USART2_IRQn);
    }
    else if (UART == USART3)
    {
        RCC_APB1ClockCmd(RCC_APB1_USART3, ENABLE);
        RCC_APB2ClockCmd(RCC_APB2_GPIOB, ENABLE);
        USART_GPIO_Config(USART3);

        NVIC_EnableIRQ(USART3_IRQn);
    }

    UART_InitStruct.BaudRate = baudrate;
    UART_InitStruct.USARTx = UART;
    UART_InitStruct.StopBits = USART_CR2_STOP_1;
    UART_InitStruct.WordLength = USART_CR1_M;
    UART_InitStruct.IRQ_Enable = ENABLE;
    USART_Init(&UART_InitStruct);
		
		SET_BIT(UART->CR1, USART_CR1_UE | USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE);
}

void UART1_Init(uint32_t baudrate)
{
    UARTx_Init(USART1, baudrate);
}
void UART2_Init(uint32_t baudrate)
{
    UARTx_Init(USART2, baudrate);
}
void UART3_Init(uint32_t baudrate)
{
    UARTx_Init(USART3, baudrate);
}

void UART1_Print(const char *str, ...)
{
    va_list args;
    va_start(args, str);
    UARTx_SendData(USART1, str, args);
    va_end(args);
}
void UART2_Print(const char *str, ...)
{
    va_list args;
    va_start(args, str);
    UARTx_SendData(USART2, str, args);
    va_end(args);
}
void UART3_Print(const char *str, ...)
{
    va_list args;
    va_start(args, str);
    UARTx_SendData(USART3, str, args);
    va_end(args);
}

uint8_t UART1_Scan(uint8_t *data)
{
    return UARTx_ReceiveData(U1, data);
}
uint8_t UART2_Scan(uint8_t *data)
{
    return UARTx_ReceiveData(U2, data);
}
uint8_t UART3_Scan(uint8_t *data)
{
    return UARTx_ReceiveData(U3, data);
}
static inline void UART_SendChar(__IO USART_TypeDef *UART, const char str)
{
    while (!(READ_BIT(UART->SR, USART_SR_TXE)))
        ;
    USART_SendData(UART, str);
}
static inline void UART_SendStr(__IO USART_TypeDef *UART, const char *str)
{
    do
    {
        UART_SendChar(UART, *str);

    } while (*(++str));
}

void UARTx_SendData(__IO USART_TypeDef *UART, const char *str, va_list args)
{
    if (!str)
        return; // Safety check for NULL input string
		
		char number[32];
		
    do
    {
        if (*str == '%')
        {
            switch (*(++str))
            {
            case 's':
            {
                char *temp_str = va_arg(args, char *);
                if (temp_str != NULL)
                {
                    UART_SendStr(UART, temp_str);
                }
                else
                {
                    UART_SendStr(UART, "(null)");
                }
                continue;
            }

            case 'd':
            {
                sprintf(number, "%d", va_arg(args, int));
                UART_SendStr(UART, number);
                continue;
            }

            case 'h':
            {
                sprintf(number, "%02X", va_arg(args, int));
                UART_SendStr(UART, number);
                continue;
            }

            case 'c':
            {
                char ch = (char)va_arg(args, int);
                UART_SendChar(UART, ch);
                continue;
            }

            case 'f':
            {
                sprintf(number, "%f", va_arg(args, double));
                UART_SendStr(UART, number);
                continue;
            }

            case '%': // Literal '%'
            {
                UART_SendChar(UART, '%');
                continue;
            }

            default: // Unknown format - send as is
            {
                UART_SendChar(UART, '%');
                UART_SendChar(UART, *str);
                continue;
            }
            }
        }

        UART_SendChar(UART, *str);
    } while (*(++str));
}

uint8_t UARTx_ReceiveData(UARTx_e Ux, uint8_t *data)
{
    if (UARTx_rx_flag[Ux] == 2 && UARTx_idx[Ux] > 0)
    {
        UARTx_dataReceived[Ux][UARTx_idx[Ux] - 1] = '\0';

        uint8_t i = 0;
        while ((data[i] = UARTx_dataReceived[Ux][i]) != '\0')
            i++;

        UARTx_idx[Ux] = 0;
        UARTx_rx_flag[Ux] = 0;
        return 1;
    }
    return 0;
}

void UARTx_IRQHandler_Handler(UARTx_e Ux, __IO USART_TypeDef *UART)
{
    if (READ_BIT(UART->SR, USART_SR_RXNE))
    {
        uint8_t byte = (uint8_t)UART->DR;
        if (UARTx_idx[Ux] < sizeof(UARTx_dataReceived[Ux]) - 1)
        {
            UARTx_dataReceived[Ux][UARTx_idx[Ux]++] = byte;
        }

        UARTx_rx_flag[Ux] = 1;

        if (byte == '\n')
        {
            UARTx_rx_flag[Ux] = 2;
        }
    }
}

void USART1_IRQHandler(void)
{
    UARTx_IRQHandler_Handler(U1, USART1);
}

void USART2_IRQHandler(void)
{
    UARTx_IRQHandler_Handler(U2, USART2);
}

void USART3_IRQHandler(void)
{
    UARTx_IRQHandler_Handler(U3, USART3);
}
