#include "T5xTypes.h"



const t5x::Profile_t cfg_Profile[] =
{
 {                ///////////////////// PROFILE 1 ////////////////////////////////////////////////////////////////////////
  {0,0,0},        // AILERON EXPO [-100/+100]     Flight Mode 1 2 3 
  {0,0,0},        // ELEVON  EXPO [-100/+100]     Flight Mode 1 2 3 
  {0,0,0},        // RUDDER  EXPO [-100/+100]     Flight Mode 1 2 3 

  {100,100,100},  // AILERON DUAL RATE [0/+140]   Flight Mode 1 2 3 
  {100,100,100},  // ELEVON  DUAL RATE [0/+140]   Flight Mode 1 2 3 
  {100,100,100},  // RUDDER  DUAL RATE [0/+140]   Flight Mode 1 2 3 

  {2*3.5, 2*3.3}, // TELEMETRY A1 VOLTAGE Warning Level ORANGE, RED
  {0,0},          // TELEMETRY A2 VOLTAGE Warning Level ORANGE, RED (Note: without divider 0-3,3V in 255 steps or 0,013V per step)  
  600,            // FLIGHT TIMER (seconds)
  "AETR123P"      // Channel Order AIL, ELE, TRH, RUD, AUX1 (SW1), AUX2 (SW2), AUX3 (SW3), AUX4 (POT1)
 },               ////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 {                ///////////////////// PROFILE 2 ////////////////////////////////////////////////////////////////////////
  {0,0,0},        // AILERON EXPO [-100/+100]     Flight Mode 1 2 3 
  {0,0,0},        // ELEVON  EXPO [-100/+100]     Flight Mode 1 2 3 
  {0,0,0},        // RUDDER  EXPO [-100/+100]     Flight Mode 1 2 3 

  {100,100,100},  // AILERON DUAL RATE [0/+140]   Flight Mode 1 2 3 
  {100,100,100},  // ELEVON  DUAL RATE [0/+140]   Flight Mode 1 2 3 
  {100,100,100},  // RUDDER  DUAL RATE [0/+140]   Flight Mode 1 2 3 

  {0.0, 0.0},     // TELEMETRY A1 VOLTAGE Warning Level ORANGE, RED
  {0.0 ,0.0},     // TELEMETRY A2 VOLTAGE Warning Level ORANGE, RED (Note: without divider 0-3,3V in 255 steps or 0,013V per step)  
  600,            // FLIGHT TIMER (seconds)
  "AETR123P"      // Channel Order AIL, ELE, TRH, RUD, AUX1 (SW1), AUX2 (SW2), AUX3 (SW3), AUX4 (POT1)
 },               ////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 {                ///////////////////// PROFILE 3 ////////////////////////////////////////////////////////////////////////
  {0, 30, 50},    // AILERON EXPO [-100/+100]     Flight Mode 1 2 3 
  {0, 30, 50},    // ELEVON  EXPO [-100/+100]     Flight Mode 1 2 3 
  {0, 50, 70},    // RUDDER  EXPO [-100/+100]     Flight Mode 1 2 3 

  {100,100,100},  // AILERON DUAL RATE [0/+140]   Flight Mode 1 2 3 
  {100,100,100},  // ELEVON  DUAL RATE [0/+140]   Flight Mode 1 2 3 
  {100,100,100},  // RUDDER  DUAL RATE [0/+140]   Flight Mode 1 2 3 

  {0.0, 0.0},     // TELEMETRY A1 VOLTAGE Warning Level ORANGE, RED
  {0.0 ,0.0},     // TELEMETRY A2 VOLTAGE Warning Level ORANGE, RED (Note: without divider 0-3,3V in 255 steps or 0,013V per step)  
  600,            // FLIGHT TIMER (seconds)
  "AETR123P"      // Channel Order AIL, ELE, TRH, RUD, AUX1 (SW1), AUX2 (SW2), AUX3 (SW3), AUX4 (POT1)
 },               ////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 {                ///////////////////// PROFILE 4 ////////////////////////////////////////////////////////////////////////
  {0,0,0},        // AILERON EXPO [-100/+100]     Flight Mode 1 2 3 
  {0,0,0},        // ELEVON  EXPO [-100/+100]     Flight Mode 1 2 3 
  {0,0,0},        // RUDDER  EXPO [-100/+100]     Flight Mode 1 2 3 

  {100,100,100},  // AILERON DUAL RATE [0/+140]   Flight Mode 1 2 3 
  {100,100,100},  // ELEVON  DUAL RATE [0/+140]   Flight Mode 1 2 3 
  {100,100,100},  // RUDDER  DUAL RATE [0/+140]   Flight Mode 1 2 3 

  {0.0, 0.0},     // TELEMETRY A1 VOLTAGE Warning Level ORANGE, RED
  {0.0 ,0.0},     // TELEMETRY A2 VOLTAGE Warning Level ORANGE, RED (Note: without divider 0-3,3V in 255 steps or 0,013V per step)  
  600,            // FLIGHT TIMER (seconds)
  "AETR123P"      // Channel Order AIL, ELE, TRH, RUD, AUX1 (SW1), AUX2 (SW2), AUX3 (SW3), AUX4 (POT1)
 },               ////////////////////////////////////////////////////////////////////////////////////////////////////////
  
 {                ///////////////////// PROFILE 5 ////////////////////////////////////////////////////////////////////////
  {0,0,0},        // AILERON EXPO [-100/+100]     Flight Mode 1 2 3 
  {0,0,0},        // ELEVON  EXPO [-100/+100]     Flight Mode 1 2 3 
  {0,0,0},        // RUDDER  EXPO [-100/+100]     Flight Mode 1 2 3 

  {100,100,100},  // AILERON DUAL RATE [0/+140]   Flight Mode 1 2 3 
  {100,100,100},  // ELEVON  DUAL RATE [0/+140]   Flight Mode 1 2 3 
  {100,100,100},  // RUDDER  DUAL RATE [0/+140]   Flight Mode 1 2 3 

  {0.0, 0.0},     // TELEMETRY A1 VOLTAGE Warning Level ORANGE, RED
  {0.0 ,0.0},     // TELEMETRY A2 VOLTAGE Warning Level ORANGE, RED (Note: without divider 0-3,3V in 255 steps or 0,013V per step)  
  600,            // FLIGHT TIMER (seconds)
  "AETR123P"      // Channel Order AIL, ELE, TRH, RUD, AUX1 (SW1), AUX2 (SW2), AUX3 (SW3), AUX4 (POT1)
 },               ////////////////////////////////////////////////////////////////////////////////////////////////////////
  
 {                ///////////////////// PROFILE 6 ////////////////////////////////////////////////////////////////////////
  {0,0,0},        // AILERON EXPO [-100/+100]     Flight Mode 1 2 3 
  {0,0,0},        // ELEVON  EXPO [-100/+100]     Flight Mode 1 2 3 
  {0,0,0},        // RUDDER  EXPO [-100/+100]     Flight Mode 1 2 3 

  {100,100,100},  // AILERON DUAL RATE [0/+140]   Flight Mode 1 2 3 
  {100,100,100},  // ELEVON  DUAL RATE [0/+140]   Flight Mode 1 2 3 
  {100,100,100},  // RUDDER  DUAL RATE [0/+140]   Flight Mode 1 2 3 

  {0.0, 0.0},     // TELEMETRY A1 VOLTAGE Warning Level ORANGE, RED
  {0.0 ,0.0},     // TELEMETRY A2 VOLTAGE Warning Level ORANGE, RED (Note: without divider 0-3,3V in 255 steps or 0,013V per step)  
  600,            // FLIGHT TIMER (seconds)
  "AETR123P"      // Channel Order AIL, ELE, TRH, RUD, AUX1 (SW1), AUX2 (SW2), AUX3 (SW3), AUX4 (POT1)
 },               ////////////////////////////////////////////////////////////////////////////////////////////////////////
 
  
 {                ///////////////////// PROFILE 7 ////////////////////////////////////////////////////////////////////////
  {0,0,0},        // AILERON EXPO [-100/+100]     Flight Mode 1 2 3 
  {0,0,0},        // ELEVON  EXPO [-100/+100]     Flight Mode 1 2 3 
  {0,0,0},        // RUDDER  EXPO [-100/+100]     Flight Mode 1 2 3 

  {100,100,100},  // AILERON DUAL RATE [0/+140]   Flight Mode 1 2 3 
  {100,100,100},  // ELEVON  DUAL RATE [0/+140]   Flight Mode 1 2 3 
  {100,100,100},  // RUDDER  DUAL RATE [0/+140]   Flight Mode 1 2 3 

  {0.0, 0.0},     // TELEMETRY A1 VOLTAGE Warning Level ORANGE, RED
  {0.0 ,0.0},     // TELEMETRY A2 VOLTAGE Warning Level ORANGE, RED (Note: without divider 0-3,3V in 255 steps or 0,013V per step)  
  600,            // FLIGHT TIMER (seconds)
  "AETR123P"      // Channel Order AIL, ELE, TRH, RUD, AUX1 (SW1), AUX2 (SW2), AUX3 (SW3), POT1
 },               ////////////////////////////////////////////////////////////////////////////////////////////////////////
  
 {                ///////////////////// PROFILE 8 ////////////////////////////////////////////////////////////////////////
  {0,0,0},        // AILERON EXPO [-100/+100]     Flight Mode 1 2 3 
  {0,0,0},        // ELEVON  EXPO [-100/+100]     Flight Mode 1 2 3 
  {0,0,0},        // RUDDER  EXPO [-100/+100]     Flight Mode 1 2 3 

  {100,100,100},  // AILERON DUAL RATE [0/+140]   Flight Mode 1 2 3 
  {100,100,100},  // ELEVON  DUAL RATE [0/+140]   Flight Mode 1 2 3 
  {100,100,100},  // RUDDER  DUAL RATE [0/+140]   Flight Mode 1 2 3 

  {0.0, 0.0},     // TELEMETRY A1 VOLTAGE Warning Level ORANGE, RED
  {0.0 ,0.0},     // TELEMETRY A2 VOLTAGE Warning Level ORANGE, RED (Note: without divider 0-3,3V in 255 steps or 0,013V per step)  
  600,            // FLIGHT TIMER (seconds)
  "AETR123P"      // Channel Order AIL, ELE, TRH, RUD, AUX1 (SW1), AUX2 (SW2), AUX3 (SW3), POT1
 },               ////////////////////////////////////////////////////////////////////////////////////////////////////////
  
 {                ///////////////////// PROFILE 9 ////////////////////////////////////////////////////////////////////////
  {0,0,0},        // AILERON EXPO [-100/+100]     Flight Mode 1 2 3 
  {0,0,0},        // ELEVON  EXPO [-100/+100]     Flight Mode 1 2 3 
  {0,0,0},        // RUDDER  EXPO [-100/+100]     Flight Mode 1 2 3 

  {100,100,100},  // AILERON DUAL RATE [0/+140]   Flight Mode 1 2 3 
  {100,100,100},  // ELEVON  DUAL RATE [0/+140]   Flight Mode 1 2 3 
  {100,100,100},  // RUDDER  DUAL RATE [0/+140]   Flight Mode 1 2 3 

  {0.0, 0.0},     // TELEMETRY A1 VOLTAGE Warning Level ORANGE, RED
  {0.0 ,0.0},     // TELEMETRY A2 VOLTAGE Warning Level ORANGE, RED (Note: without divider 0-3,3V in 255 steps or 0,013V per step)  
  600,            // FLIGHT TIMER (seconds)
  "AETR123P"      // Channel Order AIL, ELE, TRH, RUD, AUX1 (SW1), AUX2 (SW2), AUX3 (SW3), POT1
 }                ////////////////////////////////////////////////////////////////////////////////////////////////////////
};

