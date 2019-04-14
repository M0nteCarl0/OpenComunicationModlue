// OpenUSBComunicationExample.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "DeviceInfoSet.h"
#include "USB_Device.h"
#include "Open_Comunication_module.h"
#include "USB_Comands.h"
#include  <iostream>
Open_Comunication_module MyDev;
void BulkCommadConsole(void)
{


    USB_Comands Comnds = USB_Comands(MyDev,1000);

    int CM;
    if(Comnds.DeviceIsConected())
    {

        cout << "Module Conected!\n";
Begin:
        cout << "Select  CMD \n";
        cout << "0 - RED LED ON \n1 - RED LED OFF\n3 - Write Time LED Blink\n4 - Read Time LED Blink\n5- EXIT\n";
        cout <<"CMD:";
        cin >> CM;

        switch(CM)
        {

            case 0:
            {
                cout <<" RED LED ON\n";
                Comnds.LED_On();
                goto Begin;
                break;
            }
            case 1:
            {
                cout <<" RED LED OFF\n";
                Comnds.LED_Off();
                goto Begin;
                break;
            }

            case 3:
            {
                uint16_t Time = 0;
                cout << "Write Time  in milisec to module\n";
                cin >> Time;   
                Comnds.LED_Blinky(&Time);
                goto Begin;
                break;
            }
            case 4:
            {
                uint16_t Time = 0;
                cout << "Read Time in milisec from module\n";
                Comnds.LED_BlinkyReadTime(&Time);
                cout << "Readed Time " << Time << "ms\n";
                goto Begin;
                break;
            }

            case 5:
            {
				Comnds._Dev.Close();
                 exit(0);
            };
        }
    
	}
	else
	{
		cout << "Device not found\n";
		getchar();
	}

}




void GetDescriptors(void)
{
	if(MyDev.Open())
	{

  	   USB_DEVICE_DESCRIPTOR _Descriptor = MyDev.GetDeviceDescriptor();
	   USB_CONFIGURATION_DESCRIPTOR _DescriptorConf = MyDev.GetConfigurationDescriptor();
	   USB_INTERFACE_DESCRIPTOR _DescriptorInteface = MyDev.GetInterfaceDescriptor();
	   WINUSB_PIPE_INFORMATION EP1 = MyDev.GetEndpointDescriptor(0x0);
	   USB_LangIDDescriptor Lang = MyDev.GetLangIDDescriptor();
	   string Manufactory    = 	 MyDev.GetManufacureName();
	   string DeviceName     =  MyDev.GetDeviceName();
	   string Serial =   MyDev.GetSerialNumber();
	   MyDev.Close();

	}
	else
	{
		printf("DeviceNotConected\n");

	}
	
	system("pause");

}



int _tmain(int argc, _TCHAR* argv[])
{

	BulkCommadConsole();
	return 0;
}

