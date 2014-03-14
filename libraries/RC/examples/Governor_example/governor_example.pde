/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** governor_example.pde
** Demonstrate Governor functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <BiStateSwitch.h>
#include <Governor.h>
#include <ThrottleHold.h>


// define a switch for throttle hold on pin 3
rc::BiStateSwitch g_holdSwitch(3, rc::Switch_A);
// tell throttle hold which throttle setting to use, which switch and which switch state
rc::ThrottleHold g_hold(-256, rc::Switch_A, rc::SwitchState_Down);

// define a switch for the flight mode on pin 4
rc::BiStateSwitch g_flightModeSwitch(4, rc::Switch_B);
// tell the governor which switch to use
rc::Governor g_governor(rc::Switch_B);


void setup()
{
	// we'll want governor to act on throttle hold, so we'll tell it to copy the settings
	g_governor.setHold(g_hold);
	
	// we can change the rate settings for the governor if we'd like
	// we can set the rate for every switch state
	g_governor.setDownRate(4);
	g_governor.setUpRate(96);
	// with a tri state switch we could also use setCenterRate
}

void loop()
{
	// first we need to update the switches
	g_holdSwitch.read();
	g_flightModeSwitch.read();
	
	// then we can apply throttle hold
	g_hold.apply();
	
	// and finally governor
	g_governor.apply();
	
	// now check the results in the output buffer
	int16_t governorSpeed = rc::getOutput(rc::Output_GOV);
	
	// you'll see that when you move the flight mode switch, the output changes.
	// when throttle hold is active, the result will be either rc::Out_Min or rc::Out_Max
	// depending on Governor::set/getHoldDirection(). This is to indicate that endpoints
	// should be ignored by the Channel class.
}
