/**
  * @file	bsp_button.c
  * @author	Parham Estiri
  * @brief	Board Support Package (BSP) user button driver for STM32F407G-DISC1 board.
  *
  * 		This file provides functions to initialize and read the onboard user button
  * 		using CMSIS register-level access.
  *
  * @details
  * 		- Configures the GPIO pin connected to the user button as input with a pull-down resistor.
  * 		- Reads the button state and returns whether it is pressed or not.
  *
  *	@note	This implementation avoids STM32 HAL and uses direct register access for
  *			maximum performance and minimal overhead.
  *
  *	@ingroup BSP
  *
  * Target	STM32F407G-DISC1 Board
  */

#include "bsp_button.h"

/**
 * @brief	Initialize the user button GPIO.
 * @details
 * 	- Enables the clock for the button's GPIO port.
 * 	- Configures the pin as input mode.
 * 	- Enables the internal pull-down resistor.
 */
void BSP_Button_Init(void)
{
	BUTTON_GPIO_CLK_EN();		/**< Enable clock for the GPIO port containing the button	*/

	BUTTON_GPIO_PORT->MODER &= ~(3UL << (BUTTON_PIN * 2));	/**< Set the pin as input (00 in MODER)	*/

	BUTTON_GPIO_PORT->PUPDR &= ~(3UL << (BUTTON_PIN * 2));
	BUTTON_GPIO_PORT->PUPDR |=  (2UL << (BUTTON_PIN * 2));	/**< Enable pull-down resistor (10 in PUPDR)	*/
}

/**
 * @brief	Read the current state of the user button.
 * @return	'1' if the button is pressed.
 * 			'0' if the button is released.
 */
uint8_t BSP_Button_Read(void)
{
	return ((BUTTON_GPIO_PORT->IDR & (1UL << BUTTON_PIN)) != 0) ? 1 : 0;	/**< Read input data register and return pressed state	*/
}
