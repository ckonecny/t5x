/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** swashplate_example.pde
** Demonstrate Swashplate functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Swashplate.h>


rc::Swashplate g_swash;

void setup()
{
	// use the most common type of CCPM swash
	g_swash.setType(rc::Swashplate::Type_HR3);
	
	// set up mixes, use 50% on all axis
	g_swash.setAilMix(50);
	g_swash.setEleMix(50);
	g_swash.setPitMix(50);
}

void loop()
{
	// we use A0, A1 and A2 as input pins,
	// we map raw input values (0 - 1024) to normalized values (-256 - 256)
	int16_t ail = map(analogRead(A0), 0, 1024, -256, 256);
	int16_t ele = map(analogRead(A1), 0, 1024, -256, 256);
	int16_t pit = map(analogRead(A2), 0, 1024, -256, 256);
	
	// when using the input system, first write the input to the input system
	// rc::setInput(rc::Input_AIL, ail);
	// rc::setInput(rc::Input_ELE, ele);
	// rc::setInput(rc::Input_PIT, pit);
	
	// apply swashplate mixing
	g_swash.apply(ail, ele, pit);
	// when using the input system, a simple g_swash.apply(); would have been enough
	
	// results have been writen to the output system
	// rc::getOutput(rc::Output_AIL1);
	// rc::getOutput(rc::Output_ELE1);
	// rc::getOutput(rc::Output_PIT);
	// rc::getOutput(rc::Output_ELE2); (for four servo setups)
	
	// we can then use the transformed values for further modification
	// or we can transmit them using the PPMOut class
}
