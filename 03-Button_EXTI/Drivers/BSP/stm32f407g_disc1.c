/**
  * @file	stm32f407g_disc1.c
  * @author	Parham Estiri
  * @brief	Board Support Package (BSP) implementation for the STM32F407G-DISC1.
  *
  * @details
  * 	This file provides low-level driver implementations for the on-board
  * 	peripherals of the STM32F407G-DISC1 development board, including:
  * 	- LED control (initialization, on/off, toggle)
  * 	- User button handling (GPIO mode, EXTI interrupt mode, debounce logic)
  *
  * 	The BSP abstracts hardware access and simplifies application development
  * 	by providing a clean API for basic board functions.
  *
  * @note
  * 	- LED pins are configured as push-pull, low-speed outputs.
  * 	- The user button can be configured in GPIO or EXTI interrupt mode
  * 	  with software debounce support using TIM7.
  * 	- The BSP_Button_Callback() is declared as a weak function and can be
  * 	  overridden by the user application.
  *
  * @attention
  * 	This module is designed for CMSIS-level bare-metal projects and does NOT
  * 	rely on STM32 HAL drivers.
  */

/** @defgroup STM32F407G_DISC1_BSP STM32F407G-DISC1 BSP
  * @{
  */

#include "stm32f407g_disc1.h"

/** @defgroup STM32F407G_DISC1_BSP_Private_Macros STM32F407G-DISC1 BSP Private macros
  * @{
  */
/** @brief	Debounce interval for the button in milliseconds. */
#define BUTTON_DEBOUNCE_MS		20
/**
  * @}
  */

/** @defgroup STM32F407G_DISC1_BSP_Private_Variables STM32F407G-DISC1 BSP Private variables
  * @{
  */
/** @brief	Lookup table containing the GPIO pin numbers for each LED. */
static const uint16_t LED_PIN[LEDn] = {
		LED_GREEN_PIN,
		LED_ORANGE_PIN,
		LED_RED_PIN,
		LED_BLUE_PIN
};
/**
  * @}
  */

/** @defgroup STM32F407G_DISC1_BSP_Functions STM32F407G-DISC1 BSP Functions
  * @{
  */

/** @defgroup STM32F407G_DISC1_BSP_LED_Functions STM32F407G-DISC1 BSP LED Functions
  * @{
  */

/*
 * @brief	Initialize all LEDs on the board.
 * @details	Enables the GPIO clock for the LED port and configures all LED pins
 * 			as general purpose output push-pull with low speed.
 * @param	None
 * @retval	None
 */
void BSP_LED_Init(void)
{
	LED_GPIO_CLK_EN();				/**< Enable clock for the GPIO port containing the LEDs	*/

	// Configure each LED pin as general purpose output mode
	for (int i = 0; i < LEDn; i++)
	{
		LED_GPIO_PORT->MODER &= ~(3UL << (LED_PIN[i] * 2));		/**< Clear mode bits		*/
		LED_GPIO_PORT->MODER |=  (1UL << (LED_PIN[i] * 2));		/**< Set pin as output		*/
		LED_GPIO_PORT->OTYPER &= ~(1UL << LED_PIN[i]);			/**< Configure as push-pull	*/
		LED_GPIO_PORT->OSPEEDR &= ~(3UL << LED_PIN[i]);			/**< Configure as low speed	*/
	}
}

/*
 * @brief	Turn on a specific LED.
 * @param[in] led	Index of the LED to turn on.
 * @retval	None
 */
void BSP_LED_On(LED_TypeDef led)
{
	if (led < LEDn)		/**< Validate LED index	*/
	{
		LED_GPIO_PORT->BSRR = (1UL << LED_PIN[led]);	/**< Set bit to turn LED on	*/
	}
}

/*
 * @brief	Turn off a specific LED.
 * @param[in] led	Index of the LED to turn off.
 * @retval	None
 */
void BSP_LED_Off(LED_TypeDef led)
{
	if (led < LEDn)		/**< Validate LED index	*/
	{
		LED_GPIO_PORT->BSRR = (1UL << (LED_PIN[led] + 16U));	/**< Reset bit to turn LED off */
	}
}

