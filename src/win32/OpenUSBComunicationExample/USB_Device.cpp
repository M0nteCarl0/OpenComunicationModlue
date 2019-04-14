#include "USB_Device.h"

/***********************************************************************************/
USB_Device::USB_Device(void)
{
	m_hFile = NULL;
	m_hIface = NULL;
}
/***********************************************************************************/
USB_Device:: USB_Device (GUID& GUIDDevice)
{
	m_hFile = NULL;
	m_hIface = NULL;
	SetGUID(GUIDDevice);
}
/***********************************************************************************/
USB_Device::~USB_Device(void)
{
	Close();
}
/***********************************************************************************/
   void USB_Device:: SetGUID(GUID& GUIDDevice)
{

	_DeviceUniqeID = GUIDDevice;

}
/***********************************************************************************/
GUID USB_Device:: GetGUID(void)
{

    return _DeviceUniqeID;

}
/***********************************************************************************/
bool USB_Device::DeviceFound(void)
{

	


	return 0;
}
/***********************************************************************************/
int USB_Device:: GetCountFoundedDevices(void)
{


	return 0;
}
/***********************************************************************************/
void  USB_Device:: EnumerateDevices(void)
{




}
/***********************************************************************************/
bool USB_Device:: Open(void)
{
	DeviceInfoSet	 DevInfo;

	if (m_hFile)
	{
	return true;
	}


	if (ERROR_SUCCESS == DevInfo.Create (&_DeviceUniqeID))
    {
    for (int i = 0; DevInfo.SelectDevInfo (i); i ++)
    {
		if (DevInfo.SelectInterface (_DeviceUniqeID)
		&&  DevInfo.IsDevPresent    ( ))
		{
			goto lCreate;
	    }
	}
	}
	return false;

lCreate :

    if (INVALID_HANDLE_VALUE   == 
       (			   m_hFile  = ::CreateFile 
					  (DevInfo.GetInstancePath (),
					   GENERIC_WRITE 
			         | GENERIC_READ				 ,
					   0						 ,
					   NULL						 ,
					   OPEN_EXISTING			 ,
					   FILE_FLAG_OVERLAPPED |
					   0						 ,
					   NULL					   )))
    {
		return (m_hFile = NULL, false);
	}

    if (! WinUsb_Initialize (m_hFile, & m_hIface))
    {
		m_hIface = NULL;

		return (Close (), false);
	}
		return true;



}
/***********************************************************************************/
void USB_Device:: Close(void)
{
	if (m_hFile )
	{
		m_hFile  = (::CloseHandle (m_hFile), NULL);
	}
	if (m_hIface)
	{
		m_hIface = (WinUsb_Free  (m_hIface), NULL);
	}

}
/***********************************************************************************/
   USB_DEVICE_DESCRIPTOR USB_Device:: GetDeviceDescriptor(void)
{
	USB_DEVICE_DESCRIPTOR _Descriptor;
	ULONG Btr = 0;
	WinUsb_GetDescriptor(m_hIface,USB_DEVICE_DESCRIPTOR_TYPE,0,0,(uint8_t*)&_Descriptor,sizeof(_Descriptor),&Btr);
	return _Descriptor;
}
/***********************************************************************************/
   WINUSB_PIPE_INFORMATION USB_Device:: GetEndpointDescriptor(uint8_t ID,uint8_t InterfaceID)
{
	WINUSB_PIPE_INFORMATION _Descriptor;
    ULONG Btr = 0;
	WinUsb_QueryPipe(m_hIface,InterfaceID,ID,&_Descriptor);
	return _Descriptor;
}
/***********************************************************************************/
   USB_CONFIGURATION_DESCRIPTOR USB_Device:: GetConfigurationDescriptor(uint8_t ConfigID)
{
	USB_CONFIGURATION_DESCRIPTOR _Descriptor;
	unsigned long Btr;
	WinUsb_GetDescriptor(m_hIface,USB_CONFIGURATION_DESCRIPTOR_TYPE,ConfigID,0,(uint8_t*)&_Descriptor,sizeof(_Descriptor),&Btr);
	return _Descriptor;
}
/***********************************************************************************/
USB_LangIDDescriptor USB_Device::GetLangIDDescriptor(void)
{
	USB_LangIDDescriptor _Descriptor;
	unsigned long Btr;
	WinUsb_GetDescriptor(m_hIface,USB_STRING_DESCRIPTOR_TYPE,0,0,(uint8_t*)&_Descriptor,sizeof(_Descriptor),&Btr);
	return  _Descriptor;
};
/***********************************************************************************/
USB_INTERFACE_DESCRIPTOR USB_Device:: GetInterfaceDescriptor(uint8_t IntefaceID)
{
	USB_INTERFACE_DESCRIPTOR _Descriptor;
	WinUsb_QueryInterfaceSettings(m_hIface,IntefaceID,&_Descriptor);
	return _Descriptor;
}
/***********************************************************************************/
   string USB_Device::GetManufacureName(void)
{
	 unsigned long Btr;
	 uint8_t Temp[64];
	 memset(Temp,0,64);
	 uint8_t Iman =  GetDeviceDescriptor().iManufacturer;
	 uint16_t LangID = GetLangIDDescriptor().wLANGID;
	 WinUsb_GetDescriptor(m_hIface,USB_STRING_DESCRIPTOR_TYPE,Iman,LangID ,Temp,64,&Btr);
	 return  GetGenerateStringFromUnicodeByteArray(Temp,Btr);
}
/***********************************************************************************/
string USB_Device::GetDeviceName(void)
{
     unsigned long Btr;
	 uint8_t Temp[64];
	 memset(Temp,0,64);
	 uint8_t Iman =  GetDeviceDescriptor().iProduct;
	 uint16_t LangID = GetLangIDDescriptor().wLANGID;
	 WinUsb_GetDescriptor(m_hIface,USB_STRING_DESCRIPTOR_TYPE,Iman,LangID ,Temp,64,&Btr);

  return  GetGenerateStringFromUnicodeByteArray(Temp,Btr);
}
/***********************************************************************************/
string USB_Device::GetSerialNumber(void)
{
  
  unsigned long Btr;
  uint8_t Temp[64];
  memset(Temp,0,64);
  uint8_t Iman =  GetDeviceDescriptor().iSerialNumber;
  uint16_t LangID = GetLangIDDescriptor().wLANGID;
  WinUsb_GetDescriptor(m_hIface,USB_STRING_DESCRIPTOR_TYPE,Iman,LangID ,Temp,64,&Btr);
  return GetGenerateStringFromUnicodeByteArray(Temp,Btr);
}
/***********************************************************************************/
string  USB_Device::GetGenerateStringFromUnicodeByteArray(uint8_t* InputArray,uint16_t BufferSize)
{
	string Res;
	char* UnicodeData = new char[(BufferSize/2)+1];
	memset(UnicodeData,0,(BufferSize/2)+1);
	uint16_t UnicodeConbter  = 0;
	for(uint16_t i = 2;i<BufferSize;i++)
	{

		if(InputArray[i]!=0x0)
		{
			UnicodeData[UnicodeConbter++] = InputArray[i]; 
			if(i == (BufferSize-1))
			{
			UnicodeData[UnicodeConbter] = '/0';


			}
		}
	}

	Res = string((char*)UnicodeData);
	delete[] UnicodeData;
	return Res;
}
/***********************************************************************************/
 bool  USB_Device::ControlEP0DataTransfer(WINUSB_SETUP_PACKET &Setup,uint8_t* pBuf,LONG dBufSize)
 {
	bool Res = false;
	ULONG DT = 0;
	Res = WinUsb_ControlTransfer(m_hIface,Setup,pBuf,dBufSize,&DT,NULL);
	 if(DT == dBufSize && Res )
 {

	 return true;

 }
 else
 {

	 return false;

 }



 }
