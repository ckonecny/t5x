#ifndef REALTIMEDATA_H
#define REALTIMEDATA_H

#include <arduino.h>
#include "config.h"

namespace t5x
{
  
typedef struct
{
  uint16_t      Analog[8];
  uint16_t      Channel_us[8];
  uint8_t       SwitchState[3];  // SW1, SW2, SW3
  uint8_t       ProfileId;
  uint8_t       FlightMode;
  uint16_t      FreeRAM;
  uint16_t      LoopTime;
  int16_t       FlightTimerSec;
} RealtimeData_t;
  
  
class RealtimeData 
{
  public:  
    RealtimeData_t m_Data;
 
    void send();                    // send profile settings via serial to application

  private:
};
  
  
  
} // namespace
#endif
