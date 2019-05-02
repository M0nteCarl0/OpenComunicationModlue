#include "usbd_core.h"
#include "usb_dcd_int.h"
typedef  struct  USB_Stack
{
  int IsFull;
  uint8_t* ReceiveBuffer;
  int TxReady;
  int Datacount;
  int MaxRxCount;
}USB_Stack;
#ifdef __cplusplus
 extern "C" {
#endif
 int USB_Stream_Receive(uint8_t *ReceiveBuffer, int *Received);
 int USB_Stream_PutData(USB_OTG_CORE_HANDLE *Dev, int Received);
 int USB_Stream_SetupInternalReceiveFIFO(uint16_t ReceiveBufferSize);
 int USB_Stream_GetMaxRxCount(void);
 int USB_Stream_USB_Stack_Init(USB_Stack *Stack, int BufferSize);
 void USB_Stream_SetReceiveBuferSize(int BufferSize);
 int USB_Stream_GetReceiveBuferSize(void);
 int USB_Stream_USB_Stack_ResetDatacount(USB_Stack *Stack);
 int USB_Stream_USB_Stack_PutData(int *Datacount);
 void USB_Stream_InitInternalFIFODefault(void);
 void USB_Stream_InitInternalFIFO(int BufferSize);
 void USB_Stream_Init(int BufferSize);
 void USB_Stream_ClearInternalFIFO(void);
 void USB_Stream_GetDataFromStack(uint8_t *Buffer, int *State, int *N);
 void USB_Stream_Send(uint8_t *Buffer, int *N);
 int USB_Stream_GetStateTxReady(void);
 void USB_Stream_SetStateTxReady(void);
 void USB_Stream_ResetStateTxReady(void);
 uint8_t *USB_Stream_GetPointerBuffer(void);
#ifdef __cplusplus
 }
#endif 