/***********************************************************************************/
 bool  USB_Device:: TransferInterfaceDeviceEP(uint8_t uEndPoint, uint8_t* pBuf, LONG dBufSize,ULONG TimeOutMs)
 {

  OVERLAPPED * o = NULL;
  DWORD dResult; DWORD dTransfered = 0;
	
	bool Flag = true;
	WinUsb_SetPipePolicy(m_hIface,uEndPoint,PIPE_TRANSFER_TIMEOUT,sizeof(ULONG),&TimeOutMs);
	
	
	
	if (uEndPoint & 0x80)
	{
	 	WinUsb_SetPipePolicy(m_hIface,uEndPoint,IGNORE_SHORT_PACKETS,sizeof(bool),&Flag);
		dResult = WinUsb_ReadPipe  (m_hIface, uEndPoint, pBuf, dBufSize, & dTransfered, o) 

				  ? ERROR_SUCCESS : ::GetLastError ();
	}
	else
	{
		WinUsb_SetPipePolicy(m_hIface,uEndPoint,SHORT_PACKET_TERMINATE,sizeof(bool),&Flag);
        WinUsb_SetPipePolicy(m_hIface,uEndPoint,AUTO_CLEAR_STALL,sizeof(bool),&Flag);
        
		dResult = WinUsb_WritePipe (m_hIface, uEndPoint, pBuf, dBufSize, & dTransfered, o)

				  ? ERROR_SUCCESS : ::GetLastError ();
	}
	WinUsb_FlushPipe(m_hIface,uEndPoint);
	return ((ERROR_SUCCESS    == dResult)
		 || (ERROR_IO_PENDING == dResult)) ? true : false;

 }
 /***********************************************************************************/
 #if 0
  USB_TraceTransaction  USB_Device:: ControlEP0DataTransferEx(WINUSB_SETUP_PACKET &Setup,uint8_t* pBuf,LONG dBufSize)
  {


  return  USB_TraceTransaction();
  }
  /***********************************************************************************/
  USB_TraceTransaction  USB_Device:: TransferInterfaceDeviceEPEx(uint8_t uEndPoint, uint8_t* pBuf, LONG dBufSize,ULONG TimeOutMs)
  {


    return  USB_TraceTransaction();
  }
#endif
/***********************************************************************************/
 void USB_Device:: SetFile(HANDLE Source)
 {
     m_hFile =  Source;
 }
 /***********************************************************************************/
 HANDLE USB_Device:: GetFile(void)
 {
   return m_hFile;
 }
/***********************************************************************************/
 void USB_Device:: SetInterface(PVOID Source)
 {
    m_hIface = Source;
 }
 /***********************************************************************************/
 PVOID USB_Device::  GetIntreface(void)
 {
 return m_hIface;
 }
 /***********************************************************************************/
 USB_Device USB_Device::  operator=(USB_Device& Source)
 {
 this->SetGUID(Source.GetGUID());
 this->SetFile(Source.GetFile());
 this->SetInterface(Source.GetIntreface());
 return *this;
 }
 /***********************************************************************************/