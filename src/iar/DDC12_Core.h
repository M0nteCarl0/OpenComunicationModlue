#include "DDC12.h"
#ifdef __cplusplus
extern "C" {
#endif
void DDC12_Core_Init(void);
void DDC12_Core_ScanADC(void);

void DDC12_Core_StartIntegration(void);
void DDC12_Core_StopIntegration(void);

void DDC12_Core_AlteraSetRange(uint8_t Range);
uint8_t DDC12_Core_AlteraGetRange(void);

void DDC12_Core_ADC0SetRange(uint8_t Range);
uint8_t DDC12_Core_ADC0GetRange(void);

void DDC12_Core_ADC1SetRange(uint8_t Range);
uint8_t DDC12_Core_ADC1GetRange(void);

void DDC12_Core_EnableTestMode(void);
void DDC12_Core_DisableTestMode(void);


uint32_t* DDC12_Core_GetSamplesADC0A_Chanel0(void);
uint32_t* DDC12_Core_GeSamplesADC0A_Chanel1(void);
uint32_t* DDC12_Core_GeSamplesADC0B_Chanel0(void);
uint32_t* DDC12_Core_GeSamplesADC0B_Chanel1(void);


uint32_t* DDC12_Core_GeSamplesADC1A_Chanel0(void);
uint32_t* DDC12_Core_GeSamplesADC1A_Chanel1(void);
uint32_t* DDC12_Core_GeSamplesADC1B_Chanel0(void);
uint32_t* DDC12_Core_GeSamplesADC1B_Chanel1(void);





DDC112_CHANNEL_ID DDC12_Core_GetChannellID(void);
void EXTI15_10_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
#ifdef __cplusplus
}
#endif