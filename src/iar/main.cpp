#include "USB_StreamExample.h"
#include "USART_Core.hpp"
#include "Clock.h"
#include "DDC12_Core.h"
#include "LED.h"
#include "Indep_WD.h"
int main()
{
  USB_StreamExample_SetupSequnce();//Настройка HW и USB Stream
  USART_Core_Test();
  DDC12_Core_Init();
  LED_Init();
  if(iWD_Fault_is_Detected())
  {
    LED_RedOn();
  }
   
  
  iWD_Init();
  USB_StreamExample_ComunicationSeunence();//Основной цикл обработки принятых данныъх
}
