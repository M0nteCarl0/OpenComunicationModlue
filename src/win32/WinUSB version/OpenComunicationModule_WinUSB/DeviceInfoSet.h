#include <Windows.h>
#include <SetupAPI.h>
#ifndef _USB_DEVICEINFOSET_
#define _USB_DEVICEINFOSET_
class DeviceInfoSet
{
public:
	DeviceInfoSet(void);
	~DeviceInfoSet(void);
	DWORD Create(const GUID * pIfaceOrClassId, bool bForPresend = false , bool bForInterface = true);
	void Close ();
	bool SelectDevInfo	(int iDevInfo , bool bParentDevId  = false );
	bool SelectInterface (REFIID uInterfaceId );
	bool IsDevPresent	() const {
		 return (m_sDevIface.Flags & SPINT_ACTIVE) ? true : false; };
	const TCHAR * GetInstancePath () const {
		  return m_sDevIfaceDet.DevicePath; };
protected :
	HDEVINFO					m_hDevInfo;
	int							m_iDevInfo;
	SP_DEVINFO_DATA			    m_sDevInfo;
	SP_DEVICE_INTERFACE_DATA    m_sDevIface;
	union
	{
	  SP_INTERFACE_DEVICE_DETAIL_DATA	m_sDevIfaceDet;  
	  TCHAR m_pReserved [MAX_PATH * 4];
	};
};

#endif