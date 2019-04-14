#include "DDC12_Core.h"
#include "ALTERA_Control.h"
//#include "LED.h"
DDC112_InitStructure DDC1;
DDC112_InitStructure DDC2;
ALTERA_InitStructure ALTERA;

DDC112_CHANNEL_ID ChanellID;

uint32_t SamplesADC0A_Chanel0[100];
uint32_t SamplesADC0A_Chanel1[100];
uint32_t SamplesADC0B_Chanel0[100];
uint32_t SamplesADC0B_Chanel1[100];


uint32_t SamplesADC1A_Chanel0[100];
uint32_t SamplesADC1A_Chanel1[100];
uint32_t SamplesADC1B_Chanel0[100];
uint32_t SamplesADC1B_Chanel1[100];




int DataReady = 0;
int StartIntegrationADC0;
int StartIntegrationADC1;
int IntegratorItADC0;
int IntegratorItADC1;

/*****************************************************************************/
void DDC12_Core_Init(void)
{
  

  //ADC1
  DDC1.IO_PORT_RANGE = GPIOA;
  DDC1.IO_PORT_DCLK =  GPIOC;
  DDC1.IO_PORT_DOUT = GPIOA;
  DDC1.IO_PORT_DVALID = GPIOB;
  DDC1.IO_PORT_DMIT = GPIOB;
  DDC1.IO_PORT_TEST = GPIOA ;
  DDC1.IO_PORT_CONV = GPIOC ;
  
  
  DDC1.GPIO_Pin_RANGE0 = DDC112_IO_PINS_RANGE_RANGE0_ADC0;
  DDC1.GPIO_Pin_RANGE1 = DDC112_IO_PINS_RANGE_RANGE1_ADC0;
  DDC1.GPIO_Pin_RANGE2 = DDC112_IO_PINS_RANGE_RANGE2_ADC0;
  
  DDC1.GPIO_Pin_DCLK =    DDC112_IO_PINS_DCLK_ADC0;
  DDC1.GPIO_Pin_DOUT =    DDC112_IO_PINS_DOUT_ADC0 ;
  DDC1.GPIO_Pin_DVALID =  DDC112_IO_PINS_DVALID_ADC0;
  DDC1.GPIO_Pin_DMIT =    DDC112_IO_PINS_DXMIT_ADC0;
  DDC1.GPIO_Pin_TEST =    DDC112_IO_PINS_TEST_ADC0;
  DDC1.GPIO_Pin_CONV =    DDC112_IO_PINS_CONV_ADC0_1;
  
  
///ADC2
  DDC2.IO_PORT_RANGE = GPIOB;
  DDC2.IO_PORT_DCLK =  GPIOC;
  DDC2.IO_PORT_DOUT = GPIOC;
  DDC2.IO_PORT_DVALID = GPIOC;
  DDC2.IO_PORT_DMIT = GPIOC;
  DDC2.IO_PORT_TEST = GPIOA ;
  DDC2.IO_PORT_CONV = GPIOC ;
  
  
  DDC2.GPIO_Pin_RANGE0 = DDC112_IO_PINS_RANGE_RANGE0_ADC1;
  DDC2.GPIO_Pin_RANGE1 = DDC112_IO_PINS_RANGE_RANGE1_ADC1;
  DDC2.GPIO_Pin_RANGE2 = DDC112_IO_PINS_RANGE_RANGE2_ADC1;
  
  DDC2.GPIO_Pin_DCLK =    DDC112_IO_PINS_DCLK_ADC1;
  DDC2.GPIO_Pin_DOUT =    DDC112_IO_PINS_DOUT_ADC1 ;
  DDC2.GPIO_Pin_DVALID =  DDC112_IO_PINS_DVALID_ADC1;
  DDC2.GPIO_Pin_DMIT =    DDC112_IO_PINS_DXMIT_ADC1;
  DDC2.GPIO_Pin_TEST =    DDC112_IO_PINS_TEST_ADC1;
  DDC2.GPIO_Pin_CONV =    DDC112_IO_PINS_CONV_ADC0_1;


  
  ALTERA.IO_PIN_ALTERA_RSVD0 = GPIO_Pin_0;
  ALTERA.IO_PIN_ALTERA_RSVD1 = GPIO_Pin_1;
  ALTERA.IO_PIN_ALTERA_SR0 = GPIO_Pin_7;
  ALTERA.IO_PIN_ALTERA_SR1 = GPIO_Pin_8;
  ALTERA.IO_PIN_ALTERA_START_CONV = GPIO_Pin_1;
         
  ALTERA.IO_PORT_ALTERA_RSVD0 = GPIOC;
  ALTERA.IO_PORT_ALTERA_RSVD1 = GPIOC;
  ALTERA.IO_PORT_ALTERA_SR0 = GPIOB;
  ALTERA.IO_PORT_ALTERA_SR1 = GPIOB;
  ALTERA.IO_PORT_ALTERA_START_CONV = GPIOB;
  
  DDC112_Init(&DDC1);
  DDC112_Init(&DDC2);
  
  
  //Power Up sequnce 
  DDC112_SetRange(&DDC1,RANGE_VALUE_MAX_CAPACITY); // LOW
  DDC112_SetRange(&DDC2,RANGE_VALUE_MAX_CAPACITY); // LOW

   RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
   EXTI_InitTypeDef _EXTIPINs;
   NVIC_InitTypeDef _EXTIIRQ;
   
   //SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource13);//CONV Signal
   SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB,EXTI_PinSource10);//DVALId ADC0 signal1
   SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource6);//DVALId ADC1 signal1
   
   //Conv Input Signal
  _EXTIPINs.EXTI_Mode                         =  EXTI_Mode_Interrupt;  
  _EXTIPINs.EXTI_Line                         =  EXTI_Line13;//Reference
  _EXTIPINs.EXTI_Trigger                      =  EXTI_Trigger_Rising_Falling;
  _EXTIPINs.EXTI_LineCmd                      =  ENABLE;
  // EXTI_Init(&_EXTIPINs);              

   //DVALID Input Signal ADC0
  _EXTIPINs.EXTI_Mode                         =  EXTI_Mode_Interrupt;  
  _EXTIPINs.EXTI_Line                         =  EXTI_Line10;// 
  _EXTIPINs.EXTI_Trigger                      =  EXTI_Trigger_Falling; 
  _EXTIPINs.EXTI_LineCmd                      =  ENABLE; 
   EXTI_Init(&_EXTIPINs); 
 
   
   //DVALID Input Signal ADC1
  _EXTIPINs.EXTI_Mode                         =  EXTI_Mode_Interrupt;  
  _EXTIPINs.EXTI_Line                         =  EXTI_Line6;// 
  _EXTIPINs.EXTI_Trigger                      =  EXTI_Trigger_Falling; 
  _EXTIPINs.EXTI_LineCmd                      =  ENABLE; 
   EXTI_Init(&_EXTIPINs); 
 
 /*************************************************************************/
  _EXTIIRQ.NVIC_IRQChannel                    = EXTI9_5_IRQn;
  _EXTIIRQ.NVIC_IRQChannelCmd                 = ENABLE;
  _EXTIIRQ.NVIC_IRQChannelPreemptionPriority  = 1;
  _EXTIIRQ.NVIC_IRQChannelSubPriority         = 1;
   NVIC_Init(&_EXTIIRQ);


  _EXTIIRQ.NVIC_IRQChannel                    = EXTI15_10_IRQn;
  _EXTIIRQ.NVIC_IRQChannelCmd                 = ENABLE;
  _EXTIIRQ.NVIC_IRQChannelPreemptionPriority  = 1;
  _EXTIIRQ.NVIC_IRQChannelSubPriority         = 1;
   NVIC_Init(&_EXTIIRQ); 

  ALTERA_Control_Init(&ALTERA);
  ALTERA_Control_SelectRange(&ALTERA,ALTERA_Control_Range_500us);
