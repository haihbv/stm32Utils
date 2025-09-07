#ifndef __STM32SYSTEM_H
#define __STM32SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32util.h" // dùng __IO

// Base addresses
#define GPIOA_BASE 		(0x40010800UL)
#define GPIOB_BASE 		(0x40010C00UL)
#define GPIOC_BASE 		(0x40011000UL)
#define RCC_BASE    	(0x40021000UL)
#define FLASH_BASE 		(0x40022000UL)
#define AFIO_BASE 		(0x40010000UL)
#define NVIC_Base 		(0xE000E100UL)
#define EXTI_Base 		(0x40010400UL)
#define TIM1_Base 		(0x40012C00UL)
#define TIM2_Base 		(0x40000000UL)
#define TIM3_Base 		(0x40000400UL)
#define TIM4_Base 		(0x40000800UL)
#define ADC1_Base 		(0x40012400UL)
#define ADC2_Base 		(0x40012800UL)
#define USART1_Base		(0x40013800UL)
#define USART2_Base		(0x40004400UL)
#define USART3_Base		(0x40004800UL)
#define SPI1_Base       (0x40013000UL)
#define SPI2_Base       (0x40003800UL)
#define I2C1_Base		(0x40005400UL)
#define I2C2_Base		(0x40005800UL)
#define USB_Base		(0x40005C00UL)

// ===== Peripheral Structs =====
// FLASH registers
typedef union
{
	__IO uint32_t REG;
	struct
	{
		uint32_t LATENCY 		: 3;
		uint32_t HLFCYA 		: 1;
		uint32_t PRFTBE 		: 1;
		uint32_t PRFTBS 		: 1;
		uint32_t RESERVED 		: 26;
	} BITS;
} FLASH_ACR_t;

typedef struct
{
	FLASH_ACR_t 	ACR;
} FLASH_TypeDef;

// RCC registers

typedef union
{
	__IO uint32_t REG;
	struct
	{
		__IO uint32_t HSION 	: 1;
		__IO uint32_t HSIRDY 	: 1;
		__IO uint32_t RESERVED0 : 1;
		__IO uint32_t HSITRIM 	: 5;
		__IO uint32_t HSICAL 	: 8;
		__IO uint32_t HSEON 	: 1;
		__IO uint32_t HSERDY 	: 1;
		__IO uint32_t HSEBYP 	: 1;
		__IO uint32_t CSSON 	: 1;
		__IO uint32_t RESERVED1 : 4;
		__IO uint32_t PLLON 	: 1;
		__IO uint32_t PLLRDY 	: 1;
		__IO uint32_t RESERVED2 : 6;
	} BITS;
} RCC_CR_t;

typedef union
{
	__IO uint32_t REG;
	struct
	{
		uint32_t SW 			: 2;
		uint32_t SWS 			: 2;
		uint32_t HPRE 			: 4;
		uint32_t PPRE1 			: 3;
		uint32_t PPRE2 			: 3;
		uint32_t ADCPRE 		: 2;
		uint32_t PLLSRC 		: 1;
		uint32_t PLLXTPRE 		: 1;
		uint32_t PLLMUL 		: 4;
		uint32_t USBPRE 		: 1;
		uint32_t RESERVED0 		: 1;
		uint32_t MCO 			: 3;
		uint32_t RESERVED1 		: 5;
	} BITS;
} RCC_CFGR_t;

typedef union
{
	__IO uint32_t REG;
	struct
	{
		uint32_t LSIRDYF 		: 1;
		uint32_t LSERDYF 		: 1;
		uint32_t HSIRDYF 		: 1;
		uint32_t HSERDYF 		: 1;
		uint32_t PLLRDYF 		: 1;
		uint32_t RESERVED0 		: 2;
		uint32_t CSSF 			: 1;
		uint32_t LSIRDYIE 		: 1;
		uint32_t LSERDYIE 		: 1;
		uint32_t HSIRDYIE 		: 1;
		uint32_t HSERDYIE 		: 1;
		uint32_t PLLRDYIE 		: 1;
		uint32_t RESERVED1 		: 3;
		uint32_t LSIRDYC 		: 1;
		uint32_t LSERDYC 		: 1;
		uint32_t HSIRDYC 		: 1;
		uint32_t HSERDYC 		: 1;
		uint32_t PLLRDYC 		: 1;
		uint32_t RESERVED2 		: 2;
		uint32_t CSSC 			: 1;
		uint32_t RESERVED3 		: 8;
	} BITS;
} RCC_CIR_t;

