#pragma once 
#include "stm32f4xx_flash.h"
#include "stm32f4xx_hash.h"
#include "stm32f4xx.h"
#include <typeinfo>
#include <string>
#include <string.h>

#define FLASH_START 0x08000000
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */



const uint16_t SectorBegin[] = {FLASH_Sector_0,FLASH_Sector_1, FLASH_Sector_2, FLASH_Sector_3,FLASH_Sector_4 , FLASH_Sector_5, FLASH_Sector_6, FLASH_Sector_7, FLASH_Sector_8, FLASH_Sector_9, FLASH_Sector_10, FLASH_Sector_11, FLASH_Sector_12, FLASH_Sector_13, FLASH_Sector_14, FLASH_Sector_15, FLASH_Sector_16, FLASH_Sector_17, FLASH_Sector_18, FLASH_Sector_19, FLASH_Sector_20, FLASH_Sector_21, FLASH_Sector_22, FLASH_Sector_23};
const uint32_t StartAddres[]  = {ADDR_FLASH_SECTOR_0,ADDR_FLASH_SECTOR_1,ADDR_FLASH_SECTOR_2,ADDR_FLASH_SECTOR_3,ADDR_FLASH_SECTOR_4,ADDR_FLASH_SECTOR_5,ADDR_FLASH_SECTOR_6,ADDR_FLASH_SECTOR_7,ADDR_FLASH_SECTOR_8,ADDR_FLASH_SECTOR_9,ADDR_FLASH_SECTOR_10,ADDR_FLASH_SECTOR_11};
class FlashIO
{
public:
  FlashIO(void);
 ~FlashIO(void);
  template <typename T> void  Write(u32 Addres, T* Data, u32 Length)
  {
        u32  it  = 0;
        u32 obit  = 0;
        u32 objcounter = Length; 
        uint8_t* Databuff = new uint8_t[sizeof(T)];
        FLASH_Unlock();        
        FLASH_EraseSector(GetSectorID(Addres), _VoltageRange);
        do
        {
          Serialize(Data[obit],Databuff);
        do{
        FLASH_ProgramByte(Addres, Databuff[it]);
        it++;
        Addres += it;
        }while(it < sizeof(T));
        obit++;                 
        }
        while(obit < objcounter );
        FLASH_Lock();
        delete[]  Databuff;
    
  }
  
  template <typename T> void  Read(u32 Addres, T* Data, u32 Length)
  {
    u32 it = 0;
    
    u32 obit = 0;
    u32 count = Length;
   
    uint8_t* Databuff = new uint8_t[sizeof(T)] ;
  
    
   do
 {  
    
 do
 {
   Databuff[it] = *(u8*)Addres;
   it++;
   Addres+=it;
  
 }while(it < sizeof(T));

  
  Data[obit] = Deserialize(Databuff, Data[0]) ;
 obit++;
 }while( obit< count);
 
  delete[]  Databuff;
  }
  
  void SetVoltageRange(uint8_t VoltageRange);
private:
   
   template <typename T>  void Serialize(T& Object,uint8_t* Output)
   {  
      memcpy(Output,(char*)&Object,sizeof(T));
  
   };
  template <typename T>   T Deserialize(uint8_t* Input, T& ObjectType)
   {
       T Object; 
      memcpy((char*)&Object,Input,sizeof(T));

         return Object;
   };
  
  
  
   bool SectorIsClean(uint8_t Sector);
   u32 GetHighAdressSector(uint8_t Sector);
   uint16_t GetSectorID(u32 Addres);
   bool _DataWriteSuccesfull;
   uint8_t   _VoltageRange;
};



 typedef  enum FileAtributes
{
  R,
  Q,
  W,
  WW,
  RW
}FA;

struct FileTable
{
  
   uint32_t  FileCount;
   uint32_t  Free;
   uint32_t  Allocated;
   char**    FileNames;
   uint32_t* FileBegin;
   uint32_t* FileEnd;
   uint32_t* FileSizes; 
   uint32_t  Size;
  
};

//class File:private:FlashIO
//{
//  
// public:
// static  File& Open( const char* Name,const char* Atributes);
////  template<typename T>  operator << T* Input;
////  template<typename T>  operator >> T* Output;
//  void Flush();
//  char* GetFileName(void);
// private:
//  char*    _Name;
//  uint8_t  _Atributes;
//  uint32_t _Adress;
//  bool ReadOnly;
//  bool WriteOnly;
//};