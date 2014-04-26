/*****************************************************************************
  *                                                                           
  *  Copyright (c) 2014 Christian Konecny
  *  Kudos to www.der-frickler.net who started with that project on fpv-community.de                   
  *                                                                           
  *                                                                           
  *  This library is free software; you can redistribute it and/or modify it  
  *  under the terms of the GNU Lesser General Public License as published    
  *  by the Free Software Foundation; either version 2 of the License, or     
  *  (at your option) any later version.                                      
  *                                                                           
  *  This software is distributed in the hope that it will be useful, but     
  *  WITHOUT ANY WARRANTY; without even the implied warranty of               
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU        
  *  Lesser General Public License for more details.                          
  *                                                                           
  *  You should have received a copy of the GNU Lesser General Public         
  *  License along with this library; if not, write to the Free Software      
  *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA  
  *                                                                           
  *****************************************************************************
  *  T5x - an arduino based simple RC transmitter  
  *
  *  see more at:  
  *  https://github.com/ckonecny/t5x  
  *
  *  Based on the ArduinoRCLib transmitter example.
  *  Website: http://sourceforge.net/p/arduinorclib/                                                                     
  *                                                                             
  *****************************************************************************/

#include <AIPin.h>
#include <BiStateSwitch.h>
#include <TriStateSwitch.h>
#include <AnalogSwitch.h>
#include <Channel.h>
#include <DualRates.h>
#include <Expo.h>
#include <InputToOutputPipe.h>
#include <PPMOut.h>
#include <ThrottleHold.h>
#include <Timer1.h>
#include <util.h>
#include <Buzzer.h>
#include <Timer2.h>
#include <FlightTimer.h>
#include <arduino.h>
#include <EEPROM.h>

// t5x includes
#include "TxDeviceProperties.h"
#include "Profile.h"
#include "RealtimeData.h"
#include "config.h"
#include "Frsky.h"
#include "util.h"



///////////////////////////////////////////////////////////////////////
// Transmitter Settings
///////////////////////////////////////////////////////////////////////
enum {ChannelCount = 8};

/////////// Analog Pins /////////////
rc::AIPin g_aPins[4] = 
{
	rc::AIPin(A0, rc::Input_AIL), // we have to specify an input pin
	rc::AIPin(A1, rc::Input_ELE), // and we can optionally specify an index in the centralized
	rc::AIPin(A2, rc::Input_THR), // input buffer where results should be written to
	rc::AIPin(A3, rc::Input_RUD)
};

////////// Potentiometer ///////////////
rc::AIPin g_Pot1(A6,rc::Input_POT1);  // Potentiometer on A6


///////////// Switches /////////////////
rc::BiStateSwitch  g_SW1(3,    rc::Switch_A);
rc::AnalogSwitch   g_AnalogSW1(rc::Switch_A, rc::Input_SW1);

rc::TriStateSwitch g_SW2(4, 5, rc::Switch_B);
rc::AnalogSwitch   g_AnalogSW2(rc::Switch_B, rc::Input_SW2);

rc::TriStateSwitch g_SW3(6, 7, rc::Switch_C);
rc::AnalogSwitch   g_AnalogSW3(rc::Switch_C, rc::Input_SW3);


///////////// EXPO /////////////////
rc::Expo g_ailExpo[6] = {rc::Expo(0, rc::Input_AIL), rc::Expo(0, rc::Input_AIL), rc::Expo(0, rc::Input_AIL), rc::Expo(0, rc::Input_AIL), rc::Expo(0, rc::Input_AIL), rc::Expo(0, rc::Input_AIL)}; // also specify what index of the input
rc::Expo g_eleExpo[6] = {rc::Expo(0, rc::Input_ELE), rc::Expo(0, rc::Input_ELE), rc::Expo(0, rc::Input_ELE), rc::Expo(0, rc::Input_ELE), rc::Expo(0, rc::Input_ELE), rc::Expo(0, rc::Input_ELE)}; // buffer the expo should work on 
rc::Expo g_rudExpo[6] = {rc::Expo(0, rc::Input_RUD), rc::Expo(0, rc::Input_RUD), rc::Expo(0, rc::Input_RUD), rc::Expo(0, rc::Input_RUD), rc::Expo(0, rc::Input_RUD), rc::Expo(0, rc::Input_RUD)};

