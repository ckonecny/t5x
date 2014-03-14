/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** offsetrates_example.pde
** Demonstrate Offset functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <AIPin.h>
#include <BiStateSwitch.h>
#include <Offset.h>


// We need some input
rc::AIPin g_pins[3] =
{
	rc::AIPin(A0, rc::Input_AIL),
	rc::AIPin(A1, rc::Input_ELE),
	rc::AIPin(A2, rc::Input_RUD)
};


// We need a switch
rc::BiStateSwitch g_switch(3, rc::Switch_A);


// we create three offsets; for aileron, elevator and rudder
rc::Offset g_offset[3] = 
{
	rc::Offset(20, rc::Input_AIL, rc::Switch_A, rc::SwitchState_Up),
	rc::Offset(-20, rc::Input_ELE, rc::Switch_A, rc::SwitchState_Up),
	rc::Offset(0, rc::Input_RUD, rc::Switch_A, rc::SwitchState_Up)
};


void setup()
{
	// Nothing to do here
	// you may change any of the parameters of the Offset using getters and setters
	
	// The Offset applies a trim to a given input when a condition (switch position) is met
	// So when switch A is up, 20 will be added to Aileron
	// When switch A is down, Aileron won't be modified
	// This may be used to correct tendencies during certain flight conditions
	// It's a lot like Dual Rates, but instead of scaling the input, it's offset.
}

void loop()
{
	g_switch.read();
	
	for (uint8_t i = 0; i < 3; ++i)
	{
		g_pins[i].read();
		g_offset[i].apply();
	}
	
	// that's all there's to it. If the switch was up, offset will have been applied
	// if it was down, the input will not have been modified
	// results can be read using rc::getInput() for rc::Input_AIL/ELE/RUD
	
	// since Offset is actuall a trim, it's best to apply them right after the read,
	// apply dual rates, expo or curves afterwards.
}
