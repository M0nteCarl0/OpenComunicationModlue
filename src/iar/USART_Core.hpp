#include "stm32f4xx.h"
#ifdef __cplusplus
extern "C" {
#endif
void USART_Core_Init_HardwareLayer(int USARTID);
void USART_Core_Configure(int USARTID);
void USART_Core_Test(void);
void  USART2_IRQHandler(void);
#ifdef __cplusplus
}
#endif
