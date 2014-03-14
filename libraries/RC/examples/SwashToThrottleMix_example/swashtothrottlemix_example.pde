/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** swashtothrottlemix_example.pde
** Demonstrate Swashplate to Throttle mix
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <AIPin.h>
#include <SwashToThrottleMix.h>

// Use three analog pins as control input
rc::AIPin g_pins[3] = 
{
	rc::AIPin(A0, rc::Input_AIL),
	rc::AIPin(A1, rc::Input_ELE),
	rc::AIPin(A2, rc::Input_THR)
};

// specify the swash to throttle mix
rc::SwashToThrottleMix g_swToThr(15, 50); // as an example we use two different values, 15% aileron, 50% elevator

void setup()
{
	// Not much to do here
	// Swash to throttle mix is different from ordinary programmable mixes in that it takes
	// the slave value (throttle) into account. A normal mix will simply multiply master input by mix rate and
	// add it to the slave value. SwThr mix will multiply master input by mix AND the distance of slave input to center.
	// In other words: the mix effect will be strongest around center throttle stick and weakest at zero and full throttle.
	// This is to prevent your heli from taking off when you're at zero throttle and are moving the swashplate...
}

void loop()
{
	// read input, this will write to rc::Input_AIL, rc::Input_ELE and rc::Input_THR
	for (uint8_t i = 0; i < 3; ++i)
	{
		g_pins[i].read();
	}
	
	// apply the mix
	g_swToThr.apply();
	
	// The result can be obtained by rc::getInput(rc::Input_THR);
}
