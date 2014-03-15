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
  *                                                                           
  *  SimuTX.ino
  *  Kleiner RC Sender mit Frsky Akku Telemetrie
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

// Tx5 includes
#include "config.h"
#include "Frsky.h"


#define ORANGE 0
#define RED    1


///////////////////////////////////////////////////////////////////////
// Transmitter Settings
///////////////////////////////////////////////////////////////////////

enum
{
	ChannelCount = 8
};


/////////// Analog Pins /////////////
rc::AIPin g_aPins[4] = 
{
	rc::AIPin(A0, rc::Input_AIL), // we have to specify an input pint
	rc::AIPin(A1, rc::Input_ELE), // and we can optionally specify an index in the centralized
	rc::AIPin(A2, rc::Input_THR), // input buffer where results should be written to
	rc::AIPin(A3, rc::Input_RUD)
};

// ch 8
rc::AIPin g_PotiAIPin(A6);                                     // Potentiometer on A6, no Input system assigned


////////// Switches ///////////////

// ch 5 + DR/Expo
rc::TriStateSwitch g_ch5In(4, 5, rc::Switch_B, true);
rc::AnalogSwitch   g_ch5Switch(rc::Switch_B, rc::Input_FLP);

// ch 6
rc::TriStateSwitch g_ch6In(6, 7, rc::Switch_C, true);
rc::AnalogSwitch   g_ch6Switch(rc::Switch_C, rc::Input_BRK);

// ch 7
rc::BiStateSwitch g_ch7In(3, rc::Switch_A, false, false);
rc::AnalogSwitch  g_ch7Switch(rc::Switch_A, rc::Input_PIT);


uint8_t      g_ActiveProfile=0;   // holds the active profile selected by the user via 3-pos switch g_ch5In


rc::Expo g_ailExpo[3] = {rc::Expo(0, rc::Input_AIL), rc::Expo(0, rc::Input_AIL), rc::Expo(0, rc::Input_AIL)}; // also specify what index of the input
rc::Expo g_eleExpo[3] = {rc::Expo(0, rc::Input_ELE), rc::Expo(0, rc::Input_ELE), rc::Expo(0, rc::Input_ELE)}; // buffer the expo should work on (optionally)
rc::Expo g_rudExpo[3] = {rc::Expo(0, rc::Input_RUD), rc::Expo(0, rc::Input_RUD), rc::Expo(0, rc::Input_RUD)};

rc::DualRates g_ailDR[3] = {rc::DualRates(100, rc::Input_AIL), rc::DualRates(100, rc::Input_AIL), rc::DualRates(100, rc::Input_AIL)}; // also specify what index of the input
rc::DualRates g_eleDR[3] = {rc::DualRates(100, rc::Input_ELE), rc::DualRates(100, rc::Input_ELE), rc::DualRates(100, rc::Input_ELE)}; // buffer the dual rates
rc::DualRates g_rudDR[3] = {rc::DualRates(100, rc::Input_RUD), rc::DualRates(100, rc::Input_RUD), rc::DualRates(100, rc::Input_RUD)}; // should work on (optionally)



rc::Channel g_channels[ChannelCount] =
{
  	rc::Channel(rc::Output_AIL1,  rc::OutputChannel_1),
	rc::Channel(rc::Output_ELE1,  rc::OutputChannel_2),
	rc::Channel(rc::Output_THR1,  rc::OutputChannel_3),
	rc::Channel(rc::Output_RUD1,  rc::OutputChannel_4),
	rc::Channel(rc::Output_FLP1,  rc::OutputChannel_5),
	rc::Channel(rc::Output_BRK1,  rc::OutputChannel_6),
	rc::Channel(rc::Output_PIT,   rc::OutputChannel_7),
        rc::Channel(rc::Output_GEAR,  rc::OutputChannel_8)
};

// PPM related variables
rc::PPMOut g_PPMOut(ChannelCount);

