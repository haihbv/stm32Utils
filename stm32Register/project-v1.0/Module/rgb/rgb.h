#ifndef RGB_H
#define RGB_H

#include <stdint.h>

void GPIO_Config(void);
void LED_RGB_Set(uint8_t red, uint8_t green, uint8_t blue);
void LED_RGB_SetCommand(void);

#endif // RGB_H
