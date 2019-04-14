#pragma once
#include "usb_core.h"
#include "usbd_core.h"
#include "usb_dcd_int.h"
#ifndef _OCM_CORE_
#define _OCM_CORE_
#ifdef __cplusplus
 extern "C" {
#endif 
/***************************************************************************/   
enum EP_ID//Конечные точки(PIPES в терминолгии Windows)
{
  EP_ID_IN  = 0x81,//В ПК(Ведущий всегда хост!!)
  EP_ID_OUT = 0x1, //Из ПК(Ведущий всегда хост!!)
};
/***************************************************************************/
  uint8_t*  OCM_GetDeviceDescriptor( uint8_t speed , uint16_t *length);  
  uint8_t*  OCM_GetLangIDStrDescriptor( uint8_t speed , uint16_t *length); 
  uint8_t*  OCM_GetManufacturerStrDescriptor( uint8_t speed , uint16_t *length);  
  uint8_t*  OCM_GetProductStrDescriptor( uint8_t speed , uint16_t *length);  
  uint8_t*  OCM_GetSerialStrDescriptor( uint8_t speed , uint16_t *length);  
  uint8_t*  OCM_GetConfigurationStrDescriptor( uint8_t speed , uint16_t *length);  
  uint8_t*  OCM_GetInterfaceStrDescriptor( uint8_t speed , uint16_t *length);   

  uint8_t  OCM_Init         (void *pdev , uint8_t cfgidx);
  uint8_t  OCM_DeInit       (void *pdev , uint8_t cfgidx);
 /* Control Endpoints*/
  uint8_t  OCM_Setup       (void *pdev , USB_SETUP_REQ  *req); //Прием пакетов  контрольной конечной в формате сообщения 
  uint8_t  OCM_EP0_TxSent   (void *pdev );                     //Событие успешной посылки байтовго буяера с контрольной конечной точки   
  uint8_t  OCM_EP0_RxReady  (void *pdev );                     //Событие успешного примема байтовго буяера  
  /* Class Specific Endpoints*/
  uint8_t  OCM_DataIn       (void *pdev , uint8_t epnum);     //Событие  передачи  байтовго буяера  с Bulk/Interupt/Isohor конечной точки в ПК
  uint8_t  OCM_DataOut      (void *pdev , uint8_t epnum);     //Событие  приема  байтовго буяера  с Bulk/Interupt/Isohor конечной точки из ПК
  uint8_t  OCM_SOF          (void *pdev);                     //Событие  начала фрейма пакета Interupt конечной точки из ПК
  uint8_t  OCM_IsoINIncomplete  (void *pdev);                 //Событие  незакончености передачи  Isohor конечной точки из ПК
  uint8_t  OCM_IsoOUTIncomplete  (void *pdev);                //Событие  незакончености приема  Isohor конечной точки с ПК

  uint8_t* OCM_GetConfigDescriptor( uint8_t speed , uint16_t *length);  //Событие  передачи описателя конфигурации устройства а ПК
#ifdef USB_OTG_HS_CORE 
  uint8_t* OCM_GetOtherConfigDescriptor( uint8_t speed , uint16_t *length);   
#endif

#ifdef USB_SUPPORT_USER_STRING_DESC 
  uint8_t*  OCM_GetUsrStrDescriptor( uint8_t speed ,uint8_t index,  uint16_t *length);   
#endif  
  
  void OCM_DeviceInit(void);
  void OCM_DeviceInitLowLevel(void);
  void OCM_DeviceReset(uint8_t speed); 
  void OCM_DeviceConfigured(void);
  void OCM_DeviceSuspended(void);
  void OCM_DeviceResumed(void);  
  void OCM_MemCopy(uint8_t* Source,uint8_t* Destination,uint16_t Size);
  void OCM_DeviceConnected(void);  
  void OCM_DeviceDisconnected(void);
  void OCM_InitDescriptors(void);
  void OCM_InitUSBD_Class(void);
  void OCM_InitUSBD_DEVICE(void);
  void OCM_InitUSBD_Usr_cb(void);
  void OCM_LowLevelInit(void);
  void OCM_SendBulk(uint8_t* Buffer,uint16_t N);
  void OCM_InfiniteLoop(void);
  uint16_t  OCM_GetReceivedByteCountFromEndpont(USB_OTG_CORE_HANDLE *pdev,
                                                            uint8_t epnum);
  void OTG_FS_IRQHandler(void); 
 
#ifdef __cplusplus
 }
#endif 
#endif
  