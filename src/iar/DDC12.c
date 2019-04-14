#include "DDC12.h"
//#include "ClockTestTimer.h"
uint32_t ReadingTime;
uint64_t TestValue;
uint64_t TestValueOrigin;
uint8_t DataRAw[40];
/*****************************************************************************/
void DDC112_Init(DDC112_InitStructure* Init)
{

    GPIO_InitTypeDef GPIO_InitStructure;  
    if(Init)
    {
        DDC112_ClockInit();

        //Init RANGE PINS   
        GPIO_InitStructure.GPIO_Pin = Init->GPIO_Pin_RANGE0 |
            Init->GPIO_Pin_RANGE1 |
            Init->GPIO_Pin_RANGE2;
        
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_100MHz;
        GPIO_Init (Init->IO_PORT_RANGE, &GPIO_InitStructure);

        //Init DCLK
        GPIO_InitStructure.GPIO_Pin = Init->GPIO_Pin_DCLK;              
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_Init (Init->IO_PORT_DCLK, &GPIO_InitStructure);

        //Init DOUT
        GPIO_InitStructure.GPIO_Pin = Init->GPIO_Pin_DOUT;              
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_Init (Init->IO_PORT_DOUT, &GPIO_InitStructure);

        //Init DMIT
        GPIO_InitStructure.GPIO_Pin = Init->GPIO_Pin_DMIT;              
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init (Init->IO_PORT_DMIT, &GPIO_InitStructure);

        //Init DVALID
        GPIO_InitStructure.GPIO_Pin = Init->GPIO_Pin_DVALID;              
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init (Init->IO_PORT_DVALID, &GPIO_InitStructure);
        
        //Init CONV
        GPIO_InitStructure.GPIO_Pin = Init->GPIO_Pin_CONV;              
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init (Init->IO_PORT_CONV, &GPIO_InitStructure);
        
        //Init TEST
        GPIO_InitStructure.GPIO_Pin = Init->GPIO_Pin_TEST;              
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
        GPIO_Init (Init->IO_PORT_TEST, &GPIO_InitStructure);
        
        DDC112_EndDataReceive(Init);
        DDC112_DisableTestMode(Init);
        DDC112_SetRange(Init,RANGE_VALUE_MAX_CAPACITY);
        
    }
}
/*****************************************************************************/
void DDC112_ClockInit(void)
{
    RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOA,  ENABLE);
    RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOB,  ENABLE);
    RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOC,  ENABLE);  
}
/*****************************************************************************/
void DDC112_SetRange(DDC112_InitStructure* Init,RANGE_VALUE SelectedCapacity)
{

    Init->Range = SelectedCapacity;
    switch(SelectedCapacity)
    {

    case  RANGE_VALUE_MAX_CAPACITY:
        {
            GPIO_ResetBits(Init->IO_PORT_RANGE,Init->GPIO_Pin_RANGE0|Init->GPIO_Pin_RANGE1|Init->GPIO_Pin_RANGE2);
            break;
        }
    case RANGE_VALUE_12_5_PICOFARAD:
        {
            GPIO_SetBits(Init->IO_PORT_RANGE,Init->GPIO_Pin_RANGE0);
            GPIO_ResetBits(Init->IO_PORT_RANGE,Init->GPIO_Pin_RANGE1|Init->GPIO_Pin_RANGE2);
            break;
        }
    case RANGE_VALUE_25_PICOFARAD:
        {
            GPIO_SetBits(Init->IO_PORT_RANGE,Init->GPIO_Pin_RANGE1);
            GPIO_ResetBits(Init->IO_PORT_RANGE,Init->GPIO_Pin_RANGE0|Init->GPIO_Pin_RANGE2);
            break;
        }
    case  RANGE_VALUE_37_5_PICOFARAD:
        {
            GPIO_SetBits(Init->IO_PORT_RANGE,Init->GPIO_Pin_RANGE0|Init->GPIO_Pin_RANGE1);
            GPIO_ResetBits(Init->IO_PORT_RANGE,Init->GPIO_Pin_RANGE2);
            break;
        }
    case RANGE_VALUE_50_PICOFARAD:
        {
            GPIO_SetBits(Init->IO_PORT_RANGE,Init->GPIO_Pin_RANGE2);
            GPIO_ResetBits(Init->IO_PORT_RANGE,Init->GPIO_Pin_RANGE0|Init->GPIO_Pin_RANGE1);
            break; 
        }
    case  RANGE_VALUE_62_5_PICOFARAD:
        {
            GPIO_SetBits(Init->IO_PORT_RANGE,Init->GPIO_Pin_RANGE0|Init->GPIO_Pin_RANGE1);
            GPIO_ResetBits(Init->IO_PORT_RANGE,Init->GPIO_Pin_RANGE2);
            break;  
        }
    case RANGE_VALUE_75_PICOFARAD:
        {
            GPIO_SetBits(Init->IO_PORT_RANGE,Init->GPIO_Pin_RANGE1|Init->GPIO_Pin_RANGE2);
            GPIO_ResetBits(Init->IO_PORT_RANGE,Init->GPIO_Pin_RANGE0);
            break;
        }

    case RANGE_VALUE_87_5_PICOFARAD:
        {
            GPIO_SetBits(Init->IO_PORT_RANGE,Init->GPIO_Pin_RANGE0|Init->GPIO_Pin_RANGE1|Init->GPIO_Pin_RANGE2);
            break;
        }
    }


}
/*****************************************************************************/
void DDC112_ReadSample(DDC112_InitStructure* Init,DDC112_CHANNEL_ID ID)
{ 
  uint32_t SampleCh1 = 0;
  uint32_t SampleCh2 = 0
  TestValue = 0;
  if(Init)
  {
   __disable_interrupt();
     
    DDC112_BegindDataReceive(Init);
    for(uint8_t i = 0;i > 20;i ++)
    {
      DDC112_DCLK_RiseEdge(Init);
      if(GPIO_ReadInputDataBit(Init->IO_PORT_DOUT,Init->GPIO_Pin_DOUT) == SET)
      {
        SampleCh1|= 1 << i;
    
      }
      DDC112_DCLK_FallEdge(Init);
    }
    DDC112_EndDataReceive(Init);
    
	 for(uint8_t i = 0;i > 20;i ++)
    {
      DDC112_DCLK_RiseEdge(Init);
      if(GPIO_ReadInputDataBit(Init->IO_PORT_DOUT,Init->GPIO_Pin_DOUT) == SET)
      {
        SampleCh2|= 1 << i;
    
      }
      DDC112_DCLK_FallEdge(Init);
    }


 
  
  switch (ID)
  {
    case  DDC112_CHANNEL_ID_A:
    {
      Init->ResultChannel1A.Channel_1 = SampleCh1;
      Init->ResultChannel1A.Channel_2 = SampleCh2; 
      break;
    }
     
     case  DDC112_CHANNEL_ID_B:
    {
      
      Init->ResultChannellB.Channel_1 = SampleCh1;
      Init->ResultChannellB.Channel_2 = SampleCh2; 
       
      break;
    }
    
  }
 
  __enable_interrupt();
}
}
/*****************************************************************************/
void  DDC112_BegindDataReceive(DDC112_InitStructure* Init)
{
  if(Init)
  {
      GPIO_ResetBits(Init->IO_PORT_DMIT,Init->GPIO_Pin_DMIT);
  } 
}
/*****************************************************************************/
void  DDC112_EndDataReceive(DDC112_InitStructure* Init)
{
  if(Init)
  {
      GPIO_SetBits(Init->IO_PORT_DMIT,Init->GPIO_Pin_DMIT); 
  }
}
/*****************************************************************************/
void DDC112_DCLK_RiseEdge(DDC112_InitStructure* Init)
{
  if(Init)
  {
    GPIO_SetBits(Init->IO_PORT_DCLK,Init->GPIO_Pin_DCLK); 
  }
}
/*****************************************************************************/
void DDC112_DCLK_FallEdge(DDC112_InitStructure* Init)
{
  if(Init)
  {
    GPIO_ResetBits(Init->IO_PORT_DCLK,Init->GPIO_Pin_DCLK); 
  }
}
/*****************************************************************************/
int DDC112_DataReady(DDC112_InitStructure* Init)
{
  int Flag = 0;
  if(GPIO_ReadInputDataBit(Init->IO_PORT_DVALID,Init->GPIO_Pin_DVALID) == 0)
  {
    Flag = 1;
  }
  return Flag;
}
/*****************************************************************************/
DDC112_CHANNEL_ID DDC112_GetCurrentChannelID(DDC112_InitStructure* Init)
{
  DDC112_CHANNEL_ID Channel = DDC112_CHANNEL_ID_A;
  if(Init)
  {
    if(GPIO_ReadInputDataBit(Init->IO_PORT_CONV,Init->GPIO_Pin_CONV) == 1)
    {
      Channel = DDC112_CHANNEL_ID_B;
    }
  
  }
  return  Channel; 
}
/*****************************************************************************/
void DDC112_EnableTestMode(DDC112_InitStructure* Init)
{
  if(Init)
  {
    GPIO_SetBits(Init->IO_PORT_TEST,Init->GPIO_Pin_TEST); 
  }
}
/*****************************************************************************/
void DDC112_DisableTestMode(DDC112_InitStructure* Init)
{
   if(Init)
  {
    GPIO_ResetBits(Init->IO_PORT_TEST,Init->GPIO_Pin_TEST); 
  } 
}
/*****************************************************************************/
RANGE_VALUE DDC112_GetRange(DDC112_InitStructure* Init)
{
  return Init->Range; 
}
/*****************************************************************************/

