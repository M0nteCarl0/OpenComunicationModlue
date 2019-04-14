#include "stm32f4xx.h"
#ifdef __cplusplus

extern "C" {
#endif
void I2C_Core_Init(void);
void I2C_Core_GPIOInit(void);
void I2C_Core_ClockInit(void);
void I2C_Core_WriteToDevice(uint8_t Adress,uint8_t RegisterAdress,uint8_t* Data,uint16_t Count);
void I2C_Core_ReadFromDevice(uint8_t Adress,uint8_t RegisterAdress,uint8_t* Data,uint16_t Count);
void I2C_Core_ReadFromDeviceACK(uint8_t Adress,uint8_t RegisterAdress,uint8_t* Data,uint16_t Count);
#ifdef __cplusplus
}
#endif