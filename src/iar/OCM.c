#include "OCM.h"
#include "USB_Descriptors.h"
#include "USB_Stream.h"
#include "usbd_ioreq.h"
#include "usbd_req.h"
#include <stdlib.h>
#include <string.h>

uint8_t *OCM_Name = "Open Comunication Module";
uint8_t *OCM_Vendor_Name = "M0nteCarl0";
uint8_t *OCM_SerialNumber = "663399";
uint8_t *OCM_InterfaceName = "Mixed Bus protocol";
const uint16_t OCM_VID = 0x63;
const uint16_t OCM_PID = 0x5;
char *OCM_StringDescriptor;
int DataAvalible = 0;
uint8_t Descriptor[128];
uint8_t UnicodeStringDescriptorName[200];
uint8_t UnicodeStringDescriptorVendorName[200];
uint8_t UnicodeStringDescriptorSerialNumber[200];
uint8_t UnicodeStringDescriptorInterfaceName[200];
uint16_t RxCount = 0;
uint16_t BytesRs;
USBD_Class_cb_TypeDef OCM_USBD_Class;
USBD_DEVICE OCM_USBD_DEVICE;
USBD_Usr_cb_TypeDef OCM_USBD_Usr_cb;
#if defined(__ICCARM__) /*!< IAR Compiler   ¬ключение выравyивани€ по машиному \
                           \ слову(32 бита)*/
#pragma data_alignment = 4
#endif
__ALIGN_BEGIN USB_OTG_CORE_HANDLE OCM_Handle __ALIGN_END;
USB_LangIDDescriptor OCM_USB_LangIDDescriptor;
__ALIGN_BEGIN USB_device_qualifier OCM_USB_device_qualifier __ALIGN_END;
__ALIGN_BEGIN USB_DeviceDescriptor OCM_USB_DeviceDescriptor __ALIGN_END;
__ALIGN_BEGIN USB_configuration_descriptor OCM_USB_configuration_descriptor
    __ALIGN_BEGIN;
__ALIGN_BEGIN uint8_t USBD_OCM_CfgDesc[32] __ALIGN_END = {

    0x09, /* bLength: Configuation Descriptor size */
    0x2,  /* bDescriptorType: Configuration */
    32,

    0x00,      0x01, /* bNumInterfaces: 1 interface */
    0x01,            /* bConfigurationValue: */
    0x04,            /* iConfiguration: */
    0x80,            /* bmAttributes: */
    0xFA,            /* MaxPower 100 mA */

    0x09, /* bLength: Interface Descriptor size */
    0x04, /* bDescriptorType: */
    0x00, /* bInterfaceNumber: Number of Interface */
    0x00, /* bAlternateSetting: Alternate setting */
    0x02, /* bNumEndpoints*/
    0xFF, /* bInterfaceClass: Vendor Specific */
    0xFF, /* bInterfaceSubClass : Vendor Specific */
    0xFF, /* nInterfaceProtocol */
    0x02, /* iInterface: */

    0x07,                  /*Endpoint descriptor length = 7*/
    0x05,                  /*Endpoint descriptor type */
    EP_ID_IN,              /*Endpoint address (IN, address 1) */
    0x02,                  /*Bulk endpoint type */
    64,        0,    0x00, /*Polling interval in milliseconds */

    0x07,                 /*Endpoint descriptor length = 7 */
    0x05,                 /*Endpoint descriptor type */
    EP_ID_OUT,            /*Endpoint address (OUT, address 1) */
    0x02,                 /*Bulk endpoint type */
    64,        0,    0x00 /*Polling interval in milliseconds*/
};

void OCM_DeviceInit(void) {}

void OCM_DeviceReset(uint8_t speed) {}

void OCM_DeviceConfigured(void) {}

void OCM_DeviceSuspended(void) {}

void OCM_DeviceResumed(void) {}

void OCM_DeviceConnected(void) {}

void OCM_DeviceDisconnected(void) {}

void OCM_DeviceInitLowLevel(void) { OCM_LowLevelInit(); }

uint8_t *OCM_GetDeviceDescriptor(uint8_t speed, uint16_t *length) {
  *length = sizeof(OCM_USB_DeviceDescriptor);
  return (uint8_t *)&OCM_USB_DeviceDescriptor;
}
uint8_t *OCM_GetLangIDStrDescriptor(uint8_t speed, uint16_t *length) {
  return (uint8_t *)&OCM_USB_LangIDDescriptor;
}

uint8_t *OCM_GetManufacturerStrDescriptor(uint8_t speed, uint16_t *length) {
  USBD_GetString(OCM_Vendor_Name, UnicodeStringDescriptorVendorName, length);
  return UnicodeStringDescriptorVendorName;
}

