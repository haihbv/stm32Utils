#include "rgb.h"
#include "gpio.h"

// ...existing code...
#define LED_RED_PIN     GPIO_PIN_12
#define LED_GREEN_PIN   GPIO_PIN_13
#define LED_BLUE_PIN    GPIO_PIN_14
#define LED_PORT        GPIOB

static uint8_t rgb_state = 0;

void GPIO_Config(void)
{
    GPIO_InitTypeDef gpio;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Pin = LED_RED_PIN | LED_GREEN_PIN | LED_BLUE_PIN;
    gpio.Speed = GPIO_SPEED_50MHZ;
    GPIO_Init(LED_PORT, &gpio);
    LED_RGB_Set(0, 0, 0);
}

void LED_RGB_Set(uint8_t red, uint8_t green, uint8_t blue)
{
    GPIO_WritePin(LED_PORT, LED_RED_PIN, red ? BIT_SET : BIT_RESET);
    GPIO_WritePin(LED_PORT, LED_GREEN_PIN, green ? BIT_SET : BIT_RESET);
    GPIO_WritePin(LED_PORT, LED_BLUE_PIN, blue ? BIT_SET : BIT_RESET);
}

void LED_RGB_SetCommand(void)
{
    rgb_state++;
    if (rgb_state > 7)
    {
        rgb_state = 0;
    }
    switch (rgb_state)
    {
    case 1: // Red
        LED_RGB_Set(1, 0, 0);
        break;
    case 2: // Green
        LED_RGB_Set(0, 1, 0);
        break;
    case 3: // Blue
        LED_RGB_Set(0, 0, 1);
        break;
    case 4: // Yellow (Red + Green)
        LED_RGB_Set(1, 1, 0);
        break;
    case 5: // Magenta (Red + Blue)
        LED_RGB_Set(1, 0, 1);
        break;
    case 6: // Cyan (Green + Blue)
        LED_RGB_Set(0, 1, 1);
        break;
    case 7: // White (Red + Green + Blue)
        LED_RGB_Set(1, 1, 1);
        break;
    default: // All off
        LED_RGB_Set(0, 0, 0);
        break;
    }
}
