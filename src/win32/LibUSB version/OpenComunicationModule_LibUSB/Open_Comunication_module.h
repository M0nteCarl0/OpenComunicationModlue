#ifndef _OCM_
#define _OCM_
#include "usb_device.h"
class Open_Comunication_module :
	public USB_Device
{
public:
	Open_Comunication_module(void);
	~Open_Comunication_module(void);
};
#endif
