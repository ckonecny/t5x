/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** flycamone_example.pde
** Demonstrate how to use the FlycamOne class
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <BiStateSwitch.h>
#include <FlycamOne.h>
#include <ServoOut.h>
#include <Timer1.h>
#include <util.h>

#define SERVOS 1

uint8_t  g_pinsOut[SERVOS] = {2};            // Output pins
uint16_t g_input[SERVOS];                    // Input buffer for servoOut, microseconds
uint8_t  g_work[SERVOOUT_WORK_SIZE(SERVOS)]; // we need to have a work buffer for the ServoOut class

// ServoOut requires three buffers:
//     Pins buffer containing output pins
//     Input buffer containing input values in microseconds
//     Work buffer of SERVOOUT_WORK_SIZE(SERVOS) elements for internal calculations
// This setup removes any technical limit on the number of servos you want,
// and makes sure the library doesn't use more memory than it really needs,
// since the client code supplies the buffers.
rc::ServoOut g_ServoOut(g_pinsOut, g_input, g_work, SERVOS);

// FlycamOne object
rc::FlycamOne g_cam;

// We use a switch on digital pin 3
rc::BiStateSwitch g_switch(3);


void setup()
{
	// Initialize timer1, this is required for all features that use Timer1
	// (PPMIn/PPMOut/ServoIn/ServoOut)
	rc::Timer1::init();
	
	for (uint8_t i = 0;  i < SERVOS; ++i)
	{
		// set up output pins
		pinMode(g_pinsOut[i], OUTPUT);
		
		// put them low
		digitalWrite(g_pinsOut[i], LOW);
	}
	
	// fill the input buffer with some initial values
	g_input[0] = rc::normalizedToMicros(g_cam.update());
	
	// Let's say our camera is mounted upside down, in that case we can command
	// the camera to flip the screen in the setup function
	g_cam.setSensorMode(rc::FlycamOne::SensorMode_Flipped);
	// switching the sensor mode takes about 10 seconds, meanwhile the camera class
	// will be busy and won't accept any other commands
	// so if you want to switch to photo mode you'll have to wait until the cam object
	// is no longer busy. This goes for all commands.
	// The rule is:
	//  - it will only accept a command when it's not busy
	//  - it is busy from the moment it accepts a command until that command has been completed
	
	// Start the output
	g_ServoOut.start();
}


void loop()
{
	// record while the switch is in the up position
	if (g_switch.read() == rc::SwitchState_Up)
	{
		// not yet recording?
		if (g_cam.isRecording() == false)
		{
			// and camera is free to receive commands?
			if (g_cam.isBusy() == false)
			{
				g_cam.startRecording();
			}
		}
	}
	else
	{
		// recording?
		if (g_cam.isRecording())
		{
			// and camera is free to receive commands?
			if (g_cam.isBusy() == false)
			{
				g_cam.stopRecording();
			}
		}
	}
	
	// let the camera class do its work and update the input buffer
	g_input[0] = rc::normalizedToMicros(g_cam.update());
	
	// tell ServoOut there are new values available in the input buffer
	g_ServoOut.update();
}
