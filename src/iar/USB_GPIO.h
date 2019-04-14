#include "stm32f4xx.h"
#ifndef _USB_GPIO_
#define _USB_GPIO_
enum   USB_GPIO_ID
{
  USB_GPIO_ID_DP    = GPIO_Pin_12,
  USB_GPIO_ID_DM    = GPIO_Pin_11,
  USB_GPIO_ID_VBUS  = GPIO_Pin_9,   
};
void  USB_GPIO_Init(void);
void  USB_GPIO_DA_Init(void);
void  USB_GPIO_DA_VBUS_Init(void);
#endif