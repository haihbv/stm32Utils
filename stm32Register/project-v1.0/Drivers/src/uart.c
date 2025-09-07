#include "uart.h"
#include "rcc.h"
#include "gpio.h"
#include "exti.h"

uint16_t USART_GetBaudRate(uint32_t pclk, uint32_t baudrate)
{
    uint32_t usartdiv = ((pclk) / (16U * (uint32_t)baudrate)) * 100U;
    uint16_t mantissa = (uint16_t)(usartdiv / 100U);
    uint16_t fraction = (uint16_t)((((usartdiv - (mantissa * 100U)) * 16U) + 50U) / 100U);
    return (uint16_t)((mantissa << 4) | (fraction & 0x0F));
}
void USART_GPIO_Config(__IO USART_TypeDef *USARTx)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    if (USARTx == USART1)
    {
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pin = GPIO_PIN_9;
        GPIO_InitStruct.Speed = GPIO_SPEED_50MHZ;
        GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
    else if (USARTx == USART2)
    {
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pin = GPIO_PIN_2;
        GPIO_InitStruct.Speed = GPIO_SPEED_50MHZ;
        GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pin = GPIO_PIN_3;
        GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
    else if (USARTx == USART3)
    {
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Speed = GPIO_SPEED_50MHZ;
        GPIO_Init(GPIOB, &GPIO_InitStruct);

        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pin = GPIO_PIN_11;
        GPIO_Init(GPIOB, &GPIO_InitStruct);
    }
}
void USART_Init(USART_HandleTypeDef *huart)
{
    if (huart->USARTx == USART1)
    {
        RCC_APB2ClockCmd(RCC_APB2_GPIOA | RCC_APB2_USART1, ENABLE);
    }
    else if (huart->USARTx == USART2)
    {
        RCC_APB1ClockCmd(RCC_APB1_USART2, ENABLE);
        RCC_APB2ClockCmd(RCC_APB2_GPIOA, ENABLE);
    }
    else if (huart->USARTx == USART3)
    {
        RCC_APB1ClockCmd(RCC_APB1_USART3, ENABLE);
        RCC_APB2ClockCmd(RCC_APB2_GPIOB, ENABLE);
    }

    USART_GPIO_Config(huart->USARTx);

    if (huart->USARTx == USART1)
    {
        huart->USARTx->BRR = USART_GetBaudRate(USART_CLK_FRE_72Mhz, huart->BaudRate);
    }
    else
    {
        huart->USARTx->BRR = USART_GetBaudRate(USART_CLK_FRE_36Mhz, huart->BaudRate);
    }

    SET_BIT(huart->USARTx->CR1, USART_CR1_ENABLE_MASK);
    CLEAR_BIT(huart->USARTx->CR1, USART_CR1_PCE | USART_CR1_M);

    if (huart->StopBits == USART_CR2_STOP_1)
    {
        huart->USARTx->CR2 &= ~USART_CR2_STOP_2;
    }
    else if (huart->StopBits == USART_CR2_STOP_2)
    {
        huart->USARTx->CR2 |= USART_CR2_STOP_2;
    }
    if (huart->IRQ_Enable == ENABLE)
    {
        SET_BIT(huart->USARTx->CR1, USART_CR1_IRQ_MASK);
        if (huart->USARTx == USART1)
        {
            NVIC_EnableIRQ(USART1_IRQn);
        }
        else if (huart->USARTx == USART2)
        {
            NVIC_EnableIRQ(USART2_IRQn);
        }
        else if (huart->USARTx == USART3)
        {
            NVIC_EnableIRQ(USART3_IRQn);
        }
    }
}
void USART_SendData(__IO USART_TypeDef *USARTx, uint16_t Data)
{
    USARTx->DR = (Data & (uint16_t)0x01FF);
}
void USART_SendChar(__IO USART_TypeDef *USARTx, char c)
{
    while (!(READ_BIT(USARTx->SR, USART_SR_TXE)))
        ; // Wait until TXE is set

    USARTx->DR = c;
}
void USART_SendString(__IO USART_TypeDef *USARTx, const char *str)
{
    while (*str)
    {
        USART_SendChar(USARTx, *str++);
    }
}
