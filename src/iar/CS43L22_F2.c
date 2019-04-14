#include "CS43L22_F2.h"
#include "I2C Core.h"
#include "Timer.h"
void CS43L22_F2_InitAudiodac(void)
{

      GPIO_InitTypeDef GPIO_InitStructure;
      SPI_InitTypeDef  SPI_InitStructure;
  
    /* Enable GPIO clocks */
    //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  // RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
 
    /* SPI GPIO Configuration --------------------------------------------------*/
    /* Connect SPI pins to AF5 */  
    //GPIO_PinAFConfig(GPIOB, GPIO_PinSource6,GPIO_AF_I2C1);
    //GPIO_PinAFConfig(GPIOB, GPIO_PinSource9,GPIO_AF_I2C1);

  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOD,GPIO_Pin_9);
    
    Timer_WaitMilisec(1);
    GPIO_SetBits(GPIOD,GPIO_Pin_9);
 
  uint8_t PowerControl  = 0x1;  
  I2C_Core_WriteToDevice(0x4A,0x2,&PowerControl,1);
 //I2C_Core_ReadFromDeviceACK(0x4A,0x2,&PowerControl,1);
    
    
  
  
}


uint8_t CS43L22_F2_ReadPowerControl(void)
{
  uint8_t PowerControl = 0;
  I2C_Core_ReadFromDeviceACK(0x4A,0x2,&PowerControl,1);
  return  PowerControl;
  
};