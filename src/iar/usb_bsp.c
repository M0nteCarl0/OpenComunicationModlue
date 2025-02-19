/**
 ******************************************************************************
 * @file    usb_bsp.c
 * @author  MCD Application Team
 * @version V2.1.0
 * @date    19-March-2012
 * @brief   This file is responsible to offer board support package and is
 *          configurable by user.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
 *
 * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *        http://www.st.com/software_license_agreement_liberty_v2
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "usb_bsp.h"
#include "Timer.h"
#include "USB_GPIO.h"
/** @addtogroup USB_OTG_DRIVER
 * @{
 */

/** @defgroup USB_BSP
 * @brief This file is responsible to offer board support package
 * @{
 */

/** @defgroup USB_BSP_Private_Defines
 * @{
 */
/**
 * @}
 */

/** @defgroup USB_BSP_Private_TypesDefinitions
 * @{
 */
/**
 * @}
 */

/** @defgroup USB_BSP_Private_Macros
 * @{
 */
/**
 * @}
 */

/** @defgroup USBH_BSP_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @defgroup USBH_BSP_Private_FunctionPrototypes
 * @{
 */
/**
 * @}
 */

/** @defgroup USB_BSP_Private_Functions
 * @{
 */

void BSP_Init(void) {}

void USB_OTG_BSP_Init(USB_OTG_CORE_HANDLE *pdev) {
  USB_GPIO_Init();
  USB_OTG_BSP_EnableInterrupt(pdev);
}

void USB_OTG_BSP_EnableInterrupt(USB_OTG_CORE_HANDLE *pdev) {
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  NVIC_InitTypeDef USB_FS_IRQ;
  USB_FS_IRQ.NVIC_IRQChannel = OTG_FS_IRQn;
  USB_FS_IRQ.NVIC_IRQChannelCmd = ENABLE;
  USB_FS_IRQ.NVIC_IRQChannelPreemptionPriority = 1;
  USB_FS_IRQ.NVIC_IRQChannelSubPriority = 3;
  NVIC_Init(&USB_FS_IRQ);
}

/**
 * @brief  BSP_Drive_VBUS
 *         Drives the Vbus signal through IO
 * @param  speed : Full, Low
 * @param  state : VBUS states
 * @retval None
 */

void USB_OTG_BSP_DriveVBUS(uint32_t speed, uint8_t state) {}

/**
 * @brief  USB_OTG_BSP_ConfigVBUS
 *         Configures the IO for the Vbus and OverCurrent
 * @param  Speed : Full, Low
 * @retval None
 */

void USB_OTG_BSP_ConfigVBUS(uint32_t speed) {}

/**
 * @brief  USB_OTG_BSP_TimeInit
 *         Initialises delay unit Systick timer /Timer2
 * @param  None
 * @retval None
 */
void USB_OTG_BSP_TimeInit(void) {}

/**
 * @brief  USB_OTG_BSP_uDelay
 *         This function provides delay time in micro sec
 * @param  usec : Value of delay required in micro sec
 * @retval None
 */
void USB_OTG_BSP_uDelay(const uint32_t usec) { Timer_WaitMicrosec(usec); }

/**
 * @brief  USB_OTG_BSP_mDelay
 *          This function provides delay time in milli sec
 * @param  msec : Value of delay required in milli sec
 * @retval None
 */
void USB_OTG_BSP_mDelay(const uint32_t msec) { Timer_WaitMilisec(msec); }

/**
 * @brief  USB_OTG_BSP_TimerIRQ
 *         Time base IRQ
 * @param  None
 * @retval None
 */

void USB_OTG_BSP_TimerIRQ(void) {}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
