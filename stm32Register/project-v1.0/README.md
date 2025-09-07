<h1 align="center">STM32F1 Bare-Metal Makefile Project</h1>

<p align="center">
<b>Minimal, register-level STM32F103C8T6 project using Makefile and GCC. No HAL/SPL. Easy to extend, easy to hack.</b>
</p>

---

## 📦 Project Structure

```
├── Core/         # Application entry (main.c)
├── Drivers/      # Peripheral drivers (inc/: headers, src/: sources)
├── Example/      # Usage examples
├── Linker/       # Linker scripts
├── Module/       # Extra modules (ds3231, rgb, ring_buffer, ...)
├── Output/       # Build output (hex, elf, map, ...)
├── Startup/      # Startup code (C/ASM)
├── System/       # System config, peripheral definitions
├── Makefile      # Build system
└── README.md     # This file
```

---

## 🚀 Features

- Register-level drivers for STM32F103C8T6 (Blue Pill)
- No STM32 HAL/SPL dependency
- GPIO, ADC, UART (printf), Timer/PWM, EXTI, RCC, SysTick, AFIO, I2C, SPI
- Modular structure, easy to add new drivers
- Example codes for quick start

---

## ⚡ Quick Start

### 1. Build firmware

```sh
make
```

### 2. Flash to board (ST-Link V2 required)

```sh
make upload
```

Output files (hex, elf, map, ...) are in `Output/`.

---

## 🛠️ Requirements

- ARM GCC toolchain (arm-none-eabi-gcc)
- make (GNU Make)
- ST-Link V2 (for upload)
- Board: STM32F103C8T6 (Blue Pill)

---

## 📝 Example: Blink LED

```c
#include "stm32system.h"
#include "peripherals.h"

int main(void) {
  RCC_Clock(SYSCLK_FREQ_72MHZ);
  SysTick_Init();
  RCC_APB2ClockCmd(RCC_APB2_GPIOC, ENABLE);

  GPIO_InitTypeDef gpio;
  gpio.Pin = GPIO_PIN_13;
  gpio.Mode = GPIO_MODE_OUTPUT_PP;
  gpio.Speed = GPIO_SPEED_50MHZ;
  GPIO_Init(GPIOC, &gpio);

  while(1) {
    GPIOC->ODR.REG ^= (1 << 13);
    delay_ms(1000);
  }
}
```

---

## � Example List

- `Example/blink_led.c`         - Blink LED on PC13
- `Example/ring_buffer.c`       - Ring buffer usage
- `Example/adc.c`               - ADC read example
- `Example/i2c.c`               - I2C communication
- `Example/spi.c`               - SPI communication
- `Example/ds3231.c`            - DS3231 RTC module
- `Example/rgb.c`               - RGB LED control
- `Example/vargs.c`             - UART printf (variadic)

---

## 📄 License

MIT License © 2025 haihbv

- 🔌 GPIO Driver: Điều khiển chân GPIO
- 📊 ADC Driver: Đọc giá trị analog
- 📡 UART: Giao tiếp UART, hỗ trợ printf
- ⏱️ Timer: Định thời, PWM, đếm xung
- 🔔 EXTI: Ngắt ngoài từ GPIO
- ⚙️ RCC: Quản lý clock hệ thống
- ⏰ SysTick: Delay chính xác
- 🔗 AFIO: Cấu hình alternate function
- 🔄 I2C/SPI: Giao tiếp ngoại vi
- 📋 Ring Buffer: Buffer vòng tròn hiệu quả

---

### 🛠️ Yêu cầu hệ thống

- IDE: Keil uVision 5 hoặc Makefile + ARM GCC
- MCU: STM32F103C8T6 (Blue Pill)
- Debugger: ST-Link V2

---

### 📖 Ví dụ sử dụng

- **Ring Buffer:** `example/ring_buffer_example.c`
- **UART Printf:** `example/variadic_usart_example.c`
- **DS3231 RTC:** `example/ds3231_example.c`
- **SPI:** `example/spi_send1byte.c`

---

### 📄 License

MIT License © 2025 STM32F103C8 Register Driver Library
