/**
  * @file	bsp.h
  * @author	Parham Estiri
  * @brief	Board Support Package (BSP) umbrella header for STM32F407G-DISC1.
  *
  * 		This header file includes all individual BSP peripheral drivers
  * 		and provides a single initialization function to configure them.
  *
  * @details
  * 		- Groups multiple BSP modules into one include.
  * 		- Provides `BSP_Init()` to initialize all supported peripherals at once.
  *
  * @note	This header should be included instead of including each BSP module individually
  * 		when you want to initialize and use the full BSP.
  */

/**
  * @defgroup BSP	Board Support Package
  * @brief	Common hardware abstraction for STM32F407G-DISC1 peripherals.
  * @{
  */

#ifndef BSP_H_
#define BSP_H_

#ifdef __cpluspluc
extern "C" {
#endif

#include "bsp_led.h"
#include "bsp_button.h"

/**
  * @brief	Initialize all BSP peripherals.
  * @param	None
  * @retval	None
  * @note	This function must be called at the beginning of main() before using BSP functions.
  */
void BSP_Init(void);

#ifdef __cplusplus
}
#endif

/** @} */	// end of BSP group

#endif /* BSP_H_ */
