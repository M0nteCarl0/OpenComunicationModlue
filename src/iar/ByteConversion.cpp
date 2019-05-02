#include "ByteConversion.hpp"

void Conversion::WordToByte(uint16_t &Source, uint8_t &Dest1, uint8_t &Dest2) {
  Dest1 = Source & 0xFF;
  Dest2 = Source >> 8;
};

void Conversion::ByteToWord(uint16_t &Source, uint8_t &Dest1, uint8_t &Dest2) {
  Source = Dest1 | (Dest2 << 8);
};

void Conversion::DWordToByte(uint32_t &Source, uint8_t &Dest1, uint8_t &Dest2,
                             uint8_t &Dest3, uint8_t &Dest4) {
  uint16_t Word1 = Source & 0xFFFF;
  uint16_t Word2 = Source >> 16;
  Conversion::WordToByte(Word1, Dest1, Dest2);
  Conversion::WordToByte(Word2, Dest3, Dest4);
};

void Conversion::ByteToDWord(uint32_t &Source, uint8_t &Dest1, uint8_t &Dest2,
                             uint8_t &Dest3, uint8_t &Dest4) {
  uint16_t Word1 = 0;
  uint16_t Word2 = 0;
  Conversion::ByteToWord(Word1, Dest1, Dest2);
  Conversion::ByteToWord(Word2, Dest3, Dest4);
  Source = Word1 | (Word2 << 16);
};

void Conversion::QWordToByte(uint64_t &Source, uint8_t &Dest1, uint8_t &Dest2,
                             uint8_t &Dest3, uint8_t &Dest4, uint8_t &Dest5,
                             uint8_t &Dest6, uint8_t &Dest7, uint8_t &Dest8) {
  uint32_t Dword1 = Source & 0xffffffff;
  uint32_t Dword2 = Source >> 32;
  Conversion::DWordToByte(Dword1, Dest1, Dest2, Dest3, Dest4);
  Conversion::DWordToByte(Dword2, Dest5, Dest6, Dest7, Dest8);
};

void Conversion::ByteTo7Bit(uint8_t &Source, uint8_t &Dest1, uint8_t &Dest2) {
  Dest1 = Source & 0x7F;
  Dest2 = (Source >> 7);
};

void Conversion::Bit7ToByte(uint8_t &Source, uint8_t &Dest1, uint8_t &Dest2) {
  Source = Dest1 & 0x7F | (Dest2 << 7);
};

void Conversion::WordTo7Bit(uint16_t &Source, uint8_t &Dest1, uint8_t &Dest2,
                            uint8_t &Dest3, uint8_t &Dest4) {
  uint8_t D3[2];
  Conversion::WordToByte(Source, D3[0], D3[1]);
  Conversion::ByteTo7Bit(D3[0], Dest1, Dest2);
  Conversion::ByteTo7Bit(D3[1], Dest3, Dest4);
};

void Conversion::Bit7ToWord(uint16_t &Source, uint8_t &Dest1, uint8_t &Dest2,
                            uint8_t &Dest3, uint8_t &Dest4) {
  uint8_t D3[2];
  Conversion::Bit7ToByte(D3[0], Dest1, Dest2);
  Conversion::Bit7ToByte(D3[1], Dest1, Dest2);
  Conversion::ByteToWord(Source, D3[0], D3[1]);
};

void Conversion::DWordTo7Bit(uint32_t &Source, uint8_t &Dest1, uint8_t &Dest2,
                             uint8_t &Dest3, uint8_t &Dest4, uint8_t &Dest5,
                             uint8_t &Dest6, uint8_t &Dest7, uint8_t &Dest8) {

  uint8_t D3[4];
  Conversion::DWordToByte(Source, D3[0], D3[1], D3[2], D3[3]);
  Conversion::ByteTo7Bit(D3[0], Dest1, Dest2);
  Conversion::ByteTo7Bit(D3[1], Dest3, Dest4);
  Conversion::ByteTo7Bit(D3[2], Dest5, Dest6);
  Conversion::ByteTo7Bit(D3[3], Dest7, Dest8);
}

void Conversion::Bit7ToDWord(uint32_t &Source, uint8_t &Dest1, uint8_t &Dest2,
                             uint8_t &Dest3, uint8_t &Dest4, uint8_t &Dest5,
                             uint8_t &Dest6, uint8_t &Dest7, uint8_t &Dest8) {
  uint8_t D3[4];
  Conversion::Bit7ToByte(D3[0], Dest1, Dest2);
  Conversion::Bit7ToByte(D3[1], Dest3, Dest4);
  Conversion::Bit7ToByte(D3[2], Dest5, Dest6);
  Conversion::Bit7ToByte(D3[3], Dest6, Dest7);
  Conversion::ByteToDWord(Source, D3[0], D3[1], D3[2], D3[3]);
};

