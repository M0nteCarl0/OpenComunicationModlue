#include "USART_Core.hpp"
uint8_t BufferReceive[65535];
uint16_t ReceivedByteCount;
const int BufferSize = 65535;
void USART_Core_Init_HardwareLayer(int USARTID)
{
  
   RCC_APB1PeriphClockCmd (RCC_APB1Periph_USART2,ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);
   RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOA,  ENABLE);   
   GPIO_PinAFConfig (GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
   GPIO_PinAFConfig (GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
  
  GPIO_InitTypeDef GPIO_InitStructure;
                                    /* Configure USARTy Rx as input floating */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;             //GPIO_Mode_IN_FLOATING;
  GPIO_Init (GPIOA, &GPIO_InitStructure);
  
                      /* Configure USARTy Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;             //GPIO_Mode_AF_PP;
  GPIO_Init (GPIOA, &GPIO_InitStructure);
  
  
  
  
  
  
  
  DMA_InitTypeDef USART_DMA;
    
  DMA_StructInit(&USART_DMA);
  USART_DMA.DMA_BufferSize = 65535;
  USART_DMA.DMA_DIR = DMA_DIR_PeripheralToMemory;
  USART_DMA.DMA_Channel = DMA_Channel_4;

   
  USART_DMA.DMA_Memory0BaseAddr =(uint32_t)BufferReceive;
  USART_DMA.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  USART_DMA.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  USART_DMA.DMA_MemoryInc = DMA_MemoryInc_Enable;
  USART_DMA.DMA_Mode = DMA_Mode_Circular;
    
  USART_DMA.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR;
  USART_DMA.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  USART_DMA.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  USART_DMA.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  USART_DMA.DMA_Priority = DMA_Priority_High;
    
    
    
  DMA_Init(DMA1_Stream5,&USART_DMA);
  
  
  
   
  
  USART_InitTypeDef USART_InitStructure;
  USART_InitStructure.USART_BaudRate    = 921600;     //19200;                                //115200;  
  USART_InitStructure.USART_WordLength  = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits    = USART_StopBits_2;
  USART_InitStructure.USART_Parity      = USART_Parity_Odd;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode        = USART_Mode_Rx| USART_Mode_Tx;
  USART_Init (USART2, &USART_InitStructure);
  USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);
  USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);
  USART_ClearITPendingBit(USART2,USART_IT_IDLE);
  USART_Cmd (USART2, ENABLE);
  NVIC_EnableIRQ(USART2_IRQn);
  
  DMA_Cmd(DMA1_Stream5,ENABLE);
  
  
  
  
}


void USART_Core_Test(void)
{
  
  USART_Core_Init_HardwareLayer(1);
  
};


void USART_Core_Configure(int USARTID)
{
  
  
  
  
}


void  USART2_IRQHandler(void)
{
  if(USART_GetITStatus (USART2, USART_IT_IDLE) != RESET)
  {
    
    ReceivedByteCount =  BufferSize -  DMA_GetCurrDataCounter(DMA1_Stream5);
    USART_ClearITPendingBit(USART2,USART_IT_IDLE);
    
    
  }
  
  
}
