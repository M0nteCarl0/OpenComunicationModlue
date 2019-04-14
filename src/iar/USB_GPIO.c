#include "USB_GPIO.h"

void USB_GPIO_Init(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
  GPIO_DeInit(GPIOA);
  USB_GPIO_DA_Init();
  USB_GPIO_DA_VBUS_Init();  
}
/**************************************************************************/
void  USB_GPIO_DA_Init(void)
{
  GPIO_InitTypeDef USB_GPIO;
    /*
  Настройка ножек приема-передачи  
  */
  
  USB_GPIO.GPIO_Mode  = GPIO_Mode_AF;
  USB_GPIO.GPIO_Pin   = USB_GPIO_ID_DP|
                        USB_GPIO_ID_DM;
     
  USB_GPIO.GPIO_OType = GPIO_OType_PP;
  USB_GPIO.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  USB_GPIO.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOA,&USB_GPIO);  
  
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_OTG_FS);
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource12,GPIO_AF_OTG_FS);
  
}
/**************************************************************************/
void  USB_GPIO_DA_VBUS_Init(void)
{
 GPIO_InitTypeDef USB_GPIO;  
    /*
  Настройка ножки детектирования подключения устройства  
  */
  USB_GPIO.GPIO_Mode  = GPIO_Mode_IN;
  USB_GPIO.GPIO_Pin   = USB_GPIO_ID_VBUS;
  USB_GPIO.GPIO_OType = GPIO_OType_OD;
  USB_GPIO.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  USB_GPIO.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOA,&USB_GPIO); 

 GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_OTG_FS);
}
/**************************************************************************/