typedef union
{
	__IO uint32_t REG;
	struct
	{
		uint32_t AFIORST 		: 1;
		uint32_t RESERVED0 		: 1;
		uint32_t IOPARST 		: 1;
		uint32_t IOPBRST 		: 1;
		uint32_t IOPCRST 		: 1;
		uint32_t IOPDRST 		: 1;
		uint32_t IOPERST 		: 1;
		uint32_t IOPFRST 		: 1;
		uint32_t IOPGRST 		: 1;
		uint32_t ADC1RST 		: 1;
		uint32_t ADC2RST 		: 1;
		uint32_t TIM1RST 		: 1;
		uint32_t SPI1RST 		: 1;
		uint32_t TIM8RST 		: 1;
		uint32_t USART1RST 		: 1;
		uint32_t ADC3RST 		: 1;
		uint32_t RESERVED1 		: 3;
		uint32_t TIM9RST 		: 1;
		uint32_t TIM10RST 		: 1;
		uint32_t TIM11RST 		: 1;
		uint32_t RESERVED2 		: 10;
	} BITS;
} RCC_APB2RSTR_t;

typedef union
{
	__IO uint32_t REG;
	struct
	{
		uint32_t TIM2RST 		: 1;
		uint32_t TIM3RST 		: 1;
		uint32_t TIM4RST 		: 1;
		uint32_t TIM5RST 		: 1;
		uint32_t TIM6RST 		: 1;
		uint32_t TIM7RST 		: 1;
		uint32_t TIM12RST 		: 1;
		uint32_t TIM13RST 		: 1;
		uint32_t TIM14RST 		: 1;
		uint32_t RESERVED0 		: 2;
		uint32_t WWDGRST 		: 1;
		uint32_t RESERVED1 		: 2;
		uint32_t SPI2RST 		: 1;
		uint32_t SPI3RST 		: 1;
		uint32_t RESERVED2 		: 1;
		uint32_t USART2RST 		: 1;
		uint32_t USART3RST 		: 1;
		uint32_t UART4RST 		: 1;
		uint32_t UART5RST 		: 1;
		uint32_t I2C1RST 		: 1;
		uint32_t I2C2RST 		: 1;
		uint32_t USBRST 		: 1;
		uint32_t RESERVED3 		: 1;
		uint32_t CANRST 		: 1;
		uint32_t RESERVED4 		: 1;
		uint32_t BKPRST 		: 1;
		uint32_t PWRRST 		: 1;
		uint32_t DACRST 		: 1;
		uint32_t RESERVED5 		: 2;
	} BITS;
} RCC_APB1RSTR_t;

typedef union
{
	__IO uint32_t REG;
	struct
	{
		uint32_t DMA1EN 		: 1;
		uint32_t DMA2EN 		: 1;
		uint32_t SRAMEN 		: 1;
		uint32_t RESERVED0 		: 1;
		uint32_t FLITFEN 		: 1;
		uint32_t RESERVED1 		: 1;
		uint32_t CRCEN 			: 1;
		uint32_t RESERVED2 		: 1;
		uint32_t FSMCEN 		: 1;
		uint32_t RESERVED3 		: 1;
		uint32_t SDIOEN 		: 1;
		uint32_t RESERVED4 		: 21;
	} BITS;
} RCC_AHBENR_t;

