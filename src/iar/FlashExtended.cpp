#include "FlashExtended.hpp"

FlashIO::FlashIO(void)
    : _DataWriteSuccesfull(false), _VoltageRange(VoltageRange_3) {
  RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_HASH, ENABLE);
}

FlashIO::~FlashIO(void) {
  RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_HASH, DISABLE);
}

bool FlashIO::SectorIsClean(uint8_t Sector) {

  u32 RealAdress = StartAddres[Sector];
  u32 EndAdress = StartAddres[Sector + 1];
  u32 SectorSize = EndAdress - RealAdress;
  u32 DataField = 0;
  Read(RealAdress, &DataField, 1);
}

u32 FlashIO ::GetHighAdressSector(uint8_t Sector) {
  if (Sector < 23) {
    return FLASH_START + SectorBegin[Sector + 1];
  }
  if (Sector == 23) {
  }
};

uint16_t FlashIO ::GetSectorID(u32 Addres) {
  u8 SectorIndex = 0;
  do {
    u32 RealAdress = StartAddres[SectorIndex];
    u32 EndAdress = StartAddres[SectorIndex + 1];
    if (Addres >= RealAdress && Addres < EndAdress) {
      goto END;
    }
    SectorIndex++;
  } while (SectorIndex < 11);
END:
  return SectorBegin[SectorIndex];
}
void FlashIO ::SetVoltageRange(uint8_t VoltageRange) {
  _VoltageRange = VoltageRange;
};