for(int i = 0;i<100;i++)
{
  
  
  
  
  
  
  SamplesADC0A_Chanel0[i] = 255;
  SamplesADC0A_Chanel1[i] = 128;
  SamplesADC0B_Chanel0[i] = 64;
  SamplesADC0B_Chanel1[i] = 1024;
  
  
  SamplesADC1A_Chanel0[i] = 12000;
  SamplesADC1A_Chanel1[i] = 6000;
  SamplesADC1B_Chanel0[i] = 3000;
  SamplesADC1B_Chanel1[i] = 1500;
  
  
}
  
  
  
     
}
/*****************************************************************************/
DDC112_CHANNEL_ID DDC12_Core_GetChannellID(void)
{
  return ChanellID ;
}
/*****************************************************************************/
void DDC12_Core_StartIntegration(void)
{ 
  __disable_interrupt();
  StartIntegrationADC0  = 1;
  StartIntegrationADC1  = 1;
  IntegratorItADC0      = 0;
  IntegratorItADC1      = 0;
  __enable_interrupt();
  
}
/*****************************************************************************/
void DDC12_Core_StopIntegration(void)
{
  
 __disable_interrupt();
  StartIntegrationADC0  = 0;
  StartIntegrationADC1  = 0;
 __enable_interrupt(); 
    
}
/*****************************************************************************/
void DDC12_Core_AlteraSetRange(uint8_t Range)
{
   ALTERA_Control_SelectRange(&ALTERA,(ALTERA_Control_Range)Range); 
}
/*****************************************************************************/
uint8_t DDC12_Core_AlteraGetRange(void)
{
  return (uint8_t)ALTERA_Control_GetRange(&ALTERA);
}
/*****************************************************************************/
void DDC12_Core_ADC0SetRange(uint8_t Range)
{
  DDC112_SetRange(&DDC1,(RANGE_VALUE)Range);
}
/*****************************************************************************/
uint8_t DDC12_Core_ADC0GetRange(void)
{
  return (uint8_t)DDC112_GetRange(&DDC1);
}
/*****************************************************************************/
void DDC12_Core_ADC1SetRange(uint8_t Range)
{
   DDC112_SetRange(&DDC2,(RANGE_VALUE)Range);
}
/*****************************************************************************/
uint8_t DDC12_Core_ADC1GetRange(void)
{
   return (uint8_t)  DDC112_GetRange(&DDC2);
}
/*****************************************************************************/
void EXTI15_10_IRQHandler(void)
{
  
   if(EXTI_GetITStatus(EXTI_Line10))// DVALID0 0 Ok
  {
      ChanellID = DDC112_GetCurrentChannelID(&DDC1);
      DDC112_ReadSample(&DDC1,ChanellID);
      if(StartIntegrationADC0)
      {
#if 0          
          SamplesADC0A_Chanel0[IntegratorItADC0] = DDC1.ResultChannel1A.Channel_1;
          SamplesADC0A_Chanel1[IntegratorItADC0] = DDC1.ResultChannel1A.Channel_2;
  
          SamplesADC0B_Chanel0[IntegratorItADC0] = DDC1.ResultChannellB.Channel_1;
          SamplesADC0B_Chanel1[IntegratorItADC0] = DDC1.ResultChannellB.Channel_2;
       
          IntegratorItADC0++;
          if(IntegratorItADC0 == 100)
          {
            StartIntegrationADC0 = 0;
          }
#endif            
        }
        EXTI_ClearITPendingBit(EXTI_Line10); 
      }
    
  if(EXTI_GetITStatus(EXTI_Line13))//Conv OK
   {
      ChanellID = DDC112_GetCurrentChannelID(&DDC1);
      EXTI_ClearITPendingBit(EXTI_Line13); 
   }
}
/***
**************************************************************************/
void EXTI9_5_IRQHandler(void)//Conv_DVALID
{
  if(EXTI_GetITStatus(EXTI_Line6))
  {
      ChanellID = DDC112_GetCurrentChannelID(&DDC1);
      DDC112_ReadSample(&DDC2,ChanellID); 
      if(StartIntegrationADC1)
      {
        
#if 0       
          SamplesADC1A_Chanel0[IntegratorItADC1] = DDC2.ResultChannel1A.Channel_1;
          SamplesADC1A_Chanel1[IntegratorItADC1] = DDC2.ResultChannel1A.Channel_2;
          SamplesADC1B_Chanel0[IntegratorItADC1] = DDC2.ResultChannellB.Channel_1; 
          SamplesADC1B_Chanel1[IntegratorItADC1] = DDC2.ResultChannellB.Channel_2;           
          IntegratorItADC1++;
          
        if(IntegratorItADC1 == 100)
          {
            StartIntegrationADC1 = 0;
          }
  #endif     
                           
      }
      
      EXTI_ClearITPendingBit(EXTI_Line6); //DVALID ADC1
   }
}

