/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ppmout_example.pde
** Demonstrate Pulse Position Modulation Output functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <outputchannel.h>
#include <PPMOut.h>
#include <Timer1.h>


#define CHANNELS 4

uint8_t  g_pins[CHANNELS] = {A0, A1, A2, A3}; // Input pins

// PPMOut needs to be told how many channels it needs to output
rc::PPMOut g_PPMOut(CHANNELS);

void setup()
{
	// Initialize timer1, this is required for all features that use Timer1
	// (PPMIn/PPMOut/ServoIn/ServoOut)
	rc::Timer1::init();
	
	for (uint8_t i = 0;  i < CHANNELS; ++i)
	{
		// set up input pins
		pinMode(g_pins[i], INPUT);
		
		// fill input buffer, convert raw values to microseconds
		// we'll need to cast our iterator to an OutputChannel, but ugly but safe
		rc::setOutputChannel(static_cast<rc::OutputChannel>(i), map(analogRead(g_pins[i]), 0, 1024, 1000, 2000));
	}
	
	// initialize PPMOut with some settings
	g_PPMOut.setPulseLength(448);   // pulse length in microseconds
	g_PPMOut.setPauseLength(10448); // length of pause after last channel in microseconds
	// note: this is also called the end of frame, or start of frame, and is usually around 10ms
	
	// start PPMOut, use pin 9 (pins 9 and 10 are preferred)
	g_PPMOut.start(9);
}

void loop()
{
	// update the input buffer
	for (uint8_t i = 0;  i < CHANNELS; ++i)
	{
		// fill input buffer, convert raw values to microseconds
		rc::setOutputChannel(static_cast<rc::OutputChannel>(i), map(analogRead(g_pins[i]), 0, 1024, 1000, 2000));
	}
	
	// tell PPMOut there are new values available in the input buffer
	g_PPMOut.update();
}