typedef union
{
	__IO uint32_t REG;
	struct
	{
		uint32_t AFIOEN 		: 1;
		uint32_t RESERVED0 		: 1;
		uint32_t IOPAEN 		: 1;
		uint32_t IOPBEN 		: 1;
		uint32_t IOPCEN 		: 1;
		uint32_t IOPDEN 		: 1;
		uint32_t IOPEEN 		: 1;
		uint32_t IOPFEN 		: 1;
		uint32_t IOPGEN 		: 1;
		uint32_t ADC1EN 		: 1;
		uint32_t ADC2EN 		: 1;
		uint32_t TIM1EN 		: 1;
		uint32_t SPI1EN 		: 1;
		uint32_t TIM8EN 		: 1;
		uint32_t USART1EN 		: 1;
		uint32_t ADC3EN 		: 1;
		uint32_t RESERVED1 		: 3;
		uint32_t TIM9EN 		: 1;
		uint32_t TIM10EN 		: 1;
		uint32_t TIM11EN 		: 1;
		uint32_t RESERVED2 		: 10;
	} BITS;
} RCC_APB2ENR_t;

typedef union
{
	__IO uint32_t REG;
	struct
	{
		uint32_t TIM2EN 		: 1;
		uint32_t TIM3EN 		: 1;
		uint32_t TIM4EN 		: 1;
		uint32_t TIM5EN 		: 1;
		uint32_t TIM6EN 		: 1;
		uint32_t TIM7EN 		: 1;
		uint32_t TIM12EN 		: 1;
		uint32_t TIM13EN 		: 1;
		uint32_t TIM14EN 		: 1;
		uint32_t RESERVED0 		: 2;
		uint32_t WWDGEN 		: 1;
		uint32_t RESERVED1 		: 2;
		uint32_t SPI2EN 		: 1;
		uint32_t SPI3EN 		: 1;
		uint32_t RESERVED2 		: 1;
		uint32_t USART2EN 		: 1;
		uint32_t USART3EN 		: 1;
		uint32_t UART4EN 		: 1;
		uint32_t UART5EN 		: 1;
		uint32_t I2C1EN 		: 1;
		uint32_t I2C2EN 		: 1;
		uint32_t USBEN 			: 1;
		uint32_t RESERVED3 		: 1;
		uint32_t CANEN 			: 1;
		uint32_t RESERVED4 		: 1;
		uint32_t BKPEN 			: 1;
		uint32_t PWREN 			: 1;
		uint32_t DACEN 			: 1;
		uint32_t RESERVED5 		: 2;
	} BITS;
} RCC_APB1ENR_t;

typedef union
{
	__IO uint32_t REG;
	struct
	{
		uint32_t LSEON 			: 1;
		uint32_t LSERDY 		: 1;
		uint32_t LSEBYP 		: 1;
		uint32_t RESERVED0 		: 5;
		uint32_t RTCSEL 		: 2;
		uint32_t RESERVED1 		: 5;
		uint32_t RTCEN 			: 1;
		uint32_t BDRST 			: 1;
		uint32_t RESERVED2 		: 15;
	} BITS;
} RCC_BDCR_t;
typedef union
{
	__IO uint32_t REG;
	struct
	{
		uint32_t LSION 			: 1;
		uint32_t LSIRDY 		: 1;
		uint32_t RESERVED0 		: 22;
		uint32_t RMVF 			: 1;
		uint32_t RESERVED1 		: 1;
		uint32_t PINRSTF 		: 1;
		uint32_t PORRSTF 		: 1;
		uint32_t SFTRSTF 		: 1;
		uint32_t IWDGRSTF 		: 1;
		uint32_t WWDGRSTF 		: 1;
		uint32_t LPWRRSTF 		: 1;
	} BITS;
} RCC_CSR_t;

typedef struct
{
	RCC_CR_t 		CR;
	RCC_CFGR_t 		CFGR;
	RCC_CIR_t 		CIR;
	RCC_APB2RSTR_t 	APB2RSTR;
	RCC_APB1RSTR_t 	APB1RSTR;
	RCC_AHBENR_t 	AHBENR;
	RCC_APB2ENR_t 	APB2ENR;
	RCC_APB1ENR_t 	APB1ENR;
	RCC_BDCR_t 		BDCR;
	RCC_CSR_t 		CSR;
} RCC_TypeDef;

