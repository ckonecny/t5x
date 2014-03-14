/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** buzzer_example.pde
** Demonstrate Buzzer functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

// please note that RC_USE_BUZZER has to be defined in <rc_config.h>
// it cannot be used together with RC_USE_SPEAKER

#include <Buzzer.h>
#include <Timer2.h>

// you can define your own buzzer
//rc::Buzzer g_buzzer(8);
// or use the global buzzer rc::g_Buzzer

void setup()
{
	// call the init function of the timer before any other function.
	rc::Timer2::init();
	
	// we will use the global buzzer
	// it's always initialized on pin 8, but we want to use pin 7, just because we can
	rc::g_Buzzer.setPin(7);
	
	// it's possible to have multiple buzzers on different pins, but they'll all share timer2
	// -if a buzzer beeps, it will first stop ANY other active buzzers
	// -if you call the stop function of a buzzer, it will stop THAT buzzer if it was active
	// -it you change the pin of a buzzer, it will stop THAT buzzer if it was active
	// -buzzers are identified by their pin, calling stop on a buzzer will in fact stop other buzzers
	//     if they have the same pin!
}


void loop()
{
	// you can tell the buzzer to beep for a certain amount of time, units are 0.01 seconds
	rc::g_Buzzer.beep(10); // beep for 0.1 second, max value is 250, or 2.5 seconds
	delay(1000); // wait for 1 second
	
	// we can also tell it to beep multiple times
	rc::g_Buzzer.beep(10, 20, 4); // beep for 0.1 second, wait 0.2 seconds, repeat 4 times (5 beeps total)
	delay(2000); // wait two seconds
	
	// please note that the beep function will return almost instantly and executes asynchronously;
	// the beeps will be running while other code can be executed. That's why we use a delay to make
	// sure the beeps have finished.
	
	// calling beep again will stop any beeps that are currently active
	rc::g_Buzzer.beep(200); // 2 seconds
	rc::g_Buzzer.beep(2);   // 0.02 seconds
	delay(1000);
	// as you will notice, there won't be a 2 second beep since it's almost instantly cut off by the second beep call
	
	// there's also a stop function
	rc::g_Buzzer.beep(200); // 2 seconds
	rc::g_Buzzer.stop();    // Silence!
	delay(1000);
	// again, the beep will be cut off.
}
