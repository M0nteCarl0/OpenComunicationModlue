#include "Clock.h"
#include "Timer.h"
#include "USB_GPIO.h"
#include "USB_StreamExample.h"
#include "Comands.hpp"
#include "Indep_WD.h"
#pragma location=0x10000000
uint8_t Buff[4096];
int N; 
void  USB_StreamExample_SetupSequnce(void) 
{
  Clock_HSI_Init();
  Clock_HSE_Init();
  Clock_InitUSB();
  Timer_InitMilisecond(); 
  USB_GPIO_Init();
  USB_Stream_Init(4096);
}

void  USB_StreamExample_ComunicationSeunence(void)
{
  do{
      iWD_RefreshCountet(); 
      if(USB_Stream_Receive(Buff,&N)){
        Comands_ProcessLoop(Buff,N);
      }   
  }while(1);
}
