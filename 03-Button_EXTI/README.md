# STM32F4 CMSIS LED Blinky Using SysTick

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

This project demonstrates how to use **external interrupts (EXTI)** on the on the **STM32F407G-DISC1** board to control LEDs. When a user presses the onboard push button (Connected to `PA0`), an EXTI interrupt is triggered, and the corresponding **callback function turns on LEDs** connected to the board. This is a **bare-metal CMSIS project** (no HAL or LL is used).

---
## Features

- **CMSIS-only bare-metal implementation** (no HAL, no LL)
- **168MHz system clock** (configured with HSE + PLL)
- Configures **PA0** as input with external interrupt (rising edge trigger)
- Interrupt handler invokes a **button callback** function, which turns on **onboard LEDs**
- **TIM6-based timing functions** for delays:
  - `Delay_us()`, `Delay_ms()`
- **BSP abstraction** for LEDs and Button:
  - `BSP_LED_Init()`, `BSP_LED_On()`, `BSP_LED_Off()`, `BSP_LED_Toggle()`
  - `BSP_Button_Init()`, `BSP_Button_Read()`
- **Doxygen-documented code** for easy navigation and understanding

---
## Project Structure

```bash
01-LED_Blinky_SysTick/
│── Core/
│   ├── Inc/           # Header files
│   │   ├── delay.h                 # TIM6 interface
│   │   ├── system.h                # System initialization (clock, debug, NVIC)
│   │   └── system_stm32f4xx.h      # CMSIS Cortex-M4 Device System Header File for STM32F4xx devices
│   ├── Src/           # Source files
│   │   ├── delay.c                 # TIM6 implementation
│   │   ├── main.c                  # Application entry point
│   │   ├── system.c                # System configuration and clock setup
│   │   ├── system_stm32f4xx.c      # CMSIS Cortex-M4 Device Peripheral Access Layer System Source File
│   └── Startup/
│       └── startup_stm32f407vgtx.s # Startup assembly file    
├── Drivers/
│   ├── BSP/           # BSP files
│   │   ├── stm32f407g_disc1.c      # BSP implementation
│   │   └── stm32f407g_disc1.h      # BSP interface
│   └── CMSIS          # CMSIS files
├── assets/
│   └── demo.gif
├── Doxyfile                  # Doxygen config
├── LICENSE.txt               # MIT License
├── README.md                 # Project details
├── STM32F407VGTX_FLASH.ld    # Linker script for STM32F407VGTx Device from STM32F4 series
└── STM32F407VGTX_RAM.ld      # Linker script for STM32F407VGTx Device from STM32F4 series
```
---
## How It Works

1. **System_Init()**
   Configures NVIC, enables SWD debug, and sets system clock to **168MHz**.

2. **BSP_LED_Init()**
   Initializes LEDs.

3. **BSP_Button_Init(BUTTON_MODE_EXTI)**
   Initializes the push button with interrupt generation capability.

4. **Delay_Init()**
   Initializes TIM6 for delay. Provides:
     - `Delay_us(us)`: blocking delay in microseconds
     - `Delay_ms(ms)`: blocking delay in milliseconds

5. **__enable_irq()**
   Enables IRQs globally.

6. **Main loop**
   Onboard LEDs turn on and off clockwise. When the push button is pressed, the button callback function is called and all LEDs turn on at once.

---
## Building and Flashing
**Prerequisites**
  - **STM32F407G-DISC1** development board
  - **ARM GCC Toolchain** or **STM32CubeIDE**
  - **ST-Link** programmer/debugger
  - *Doxygen* (optional, for generating docs)

**Getting Started**
1. Clone the repository:
```bash
git clone https://github.com/parham-estiri/STM32F4-CMSIS-Projects.git
```
2. Open the project in **STM32CubeIDE** or you preferred ARM toolchain (Keil, IAR, etc.)
3. Build and flash to your STM32F407G-DISC1 board
4. Observe the LED behavior
---
## Demo
- Here's the LED blinking in action:

- ![LED Blinky Demo](assets/demo.gif)

- **Note**: The wires from ST-Link to PA2 and PA3 are not used in this project.

---
## Doxygen Documentation
- The project is fully documented using **Doxygen**. Follow these steps to generate and view the documentation:
1. **Install Doxygen**
    - Windows: [https://www.doxygen.nl/download.html](https://www.doxygen.nl/download.html)
    - Linux (Ubuntu/Debian):
    ```bash
    sudo apt install doxygen
    ```

2. **Generate Documentation**
    - From the project root directory (where `Doxyfile` is located), run:
    ```bash
    doxygen Doxyfile
    ```
    This will generate HTML files in `docs/html/`.

3. **View Documentation**
    - Open `docs/html/index.html` in a web browser. You can browse:
      - Modules
      - Functions
      - Detailed comments and explanations

---
## License
This project is licensed under the MIT License.
Feel free to use it in your own embedded projects.

---
## Author
**Parham Estiri**
Embedded Systems Developer