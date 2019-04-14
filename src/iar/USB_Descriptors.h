#include <stdint.h>

__ALIGN_BEGIN  typedef struct USB_LangIDDescriptor
{
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint16_t wLANGID;
}USB_LangIDDescriptor __ALIGN_END;

__ALIGN_BEGIN  typedef struct USB_DeviceDescriptor
{
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint16_t  bcdUSB;
  uint8_t bDeviceClass;
  uint8_t bDeviceSubclass;
  uint8_t bDeviceProtocol;
  uint8_t  bMaxPacketSize0;
  uint16_t  idVendor;
  uint16_t  idProduct;
  uint16_t   bcdDevice ;
  uint8_t  iManufacturer;
  uint8_t iProduct;
  uint8_t iSerialNumber;
  uint8_t  bNumConfigurations;  
}USB_DeviceDescriptor __ALIGN_END;


__ALIGN_BEGIN  typedef struct USB_device_qualifier
{
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint16_t  bcdUSB;
  uint8_t bDeviceClass;
  uint8_t bDeviceSubclass;
  uint8_t bDeviceProtocol;
  uint8_t  bMaxPacketSize0;
  uint8_t  bNumConfigurations;
  uint8_t  Reseverd;
}USB_device_qualifier __ALIGN_END;



__ALIGN_BEGIN typedef struct USB_interface_descriptor
 {
 uint8_t   bLength;
 uint8_t   bDescriptorType;  
 uint8_t   bInterfaceNumber;
 uint8_t   bAlternateSetting;
 uint8_t   bNumEndpoints;
 uint8_t   bInterfaceClass;
 uint8_t   bInterfaceSubclass; 
 uint8_t   bInterfaceProtocol;
 uint8_t   iInterface;
 } USB_interface_descriptor __ALIGN_END;


__ALIGN_BEGIN typedef struct  USB_configuration_descriptor
{
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint16_t  wTotalLength;
  uint8_t bNumInterfaces;
  uint8_t bConfigurationValue;
  uint8_t iConfiguration;
  uint8_t  bmAttributes;
  uint8_t  bMaxPower;
  USB_interface_descriptor USB_interface_descriptors;
} USB_configuration_descriptor  __ALIGN_END;

//uint8_t* USB_MakeConfigurationDescriptor(
