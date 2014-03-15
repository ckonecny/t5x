#include "Tx5Types.h"



const tx5::Profile_t g_Profile[] =
{
 {                ///////////////////// PROFILE 1 ////////////////////////////////////////////////////////////////////////
  {0,0,0},        // AILERON EXPO [-100/+100]     Flight Mode 1 2 3 
  {0,0,0},        // ELEVON  EXPO [-100/+100]     Flight Mode 1 2 3 
  {0,0,0},        // RUDDER  EXPO [-100/+100]     Flight Mode 1 2 3 

  {100,100,100},  // AILERON DUAL RATE [0/+140]   Flight Mode 1 2 3 
  {100,100,100},  // ELEVON  DUAL RATE [0/+140]   Flight Mode 1 2 3 
  {100,100,100},  // RUDDER  DUAL RATE [0/+140]   Flight Mode 1 2 3 

  {7.0, 6.6},     // TELEMETRY A1 VOLTAGE Warning Level ORANGE, RED
  {0,0},          // TELEMETRY A2 VOLTAGE Warning Level ORANGE, RED (Note: without divider 0-3,3V in 255 steps or 0,013V per step)  
  600             // FLIGHT TIMER (seconds)
 },               ////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 {                ///////////////////// PROFILE 2 ////////////////////////////////////////////////////////////////////////
  {-30,-30,-30},  // AILERON EXPO [-100/+100]     Flight Mode 1 2 3 
  {-30,-30,-30},  // ELEVON  EXPO [-100/+100]     Flight Mode 1 2 3 
  {-30,-30,-30},  // RUDDER  EXPO [-100/+100]     Flight Mode 1 2 3 

  {100,100,100},  // AILERON DUAL RATE [0/+140]   Flight Mode 1 2 3 
  {100,100,100},  // ELEVON  DUAL RATE [0/+140]   Flight Mode 1 2 3 
  {100,100,100},  // RUDDER  DUAL RATE [0/+140]   Flight Mode 1 2 3 

  {0.0, 0.0},     // TELEMETRY A1 VOLTAGE Warning Level ORANGE, RED
  {0.0 ,0.0},     // TELEMETRY A2 VOLTAGE Warning Level ORANGE, RED (Note: without divider 0-3,3V in 255 steps or 0,013V per step)  
  600             // FLIGHT TIMER (seconds)
 },               ////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 {                ///////////////////// PROFILE 3 ////////////////////////////////////////////////////////////////////////
  {0,-30,-50},  // AILERON EXPO [-100/+100]     Flight Mode 1 2 3 
  {0,-30,-50},  // ELEVON  EXPO [-100/+100]     Flight Mode 1 2 3 
  {0,-30,-50},  // RUDDER  EXPO [-100/+100]     Flight Mode 1 2 3 

  {100,100,100},  // AILERON DUAL RATE [0/+140]   Flight Mode 1 2 3 
  {100,100,100},  // ELEVON  DUAL RATE [0/+140]   Flight Mode 1 2 3 
  {100,100,100},  // RUDDER  DUAL RATE [0/+140]   Flight Mode 1 2 3 

  {0.0, 0.0},     // TELEMETRY A1 VOLTAGE Warning Level ORANGE, RED
  {0.0 ,0.0},     // TELEMETRY A2 VOLTAGE Warning Level ORANGE, RED (Note: without divider 0-3,3V in 255 steps or 0,013V per step)  
  600             // FLIGHT TIMER (seconds)
 }                ////////////////////////////////////////////////////////////////////////////////////////////////////////
};

const float     g_V_TX[]={4.7, 4.5};               // TX Voltage Warning Level ORANGE, RED                              
const uint8_t   g_RSSI[]={40,30};                  // receiver signal strength indicator [0-127]
const uint16_t  g_Telemetry_Check_Interval=8000;   // Tx Voltage, RSSI, A1 Voltage & A2 Voltage are to be checked every XXX ms. 




// use the AnalogReadSerial.ino sketch to determine the min, mid and max values for each analog input
const tx5::AnalogSettings_t g_AnalogSettings[]=
{
  {{93, 520, 965}, true},        //A0 {MIN, MID, MAX}, ChannelReverse 
  {{35, 493, 937}, false},       //A1 {MIN, MID, MAX}, ChannelReverse 
  {{26, 510, 920}, true},        //A2 {MIN, MID, MAX}, ChannelReverse 
  {{83, 500, 950}, true}         //A3 {MIN, MID, MAX}, ChannelReverse 
};

#define TX_VOLT_PIN    A7        // voltage sensor on A7 
#define TX_BUZZER_PIN   8        // buzzer connected to digital pin 8
#define TX_LED_PIN     13        // LED is on standard pin 13


