/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** retracts_example.pde
** Demonstrate Retracts functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** Demonstration: https://www.youtube.com/watch?v=wCi2PpY_LIs
** -------------------------------------------------------------------------*/

#include <BiStateSwitch.h>
#include <Retracts.h>
#include <ServoOut.h>
#include <Timer1.h>
#include <util.h>

#define SERVOS 2

uint8_t  g_pinsOut[SERVOS] = {2, 3};          // Output pins
uint16_t g_input[SERVOS];                     // Input buffer for servoOut, microseconds
uint8_t  g_work[SERVOOUT_WORK_SIZE(SERVOS)];  // we need to have a work buffer for the ServoOut class

// ServoOut requires three buffers:
//     Pins buffer containing output pins
//     Input buffer containing input values in microseconds
//     Work buffer of SERVOOUT_WORK_SIZE(SERVOS) elements for internal calculations
// This setup removes any technical limit on the number of servos you want,
// and makes sure the library doesn't use more memory than it really needs,
// since the client code supplies the buffers.
rc::ServoOut g_ServoOut(g_pinsOut, g_input, g_work, SERVOS);

// The Retracts class supports various setups, here we go for the fancy dual servo setup
// One servo to control the doors, the other to control the gear
// We'll use Switch_A as input
rc::Retracts g_Retracts(rc::Retracts::Type_Dual, rc::Switch_A);

// We use a switch on digital pin 4 as input, write results to Switch_A
rc::BiStateSwitch g_switch(4, rc::Switch_A);

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
	
	// To initialize the retracts we'll have to set the speed of the doors and gear
	g_Retracts.setDoorsSpeed(4000); // The time it takes to open/close the doors in milliseconds
	g_Retracts.setGearSpeed(6000); // The time it takes to lower/raise the gear in milliseconds
	
	// fill the input buffer with some initial values
	// this is safe since Retracts initializes with gear lowered and doors open by default
	g_input[0] = rc::normalizedToMicros(g_Retracts.getDoorsPosition());
	g_input[1] = rc::normalizedToMicros(g_Retracts.getGearPosition());
	
	// we can also specify a delay, with this there will be a short pause between the movement of
	// the doors and the gear. If you specify a negative value there will be a overlap in movement.
	// In this case we want the gear to start lowering 1.5 seconds before the doors have opened completely
	// it also means the doors will start closing 1.5 seconds before the gear has been raised completely.
	// If we wanted a delay between the movement of the doors and gear, we'd have to specify a positive value.
	g_Retracts.setDelay(-1500);
	
	g_ServoOut.start();
}

void loop()
{
	// read the switch
	g_switch.read(); // writes to rc::Switch_A
	
	// update the retracts, you'll need to do this often to get a smooth motion
	g_Retracts.update();
	
	// update the input buffer
	// the Retracts class works with normalized values, so you'll need to convert them to microseconds
	// because the ServoOut class works with micros
	// normally you at least would want to do some channel transformations like endpoints and channel
	// reverse to make sure your servos aren't binding and are moving in the right direction,
	// but for the sake of this example we'll just ignore that for now.
	g_input[0] = rc::normalizedToMicros(g_Retracts.getDoorsPosition());
	g_input[1] = rc::normalizedToMicros(g_Retracts.getGearPosition());
	// Retracts also writes to the output system (Output_GEAR and Output_DOOR)
	// You can just use two rc::Channels and tell them to use those indices as source
	
	// tell ServoOut there are new values available in the input buffer
	g_ServoOut.update();
}
