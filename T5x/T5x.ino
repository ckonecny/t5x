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

// t5x includes
#include "config.h"
#include "Frsky.h"

// warning levels for Telemetry Stuff
#define ORANGE 0
#define RED    1


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

t5x::Frsky      g_Frsky;                // global frsky telemetry object 
rc::FlightTimer g_Timer;                // global flight timer
int16_t         g_TimerSecAtPaused = 0; // to start a new timer after pause
unsigned long   now                = 0; // for scheduling
unsigned long   pmon_last          = 0; // only needed to verify loop time
unsigned long   last_telemetry     = 0; // for scheduling
unsigned long   last_flight_timer  = 0; // for scheduling
uint8_t          g_ActiveProfile   = 0; // active profile selected by the user via 3-pos switch

int8_t getChannelPosition(char aChar)
// return the channel position of the given character as per definition in the model profile
// if not found, return -
{
  char* pChar = strchr(cfg_Profile[g_ActiveProfile].ChannelOrder, aChar);
  if (pChar!=NULL) return int(pChar)-int(cfg_Profile[g_ActiveProfile].ChannelOrder);
  else return -1;
}

void setup()
{
        Serial.begin(9600);    // telemetry
        
        // initialize switches working direction. maybe user wants to let them work in the other direction
        g_SW1.setReverse(cfg_SwitchSettings[0].Reverse);
        g_SW2.setReverse(cfg_SwitchSettings[1].Reverse);
        g_SW3.setReverse(cfg_SwitchSettings[2].Reverse);
        
         
         // read both 3-pos switches for determining the actual profile to be used
#ifdef T5X_PROFILE_SW2_PRIMARY
  	g_ActiveProfile=(2-g_SW2.read())+((2-g_SW3.read())*3);
#else
  	g_ActiveProfile=(2-g_SW3.read())+((2-g_SW2.read())*3);
#endif

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
            g_ailExpo[i].set(cfg_Profile[g_ActiveProfile].AilExpo[i]);
            g_eleExpo[i].set(cfg_Profile[g_ActiveProfile].EleExpo[i]);
            g_rudExpo[i].set(cfg_Profile[g_ActiveProfile].RudExpo[i]);
              g_ailDR[i].set(cfg_Profile[g_ActiveProfile].AilDR[i]  );
              g_eleDR[i].set(cfg_Profile[g_ActiveProfile].EleDR[i]  );
              g_rudDR[i].set(cfg_Profile[g_ActiveProfile].RudDR[i]  );
        }
  
  
 
	// Initialize timer
	rc::Timer1::init();
	rc::Timer2::init();
	
         // read switch to enable/disable buzzer (silence mode)
  	rc::SwitchState tSwitchState = g_SW1.read();
        if (tSwitchState == rc::SwitchState_Up)     
        {
          rc::g_Buzzer.setPin(T5X_TX_BUZZER_PIN);  // buzzer on -  NORMAL MODE
          digitalWrite(T5X_TX_LED_PIN, HIGH);      // turn the LED steady on
        } 
        else rc::g_Buzzer.setPin(T5X_TX_LED_PIN);  // buzzer off - SILENCE MODE (use LED instead of buzzer)

        
        rc::g_Buzzer.beep(600, 0, 0);
        


	// set calibration values, these depend on hardware configurations
        for(int i=0; i<4; i++)  // calibrate/reverse gimbals for AIL, ELE, THR, RUD
        {
            g_aPins[i].setCalibration(cfg_AnalogSettings[i].Calibration[0], cfg_AnalogSettings[i].Calibration[1],  cfg_AnalogSettings[i].Calibration[2]);
            g_aPins[i].setReverse(cfg_AnalogSettings[i].Reverse);  
    	}
	
        g_Pot1.setCalibration(cfg_AnalogSettings[6].Calibration[0], cfg_AnalogSettings[6].Calibration[1],  cfg_AnalogSettings[6].Calibration[2]);
        g_Pot1.setReverse(cfg_AnalogSettings[6].Reverse);      
	
        // set up normalized -> microseconds conversion
	rc::setCenter(1500); // servo center point
	rc::setTravel(700);  // max servo travel from center point
	// our output signal will lie between 920 and 2120 microseconds (1520 +/- 600)
	
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


	// set up PPM
	g_PPMOut.setPulseLength(400);   // default pulse length used by FrSky hardware
	g_PPMOut.setPauseLength(20000); // default frame length used by FrSky hardware
	g_PPMOut.start(9); // use pin 9, which is preferred as it's faster

        delay(1500);
        rc::g_Buzzer.beep(20, 10, g_ActiveProfile);      // beep g_ActiveProfile times
        delay(3000);
        
        g_Timer.setTarget(cfg_Profile[g_ActiveProfile].Timer);
        g_Timer.setDirection(false);                     // count down timer
}