/*
 * @brief	Toggle the state of a specific LED.
 * @param[in] led	Index of the LED to toggle.
 * @retval	None
 */
void BSP_LED_Toggle(LED_TypeDef led)
{
	if (led < LEDn)		/**< Validate LED index	*/
	{
		LED_GPIO_PORT->ODR ^= (1UL << LED_PIN[led]);	/**< XOR the ODR bit to toggle LED */
	}
}
/**
  * @}
  */

/** @defgroup STM32F407G_DISC1_BSP_BUTTON_Functions STM32F407G-DISC1 BSP BUTTON Functions
  * @{
  */

/** @brief	Initialize button GPIO helper function. */
static inline BSP_Button_GPIO_Init(void);
/** @brief	Initialize button EXTI line. */
void BSP_Button_EXTI_Init(void);
/** @brief	Initialize button NVIC configuration. */
void BSP_Button_NVIC_Init(void);
/** @brief	Initialize button debounce timer (TIM7). */
static void BSP_Button_DebounceTimer_Init(void);

/**
  * @brief	Initialize the user button GPIO and EXTI line.
  * @details
  * 	- Enables the clock for the button's GPIO port.
  * 	- Configures the pin as input mode.
  * 	- Enables the internal pull-down resistor.
  *
  * @param[in] Mode	Specifies button mode.
  * 			- BUTTON_MODE_GPIO: Simple GPIO input
  * 			- BUTTON_MODE_EXTI: External interrupt mode
  * @retval	None
  */
void BSP_Button_Init(ButtonMode_TypeDef Mode)
{
	BUTTON_GPIO_CLK_EN();		/**< Enable clock for the GPIO port containing the button	*/
	BSP_Button_GPIO_Init();		/**< Configure button pin as input with pull-down			*/

	switch (Mode) {
		case BUTTON_MODE_GPIO:
			break;
		case BUTTON_MODE_EXTI:
			BSP_Button_EXTI_Init();					/**< Initialize EXTI							*/
			BSP_Button_NVIC_Init();					/**< Initialize NVIC for the button interrupt	*/
			BSP_Button_DebounceTimer_Init();		/**< Initialize debounce timer					*/
			break;
		default:
			assert(!"Invalid Button Mode!");		/**< Assert on invalid mode	*/
			break;
	}
}

/**
  * @brief	Read the current state of the user button.
  * @retval	1 if pressed, 0 if released
  */
uint8_t BSP_Button_Read(void)
{
	return ((BUTTON_GPIO_PORT->IDR & (1UL << BUTTON_PIN)) != 0) ? 1 : 0;	/**< Return pressed state	*/
}

/**
  * @brief	Configure button GPIO pin.
  * @details	Sets mode to input, enables pull-down resistor, and configures low speed.
  * @param	None
  * @retval	None
  */
static inline BSP_Button_GPIO_Init(void)
{
	BUTTON_GPIO_PORT->MODER &= ~(3UL << (BUTTON_PIN * 2));		/**< Set the pin as input	*/

	BUTTON_GPIO_PORT->PUPDR &= ~(3UL << (BUTTON_PIN * 2));		/**< Clear pull bits		*/
	BUTTON_GPIO_PORT->PUPDR |=  (2UL << (BUTTON_PIN * 2));		/**< Enable pull-down		*/

	BUTTON_GPIO_PORT->OSPEEDR &= ~(3UL << (BUTTON_PIN * 2));	/**< Configure low speed	*/
}

/**
  * @brief	Initialize the user button EXTI.
  * @details	- Enables the SYSCFG clock.
  * 			- Maps the button GPIO pin to the EXTI line.
  * 			- Unmasks the EXTI interrupt and enables rising edge trigger.
  * 			- Clears any pending interrupt flag.
  * @param	None
  * @retval	None
  */
void BSP_Button_EXTI_Init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;			/**< Enable SYSCFG Clock */

	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0;		/**< Clear EXTICR[0] bits	*/
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;	/**< Route PA0 to EXTI0		*/

	EXTI->IMR |= (1 << BUTTON_PIN);					/**< Unmask the interrupt request	*/

	EXTI->RTSR |= (1 << BUTTON_PIN);				/**< Enable rising edge trigger		*/
	EXTI->FTSR &= ~(1 << BUTTON_PIN);				/**< Disable falling edge trigger	*/

	EXTI->PR = (1 << BUTTON_PIN);					/**< Clear pending interrupt flag	*/
}

