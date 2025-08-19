/**
  * @file	systick.c
  * @author	Parham Estiri
  * @brief	Implementation of SysTick timer functions for STM32F4 series.
  *
  * 		This file provides initialization, millisecond delay, and time tracking functions
  * 		using the SysTick timer.
  */

#include "systick.h"

/**
  *	@brief	Millisecond counter incremented by SysTick interrupt.
  *	@details	This variable keeps track of the number of milliseconds since
  *				SysTick_Init() was called.
  */
static volatile uint32_t msTicks = 0;

/**
  * @brief	System core clock frequency.
  * @details	Defined in system_stm32fxx.c. Used to calculate SysTick reload value.
  */
extern uint32_t SystemCoreClock;

/**
  * @brief	SysTick interrupt handler.
  * @details	This function is called automatically every 1ms when SysTick
  * 			interrupt occurs. It increments the millisecond counter.
  * @param	None
  * @retval	None
  */
void SysTick_Handler(void)
{
	msTicks++;		/**< Increment millisecond counter	*/
}

/**
  * @brief	Returns the number of milliseconds since SysTick was initialized.
  * @details	Useful for non-blocking timing or measuring elapsed time.
  * @param	None
  * @retval	Elapsed time in milliseconds.
  */
uint32_t millis(void)
{
	return msTicks;
}

/**
  * @brief	Delays execution for a specified number of milliseconds.
  * @details	This function blocks execution for the specified duration using
  * 			the SysTick timer.
  * @param[in] ms	Number of milliseconds to delay.
  * @retval	None
  */
void SysTick_delay_ms(uint32_t ms)
{
	uint32_t start = msTicks;			/**< Record starting tick count			*/
	while ((msTicks - start) < ms);		/**< Wait until specified time passes	*/
}

/**
  * @brief	Initializes the SysTick timer.
  * @details	Configures the SysTick timer to generate a 1ms tick interrupt
  * 			based on the system core clock.
  * @param	None
  * @retval	None
  */
void SysTick_Init(void)
{
	SysTick->CTRL = 0;			/**< Disable SysTick during configuration	*/

	SysTick->LOAD = (SystemCoreClock / 1000) - 1;	/**< Set reload value for 1ms tick: (SystemCoreClock / 1000) - 1	*/

	SysTick->VAL = 0;			/**< Reset SysTick current value	*/

	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk		/**< Use processor clock	*/
				  | SysTick_CTRL_TICKINT_Msk		/**< Enable interrupt		*/
				  | SysTick_CTRL_ENABLE_Msk;		/**< Enable SysTick counter	*/
}
