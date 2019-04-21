#pragma once
#include "USB_Device.h"
#define  N 4096
enum USB_Comands_ERR
{
    USB_Comands_ERR_OK = 1,
    USB_Comands_ERR_MEMORY_OVR,
    USB_Comands_ERR_TRANSMIT_ERROR,
    USB_Comands_ERR_RECEIVE_ERROR,
};
enum  Comands_ID
 {
   Comands_ID_WRITE_LED_ON		= 0x1,
   Comands_ID_WRITE_LED_OFF		= 0x2,
   Comands_ID_WRITE_LED_Blinky  = 0x3,
   Comands_ID_READ_LED_Blinky   = 0x83,
 };
 enum EP_ID
 {
  EP_ID_IN						= 0x81,
  EP_ID_OUT						= 0x1,
};


class USB_Comands
{
public:
    USB_Comands( int TransatcionTimeOunt);
    USB_Comands(USB_Device Device , int TransatcionTimeOunt);
    ~USB_Comands(void);
    bool ReadComand(UINT8 ComandID,UINT8* BuffTx ,UINT16 DataCountTx,UINT8* BuffRx ,UINT16 DataCountRx);
    bool WriteComand(UINT8 ComandID,UINT8* BuffTx ,UINT16 DataCountTx,UINT16 DataReqested = 0);
    USB_Comands_ERR  LED_On(void);
    USB_Comands_ERR  LED_Off(void);
    USB_Comands_ERR  LED_Blinky(UINT16* TimeMs);
    USB_Comands_ERR  LED_BlinkyReadTime(UINT16* TimeMs);
    bool DeviceIsConected(void);
	USB_Device _Dev;
    private:
    UINT8 BufferRx[N];
    UINT8 BufferTx[N];
    int _TransatcionTimeOunt;
};

