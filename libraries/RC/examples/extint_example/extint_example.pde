/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** extint_example.pde
** Demonstrate external interrupt handler
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <stdio.h>


#include <rc_extint.h>
#include <rc_uart.h>

// we need to declare our callback functions first
void callbackForPin2(uint8_t p_pin, void* p_user);
void callbackForPin3(uint8_t p_pin, void* p_user);

// we'll update this counter from our callback
// since we're dealing with a variable that will be accessed from the loop
// and from an interrupt, we need to make them volatile.
// this prevents the compiler from being smart and caching it.
// every time you access a volatile variable, it will be read from memory.
volatile uint8_t counter2 = 0;
volatile uint8_t counter3 = 0;

void setup()
{
	// The Arduinos have a few pins which cause their own interrupts
	// these are so called external interrupts. They're usually used when
	// external hardware is connected to tell the Arduino something happened.
	// There are four types of states that can be used as a trigger
	//     rc::extint::ISC_Low    -Pin is low           
	//     rc::extint::ISC_Change -Pin has changed
	//     rc::extint::ISC_Fall   -Pin went low (fall)
	//     rc::extint::ISC_Rise   -Pin went high (rise)
	// For an Arduino Uno or Nano (both Atmega 328 or 168) only pins 2 and 3 can be used
	// other Arduinos may have more pins for this, consult the datasheet for more info.
	
	// ArduinoRCLib offers an easy way to handle external interrupts
	// But, if you don't want to use it, comment out the following line in <rc_config.h>:
	// #define RC_USE_EXTINT
	// All ArduinoRCLib classes that use external interrupts have a publicly available
	// interrupt handler which needs to be called from your interrupt service routine.
	
	// If you want to enable external interrupts for a pin, simply call
	rc::extint::enable(2, rc::extint::ISC_Rise, callbackForPin2, const_cast<uint8_t*>(&counter2));
	// 2 is the number of the pin you want to enable extint for
	// the second parameter is the state which should trigger the interupt
	// the third parameter is the function that needs to be called when the interrupt occurs
	// the function needs to return void and have two parameters
	//     the first parameter is the pin number and type uint8_t
	//     the second is a void pointer which may contain user defined data
	//     the name of the function is up to you
	// the last parameter of the enable function is optional
	//     whatever you pass there will be passed to the callback function when the interrupt occurs
	
	// we do the same for pin 3
	// note the cast, it's a bit complicated but I'll explain quickly
	// the compiler expects a void* as last parameter, but we're passing a volatile uint8_t*
	// the compiler has no problems implicitly casting a uint8_t* to a void*, but it will never
	// implicitly cast away the volatile part (or const for that matter). This is why we'll
	// use a const_cast to remove the volatile part, the compiler will implicitly cast the rest
	// to a void*
	rc::extint::enable(3, rc::extint::ISC_Fall, callbackForPin3, const_cast<uint8_t*>(&counter3));
	
	// we're going to turn the LED on when pin 2 goes high, and off when pin 3 goes low
	// like a very complicated light switch...
	pinMode(13, OUTPUT);
	digitalWrite(13, LOW);
	
	// it's safe to use the same callback function for multiple pins if you want
	// let's pass a pointer to a variable as user data
	// note that the compiler will implicitly cast the volatile uint8_t* to a volatile void*
	// we'll indicate we want to lose the volatile part by using a const_cast to a uint8_t*
	// now the compiler will gladly implicitly cast to a void*
	// both callbacks get different user data
	// it's also safe to give them the same user data
	
	// if you want to disable an external interrupt it use
	// rc::extint::disable(2);
	// simply specify the pin number
	
	// we'll want some output, so we initialize uart here
	rc::uart::init(9600);
	rc::uart::setStdOut();
}


void loop()
{
	printf("count 2: %u  count 3: %u\n", counter2, counter3);
	delay(1000);
}


// this is our actual callback function
void callbackForPin2(uint8_t p_pin, void* p_user)
{
	// we can ignore the pin
	digitalWrite(13, HIGH);
	
	// we'll need to cast the void* back to a volatile uint8_t*
	// no need to use a const_cast, the compiler will gladly cast to volatile
	volatile uint8_t* ptr = reinterpret_cast<volatile uint8_t*>(p_user);
	
	// now dereference the pointer and increment it
	*ptr += 1;
}

// this is our shared callback function
void callbackForPin3(uint8_t p_pin, void* p_user)
{
	// we can ignore the pin
	digitalWrite(13, LOW);
	
	// we'll need to cast the void* back to a volatile uint8_t*
	// no need to use a const_cast, the compiler will gladly cast to volatile
	volatile uint8_t* ptr = reinterpret_cast<volatile uint8_t*>(p_user);
	
	// now dereference the pointer and increment it
	*ptr += 1;
}