void loop()
{
	rc::SwitchState SW1State = g_SW1.read();

#ifdef T5X_SW2_SELECTS_FLIGHTMODE
	rc::SwitchState fSwitchState = g_SW2.read();
	g_SW3.read();
#else
	rc::SwitchState fSwitchState = g_SW3.read();
	g_SW2.read();
#endif

        int flightmode = 0;
        if      (fSwitchState == rc::SwitchState_Down  ) flightmode = 0;
        else if (fSwitchState == rc::SwitchState_Center) flightmode = 1;
        else if (fSwitchState == rc::SwitchState_Up    ) flightmode = 2;

        if ((SW1State==rc::SwitchState_Up) && (strchr(cfg_Profile[g_ActiveProfile].ChannelOrder,'M')!=NULL)) flightmode=flightmode+3;  // virtual flightmode active? if so, evaluate switch 2 for that purpose
  
	g_AnalogSW1.update();  // update the input system
	g_AnalogSW2.update();  // update the input system
	g_AnalogSW3.update();  // update the input system

	
	// read analog values, these write to the input system (AIL, ELE, THR, RUD & POT1)
      	                       g_aPins[0].read(); // aileron
	                       g_aPins[1].read(); // elevator
	int16_t throttle_val = g_aPins[2].read(); // throttle (we need the value to trigger the timer)
	                       g_aPins[3].read(); // rudder

        g_Pot1.read();

        
	// apply expo and dual rates to input, these read from and write to input system
	g_ailExpo[flightmode].apply();
	g_eleExpo[flightmode].apply();
	g_rudExpo[flightmode].apply();

	g_rudDR[flightmode].apply();
	g_eleDR[flightmode].apply();
	g_ailDR[flightmode].apply();

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
          switch (cfg_Profile[g_ActiveProfile].ChannelOrder[i])
          {          
            case '-':   g_channels[i].apply(0);                        break;   // ensure empty channel remains 0.
            case 'M':   g_channels[i].apply(cfg_VFMSteps[flightmode]); break;   // apply virtual mode switch value according to flight mode 
            default:    g_channels[i].apply();                                  // apply value from InputToOutputPipe
          }
        }

	// Tell PPMOut that new values are ready
	g_PPMOut.update();


        g_Frsky.update();    // read telemetry data from serial link and update the values

        now = millis();  

        if ((now - last_telemetry >= cfg_Telemetry_Check_Interval)) 
        {
          last_telemetry = now;
          float voltageTX = analogRead(T5X_TX_VOLT_PIN)*0.0146627565982405; // 0-15V in 1023 steps or 0,0146V per step
          if (voltageTX < cfg_V_TX[RED]) rc::g_Buzzer.beep(10,10,2);
          else if (voltageTX < cfg_V_TX[ORANGE]) rc::g_Buzzer.beep(20);

          if (g_Frsky.TelemetryLinkAlive())
          {
            if (g_Frsky.m_A1_Voltage*0.0517647058823529 < cfg_Profile[g_ActiveProfile].V_A1[RED]) rc::g_Buzzer.beep(10,10,2);     //  0-13,2V in 255 steps or 0,052V per step
            else if (g_Frsky.m_A1_Voltage*0.0517647058823529 < cfg_Profile[g_ActiveProfile].V_A1[ORANGE]) rc::g_Buzzer.beep(20);  //  0-13,2V in 255 steps or 0,052V per step

            if (g_Frsky.m_RSSI < cfg_RSSI[RED]) rc::g_Buzzer.beep(10,10,2);
            else if (g_Frsky.m_RSSI < cfg_RSSI[ORANGE]) rc::g_Buzzer.beep(20);
          }
          else  rc::g_Buzzer.beep(10,10,2);
        }


        if (now - last_flight_timer >= 1000)
        {
          if (throttle_val > cfg_FlightTimeTrigger_ThrottleVal)  
          {
            if (g_TimerSecAtPaused==0) g_Timer.update(true);
            else
            {
              g_Timer.setTarget(g_TimerSecAtPaused);
              g_TimerSecAtPaused=0;
            }
          }
          else
          {
            g_Timer.update(false);
            g_TimerSecAtPaused=g_Timer.getTime();
  	  }
        }

//        Serial.println(now-pmon_last);      // for loop time measurment
//        pmon_last=now;                      // to get a feeling of performance...
}


