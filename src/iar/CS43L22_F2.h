#pragma once
#include "stm32f4xx.h"
#ifndef CS43L22_F2
#define CS43L22_F2
#ifdef __cplusplus
 extern "C" {
#endif 
#define ADDR 0x94  
void CS43L22_F2_InitAudiodac(void);
uint8_t CS43L22_F2_ReadPowerControl(void);

   
   
   
#ifdef __cplusplus
}
#endif 
#endif