/**************************************************************************/
uint32_t* DDC12_Core_GetSamplesADC0A_Chanel0(void)
{
  return  SamplesADC0A_Chanel0;
}
/**************************************************************************/
uint32_t* DDC12_Core_GeSamplesADC0A_Chanel1(void)
{
  return  SamplesADC0A_Chanel1;
}
/**************************************************************************/
uint32_t* DDC12_Core_GeSamplesADC0B_Chanel0(void)
{
  return  SamplesADC0B_Chanel0;
}
/**************************************************************************/
uint32_t* DDC12_Core_GeSamplesADC0B_Chanel1(void)
{
  return  SamplesADC0B_Chanel1;
}
/**************************************************************************/
uint32_t* DDC12_Core_GeSamplesADC1A_Chanel0(void)
{
  return  SamplesADC1A_Chanel0;
}
/**************************************************************************/
uint32_t* DDC12_Core_GeSamplesADC1A_Chanel1(void)
{
  return  SamplesADC1A_Chanel1;
}
/**************************************************************************/
uint32_t* DDC12_Core_GeSamplesADC1B_Chanel0(void)
{
  return  SamplesADC1B_Chanel0;
}
/**************************************************************************/
uint32_t* DDC12_Core_GeSamplesADC1B_Chanel1(void)
{
  return  SamplesADC1B_Chanel1;
}
/**************************************************************************/
void DDC12_Core_EnableTestMode(void)
{
  DDC112_EnableTestMode(&DDC1);
  DDC112_EnableTestMode(&DDC2); 
}
/**************************************************************************/
void DDC12_Core_DisableTestMode(void)
{
  DDC112_DisableTestMode(&DDC1);
  DDC112_DisableTestMode(&DDC2);
}
/**************************************************************************/