const float     cfg_V_TX[] =                       { 4*1.15,  4*1.1};   // TX Voltage Warning Level ORANGE, RED                              
const uint8_t   cfg_RSSI[] =                       {40  , 30  };        // receiver signal strength indicator [0-127] Warning Level ORANGE, RED
const uint16_t  cfg_Telemetry_Check_Interval =             8000;        // Tx Voltage, RSSI, A1 Voltage & A2 Voltage are to be checked every XXX ms. 
const int16_t   cfg_FlightTimeTrigger_ThrottleVal =        -200;        // Throttle Value that triggers the Flight Timer


// use the AnalogReadSerial.ino sketch to determine the MIN, MID and MAX values for the main analog inputs
const t5x::AnalogSettings_t cfg_AnalogSettings[]=
{                                   //    Calibration     ChannelReverse  Comment
  {{93,   520,  965}, true},        //A0 {MIN, MID, MAX}, ChannelReverse  AIL
  {{35,   493,  937}, false},       //A1 {MIN, MID, MAX}, ChannelReverse  ELE
  {{26,   510,  920}, true},        //A2 {MIN, MID, MAX}, ChannelReverse  THR
  {{83,   500,  950}, true},        //A3 {MIN, MID, MAX}, ChannelReverse  RUD
  {{0 ,     0,    0}, true},        //A4 {MIN, MID, MAX}, ChannelReverse  reserved for I2C SDA, no need for calibration 
  {{0 ,     0,    0}, true},        //A5 {MIN, MID, MAX}, ChannelReverse  reserved for I2C SCL, no need for calibration
  {{0 ,   512, 1023}, true},        //A6 {MIN, MID, MAX}, ChannelReverse  Potentiometer
  {{0 ,     0,   0 }, true}         //A7 {MIN, MID, MAX}, ChannelReverse  voltage sensor, no need for calibration  
};


