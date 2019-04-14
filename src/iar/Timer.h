#include "stm32f4xx.h"
#ifdef __cplusplus
 extern "C" {
#endif 
 void Timer_InitMilisecond(void);
 void Timer_WaitMilisec(uint16_t Time);
 void Timer_WaitMicrosec(uint16_t Time);
 void Timer_WaitLoop(void);
 void Timer_PrepareWaitTimer(uint16_t Time);
 void Timer_SetPrescalar(uint16_t PSC);
 void TIM2_IRQHandler(void);
 
#ifdef __cplusplus
 }
#endif 