// GPIO registers
typedef union
{
    __IO uint32_t REG;
    struct
    {
        __IO uint32_t MODE0     : 2; 
        __IO uint32_t CNF0      : 2; 
        __IO uint32_t MODE1     : 2; 
        __IO uint32_t CNF1      : 2; 
        __IO uint32_t MODE2     : 2; 
        __IO uint32_t CNF2      : 2; 
        __IO uint32_t MODE3     : 2; 
        __IO uint32_t CNF3      : 2; 
        __IO uint32_t MODE4     : 2; 
        __IO uint32_t CNF4      : 2; 
        __IO uint32_t MODE5     : 2; 
        __IO uint32_t CNF5      : 2; 
        __IO uint32_t MODE6     : 2; 
        __IO uint32_t CNF6      : 2; 
        __IO uint32_t MODE7     : 2; 
        __IO uint32_t CNF7      : 2; 
    } BITS;
} GPIO_CRL_t;
typedef union
{
    __IO uint32_t REG;
    struct
    {
        __IO uint32_t MODE8     : 2; 
        __IO uint32_t CNF8      : 2; 
        __IO uint32_t MODE9     : 2; 
        __IO uint32_t CNF9      : 2; 
        __IO uint32_t MODE10    : 2; 
        __IO uint32_t CNF10     : 2; 
        __IO uint32_t MODE11    : 2; 
        __IO uint32_t CNF11     : 2; 
        __IO uint32_t MODE12    : 2; 
        __IO uint32_t CNF12     : 2; 
        __IO uint32_t MODE13    : 2; 
        __IO uint32_t CNF13     : 2; 
        __IO uint32_t MODE14    : 2; 
        __IO uint32_t CNF14     : 2; 
        __IO uint32_t MODE15    : 2; 
        __IO uint32_t CNF15     : 2; 
    } BITS;
} GPIO_CRH_t;
typedef union
{
    __IO uint32_t REG;
    struct
    {
        __IO uint32_t IDR0      : 1;  
        __IO uint32_t IDR1      : 1;  
        __IO uint32_t IDR2      : 1;  
        __IO uint32_t IDR3      : 1;  
        __IO uint32_t IDR4      : 1;  
        __IO uint32_t IDR5      : 1;  
        __IO uint32_t IDR6      : 1;  
        __IO uint32_t IDR7      : 1;  
        __IO uint32_t IDR8      : 1;  
        __IO uint32_t IDR9      : 1;  
        __IO uint32_t IDR10     : 1;  
        __IO uint32_t IDR11     : 1;  
        __IO uint32_t IDR12     : 1;  
        __IO uint32_t IDR13     : 1;  
        __IO uint32_t IDR14     : 1;  
        __IO uint32_t IDR15     : 1;  
        __IO uint32_t RESERVED  : 16; 
    } BITS;
} GPIO_IDR_t;
typedef union
{
    __IO uint32_t REG;
    struct
    {
        __IO uint32_t ODR0      : 1;  
        __IO uint32_t ODR1      : 1;  
        __IO uint32_t ODR2      : 1;  
        __IO uint32_t ODR3      : 1;  
        __IO uint32_t ODR4      : 1;  
        __IO uint32_t ODR5      : 1;  
        __IO uint32_t ODR6      : 1;  
        __IO uint32_t ODR7      : 1;  
        __IO uint32_t ODR8      : 1;  
        __IO uint32_t ODR9      : 1;  
        __IO uint32_t ODR10     : 1;  
        __IO uint32_t ODR11     : 1;  
        __IO uint32_t ODR12     : 1;  
        __IO uint32_t ODR13     : 1;  
        __IO uint32_t ODR14     : 1;  
        __IO uint32_t ODR15     : 1;  
        __IO uint32_t RESERVED  : 16; 
    } BITS;
} GPIO_ODR_t;
typedef union
{
    __IO uint32_t REG;
    struct
    {
        __IO uint32_t BS0       : 1; 
        __IO uint32_t BS1       : 1; 
        __IO uint32_t BS2       : 1; 
        __IO uint32_t BS3       : 1; 
        __IO uint32_t BS4       : 1; 
        __IO uint32_t BS5       : 1; 
        __IO uint32_t BS6       : 1; 
        __IO uint32_t BS7       : 1; 
        __IO uint32_t BS8       : 1; 
        __IO uint32_t BS9       : 1; 
        __IO uint32_t BS10      : 1; 
        __IO uint32_t BS11      : 1; 
        __IO uint32_t BS12      : 1; 
        __IO uint32_t BS13      : 1; 
        __IO uint32_t BS14      : 1; 
        __IO uint32_t BS15      : 1; 
        __IO uint32_t BR0       : 1; 
        __IO uint32_t BR1       : 1; 
        __IO uint32_t BR2       : 1; 
        __IO uint32_t BR3       : 1; 
        __IO uint32_t BR4       : 1; 
        __IO uint32_t BR5       : 1; 
        __IO uint32_t BR6       : 1; 
        __IO uint32_t BR7       : 1; 
        __IO uint32_t BR8       : 1; 
        __IO uint32_t BR9       : 1; 
        __IO uint32_t BR10      : 1; 
        __IO uint32_t BR11      : 1; 
        __IO uint32_t BR12      : 1; 
        __IO uint32_t BR13      : 1; 
        __IO uint32_t BR14      : 1; 
        __IO uint32_t BR15      : 1; 
    } BITS;
} GPIO_BSRR_t;
typedef union
{
    __IO uint32_t REG;
    struct
    {
        __IO uint32_t BR0       : 1;     
        __IO uint32_t BR1       : 1;     
        __IO uint32_t BR2       : 1;     
        __IO uint32_t BR3       : 1;     
        __IO uint32_t BR4       : 1;     
        __IO uint32_t BR5       : 1;     
        __IO uint32_t BR6       : 1;     
        __IO uint32_t BR7       : 1;     
        __IO uint32_t BR8       : 1;     
        __IO uint32_t BR9       : 1;     
        __IO uint32_t BR10      : 1;     
        __IO uint32_t BR11      : 1;     
        __IO uint32_t BR12      : 1;     
        __IO uint32_t BR13      : 1;     
        __IO uint32_t BR14      : 1;     
        __IO uint32_t BR15      : 1;     
        __IO uint32_t RESERVED  : 16; 
    } BITS;
} GPIO_BRR_t;
typedef union
{
    __IO uint32_t REG;
    struct
    {
    __IO uint32_t LCK0      : 1;  
    __IO uint32_t LCK1      : 1;  
    __IO uint32_t LCK2      : 1;  
    __IO uint32_t LCK3      : 1;  
    __IO uint32_t LCK4      : 1;  
    __IO uint32_t LCK5      : 1;  
    __IO uint32_t LCK6      : 1;  
    __IO uint32_t LCK7      : 1;  
    __IO uint32_t LCK8      : 1;  
    __IO uint32_t LCK9      : 1;  
    __IO uint32_t LCK10     : 1;  
    __IO uint32_t LCK11     : 1;  
    __IO uint32_t LCK12     : 1;  
    __IO uint32_t LCK13     : 1;  
    __IO uint32_t LCK14     : 1;  
    __IO uint32_t LCK15     : 1;  
    __IO uint32_t LCKK      : 1;  
    __IO uint32_t RESERVED  : 15; 
    } BITS;
} GPIO_LCKR_t;

