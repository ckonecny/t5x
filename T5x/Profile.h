#ifndef PROFILE_H
#define PROFILE_H

#include <arduino.h>
#include "config.h"

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

    uint8_t       V_A1[3];    
    uint8_t       V_A2[3];
    uint16_t      Timer;
    char          ChannelOrder[9];
} Profile_t;



class Profile 
{
  public:  
    Profile_t m_Data;
    uint8_t m_Id;
 
    void send();                    // send profile settings via serial to application
    void receive(byte aMsg[]);      // decode the received byte array 
    void init();                    // initialize profile data in EEPROM with default values
    void load(uint8_t aProfileId);  // load given profile id from EEPROM to RAM
    void save(uint8_t aProfileId);  // save profile to EEPROM

  private:
};


#if defined(T5X_CONDITIONAL_INITIALIZE_EEPROM) || not defined(T5X_USE_EEPROM)
static const t5x::Profile_t gDefaultProfile =
{ 
  { 30, 50, 70,  0,  0,  0},  // AILERON EXPO [-100/+100]     Flight Mode 1 2 3 4 5 6
  { 30, 50, 70,  0,  0,  0},  // ELEVON  EXPO [-100/+100]     Flight Mode 1 2 3 4 5 6
  { 30, 50, 70,  0,  0,  0},  // RUDDER  EXPO [-100/+100]     Flight Mode 1 2 3 4 5 6
  
  {100,100,100,100,100,100},  // AILERON DUAL RATE [0/+140]   Flight Mode 1 2 3 4 5 6
  {100,100,100,100,100,100},  // ELEVON  DUAL RATE [0/+140]   Flight Mode 1 2 3 4 5 6
  {100,100,100,100,100,100},  // RUDDER  DUAL RATE [0/+140]   Flight Mode 1 2 3 4 5 6
  
  {2, 35, 33},                // TELEMETRY A1 VOLTAGE Warning Level ORANGE, RED
  {0, 0, 0},                  // TELEMETRY A2 VOLTAGE Warning Level ORANGE, RED (Note: without divider 0-3,3V in 255 steps or 0,013V per step)  
  420,                        // FLIGHT TIMER (seconds)
  "AETR123P"                  // Channel Order AIL, ELE, TRH, RUD, AUX1 (SW1), AUX2 (SW2), AUX3 (SW3), AUX4 (POT1)
};
#endif

} // namespace
#endif
