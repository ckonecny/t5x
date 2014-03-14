/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** switchtoggler_example.pde
** Demonstrate switch toggler functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <BiStateSwitch.h>
#include <SwitchToggler.h>

rc::BiStateSwitch g_switch(3, rc::Switch_A);
rc::SwitchToggler g_toggler(rc::SwitchState_Up, rc::Switch_A); // toggle when switch A goes up

void setup()
{
	// let's use pin 13 (LED) as output so we can actually see something happening
	pinMode(13, OUTPUT);
	digitalWrite(13, LOW);
}

void loop()
{
	g_switch.read(); // first you need to read the actual switch, which will update rc::Switch_A
	g_toggler.apply(); // Then apply the toggler
	
	if (rc::getSwitchState(rc::Switch_A) == rc::SwitchState_Up)
	{
		digitalWrite(13, HIGH);
	}
	else
	{
		digitalWrite(13, LOW);
	}
	
	// when you run this example you'll see the LED going on and off every time
	// you move the switch to the up position
	//
	// move it up: led goes on (toggle)
	// move it down: led stays on
	// move it up: led goes off (toggle)
	// move it down: led stays off
}
