#include "Timer.h"

void Timer_InitMilisecond(void) {
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  TIM_DeInit(TIM2);
  TIM_TimeBaseInitTypeDef Timer_Intit;
  Timer_Intit.TIM_ClockDivision = TIM_CKD_DIV1; // 36Mhz
  Timer_Intit.TIM_CounterMode = TIM_CounterMode_Up;
  Timer_Intit.TIM_Period = 1;
  Timer_Intit.TIM_Prescaler = 42000;
  Timer_Intit.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &Timer_Intit);
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  TIM_Cmd(TIM2, DISABLE);
}

void Timer_SetPrescalar(uint16_t PSC) { TIM2->PSC = PSC; }

void Timer_WaitLoop(void) {
  do {
  } while (TIM2->CR1 & TIM_CR1_CEN);
}

void Timer_PrepareWaitTimer(uint16_t Time) {
  if (Time > 1) {
    TIM_SetCounter(TIM2, 0);
    TIM_SetAutoreload(TIM2, Time);
  } else {
    TIM_SetCounter(TIM2, 1);
    TIM_SetAutoreload(TIM2, 2);
  }

  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  NVIC_EnableIRQ(TIM2_IRQn);
  TIM_Cmd(TIM2, ENABLE);
}

void Timer_WaitMilisec(uint16_t Time) {
  TIM_PrescalerConfig(TIM2, 42000, TIM_PSCReloadMode_Immediate);
  Timer_PrepareWaitTimer(Time);
  Timer_WaitLoop();
}

void Timer_WaitMicrosec(uint16_t Time) {
  TIM_PrescalerConfig(TIM2, 42, TIM_PSCReloadMode_Immediate);
  Timer_PrepareWaitTimer(Time);
  Timer_WaitLoop();
}

void TIM2_IRQHandler(void) {
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    TIM_Cmd(TIM2, DISABLE);
  }
}
