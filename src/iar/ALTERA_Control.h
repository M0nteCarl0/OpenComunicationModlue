#include "stm32f4xx.h"

#ifdef __cplusplus
extern "C" {
#endif
 
 typedef  enum  ALTERA_Control_Range
{
  ALTERA_Control_Range_500us,
  ALTERA_Control_Range_1000us,
  ALTERA_Control_Range_2000us,
  ALTERA_Control_Range_4000us,
}ALTERA_Control_Range;

  
  
  
typedef struct ALTERA_InitStructure
{
  
  GPIO_TypeDef* IO_PORT_ALTERA_START_CONV;
  GPIO_TypeDef* IO_PORT_ALTERA_RSVD0;
  GPIO_TypeDef* IO_PORT_ALTERA_RSVD1;
  GPIO_TypeDef* IO_PORT_ALTERA_SR0;
  GPIO_TypeDef* IO_PORT_ALTERA_SR1;
  
  
  uint32_t IO_PIN_ALTERA_START_CONV;
  uint32_t IO_PIN_ALTERA_RSVD0;
  uint32_t IO_PIN_ALTERA_RSVD1;
  uint32_t IO_PIN_ALTERA_SR0;
  uint32_t IO_PIN_ALTERA_SR1;
  
  ALTERA_Control_Range Range;
  
  
}ALTERA_InitStructure;
  


  
void  ALTERA_Control_Init(ALTERA_InitStructure* Init); 
void  ALTERA_Control_StartADCClocking(ALTERA_InitStructure* Init);
void  ALTERA_Control_StopADCClocking(ALTERA_InitStructure* Init);
void  ALTERA_Control_SelectRange(ALTERA_InitStructure* Init, ALTERA_Control_Range Range);
ALTERA_Control_Range ALTERA_Control_GetRange(ALTERA_InitStructure* Init);

  
  
  


#ifdef __cplusplus
}
#endif
  