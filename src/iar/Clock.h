#include "stm32f4xx.h"
#ifndef _CLK_
#define _CLK_
#ifdef __cplusplus
 extern "C" {
#endif  
  
   
   
   
#define  CPU_ID  uint32_t(0xE000ED00) 
#define  FLASH_SIZE    uint32_t(0x1FFF7A10)
   
 typedef  struct CPU_IDS
  {  
   __IO uint8_t  Revision:4;
   __IO uint16_t Part_No:12;
   __IO  uint8_t  Const:4;
   __IO uint8_t  Variant:4;
   __IO uint8_t  Implenter:8;
  }CPU_IDS;  
 
 
 typedef  struct FLASHS
 {
    __IO uint16_t  SIZE;
   
 }FLASHS;
#define  CPU_IDTypedef   ((CPU_IDS*) CPU_ID)  
#define   FLASHS_Typedef  ((FLASHS*)FLASH_SIZE )
  typedef  struct Clocks
  {  
    uint32_t OSC_TYPE;
    uint32_t OSC_MHZ;
    uint32_t PLLM;
    uint32_t PLLN;
    uint32_t PLLQ;
    uint32_t PLLP;
    uint32_t AHB_Divider;
    uint32_t APB1_Divider;
    uint32_t APB2_Divider;
  }Clocks;
   
  
   typedef  struct WorkCLK
  {  
    uint32_t OSC_Hertz;
    uint32_t AHB;
    uint32_t APB1;
    uint32_t APB2;
    uint32_t Timers;
  }WorkCLK;
  
  
void Clock_HSI_Init(void);
void Clock_HSE_Init(void);
void Clock_InitClocs(Clocks CLK);
void Clock_InitUSB(void);
WorkCLK  Clock_GetWorkClocks(void);
uint32_t  Clock_GetAHBDicider(uint32_t DivAllias);
uint32_t  Clock_GetAPBDicider(uint32_t DivAllias);
#ifdef __cplusplus
 }
#endif
#endif