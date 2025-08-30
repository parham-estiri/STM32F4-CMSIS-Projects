/**
  * @file	main.c
  * @author	Parham Estiri
  * @brief	Interrupt-driven push button.
  *
  * 		This file initializes the system, board support package (BSP) LEDs,
  * 		BSP user button in interrupt mode, and TIM6 peripheral, then enters
  * 		into the infinite loop, waiting for the EXTI0 interrupt to occur to
  * 		call the `BSP_Button_Callback()` function.
  *
  * @note	Uses CMSIS-only style (no HAL).
  */

#include "system.h"
#include "stm32f407g_disc1.h"
#include "delay.h"

/**
  * @brief	Application entry point.
  *
  * 		The main function performs the following steps:
  * 		1. Initializes system clock and core peripherals.
  * 		2. Initializes board support package (LEDs, button, EXTI0 for the button).
  * 		4. Enters an infinite loop (LEDs turn on and off clockwise). Whenever the
  * 		   button is pressed, all LEDs turn on at once.
  *
  * @param	None
  * @retval int		Always returns 0 (though this function never exits).
  */
int main(void)
{
	System_Init();			/**< Initialize system configuration		*/
	BSP_LED_Init();			/**< Initialize all LEDs on the board		*/
	BSP_Button_Init(BUTTON_MODE_EXTI);		/**< Initialize the button with interrupt generation capability	*/
	Delay_Init();			/**< Initialize TIM6 for delay				*/

	__enable_irq();			/**< Enable IRQs globally					*/

	/**< Main loop */
	while (1)
	{
		for (int i = 0; i < 4; i++) {
			BSP_LED_On(i);
			Delay_ms(500);
			BSP_LED_Off(i);
		}
	}
}

void BSP_Button_Callback(void)
{
	BSP_LED_On(LED_GREEN);
	BSP_LED_On(LED_ORANGE);
	BSP_LED_On(LED_RED);
	BSP_LED_On(LED_BLUE);
}
