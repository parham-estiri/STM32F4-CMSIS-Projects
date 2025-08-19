/**
  * @file	bsp.c
  * @author	Parham Estiri
  * @brief	Board Support Package (BSP) source for STM32F407G-DISC1.
  *
  * 		This file implements the top-level initialization for all BSP modules,
  * 		allowing the entire board support system to be initialized with a single call.
  *
  * @details
  * 		- Calls `BSP_LED_Init()` to configure onboard LEDs.
  * 		- Calls `BSP_Button_Init()` to configure the user button.
  *
  * @ingroup BSP
  */

#include "bsp.h"

/**
  * @brief	Initialize all BSP peripherals.
  * @details	This function initializes all board-level peripherals by calling
  * 			each individual BSP module's initialization function.
  */
void BSP_Init(void)
{
	BSP_LED_Init();			/**< Initialize LED driver		*/
	BSP_Button_Init();		/**< Initialize Button driver	*/
}
