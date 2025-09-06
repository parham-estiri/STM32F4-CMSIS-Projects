/**
  * @file	stm32f407g_disc1.h
  * @author	Parham Estiri
  * @brief	Board Support Package (BSP) header for the STM32F407G-DISC1.
  *
  * @details
  * 	This header file provides public type definitions, macros, constants,
  * 	and function prototypes for controlling on-board peripherals of the
  * 	STM32F407G-DISC1 development board:
  * 	- LEDs (GPIO configuration, control functions)
  * 	- User button (GPIO and EXTI configuration, state read)
  *
  * 	Applications should include this header to access BSP functions
  * 	implemented in stm32f407g_disc1.c.
  *
  * @note
  * 	- Designed for CMSIS-level bare-metal development without HAL drivers.
  * 	- Compatible with both C and C++ projects.
  */

/** @addtogroup STM32F407G_DISC1_BSP STM32F407G-DISC1 BSP
  * @{
  */

#ifndef STM32F407G_DISC1_H_
#define STM32F407G_DISC1_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "stm32f407xx.h"
#include "assert.h"

/** @defgroup STM32F407G_DISC1_BSP_Exported_Types STM32F407G-DISC1 BSP Exported types
  * @{
  */

/**
  * @brief LED identifiers for STM32F407G-DISC1.
  */
typedef enum {
	LED_GREEN	= 0,	/**< Green LED	*/
	LED_ORANGE	= 1,	/**< Orange LED	*/
	LED_RED		= 2,	/**< Red LED	*/
	LED_BLUE	= 3		/**< Blue LED	*/
} LED_TypeDef;

/**
  * @brief Button operating modes.
  */
typedef enum {
	BUTTON_MODE_GPIO = 0,	/**< Button used as simple GPIO input	*/
	BUTTON_MODE_EXTI = 1	/**< Button used with EXTI interrupt	*/
} ButtonMode_TypeDef;
/**
  * @}
  */

/** @defgroup STM32F407G_DISC1_BSP_Exported_Constants STM32F407G-DISC1 BSP Exported constants
  * @{
  */

/** @defgroup STM32F407G_DISC1_BSP_LED_Exported_Constants STM32F407G-DISC1 BSP LED exported constants
  * @{
  */
#define LEDn					4		/**< Total number of LEDs on board	*/

#define LED_GPIO_PORT			GPIOD	/**< Port connected to LEDs		*/
#define LED_GPIO_CLK_EN()		(RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN)	/**< Enable port clock	*/

#define LED_GREEN_PIN			12		/**< Pin number for Green LED	*/
#define LED_ORANGE_PIN			13		/**< Pin number for Orange LED	*/
#define LED_RED_PIN				14		/**< Pin number for Red LED		*/
#define LED_BLUE_PIN			15		/**< Pin number for Blue LED	*/
/**
  * @}
  */

/** @defgroup STM32F407G_DISC1_BSP_Button_Exported_Constants STM32F407G-DISC1 BSP Button exported constants
  * @{
  */
#define BUTTONn					1		/**< Total number of user buttons	*/

#define BUTTON_GPIO_PORT		GPIOA	/**< Port connected to user button	*/
#define BUTTON_GPIO_CLK_EN()	(RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN)	/**< Enable port clock	*/

#define BUTTON_PIN				0		/**< Pin number for user button		*/

#define BUTTON_EXTI_IRQn		EXTI0_IRQn	/**< External interrupt line for user button	*/
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup STM32F407G_DISC1_BSP_Exported_Functions STM32F407G-DISC1 BSP exported functions
  * @{
  */
/**
  * @brief Initialize all LEDs.
  */
void BSP_LED_Init(void);

/**
  * @brief	Turn on a specific LED.
  * @param[in] led	Index of the LED to turn on.
  * @retval	None
  */
void BSP_LED_On(LED_TypeDef led);

/**
  * @brief	Turn off a specific LED.
  * @param[in] led	Index of the LED to turn off.
  * @retval	None
  */
void BSP_LED_Off(LED_TypeDef led);

/**
  * @brief	Toggle the state of a specific LED.
  * @param[in] led	Index of the LED to toggle.
  * @retval	None
  */
void BSP_LED_Toggle(LED_TypeDef led);

/**
  * @brief	Initialize the user button.
  * @param[in] Mode	Button mode (GPIO or EXTI).
  * @retval	None
  */
void BSP_Button_Init(ButtonMode_TypeDef Mode);

/**
  * @brief	Read the current state of the user button.
  * @retval	1 if pressed, 0 if released
  */
uint8_t BSP_Button_Read(void);
/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F407G_DISC1_H_ */