typedef struct
{
    GPIO_CRL_t CRL;   
    GPIO_CRH_t CRH;   
    GPIO_IDR_t IDR;   
    GPIO_ODR_t ODR;   
    GPIO_BSRR_t BSRR; 
    GPIO_BRR_t BRR;   
    GPIO_LCKR_t LCK;  
} GPIO_TypeDef;

// NVIC registers
typedef struct
{
	__IO uint32_t ISER[8];  /*!< Interrupt Set Enable Registers,           Address offset: 0x00-0x1C */
	uint32_t      RESERVED0[24];
	__IO uint32_t ICER[8];  /*!< Interrupt Clear Enable Registers,         Address offset: 0x80-0x9C */
	uint32_t      RESERVED1[24];
	__IO uint32_t ISPR[8];  /*!< Interrupt Set Pending Registers,          Address offset: 0x100-0x11C */
	uint32_t      RESERVED2[24];
	__IO uint32_t ICPR[8];  /*!< Interrupt Clear Pending Registers,        Address offset: 0x180-0x19C */
	uint32_t      RESERVED3[24];
	__IO uint32_t IABR[8];  /*!< Interrupt Active bit Registers,           Address offset: 0x200-0x21C */
	uint32_t      RESERVED4[56];                      
	__IO uint8_t  IPR[240]; /*!< Interrupt Priority Registers,             Address offset: 0x300-0x3EF */
	uint32_t      RESERVED5[644];                        
	__O  uint32_t STIR;     /*!< Software Trigger Interrupt Register,      Address offset: 0xE00 */
} NVIC_TypeDef;

