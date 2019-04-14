#pragma once
#include <string>
#include <stdint.h>
#include "winusb.h"
#include "DeviceInfoSet.h"
#include "HiRessTimeMeasure.h"
#ifndef _USB_DEVICE_
#define _USB_DEVICE_
 typedef struct USB_LangIDDescriptor
{
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint16_t wLANGID;
}USB_LangIDDescriptor;
using namespace std;

class USB_Device
{
public:
	USB_Device(void);
	USB_Device(GUID& GUIDDevice);
	~USB_Device(void);
	void SetGUID(GUID& GUIDDevice);
    GUID GetGUID(void);

	bool DeviceFound(void);
	int GetCountFoundedDevices(void);
	
	USB_DEVICE_DESCRIPTOR GetDeviceDescriptor(void);
	WINUSB_PIPE_INFORMATION GetEndpointDescriptor(uint8_t ID,uint8_t InterfaceID = 0);
	USB_CONFIGURATION_DESCRIPTOR GetConfigurationDescriptor(uint8_t ConfigID = 0);
	USB_INTERFACE_DESCRIPTOR GetInterfaceDescriptor(uint8_t IntefaceID = 0);
	USB_LangIDDescriptor GetLangIDDescriptor(void);

	bool  ControlEP0DataTransfer(WINUSB_SETUP_PACKET &Setup,uint8_t* pBuf,LONG dBufSize);
	bool TransferInterfaceDeviceEP(uint8_t uEndPoint, uint8_t* pBuf, LONG dBufSize,ULONG TimeOutMs);

	string GetManufacureName(void);
	string GetDeviceName(void);
	string GetSerialNumber(void);
	void EnumerateDevices(void);
    PVOID GetIntreface(void);
	bool Open(void);
	void Close(void);
    USB_Device operator=(USB_Device& Source);
private:
    void SetFile(HANDLE Source);
    HANDLE GetFile(void);
    void SetInterface(PVOID Source);
  
	GUID		  _DeviceUniqeID;
	string GetGenerateStringFromUnicodeByteArray(UCHAR* InputArray,uint16_t BufferSize);
	HANDLE			m_hFile	;
	PVOID			m_hIface;
	HiRessTimeMeasure TimeOperation;

};
#endif

