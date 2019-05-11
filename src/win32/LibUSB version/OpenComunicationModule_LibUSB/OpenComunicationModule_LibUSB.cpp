// OpenComunicationModule_LibUSB.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <libusb-1.0\libusb.h>
#include <stdio.h>
#include <string.h>



int _tmain(int argc, _TCHAR* argv[])
{
    libusb_device **devs;
    libusb_context* Contex;
    libusb_device_handle * handle;
	ssize_t cnt;
	int r, i;

	

	r = libusb_init(&Contex);
	if (r < 0)
		return r;

   handle =  libusb_open_device_with_vid_pid(Contex,0x63,0x5);
 
   libusb_close(handle);

	

	libusb_exit(Contex);
getchar();
	return 0;
}

