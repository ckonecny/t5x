/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** servoin_example.pde
** Demonstrate Servo Signal Input functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inputchannel.h>
#include <ServoIn.h>
#include <Timer1.h>

// we specify the pins in progmem
static const prog_uint8_t s_pins[RC_MAX_CHANNELS] = {8, 9, 10, 11};

rc::ServoIn g_ServoIn;


void setup()
{
	// Initialize timer1, this is required for all features that use Timer1
	// (PPMIn/PPMOut/ServoIn/ServoOut)
	rc::Timer1::init();
	
	// we need to tell ServoIn which pins to use
	g_ServoIn.setPins(s_pins);
	
	// it's also possible to set pins individually
	g_ServoIn.setPin(0, 8); // Servo 0 uses pin 8
	
	// ServoIn will take care of all pin change interrupts and will set pin modes
	// if you'd rather handle the pin change interrupts yourself, you need to edit rc_config.h
	// and comment out the line that says #define RC_USE_PCINT
	// you'll need to set up pin change interrupts yourself and call pinChanged(p_servo, p_high)
	// from the interrupt handler.
	
	// start listening
	g_ServoIn.start();
}

void loop()
{
	// update incoming values
	g_ServoIn.update();
	
	// handle servo values here, stored in rc::getInputChannel()
	// or get the raw pointer to the buffer using rc::getRawInputChannels()
}
