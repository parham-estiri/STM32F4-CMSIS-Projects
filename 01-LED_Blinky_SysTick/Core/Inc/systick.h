/**
  * @file	systick.h
  * @author	Parham Estiri
  * @brief	SysTick driver interface.
  *
  *			Provides APIs for:
  *				- SysTick initialization (CMSIS or Custom)
  *				- Delay in milliseconds
  *				- Tick counter using SysTick interrupt
  */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#ifdef __cpluspluc
extern "C" {
#endif /* __cplusplus */

#include "stm32f4xx.h"

/**
  * @brief	Enumeration for SysTick implementation method
  */
typedef enum {
	SYSTICK_CMSIS	= 0,	/**< Use CMSIS SysTick_Config() */
	SYSTICK_CUSTOM	= 1		/**< Use manual configuration	*/
} SysTick_Impl_t;

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
void SysTick_Init(uint32_t ticks_per_second, SysTick_Impl_t impl);

/**
  * @brief	Enable SysTick timer and interrupt
  */
void SysTick_Enable(void);

/**
  * @brief	Disable SysTick timer and interrupt
  */
void SysTick_Disable(void);

/**
  * @brief	Blocking delay in milliseconds
  * @param[in] ms	Number of milliseconds to delay.
  * @retval	None
  */
void SysTick_Delay_ms(uint32_t ms);

/**
  * @brief	Get current tick count in milliseconds
  * @param	None
  * @retval	Tick count since SysTick initialization.
  */
uint32_t SysTick_GetTick(void);

/**
  * @brief	SysTick interrupt handler
  */
void SysTick_Handler(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SYSTICK_H_ */
