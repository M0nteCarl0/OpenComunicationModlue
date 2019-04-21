#include "StdAfx.h"
#include "USB_Comands.h"

 USB_Comands:: USB_Comands(USB_Device Device , int TransatcionTimeOunt)
 {
	_Dev = Device;
	_TransatcionTimeOunt = TransatcionTimeOunt;
	 memset(&BufferTx,0,N);
	 memset(&BufferRx,0,N);
 }

USB_Comands::USB_Comands(int TransatcionTimeOunt)
{
   _Dev.Open();
   _TransatcionTimeOunt = TransatcionTimeOunt;
   memset(&BufferTx,0,N);
   memset(&BufferRx,0,N);  
}
/****************************************************************************************************/
USB_Comands::~USB_Comands(void)
{
}

/****************************************************************************************************/
bool  USB_Comands:: ReadComand(UINT8 ComandID,UINT8* BuffTx ,UINT16 DataCountTx,UINT8* BuffRx ,UINT16 DataCountRx)
{
	bool Res = 0;
	if(WriteComand( ComandID,BuffTx , DataCountTx, DataCountRx))
	{
	    if(_Dev.TransferInterfaceDeviceEP(EP_ID_IN,BuffRx,DataCountRx,_TransatcionTimeOunt))
	    {
	        Res = 1;
	    }
	}
	return  Res;
}
/****************************************************************************************************/
bool USB_Comands:: WriteComand(UINT8 ComandID,UINT8* BuffTx ,UINT16 DataCountTx,UINT16 DataReqested )
{
	OVERLAPPED Ovl;
	BuffTx[0] = 0x92;
	BuffTx[1] = ComandID;
	BuffTx[2] = DataCountTx & 0xFF;
	BuffTx[3] = DataCountTx >> 8;
	BuffTx[4] = DataReqested & 0xFF;
	BuffTx[5] = DataReqested >> 8;
	return  _Dev.TransferInterfaceDeviceEP(EP_ID_OUT,BuffTx,DataCountTx,_TransatcionTimeOunt);
}

USB_Comands_ERR   USB_Comands:: LED_On(void)
{
	return (USB_Comands_ERR) WriteComand(Comands_ID_WRITE_LED_ON,BufferTx,5);
}

USB_Comands_ERR  USB_Comands:: LED_Off(void)
{
	return (USB_Comands_ERR) WriteComand(Comands_ID_WRITE_LED_OFF,BufferTx,5);
}

USB_Comands_ERR  USB_Comands:: LED_Blinky(UINT16* TimeMs)
{
	int NS  = 8;
	BufferTx[6] = *TimeMs & 0xFF;
	BufferTx[7] = *TimeMs>>8;
	return (USB_Comands_ERR) WriteComand(Comands_ID_WRITE_LED_Blinky,BufferTx,NS);;
}

USB_Comands_ERR  USB_Comands::  LED_BlinkyReadTime(UINT16* TimeMs)
{
	int NR = 8;
	int NS = 6;
	bool Res =  ReadComand(Comands_ID_READ_LED_Blinky,BufferTx ,NS,BufferRx ,NR);
	if(Res)
	{
		 *TimeMs =  BufferRx[6] | BufferRx[7] <<8;
	}
	return (USB_Comands_ERR) Res;
}
/****************************************************************************************************/
 bool  USB_Comands:: DeviceIsConected(void)
 {
	 return  _Dev.Open();
 }
 /****************************************************************************************************/