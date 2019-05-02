#include "Comand_protocol.h"
#define Signature 0x92

int Comand_protocol_CheckHeader(uint8_t *Buff, int *N) {
  int Flag = 0;
  int DataReceived = Buff[2] | (Buff[3] << 8);
  if (Buff[0] == Signature) {
    if (DataReceived == *N) {
      Flag = 1;
    }
  }
  return Flag;
}

int Comand_protocol_CheckData(uint8_t *Buff, int *N) //
{
  return Comand_protocol_CheckHeader(Buff, N);
}

int Comand_protocol_parcer(uint8_t *Buff, int *N, uint8_t *ComandID) {
  int Flag = 0;
  if (Comand_protocol_CheckData(Buff, N)) {
    *ComandID = Buff[1];
    Flag = 1;
  }
  return Flag;
}

int Comand_protocol_GetRequstedByteCount(uint8_t *Buff) {
  int DataToSend = Buff[4] | (Buff[5] << 8);
  return DataToSend;
};
