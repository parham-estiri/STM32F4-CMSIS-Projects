/**
  * @file	bsp_led.h
  * @author	Parham Estiri
  * @brief	Board Support Package (BSP) LED driver header file for STM32F407G-DISC1 board.
  *
  * 		This header file declares the LED driver interface and defines the hardware
  * 		configuration macros for controlling the onboard LEDs (Green, Orange, Red, Blue)
  * 		using CMSIS register access.
  *
  * @details
  * 		- LED GPIO port and clock enable macros
  * 		- LED pin number definitions
  * 		- Enumeration for LED identifiers
  * 		- Function prototypes for LED control
  *
  *	@note	This BSP module avoid STM32 HAL and uses direct register access for
  *			maximum performance and minimal overhead.
  *
  *	@ingroup BSP
  *
  * Target	STM32F407G-DISC1 Board
  */

#ifndef BSP_LED_H_
#define BSP_LED_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"

/**
 * @name	LED GPIO Port and Clock Macros
 * @brief	Hardware definitions for LED control.
 * @{
 */
#define LED_GPIO_PORT		GPIOD		/**< GPIO port where all LEDs are connected	*/
#define LED_GPIO_CLK_EN()	(RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN)	/**< Enable GPIO clock	*/
/** @} */

/**
 * @name	LED Pin Numbers
 * @brief	GPIO pin assignments for each LED.
 * @{
 */
#define LED_GREEN_PIN	12
#define LED_ORANGE_PIN	13
#define LED_RED_PIN		14
#define LED_BLUE_PIN	15
/** @} */

/**
 * @enum	BSP_LED_Id_t
 * @brief	LED identifiers for BSP functions.
 */
typedef enum {
	LED_GREEN = 0,
	LED_ORANGE,
	LED_RED,
	LED_BLUE
} BSP_LED_Id_t;

/**
 * @brief	Initialize all LEDs on the board.
 * @details	Configures GPIO port, mode, type, and speed for LED pins.
 * @param	None
 * @retval	None
 */
void BSP_LED_Init();

/**
 * @brief	Turn on a specific LED.
 * @param[in] led	LED index from BSP_LED_Id_t.
 * @retval	None
 */
void BSP_LED_On(BSP_LED_Id_t led);

/**
 * @brief	Turn off a specific LED.
 * @param[in] led	LED index from BSP_LED_Id_t.
 * @retval	None
 */
void BSP_LED_Off(BSP_LED_Id_t led);

/**
 * @brief	Toggle the state of a specific LED.
 * @param[in] led	LED index from BSP_LED_Id_t.
 * @retval	None
 */
void BSP_LED_Toggle(BSP_LED_Id_t led);

#ifdef __cplusplus
}
#endif

#endif /* BSP_LED_H_ */
