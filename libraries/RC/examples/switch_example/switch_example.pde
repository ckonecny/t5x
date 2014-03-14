/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** switch_example.pde
** Demonstrate bi and tri state switches
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <BiStateSwitch.h>
#include <TriStateSwitch.h>

// A bi state switch is a simple two position toggle switch
// it can be momentary (spring loaded) or alternating (normal)
// The first parameter is the input pin
// a high signal on the pin indicates up position
// The second parameter can be used to make the switch store its state in a central location
// the third parameter indicates whether the switch is spring loaded
// with the last parameter this can be used if the switch is mounted up side down
rc::BiStateSwitch g_bi(3, rc::Switch_A, false, false);

// A tri state switch is a three position toggle switch
// The first parameter is the input pin for the up position
// a high signal on the up pin indicates up position
// The second parameter is the input pin for the down position
// a high signal on the down pin indicates down position
// when both pins are high or low, the center position is assumed
// The third parameter can be used to make the switch store its state in a central location
// The last parameter can be used to flip the up and down pins
rc::TriStateSwitch g_tri(4, 5, rc::Switch_B, false);

void setup()
{
	// we can change any of the constructor parameters afterwards as well
	// but that won't be needed here
}

void loop()
{
	// we can call the read function of the switches to get their position
	rc::SwitchState biState  = g_bi.read();
	rc::SwitchState triState = g_tri.read();
	
	// the state can be either
	// rc::SwitchState_Up
	// rc::SwitchState_Center
	// rc::SwitchState_Down
	// rc::SwitchState_Disconnected
	// the last state won't occur when calling the read function though
	
	// it's also possible to get the state using the rc::getSwitchState function
	biState  = rc::getSwitchState(rc::Switch_A);
	triState = rc::getSwitchState(rc::Switch_B);
	
	// in this case it's possible to get rc::SwitchState_Disconnected
	// in case you provide rc::Switch_C for example (which has no switch assigned to it)
	
	// That's all!
}