// EXTI registers
typedef union
  {
  __IO uint32_t ALL;
  struct
  {
    __IO uint32_t BIT0  : 1;
    __IO uint32_t BIT1  : 1;
    __IO uint32_t BIT2  : 1;
    __IO uint32_t BIT3  : 1;
    __IO uint32_t BIT4  : 1;
    __IO uint32_t BIT5  : 1;
    __IO uint32_t BIT6  : 1;
    __IO uint32_t BIT7  : 1;
    __IO uint32_t BIT8  : 1;
    __IO uint32_t BIT9  : 1;
    __IO uint32_t BIT10 : 1;
    __IO uint32_t BIT11 : 1;
    __IO uint32_t BIT12 : 1;
    __IO uint32_t BIT13 : 1;
    __IO uint32_t BIT14 : 1;
    __IO uint32_t BIT15 : 1;
    __IO uint32_t BIT16 : 1;
    __IO uint32_t BIT17 : 1;
    __IO uint32_t BIT18 : 1;
    __IO uint32_t BIT19 : 1;
    __IO uint32_t BIT20 : 1;
    __IO uint32_t BIT21 : 1;
    __IO uint32_t BIT22 : 1;
    __IO uint32_t BIT23 : 1;
    __IO uint32_t BIT24 : 1;
    __IO uint32_t BIT25 : 1;
    __IO uint32_t BIT26 : 1;
    __IO uint32_t BIT27 : 1;
    __IO uint32_t BIT28 : 1;
    __IO uint32_t BIT29 : 1;
    __IO uint32_t BIT30 : 1;
    __IO uint32_t BIT31 : 1;
  } BITS;
} __32bit;
typedef struct
{
    __32bit IMR;
    __32bit EMR;
    __32bit RTSR;
    __32bit FTSR;
    __32bit SWIER;
    __32bit PR;
} EXTI_TypeDef;

// TIM registers
typedef struct {
   __IO uint32_t CR1;    
   __IO uint32_t CR2;    
   __IO uint32_t SMCR;   
   __IO uint32_t DIER;   
   __IO uint32_t SR;     
   __IO uint32_t EGR;    
   __IO uint32_t CCMR1;  
   __IO uint32_t CCMR2;  
   __IO uint32_t CCER;   
   __IO uint32_t CNT;    
   __IO uint32_t PSC;    
   __IO uint32_t ARR;    
   __IO uint32_t RCR;    
   __IO uint32_t CCR1;   
   __IO uint32_t CCR2;   
   __IO uint32_t CCR3;   
   __IO uint32_t CCR4;   
   __IO uint32_t BDTR;   
   __IO uint32_t DCR;    
   __IO uint32_t DMAR;   
} TIM_TypeDef;

