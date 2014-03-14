/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** throttlehold_example.pde
** Demonstrate Throttle Hold functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <AIPin.h>
#include <BiStateSwitch.h>
#include <ThrottleHold.h>


// we use A0 as input for the throttle
rc::AIPin g_thrPin(A0, rc::Input_THR);

// we use pin 3 as a hold switch and store the result in rc::Switch_A
rc::BiStateSwitch g_hldPin(3, rc::Switch_A);

// we can define the throttle hold level in the contructor
// The first parameter is the level the throttle will be on when hold is enabled
// The second defines which switch the hold should act on
// The third is the state the switch should be in
rc::ThrottleHold g_hold(-256, rc::Switch_A, rc::SwitchState_Down);

void setup()
{
	// nothing to do here
}

void loop()
{
	g_thrPin.read(); // will write results to rc::Input_THR
	// ThrottleHold uses rc::Input_THR as default input
	// you can specify a different input using setIndex()
	// or you can specify some value in the apply function
	g_hldPin.read(); // will write to rc::Switch_A
	
	// The ThrottleHold object will read input throttle from rc::Input_THR
	// it will read the switch position from rc::Switch_A
	// and it will write the result back to rc::Input_THR
	g_hold.apply();
	// in case the hold switch was in the low position, the result will be -256 (which we specified in the constructor)
	// otherwise it will be whatever g_thrPin.read() wrote.
	// you can get the result using rc::getInput(rc::Input_THR);
	// print it out using Serial to see it in action!
}
