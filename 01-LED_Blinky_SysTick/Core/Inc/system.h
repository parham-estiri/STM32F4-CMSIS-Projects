/**
  * @file	system.h
  * @author	Parham Estiri
  * @brief	System Initialization and Configuration Header File.
  *
  * Target	STM32F407VGT6
  */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "stm32f4xx.h"

/******************************  Function Prototypes  ******************************/

/**
  * @brief	Sets NVIC priority grouping, initializes SWD, configures system clock, and updates SystemCoreClock variable.
  * @param	None
  * @retval	None
  * @note	This function must be called at the beginning of main() before using peripherals.
  */
void System_Init(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SYSTEM_H_ */
