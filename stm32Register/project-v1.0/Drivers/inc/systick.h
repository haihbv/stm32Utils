#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32system.h"

#define SYSTICK_CTRL        (*((volatile uint32_t *)0xE000E010)) 
#define SYSTICK_LOAD        (*((volatile uint32_t *)0xE000E014)) 
#define SYSTICK_VAL         (*((volatile uint32_t *)0xE000E018))  

void SysTick_Handler(void);
void SysTick_Init(void);
uint32_t millis(void);
void delay_ms(uint32_t ms);

#endif
