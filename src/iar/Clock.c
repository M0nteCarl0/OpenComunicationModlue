#include "Clock.h"
#include <stdio.h>

static WorkCLK DeviceClocks;

void Clock_HSI_Init(void) // 1-st Stage
{
  RCC_DeInit();
  RCC_HSICmd(ENABLE);
  RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
  RCC_HCLKConfig(RCC_SYSCLK_Div1);
  RCC_PCLK1Config(RCC_HCLK_Div1);
  RCC_PCLK2Config(RCC_HCLK_Div1);
  FLASH_SetLatency(FLASH_Latency_7);
}

void Clock_HSE_Init(void) // 2-nd Stage
{
  RCC_DeInit();
  RCC_HSICmd(ENABLE);
  while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) != SET) {
  };
  RCC_HSEConfig(RCC_HSE_ON);
  RCC_WaitForHSEStartUp();
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

  /*
  finput = 8 Mhz
  PLLM = 8
  PLLM = 336
  PLLP = 2
  PLLQ = 8
  
  FVCO = finput * (PLLN/PLLM) = 8 * (336/8) ->336
  FPLL = FVCO/PLLP = 336/2 ->168
  FUSB = FVCO/PLLQ = 336/7 ->48
  AHB  Clock = FPLL->168;
  APB1 Clock = FPLL/DIVAPB1 = 168/4 = 42 Mhz
  APB2 Clock = FPLL/DIVAPB2 = 168/4 = 42 Mhz
  */
  RCC_PLLConfig(RCC_PLLSource_HSE, 8, 336, 2, 7); // 168 mhz CORE
  RCC_PLLCmd(ENABLE);
  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != SET) {
  };
  RCC_HCLKConfig(RCC_SYSCLK_Div1); // 168 mhz AHB(OTG HS,ETH,DMA,CRC,GPIOx)
  RCC_PCLK1Config(RCC_HCLK_Div8);  // 21 mhz APB1(DAC,PWR,I2Cx,SPIx)
  RCC_PCLK2Config(RCC_HCLK_Div4);  // 42 mhz APB2
  SYSCFG_CompensationCellCmd(ENABLE);
}

void Clock_InitClocs(Clocks CLK) {
  RCC_DeInit();
  uint32_t PLLSource = 0x0;
  if (CLK.OSC_TYPE == RCC_SYSCLKSource_HSI) {

    RCC_HSICmd(ENABLE);
    CLK.OSC_MHZ = 16;
    while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) != SET) {
    };
    PLLSource = RCC_PLLSource_HSI;
  } else {
    RCC_HSEConfig(RCC_HSE_ON);
    while (RCC_WaitForHSEStartUp() != SUCCESS) {
    };
    PLLSource = RCC_PLLSource_HSE;
  }
  DeviceClocks.OSC_Hertz = CLK.OSC_MHZ * 1000000;
  DeviceClocks.AHB =
      (DeviceClocks.OSC_Hertz * (CLK.PLLN / CLK.PLLM)) / CLK.PLLP;
  RCC_PLLConfig(PLLSource, CLK.PLLM, CLK.PLLN, CLK.PLLP, CLK.PLLQ);
  RCC_PLLCmd(ENABLE);
  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != SET) {
  };
  RCC_HCLKConfig(CLK.AHB_Divider);
  RCC_PCLK1Config(CLK.APB1_Divider);
  RCC_PCLK2Config(CLK.APB2_Divider);
}

uint32_t Clock_GetAHBDicider(uint32_t DivAllias) {
  uint32_t Divider;
  switch (DivAllias) {
  case RCC_SYSCLK_Div1: {
    Divider = 1;
    break;
  };
  case RCC_SYSCLK_Div2: {
    Divider = 2;
    break;
  };
  case RCC_SYSCLK_Div4: {
    Divider = 4;
    break;
  };
  case RCC_SYSCLK_Div8: {
    Divider = 8;
    break;
  };
  case RCC_SYSCLK_Div16: {
    Divider = 16;
    break;
  };
  case RCC_SYSCLK_Div64: {
    Divider = 64;
    break;
  };
  case RCC_SYSCLK_Div128: {
    Divider = 128;
    break;
  };
  case RCC_SYSCLK_Div256: {
    Divider = 256;
    break;
  };
  case RCC_SYSCLK_Div512: {
    Divider = 512;
    break;
  };
  }
  return Divider;
}

uint32_t Clock_GetAPBDicider(uint32_t DivAllias) {
  uint32_t Divider;
  switch (DivAllias) {
  case RCC_HCLK_Div1: {
    Divider = 1;
    break;
  };
  case RCC_HCLK_Div2: {
    Divider = 2;
    break;
  };
  case RCC_HCLK_Div4: {
    Divider = 4;
    break;
  };
  case RCC_HCLK_Div8: {
    Divider = 8;
    break;
  };
  case RCC_HCLK_Div16: {
    Divider = 16;
    break;
  };
  }
  return Divider;
}

WorkCLK Clock_GetWorkClocks(void) { return DeviceClocks; };

void Clock_InitUSB(void) {
  RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_OTG_FS, ENABLE);
};
