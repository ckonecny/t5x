/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** flighttimer_example.pde
** Demonstrate Flight Timer functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** Video: http://www.youtube.com/watch?v=bZchL4sjCWs
** -------------------------------------------------------------------------*/

#include <BiStateSwitch.h>
#include <FlightTimer.h>
#include <Timer2.h>


// create a switch on pin 3
rc::BiStateSwitch g_switch(3, rc::Switch_A);

// create a flight timer, active when switch A is up
rc::FlightTimer g_timer(rc::Switch_A, rc::SwitchState_Up);


void setup()
{
	// call the init function of the timer before any other function. We need this
	// for the buzzer or speaker, whichever is being used
	rc::Timer2::init();
	
	// we'll want to set a target for the timer
	g_timer.setTarget(30); // 30 seconds
	
	// and a direction in which the timer will be counting, let's count down
	g_timer.setDirection(false); // false is down, true is up
	
	// if you don't have a buzzer/speaker, set the buzzer/speaker pin to 13
#if 0 // set to 1 if you want the LED to blink
#ifdef RC_USE_BUZZER
	g_buzzer.setPin(13);
#endif
#ifdef RC_USE_SPEAKER
	g_speaker.setPin(13);
#endif
#endif
}


void loop()
{
	// read the switch
	g_switch.read();
	
	// and update the timer
	g_timer.update();
	
	// you can get the remaining time using getTime
	if (g_timer.getTime() < -90)
	{
		// since we're counting down, the timer will start at the target (30 sec)
		// and count down, after reaching zero the timer will go negative
		// we're going to reset the timer 2 minutes after we've started
		g_timer.reset();
	}
	
	// When you run this example you will notice the following behavior:
	// When the timer has reached 0 (or target when counting up) you'll hear a 1 second beep
	// 10 seconds before that you'll hear a short double beep every second
	// every minute you'll hear a short single beep (also after target has been reached)
}
