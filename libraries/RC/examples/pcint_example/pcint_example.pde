/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** pcint_example.pde
** Demonstrate pin change interrupt handler
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <stdio.h>


#include <rc_pcint.h>
#include <rc_uart.h>

// we need to declare our callback function2 first
void callbackForPin2(uint8_t p_pin, bool p_high, void* p_user);
void callbackForPin3and4(uint8_t p_pin, bool p_high, void* p_user);

// we'll update this counter from our callback
// since we're dealing with a variable that will be accessed from the loop
// and from an interrupt, we need to make them volatile.
// this prevents the compiler from being smart and caching it.
// every time you access a volatile variable, it will be read from memory.
volatile uint8_t counter3 = 0;
volatile uint8_t counter4 = 0;

void setup()
{
	// pin change interrupts can be used to detect changes in input pins
	// when pin change interrupts are enabled an interrupt will be triggered
	// every time the pin changes
	// pin change interrupts can be enabled for every individual pin
	
	// ArduinoRCLib offers an easy way to handle pin change interrupts
	// if you don't want to use it, comment out the following line in <rc_config.h>:
	// #define RC_USE_PCINT
	
	// If you want to enable pin change interrupts for a pin, simply call
	rc::pcint::enable(2, callbackForPin2);
	// 2 is the number of the pin you want to enable pcint for
	// the second parameter is the function that needs to be called when the interrupt occurs
	// the function needs to return void and have three parameters
	//     the first parameter is the pin number and type uint8_t
	//     the second is a bool which indicates if the pin went high or low
	//     the third is a void pointer which may contain user defined data
	//     the name of the function is up to you
	// the last parameter of the enable function is optional (not included here)
	//     whatever you pass there will be passed to the callback function when the interrupt occurs
	
	// we're going to turn the LED on when pin 2 goes high, and off when it goes low
	// like a very complicated light switch...
	pinMode(13, OUTPUT);
	digitalWrite(13, LOW);
	
	// it's safe to use the same callback function for multiple pins if you want
	// let's pass a pointer to a variable as user data
	// note that the compiler will implicitly cast the volatile uint8_t* to a volatile void*
	// we'll indicate we want to lose the volatile part by using a const_cast to a uint8_t*
	// now the compiler will gladly implicitly cast to a void*
	rc::pcint::enable(3, callbackForPin3and4, const_cast<uint8_t*>(&counter3));
	rc::pcint::enable(4, callbackForPin3and4, const_cast<uint8_t*>(&counter4));
	// both callbacks get different user data
	// it's also safe to give them the same user data
	
	// if you want to disable a pin change interrupt it use
	// rc::pcint::disable(2);
	// simply specify the pin number
	
	// we'll want some output, so we initialize uart here
	rc::uart::init(9600);
	rc::uart::setStdOut();
}


void loop()
{
	printf("count 3: %u  count 4: %u\n", counter3, counter4);
	delay(1000);
}


// this is our actual callback function
void callbackForPin2(uint8_t p_pin, bool p_high, void* p_user)
{
	// we can ignore the pin
	digitalWrite(13, p_high ? HIGH : LOW);
	// and we ignore the user parameter
}

// this is our shared callback function
void callbackForPin3and4(uint8_t p_pin, bool p_high, void* p_user)
{
	// Just a quick rant here (since you're reading this anyway)
	// as you may have noticed ArduinoRCLib and all examples only
	// use C++ style casts (reinterpret_cast, static_cast, const_cast)
	// instead of C style cast: (type)value;
	// It may seem intimidating or extremely verbose, but having various
	// cast types forces you to think about what you're doing.
	// It also helps preventing accidental casts to the wrong type since
	// you're actually telling the compiler what you're trying to achieve.
	// For more info I highly recommend Effective C++ by Scott Meyers
	// end of rant
	
	// we'll need to cast the void* back to a volatile uint8_t*
	// no need to use a const_cast, the compiler will gladly cast to volatile
	volatile uint8_t* ptr = reinterpret_cast<volatile uint8_t*>(p_user);
	
	// now dereference the pointer and increment it
	*ptr += 1;
	
	// if the pin was pin 3, the pointer will point to counter3
	// if the pin was pin 4, the pointer will point to counter4
}
