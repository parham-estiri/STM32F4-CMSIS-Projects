/**
  * @file	systick.c
  * @author	Parham Estiri
  * @brief	SysTick driver implementation.
  */

#include "systick.h"

/**
  *	@brief	Global tick counter in milliseconds
  */
static volatile uint32_t systick_ms = 0;

/**
  * @brief	Initialize SysTick timer
  * @details	Configures the SysTick timer to generate a 1ms tick interrupt
  * 			based on the system core clock.
  * @param[in] ticks_per_second		Number of SysTick interrupt per second
  * 								Typically, 1000 for 1ms tick
  * @param[in] impl		Implementation style: CMSIS or Custom
  * @retval	None
  * @note	This function must be called at the beginning of main() before using SysTick.
  */
void SysTick_Init(uint32_t ticks_per_second, SysTick_Impl_t impl)
{
	systick_ms = 0;			/**< Reset tick counter */

	switch (impl)
	{
		case SYSTICK_CMSIS:
			/* CMSIS function: automatically sets reload, enables counter & interrupt */
			SysTick_Config(SystemCoreClock / ticks_per_second);
			break;

		case SYSTICK_CUSTOM:
			/* Manual register-level configuration */
			SysTick->LOAD = (uint32_t)((SystemCoreClock / ticks_per_second) - 1UL);	/**< Set reload value */
			SysTick->VAL  = 0UL;							/**< Reset SysTick current value */
			SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk		/**< Use processor clock	*/
						  | SysTick_CTRL_TICKINT_Msk		/**< Enable interrupt		*/
						  | SysTick_CTRL_ENABLE_Msk;		/**< Enable SysTick counter	*/
			break;

		default:
			break;
	}
}

/**
  * @brief	Enable SysTick timer and interrupt
  */
void SysTick_Enable(void)
{
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk		/**< Enable interrupt		*/
				  | SysTick_CTRL_ENABLE_Msk;		/**< Enable SysTick counter	*/
}

/**
  * @brief	Disable SysTick timer and interrupt
  */
void SysTick_Disable(void)
{
	SysTick->CTRL &= ~(SysTick_CTRL_TICKINT_Msk		/**< Disable interrupt		*/
				  | SysTick_CTRL_ENABLE_Msk);		/**< Disable SysTick counter	*/
}

/**
  * @brief	Blocking delay in milliseconds
  * @param[in] ms	Number of milliseconds to delay.
  * @retval	None
  */
void SysTick_delay_ms(uint32_t ms)
{
	uint32_t start = systick_ms;		/**< Record starting tick count			*/
	while ((systick_ms - start) < ms){	/**< Wait until specified time passes	*/
		__WFI();						/**< Sleep until next interrupt			*/
	}
}

/**
  * @brief	Get current tick count in milliseconds
  * @param	None
  * @retval	Tick count since SysTick initialization.
  */
uint32_t SysTick_GetTick(void)
{
	return systick_ms;
}

/**
  * @brief	SysTick interrupt handler
  */
void SysTick_Handler(void)
{
	systick_ms++;		/**< Increment millisecond counter	*/
}
