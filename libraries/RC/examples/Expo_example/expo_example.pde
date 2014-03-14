/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** expo_example.pde
** Demonstrate Expo functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Expo.h>


rc::Expo g_expo;

void setup()
{
	// we use 30% expo, dumb down the sensitivity in the center a bit, if we
	// want to make it more twitchy around the center we use a negative value
	g_expo = 30;
	
	// Expo can also be used in combination with the input system
	// g_expo.setIndex(rc::Input_AIL);
	// or specify it as a constructor parameter
	// Then input will be read from (and results will be written back to) the input system
}

void loop()
{
	// we use A0 as input pin, we map raw input values (0 - 1024) to normalized
	// values (-256 - 256)
	int16_t normalized = map(analogRead(A0), 0, 1024, -256, 256);
	
	// and apply expo
	normalized = g_expo.apply(normalized);
	
	// when using the input system, simply do
	// g_expo.apply();
	// just make sure the input source has been set with some value
	// either manually (rc::setInput(rc::Input_AIL, somevalue)) or by
	// some input source (like AIPin)
	
	// we can then use the transformed value for further modification
	// or we can transmit it using the PPMOut class
}
