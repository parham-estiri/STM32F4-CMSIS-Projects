/**
  * @file	bsp_led.c
  * @author	Parham Estiri
  * @brief	Board Support Package (BSP) LED driver for STM32F407G-DISC1 board.
  *
  * 		This file provides low-level control of the onboard LEDs (Green, Orange, Red, Blue)
  * 		using CMSIS register definitions.
  *
  * @details
  * 		Features implemented:
  * 		 - Initialize all LED GPIO pins (clock enable, mode, type, speed)
  *			 - Turn on a specific LED
  *			 - Turn off a specific LED
  *			 - Toggle a specific LED
  *
  *	@note	This implementation avoids STM32 HAL and uses direct register access for
  *			maximum performance and minimal overhead.
  *
  *	@ingroup BSP
  *
  * Target	STM32F407G-DISC1 Board
  */

#include "bsp_led.h"

/**
 * @brief	Lookup table containing the GPIO pin numbers for each LED.
 */
static const uint16_t led_pin[] = {
		LED_GREEN_PIN,
		LED_ORANGE_PIN,
		LED_RED_PIN,
		LED_BLUE_PIN
};

/*
 * @brief	Number of LEDs available on the board.
 * @details	Automatically calculated from the led_pin[] array.
 */
#define BSP_LED_COUNT	(sizeof(led_pin) / sizeof(led_pin[0]))

/*
 * @brief	Initialize all LEDs on the board.
 * @details	Enables the GPIO clock for the LED port.
 * 			Configures the LED pins as output, push-pull, and low speed.
 * @param	None
 * @retval	None
 */
void BSP_LED_Init(void)
{
	LED_GPIO_CLK_EN();				/**< Enable clock for the GPIO port containing the LEDs		*/

	// Configure each LED pin as general purpose output mode
	// MODER register: 00 = input, 01 = output
	for (int i = 0; i < BSP_LED_COUNT; i++)
	{
		LED_GPIO_PORT->MODER &= ~(3UL << (led_pin[i] * 2));
		LED_GPIO_PORT->MODER |=  (1UL << (led_pin[i] * 2));		/**< Set the pin as output		*/
	}

	LED_GPIO_PORT->OTYPER = 0;		/**< Set output type to push-pull for all pins				*/

	LED_GPIO_PORT->OSPEEDR = 0;		/**< Set all pins to low speed								*/
}

/*
 * @brief	Turn on a specific LED.
 * @param[in] led	Index of the LED to turn on (0 to BSP_LED_COUNT-1).
 * @retval	None
 */
void BSP_LED_On(BSP_LED_Id_t led)
{
	if (led < BSP_LED_COUNT)		/**< Check if LED index is valid	*/
	{
		LED_GPIO_PORT->BSRR |= (1UL << led_pin[led]);	/**< Set the corresponding pin (BSRR: lower half sets bits)	*/
	}
}

/*
 * @brief	Turn off a specific LED.
 * @param[in] led	Index of the LED to turn off (0 to BSP_LED_COUNT-1).
 * @retval	None
 */
void BSP_LED_Off(BSP_LED_Id_t led)
{
	if (led < BSP_LED_COUNT)		/**< Check if LED index is valid	*/
	{
		LED_GPIO_PORT->BSRR |= (1UL << (led_pin[led] + 16));	/**< Reset the corresponding pin (BSRR: upper half resets bits)	*/
	}
}

/*
 * @brief	Toggle the state of a specific LED.
 * @param[in] led	Index of the LED to toggle (0 to BSP_LED_COUNT-1).
 * @retval	None
 */
void BSP_LED_Toggle(BSP_LED_Id_t led)
{
	if (led < BSP_LED_COUNT)		/**< Check if LED index is valid	*/
	{
		LED_GPIO_PORT->ODR ^= (1UL << led_pin[led]);	/**< XOR the output data register bit to toggle LED	*/
	}
}
