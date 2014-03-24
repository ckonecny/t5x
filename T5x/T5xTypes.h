#include <arduino.h>

namespace t5x
{

// (Model) Profiles are holding model related information/configuration values. 
// T5x allows to switch between models and handle them differently
typedef struct
{
    int8_t        AilExpo[6];
    int8_t        EleExpo[6];
    int8_t        RudExpo[6];
    uint8_t       AilDR[6];
    uint8_t       EleDR[6];
    uint8_t       RudDR[6];

    float         V_A1[2];    
    float         V_A2[2];
    uint16_t      Timer;
    char          ChannelOrder[9];
} Profile_t;


typedef struct
{
  uint16_t Calibration[3];
  boolean Reverse;
} AnalogSettings_t;

typedef struct
{
  boolean Reverse;
} SwitchSettings_t;

} // namespace end
