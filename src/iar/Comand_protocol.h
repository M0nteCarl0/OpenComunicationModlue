#pragma once
#include <stdint.h>
#ifdef __cplusplus
 extern "C" {
#endif 
int Comand_protocol_parcer(uint8_t* Buff,int* N,uint8_t* ComandID);   
int Comand_protocol_DataReceive_parcer(uint8_t* Buff,int* N,uint8_t* ComandID);
int Comand_protocol_CheckHeader(uint8_t* Buff,int* N);
int Comand_protocol_CheckData(uint8_t* Buff,int* N);
void Comand_protocol_Send(uint8_t* Buff,int* N);
int Comand_protocol_GetRequstedByteCount(uint8_t* Buff);
#ifdef __cplusplus
 }
#endif 