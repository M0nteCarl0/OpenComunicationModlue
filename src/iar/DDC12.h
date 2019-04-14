#include "stm32f4xx.h"
#ifndef _LDDC112_
#define _DDC112_
#ifdef __cplusplus
extern "C" {
#endif
  
enum DDC112_IO_PINS_RANGE
{
  DDC112_IO_PINS_RANGE_RANGE0_ADC0 = GPIO_Pin_2,
  DDC112_IO_PINS_RANGE_RANGE1_ADC0 = GPIO_Pin_3,
  DDC112_IO_PINS_RANGE_RANGE2_ADC0 = GPIO_Pin_4,
  
  DDC112_IO_PINS_RANGE_RANGE0_ADC1 = GPIO_Pin_12,
  DDC112_IO_PINS_RANGE_RANGE1_ADC1 = GPIO_Pin_13,
  DDC112_IO_PINS_RANGE_RANGE2_ADC1 = GPIO_Pin_14,
  
  
};



enum DDC112_IO_PINS_CONV
{
  DDC112_IO_PINS_CONV_ADC0_1 = GPIO_Pin_13,
  
};



 enum DDC112_IO_PINS_DCLK
{
  DDC112_IO_PINS_DCLK_ADC0 = GPIO_Pin_4,
  DDC112_IO_PINS_DCLK_ADC1 = GPIO_Pin_10,
  
};

enum DDC112_IO_PINS_DXMIT
{
  DDC112_IO_PINS_DXMIT_ADC0 = GPIO_Pin_11,
  DDC112_IO_PINS_DXMIT_ADC1 = GPIO_Pin_7,
};

enum DDC112_IO_PINS_DVALID
{
  DDC112_IO_PINS_DVALID_ADC0 = GPIO_Pin_10,
  DDC112_IO_PINS_DVALID_ADC1 = GPIO_Pin_6,
  
};

enum DDC112_IO_PINS_DOUT
{
  
  DDC112_IO_PINS_DOUT_ADC0 = GPIO_Pin_1,
  DDC112_IO_PINS_DOUT_ADC1 = GPIO_Pin_12,
  
};

enum DDC112_IO_PINS_TEST
{
  DDC112_IO_PINS_TEST_ADC0 = GPIO_Pin_5,
  DDC112_IO_PINS_TEST_ADC1 = GPIO_Pin_8,
  
  
};

 typedef enum  RANGE_VALUE
{
  
  RANGE_VALUE_MAX_CAPACITY = 0,
  RANGE_VALUE_12_5_PICOFARAD,
  RANGE_VALUE_25_PICOFARAD,
  RANGE_VALUE_37_5_PICOFARAD,
  RANGE_VALUE_50_PICOFARAD,
  RANGE_VALUE_62_5_PICOFARAD,
  RANGE_VALUE_75_PICOFARAD,
  RANGE_VALUE_87_5_PICOFARAD,
}RANGE_VALUE;

typedef  struct ConversionResult
{
  
  uint32_t Channel_1;
  uint32_t Channel_2;
  
}ConversionResult;

/*
#if 0
enum DDC112_IO_PORTS_TEST
{
  DDC112_IO_PORTS_TEST_ADC0_1 = GPIOA,
  
};
enum DDC112_IO_PORTS_DCLK
{
  DDC112_IO_PORTS_DCLK_ADC0_1 =  GPIOC,
};

enum DDC112_IO_PORTS_DOUT
{
  DDC112_IO_PORTS_DOUT_ADC0 = GPIOA,
  DDC112_IO_PORTS_DOUT_ADC1 = GPIOC,
  
  
};
 
enum DDC112_IO_PORTS_DVALID
{
  DDC112_IO_PORTS_DVALID_ADC0 = GPIOB,
  DDC112_IO_PORTS_DVALID_ADC1 = GPIOC,
  
  
};
 
enum DDC112_IO_PORTS_DXMIT
{
   DDC112_IO_PORTS_DXMIT_ADC0  = GPIOB,
   DDC112_IO_PORTS_DXMIT_ADC1  = GPIOC,
  
  
};
  


typedef  enum DDC112_IO_PORTS_RANGE
{
  DDC112_IO_PORTS_RANGE_ADC0 = GPIOA,
  DDC112_IO_PORTS_RANGE_ADC1 = GPIOB,
}DDC112_IO_PORTS_RANGE;

#endif
*/
typedef struct DDC112_InitStructure
{
  
  
  uint32_t RCC_RANGE0;
  uint32_t RCC_RANGE1;
  uint32_t RCC_RANGE2;
  
  uint32_t RCC_DCLK;
  uint32_t RCC_DOUT;
  uint32_t RCC_DVALID;
  uint32_t RCC_DMIT;
  uint32_t RCC_TEST;
  
  GPIO_TypeDef* IO_PORT_RANGE;
  GPIO_TypeDef* IO_PORT_DCLK;
  GPIO_TypeDef* IO_PORT_DOUT;
  GPIO_TypeDef* IO_PORT_DVALID;
  GPIO_TypeDef* IO_PORT_DMIT;
  GPIO_TypeDef* IO_PORT_TEST;
  GPIO_TypeDef* IO_PORT_CONV;
  
  uint32_t GPIO_Pin_RANGE0;
  uint32_t GPIO_Pin_RANGE1;
  uint32_t GPIO_Pin_RANGE2;
  
  uint32_t GPIO_Pin_DCLK;
  uint32_t GPIO_Pin_DOUT;
  uint32_t GPIO_Pin_DVALID;
  uint32_t GPIO_Pin_DMIT;
  uint32_t GPIO_Pin_TEST;
  uint32_t GPIO_Pin_CONV;
  
  RANGE_VALUE Range;
  ConversionResult ResultChannel1A;
  ConversionResult ResultChannellB;
}DDC112_InitStructure;




typedef  enum DDC112_CHANNEL_ID
{
  DDC112_CHANNEL_ID_A,
  DDC112_CHANNEL_ID_B,
}DDC112_CHANNEL_ID;


void DDC112_Init(DDC112_InitStructure* Init);
void DDC112_ClockInit(void);

DDC112_CHANNEL_ID DDC112_GetCurrentChannelID(DDC112_InitStructure* Init);

void DDC112_SetRange(DDC112_InitStructure* Init,RANGE_VALUE SelectedCapacity);

RANGE_VALUE DDC112_GetRange(DDC112_InitStructure* Init);

void DDC112_MeasureProcess(void);
void DDC112_EnableTestMode(DDC112_InitStructure* Init);
void DDC112_DisableTestMode(DDC112_InitStructure* Init);
void DDC112_DCLK_RiseEdge(DDC112_InitStructure* Init);
void DDC112_DCLK_FallEdge(DDC112_InitStructure* Init);

uint32_t DDC112_GetChannel1Data(DDC112_InitStructure* Init);
uint32_t DDC112_GetChannel2Data(DDC112_InitStructure* Init);

int DDC112_DataReady(DDC112_InitStructure* Init);
void  DDC112_BegindDataReceive(DDC112_InitStructure* Init);
void DDC112_ReadSample(DDC112_InitStructure* Init, DDC112_CHANNEL_ID ID);

void  DDC112_EndDataReceive(DDC112_InitStructure* Init);


#ifdef __cplusplus
}
#endif
#endif