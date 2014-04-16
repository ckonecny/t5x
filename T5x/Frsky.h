#include <arduino.h>

namespace t5x
{

#define T5X_FRSKY_TELEMETRY_FRAMESIZE 11

class Frsky 
{
  public:
    Frsky();
    
    void            update();
    const boolean   TelemetryLinkAlive();
  
    uint8_t         m_A1_Voltage;
    uint8_t         m_A2_Voltage;
    uint8_t         m_RSSI;

  private:
    uint8_t         m_Data[T5X_FRSKY_TELEMETRY_FRAMESIZE];
    uint8_t         m_Counter;
    unsigned long   m_LastValidFrameMillis;
};

} // namespace end
