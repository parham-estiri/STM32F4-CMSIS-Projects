/**
  * @file	delay.h
  * @author	Parham Estiri
  * @brief	Header file for TIM6-base delay functions.
  *
  * 		This module provides:
  * 		 - Initialization of TIM6 in one-pulse mode
  * 		 - Microsecond-level blocking delay
  * 		 - Millisecond-level blocking delay
  *
  * Target	STM32F407VGT6
  */

#ifndef DELAY_H_
#define DELAY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f407xx.h"

/**
  * @brief	Initialize TIM6 for delay functions.
  *
  *			Configures TIM6 in one-pulse mode with a prescaler to generate
  *			a 1 MHz timer tick (1 µs resolution).
  *
  *	@param	None
  *	@retval	None
  *
  *	@note	This function must be called at main() before using Delay_us() or Delay_ms().
  */
void Delay_Init(void);

/**
  * @brief	Generate a blocking delay in microseconds.
  *
  *			Uses TIM6 in one-pulse mode to wait for the specified duration.
  *
  *	@param[in] us	Delay duration in microseconds (1 to 65535).
  *	@retval	None
  *
  *	@note	- Maximum delay is limited to 16-bit timer range (65535 µs).
  *			- Delay of 0 is ignored.
  *			- Consecutive calls with the same value are optimized by avoiding
  *			  redundant ARR updates.
  */
void Delay_us(uint32_t us);

/**
  * @brief	Generate a blocking delay in milliseconds.
  *
  *			Internally calls delay_us() in a loop to achieve millisecond resolution.
  *
  *	@param[in] ms	Delay duration in milliseconds.
  *	@retval	None
  *
  *	@note	- Maximum delay depends on loop count and system clock.
  */
void Delay_ms(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif /* DELAY_H_ */
