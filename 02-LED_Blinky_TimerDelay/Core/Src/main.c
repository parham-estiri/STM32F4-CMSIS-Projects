/**
  * @file	main.c
  * @author	Parham Estiri
  * @brief	LED Blinky application using TIM6.
  *
  * 		This file initializes the system, board support package (BSP),
  * 		and TIM6 peripheral, then enters the main loop toggling the
  * 		blue LED every 1 second.
  *
  * @note	Uses CMSIS-only style (no HAL).
  */

#include "system.h"
#include "bsp.h"
#include "delay.h"

/**
  * @brief	Application entry point.
  *
  * 		The main function performs the following steps:
  * 		1. Initializes system clock and core peripherals.
  * 		2. Initializes board support package (LEDs, buttons).
  * 		3. Initializes TIM6 for millisecond timing.
  * 		4. Enters an infinite loop where the blue LED is toggled every 1000ms.
  *
  * @param	None
  * @retval int		Always returns 0 (though this function never exits).
  */
int main(void)
{
	System_Init();			/**< Initialize system configuration		*/
	BSP_Init();				/**< Initialize board support package		*/
	Delay_Init();			/**< Initialize TIM6 for delays				*/

	/**< Main loop */
	while (1)
	{
		BSP_LED_Toggle(LED_BLUE);	/**< Toggle the blue LED	*/
		Delay_ms(1000);				/**< 1 second delay			*/
	}
}