// Set up pipes for direct input to output copying
rc::InputToOutputPipe g_aileron( rc::Input_AIL, rc::Output_AIL1);
rc::InputToOutputPipe g_elevator(rc::Input_ELE, rc::Output_ELE1);
rc::InputToOutputPipe g_throttle(rc::Input_THR, rc::Output_THR1);
rc::InputToOutputPipe g_rudder(  rc::Input_RUD, rc::Output_RUD1);
rc::InputToOutputPipe g_aux1(    rc::Input_FLP, rc::Output_FLP1);
rc::InputToOutputPipe g_aux2(    rc::Input_BRK, rc::Output_BRK1);
rc::InputToOutputPipe g_aux3(    rc::Input_PIT, rc::Output_PIT);
// note: Channel 8 is not part of Input/Output-system


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

tx5::Frsky g_Frsky;


unsigned long last = 0;

void setup()
{
        Serial.begin(9600);
        
         // read switch to determine the actual profile to be used
  	rc::SwitchState tSwitchState = g_ch6In.read();
        if      (tSwitchState == rc::SwitchState_Up)     g_ActiveProfile = 0;
        else if (tSwitchState == rc::SwitchState_Center) g_ActiveProfile = 1;
        else if (tSwitchState == rc::SwitchState_Down)   g_ActiveProfile = 2;
  
        // initialize expo and dualrate objects with the profile specific values
        for (uint8_t i=0; i < 3; i++)
        {
            g_ailExpo[i].set(g_Profile[g_ActiveProfile].AilExpo[i]);
            g_eleExpo[i].set(g_Profile[g_ActiveProfile].EleExpo[i]);
            g_rudExpo[i].set(g_Profile[g_ActiveProfile].RudExpo[i]);
            g_ailDR[i].set(g_Profile[g_ActiveProfile].AilDR[i]);
            g_eleDR[i].set(g_Profile[g_ActiveProfile].EleDR[i]);
            g_rudDR[i].set(g_Profile[g_ActiveProfile].RudDR[i]);
        }
  
  
 
	// Initialize timer
	rc::Timer1::init();
	rc::Timer2::init();
	
         // read switch to enable/disable buzzer (silence mode)
  	tSwitchState = g_ch7In.read();
        if (tSwitchState == rc::SwitchState_Up)     
        {
          rc::g_Buzzer.setPin(TX_BUZZER_PIN);  // buzzer on
          digitalWrite(TX_LED_PIN, HIGH);      // turns the LED on
        } 
        else rc::g_Buzzer.setPin(TX_LED_PIN);  // buzzer off (use LED instead)

        
        rc::g_Buzzer.beep(600, 0, 0);
        


	// set calibration values, these depend on hardware configurations
        
        for(int i=0; i<4; i++)
        {
            g_aPins[i].setCalibration(g_AnalogSettings[i].Calibration[0], g_AnalogSettings[i].Calibration[1],  g_AnalogSettings[i].Calibration[2]);
            g_aPins[i].setReverse(g_AnalogSettings[i].Reverse);  
    	}
	
        g_PotiAIPin.setCalibration(0,512,1023);
        
	// set up normalized -> microseconds conversion
	rc::setCenter(1500); // servo center point
	rc::setTravel(700);  // max servo travel from center point
	// our output signal will lie between 920 and 2120 microseconds (1520 +/- 600)
	
	// fill channel values buffer with sane values, all centered
	rc::setOutputChannel(rc::OutputChannel_1, rc::normalizedToMicros(0));
	rc::setOutputChannel(rc::OutputChannel_2, rc::normalizedToMicros(0));
	rc::setOutputChannel(rc::OutputChannel_3, rc::normalizedToMicros(-256)); // Throttle channel, MUST BE AT 0 THROTTLE!
	rc::setOutputChannel(rc::OutputChannel_4, rc::normalizedToMicros(0));
	rc::setOutputChannel(rc::OutputChannel_5, rc::normalizedToMicros(0));
	rc::setOutputChannel(rc::OutputChannel_6, rc::normalizedToMicros(0));
	rc::setOutputChannel(rc::OutputChannel_7, rc::normalizedToMicros(0));
	rc::setOutputChannel(rc::OutputChannel_8, rc::normalizedToMicros(0));

	
	// set up PPM
	g_PPMOut.setPulseLength(400);   // default pulse length used by FrSky hardware
	g_PPMOut.setPauseLength(20000); // default frame length used by FrSky hardware
	g_PPMOut.start(9); // use pin 9, which is preferred as it's faster

        delay(1500);
        rc::g_Buzzer.beep(20, 10, g_ActiveProfile);      // beep g_ActiveProfile times
        delay(3000);
}

