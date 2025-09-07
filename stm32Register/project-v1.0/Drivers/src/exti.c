#include "exti.h"
#include "afio.h"

void EXTI0_IRQHandler(void)
{
    if (EXTI->PR.BITS.BIT0 != 0)
    {
        EXTI->PR.ALL = (uint32_t)(1 << 0);
    }
}

int8_t get_pin_number(uint16_t GPIO_Pin)
{
    for (int8_t i = 0; i < 16; i++)
    {
        if (GPIO_Pin & (1 << i))
            return i;
    }
    return -1;
}

int8_t get_exti_line(volatile GPIO_TypeDef *GPIOx)
{
    if (GPIOx == GPIOA)
    {
        return 0;
    }
    if (GPIOx == GPIOB)
    {
        return 1;
    }
    if (GPIOx == GPIOC)
    {
        return 2;
    }
    return -1;
}

void EXTI_Init(volatile GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t mode)
{
    int8_t extiLine = get_exti_line(GPIOx);
    int8_t pinNumber = get_pin_number(GPIO_Pin);
    if (extiLine < 0 || pinNumber < 0)
    {
        return;
    }
    uint32_t extiConfig = (pinNumber % 4) * 4;
    if (pinNumber < 4)
    {
        AFIO->EXTICR1.ALL &= ~(uint32_t)(0x0F << extiConfig);
        AFIO->EXTICR1.ALL |= (uint32_t)(extiLine << extiConfig);
    }
    else if (pinNumber < 8)
    {
        AFIO->EXTICR2.ALL &= ~(uint32_t)(0x0F << extiConfig);
        AFIO->EXTICR2.ALL |= (uint32_t)(extiLine << extiConfig);
    }
    else if (pinNumber < 12)
    {
        AFIO->EXTICR3.ALL &= ~(uint32_t)(0x0F << extiConfig);
        AFIO->EXTICR3.ALL |= (uint32_t)(extiLine << extiConfig);
    }
    else
    {
        AFIO->EXTICR4.ALL &= ~(uint32_t)(0x0F << extiConfig);
        AFIO->EXTICR4.ALL |= (uint32_t)(extiLine << extiConfig);
    }

    EXTI->IMR.ALL |= (1 << pinNumber);

    switch (mode)
    {
    case EXTI_MODE_RISING:
        EXTI->RTSR.ALL |= (1 << pinNumber);
        EXTI->FTSR.ALL &= ~(1 << pinNumber);
        break;
    case EXTI_MODE_FALLING:
        EXTI->RTSR.ALL &= ~(1 << pinNumber);
        EXTI->FTSR.ALL |= (1 << pinNumber);
        break;
    case EXTI_MODE_BOTH:
        EXTI->RTSR.ALL |= (1 << pinNumber);
        EXTI->FTSR.ALL |= (1 << pinNumber);
        break;
    default:
        return;
    }

    // Enable NVIC interrupt đúng mapping STM32F1
    if (pinNumber <= 4)
    {
        NVIC->ISER[0] |= (1 << (EXTI0_IRQn + pinNumber));
    }
    else if (pinNumber <= 9)
    {
        NVIC->ISER[0] |= (1 << EXTI9_5_IRQn);
    }
    else if (pinNumber <= 15)
    {
        NVIC->ISER[EXTI15_10_IRQn / 32] |= (1 << (EXTI15_10_IRQn % 32));
    }
}

void NVIC_EnableIRQ(IRQn_Type IRQn)
{
    if (IRQn < 0 || IRQn >= 84)
        return;
    NVIC->ISER[IRQn / 32] |= (1 << (IRQn % 32));
}
