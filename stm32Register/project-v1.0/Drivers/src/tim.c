#include "tim.h"
#include "gpio.h"
#include "rcc.h"

void TIM_Cmd(volatile TIM_TypeDef *TIMx, uint32_t cmd)
{
	if (cmd != DISABLE)
	{
		TIMx->CR1 |= TIM_CR1_CEN;
	}
	else
	{
		TIMx->CR1 &= ~(uint32_t)TIM_CR1_CEN;
	}
}

void TIM_BaseInit(volatile TIM_TypeDef *TIMx, TIM_BaseConfig_t config)
{
	TIMx->PSC = config.Prescaler;
	TIMx->ARR = config.AutoReload;
	TIMx->CNT = 0;
	TIMx->CR1 |= TIM_CR1_ARPE;
	TIMx->EGR |= TIM_EGR_UG;
}

void TIM_PWMInit(volatile TIM_TypeDef *TIMx, TIM_OCConfig_t config)
{
	switch (config.Channel)
	{
	case TIM_CHANNEL_1:
		TIMx->CCMR1 &= ~(uint32_t)TIM_CCMR1_OC1M_MASK;
		TIMx->CCMR1 |= (uint8_t)(config.OCMode << 4U);
		TIMx->CCMR1 |= TIM_CCMR1_OC1PE;
		TIMx->CCR1 = config.Pulse;
		TIMx->CCER |= TIM_CCER_CC1E;
		break;

	case TIM_CHANNEL_2:
		TIMx->CCMR1 &= ~(uint32_t)TIM_CCMR1_OC2M_MASK;
		TIMx->CCMR1 |= (uint8_t)(config.OCMode << 12U);
		TIMx->CCMR1 |= TIM_CCMR1_OC2PE;
		TIMx->CCR2 = config.Pulse;
		TIMx->CCER |= TIM_CCER_CC2E;
		break;

	case TIM_CHANNEL_3:
		TIMx->CCMR2 &= ~(uint32_t)TIM_CCMR2_OC3M_MASK;
		TIMx->CCMR2 |= (uint8_t)(config.OCMode << 4U);
		TIMx->CCMR2 |= TIM_CCMR2_OC3PE;
		TIMx->CCR3 = config.Pulse;
		TIMx->CCER |= TIM_CCER_CC3E;
		break;

	case TIM_CHANNEL_4:
		TIMx->CCMR2 &= ~(uint32_t)TIM_CCMR2_OC4M_MASK;
		TIMx->CCMR2 |= (uint8_t)(config.OCMode << 12U);
		TIMx->CCMR2 |= TIM_CCMR2_OC4PE;
		TIMx->CCR4 = config.Pulse;
		TIMx->CCER |= TIM_CCER_CC4E;
		break;
	}

	TIMx->CR1 |= TIM_CR1_ARPE;

	TIMx->EGR |= TIM_EGR_UG;

	if (TIMx == TIM1)
	{
		TIMx->BDTR |= TIM_BDTR_MOE;
	}
	else if (TIMx != TIM1)
	{
		return; // only TIM1 supports MOE
	}
}

void TIM_SetCompare(volatile TIM_TypeDef *TIMx, uint8_t channel, uint16_t value)
{
	switch (channel)
	{
	case TIM_CHANNEL_1:
		TIMx->CCR1 = value;
		break;
	case TIM_CHANNEL_2:
		TIMx->CCR2 = value;
		break;
	case TIM_CHANNEL_3:
		TIMx->CCR3 = value;
		break;
	case TIM_CHANNEL_4:
		TIMx->CCR4 = value;
		break;
	default:
		break;
	}
}

void TIM3_Delay_Init(void)
{
	RCC_APB1ClockCmd(RCC_APB1_TIM3, ENABLE);

	TIM3->ARR = 9999;
	TIM3->PSC = 72 - 1;

	TIM_Cmd(TIM3, ENABLE);
}

void delay_us(uint32_t us)
{
	uint16_t start = (uint16_t)TIM3->CNT;
	while ((uint16_t)(TIM3->CNT - start) < us)
		;
}

// void delay_ms(uint32_t ms)
//{
//	while (ms--)
//	{
//		delay_us(1000);
//	}
// }
void Servo_Init(void)
{
	RCC_APB1ClockCmd(RCC_APB1_TIM2, ENABLE);
	RCC_APB2ClockCmd(RCC_APB2_GPIOA, ENABLE);

	GPIO_InitTypeDef gpio;
	gpio.Pin = GPIO_PIN_0;
	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Speed = GPIO_SPEED_50MHZ;
	GPIO_Init(GPIOA, &gpio);

	TIM_BaseConfig_t tim;
	tim.Prescaler = 71;
	tim.AutoReload = 19999;
	TIM_BaseInit(TIM2, tim);

	TIM_OCConfig_t pwm;
	pwm.Channel = TIM_CHANNEL_1;
	pwm.OCMode = TIM_OCMODE_PWM1;
	pwm.Pulse = 1500;
	TIM_PWMInit(TIM2, pwm);

	TIM_Cmd(TIM2, ENABLE);
}
void Servo_SetAngle(uint8_t angle)
{
	if (angle > 180)
	{
		angle = 180;
	}
	uint16_t pulse = 500 + (angle * 2000) / 180;
	TIM2->CCR1 = pulse;
}
