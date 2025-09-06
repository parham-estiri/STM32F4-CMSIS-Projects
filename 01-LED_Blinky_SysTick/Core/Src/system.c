/**
  * @file	system.c
  * @author	Parham Estiri
  * @brief	System Initialization and Configuration.
  *
  * 		This file contains:
  * 		 - NVIC priority grouping macros
  *			 - Serial Wire Debug (SWD) interface configuration
  * 		 - System Clock configurations
  *
  * Target	STM32F407VGT6
  */

#include "system.h"

/************************  NVIC Priority Group Definitions  ************************/
#define NVIC_PRIORITYGROUP_0	0x7UL	/**< 0 bits for pre-emption priority, 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1	0x6UL	/**< 1 bits for pre-emption priority, 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2	0x5UL	/**< 2 bits for pre-emption priority, 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3	0x4UL	/**< 3 bits for pre-emption priority, 1 bits for subpriority */
#define NVIC_PRIORITYGROUP_4	0x3UL	/**< 4 bits for pre-emption priority, 0 bits for subpriority */

/**************************  PLL Configuration Constants  **************************/
#define PLL_M		4UL				/**< PLL division factor for main PLL input clock	*/
#define PLL_N		168UL			/**< PLL multiplication factor for VCO				*/
#define PLL_P		2UL				/**< PLL division factor for main system clock		*/
#define PLL_Q		7UL				/**< PLL division factor for USB clock				*/

/**************************  Static Function Prototypes  ***************************/
static void System_SWD_Init(void);
static void System_Clock_Config(void);

/**
  * @brief	Sets NVIC priority grouping, initializes SWD, configures system clock, and updates SystemCoreClock variable.
  * @param	None
  * @retval	None
  * @note	This function must be called at the beginning of main() before using peripherals.
  */
void System_Init(void)
{
	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);	/**< NVIC: 4 preemptive, 0 sub-priority bits  */
	System_SWD_Init();								/**< Enable Serial Wire Debug				  */
	System_Clock_Config();							/**< Clock configuration					  */
	SystemCoreClockUpdate();						/**< Update SystemCoreClock variable		  */
}

/**
  * @brief	Initializes Serial Wire Debug (SWD) Interface on PA13 and PA14.
  * @param	None
  * @retval	None
  */
static void System_SWD_Init(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;			/**< Enable GPIOA clock								*/

	DBGMCU->CR |= DBGMCU_CR_DBG_SLEEP				/**< Enable debugging in sleep mode					*/
			   |  DBGMCU_CR_DBG_STOP				/**< Enable debugging in stop mode					*/
			   |  DBGMCU_CR_DBG_STANDBY;			/**< Enable debugging in standby mode				*/

	GPIOA->MODER &= ~(GPIO_MODER_MODER13 | GPIO_MODER_MODER14);
	GPIOA->MODER |= (GPIO_MODER_MODER13_1 | GPIO_MODER_MODER14_1);	/**< Set PA13 and PA14 to AF mode	*/

	GPIOA->AFR[1] &= ~((0xFU << (4 * 5)) | (0xFU << (4 * 6)));
	GPIOA->AFR[1] |= ((0x0U << (4 * 5)) | (0x0U << (4 * 6)));		/**< Set AF0 for PA13 and PA14		*/

	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13		/**< Set PA13 to very high speed					*/
				   |  GPIO_OSPEEDER_OSPEEDR14;		/**< Set PA14 to very high speed					*/

	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR13 | GPIO_PUPDR_PUPDR14);		/**< Set pins on no pull-up/down	*/
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR13_0;			/**< Enable pull-up on PA13 for stability			*/
}

/**
  * @brief	Configures the System Clock to 168 MHz using HSE and PLLCLK.
  * @param	None
  * @retval	None
  */
static void System_Clock_Config(void)
{
	RCC->CR |= RCC_CR_HSEON;				/**< Enable HSE clock							*/
	while(!(RCC->CR & RCC_CR_HSERDY));		/**< Wait until HSE is ready					*/

	RCC->APB1ENR |= RCC_APB1ENR_PWREN;		/**< Enable power interface clock				*/

	PWR->CR |= PWR_CR_VOS;					/**< Set voltage regulator to default value		*/

	FLASH->ACR |= FLASH_ACR_ICEN			/**< Enable instruction cache					*/
			   |  FLASH_ACR_PRFTEN			/**< Enable FLASH prefetch buffer				*/
			   |  FLASH_ACR_DCEN			/**< Enable data cache							*/
			   |  FLASH_ACR_LATENCY_5WS;	/**< Set latency on 5 wait states for 168 MHz	*/

	RCC->CFGR |= RCC_CFGR_HPRE_DIV1			/**< AHB  prescaler => /1						*/
			  |  RCC_CFGR_PPRE1_DIV4		/**< APB1 prescaler => /4						*/
	          |  RCC_CFGR_PPRE2_DIV2;		/**< APB2 prescaler => /2						*/

	RCC->PLLCFGR = 0UL;						/**< Clear PLL configuration					*/
	RCC->PLLCFGR |= (PLL_M & 0x3FU)						/**< PLLM = 4						*/
				 |	((PLL_N & 0x1FFU) << 6)				/**< PLLN = 168						*/
				 |	(((PLL_P / 2 - 1) & 0x3U) << 16)	/**< PLLP = 2						*/
				 |	((PLL_Q & 0xFU) << 24)				/**< PLLQ = 7						*/
				 |	RCC_PLLCFGR_PLLSRC_HSE;		/**< Set HSE as PLL clock source			*/

	RCC->CR |= RCC_CR_PLLON;				/**< Enable PLL									*/
	while(!(RCC->CR & RCC_CR_PLLRDY));		/**< Wait until PLL is stable					*/

	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;			/**< Select PLL as system clock source			*/
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);		/**< Wait until PLL is set	*/

	RCC->CR |= RCC_CR_CSSON;				/**< Enable clock security system (CSS)			*/
}