// in case switches should work in the opposite direction, you can simply configure that here. no need to open the case or resolder something...
const t5x::SwitchSettings_t cfg_SwitchSettings[]=
{ 
  {false},                         // SW1  Reverse
  {false},                         // SW2  Reverse
  {false}                          // SW3  Reverse
};


// which of the 2 3-pos switches SW2 or SW3 is the primary one for selecting the active profile?
//#define T5X_PROFILE_SW2_PRIMARY        // switch state 0-2. SW2+3*SW3 SW2:[0,1,2] + SW3:[0,3,6] 
#define T5X_PROFILE_SW3_PRIMARY          // switch state 0-2. SW3+3*SW2 SW3:[0,1,2] + SW2:[0,3,6]

// choose one from the two 3-state switches SW2 or SW3 which one should be evaluated for selecting active flightmode
//#define T5X_SW2_SELECTS_FLIGHTMODE     // SW2 selects the active flightmode during normal operation
#define T5X_SW3_SELECTS_FLIGHTMODE       // SW3 selects the active flightmode during normal operation


// this should never be necessary to be changed
#define T5X_TX_VOLT_PIN    A7        // voltage sensor on A7 
#define T5X_TX_BUZZER_PIN   8        // buzzer connected to digital pin 8
#define T5X_TX_LED_PIN     13        // LED is on standard pin 13