/////////// Dual Rate //////////////
rc::DualRates g_ailDR[6] = {rc::DualRates(100, rc::Input_AIL), rc::DualRates(100, rc::Input_AIL), rc::DualRates(100, rc::Input_AIL), rc::DualRates(100, rc::Input_AIL), rc::DualRates(100, rc::Input_AIL), rc::DualRates(100, rc::Input_AIL)}; // also specify what index of the input
rc::DualRates g_eleDR[6] = {rc::DualRates(100, rc::Input_ELE), rc::DualRates(100, rc::Input_ELE), rc::DualRates(100, rc::Input_ELE), rc::DualRates(100, rc::Input_ELE), rc::DualRates(100, rc::Input_ELE), rc::DualRates(100, rc::Input_ELE)}; // buffer the dual rates
rc::DualRates g_rudDR[6] = {rc::DualRates(100, rc::Input_RUD), rc::DualRates(100, rc::Input_RUD), rc::DualRates(100, rc::Input_RUD), rc::DualRates(100, rc::Input_RUD), rc::DualRates(100, rc::Input_RUD), rc::DualRates(100, rc::Input_RUD)}; // should work on


// Set up pipes for direct input to output copying
rc::InputToOutputPipe g_aileron( rc::Input_AIL, rc::Output_AIL1);
rc::InputToOutputPipe g_elevator(rc::Input_ELE, rc::Output_ELE1);
rc::InputToOutputPipe g_throttle(rc::Input_THR, rc::Output_THR1);
rc::InputToOutputPipe g_rudder(  rc::Input_RUD, rc::Output_RUD1);
rc::InputToOutputPipe g_aux1(    rc::Input_SW1, rc::Output_AUX1); // SW1
rc::InputToOutputPipe g_aux2(    rc::Input_SW2, rc::Output_AUX2); // SW2
rc::InputToOutputPipe g_aux3(    rc::Input_SW3, rc::Output_AUX3); // SW3
rc::InputToOutputPipe g_aux4(    rc::Input_POT1,rc::Output_AUX4); // Potentiometer


////////// Channel Order ///////////
rc::Channel g_channels[ChannelCount] =
{
  	rc::Channel(rc::Output_None,  rc::OutputChannel_1),
	rc::Channel(rc::Output_None,  rc::OutputChannel_2),
	rc::Channel(rc::Output_None,  rc::OutputChannel_3),
	rc::Channel(rc::Output_None,  rc::OutputChannel_4),
	rc::Channel(rc::Output_None,  rc::OutputChannel_5),  
	rc::Channel(rc::Output_None,  rc::OutputChannel_6),  
	rc::Channel(rc::Output_None,  rc::OutputChannel_7),  
        rc::Channel(rc::Output_None,  rc::OutputChannel_8)   
};

// define PPM for the given amount of channels 
rc::PPMOut g_PPMOut(ChannelCount);


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
t5x::TxDeviceProperties gTxDevice;
t5x::Profile            gProfile;
t5x::RealtimeData       gRealtime;
t5x::Frsky              g_Frsky;                // global frsky telemetry object 

rc::FlightTimer         gTimer;                // global flight timer
int16_t                 gTimerSecAtPaused = 0; // to start a new timer after pause

unsigned long           now                = 0; // for scheduling
unsigned long           last               = 0; // measure loop time
unsigned long           last_telemetry     = 0; // for scheduling
unsigned long           last_flight_timer  = 0; // to create a new timer after pause
unsigned long           last_realtime_data = 0; // for setup mode only

byte                    gRxBuffer[100];         // Receive Buffer
uint8_t                 byteCount          = 0; // reveived bytes


enum OperatingMode_t
{
   OperatingMode_Normal,
   OperatingMode_Setup
};  

OperatingMode_t g_OperatingMode   = OperatingMode_Normal;

int8_t getChannelPosition(char aChar)
// return the channel position of the given character as per definition in the model profile
// if not found, return -
{
  char* pChar = strchr(gProfile.m_Data.ChannelOrder, aChar);
  if (pChar!=NULL) return int(pChar)-int(gProfile.m_Data.ChannelOrder);
  else return -1;
}



