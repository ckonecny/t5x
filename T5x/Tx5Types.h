#include <arduino.h>

namespace tx5
{

typedef struct
{
    int8_t        AilExpo[3];
    int8_t        EleExpo[3];
    int8_t        RudExpo[3];
    uint8_t       AilDR[3];
    uint8_t       EleDR[3];
    uint8_t       RudDR[3];

    uint8_t       V_A1[2];    // The internal sensor has a 4:1 divider, so the value is 0-13,2V in 255 steps or 0,052V per step. 0...warning, 1...emergency
    uint8_t       V_A2[2];    // A2 without divider is 0-3,3V in 255 steps or 0,013V per step.                                   0...warning, 1...emergency
    uint16_t      Timer;      // flight timer     
} Profile_t;


typedef struct
{
  uint16_t Calibration[3];
  boolean Reverse;
} AnalogSettings_t;

} // namespace end
