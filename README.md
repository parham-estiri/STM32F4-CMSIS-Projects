# STM32F4 CMSIS Projects

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE.txt)

This repository contains a collection of **STM32F4 microcontroller projects** developed using the **CMSIS (Cortex Microcontroller Software Interface Standard)** framework.
All projects are written in **C**, follow a structured and modular coding style, and are documented with **Doxygen** for easy navigation and maintainability.

---
## Features
- Bare-metal STM32F4 programming using **CMSIS drivers** (no HAL)
- Professional coding style with clear modular separation:
    - **System initialization** (clock, startup, etc.)
    - **Board Support Package (BSP)** for LEDs, buttons, and peripherals
    - **Drivers** and **utilities** (e.g., SysTick-based and timer-based delays)
- Each project includes:
    - **Source** (`Src/`) and **header** (`Inc/`) files
    - **Startup code** for STM32F407VGT6 (STM32F407G-DISC1 Discovery board)
    - **BSP** (`Drivers/BSP`) and **CMSIS** (`Drivers/CMSIS`) files
    - **Doxygen documentation**

---
## Repository Structure
``` bash
STM32F4-CMSIS-Projects/
│── 01-LED_Blinky_SysTick/
│   └── ...             # See the project README.md
│
│── 02-LED_Blinky_TimerDelay/
│   └── ...             # See the project README.md
│
│── 03-Button_EXTI/
│   └── ...             # See the project README.md
│
│── .gitignore
│── LICENSE.txt         # MIT License
└── README.md
```

---
## Building and Flashing
**Prerequisites**
  - **STM32F407G-DISC1** development board
  - **ARM GCC Toolchain** or **STM32CubeIDE**
  - **ST-Link** programmer/debugger
  - **Doxygen** (optional, for generating docs)

**Getting Started**
1. Clone the repository:
```bash
git clone https://github.com/parham-estiri/STM32F4-CMSIS-Projects.git
```
2. Open the desired project in **STM32CubeIDE** or you preferred ARM toolchain (Keil, IAR, etc.)
3. Build and flash to your STM32F407G-DISC1 board

---
## Doxygen Documentation
- All projects are fully documented using **Doxygen**. Follow these steps to generate and view the documentation:
1. **Install Doxygen**
    - Windows: [https://www.doxygen.nl/download.html](https://www.doxygen.nl/download.html)
    - Linux (Ubuntu/Debian):
    ```bash
    sudo apt install doxygen
    ```

2. **Generate Documentation**
    - From the desired project root directory (where `Doxyfile` is located), run:
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
These projects are licensed under the MIT License.
Feel free to use them in your own embedded projects.

---
## Author
**Parham Estiri**
Embedded Systems Developer