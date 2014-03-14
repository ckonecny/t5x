/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** uart_example.pde
** Demonstrate uart functions
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <stdio.h>
#include <avr/pgmspace.h>

#include <rc_uart.h>


void setup()
{
	// First initialize uart by setting the baud rate
	rc::uart::init(9600);
	
	// Then you can tell it to override stdout
	rc::uart::setStdOut();
	
	// and override stdin
	rc::uart::setStdIn();
	
	// now we can use all sorts of functions from stdio.h
	
	// lame, but it works!
	puts("Hello world!");
	
	// It's a good habit to put static strings in progmem
	// you can use the macro PSTR for that, it's defined in <avr/pgmspace.h>
	// use the *_P variants of the standard file functions
	puts_P(PSTR("Hello PROGMEM world!"));
	// you're going to get some compiler warnings
	// (if you've set the compiler output to verbose)
	// but you can ignore those, it's a known compiler bug
	
	// printf also works ofcourse
	// in order to use PROGMEM strings as an argument, use %S instead of %s
	printf_P(PSTR("Hello from %s and %S\n"), "RAM", PSTR("PROGMEM"));
	
	// you can also use stdout as file pointer, it's the same
	fputs_P(PSTR("To stdout!"), stdout);
}


void loop()
{
	// create a small echo program!
	int c = fgetc(stdin);
	fputc(c, stdout);
}
