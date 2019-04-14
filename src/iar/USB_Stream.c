#include "OCM.h"
#include "USB_Stream.h"
#include <stdlib.h>
#include <intrinsics.h>
#pragma location= 0x10007530
USB_Stack ReceiveStack;
/******************************************************************************/
int   USB_Stream_Receive(uint8_t* ReceiveBuffer,int* Received)
{
 __disable_interrupt();
  int Ret = 0;
  int OVR = 0;
  USB_Stream_GetDataFromStack(ReceiveBuffer,&OVR,Received);
  if(!OVR)
  {
    Ret = 1; 
    USB_Stream_ClearInternalFIFO();
  }
 __enable_interrupt();
  return Ret;
}
/******************************************************************************/
int  USB_Stream_PutData(USB_OTG_CORE_HANDLE* Dev,int Received)
{
  int Ret = 1;
  ReceiveStack.Datacount = Received;
  if(ReceiveStack.Datacount > ReceiveStack.MaxRxCount)
  {  
     DCD_SetEPStatus (Dev , 
                      EP_ID_OUT , 
                      USB_OTG_EP_RX_NAK);//Пришли неверное количество  данных  повторный  запрос
     DCD_EP_Flush(Dev,EP_ID_OUT);//Сброс  EP
     Ret = 0;
     ReceiveStack.IsFull = 1;
  }
  if(ReceiveStack.Datacount <=ReceiveStack.MaxRxCount && ReceiveStack.Datacount!=0)
  {
      ReceiveStack.IsFull = 0;
  }
    DCD_EP_PrepareRx(Dev,EP_ID_OUT,ReceiveStack.ReceiveBuffer,ReceiveStack.MaxRxCount);
  
  return  Ret; 
}
/******************************************************************************/
int   USB_Stream_GetMaxRxCount(void)
{
  return ReceiveStack.MaxRxCount;
}
/******************************************************************************/
int   USB_Stream_USB_Stack_Init(USB_Stack* Stack,int  BufferSize)
{
  Stack->Datacount      = 0;
  Stack->IsFull         = 0;
  Stack->TxReady        = 0;
  Stack->MaxRxCount     = BufferSize;
  Stack->ReceiveBuffer  = (uint8_t*)malloc(BufferSize);
}
/******************************************************************************/
int   USB_Stream_USB_Stack_ResetDatacount(USB_Stack* Stack)
{
  Stack->Datacount = 0;    
}
/******************************************************************************/
void  USB_Stream_InitInternalFIFODefault(void)
{
  USB_Stream_USB_Stack_Init(&ReceiveStack,4096);
}
/******************************************************************************/
void  USB_Stream_Init(int BufferSize)
{
   USB_Stream_USB_Stack_Init(&ReceiveStack,BufferSize);
   OCM_DeviceInitLowLevel();
}
/******************************************************************************/
void  USB_Stream_InitInternalFIFO(int BufferSize)
{
  USB_Stream_USB_Stack_Init(&ReceiveStack,BufferSize);
}
/******************************************************************************/
void  USB_Stream_GetDataFromStack(uint8_t* Buffer,int* State,int* N)
{
 *N = ReceiveStack.Datacount;
 *State  = ReceiveStack.IsFull;
 for(int i = 0;i < ReceiveStack.Datacount; i++)
 {
   Buffer[i] =   ReceiveStack.ReceiveBuffer[i];
 }
}
/******************************************************************************/
void  USB_Stream_ClearInternalFIFO(void)
{
  ReceiveStack.Datacount = 0;
  for(int i = 0;i < ReceiveStack.Datacount; i++)
 {
    ReceiveStack.ReceiveBuffer[i] = 0;
 }
}
/******************************************************************************/
void  USB_Stream_Send(uint8_t* Buffer,int* N)
{
 __disable_interrupt(); 
   OCM_SendBulk(Buffer,*N); 
   USB_Stream_SetStateTxReady();
 __enable_interrupt();
}
/******************************************************************************/
int  USB_Stream_GetStateTxReady(void)
{
  return  ReceiveStack.TxReady;
}
/******************************************************************************/
void  USB_Stream_SetStateTxReady(void)
{
   ReceiveStack.TxReady = 1;
}
/******************************************************************************/
void  USB_Stream_ResetStateTxReady(void)
{ 
  ReceiveStack.TxReady = 0; 
}
/******************************************************************************/
void  USB_Stream_SetReceiveBuferSize(int BufferSize)
{
   USB_Stream_USB_Stack_Init(&ReceiveStack,BufferSize);
}
/******************************************************************************/
int   USB_Stream_GetReceiveBuferSize(void)
{
  return ReceiveStack.MaxRxCount;
}
/******************************************************************************/
uint8_t* USB_Stream_GetPointerBuffer(void)
{
  return ReceiveStack.ReceiveBuffer;
}
/******************************************************************************/