uint8_t *OCM_GetProductStrDescriptor(uint8_t speed, uint16_t *length) {
  USBD_GetString(OCM_Name, UnicodeStringDescriptorName, length);
  return UnicodeStringDescriptorName;
}

uint8_t *OCM_GetSerialStrDescriptor(uint8_t speed, uint16_t *length) {
  USBD_GetString(OCM_SerialNumber, UnicodeStringDescriptorSerialNumber, length);
  return UnicodeStringDescriptorSerialNumber;
}

uint8_t *OCM_GetConfigurationStrDescriptor(uint8_t speed, uint16_t *length) {
  USBD_GetString(OCM_SerialNumber, UnicodeStringDescriptorSerialNumber, length);
  return Descriptor;
}

uint8_t *OCM_GetInterfaceStrDescriptor(uint8_t speed, uint16_t *length) {
  USBD_GetString(OCM_InterfaceName, UnicodeStringDescriptorInterfaceName,
                 length);
  return UnicodeStringDescriptorInterfaceName;
}

uint8_t OCM_Init(void *pdev, uint8_t cfgidx) {
  OCM_DeInit(pdev, cfgidx);
  DCD_EP_Open(pdev, EP_ID_OUT, 64, USB_OTG_EP_BULK);
  DCD_EP_Open(pdev, EP_ID_IN, 64, USB_OTG_EP_BULK);
  DCD_EP_Flush(pdev, EP_ID_OUT);
  DCD_EP_Flush(pdev, EP_ID_IN);
  DCD_EP_PrepareRx(pdev, EP_ID_IN, USB_Stream_GetPointerBuffer(),
                   USB_Stream_GetMaxRxCount());
  return USBD_OK;
}

uint8_t OCM_DeInit(void *pdev, uint8_t cfgidx) {
  DCD_EP_Close(pdev, EP_ID_OUT);
  DCD_EP_Close(pdev, EP_ID_IN);
  return USBD_OK;
}

uint8_t OCM_Setup(void *pdev, USB_SETUP_REQ *req) {
  USB_OTG_CORE_HANDLE *Dev = (USB_OTG_CORE_HANDLE *)pdev;
  switch (req->bmRequest & USB_REQ_TYPE_MASK) {
  case USB_REQ_TYPE_VENDOR: {
    break;
  }
  };
  return USBD_OK;
}

uint8_t OCM_EP0_TxSent(void *pdev) { return USBD_OK; }

uint8_t OCM_EP0_RxReady(void *pdev) { return USBD_OK; }

uint8_t OCM_DataIn(void *pdev, uint8_t epnum) {
  if (USB_Stream_GetStateTxReady()) {
    DCD_EP_Flush(&OCM_Handle, EP_ID_IN);
    USB_Stream_ResetStateTxReady();
  }
  return USBD_OK;
}

uint8_t OCM_DataOut(void *pdev, uint8_t epnum) {
  uint32_t Received_DataSize =
      OCM_GetReceivedByteCountFromEndpont(pdev, EP_ID_OUT);
  USB_Stream_PutData(pdev, Received_DataSize);
  return USBD_OK;
}

uint8_t OCM_SOF(void *pdev) { return USBD_OK; }

uint8_t OCM_IsoINIncomplete(void *pdev) { return USBD_OK; }

uint8_t OCM_IsoOUTIncomplete(void *pdev) { return USBD_OK; }

uint8_t *OCM_GetConfigDescriptor(uint8_t speed, uint16_t *length) {
  *length = 32;
  return USBD_OCM_CfgDesc;
}

void OCM_LowLevelInit(void) {
  OCM_InitDescriptors();
  OCM_InitUSBD_Class();
  OCM_InitUSBD_DEVICE();
  OCM_InitUSBD_Usr_cb();
  USBD_Init(&OCM_Handle, USB_OTG_FS_CORE_ID, &OCM_USBD_DEVICE, &OCM_USBD_Class,
            &OCM_USBD_Usr_cb);
}

