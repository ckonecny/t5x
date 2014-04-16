#include "util.h"
#include "TxDeviceProperties.h"
#include "Profile.h"


int freeRam () 
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}


namespace t5x
{
#define T5X_EEPROM_VERSION_ADDRESS  1000
const uint8_t gEEPROM_Version     = 0x01;

bool EEPROMVersionIsInvalid()
{
  uint8_t ver;
  EEPROM_readAnything(T5X_EEPROM_VERSION_ADDRESS, ver); 
  
  if (ver!=gEEPROM_Version)
    return true;
  else
    return false;
}

void SetValidEEPROMVersion()
{
  EEPROM_writeAnything(T5X_EEPROM_VERSION_ADDRESS, gEEPROM_Version); 
}

} // namespace
