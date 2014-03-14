/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** gyro_example.pde
** Demonstrate Gyro functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Gyro.h>


rc::Gyro g_gyro;

void setup()
{
	// set up the gyro type, heading hold type in this case
	g_gyro.setType(rc::Gyro::Type_AVCS);
	
	// you can also use Gyro in combination with the output system
	// g_gyro.setDestination(rc::Output_GYR1);
	// or specify it in the constructor
	// results will be written to the output system
}

void loop()
{
	// we use a switch to change between gyro modes
	g_gyro.setMode(digitalRead(3) == HIGH ?
	               rc::Gyro::Mode_AVCS :
	               rc::Gyro::Mode_Normal);
	
	// we use a knob to set the gain
	// we use A0 as input pin, we map raw input values (0 - 1024)
	// to a different range range (0 - 100)
	g_gyro = map(analogRead(A0), 0, 1024, 0, 100);
	
	// get the normalized channel value corresponding to the mode and gain
	int16_t chGyro = g_gyro.apply();
	
	// when using the output system, you can also get the result using
	// rc::getOutput(rc::Output_GYR1);
	// or use a Channel which uses Output_GYR1 as source!
	
	// we can now transmit this value using the PPMOut class
}