// ADC registers
typedef struct
{
    __IO uint32_t SR;
    __IO uint32_t CR1;
    __IO uint32_t CR2;
    __IO uint32_t SMPR1;
    __IO uint32_t SMPR2;
    __IO uint32_t JOFR1;
    __IO uint32_t JOFR2;
    __IO uint32_t JOFR3;
    __IO uint32_t JOFR4;
    __IO uint32_t HTR;
    __IO uint32_t LTR;
    __IO uint32_t SQR1;
    __IO uint32_t SQR2;
    __IO uint32_t SQR3;
    __IO uint32_t JSQR;
    __IO uint32_t JDR1;
    __IO uint32_t JDR2;
    __IO uint32_t JDR3;
    __IO uint32_t JDR4;
    __IO uint32_t DR;
} ADC_TypeDef;

// UART registers
typedef struct
{
    __IO uint32_t SR;
    __IO uint32_t DR;
    __IO uint32_t BRR;
    __IO uint32_t CR1;
    __IO uint32_t CR2;
    __IO uint32_t CR3;
    __IO uint32_t GTPR;
} USART_TypeDef;

// SPI registers
typedef struct
{
    __IO uint32_t CR1;
    __IO uint32_t CR2;
    __IO uint32_t SR;
    __IO uint32_t DR;
    __IO uint32_t CRCPR;
    __IO uint32_t RXCRCR;
    __IO uint32_t TXCRCR;
    __IO uint32_t I2SCFGR;
    __IO uint32_t I2SPR;
} SPI_TypeDef;

// I2C registers
typedef struct
{
	__IO uint32_t CR1;
	__IO uint32_t CR2;
	__IO uint32_t OAR1;
	__IO uint32_t OAR2;
	__IO uint32_t DR;
	__IO uint32_t SR1;
	__IO uint32_t SR2;
	__IO uint32_t CCR;
	__IO uint32_t TRISE;
} I2C_TypeDef;

// USB registers
typedef struct
{
	__IO uint32_t EP0R;
	__IO uint32_t EP1R;
	__IO uint32_t EP2R;
	__IO uint32_t EP3R;
	__IO uint32_t EP4R;
	__IO uint32_t EP5R;
	__IO uint32_t EP6R;
	__IO uint32_t EP7R;
	__IO uint32_t RESERVED[3];
	__IO uint32_t CNTR;
	__IO uint32_t ISTR;
	__IO uint32_t FNR;
	__IO uint32_t DADDR;
	__IO uint32_t BTABLE;
} USB_TypeDef;

// ===== Peripheral instance =====
#define GPIOA 		((__IO GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB 		((__IO GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC 		((__IO GPIO_TypeDef *)GPIOC_BASE)
#define RCC 		((__IO RCC_TypeDef *)RCC_BASE)
#define FLASH 		((__IO FLASH_TypeDef *)FLASH_BASE)
#define AFIO 		((__IO AFIO_TypeDef *)AFIO_BASE)
#define NVIC 		((__IO NVIC_TypeDef *)NVIC_Base)
#define EXTI 		((__IO EXTI_TypeDef *)EXTI_Base)
#define TIM1 		((__IO TIM_TypeDef *)TIM1_Base)
#define TIM2 		((__IO TIM_TypeDef *)TIM2_Base)
#define TIM3 		((__IO TIM_TypeDef *)TIM3_Base)
#define TIM4 		((__IO TIM_TypeDef *)TIM4_Base)
#define ADC1 	 	((__IO ADC_TypeDef *)ADC1_Base)
#define ADC2 	 	((__IO ADC_TypeDef *)ADC2_Base)
#define USART1      ((__IO USART_TypeDef *)USART1_Base)
#define USART2      ((__IO USART_TypeDef *)USART2_Base)
#define USART3      ((__IO USART_TypeDef *)USART3_Base)
#define SPI1        ((__IO SPI_TypeDef *)SPI1_Base)
#define SPI2        ((__IO SPI_TypeDef *)SPI2_Base)
#define I2C1		((__IO I2C_TypeDef *)I2C1_Base)
#define I2C2		((__IO I2C_TypeDef *)I2C2_Base)
#define USB			((__IO USB_TypeDef *)USB_Base)

#ifdef __cplusplus
}
#endif

#endif /* __STM32SYSTEM_H */

