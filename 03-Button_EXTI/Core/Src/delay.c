/**
  * @file	delay.c
  * @author	Parham Estiri
  * @brief	Implementation of Timer-based delay functions using TIM6.
  *
  * 		This file provides:
  * 		 - TIM6 initialization (One-pulse mode)
  * 		 - Microsecond-level delay function
  * 		 - Millisecond-level delay function
  *
  * Target	STM32F407VGT6
  */

#include "delay.h"

static uint32_t last_delay_us = 0;			/**< Stores last delay value (µs) to reduce redundant updates	*/

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
void Delay_Init(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;		/**< Enable TIM6 clock								*/

	TIM6->PSC = 84 - 1;						/**< Prescaler: 84Mhz / 84 = 1MHz -> 1µs tick		*/

	TIM6->CR1 = TIM_CR1_OPM;				/**< One-pulse mode: stops timer after each delay	*/
}

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
void Delay_us(uint32_t us)
{
	if (us == 0 || us > 0xFFFF)		/**< Limit maximum delay and ignore delay of 0				*/
		return;

	// Only update ARR and EGR if value changed
	if (us != last_delay_us)		/**< Update ARR only if new delay differs from previous one	*/
	{
		TIM6->ARR = (uint16_t)us;	/**< Set auto-reload value	*/
		TIM6->EGR = TIM_EGR_UG;		/**< Force register update	*/
		last_delay_us = us;
	}

	TIM6->CNT = 0;				/**< Reset counter		*/
	TIM6->SR = 0;				/**< Clear update flag	*/
	TIM6->CR1 |= TIM_CR1_CEN;	/**< Start timer		*/

	while (!(TIM6->SR & TIM_SR_UIF));	/**< Wait until update event (overflow)	*/
	TIM6->SR = 0;				/**< Clear flag again	*/
}

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
void Delay_ms(uint32_t ms)
{
	while (ms--)
	{
		Delay_us(1000);		/**< 1ms delay */
	}
}
