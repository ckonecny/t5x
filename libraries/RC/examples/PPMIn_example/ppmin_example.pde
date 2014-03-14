/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ppmin_example.pde
** Demonstrate Pulse Position Modulation Input functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <PPMIn.h>
#include <Timer1.h>


rc::PPMIn g_PPMIn;

void setup()
{
	// Initialize timer1, this is required for all features that use Timer1
	// (PPMIn/PPMOut/ServoIn/ServoOut)
	rc::Timer1::init();
	
	// We use pin 8 as PPM input pin
	g_PPMIn.setPin(8);
	
	// PPMIn will handle the pin change interrupts, if you want to do this yourself
	// remove the line #define RC_USE_PCINT from rc_config.h and call g_PPMIn.pinChanged(p_high)
	// from your interrupt handler.
	
	// set a timeout (default 500 milliseconds)
	g_PPMIn.setTimeout(1000);
	
	// start listening
	g_PPMIn.start();
}


void loop()
{
	// update incoming values
	g_PPMIn.update();
	
	if (g_PPMIn.isStable())
	{
		// do magic, incoming values available in rc::getInputChannel() in microseconds.
		// or use rc::getRawInputChannels() to get a pointer to the raw buffer
		// see <inputchannel.h>
	}
	else if (g_PPMIn.isLost())
	{
		// signal has been lost (no new valid frames for 'timeout' milliseconds)
	}
}