void applyDeviceSettings()
{
    // initialize switches working direction. maybe user wants to let them work in the other direction
    g_SW1.setReverse(gTxDevice.m_Properties.SwitchSettings[0].Reverse);
    g_SW2.setReverse(gTxDevice.m_Properties.SwitchSettings[1].Reverse);
    g_SW3.setReverse(gTxDevice.m_Properties.SwitchSettings[2].Reverse);
    
    // set calibration values, these depend on hardware configurations
    for(int i=0; i<4; i++)  // calibrate/reverse gimbals for AIL, ELE, THR, RUD
    {
        g_aPins[i].setCalibration(gTxDevice.m_Properties.AnalogSettings[i].Calibration[0], gTxDevice.m_Properties.AnalogSettings[i].Calibration[1],  gTxDevice.m_Properties.AnalogSettings[i].Calibration[2]);
        g_aPins[i].setReverse(gTxDevice.m_Properties.AnalogSettings[i].Reverse);  
	}
	
    g_Pot1.setCalibration(gTxDevice.m_Properties.AnalogSettings[6].Calibration[0], gTxDevice.m_Properties.AnalogSettings[6].Calibration[1],  gTxDevice.m_Properties.AnalogSettings[6].Calibration[2]);
    g_Pot1.setReverse(gTxDevice.m_Properties.AnalogSettings[6].Reverse);      
}


void applyProfile()
{
    int8_t j=getChannelPosition('A'); if (j>-1) g_channels[j].setSource(rc::Output_AIL1);
           j=getChannelPosition('E'); if (j>-1) g_channels[j].setSource(rc::Output_ELE1);
           j=getChannelPosition('T'); if (j>-1) g_channels[j].setSource(rc::Output_THR1);
           j=getChannelPosition('R'); if (j>-1) g_channels[j].setSource(rc::Output_RUD1);
           j=getChannelPosition('1'); if (j>-1) g_channels[j].setSource(rc::Output_AUX1);
           j=getChannelPosition('2'); if (j>-1) g_channels[j].setSource(rc::Output_AUX2);
           j=getChannelPosition('3'); if (j>-1) g_channels[j].setSource(rc::Output_AUX3);
           j=getChannelPosition('P'); if (j>-1) g_channels[j].setSource(rc::Output_AUX4);

    // initialize expo and dualrate objects with the profile specific values
    for (uint8_t i=0; i < 6; i++)
    {
        g_ailExpo[i].set(gProfile.m_Data.AilExpo[i]);
        g_eleExpo[i].set(gProfile.m_Data.EleExpo[i]);
        g_rudExpo[i].set(gProfile.m_Data.RudExpo[i]);
          g_ailDR[i].set(gProfile.m_Data.AilDR[i]  );
          g_eleDR[i].set(gProfile.m_Data.EleDR[i]  );
          g_rudDR[i].set(gProfile.m_Data.RudDR[i]  );
    }
    
    // fill channel values buffer with same values, all centered
    j=getChannelPosition('A'); if (j>-1) rc::setOutputChannel(rc::OutputChannel(j), rc::normalizedToMicros(0));
    j=getChannelPosition('E'); if (j>-1) rc::setOutputChannel(rc::OutputChannel(j), rc::normalizedToMicros(0));
    j=getChannelPosition('T'); if (j>-1) rc::setOutputChannel(rc::OutputChannel(j), rc::normalizedToMicros(-256));
    j=getChannelPosition('R'); if (j>-1) rc::setOutputChannel(rc::OutputChannel(j), rc::normalizedToMicros(0));
    j=getChannelPosition('1'); if (j>-1) rc::setOutputChannel(rc::OutputChannel(j), rc::normalizedToMicros(0));
    j=getChannelPosition('2'); if (j>-1) rc::setOutputChannel(rc::OutputChannel(j), rc::normalizedToMicros(0));
    j=getChannelPosition('3'); if (j>-1) rc::setOutputChannel(rc::OutputChannel(j), rc::normalizedToMicros(0));
    j=getChannelPosition('P'); if (j>-1) rc::setOutputChannel(rc::OutputChannel(j), rc::normalizedToMicros(0));
    j=getChannelPosition('M'); if (j>-1) rc::setOutputChannel(rc::OutputChannel(j), rc::normalizedToMicros(0));
    j=getChannelPosition('-'); if (j>-1) rc::setOutputChannel(rc::OutputChannel(j), rc::normalizedToMicros(0));        
    
    gTimer.setTarget(gProfile.m_Data.Timer);
    gTimer.setDirection(false);                     // count down timer
  
}

