#include <stdint.h>
#include "USB_Stream.h"
enum  Comands_ID
 {
   Comands_ID_WRITE_LED_ON = 0x1,
   Comands_ID_WRITE_LED_OFF = 0x2,
   Comands_ID_WRITE_LED_Blinky = 0x3,
   Comands_ID_WRITE_CUSTOM_BYTE = 0x4,
   Comands_ID_READ_LED_Blinky = 0x83,
   Comands_ID_READ_CUSTOM_BYTE = 0x84,
  
   Comands_ID_WRITE_RANGE_ALTERA       = 0x5,
   Comands_ID_WRITE_RANGE_ADC0         = 0x6,
   Comands_ID_WRITE_RANGE_ADC1         = 0x7,
   Comands_ID_START_INTEGRATION        = 0x8,
   Comands_ID_STOP_INTEGRATION         = 0x9,
   Comands_ID_START_MANUAL_TRIGGER     = 0x10,
   Comands_ID_ENABLE_TEST_MODE         = 0x11,
   Comands_ID_DISABLE_TEST_MODE        = 0x12,
   
   
   Comands_ID_READ_RANGE_ALTERA        = 0x85,
   Comands_ID_READ_RANGE_ADC0          = 0x86,
   Comands_ID_READ_RANGE_ADC1          = 0x87,
   Comands_ID_READ_CURRENT_CHANNEL_ADC = 0x88,
   Comands_ID_READ_AMPLITUDES_ADC      = 0x89,
   Comands_ID_READ_AMPLITUDES_ADCMix   = 0x90,
  
 };
#ifdef __cplusplus
 extern "C" {
#endif 

void  Comands_ProcessLoop(uint8_t* Buff,int N);
int   Comands_Receive(uint8_t* Buff,int* N );
void  Comands_ID_WRITE_LED_ON_EV(uint8_t* Buff,int* N );
void  Comands_ID_WRITE_LED_OFF_EV(uint8_t* Buff,int* N );
void  Comands_ID_WRITE_LED_Blinky_EV(uint8_t* Buff,int* N );
void  Comands_ID_READ_LED_Blinky_EV(uint8_t* Buff,int* N );

void  Comands_ID_WRITE_RANGE_ALTERA_EV(uint8_t* Buff,int* N );
void  Comands_ID_WRITE_RANGE_ADC0_EV (uint8_t* Buff,int* N );
void  Comands_ID_WRITE_RANGE_ADC1_EV (uint8_t* Buff,int* N );
 
void  Comands_ID_START_INTEGRATION_EV(uint8_t* Buff,int* N );
void  Comands_ID_STOP_INTEGRATION_EV (uint8_t* Buff,int* N );

void  Comands_ID_ENABLE_TEST_MODE_EV(uint8_t* Buff,int* N );
void  Comands_ID_DISABLE_TEST_MODE_EV (uint8_t* Buff,int* N );


void  Comands_ID_READ_RANGE_ALTERA_EV (uint8_t* Buff,int* N );
void  Comands_ID_READ_RANGE_ADC0_EV (uint8_t* Buff,int* N );
void  Comands_ID_READ_RANGE_ADC1_EV(uint8_t* Buff,int* N );
void  Comands_ID_READ_CURRENT_CHANNEL_ADC_EV (uint8_t* Buff,int* N );

void  Comands_ID_READ_AMPLITUDES_ADC_EV(uint8_t* Buff,int* N);
void  Comands_ID_READ_AMPLITUDES_ADCMix_EV(uint8_t* Buff,int* N);


#ifdef __cplusplus
 }
#endif 