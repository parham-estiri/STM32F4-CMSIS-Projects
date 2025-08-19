/**
  * @file	bsp_button.h
  * @author	Parham Estiri
  * @brief	Board Support Package (BSP) user button header file for STM32F407G-DISC1 board.
  *
  * 		This header defines the hardware configuration and function prototypes for
  * 		initializing and reading the onboard user button using CMSIS register-level access.
  *
  * @details
  * 		- Defines GPIO port, pin number, and clock enable macro for the button.
  * 		- Provides a function to initialize the button (input mode with pull-down).
  * 		- Provides a function to read the button state.
  *
  *	@note	This BSP module avoid STM32 HAL and uses direct register access for
  *			maximum performance and minimal overhead.
  *
  *	@ingroup BSP
  *
  * Target	STM32F407G-DISC1 Board
  */

#ifndef BSP_BUTTON_H_
#define BSP_BUTTON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"

/**
 * @name	Button GPIO Port and Clock Macros
 * @brief	Hardware definitions for the onboard user button.
 * @{
 */
#define BUTTON_GPIO_PORT		GPIOA
#define BUTTON_GPIO_CLK_EN()	(RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN)
#define BUTTON_PIN				0
/** @} */

/**
 * @brief	Initialize the user button GPIO.
 * @details	Configures the button pin as input mode with pull-down resistor.
 * @param	None
 * @retval	None
 */
void BSP_Button_Init(void);

/**
 * @brief	Read the current state of the user button.
 * @return	'1' if the button is pressed.
 * 			'0' if the button is released.
 */
uint8_t BSP_Button_Read(void);

#ifdef __cplusplus
}
#endif

#endif /* BSP_BUTTON_H_ */
