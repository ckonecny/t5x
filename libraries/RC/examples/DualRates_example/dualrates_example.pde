/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** dualrates_example.pde
** Demonstrate Dual Rates functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <DualRates.h>

// we create two rates, one for normal and one for stunt mode
rc::DualRates g_rates[2];

void setup()
{
	// we set up two rates, one for each flight mode
	g_rates[0] = 80;  // normal mode, 80% response
	g_rates[1] = 100; // stunt mode, we want faster response here
	
	// we can also use DualRates in combination with the input system
	// you'll have to specify an index to the input system on which the
	// DualRates have to work
	// g_rates[0].setIndex(rx::Input_AIL);
	// or specify it as a constructor parameter
}

void loop()
{
	// we use A0 as input pin, we map raw input values (0 - 1024) to normalized
	// values (-256 - 256)
	int16_t normalized = map(analogRead(A0), 0, 1024, -256, 256);
	
	// and apply the rates, we use digital pin 3 as a flight mode switch
	normalized = g_rates[digitalRead(3)].apply(normalized);
	
	// when using the input system the above line looks like this:
	// g_rates[digitalRead(3)].apply();
	// provided that Input_AIL had been set either manually or by some other class like AIPin
	
	// we can then use the transformed value for further modification
	// or we can transmit it using the PPMOut class
}
