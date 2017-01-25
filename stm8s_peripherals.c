/**
  ********************************************************************************
  * @file    stm8s_peripherals.c
  * @author  Wesley - Itech team
  * @version V1.0
  * @date    24-Jan-2017
  * @brief   This file contains principals functions for STM8S peripherals control
  ********************************************************************************
  *
  * @attention	This code have been develop with a STM8S-Discovery
  *				evaluation board which has a STM8S105C6T6 target MCU
  *
  ********************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stm8s_peripherals.h"

/**
  * @brief	STM8S105 Clock Configuration for use the HSE (16 MHz)
  * @param	None
  * @retval	None
  */
void CLK_Config(void){
	CLK_DeInit();
	CLK_HSECmd(ENABLE);
	CLK_ClockSwitchConfig(CLK_SWITCHMODE_MANUAL, CLK_SOURCE_HSE, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
	CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
}

/**
  * @brief	Timer2 Configuration for base_timer of 1 ms
  *			fOsc = fCPU:	16MHz
  *			Prescaler:		64
  *			fTimer:			250kHz -> T: 4us
  *			Base_Timer: 	T * 250 -> 1ms
  * @param	None
  * @retval	None
  */
void TIM2_Config(void){
	TIM2_DeInit();
	TIM2_TimeBaseInit(TIM2_PRESCALER_64, 250);
	TIM2_ITConfig(TIM2_IT_UPDATE, ENABLE);
	TIM2_Cmd(ENABLE);
}

/**
  * @brief	GPIO Configuration for 3 output led's
  * @param	None
  * @retval	None
  */
void GPIO_Config(void){
	GPIO_Init(LED_RX, GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_Init(LED_TX, GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_Init(LED_EVAL, GPIO_MODE_OUT_PP_LOW_FAST);
	TurnOff(LED_RX);
	TurnOff(LED_TX);
	TurnOff(LED_EVAL);
}

/**
  * @brief	UART2 configuration for 115200,8N1 
  * @param	None
  * @retval	None
  */
void UART2_Config(void){
	UART2_DeInit();
	UART2_Init(115200, UART2_WORDLENGTH_8D, UART2_STOPBITS_1, UART2_PARITY_NO, UART2_SYNCMODE_CLOCK_DISABLE,  UART2_MODE_TXRX_ENABLE);
	UART2_ITConfig(UART2_IT_RXNE_OR, ENABLE);
}

/**
  * @brief	Delayed function for general purpose 
  * @param	unsigned 16 [0 - 65535]
  * @retval	None
  */
void Delay_ms(uint16_t time){
	Miliseconds_Reference = 0;
	while(Miliseconds_Reference <= (time - 1));
}

/**
  * @brief	String Compare
  * @param	Pointer to first string
  * @param	Pointer to second string
  * @retval	boolean value: 1 = TRUE, 0 = FALSE
  */
bool String_Compare(char *FirstString, char *SecondString){
	uint8_t Index;
	
  for(Index = 0; (FirstString[Index] || SecondString[Index]) != '\0'; Index++){
      if (Byte_Compare(FirstString[Index], SecondString[Index]) != TRUE)
        return FALSE;
  }
  
  return TRUE;
}

/**
  * @brief	Byte Compare
  * @param	First char
  * @param	Second char
  * @retval	boolean value: 1 = TRUE, 0 = FALSE
  */
bool Byte_Compare(char x, char y){
  if(x == y)
    return TRUE;
  else
    return FALSE;
}

/**
  * @brief	Send String to UART2
  * @param	Pointer to string index address
  * @retval	None
  */
void Send_String(char *string){
	uint8_t index;

	for(index = 0; string[index] != '\0'; index++){
		UART2_SendData8(string[index]);
		//while(!UART2_GetFlagStatus(UART2_FLAG_TC));
		while(!UART2_GetFlagStatus(UART2_FLAG_TXE));
	}
}

/**
  * @brief	Int_To_ASCII
  * @param	Integer value to be converted to ASCII
  * @retval	Pointer to char representative
  */
char *Int_To_ASCII(int value){
  static char str[11];
  char *ptr = &str[10];
  
  if(!value){
	  *--ptr = 0x30;
  }
  else{
	  
	  if((value >> 7) & 0x01){ //signal verify
          value = (~value) & 0x00FF;
		  
          for(; value; value/=10){
              *--ptr = 0x30 + value%10;
          }
		  *--ptr = 0x2d; //put the '-' signal
      }else{
		  for(;value;value/=10){
          *--ptr = 0x30 + value%10;
          }
      }
  }
  
  return ptr;
}