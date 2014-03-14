/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** speaker_example.pde
** Demonstrate Speaker functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** Video: http://www.youtube.com/watch?v=tHbyathQDaU
** -------------------------------------------------------------------------*/

// please note that RC_USE_SPEAKER has to be defined in <rc_config.h>
// it cannot be used together with RC_USE_BUZZER

#include <Speaker.h>
#include <Timer2.h>

// you can define your own speaker
rc::Speaker g_speaker2(8);
// or use the global speaker rc::g_Speaker

void setup()
{
	// call the init function of the timer before any other function.
	rc::Timer2::init();
	
	// we will use the global speaker
	// it's always initialized on pin 8, but we want to use pin 7,
	// just because we want to demonstrate we can
	rc::g_Speaker.setPin(7);
	// and we have our own second speaker on pin 8: g_speaker2
	
	// it's important to know that all speaker object share timer2
	// if one speaker starts, it will stop ANY active speaker
	// if you call the stop function of a speaker, it will only stop THAT speaker
	// if you change the pin of a speaker, it will stop THAT speaker
	// speakers are identified by their pin, calling stop on a speaker will in fact stop other speakers
	//     if they share the same pin!
}


void loop()
{
	// you can tell the speaker to beep for a certain amount of time, units are 0.01 seconds
	// you'll also have to specify the frequency, we'll play a C4 (261.64 Hz)
	rc::g_Speaker.beep(262, 10); // beep for 0.1 second, max value is 250, or 2.5 seconds
	delay(1000); // wait for 1 second
	
	// we can also tell it to beep multiple times (we'll use a C3, 130.81 Hz)
	// we use speaker 2 now
	g_speaker2.beep(131, 10, 20, 4); // beep for 0.1 second, wait 0.2 seconds, repeat 4 times (5 beeps total)
	delay(2000); // wait two seconds
	
	// please note that the beep function will return almost instantly and executes asynchronously;
	// the beeps will be running while other code can be executed. That's why we use a delay to make
	// sure the beeps have finished.
	
	// calling beep again will stop any speakers that are currently active
	rc::g_Speaker.beep(165, 200); // E3, 2 seconds
	delay(100); // sleep 0.1 seconds
	// speaker 2 will stop speaker 1
	g_speaker2.beep(262, 2);   // C4, 0.02 seconds
	delay(1000);
	// as you will notice, there won't be a 2 second beep since it's cut off by the other speaker
	
	// there's also a stop function
	g_speaker2.beep(349, 2000); // F4, 2 seconds
	rc::g_Speaker.stop(); // Silence! Not? Stop will only stop the speaker you call the function on.
	delay(500);
	g_speaker2.stop(); // Now it becomes silent!
	delay(1000);
}
