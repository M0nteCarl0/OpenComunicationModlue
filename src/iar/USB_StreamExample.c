#include "Clock.h"
#include "Timer.h"
#include "USB_GPIO.h"
#include "USB_StreamExample.h"
#include "Comands.hpp"
#include "Indep_WD.h"

#pragma location=0x10000000
uint8_t Buff[4096];
int N; 
/****************************************************************************/
void  USB_StreamExample_SetupSequnce(void)//Пример настройки USB устройства 
{
  
    Clock_HSI_Init();//Настройка внутренего осцилятора
    Clock_HSE_Init();//Настройка внешнего осцилятора
    Clock_InitUSB();//Тактирование USB FS
    Timer_InitMilisecond();//Таймер для USB 
    USB_GPIO_Init();//Настройка GPIO
   //USB_Stream_InitInternalFIFODefault();//Первый вариант настроки USB Stream(1,0)
   //USB_Stream_InitInternalFIFO(4096)//Второй вариант настройки USB Stream(1,0)
   //OCM_LowLevelInit();//Инициализация дескрипторов(1,1)
    USB_Stream_Init(4096);//Третий вариант с инициализацией дескрипторов(1,0)
  
  
}
/****************************************************************************/
void  USB_StreamExample_ComunicationSeunence(void)
{
  do{
      iWD_RefreshCountet(); 
      if(USB_Stream_Receive(Buff,&N))//Если данные доступны то возращаем 1 иначе 0
      {
        Comands_ProcessLoop(Buff,N);//Разбор даннных и исполнение команд
      }
  }while(1);
  
}
/****************************************************************************/