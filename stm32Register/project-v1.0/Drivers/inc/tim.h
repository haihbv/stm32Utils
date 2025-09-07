#ifndef TIMER_H
#define TIMER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32system.h"

typedef struct 
{
  uint16_t Prescaler;
  uint16_t AutoReload;  
} TIM_BaseConfig_t;

typedef struct 
{
  uint8_t Channel;      
  uint8_t OCMode;       
  uint16_t Pulse;       
} TIM_OCConfig_t;


#define TIM_CHANNEL_1       1  
#define TIM_CHANNEL_2       2  
#define TIM_CHANNEL_3       3  
#define TIM_CHANNEL_4       4  

#define TIM_CR1_CEN         (1 << 0)  
#define TIM_CR1_UDIS        (1 << 1)    
#define TIM_CR1_URS         (1 << 2)    
#define TIM_CR1_OPM         (1 << 3)    
#define TIM_CR1_DIR         (1 << 4)    
#define TIM_CR1_CMS_0       (1 << 5)    
#define TIM_CR1_CMS_1       (1 << 6)    
#define TIM_CR1_ARPE        (1 << 7)    
#define TIM_CR1_CKD_0       (1 << 8)    
#define TIM_CR1_CKD_1       (1 << 9)    

#define TIM_CR2_CCDS        (1 << 3)  
#define TIM_OCMODE_PWM1     6U  
#define TIM_OCMODE_PWM2     7U

/* Output Compare 1 */
#define TIM_CCMR1_OC1FE     (1 << 2)         
#define TIM_CCMR1_OC1PE     (1 << 3)         
#define TIM_CCMR1_OC1M_MASK (7 << 4)     
#define TIM_CCMR1_OC1M_0    (1 << 4)         
#define TIM_CCMR1_OC1M_1    (1 << 5)         
#define TIM_CCMR1_OC1M_2    (1 << 6)         
#define TIM_CCMR1_OC1CE     (1 << 7)         
/* Output Compare 2 */
#define TIM_CCMR1_OC2FE     (1 << 10)    
#define TIM_CCMR1_OC2PE     (1 << 11)    
#define TIM_CCMR1_OC2M_MASK (7 << 12)    
#define TIM_CCMR1_OC2M_0    (1 << 12)    
#define TIM_CCMR1_OC2M_1    (1 << 13)    
#define TIM_CCMR1_OC2M_2    (1 << 14)    
#define TIM_CCMR1_OC2CE     (1 << 15)    
/* Output Compare 3 */
#define TIM_CCMR2_OC3FE     (1 << 2)     
#define TIM_CCMR2_OC3PE     (1 << 3)     
#define TIM_CCMR2_OC3M_MASK (7 << 4)     
#define TIM_CCMR2_OC3M_0    (1 << 4)     
#define TIM_CCMR2_OC3M_1    (1 << 5)     
#define TIM_CCMR2_OC3M_2    (1 << 6)     
#define TIM_CCMR2_OC3CE     (1 << 7)     
/* Output Compare 4 */
#define TIM_CCMR2_OC4FE     (1 << 10)    
#define TIM_CCMR2_OC4PE     (1 << 11)    
#define TIM_CCMR2_OC4M_MASK (7 << 12)    
#define TIM_CCMR2_OC4M_0    (1 << 12)    
#define TIM_CCMR2_OC4M_1    (1 << 13)    
#define TIM_CCMR2_OC4M_2    (1 << 14)    
#define TIM_CCMR2_OC4CE     (1 << 15)    

/* Channel 1 */
#define TIM_CCER_CC1E       (1 << 0)         
#define TIM_CCER_CC1P       (1 << 1)         
#define TIM_CCER_CC1NE      (1 << 2)         
#define TIM_CCER_CC1NP      (1 << 3)         
/* Channel 2 */
#define TIM_CCER_CC2E       (1 << 4)         
#define TIM_CCER_CC2P       (1 << 5)         
#define TIM_CCER_CC2NE      (1 << 6)         
#define TIM_CCER_CC2NP      (1 << 7)         
/* Channel 3 */
#define TIM_CCER_CC3E       (1 << 8)         
#define TIM_CCER_CC3P       (1 << 9)         
#define TIM_CCER_CC3NE      (1 << 10)        
#define TIM_CCER_CC3NP      (1 << 11)        
/* Channel 4 */
#define TIM_CCER_CC4E       (1 << 12)        
#define TIM_CCER_CC4P       (1 << 13)        
#define TIM_CCER_CC4NP      (1 << 15)        

/* EGR */
#define TIM_EGR_UG          (1 << 0)         
#define TIM_EGR_CC1G        (1 << 1)         
#define TIM_EGR_CC2G        (1 << 2)         
#define TIM_EGR_CC3G        (1 << 3)         
#define TIM_EGR_CC4G        (1 << 4)         
#define TIM_EGR_COMG        (1 << 5)         
#define TIM_EGR_TG          (1 << 6)         
#define TIM_EGR_BG          (1 << 7)        

/* DIER */
#define TIM_DIER_UIE        (1 << 0)         
#define TIM_DIER_CC1IE      (1 << 1)         
#define TIM_DIER_CC2IE      (1 << 2)         
#define TIM_DIER_CC3IE      (1 << 3)         
#define TIM_DIER_CC4IE      (1 << 4)         
#define TIM_DIER_TIE        (1 << 6)         
#define TIM_DIER_UDE        (1 << 8)         

/* SR */
#define TIM_SR_UIF          (1 << 0)         
#define TIM_SR_CC1IF        (1 << 1)         
#define TIM_SR_CC2IF        (1 << 2)         
#define TIM_SR_CC3IF        (1 << 3)         
#define TIM_SR_CC4IF        (1 << 4)         
#define TIM_SR_TIF          (1 << 6)         
#define TIM_SR_CC1OF        (1 << 9)         
#define TIM_SR_CC2OF        (1 << 10)        

/* BDTR */
#define TIM_BDTR_MOE        (1 << 15)        
#define TIM_BDTR_AOE        (1 << 14)        
#define TIM_BDTR_BKE        (1 << 12)        
#define TIM_BDTR_BKP        (1 << 13)        
#define TIM_BDTR_OSSR       (1 << 10)        
#define TIM_BDTR_OSSI       (1 << 11)        
#define TIM_BDTR_LOCK_MASK  (0x3 << 8)       
#define TIM_BDTR_DTG_MASK   (0xFF << 0)      

void TIM_Cmd(volatile TIM_TypeDef *TIMx, uint32_t cmd);
void TIM_BaseInit(volatile TIM_TypeDef *TIMx, TIM_BaseConfig_t config);
void TIM_PWMInit(volatile TIM_TypeDef *TIMx, TIM_OCConfig_t config);
void TIM_SetCompare(volatile TIM_TypeDef *TIMx, uint8_t channel, uint16_t value);
void TIM3_Delay_Init(void);
void delay_us(uint32_t us);
void Servo_Init(void);
void Servo_SetAngle(uint8_t angle);

#ifdef __cplusplus
}
#endif

#endif /* TIMER_H */



