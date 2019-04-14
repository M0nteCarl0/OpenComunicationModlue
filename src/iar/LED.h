
#include "stm32f4xx.h"
#pragma once
#ifndef _LED_
#define _LED_
#ifdef __cplusplus
 extern "C" {
#endif 



#if 0   

#endif  

typedef struct LED_InitStructure
{
  
  GPIO_TypeDef* IO_PORT_LEDS;
  
  uint32_t IO_PIN_LED_GREEN;
  uint32_t IO_PIN_LED_RED;
 
   
}LED_InitStructure;
  

void LED_Reset_RED(LED_InitStructure* Init);
void LED_Set_RED(LED_InitStructure* Init);
void LED_Init(void);

void LED_GreenOn(void);
void LED_GreenOff(void);

void LED_RedOn(void);
void LED_RedOff(void);

void LED_OrangeOn(void);
void LED_OrangeOff(void);

void LED_BlueOn(void);
void LED_BlueOff(void);

void  KT1On(void);
void KT1Off(void);

#ifdef __cplusplus
}
#endif 
#endif