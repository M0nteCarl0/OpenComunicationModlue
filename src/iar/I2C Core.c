#include "I2C Core.h"
/******************************************************************************/
void I2C_Core_Init(void)
{
  I2C_Core_ClockInit();
  I2C_Core_GPIOInit();
  I2C_InitTypeDef I2C_Ini;
  I2C_StructInit(&I2C_Ini);
  I2C_Ini.I2C_Ack =I2C_Ack_Enable;
  I2C_Ini.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_Ini.I2C_ClockSpeed = 100000;
  I2C_Ini.I2C_DutyCycle =I2C_DutyCycle_2;
  I2C_Ini.I2C_Mode = I2C_Mode_I2C;
  I2C_Ini.I2C_OwnAddress1 = 0x1;
  I2C_Init(I2C1,&I2C_Ini);
  I2C_Cmd(I2C1,ENABLE);
  
  
}
/******************************************************************************/
void I2C_Core_GPIOInit(void)
{
#if 0
   GPIO_PinAFConfig(GPIOC, GPIO_PinSource9,GPIO_AF_I2C3);
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource8,GPIO_AF_I2C3);
   GPIO_InitTypeDef IICGpio;
   
   GPIO_StructInit(&IICGpio);
   IICGpio.GPIO_Mode  =GPIO_Mode_AF;
   IICGpio.GPIO_Pin = GPIO_Pin_8;
   IICGpio.GPIO_OType = GPIO_OType_OD;
   GPIO_Init(GPIOA,&IICGpio);
   
   IICGpio.GPIO_Pin = GPIO_Pin_9;
   GPIO_Init(GPIOC,&IICGpio);
#endif
   
   GPIO_PinAFConfig(GPIOB, GPIO_PinSource6,GPIO_AF_I2C1);
   GPIO_PinAFConfig(GPIOB, GPIO_PinSource9,GPIO_AF_I2C1);
   GPIO_InitTypeDef IICGpio;
   
   GPIO_StructInit(&IICGpio);
   IICGpio.GPIO_Mode  =GPIO_Mode_AF;
   IICGpio.GPIO_Pin = GPIO_Pin_9;
   IICGpio.GPIO_OType = GPIO_OType_OD;
   GPIO_Init(GPIOB,&IICGpio);
   
   IICGpio.GPIO_Pin = GPIO_Pin_6;
   GPIO_Init(GPIOB,&IICGpio);
   
}
/******************************************************************************/
void I2C_Core_ClockInit(void)
{
#if 0
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C3,ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
#endif
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
    
}
/******************************************************************************/
void I2C_Core_WriteToDevice(uint8_t Adress,uint8_t RegisterAdress,uint8_t* Data,uint16_t Count)
{
  __disable_irq();
  while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));{};
  I2C_GenerateSTART(I2C1,ENABLE);
  while(!I2C_CheckEvent(I2C1 ,I2C_EVENT_MASTER_MODE_SELECT));{};
  I2C_Send7bitAddress(I2C1,Adress<<1,I2C_Direction_Transmitter);
 
  while(!I2C_CheckEvent(I2C1 ,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));{};
  if(RegisterAdress!=255)
  { 
  I2C_SendData(I2C1,RegisterAdress);
  while(!I2C_GetFlagStatus(I2C1,I2C_FLAG_BTF));{};
  }
  if(  Count!=0)
  {
    for(uint16_t i = 0;i<Count;i++)
    {
     while(!I2C_GetFlagStatus(I2C1,I2C_FLAG_TXE));{};    
     I2C_SendData(I2C1,Data[i]);
     while(!I2C_GetFlagStatus(I2C1,I2C_FLAG_BTF));{};  
    }
  }
  
  I2C_GenerateSTOP(I2C1,ENABLE);
  while(I2C_GetFlagStatus(I2C1,I2C_FLAG_STOPF));{};
  __enable_irq();
  
}
/******************************************************************************/
void I2C_Core_ReadFromDevice(uint8_t Adress,uint8_t RegisterAdress,uint8_t* Data,uint16_t Count)
{
  
  I2C_Core_WriteToDevice(Adress,RegisterAdress,Data,0);
   __disable_irq();
    while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));{};
   I2C_GenerateSTART(I2C1,ENABLE);
    while(!I2C_CheckEvent(I2C1 ,I2C_EVENT_MASTER_MODE_SELECT));{}; 
   I2C_Send7bitAddress(I2C1,Adress<<1,I2C_Direction_Receiver);
   while(!I2C_CheckEvent(I2C1 ,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));{};
   while(!I2C_GetFlagStatus(I2C1 ,I2C_FLAG_BTF));{}; 
   I2C_GenerateSTOP(I2C1,ENABLE);
   I2C_AcknowledgeConfig(I2C1,DISABLE);
   I2C_NACKPositionConfig( I2C1,I2C_NACKPosition_Next);
  for(uint16_t i = 0;i<Count;i++)
  {
   while(I2C_GetFlagStatus(I2C1 ,I2C_FLAG_RXNE) == RESET);{};
   Data[i] = I2C_ReceiveData(I2C1);
   I2C_NACKPositionConfig( I2C1,I2C_NACKPosition_Next);
  
  }
   I2C_NACKPositionConfig( I2C1,I2C_NACKPosition_Current);
   I2C_AcknowledgeConfig(I2C1,ENABLE);
   I2C_GenerateSTOP(I2C1,ENABLE);
   while(I2C_GetFlagStatus(I2C1,I2C_FLAG_STOPF));{};
    __enable_irq();
  
}
/******************************************************************************/
void I2C_Core_ReadFromDeviceACK(uint8_t Adress,uint8_t RegisterAdress,uint8_t* Data,uint16_t Count)
{
   I2C_Core_WriteToDevice(Adress,RegisterAdress,Data,0);
   __disable_irq();
   while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));{};
   I2C_GenerateSTART(I2C1,ENABLE);
   while(!I2C_CheckEvent(I2C1 ,I2C_EVENT_MASTER_MODE_SELECT));{}; 
   I2C_Send7bitAddress(I2C1,Adress<<1,I2C_Direction_Receiver);
   while(!I2C_CheckEvent(I2C1 ,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));{};
   while(!I2C_GetFlagStatus(I2C1 ,I2C_FLAG_BTF));{}; 
   I2C_GenerateSTOP(I2C1,ENABLE);
  for(uint16_t i = 0;i<Count;i++)
  {
   while(I2C_GetFlagStatus(I2C1 ,I2C_FLAG_RXNE) == RESET);{};
   Data[i] = I2C_ReceiveData(I2C1);
  }
   I2C_GenerateSTOP(I2C1,ENABLE);
   while(I2C_GetFlagStatus(I2C1,I2C_FLAG_STOPF));{};
    __enable_irq();
  
  
  
}
