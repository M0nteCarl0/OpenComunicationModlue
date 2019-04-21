
#include "Comand_protocol.h"
#include "Comands.hpp"
#include "ByteConversion.hpp"
#include "LED.h"
#include "FlashExtended.hpp"
uint16_t Time;
void  Comands_ProcessLoop(uint8_t* Buff , int N)
{
  uint8_t ComandID;
  if(Comand_protocol_parcer(Buff,&N,&ComandID)){
      switch(ComandID){
          case  Comands_ID_WRITE_LED_ON: {
          Comands_ID_WRITE_LED_ON_EV(Buff,&N );
          break;
          }
          case  Comands_ID_WRITE_LED_OFF: {
          Comands_ID_WRITE_LED_OFF_EV( Buff, &N );
          break;
          }
          case Comands_ID_WRITE_LED_Blinky: {
          Comands_ID_WRITE_LED_Blinky_EV(Buff, &N);
          break;
          }
          case Comands_ID_READ_LED_Blinky: {
          Comands_ID_READ_LED_Blinky_EV(Buff,&N );
          break;
          }  
        }
      }
}


void  Comands_ID_WRITE_LED_ON_EV(uint8_t* Buff , int* N )
{
  LED_RedOn();
}

void  Comands_ID_WRITE_LED_OFF_EV(uint8_t* Buff , int* N )
{
  LED_RedOff();
}

void  Comands_ID_WRITE_LED_Blinky_EV(uint8_t* Buff , int* N )
{
  Time = Buff[6] | (Buff[7]<<8);
}

void  Comands_ID_READ_LED_Blinky_EV(uint8_t* Buff , int* N )
{ 
  int SN  = Comand_protocol_GetRequstedByteCount(Buff); 
  Buff[6] = Time & 0xff;
  Buff[7] = Time >> 8;
  USB_Stream_Send(Buff,&SN); 
}



