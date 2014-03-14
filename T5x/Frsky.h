#include <arduino.h>

namespace tx5
{

#define FRAMESIZE 11

class Frsky 
{
  public:
    Frsky();
    
    void update();
  
    uint8_t m_A1_Voltage;
    uint8_t m_A2_Voltage;
    uint8_t m_RSSI;

  private:
    uint8_t m_Data[FRAMESIZE];
    uint8_t m_Counter;
};

} // namespace end
