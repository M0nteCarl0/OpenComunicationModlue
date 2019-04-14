
#include "Comand_protocol.h"
#include "Comands.hpp"
#include "ByteConversion.hpp"
#include "DDC12_Core.h"
#include "LED.h"
#include "FlashExtended.hpp"
typedef struct
{
  uint32_t ABS_POS;
  uint16_t EL_POS;
  uint32_t MARK;
  uint32_t SPEED;
  uint16_t ACC;
  uint16_t DEC;
  uint16_t MAX_SPEED;
  uint16_t MIN_SPEED;
  uint16_t FS_SPD;
  uint8_t  TVAL_HOLD;
  uint8_t  TVAL_RUN;
  uint8_t  TVAL_ACC;
  uint8_t  TVAL_DEC;
  uint16_t RESERVED_3;
  uint8_t  T_FAST;
  uint8_t  TON_MIN;
  uint8_t  TOFF_MIN;
  uint8_t  RESERVED_2;
  uint8_t  ADC_OUT;
  uint8_t  OCD_TH;
  uint8_t  RESERVED_1;
  uint8_t  STEP_MODE;
  uint8_t  ALARM_EN;
  uint16_t GATECFG1;
  uint8_t  GATECFG2;
  uint16_t CONFIG;
  uint16_t STATUS;
  uint16_t CheckWord;
}cSPIN_RegsStruct_TypeDef;
cSPIN_RegsStruct_TypeDef TestStructure;
int32_t                  g_AddresSPIN =   0x08040000;
FlashIO Flash;
/**
******************************************************************************
* @file    Comands.c
* @author  TechNotarius
* @version V 0.5.1
* @date    5-june-2017
* @brief   
*         
*/ 
uint16_t Time = 0;
uint16_t TimeErr = 0;

/*****************************************************************************/
 void  Comands_ProcessLoop(uint8_t* Buff,int N)//Функция исполнения команд
{
    uint8_t ComandID;
    if(Comand_protocol_parcer(Buff,&N,&ComandID))//Функция разбора полученых данных  по простому протоколу(Базис для имплантации собственого протокола)
    {
        switch(ComandID)
        {
           case  Comands_ID_READ_RANGE_ALTERA:
          {
            
            Comands_ID_READ_RANGE_ALTERA_EV(Buff,&N );
            break;
          }
          case Comands_ID_READ_RANGE_ADC0:
           {
            Comands_ID_READ_RANGE_ADC0_EV (Buff,&N );
            break;
          }
          case    Comands_ID_READ_RANGE_ADC1:
          {
           
           Comands_ID_READ_RANGE_ADC1_EV (Buff,&N );
          break; 
          }
          case  Comands_ID_READ_CURRENT_CHANNEL_ADC:
          {
            Comands_ID_READ_CURRENT_CHANNEL_ADC_EV (Buff, &N );
            break;
          }
        
            case Comands_ID_WRITE_RANGE_ALTERA:
            {
             Comands_ID_WRITE_RANGE_ALTERA_EV(Buff,&N);
            break;
            }
            case  Comands_ID_WRITE_RANGE_ADC0:
            {
              
             Comands_ID_WRITE_RANGE_ADC0_EV (Buff,&N );
             break;
            }
            case  Comands_ID_WRITE_RANGE_ADC1:
            {
              Comands_ID_WRITE_RANGE_ADC1_EV (Buff, &N );
              break;
            }
            case  Comands_ID_START_INTEGRATION:
            {
              
            Comands_ID_START_INTEGRATION_EV(Buff,&N);
            break; 
            }
          
            case Comands_ID_STOP_INTEGRATION:
           {
             Comands_ID_STOP_INTEGRATION_EV(Buff,&N);
             break;
           }
             
            case  Comands_ID_WRITE_LED_ON:
            {
          
             Comands_ID_WRITE_LED_ON_EV(Buff,&N );
            break;
            }
            case  Comands_ID_WRITE_LED_OFF:
            {
              Comands_ID_WRITE_LED_OFF_EV( Buff, &N );
            break;
            }
            case Comands_ID_WRITE_LED_Blinky:
            {
              Comands_ID_WRITE_LED_Blinky_EV(Buff, &N);
            break;
            }
            case Comands_ID_READ_LED_Blinky:
            {
              Comands_ID_READ_LED_Blinky_EV(Buff,&N );
            break;
            }
            
           case Comands_ID_READ_AMPLITUDES_ADC:
          {
            Comands_ID_READ_AMPLITUDES_ADC_EV(Buff,&N);
            break;
          }
       
         
        case  Comands_ID_DISABLE_TEST_MODE:
          {
           Comands_ID_DISABLE_TEST_MODE_EV(Buff,&N);
           break;
          }
          case   Comands_ID_ENABLE_TEST_MODE:
          {
            Comands_ID_ENABLE_TEST_MODE_EV(Buff,&N);
            break;
          }
          
          
          case  Comands_ID_READ_AMPLITUDES_ADCMix:
            {
                Comands_ID_READ_AMPLITUDES_ADCMix_EV(Buff,&N);
                break;   
            }
           
          
        }
          
         
  
          
          
          
          
          
          
          
          
          
#if 0    
            case  Comands_ID_WRITE_LED_ON:
            {
              Comands_ID_WRITE_LED_ON_EV(Buff,&N );
            break;
            }
            case  Comands_ID_WRITE_LED_OFF:
            {
              Comands_ID_WRITE_LED_OFF_EV( Buff, &N );
            break;
            }
            case Comands_ID_WRITE_LED_Blinky:
            {
              Comands_ID_WRITE_LED_Blinky_EV(Buff, &N);
            break;
            }
            case Comands_ID_READ_LED_Blinky:
            {
              Comands_ID_READ_LED_Blinky_EV(Buff,&N );
            break;
            }
            
            case Comands_ID_READ_AMPLITUDES_ADC:
            {
              Comands_ID_READ_AMPLITUDES_ADC_EV(Buff,&N );
              break;
            }
#endif              
            
        }
    }

