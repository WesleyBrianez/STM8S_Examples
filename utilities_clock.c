/**
  ********************************************************************************
  * @file		utilities_clock.c
  * @author		Itech team
  * @version 	V1.0
  * @date    	17-Jan-2017
  * @brief   	This file contains a brief routine for for STM8S-discovery
				clock configuration which has an HSE = 16MHz.
				This code also facilitate another versions of configs and
				clocks attribute
  *******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "utilities_clock.h"

/**
  * @brief HSE Clock Configuration 
  * @param None
  * @retval None
  */
void CLK_Config(void){
	CLK_DeInit();	//Deinitializes the CLK peripheral registers to their default reset  values.
	CLK_HSECmd(ENABLE); //Enable the External High Speed oscillator (HSE).
	CLK_ClockSwitchConfig(CLK_SWITCHMODE_MANUAL, CLK_SOURCE_HSE, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE); //Change to use External Source Clock
	CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1); //Configures CPU clock dividers.
}