#include <stdint.h>

#ifndef Conversion_HELPER
#define Conversion_HELPER

#ifdef __cplusplus
extern "C" {
#endif

namespace Conversion {
void WordToByte(uint16_t &Source, uint8_t &Dest1, uint8_t &Dest2);
void ByteToWord(uint16_t &Source, uint8_t &Dest1, uint8_t &Dest2);
void SWordToByte(uint16_t &Source, uint8_t &Dest1, uint8_t &Dest2);
void ByteToSWord(uint16_t &Source, uint8_t &Dest1, uint8_t &Dest2);
void QWordToByte(uint64_t &Source, uint8_t &Dest1, uint8_t &Dest2,
                 uint8_t &Dest3, uint8_t &Dest4, uint8_t &Dest5, uint8_t &Dest6,
                 uint8_t &Dest7, uint8_t &Dest8);
void DWordToByte(uint32_t &Source, uint8_t &Dest1, uint8_t &Dest2,
                 uint8_t &Dest3, uint8_t &Dest4);
void ByteToDWord(uint32_t &Source, uint8_t &Dest1, uint8_t &Dest2,
                 uint8_t &Dest3, uint8_t &Dest4);
void ByteTo7Bit(uint8_t &Source, uint8_t &Dest1, uint8_t &Dest2);
void Bit7ToByte(uint8_t &Source, uint8_t &Dest1, uint8_t &Dest2);
void WordTo7Bit(uint16_t &Source, uint8_t &Dest1, uint8_t &Dest2,
                uint8_t &Dest3, uint8_t &Dest4);
void Bit7ToWord(uint16_t &Source, uint8_t &Dest1, uint8_t &Dest2,
                uint8_t &Dest3, uint8_t &Dest4);
void DWordTo7Bit(uint32_t &Source, uint8_t &Dest1, uint8_t &Dest2,
                 uint8_t &Dest3, uint8_t &Dest4, uint8_t &Dest5, uint8_t &Dest6,
                 uint8_t &Dest7, uint8_t &Dest8);
void Bit7ToDWord(uint32_t &Source, uint8_t &Dest1, uint8_t &Dest2,
                 uint8_t &Dest3, uint8_t &Dest4, uint8_t &Dest5, uint8_t &Dest6,
                 uint8_t &Dest7, uint8_t &Dest8);
void QWordTo7Bit(uint64_t &Source, uint8_t &Dest1, uint8_t &Dest2,
                 uint8_t &Dest3, uint8_t &Dest4, uint8_t &Dest5, uint8_t &Dest6,
                 uint8_t &Dest7, uint8_t &Dest8, uint8_t &Dest9,
                 uint8_t &Dest10, uint8_t &Dest11, uint8_t &Dest12,
                 uint8_t &Dest13, uint8_t &Dest14, uint8_t &Dest15,
                 uint8_t &Dest16);
void Bit7ToQWord(uint64_t &Source, uint8_t &Dest1, uint8_t &Dest2,
                 uint8_t &Dest3, uint8_t &Dest4, uint8_t &Dest5, uint8_t &Dest6,
                 uint8_t &Dest7, uint8_t &Dest8, uint8_t &Dest9,
                 uint8_t &Dest10, uint8_t &Dest11, uint8_t &Dest12,
                 uint8_t &Dest13, uint8_t &Dest14, uint8_t &Dest15,
                 uint8_t &Dest16);
void FloatTo7Bit(float &Source, uint8_t &Dest1, uint8_t &Dest2, uint8_t &Dest3,
                 uint8_t &Dest4, uint8_t &Dest5, uint8_t &Dest6, uint8_t &Dest7,
                 uint8_t &Dest8);
void Bit7ToFloat(float &Source, uint8_t &Dest1, uint8_t &Dest2, uint8_t &Dest3,
                 uint8_t &Dest4, uint8_t &Dest5, uint8_t &Dest6, uint8_t &Dest7,
                 uint8_t &Dest8);
void Signed8BitToUnsigned7bitFormat(int8_t &Source, uint8_t &Dest1,
                                    uint8_t &Dest2);
void Unsigned7bitFormaTotSigned8Bit(int8_t &Destinatation, uint8_t &Source1,
                                    uint8_t &Source2);
void Signed16BitToUnsigned7bitFormat(int16_t &Source, uint8_t &Dest1,
                                     uint8_t &Dest2, uint8_t &Dest3);
void Unsigned7bitFormaTotSigned16Bit(int16_t &Destinatation, uint8_t &Source1,
                                     uint8_t &Source2, uint8_t &Source3);

void Signed32BitToUnsigned7bitFormat(int32_t &Source, uint8_t &Dest1,
                                     uint8_t &Dest2, uint8_t &Dest3,
                                     uint8_t &Dest4, uint8_t &Dest5);
void Unsigned7bitFormaTotSigned32Bit(int32_t &Destinatation, uint8_t &Source1,
                                     uint8_t &Source2, uint8_t &Source3,
                                     uint8_t &Source4, uint8_t &Source5);

void Signed64BitToUnsigned7bitFormat(int64_t &Source, uint8_t &Dest1,
                                     uint8_t &Dest2, uint8_t &Dest3,
                                     uint8_t &Dest4, uint8_t &Dest5,
                                     uint8_t &Dest6, uint8_t &Dest7,
                                     uint8_t &Dest8, uint8_t &Dest9,
                                     uint8_t &Dest10);
void Unsigned7bitFormaTotSigned64Bit(int64_t &Destinatation, uint8_t &Source1,
                                     uint8_t &Source2, uint8_t &Source3,
                                     uint8_t &Source4, uint8_t &Source5,
                                     uint8_t &Source6, uint8_t &Source7,
                                     uint8_t &Source8, uint8_t &Source9,
                                     uint8_t &Source10);

void UnsignedBuffer32BitToUnsigned8bitFormatBuffer(uint32_t *SourceBuffer,
                                                   uint32_t SourceSizeBuffer,
                                                   uint8_t *OutputBuffer,
                                                   uint32_t OutpuSizeBuffer);
void Unsigned8bitFormatBufferToUnsignedBuffer32Bit(uint8_t *SourceBuffer,
                                                   uint32_t SourceSizeBuffer,
                                                   uint32_t *OutputBuffer,
                                                   uint32_t OutpuSizeBuffer);

}; // namespace Conversion
#ifdef __cplusplus
}
#endif
#endif
