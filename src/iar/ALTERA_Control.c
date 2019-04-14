#include "ALTERA_Control.h"
void  ALTERA_Control_Init(ALTERA_InitStructure* Init)
{
        GPIO_InitTypeDef GPIO_InitStructure;  
 
        //Init StartConv ALTERA
        GPIO_InitStructure.GPIO_Pin = Init->IO_PIN_ALTERA_START_CONV;              
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
        GPIO_Init (Init->IO_PORT_ALTERA_START_CONV, &GPIO_InitStructure);

        //Init SR0 ALTERA
        GPIO_InitStructure.GPIO_Pin = Init->IO_PIN_ALTERA_SR0;              
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
        GPIO_Init (Init->IO_PORT_ALTERA_SR0, &GPIO_InitStructure);
        
        //Init SR1 ALTERA
        GPIO_InitStructure.GPIO_Pin = Init->IO_PIN_ALTERA_SR1;              
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
        GPIO_Init (Init->IO_PORT_ALTERA_SR1, &GPIO_InitStructure);
        
        //Init RSVD0 ALTERA
        GPIO_InitStructure.GPIO_Pin = Init->IO_PIN_ALTERA_RSVD0;              
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
        GPIO_Init (Init->IO_PORT_ALTERA_RSVD0, &GPIO_InitStructure);
        
        //Init RSVD0 ALTERA
        GPIO_InitStructure.GPIO_Pin = Init->IO_PIN_ALTERA_RSVD1;              
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
        GPIO_Init (Init->IO_PORT_ALTERA_RSVD1, &GPIO_InitStructure);
        ALTERA_Control_SelectRange(Init,ALTERA_Control_Range_500us);
        
}
/******************************************************************************/
void  ALTERA_Control_StartADCClocking(ALTERA_InitStructure* Init)
{
   if(Init)
  {
    GPIO_SetBits(Init->IO_PORT_ALTERA_START_CONV,Init->IO_PIN_ALTERA_START_CONV); 
  } 
}
/******************************************************************************/
void  ALTERA_Control_StopADCClocking(ALTERA_InitStructure* Init)
{
  if(Init)
  {
    GPIO_ResetBits(Init->IO_PORT_ALTERA_START_CONV,Init->IO_PIN_ALTERA_START_CONV); 
  }
  
}
/******************************************************************************/
void  ALTERA_Control_SelectRange(ALTERA_InitStructure* Init, ALTERA_Control_Range Range)
{
  
  Init->Range = Range;
  switch(Range)
  {
    
  case ALTERA_Control_Range_500us:
    {
        GPIO_ResetBits(Init->IO_PORT_ALTERA_SR0,Init->IO_PIN_ALTERA_SR0);
        GPIO_ResetBits(Init->IO_PORT_ALTERA_SR1,Init->IO_PIN_ALTERA_SR1);
        break;
    }
  case ALTERA_Control_Range_1000us:
    {
       GPIO_SetBits(Init->IO_PORT_ALTERA_SR0,Init->IO_PIN_ALTERA_SR0);
       GPIO_ResetBits(Init->IO_PORT_ALTERA_SR1,Init->IO_PIN_ALTERA_SR1);
       break;
    }
  case ALTERA_Control_Range_2000us:
    {
       GPIO_ResetBits(Init->IO_PORT_ALTERA_SR0,Init->IO_PIN_ALTERA_SR0);
       GPIO_SetBits(Init->IO_PORT_ALTERA_SR1,Init->IO_PIN_ALTERA_SR1);
       break;
    }
  case ALTERA_Control_Range_4000us:
    {
       GPIO_SetBits(Init->IO_PORT_ALTERA_SR0,Init->IO_PIN_ALTERA_SR0);
       GPIO_SetBits(Init->IO_PORT_ALTERA_SR1,Init->IO_PIN_ALTERA_SR1);
       break;
    }
    
    
  }
  
  
}
/******************************************************************************/
ALTERA_Control_Range ALTERA_Control_GetRange(ALTERA_InitStructure* Init)
{
  return Init->Range;
}
