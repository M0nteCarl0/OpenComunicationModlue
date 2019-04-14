#include "Comand_protocol.h"
#define Signature 0x92
/**
******************************************************************************
* @file    Comand_protocol.c
* @author  TechNotarius
* @version V 0.5.1
* @date    5-june-2017
* @brief   Skeleton for protocol implentation
*         
*/ 
/****************************************************************************/
int Comand_protocol_CheckHeader(uint8_t* Buff,int* N)//Фильтр заголовка
{
   int Flag = 0;
   int DataReceived = Buff[2] |( Buff[3] << 8); //Послано в модуль
   if(Buff[0] == Signature)
   {   
     if(DataReceived==*N)
     {
        Flag = 1;
     }
   }
   return Flag;
}
/****************************************************************************/
int Comand_protocol_CheckData(uint8_t* Buff,int* N)//
{
  return Comand_protocol_CheckHeader(Buff,N);
}
/****************************************************************************/
int Comand_protocol_parcer(uint8_t* Buff,int* N,uint8_t* ComandID)//Функция возврата отфильтрованых данныъ
{
        int Flag = 0;    
        if(Comand_protocol_CheckData(Buff,N))
        {
          *ComandID = Buff[1];
          Flag = 1; 
        }
  return  Flag;
}
/****************************************************************************/
int Comand_protocol_GetRequstedByteCount(uint8_t* Buff)
{
  int  DataToSend =  Buff[4] |( Buff[5] << 8);
  return DataToSend;
};
/****************************************************************************/