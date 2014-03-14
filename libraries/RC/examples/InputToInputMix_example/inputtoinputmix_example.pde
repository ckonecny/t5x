/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** inputtoinputmix_example.pde
** Demonstrate Input to Input mixes
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <AIPin.h>
#include <InputToInputMix.h>

// Use A0 as analog input for aileron
rc::AIPin g_pin(A0, rc::Input_AIL);

// specify an aileron to rudder mix
// we use 25% positive mix (25% of aileron input will be added to rudder input when aileron is positive)
// we use 25% negative mix (25% of aileron input will be added to rudder input when aileron is negative)
// we use an offset of 0 (master input gets subtracted by this before the mix is applied)
// we use Input_AIL as master (input)
// we use Input_RUD as slave (destination)
rc::InputToInputMix g_ailToRud(25, 25, 0, rc::Input_AIL, rc::Input_RUD);

void setup()
{
	// nothing to do here!
}

void loop()
{
	g_pin.read(); // input from A0 will be placed in Input_AIL
	
	// This is important!
	rc::setInput(rc::Input_RUD, 0);
	// because we don't use any input for rudder, we need to reset it here
	// otherwise aileron will be added in every call of loop(), which would
	// quickly result in rudder being either extremely positive or extremely negative
	
	g_ailToRud.apply(); // apply aileron to rudder mix
	
	// now we can see the results using
	// rc::getInput(rc::Input_AIL);
	// rc::getInput(rc::Input_RUD);
	// give it a try and print it out on the serial port!
	
	// you'll see that 25% of aileron input gets added to rudder
	
	// There are a few occasions were you'll want to use a negative mix on one side
	// for example in a Swashplate to Throttle mix
	// In this case you'll want throttle to increase slightly when aileron or elevator input is applied in any direction
	// this can be achieved by setting the negative mix to a negative number (e.g. -25)
	// When negative swash input is applied, throttle will be increased (neg * neg = pos)
	
	// It's also possible to set a master offset on the mix. The offset determines the center position of the master.
	// This is usefull when dealing with a throttle to X mix since throttle center lies around -256 instead of 0.
	
	// Lastly, to create an offset mix, simply set the Master to None. When you apply the mix, the offset will be applied to the slave.
}
