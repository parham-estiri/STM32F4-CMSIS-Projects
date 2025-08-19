/**
  * @file	main.c
  * @author	Parham Estiri
  * @brief	LED Blinky application using SysTick.
  *
  * 		This file initializes the system, board support package (BSP),
  * 		and SysTick timer, then enters the main loop toggling the red LED
  * 		every 1 second.
  *
  * @note	Uses CMSIS-only style (no HAL).
  */

#include "system.h"
#include "bsp.h"
#include "systick.h"

/**
  * @brief	Application entry point.
  *
  * 		The main function performs the following steps:
  * 		1. Initializes system clock and core peripherals.
  * 		2. Initializes board support package (LEDs, buttons).
  * 		3. Initializes SysTick for millisecond timing.
  * 		4. Enters an infinite loop where the red LED is toggled every 1000ms.
  *
  * @param	None
  * @retval int		Always returns 0 (though this function never exits).
  */
int main(void)
{
	System_Init();			/**< Initialize system configuration		*/
	BSP_Init();				/**< Initialize board support package		*/
	SysTick_Init();			/**< Initialize SysTick timer for delays	*/

	/**< Main loop */
	while (1)
	{
		BSP_LED_Toggle(LED_RED);	/**< Toggle the red LED		*/
		SysTick_delay_ms(1000);		/**< 1 second delay			*/
	}
}
