#ifndef _AFIO_H
#define _AFIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32system.h"

typedef union
{
	__IO uint32_t ALL;
	struct 
	{
		__IO uint32_t PIN       :4;
		__IO uint32_t PORT      :3;
		__IO uint32_t EVOE      :1;
		__IO uint32_t RESERVED  :24;
	} BITS;
} AFIO_EVCR_t;

typedef union
{
	__IO uint32_t ALL;
	struct 
	{
		__IO uint32_t SPI1_REMAP         :1;
		__IO uint32_t I2C1_REMAP         :1;
		__IO uint32_t USART1_REMAP       :1;
		__IO uint32_t USART2_REMAP       :1;
		__IO uint32_t USART3_REMAP       :2;
		__IO uint32_t TIM1_REMAP         :2;
		__IO uint32_t TIM2_REMAP         :2;
		__IO uint32_t TIM3_REMAP         :2;
		__IO uint32_t TIM4_REMAP         :1;
		__IO uint32_t CAN_REMAP          :2;
		__IO uint32_t PD01_REMAP         :1;
		__IO uint32_t TIM5CH4_REMAP      :1;
		__IO uint32_t ADC1_ETRGINJ_REMAP :1;
		__IO uint32_t ADC1_ETRGREG_REMAP :1;
		__IO uint32_t ADC2_ETRGINJ_REMAP :1;
		__IO uint32_t ADC2_ETRGREG_REMAP :1;
		__IO uint32_t SWJ_CFG            :3; 
		__IO uint32_t RESERVED           :8;
	} BITS;
} AFIO_MAPR_t;

typedef union
{
	__IO uint32_t ALL;
	struct
	{
		__IO uint32_t EXTI0      :4;
		__IO uint32_t EXTI1      :4;
		__IO uint32_t EXTI2      :4;
		__IO uint32_t EXTI3      :4;
		__IO uint32_t RESERVED   :16;
	} BITS;
} AFIO_EXTICR1_t;

typedef union
{
	__IO uint32_t ALL;
	struct
	{
		__IO uint32_t EXTI4      :4;
		__IO uint32_t EXTI5      :4;
		__IO uint32_t EXTI6      :4;
		__IO uint32_t EXTI7      :4;
		__IO uint32_t RESERVED   :16;
	} BITS;
} AFIO_EXTICR2_t;

typedef union
{
	__IO uint32_t ALL;
	struct
	{
		__IO uint32_t EXTI8      :4;
		__IO uint32_t EXTI9      :4;
		__IO uint32_t EXTI10     :4;
		__IO uint32_t EXTI11     :4;
		__IO uint32_t RESERVED   :16;
	} BITS;
} AFIO_EXTICR3_t;

typedef union
{
	__IO uint32_t ALL;
	struct
	{
		__IO uint32_t EXTI12     :4;
		__IO uint32_t EXTI13     :4;
		__IO uint32_t EXTI14     :4;
		__IO uint32_t EXTI15     :4;
		__IO uint32_t RESERVED   :16;
	} BITS;
} AFIO_EXTICR4_t;

typedef union
{
	__IO uint32_t ALL;
	struct
	{
		__IO uint32_t RESERVED0       :2;
		__IO uint32_t TIM9_REMAP      :1;
		__IO uint32_t TIM10_REMAP     :1;
		__IO uint32_t TIM11_REMAP     :1;
		__IO uint32_t TIM13_REMAP     :1;
		__IO uint32_t TIM14_REMAP     :1;
		__IO uint32_t FSMC_NADV_REMAP :1;
		__IO uint32_t RESERVED1       :24;
	} BITS;
} AFIO_MAPR2_t;


typedef struct
{
	AFIO_EVCR_t      EVCR;
	AFIO_MAPR_t      MAPR;
	AFIO_EXTICR1_t	 EXTICR1;
	AFIO_EXTICR2_t	 EXTICR2;
	AFIO_EXTICR3_t	 EXTICR3;
	AFIO_EXTICR4_t	 EXTICR4;
	AFIO_MAPR2_t     MAPR2;
} AFIO_TypeDef;

#ifdef __cplusplus
}
#endif

#endif /* _AFIO_H */

