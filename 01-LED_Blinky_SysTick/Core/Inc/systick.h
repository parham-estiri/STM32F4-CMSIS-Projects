/**
  * @file	systick.h
  * @author	Parham Estiri
  * @brief	Header file for SysTick timer functions for STM32F4 series.
  *
  * 		This file provides initialization and delay utilities using
  * 		the SysTick timer on STM32F4 microcontrollers.
  */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#ifdef __cpluspluc
extern "C" {
#endif

#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include <stdint.h>

/**
  * @brief	Initialize the SysTick timer.
  * @details	Configures the SysTick timer to generate a 1ms tick interrupt
  * 			based on the system core clock.
  * @param	None
  * @retval	None
  * @note	This function must be called at the beginning of main() before using SysTick.
  */
void SysTick_Init(void);

/**
  * @brief	Delays execution for a specified number of milliseconds.
  * @details	Blocks execution for the specified duration using the SysTick timer.
  *				The CPU executes the __WFI() instruction inside the wait loop,
  *				entering sleep mode between ticks to reduce power consumption.
  * @param[in] ms	Number of milliseconds to delay.
  * @retval	None
  */
void SysTick_delay_ms(uint32_t ms);

/**
  * @brief	Return the number of milliseconds since SysTick was initialized.
  * @details	Useful for non-blocking timing or measuring elapsed time.
  * @param	None
  * @retval	Elapsed time in milliseconds.
  */
uint32_t millis(void);

#ifdef __cplusplus
}
#endif

#endif /* SYSTICK_H_ */
