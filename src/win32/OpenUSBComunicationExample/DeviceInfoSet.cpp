#include "DeviceInfoSet.h"

/***************************************************************************/
DeviceInfoSet::DeviceInfoSet(void)
{
}

/***************************************************************************/
DeviceInfoSet::~DeviceInfoSet(void)
{
}
/***************************************************************************/
DWORD			DeviceInfoSet::Create	(const GUID * pIfaceOrClassId	    ,
									   bool   bForPresend    ,
									   bool   bForInterface   )
{

	DWORD dResult;

    if (ERROR_SUCCESS	     == (  dResult  = 
    
       (INVALID_HANDLE_VALUE != (m_hDevInfo = 

       SetupDiGetClassDevsA   (pIfaceOrClassId, NULL, NULL,

			  ((bForPresend  ) ? DIGCF_PRESENT			 : 0) |
			  ((bForInterface) ? DIGCF_INTERFACEDEVICE   : 0))))
	      
      ? ERROR_SUCCESS : (m_hDevInfo = NULL, ::GetLastError ())))
    {
    }

    return dResult;

}
/***************************************************************************/
void		DeviceInfoSet::	Close			()
{

	 if (m_hDevInfo)
    {
		m_hDevInfo = (::SetupDiDestroyDeviceInfoList (m_hDevInfo), NULL);
    }

}
/***************************************************************************/
bool			DeviceInfoSet::	SelectDevInfo	(int  iDevInfo,  bool   bParentDevId   )
{

	 m_sDevInfo.cbSize = sizeof (m_sDevInfo);

    if (0 <= (m_iDevInfo = (::SetupDiEnumDeviceInfo 

    	     (m_hDevInfo, iDevInfo, & m_sDevInfo)) ? iDevInfo : -1))
    {
		return true ;
    }
		return false;

}
/***************************************************************************/
bool			DeviceInfoSet::	SelectInterface	(/*m_iDevInfo*/ REFIID uInterfaceId )
{


	  m_sDevIface.cbSize = sizeof (m_sDevIface);

    if (::SetupDiEnumDeviceInterfaces	  (m_hDevInfo	  ,
//										 & m_sDevInfo	  ,
										   NULL  		  ,
										 & uInterfaceId	  ,
										   m_iDevInfo	  ,
										 & m_sDevIface	 ))
    {
	m_sDevIfaceDet.cbSize = sizeof (m_sDevIfaceDet);

    if (::SetupDiGetInterfaceDeviceDetail (m_hDevInfo	  ,
				  						 & m_sDevIface    ,
										 & m_sDevIfaceDet ,
							sizeof (	   m_pReserved	 ),
										   NULL			  ,
										   NULL	         ))
    {
	return true;
    }
    }
	return false;



}
/***************************************************************************/