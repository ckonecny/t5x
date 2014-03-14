/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** aipin_example.pde
** Demonstrate analog input pin functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <AIPin.h>

// We create an AIPin on analog pin A0 by simply specifying the pin number
// The second parameter is optional, it specifies a destination in the
// input system, in this case Aileron input.
rc::AIPin g_pin(A0, rc::Input_AIL);

void setup()
{
	// say our input is limited because of physical constraints to a throw of
	// 100 to 940 and the center is a bit off (520) then we can set calibration
	g_pin.setCalibration(100, 520, 940);
	
	// if, for example, the potentiometer is mounted upside down
	// we can simply reverse the input
	g_pin.setReverse(true);
}

void loop()
{
	// all we need to do is call the read function and we get
	// a normalized value
	int16_t normalized = g_pin.read();
	// internally the raw value will be mapped on the specified range, so if
	// the raw value is 100 or below it will return -256
	// if it's 520 it'll return 0
	// and if it's 940 or above it'll return 256.
	// if it's anywhere in between it'll map it linearly.
	// we can then use the value for further modification
	
	// you can also get the value using the input system:
	normalized = rc::getInput(rc::Input_AIL);
	// various classes can perform transformations on the input system
	// for example Curve, DualRate, Expo and InputToInputMix
	// other classes can use the input system as source of their parameters
	// like the Swashplate and PlaneModel classes
}
