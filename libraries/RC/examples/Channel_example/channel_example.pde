/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** channel_example.pde
** Demonstrate Channel functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Channel.h>


// we define a single channel here, for the sake of simplicity
rc::Channel g_channel;

void setup()
{
	// say our servo is moving in the wrong direction,
	// we'd want to use channel reverse
	g_channel.setReverse(true);
	
	// and for some reason we want to limit the throw of our servo
	g_channel.setEndPointMin(80);
	
	// and our servo's center might be a tad bit off
	g_channel.setSubtrim(20);
	
	// furthermore, we'd like to make our servo a bit slower
	// we can specify the time it takes for the servo to travel
	// between two extremes (full throw) in deciseconds (0.1 second)
	// as an example, we'll set it to two seconds (20 deciseconds)
	g_channel.setSpeed(20);
	
	// it is also possible to use the output system as source for a channel
	// like this: g_channel.setSource(rc::Output_AIL1);
	// this will map Aileron 1 to the channel.
	// Other classes, like Swashplate and PlaneModel, can write their output
	// to the output system. This way you map output to a channel during setup
	// and don't have to deal with temporary variables in your loop
	// you can also specify the source as a constructor parameter
}

void loop()
{
	// we use A0 as input pin, we map raw input values (0 - 1024) to normalized
	// values (-256 - 256)
	// I'd recommend using the AIPin class instead of doing it this way though...
	int16_t normalized = map(analogRead(A0), 0, 1024, -256, 256);
	
	// and apply channel transformations
	normalized = g_channel.apply(normalized);
	
	// if we had used the output system we'd have to make sure Aileron 1 has a value
	// either by using a class that fills it, or setting it manually like this:
	// rc::setOutput(rc::Output_AIL1, normalized);
	// then the we wouldn't need to pass a parameter to apply
	// normalized = g_channel.apply();
	// the apply function will fetch the AIL1 value from the output system
	// this is really handy when you have an array of channels; you can just
	// iterate through the array and call apply on each channel.
	
	// we can then use the transformed value for further modification
	// or we can transmit it using the PPMOut or ServoOut class
	// you can translate the normalized value to microseconds by using the
	// functions from utils.h:
	// uint16_t micros = rc::normalizedToMicros(normalized);
	// which can then be passed to PPMOut or ServoOut
}