// enable the below to use pointer calculation instead of String.indexOf
#define T5X_USE_LESS_ROM_FOR_CHANNEL_ORDER_EVALUATION


// check if preprocessor settings make sense, or generate error just in case of nonsense
#if defined(T5X_PROFILE_SW2_PRIMARY) && defined(T5X_PROFILE_SW3_PRIMARY)
	#error Cannot use T5X_PROFILE_SW2_PRIMARY in combination with T5X_PROFILE_SW3_PRIMARY
#endif

#if !defined(T5X_PROFILE_SW2_PRIMARY) && !defined(T5X_PROFILE_SW3_PRIMARY)
	#error Neither T5X_PROFILE_SW2_PRIMARY nor T5X_PROFILE_SW3_PRIMARY is used
#endif



#if defined(T5X_SW2_SELECTS_FLIGHTMODE) && defined(T5X_SW3_SELECTS_FLIGHTMODE)
	#error Cannot use T5X_SW2_SELECTS_FLIGHTMODE in combination with T5X_SW3_SELECTS_FLIGHTMODE
#endif

#if !defined(T5X_SW2_SELECTS_FLIGHTMODE) && !defined(T5X_SW3_SELECTS_FLIGHTMODE)
	#error Neither T5X_SW2_SELECTS_FLIGHTMODE nor T5X_SW3_SELECTS_FLIGHTMODE is used
#endif
