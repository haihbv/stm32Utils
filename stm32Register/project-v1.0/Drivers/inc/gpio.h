#ifndef GPIO_H
#define GPIO_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32system.h"

typedef enum
{
    GPIO_MODE_INPUT = 0x00, 
    GPIO_MODE_OUTPUT_PP,    
    GPIO_MODE_OUTPUT_OD,    
    GPIO_MODE_AF_PP,        
    GPIO_MODE_AF_OD,        
    GPIO_MODE_ANALOG,       
    GPIO_MODE_INPUT_PU,     
    GPIO_MODE_INPUT_PD      
} GPIO_Mode_t;

typedef enum
{
    GPIO_SPEED_NONE = 0x00,  
    GPIO_SPEED_10MHZ = 0x01, 
    GPIO_SPEED_2MHZ = 0x02,  
    GPIO_SPEED_50MHZ = 0x03  
} GPIO_Speed_t;


typedef struct
{
    uint16_t Pin;       
                        
    GPIO_Mode_t Mode;   
                        
    GPIO_Speed_t Speed; 
                        
} GPIO_InitTypeDef;

void GPIO_Init(__IO GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct);
void GPIO_WritePin(__IO GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState state);
void GPIO_TogglePin(__IO GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint8_t GPIO_ReadPin(__IO GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#ifdef __cplusplus
}
#endif

#endif /* GPIO_H */

