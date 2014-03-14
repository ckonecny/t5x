/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** engine_example.pde
** Demonstrate Engine functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <AIPin.h>
#include <BiStateSwitch.h>
#include <Engine.h>


// we use A0 as input for the throttle and A1 for rudder
rc::AIPin g_thr(A0, rc::Input_THR);
rc::AIPin g_rud(A1, rc::Input_RUD);

// we use pin 3 as a cut switch and store the result in rc::Switch_A
rc::BiStateSwitch g_cut(3, rc::Switch_A);

// We create two engine objects
// The first parameter is the output destination
// The second defines which switch should be used for cut
// The third is the state the switch should be in
rc::Engine g_engines[3] =
{
	rc::Engine(rc::Output_THR1, rc::Switch_A, rc::SwitchState_Up), // left wing engine
	rc::Engine(rc::Output_THR2, rc::Switch_A, rc::SwitchState_Up), // nose engine
	rc::Engine(rc::Output_THR3, rc::Switch_A, rc::SwitchState_Up)  // right wing engine
};


void setup()
{
	// we can define an idle level here
	g_engines[0].setIdle(-220);
	g_engines[1].setIdle(-220);
	g_engines[2].setIdle(-220);
	
	// we can specify some rudder mix, which will make an engine turn faster or slower when rudder is applied
	g_engines[0].setRudderMix(5);
	g_engines[2].setRudderMix(-5);
	
	// if you wanted to you could also only make one wing's engine move faster by calling
	// setPosMix and setNegMix (just like you would for a normal programmable mix)
	
	// please note that throttle mixes do nothing at full and zero throttle, to prevent accidental takeoffs...
}

void loop()
{
	g_thr.read(); // will write results to rc::Input_THR
	g_rud.read(); // will write results to rc::Input_RUD
	g_cut.read(); // will write to rc::Switch_A
	
	// The Engine object will read input throttle from rc::Input_THR
	// it will read the switch position from rc::Switch_A
	// and it will write the result to rc::Output_THR1-3
	for (uint8_t i = 0; i < 3; ++i)
	{
		g_engines[i].apply();
	}
	// in case the cut switch was in the up position, the result will be -256 (engine off)
	// otherwise it will be whatever g_thrPin.read() wrote, but at least -220 (idle).
	// you can get the result using rc::getOutput(rc::Output_THR1-3);
	// print it out using Serial to see it in action!
}
