/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** rotaryencoder_example.pde
** Demonstrate Rotary Encoder usage
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <stdio.h>

#include <RotaryEncoder.h>
#include <rc_uart.h>

// We create a RotaryEncoder by specifying the input pins
// note that the pins need to support external interrupts
// on a Atmega 168/328 based Arduino (Uno/Nano)
// only pins 2 and 3 support external interrupt
// the last parameter indicates whether the rest state of the
// pins is low (false) or high (true)
rc::RotaryEncoder g_dial(2, 3, true);

void setup()
{
	// we're going to enable the internal pull-up resistors for the pins
	// this means that when nothing is connected to the pins, they will read HIGH
	// we connect the center pin of the rotary encoder to ground, so when one
	// of the signal pins connects it will read LOW
	// This is why we've set the third parameter of the constructor to true:
	// in rest state, both pins will read HIGH.
	
	// both pins are already in input mode, so we can enable the pull-ups by writing HIGH to them
	digitalWrite(2, HIGH);
	digitalWrite(3, HIGH);
	
	// we can set a min and max
	g_dial.setMin(0);
	g_dial.setMax(19);
	// my rotary encoder is a 20 step encoder, so a full revolution will bring the value back to 0
	
	// we'll make it wrap around, so when max overflows we'll start at min
	g_dial.setWrap(true);
	// if you want it to stop increasing at max or decreasing at min, set wrap to false
	
	// because the pins use pull-ups, the rotation is inverted, we can fix this by
	// setting the direction to reversed
	// now CW rotation increases the position, CCW decreases it
	g_dial.setReversed(true);
	
	// we will set up communications over uart so we can output some info
	rc::uart::init(9600);
	rc::uart::setStdOut();
}

void loop()
{
	// we can get the absolute position like this
	int8_t pos = g_dial.readPosition();
	
	// and a relative movement like this
	int8_t steps = g_dial.readSteps();
	// this returns the change in position since the previous readSteps
	
	printf("%d %d\n", pos, steps);
	delay(200);
}
