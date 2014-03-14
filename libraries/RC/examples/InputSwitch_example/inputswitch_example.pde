/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** inputswitch_example.pde
** Demonstrate input switch functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <AIPin.h>
#include <InputSwitch.h>

// We create an AIPin on analog pin A0 as a source
rc::AIPin g_pin(A0, rc::Input_AIL);

// Create two InputSwitches which take aileron input and write as a switch
rc::InputSwitch g_switchA(rc::Input_AIL, rc::Switch_A);
rc::InputSwitch g_switchB(rc::Input_AIL, rc::Switch_B);

void setup()
{
	g_switchA.setMark(128);      // all values >= 128 are considered "Up"
	g_switchA.setMirrored(true); // all values <= -128 are also considered "Up"
	g_switchA.setReversed(true); // all values < 128 && > -128 are considered "Up"
	g_switchA.setDeadBand(15);   // when value enters -113 > value > 113 it's considered "Up",
	                             // when it leaves -143 > value > 143 it's considered "Down"
	
	g_switchB.setMark(192);      // all values >= 192 are considered "Up"
	g_switchB.setRanged(true);   // enable mark2
	g_switchB.setMark2(64);      // all values <= 192 and >= 64 are considered "Up"
	g_switchB.setMirrored(true); // all values >= -192 and <= -64 are also considered "Up"
	
	// note that you can not use dead band in combination with ranged mode
}

void loop()
{
	g_pin.read(); // update the source pin
	
	// update switches
	rc::SwitchState stateA = g_switchA.read();
	rc::SwitchState stateB = g_switchB.read();
	
	// you can also get the switch state like this:
	stateA = rc::getSwitchState(rc::Switch_A);
	stateB = rc::getSwitchState(rc::Switch_B);
}