/**
  * @brief	Initialize NVIC for button EXTI.
  * @details	This function:
  * 			- Retrieves the current NVIC priority grouping.
  * 			- Sets preemptive and subpriority for the button EXTI interrupt.
  * 			- Enables the EXTI interrupt in the NVIC.
  * @param	None
  * @retval	None
  *
  * @note	Preemptive priority is set to 0x0E, subpriority to 0.
  */
void BSP_Button_NVIC_Init(void)
{
	uint32_t PG = NVIC_GetPriorityGrouping();		/**< Get priority grouping	*/
	NVIC_SetPriority(BUTTON_EXTI_IRQn, NVIC_EncodePriority(PG, 0x0E, 0));		/**< Set interrupt priority	*/
	NVIC_EnableIRQ(BUTTON_EXTI_IRQn);				/**< Enable IRQ	*/
}

/**
  * @brief	Initialize TIM7 debounce timer.
  * @details	This function:
  * 				- Configures TIM7 in one-pulse mode with a 1kHz tick to generate
  * 				  a software debounce interval defined by BUTTON_DEBOUNCE_MS.
  * 			The timer update interrupt is enabled, and NVIC priority is set for TIM7.
  * @param	None
  * @retval	None
  *
  * @note	Preemptive priority is set to 0x0F, subpriority to 0.
  */
static void BSP_Button_DebounceTimer_Init(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;				/**< Enable TIM7 clock			*/

	TIM7->PSC = (SystemCoreClock / 1000) - 1;		/**< 1 kHz tick (1 ms)			*/
	TIM7->ARR = BUTTON_DEBOUNCE_MS;					/**< Debounce interval			*/
	TIM7->CR1 |= TIM_CR1_OPM;						/**< One-pulse mode				*/
	TIM7->DIER |= TIM_DIER_UIE;						/**< Enable update interrupt	*/

	uint32_t PG = NVIC_GetPriorityGrouping();		/**< Get priority grouping	*/
	NVIC_SetPriority(TIM7_IRQn, NVIC_EncodePriority(PG, 0x0F, 0));		/**< Set interrupt priority	*/
	NVIC_EnableIRQ(TIM7_IRQn);						/**< Enable IRQ	*/
}

/**
  * @brief	User button callback function.
  * @details	- Weakly defined to allow user override.
  * 			- Toggles the orange LED by default when the button is pressed.
  * @param	None
  * @retval	None
  *
  * @note	Define your own BSP_Button_Callback() in your application to override this behavior.
  */
__attribute__((weak)) void BSP_Button_Callback(void)
{
	BSP_LED_Toggle(LED_ORANGE);			/**< Toggle orange LED by default	*/
}

/**
  * @brief	EXTI0 Interrupt Handler.
  * @details	Clear pending flag, disables EXTI line, starts TIM7 for debounce.
  */
void EXTI0_IRQHandler(void)
{
	if (EXTI->PR & (1 << BUTTON_PIN))		/**< Check if EXTI0 pending	*/
	{
		EXTI->PR = (1 << BUTTON_PIN);		/**< Clear pending flag	*/
		EXTI->IMR &= ~(1 << BUTTON_PIN);	/**< Disable EXTI line	*/
		TIM7->CNT = 0;						/**< Reset counter		*/
		TIM7->CR1 |= TIM_CR1_CEN;			/**< Start TIM7			*/
	}
}

/**
  * @brief	TIM7 Interrupt Handler for debounce.
  * @details	Clear update flag, re-enables EXTI line, calls button callback if pressed.
  */
void TIM7_IRQHandler(void)
{
	if (TIM7->SR & TIM_SR_UIF)				/**< Check update flag		*/
	{
		TIM7->SR &= ~TIM_SR_UIF;			/**< Clear update flag		*/
		EXTI->IMR |= (1 << BUTTON_PIN);		/**< Re-enable EXTI line	*/

		if (BSP_Button_Read()) {			/**< If button still pressed */
			BSP_Button_Callback();			/**< Call button callback	*/
		}
	}
}
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
