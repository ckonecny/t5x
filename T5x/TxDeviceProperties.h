#ifndef TXDEVICEPROPERTIES_H
#define TXDEVICEPROPERTIES_H

#include <arduino.h>
#include "config.h"

namespace t5x
{


typedef struct
{
  struct AnalogSettings_t
  {
    uint16_t Calibration[3];
    boolean Reverse;
  } AnalogSettings[8];
  
  
  struct SwitchSettings_t
  {
    boolean Reverse;
  } SwitchSettings[3]; 
  
  struct TelemetrySettings_t
  {
    uint8_t   V_TX[3];                             // Cellcount, Orange, Red Level
    uint8_t   RSSIPercent[2];                      // Orange, Red Level            
    uint8_t   Check_Interval;                      // seconds 0-255
  } TelemetrySettings; 
  
  uint8_t     FlightTimeTrigger_ThrottlePercent;   // 0-100%                       WAS: absolute value before (attention, was negative value!)
  int16_t     VFMSteps[6];
  boolean     Sw2SelectsFlightMode;                // true:  SW2 selects flight mode
                                                   // false: SW3 selects flight mode
                                                   //  note: when using virtual flight mode switch, also bi-state switch SW1 will contribute
  boolean     Sw2IsPrimaryProfileSelector;         // true:  SW2+3*SW3 SW2:[0,1,2] + SW3:[0,3,6] = 0-8 
                                                   // false: SW3+3*SW2 SW3:[0,1,2] + SW2:[0,3,6] = 0-8
} T5xDeviceProperties_t;





class TxDeviceProperties 
{
  public:  
    T5xDeviceProperties_t m_Properties;
 
    void send();
    void receive(byte aMsg[]);      // decode the received byte array     
    void init();                    // initialize Device Properties in EEPROM with default data
    void load();
    void save();
};



#if defined(T5X_CONDITIONAL_INITIALIZE_EEPROM) || not defined(T5X_USE_EEPROM)
const t5x::T5xDeviceProperties_t gDefaultDeviceSettings=
{
  {                                   //    Calibration     ChannelReverse  Comment
    {{0 ,   512, 1023}, true},        //A0 {MIN, MID, MAX}, ChannelReverse  AIL
    {{0 ,   512, 1023}, false},       //A1 {MIN, MID, MAX}, ChannelReverse  ELE
    {{0 ,   512, 1023}, true},        //A2 {MIN, MID, MAX}, ChannelReverse  THR
    {{0 ,   512, 1023}, true},        //A3 {MIN, MID, MAX}, ChannelReverse  RUD
    {{0 ,   512, 1023}, true},        //A4 {MIN, MID, MAX}, ChannelReverse  reserved for I2C SDA, no need for calibration 
    {{0 ,   512, 1023}, true},        //A5 {MIN, MID, MAX}, ChannelReverse  reserved for I2C SCL, no need for calibration
    {{0 ,   512, 1023}, true},        //A6 {MIN, MID, MAX}, ChannelReverse  Potentiometer
    {{0 ,   512, 1023}, true}         //A7 {MIN, MID, MAX}, ChannelReverse  voltage sensor, no need for calibration  
  },
  {
    {false},                          // SW1  Reverse
    {false},                          // SW2  Reverse
    {false},                          // SW3  Reverse
  },
  {
    { 4,  12,     11},                // TX Voltage Monitoring: CellCount, Orange, Red Level
    {     40,     30},                // RSSI Percentage: Orange, Red Level
    10,                               // Telemetry Check Interval in seconds
  },
  20,                                 // Flight Timer Throttle threshold percentage
  { -256, -110, -40, 256, 110, 40},   // VFM Steps
  false,
  false
};
#endif

} // namespace end

#endif