void loop()
{
        unsigned long now = millis();       
  
        g_Frsky.update();    // read telemetry data from serial link and update the values
       
        if ((now - last >= g_Telemetry_Check_Interval)) {
          last = now;
          float voltageTX = analogRead(TX_VOLT_PIN)*0.0146627565982405; // 0-15V in 1023 steps or 0,0146V per step
          if (voltageTX < g_V_TX[RED]) rc::g_Buzzer.beep(10,10,2);
          else if (voltageTX < g_V_TX[ORANGE]) rc::g_Buzzer.beep(20);

          if (g_Frsky.m_A1_Voltage*0.0517647058823529 < g_Profile[g_ActiveProfile].V_A1[RED]) rc::g_Buzzer.beep(10,10,2);     //  0-13,2V in 255 steps or 0,052V per step
          else if (g_Frsky.m_A1_Voltage*0.0517647058823529 < g_Profile[g_ActiveProfile].V_A1[ORANGE]) rc::g_Buzzer.beep(20);  //  0-13,2V in 255 steps or 0,052V per step

          if (g_Frsky.m_RSSI < g_RSSI[RED]) rc::g_Buzzer.beep(10,10,2);
          else if (g_Frsky.m_RSSI < g_RSSI[ORANGE]) rc::g_Buzzer.beep(20);
        }


	g_ch5In.read();
	g_ch5Switch.update();

	rc::SwitchState fSwitchState = g_ch6In.read();
        int flightmode = 0;
        if      (fSwitchState == rc::SwitchState_Down)   flightmode = 0;
        else if (fSwitchState == rc::SwitchState_Center) flightmode = 1;
        else if (fSwitchState == rc::SwitchState_Up)     flightmode = 2;
        

  
	g_ch6In.read();
	g_ch6Switch.update();
                             
	g_ch7In.read();
	g_ch7Switch.update();

	
	// read analog values, these write to the input system (AIL, ELE, THR and RUD)
	g_aPins[0].read(); // aileron
	g_aPins[1].read(); // elevator
	g_aPins[2].read(); // throttle
	g_aPins[3].read(); // rudder

	
	// apply expo and dual rates to input, these read from and write to input system
	g_ailExpo[flightmode].apply();
	g_ailDR[flightmode].apply();
	
	g_eleExpo[flightmode].apply();
	g_eleDR[flightmode].apply();
	
	g_rudExpo[flightmode].apply();
	g_rudDR[flightmode].apply();

        g_aileron.apply();
        g_elevator.apply();
	g_rudder.apply();
	g_throttle.apply();
	g_aux1.apply();
	g_aux2.apply();
	g_aux3.apply();
	
	// END OF OUTPUT HANDLING
	// Now we've filled all the parts of the output system we need (AIL1, ELE1, THR1, RUD1, GYR1 and PIT1)
	// now we can start using the output to generate a signal or data packet
	// Well, almost. Channel does perform some transformations, but these aren't written back into the output system
	// since more than one channel may use the same output as source.
	
	// perform channel transformations and set channel values
	for (uint8_t i = 0; i < ChannelCount; ++i) g_channels[i].apply();
	
        // Channel 8 is handled outside the input output system, hence apply the values directly
        g_channels[7].apply(g_PotiAIPin.read());
	// Tell PPMOut that new values are ready
	g_PPMOut.update();
}