/*****************************************************************************/
void  Comands_ID_WRITE_LED_ON_EV(uint8_t* Buff,int* N )
{
   LED_RedOn();
}
/*****************************************************************************/
void  Comands_ID_WRITE_LED_OFF_EV(uint8_t* Buff,int* N )
{
    LED_RedOff();
}
/*****************************************************************************/
void  Comands_ID_WRITE_LED_Blinky_EV(uint8_t* Buff,int* N )
{
  Time = Buff[6] | (Buff[7]<<8);
  Flash.Write(g_AddresSPIN,&TestStructure,1);
}
/*****************************************************************************/
void  Comands_ID_READ_LED_Blinky_EV(uint8_t* Buff,int* N )
{ 
  int SN  = Comand_protocol_GetRequstedByteCount(Buff); 
  Buff[6] = Time & 0xff;
  Buff[7] = Time >> 8;
  USB_Stream_Send(Buff,&SN); 
}
/*****************************************************************************/


/*****************************************************************************/
void  Comands_ID_START_INTEGRATION_EV(uint8_t* Buff,int* N )
{
   DDC12_Core_StartIntegration(); 
}
/*****************************************************************************/
void  Comands_ID_STOP_INTEGRATION_EV (uint8_t* Buff,int* N )
{
    DDC12_Core_StopIntegration(); 
}
/*****************************************************************************/
void  Comands_ID_READ_RANGE_ALTERA_EV (uint8_t* Buff,int* N )
{
  __disable_interrupt();
  int SN  = Comand_protocol_GetRequstedByteCount(Buff); 
  Buff[6] =  DDC12_Core_AlteraGetRange();
  __enable_interrupt();
  USB_Stream_Send(Buff,&SN); 
  
  
}
/*****************************************************************************/
void  Comands_ID_READ_RANGE_ADC0_EV (uint8_t* Buff,int* N )
{
  __disable_interrupt();
  int SN  = Comand_protocol_GetRequstedByteCount(Buff);
  uint8_t DDC1_Range = DDC12_Core_ADC0GetRange();
  Buff[6] =  DDC1_Range;
  __enable_interrupt();
  USB_Stream_Send(Buff,&SN); 
  
}
/*****************************************************************************/
void  Comands_ID_READ_RANGE_ADC1_EV(uint8_t* Buff,int* N )
{
  
 __disable_interrupt();
  int SN  = Comand_protocol_GetRequstedByteCount(Buff); 
  uint8_t DDC2_Range =  DDC12_Core_ADC1GetRange();
  Buff[6] = DDC2_Range;
  __enable_interrupt();
  USB_Stream_Send(Buff,&SN); 
  
}
/*****************************************************************************/
void  Comands_ID_READ_CURRENT_CHANNEL_ADC_EV (uint8_t* Buff,int* N )
{
  __disable_interrupt(); 
  int SN  = Comand_protocol_GetRequstedByteCount(Buff); 
  Buff[6] =  DDC12_Core_GetChannellID();
   __enable_interrupt();
  USB_Stream_Send(Buff,&SN); 
  
}
/*****************************************************************************/
void  Comands_ID_WRITE_RANGE_ALTERA_EV(uint8_t* Buff,int* N )
{
  DDC12_Core_AlteraSetRange( Buff[6]);
}
/*****************************************************************************/
void  Comands_ID_WRITE_RANGE_ADC0_EV (uint8_t* Buff,int* N )
{
  DDC12_Core_ADC0SetRange(Buff[6]);
}
/*****************************************************************************/
void  Comands_ID_WRITE_RANGE_ADC1_EV (uint8_t* Buff,int* N )
{
  
  DDC12_Core_ADC1SetRange(Buff[6]);
  
}
/*****************************************************************************/
void  Comands_ID_READ_AMPLITUDES_ADC_EV(uint8_t* Buff,int* N)
{
  bool Flag = true;
  __disable_interrupt();
   int SN  = Comand_protocol_GetRequstedByteCount(Buff); 
   uint32_t Offset;
   uint32_t* SamplesADC0A_Chanel0 = DDC12_Core_GetSamplesADC0A_Chanel0();
   uint32_t* SamplesADC0A_Chanel1 = DDC12_Core_GeSamplesADC0A_Chanel1();
   uint32_t* SamplesADC0B_Chanel0 = DDC12_Core_GeSamplesADC0B_Chanel0();
   uint32_t* SamplesADC0B_Chanel1 = DDC12_Core_GeSamplesADC0B_Chanel1();
                                                         
   uint32_t* SamplesADC1A_Chanel0 = DDC12_Core_GeSamplesADC1A_Chanel0();
   uint32_t* SamplesADC1A_Chanel1 = DDC12_Core_GeSamplesADC1A_Chanel1();
   uint32_t* SamplesADC1B_Chanel0 = DDC12_Core_GeSamplesADC1B_Chanel0();
   uint32_t* SamplesADC1B_Chanel1 = DDC12_Core_GeSamplesADC1B_Chanel1();
     
 Conversion::UnsignedBuffer32BitToUnsigned8bitFormatBuffer(SamplesADC0A_Chanel0,100,&Buff[6],Offset);
 Conversion:: UnsignedBuffer32BitToUnsigned8bitFormatBuffer(SamplesADC0A_Chanel1,100,&Buff[407],Offset);
 Conversion:: UnsignedBuffer32BitToUnsigned8bitFormatBuffer(SamplesADC0B_Chanel0,100,&Buff[807],Offset);
 Conversion:: UnsignedBuffer32BitToUnsigned8bitFormatBuffer(SamplesADC0B_Chanel1,100,&Buff[1207],Offset);
  
 Conversion::  UnsignedBuffer32BitToUnsigned8bitFormatBuffer(SamplesADC1A_Chanel0,100,&Buff[1607],Offset);
 Conversion::  UnsignedBuffer32BitToUnsigned8bitFormatBuffer(SamplesADC1A_Chanel1,100,&Buff[2007],Offset);
 Conversion::  UnsignedBuffer32BitToUnsigned8bitFormatBuffer(SamplesADC1B_Chanel0,100,&Buff[2407],Offset);
 Conversion::  UnsignedBuffer32BitToUnsigned8bitFormatBuffer(SamplesADC1B_Chanel1,100,&Buff[2807],Offset); 
 __enable_interrupt();
 USB_Stream_Send(Buff,&SN); 

}
/*****************************************************************************/
void  Comands_ID_READ_AMPLITUDES_ADCMix_EV(uint8_t* Buff,int* N)
{

    __disable_interrupt();
    int SN  = Comand_protocol_GetRequstedByteCount(Buff); 
    uint32_t Offset; 
    uint32_t* SamplesADC0_Chanel0  =  DDC12_Core_GetSamplesADC0A_Chanel0();
    uint32_t* SamplesADC0_Chanel1  =  DDC12_Core_GeSamplesADC0A_Chanel1();
    uint32_t* SamplesADC1_Chanel0  =  DDC12_Core_GeSamplesADC0B_Chanel0();
    uint32_t* SamplesADC1_Chanel1  =  DDC12_Core_GeSamplesADC0B_Chanel1();

    Conversion::UnsignedBuffer32BitToUnsigned8bitFormatBuffer(SamplesADC0_Chanel0,100,&Buff[6],Offset);
    Conversion::UnsignedBuffer32BitToUnsigned8bitFormatBuffer(SamplesADC0_Chanel1,100,&Buff[406],Offset);
    Conversion::UnsignedBuffer32BitToUnsigned8bitFormatBuffer(SamplesADC1_Chanel0,100,&Buff[806],Offset);
    Conversion::UnsignedBuffer32BitToUnsigned8bitFormatBuffer(SamplesADC1_Chanel1,100,&Buff[1206],Offset);

    USB_Stream_Send(Buff,&SN); 
    __enable_interrupt();


}
/*****************************************************************************/
void  Comands_ID_ENABLE_TEST_MODE_EV(uint8_t* Buff,int* N )
{
  DDC12_Core_EnableTestMode();
}
/*****************************************************************************/
void  Comands_ID_DISABLE_TEST_MODE_EV (uint8_t* Buff,int* N )
{
  DDC12_Core_DisableTestMode();
}
/*****************************************************************************/