void setup()
{
  	// Initialize timer
	rc::Timer1::init();
	rc::Timer2::init();

        Serial.begin(9600);    // telemetry/configuration

#ifdef T5X_CONDITIONAL_INITIALIZE_EEPROM        
        if (t5x::EEPROMVersionIsInvalid())
        {
          gTxDevice.init();
          gProfile.init();
          t5x::SetValidEEPROMVersion();
        }
#endif        

        gTxDevice.load();      // load device settings either from EEPROM or ROM, depending on, if T5X_USE_EEPROM is defined
        applyDeviceSettings();

        if (analogRead(T5X_TX_VOLT_PIN)<20)    // if power is off, we have only little rustling numbers below 5 or so...
          g_OperatingMode=OperatingMode_Setup;
        else 
          g_OperatingMode=OperatingMode_Normal;

         
        if (gTxDevice.m_Properties.Sw2IsPrimaryProfileSelector) 
          gRealtime.m_Data.ProfileId=(2-g_SW2.read())+((2-g_SW3.read())*3);
        else
          gRealtime.m_Data.ProfileId=(2-g_SW3.read())+((2-g_SW2.read())*3);


        gProfile.load(gRealtime.m_Data.ProfileId);
        applyProfile();
         
	
         // read switch to enable/disable buzzer (silence mode)
  	rc::SwitchState tSwitchState = g_SW1.read();
        if ((tSwitchState == rc::SwitchState_Up) and (g_OperatingMode==OperatingMode_Normal))   
        {
          rc::g_Buzzer.setPin(T5X_TX_BUZZER_PIN);  // buzzer on -  NORMAL MODE
          digitalWrite(T5X_TX_LED_PIN, HIGH);      // turn the LED steady on
        } 
        else rc::g_Buzzer.setPin(T5X_TX_LED_PIN);  // buzzer off - SILENCE MODE (use LED instead of buzzer)

        
        rc::g_Buzzer.beep(600, 0, 0);
        


        // set up normalized -> microseconds conversion
	rc::setCenter(T5X_PPM_CENTER); 
	rc::setTravel(T5X_PPM_TRAVEL);  

	// set up PPM
	g_PPMOut.setPulseLength(400);   // default pulse length used by FrSky hardware
	g_PPMOut.setPauseLength(20000); // default frame length used by FrSky hardware
	g_PPMOut.start(9); // use pin 9, which is preferred as it's faster

        delay(1500);
        rc::g_Buzzer.beep(20, 10, gRealtime.m_Data.ProfileId);      // beep gRealtime.m_Data.ProfileId times
        delay(3000);

        if (g_OperatingMode==OperatingMode_Setup)
          rc::g_Buzzer.beep(5, 2, 20);                    // signal that we are in setup mode        
}

