/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** analogswitch_example.pde
** Demonstrate analog switch
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <AnalogSwitch.h>
#include <BiStateSwitch.h>

// An analog switch takes either a bi-state or tri-state switch as input
rc::BiStateSwitch g_bi(3, rc::Switch_A);

// The analog switch will read input from the specified switch input (Switch_A)
// and writes the result to the specified input index (Input_AIL)
rc::AnalogSwitch g_aswitch(rc::Switch_A, rc::Input_AIL);

void setup()
{
	// we can specify a duration if we want to, default is 0 (instant)
	// the duration is specified in milliseconds and can be as large as 10000 (10 sec)
	// it indicates the time it takes to transition from one extreme (-256) to the other (256)
	g_aswitch.setDuration(2000); // 2 seconds
}

void loop()
{
	// we'll have to read the source switch first
	g_bi.read();
	
	// and then we can update the analog switch
	g_aswitch.update();
	
	// we can get the result either from the update function (the return value)
	// or from the central input buffer:
	int16_t result = rc::getInput(rc::Input_AIL);
	
	// the state of the source switch can also be read if you're interested
	rc::SwitchState state = rc::getSwitchState(rc::Switch_A);
	
}
