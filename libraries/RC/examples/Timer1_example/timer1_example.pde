/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** timer1_example.pde
** Demonstrate Timer1 functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Timer1.h>

// forward declaration of callback functions
void callbackA();
void callbackOVF();

void setup()
{
	// call the init function before any other function.
	// We use debug mode, otherwise everything will go way too fast to see
	rc::Timer1::init(true);
	
	// we'll use pin A0 as analog input
	pinMode(A0, INPUT);
	
	// and pin 9 as output
	pinMode(9, OUTPUT);
	digitalWrite(9, HIGH);
	
	OCR1A = map(analogRead(A0), 0, 1024, 0, 65535);
	
	// we want a compare match handler for OCR1A and overflows
	rc::Timer1::setCompareMatch(true, true,  callbackA);
	rc::Timer1::setOverflow(true, callbackOVF);
	
	// we start the timer
	rc::Timer1::start();
	
	// The timer will be running at a prescaler of 1024 (debug)
	// CPU frequency is 16 MHz
	// Timer frequency will be 15625 Hz
	// The timer will overflow after 65536 ticks, or about 4.2 seconds
	// 
	// In normal mode, the prescaler will be set to 8
	// Timer frequency will be 2 MHz
	// Every tick is 0.5 microseconds
	// Timer will overflow after 32768 microseconds, about 3.5 milliseconds,
	// roughly 30.5 times per second
}


void loop()
{
	// we base the compare registers on analog input
	// by changing the analog input (twisting a potentiometer) we can
	// change the time the connected LED is on
	OCR1A = map(analogRead(A0), 0, 1024, 0, 65536);
	delay(1000);
}


// implementation of callback function
void callbackA()
{
	digitalWrite(9, LOW);
}

void callbackOVF()
{
	digitalWrite(9, HIGH);
}
