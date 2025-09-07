#ifndef __ADC_H
#define __ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32system.h"

void ADC1_CHO_Init(void);
uint16_t ADC1_CHO_Read(void);

#ifdef __cplusplus
}
#endif

#endif // __ADC_H