void loop()
{
        int16_t throttle_val=0;
        
	gRealtime.m_Data.SwitchState[0] = g_SW1.read();
	gRealtime.m_Data.SwitchState[1] = g_SW2.read();
	gRealtime.m_Data.SwitchState[2] = g_SW3.read();

        rc::SwitchState fSwitchState = rc::SwitchState_Disconnected;
        if (gTxDevice.m_Properties.Sw2SelectsFlightMode) 
      	  fSwitchState = rc::SwitchState(gRealtime.m_Data.SwitchState[1]);
        else
 	  fSwitchState = rc::SwitchState(gRealtime.m_Data.SwitchState[2]);

        gRealtime.m_Data.FlightMode = 0;
        if      (fSwitchState == rc::SwitchState_Down  ) gRealtime.m_Data.FlightMode = 0;
        else if (fSwitchState == rc::SwitchState_Center) gRealtime.m_Data.FlightMode = 1;
        else if (fSwitchState == rc::SwitchState_Up    ) gRealtime.m_Data.FlightMode = 2;

        if ((gRealtime.m_Data.SwitchState[0]==rc::SwitchState_Up) && (strchr(gProfile.m_Data.ChannelOrder,'M')!=NULL)) gRealtime.m_Data.FlightMode=gRealtime.m_Data.FlightMode+3;  // virtual flightmode active? if so, evaluate switch 2 for that purpose
  
	g_AnalogSW1.update();  // update the input system
	g_AnalogSW2.update();  // update the input system
	g_AnalogSW3.update();  // update the input system

	
	// read analog values, these write to the input system (AIL, ELE, THR, RUD & POT1)
        for (int i=0; i<4; i++) g_aPins[i].read(); 
       
        g_Pot1.read();

        
	// apply expo and dual rates to input, these read from and write to input system
	g_ailExpo[gRealtime.m_Data.FlightMode].apply();
	g_eleExpo[gRealtime.m_Data.FlightMode].apply();
	g_rudExpo[gRealtime.m_Data.FlightMode].apply();

	g_rudDR[gRealtime.m_Data.FlightMode].apply();
	g_eleDR[gRealtime.m_Data.FlightMode].apply();
	g_ailDR[gRealtime.m_Data.FlightMode].apply();

        g_aileron.apply();
        g_elevator.apply();
	g_throttle.apply();
	g_rudder.apply();
	g_aux1.apply();        // SW1
	g_aux2.apply();        // SW2
	g_aux3.apply();        // SW3
        g_aux4.apply();        // Poti

	// perform channel transformations and set channel values
	for (uint8_t i = 0; i < ChannelCount; ++i)
        {
          switch (gProfile.m_Data.ChannelOrder[i])
          {          
            case '-':   gRealtime.m_Data.Channel_us[i]=g_channels[i].apply(0);                                                            break;   // ensure empty channel remains 0.
            case 'M':   gRealtime.m_Data.Channel_us[i]=g_channels[i].apply(gTxDevice.m_Properties.VFMSteps[gRealtime.m_Data.FlightMode]); break;   // apply virtual mode switch value according to flight mode 
            case 'T':   gRealtime.m_Data.Channel_us[i]=g_channels[i].apply(); throttle_val = gRealtime.m_Data.Channel_us[i];              break;
            default:    gRealtime.m_Data.Channel_us[i]=g_channels[i].apply();                                                                      // apply value from InputToOutputPipe
          }
        }

	// Tell PPMOut that new values are ready
	g_PPMOut.update();
        
        last=now;
        now = millis(); 

   if (g_OperatingMode==OperatingMode_Normal)
   {
        g_Frsky.update();    // read telemetry data from serial link and update the values

        if ((now - last_telemetry >= gTxDevice.m_Properties.TelemetrySettings.Check_Interval*1000)) 
        {
          last_telemetry = now;
          float voltageTX = analogRead(T5X_TX_VOLT_PIN)*0.0146627565982405; // 0-15V in 1023 steps or 0,0146V per step
          if (voltageTX < gTxDevice.m_Properties.TelemetrySettings.V_TX[T5X_CELLCOUNT]*gTxDevice.m_Properties.TelemetrySettings.V_TX[T5X_RED]/10.0) rc::g_Buzzer.beep(5,5,2);
          else if (voltageTX < gTxDevice.m_Properties.TelemetrySettings.V_TX[T5X_CELLCOUNT]*gTxDevice.m_Properties.TelemetrySettings.V_TX[T5X_ORANGE]/10.0) rc::g_Buzzer.beep(50);

          if (g_Frsky.TelemetryLinkAlive())
          {
            if (g_Frsky.m_A1_Voltage*0.0517647058823529 < gProfile.m_Data.V_A1[T5X_CELLCOUNT]*gProfile.m_Data.V_A1[T5X_RED]/10.0) rc::g_Buzzer.beep(10,10,2);     //  0-13,2V in 255 steps or 0,052V per step
            else if (g_Frsky.m_A1_Voltage*0.0517647058823529 < gProfile.m_Data.V_A1[T5X_CELLCOUNT]*gProfile.m_Data.V_A1[T5X_ORANGE]/10.0) rc::g_Buzzer.beep(20);  //  0-13,2V in 255 steps or 0,052V per step

            if (g_Frsky.m_A2_Voltage*0.0129411764706*((gProfile.m_Data.V_A2[T5X_CELLCOUNT] & 0xF0) >> 4) < (gProfile.m_Data.V_A2[T5X_CELLCOUNT] & 0x0F)*gProfile.m_Data.V_A2[T5X_RED]/10.0) rc::g_Buzzer.beep(10,10,2);      //  0-3,3V in 255 steps or 0,013V per step, the real voltage range is actually defined by the voltage divider ratio 
            else if (g_Frsky.m_A2_Voltage*0.0129411764706*((gProfile.m_Data.V_A2[T5X_CELLCOUNT] & 0xF0) >> 4) < (gProfile.m_Data.V_A2[T5X_CELLCOUNT] & 0x0F)*gProfile.m_Data.V_A2[T5X_ORANGE]/10.0) rc::g_Buzzer.beep(20);   //  0-3,3V in 255 steps or 0.013V per step, the real voltage range is actually defined by the voltage divider ratio 

            if (g_Frsky.m_RSSI < gTxDevice.m_Properties.TelemetrySettings.RSSIPercent[T5X_RED]*255/100) rc::g_Buzzer.beep(10,10,2);
            else if (g_Frsky.m_RSSI < gTxDevice.m_Properties.TelemetrySettings.RSSIPercent[T5X_ORANGE]*255/100) rc::g_Buzzer.beep(20);
          }
          else  rc::g_Buzzer.beep(10,10,2);
        }

   }
   else // g_OperatingMode==OperatingMode_Setup
   {

     while (Serial.available()) 
     {
        byte b = Serial.read();  
              
        if      ( (byteCount==0) && (b==0xFE))   gRxBuffer[byteCount++]=b;  // first header byte 
        else if ( (byteCount==1) && (b==0xFE))   gRxBuffer[byteCount++]=b;  // 2nd header byte
        else if (  byteCount==2)
        {
          if(
              (b==T5X_MSG_TXDEVICE_PROPERTIES_REQ_MSGID) 
              || 
              (b==T5X_MSG_PROFILE_DATA_REQ_MSGID) 
              || 
              (b==T5X_MSG_PROFILE_DATA_APPLY_MSGID)
              ||
              (b==T5X_MSG_TXDEVICE_PROPERTIES_APPLY_MSGID)
              ||
              (b==T5X_MSG_SAVE_CONFIG_TO_EEPROM_MSGID)
            )   
             gRxBuffer[byteCount++]=b;  // valid message ID?
            else
              byteCount=0;
        }
        else if (byteCount>2)
        {
          switch (gRxBuffer[2])
          {
            case T5X_MSG_TXDEVICE_PROPERTIES_REQ_MSGID:            

                gTxDevice.send();
                byteCount=0;           
                break;
            

            case T5X_MSG_PROFILE_DATA_REQ_MSGID:

                gProfile.send();
                byteCount=0;           
                break;
                
            case T5X_MSG_PROFILE_DATA_APPLY_MSGID:
            
                gRxBuffer[byteCount]=b;
                
                if (byteCount<(sizeof(gProfile.m_Data)+2))  
                {              
                  byteCount++;
                }
                else
                {
                  rc::g_Buzzer.beep(5, 2, 1);              
                  byteCount=0;
                  gProfile.receive(gRxBuffer);
                  applyProfile();    // apply gProfile to actual Tx
                }
                  
                break;
            
            case T5X_MSG_TXDEVICE_PROPERTIES_APPLY_MSGID:

                gRxBuffer[byteCount]=b;
                
                if (byteCount<(sizeof(gTxDevice.m_Properties)+2))  
                {              
                  byteCount++;
                }
                else
                {
                  rc::g_Buzzer.beep(5, 2, 1);              
                  byteCount=0;
                  gTxDevice.receive(gRxBuffer);
                  applyDeviceSettings(); 
                }
                   
                break;
  
             case T5X_MSG_SAVE_CONFIG_TO_EEPROM_MSGID:            
                rc::g_Buzzer.beep(3, 2, 10); 
                gTxDevice.save();
                gProfile.save(gRealtime.m_Data.ProfileId);               
                byteCount=0;           
                break;
                
            default:
                byteCount=0;  
          }  
        }        
     }
    
      if (now - last_realtime_data > 60)   // we report real time data only every now and then, otherwise we would get misleading looptime values caused only because of serial communication...
      {
        last_realtime_data=now;
        gRealtime.m_Data.Analog[0]=analogRead(A0);
        gRealtime.m_Data.Analog[1]=analogRead(A1);
        gRealtime.m_Data.Analog[2]=analogRead(A2);
        gRealtime.m_Data.Analog[3]=analogRead(A3);
        gRealtime.m_Data.Analog[4]=analogRead(A4);
        gRealtime.m_Data.Analog[5]=analogRead(A5);
        gRealtime.m_Data.Analog[6]=analogRead(A6);
        gRealtime.m_Data.Analog[7]=analogRead(A7);
        
        gRealtime.m_Data.FlightTimerSec=gTimer.getTime();
  
        gRealtime.m_Data.FreeRAM=freeRam();
        gRealtime.m_Data.LoopTime=now-last;
  
        gRealtime.send();
      }
   }
   
    if (now - last_flight_timer >= 1000)
    {
      last_flight_timer = now;
      if ((50*(throttle_val-T5X_PPM_CENTER-T5X_PPM_TRAVEL)/T5X_PPM_TRAVEL+100) > gTxDevice.m_Properties.FlightTimeTrigger_ThrottlePercent)  
      {
        if (gTimerSecAtPaused==0) gTimer.update(true);
        else
        {
          gTimer.setTarget(gTimerSecAtPaused);
          gTimerSecAtPaused=0;
        }
      }
      else
      {
        gTimer.update(false);
        gTimerSecAtPaused=gTimer.getTime();
    	}
    }

}