void OCM_InitDescriptors(void) {
  OCM_USB_DeviceDescriptor.bLength = 0x12;
  OCM_USB_DeviceDescriptor.bDescriptorType = 0x1;
  OCM_USB_DeviceDescriptor.bcdUSB = 0x200;
  OCM_USB_DeviceDescriptor.bDeviceClass = 0xFF;
  OCM_USB_DeviceDescriptor.bDeviceSubclass = 0xFF;
  OCM_USB_DeviceDescriptor.bDeviceProtocol = 0x1;
  OCM_USB_DeviceDescriptor.bMaxPacketSize0 = 0x40;
  OCM_USB_DeviceDescriptor.idProduct = OCM_PID;
  OCM_USB_DeviceDescriptor.idVendor = OCM_VID;
  OCM_USB_DeviceDescriptor.bcdDevice = 0x1;
  OCM_USB_DeviceDescriptor.iManufacturer = 0x1;
  OCM_USB_DeviceDescriptor.iProduct = 0x2;
  OCM_USB_DeviceDescriptor.iSerialNumber = 0x3;
  OCM_USB_DeviceDescriptor.bNumConfigurations = 0x1;

  OCM_USB_device_qualifier.bLength = 0xA;
  OCM_USB_device_qualifier.bcdUSB = 0x200;
  OCM_USB_device_qualifier.bDescriptorType = 0x6;
  OCM_USB_device_qualifier.bDeviceClass = 0xFF;
  OCM_USB_device_qualifier.bDeviceSubclass = 0xFF;
  OCM_USB_device_qualifier.bDeviceProtocol = 0x0;
  OCM_USB_device_qualifier.bMaxPacketSize0 = 0x40;
  OCM_USB_device_qualifier.bNumConfigurations = 0x1;
  OCM_USB_device_qualifier.Reseverd = 0x1;

  OCM_USB_LangIDDescriptor.bDescriptorType = 0x3;
  OCM_USB_LangIDDescriptor.bLength = sizeof(OCM_USB_LangIDDescriptor);
  OCM_USB_LangIDDescriptor.wLANGID = 0x409;
}

void OCM_InitUSBD_Class(void) {
  OCM_USBD_Class.Init = &OCM_Init;
  OCM_USBD_Class.Setup = &OCM_Setup;
  OCM_USBD_Class.DeInit = &OCM_DeInit;
  OCM_USBD_Class.GetConfigDescriptor = &OCM_GetConfigDescriptor;
  OCM_USBD_Class.EP0_RxReady = &OCM_EP0_RxReady;
  OCM_USBD_Class.EP0_TxSent = &OCM_EP0_TxSent;
  OCM_USBD_Class.DataIn = &OCM_DataIn;
  OCM_USBD_Class.DataOut = &OCM_DataOut;
}

void OCM_InitUSBD_DEVICE(void) {
  OCM_USBD_DEVICE.GetConfigurationStrDescriptor =
      &OCM_GetConfigurationStrDescriptor;
  OCM_USBD_DEVICE.GetDeviceDescriptor = &OCM_GetDeviceDescriptor;
  OCM_USBD_DEVICE.GetInterfaceStrDescriptor = &OCM_GetInterfaceStrDescriptor;
  OCM_USBD_DEVICE.GetLangIDStrDescriptor = &OCM_GetLangIDStrDescriptor;
  OCM_USBD_DEVICE.GetManufacturerStrDescriptor =
      &OCM_GetManufacturerStrDescriptor;
  OCM_USBD_DEVICE.GetProductStrDescriptor = &OCM_GetProductStrDescriptor;
  OCM_USBD_DEVICE.GetSerialStrDescriptor = &OCM_GetSerialStrDescriptor;
}

void OCM_InitUSBD_Usr_cb(void) {
  OCM_USBD_Usr_cb.DeviceConfigured = &OCM_DeviceConfigured;
  OCM_USBD_Usr_cb.DeviceConnected = &OCM_DeviceConnected;
  OCM_USBD_Usr_cb.DeviceDisconnected = &OCM_DeviceDisconnected;
  OCM_USBD_Usr_cb.DeviceReset = &OCM_DeviceReset;
  OCM_USBD_Usr_cb.DeviceResumed = &OCM_DeviceResumed;
  OCM_USBD_Usr_cb.DeviceSuspended = &OCM_DeviceSuspended;
  OCM_USBD_Usr_cb.Init = &OCM_DeviceInit;
}

void OTG_FS_IRQHandler(void) { USBD_OTG_ISR_Handler(&OCM_Handle); }

void OCM_MemCopy(uint8_t *Source, uint8_t *Destination, uint16_t Size) {
  for (uint16_t i = 0; i < Size; i++) {
    Destination[i] = Source[i];
  }
}

uint16_t OCM_GetReceivedByteCountFromEndpont(USB_OTG_CORE_HANDLE *pdev,
                                             uint8_t epnum) {
  return pdev->dev.out_ep[epnum].xfer_count;
}

void OCM_SendBulk(uint8_t *Buffer, uint16_t N) {
  DCD_EP_Tx(&OCM_Handle, EP_ID_IN, Buffer, N);
}
