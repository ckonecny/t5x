#include "Frsky.h"
#include <arduino.h>


namespace t5x
{

Frsky::Frsky()
:m_Counter(0), m_A1_Voltage(0), m_A2_Voltage(0)
{
}

void Frsky::update()
{
    // Read RAW Data from FrSky
    while (Serial.available()) 
    {
      byte b = Serial.read();  

      /* 0xFD USERDATA */  /* 0xFE RSSI */
      if (b == 0x7E && m_Counter == FRAMESIZE-1 && m_Data[0] == 0x7E && m_Data[1] == 0xFE )
      {
        m_A1_Voltage = m_Data[2];
        m_A2_Voltage = m_Data[3];
        m_RSSI       = m_Data[4];        
      }
      else if (b == 0x7D) b ^= 0x20;     // Byte stuffing!
      else if (b == 0x7E) m_Counter = 0; // Start of Frames. 
     
      m_Data[m_Counter++] = b; 
    }
}




} // namespace end
