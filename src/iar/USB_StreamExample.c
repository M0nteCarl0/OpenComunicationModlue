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
void  USB_StreamExample_SetupSequnce(void)//������ ��������� USB ���������� 
{
  
    Clock_HSI_Init();//��������� ���������� ����������
    Clock_HSE_Init();//��������� �������� ����������
    Clock_InitUSB();//������������ USB FS
    Timer_InitMilisecond();//������ ��� USB 
    USB_GPIO_Init();//��������� GPIO
   //USB_Stream_InitInternalFIFODefault();//������ ������� �������� USB Stream(1,0)
   //USB_Stream_InitInternalFIFO(4096)//������ ������� ��������� USB Stream(1,0)
   //OCM_LowLevelInit();//������������� ������������(1,1)
    USB_Stream_Init(4096);//������ ������� � �������������� ������������(1,0)
  
  
}
/****************************************************************************/
void  USB_StreamExample_ComunicationSeunence(void)
{
  do{
      iWD_RefreshCountet(); 
      if(USB_Stream_Receive(Buff,&N))//���� ������ �������� �� ��������� 1 ����� 0
      {
        Comands_ProcessLoop(Buff,N);//������ ������� � ���������� ������
      }
  }while(1);
  
}
/****************************************************************************/