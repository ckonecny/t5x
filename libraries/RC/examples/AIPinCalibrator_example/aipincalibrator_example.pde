/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** aipincalibrator_example.pde
** Demonstrate analog input pin functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <AIPinCalibrator.h>
#include <rc_uart.h>

// We create an AIPin on analog pin A0 by simply specifying the pin number
// The second parameter is optional, it specifies a destination in the
// input system, in this case Aileron input.
rc::AIPin g_pin(A0, rc::Input_AIL);

// we also create a calibrator object, which may be recycled for other AIPins
rc::AIPinCalibrator g_cal(&g_pin);

// we use a global variable to keep track of whether we've calibrated or not
bool g_calibrated = false;

void setup()
{
	// First initialize uart by setting the baud rate
	rc::uart::init(9600);
	
	// Then you can tell it to override stdout
	rc::uart::setStdOut();
	
	
	// We'll use pin 13 (LED) as an indicator that calibration has completed
	pinMode(13, OUTPUT);
	digitalWrite(13, LOW);
	
	g_cal.start(); // let's start the calibration process
}

void loop()
{
	// make sure you move the stick/pot around a few times to its extremes (or not)
	// while we're calibrating. Move it back to the center and keep it there
	// when you think you're done.
	if (g_calibrated == false)
	{
		// simply call update every time, this is a no-op when there's nothing
		// left to calibrate
		g_cal.update();
		
		if (g_cal.isDone())
		{
			g_calibrated = true;
			g_cal.stop();
			digitalWrite(13, HIGH); // turn on the LED to show we're done
		}
	}
	else
	{
		uint16_t normalized = g_pin.read();
		// now we have a normalized and calibrated value
	}
}