void Conversion::Signed8BitToUnsigned7bitFormat(int8_t &Source, uint8_t &Dest1,
                                                uint8_t &Dest2) {
  Dest1 = Source & 0x7f;
  Dest2 = (Source & 0x80) >> 7;
}

void Conversion::Unsigned7bitFormaTotSigned8Bit(int8_t &Destinatation,
                                                uint8_t &Source1,
                                                uint8_t &Source2) {
  Destinatation = Source1 | Source2 << 7;
}

void Conversion::Signed16BitToUnsigned7bitFormat(int16_t &Source,
                                                 uint8_t &Dest1, uint8_t &Dest2,
                                                 uint8_t &Dest3) {
  Dest1 = Source & 0xFF;
  Dest2 = (Source >> 8) & 0xFF;

  Dest3 = 0;
  if (Dest1 & 0x80) {
    Dest3 |= 1 << 0;
  }

  if (Dest2 & 0x80) {
    Dest3 |= 1 << 1;
  }
  Dest1 = Dest1 & 0x7f;
  Dest2 = Dest2 & 0x7f;
}

void Conversion::Unsigned7bitFormaTotSigned16Bit(int16_t &Destinatation,
                                                 uint8_t &Source1,
                                                 uint8_t &Source2,
                                                 uint8_t &Source3) {
  uint8_t Buff[2];
  Buff[0] = Source1;
  Buff[1] = Source2;
  if (Source3 & 1 << 0) {
    Buff[0] |= 0x80;
  }

  if (Source3 & 1 << 1) {
    Buff[1] |= 0x80;
  }
  Destinatation = Buff[0] | (int16_t)Buff[1] << 8;
}
/***************************************************************************/
void Conversion::Signed32BitToUnsigned7bitFormat(int32_t &Source,
                                                 uint8_t &Dest1, uint8_t &Dest2,
                                                 uint8_t &Dest3, uint8_t &Dest4,
                                                 uint8_t &Dest5) {

  Dest1 = Source & 0xFF;
  Dest2 = (Source >> 8) & 0xFF;
  Dest3 = (Source >> 16) & 0xFF;
  Dest4 = (Source >> 24) & 0xFF;
  Dest5 = 0;
  if (Dest1 & 0x80) {
    Dest5 |= 1 << 0;
  }

  if (Dest2 & 0x80) {
    Dest5 |= 1 << 1;
  }

  if (Dest3 & 0x80) {
    Dest5 |= 1 << 2;
  }

  if (Dest4 & 0x80) {
    Dest5 |= 1 << 3;
  }
  Dest1 = Dest1 & 0x7f;
  Dest2 = Dest2 & 0x7f;
  Dest3 = Dest3 & 0x7f;
  Dest4 = Dest4 & 0x7f;
}
/***************************************************************************/
void Conversion::Unsigned7bitFormaTotSigned32Bit(
    int32_t &Destinatation, uint8_t &Source1, uint8_t &Source2,
    uint8_t &Source3, uint8_t &Source4, uint8_t &Source5) {

  uint8_t Buff[4];
  Buff[0] = Source1;
  Buff[1] = Source2;
  Buff[2] = Source3;
  Buff[3] = Source4;
  if (Source5 & 1 << 0) {
    Buff[0] |= 0x80;
  }
  if (Source5 & 1 << 1) {
    Buff[1] |= 0x80;
  }
  if (Source5 & 1 << 2) {
    Buff[2] |= 0x80;
  }
  if (Source5 & 1 << 3) {
    Buff[3] |= 0x80;
  }
  Destinatation = Buff[0] | (int32_t)Buff[1] << 8 | (int32_t)Buff[2] << 16 |
                  (int32_t)Buff[3] << 24;
}

