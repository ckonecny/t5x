#include <arduino.h>

namespace t5x
{

// (Model) Profiles are holding model related information/configuration values. 
// T5x allows to switch between models and handle them differently
typedef struct
{
    int8_t        AilExpo[3];
    int8_t        EleExpo[3];
    int8_t        RudExpo[3];
    uint8_t       AilDR[3];
    uint8_t       EleDR[3];
    uint8_t       RudDR[3];

    float         V_A1[2];    
    float         V_A2[2];
    uint16_t      Timer;
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
