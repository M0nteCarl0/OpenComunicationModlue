#include "Indep_WD.h"
uint16_t GuardTime = 5000; // ms

void iWD_Init(void) {
  RCC_LSICmd(ENABLE);
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
  /* IWDG counter clock: LSI/32 = 1 Khz = 1 ms  */
  IWDG_SetPrescaler(IWDG_Prescaler_32);
  IWDG_SetReload(GuardTime);
  IWDG_ReloadCounter();
  IWDG_Enable();
}

int iWD_Fault_is_Detected(void) {
  int Flag = 0;
  if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET) {
    Flag = 1;
    RCC_ClearFlag();
  }
  return Flag;
}

void iWD_RefreshCountet(void) { IWDG_ReloadCounter(); }
