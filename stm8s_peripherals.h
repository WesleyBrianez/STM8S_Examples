/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM8S_PERIPHERALS_H
#define __STM8S_PERIPHERALS_H

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

/* Define to stm8s peripheral control ----------------------------------------*/

#define TurnOn		GPIO_WriteLow
#define TurnOff		GPIO_WriteHigh
#define Toggle		GPIO_WriteReverse

#define LED_EVAL	GPIOD, GPIO_PIN_0
#define	LED_TX		GPIOC, GPIO_PIN_5
#define	LED_RX		GPIOC, GPIO_PIN_7

/* Exported Functions --------------------------------------------------------*/
void CLK_Config(void);
void TIM2_Config(void);
void GPIO_Config(void);
void UART2_Config(void);
void Delay_ms(uint16_t time);
bool String_Compare(char *FirstString, char *SecondString);
bool Byte_Compare(char x, char y);
void Send_String(char *string);
void Send_CLK_String(int hours, int minutes, int seconds);
char *Int_To_ASCII(int num);


#endif /* __STM8S_PERIPHERALS_H */