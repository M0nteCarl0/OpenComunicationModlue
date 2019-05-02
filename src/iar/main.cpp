#include "Clock.h"
#include "Indep_WD.h"
#include "LED.h"
#include "USART_Core.hpp"
#include "USB_StreamExample.h"
int main() {
  USB_StreamExample_SetupSequnce();
  LED_Init();
  if (iWD_Fault_is_Detected()) {
    LED_RedOn();
  }
  iWD_Init();
  USB_StreamExample_ComunicationSeunence();
}
