#include "Open_Comunication_module.h"
GUID OCM =  {0x658596FD,0xACD8,0x418D,0x94,0x69,0x57,0x67,0x18,0x64,0xEF,0x83};

Open_Comunication_module::Open_Comunication_module(void):USB_Device(OCM)
{
}


Open_Comunication_module::~Open_Comunication_module(void)
{
}