void Conversion::Signed64BitToUnsigned7bitFormat(
    int64_t &Source, uint8_t &Dest1, uint8_t &Dest2, uint8_t &Dest3,
    uint8_t &Dest4, uint8_t &Dest5, uint8_t &Dest6, uint8_t &Dest7,
    uint8_t &Dest8, uint8_t &Dest9, uint8_t &Dest10) {

  Dest1 = Source & 0xFF;
  Dest2 = (Source >> 8) & 0xFF;
  Dest3 = (Source >> 16) & 0xFF;
  Dest4 = (Source >> 24) & 0xFF;
  Dest5 = (Source >> 32) & 0xFF;
  Dest6 = (Source >> 40) & 0xFF;
  Dest7 = (Source >> 48) & 0xFF;
  Dest8 = (Source >> 56) & 0xFF;
  Dest9 = 0;
  Dest10 = 0;
  if (Dest1 & 0x80) {
    Dest9 |= 1 << 0;
  }
  if (Dest2 & 0x80) {
    Dest9 |= 1 << 1;
  }
  if (Dest3 & 0x80) {
    Dest9 |= 1 << 2;
  }
  if (Dest4 & 0x80) {
    Dest9 |= 1 << 3;
  }
  if (Dest5 & 0x80) {
    Dest9 |= 1 << 4;
  }
  if (Dest6 & 0x80) {
    Dest9 |= 1 << 5;
  }
  if (Dest7 & 0x80) {
    Dest9 |= 1 << 6;
  }
  if (Dest8 & 0x80) {
    Dest10 |= 1 << 1;
  }

  Dest1 = Dest1 & 0x7f;
  Dest2 = Dest2 & 0x7f;
  Dest3 = Dest3 & 0x7f;
  Dest4 = Dest4 & 0x7f;
  Dest5 = Dest5 & 0x7f;
  Dest6 = Dest6 & 0x7f;
  Dest7 = Dest7 & 0x7f;
  Dest8 = Dest8 & 0x7f;
}

void Conversion::Unsigned7bitFormaTotSigned64Bit(
    int64_t &Destinatation, uint8_t &Source1, uint8_t &Source2,
    uint8_t &Source3, uint8_t &Source4, uint8_t &Source5, uint8_t &Source6,
    uint8_t &Source7, uint8_t &Source8, uint8_t &Source9, uint8_t &Source10) {

  uint8_t Buff[8];
  Buff[0] = Source1;
  Buff[1] = Source2;
  Buff[2] = Source3;
  Buff[3] = Source4;
  Buff[4] = Source5;
  Buff[5] = Source6;
  Buff[6] = Source7;
  Buff[7] = Source8;

  if (Source9 & 1 << 0) {
    Buff[0] |= 0x80;
  }

  if (Source9 & 1 << 1) {
    Buff[1] |= 0x80;
  }

  if (Source9 & 1 << 2) {
    Buff[2] |= 0x80;
  }

  if (Source9 & 1 << 3) {
    Buff[3] |= 0x80;
  }

  if (Source9 & 1 << 4) {
    Buff[4] |= 0x80;
  }

  if (Source9 & 1 << 5) {
    Buff[5] |= 0x80;
  }

  if (Source9 & 1 << 6) {
    Buff[6] |= 0x80;
  }

  if (Source10 & 1 << 1) {
    Buff[7] |= 0x80;
  }

  Destinatation = Buff[0] | (int64_t)Buff[1] << 8 | (int64_t)Buff[2] << 16 |
                  (int64_t)Buff[3] << 24 | (int64_t)Buff[4] << 32 |
                  (int64_t)Buff[5] << 40 | (int64_t)Buff[6] << 48 |
                  (int64_t)Buff[7] << 56;
}
/***************************************************************************/
void Conversion::UnsignedBuffer32BitToUnsigned8bitFormatBuffer(
    uint32_t *SourceBuffer, uint32_t SourceSizeBuffer, uint8_t *OutputBuffer,
    uint32_t OutpuSizeBuffer) {

  uint32_t DestinationBuffer = 0;
  OutpuSizeBuffer = SourceSizeBuffer * 4;
  for (uint32_t i = 0; i < SourceSizeBuffer; i++) {

    OutputBuffer[DestinationBuffer] = SourceBuffer[i] & 0xFF;
    OutputBuffer[DestinationBuffer + 1] = (SourceBuffer[i] >> 8) & 0xFF;
    OutputBuffer[DestinationBuffer + 2] = (SourceBuffer[i] >> 16) & 0xFF;
    OutputBuffer[DestinationBuffer + 3] = (SourceBuffer[i] >> 24) & 0xFF;
    DestinationBuffer += 4;
  }
}
/***************************************************************************/
void Conversion::Unsigned8bitFormatBufferToUnsignedBuffer32Bit(
    uint8_t *SourceBuffer, uint32_t SourceSizeBuffer, uint32_t *OutputBuffer,
    uint32_t OutpuSizeBuffer) {
  uint32_t DestinationBuffer = 0;
  OutpuSizeBuffer = SourceSizeBuffer / 4;
  for (uint32_t i = 0; i < OutpuSizeBuffer; i++) {
    OutputBuffer[i] = SourceBuffer[DestinationBuffer] |
                      SourceBuffer[DestinationBuffer + 1] << 8 |
                      SourceBuffer[DestinationBuffer + 2] << 16 |
                      SourceBuffer[DestinationBuffer + 3] << 24;
    DestinationBuffer += 4;
  }
}
/***************************************************************************/
