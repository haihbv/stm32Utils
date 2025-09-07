#ifndef __STM32UTIL_H
#define __STM32UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// ========== Volatile keywords ==========
#define __I  volatile const
#define __O  volatile
#define __IO volatile

// ========== Bit Manipulation ==========
#define SET_BIT(REG, BIT)        ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)      ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)       ((REG) & (BIT))

// ========== General Types ==========
typedef enum { BIT_RESET = 0, BIT_SET = !BIT_RESET} GPIO_PinState;
typedef enum { DISABLE = 0, ENABLE = !DISABLE } FunctionalState;
typedef enum { RESET = 0, SET = !RESET } FlagStatus;
typedef enum { FALSE = 0, TRUE = !FALSE } Bool;
typedef enum { ERROR = 0, SUCCESS = !ERROR } ErrorStatus;


// ========== GPIO Pin Definitions ==========
#define GPIO_PIN_0     	    (0x0001U)
#define GPIO_PIN_1     	    (0x0002U)
#define GPIO_PIN_2     	    (0x0004U)
#define GPIO_PIN_3     	    (0x0008U)
#define GPIO_PIN_4     	    (0x0010U)
#define GPIO_PIN_5     	    (0x0020U)
#define GPIO_PIN_6     	    (0x0040U)
#define GPIO_PIN_7     	    (0x0080U)
#define GPIO_PIN_8     	    (0x0100U)
#define GPIO_PIN_9     	    (0x0200U)
#define GPIO_PIN_10    	    (0x0400U)
#define GPIO_PIN_11    	    (0x0800U)
#define GPIO_PIN_12    	    (0x1000U)
#define GPIO_PIN_13    	    (0x2000U)
#define GPIO_PIN_14    	    (0x4000U)
#define GPIO_PIN_15    	    (0x8000U)
#define GPIO_PIN_ALL   	    (0xFFFFU)


#ifdef __cplusplus
}
#endif

#endif /* __STM32UTIL_H */
