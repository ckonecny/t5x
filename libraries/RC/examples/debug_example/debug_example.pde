/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** debug_example.pde
** Demonstrate debugging features
**
** Note:
** You may get compiler warnings when compiling this like:
** warning: only initialized variables can be placed into program memory area
** It is safe to ignore these, this is a compiler bug
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/


// Set the debug level for this compile unit (all code in this file)
// 0 = OFF - asserts disabled
// 1 = ERROR - Asserts and error messages enabled
// 2 = WARN  - Warnings enabled
// 3 = INFO  - Informational messages enabled
// 4 = DEBUG - Debugging messages enabled
// 5 = TRACE - Trace messages enabled
#define RC_DEBUG_LEVEL 4

// include this file for the debugging functions
#include <rc_debug.h>
// if you hadn't defined RC_DEBUG_LEVEL before including rc_debug.h, the
// debug level would've been set to the global level RC_GLOBAL_LEVEL
// this is defined in rc_config.h
// So if you want to disable debugging completely, modify rc_config.h to set
// the global level to 0
// The library classes themselves have their debug level defined in
// rc_debug_lib.h named RC_LIB_LEVEL. Change its define if you want to turn
// lib debugging on or off.

// we're going to use serial (uart) as stdout, so we need to include that
#include <rc_uart.h>


void setup()
{
	// setup uart
	rc::uart::init(9600); // specify baud rate, match this with your serial window
	
	// make uart implement stdout
	rc::uart::setStdOut();
	// we need to do this since the debug functions write everything to stdout
	
	// There are a bunch of debugging functions available
	// These are defined as macros, based on the debug level, calls to these
	// macros will be included or stripped from your project.
	
	// First is the trace message, these are usefull for tracking the flow
	// of your code. These are only available when debug level is 5 or higher
	// These are incredibly verbose and will cause a flood of output on your console
	RC_TRACE("This is a trace message");
	
	// Second is the debug message. Use these if you want to show the results of
	// calculations or some other kind of debugging information.
	// These calls are included in debug level 4 or higher
	// It's also possible to include parameters in all debug messaging functions, like this:
	RC_DEBUG("This is a debug message with %d %s", 2, "parameters");
	
	// Third we have the info message. Use this for informational messages, available at level 3 and higher
	RC_INFO("This is an info message");
	
	// Next we have warnings, these are more serious and will require attention, level 2 and up
	RC_WARN("This is a warning message");
	
	// Lastly we have errors, use these for detecting programming errors, level 1 and up
	RC_ERROR("This is an error message");
	
	// At debug levels 1 and up, a few asserts are also available. With asserts you may check
	// for certain conditions and halt your program if those conditions fail.
	// For example, you can check input parameters or register states. This makes it easier
	// to catch programming errors.
	
	// First we have the simplest assert
	// By the way, when running this example you'll want to comment the assert out
	// or make sure the code 'll pass the asserts ;)
	uint8_t x = 0;
	RC_ASSERT(x > 0);
	// This will trigger the assert since (x > 0) == false
	// it will show an error message showing the file name, line number and a message telling
	// the assertion x > 0 failed. The program will halt and not do anything anymore.
	
	// Second we have an assert with custom message, you can also pass parameters
	RC_ASSERT_MSG(x > 0, "Oh no! x (%d) is not larger than 0!", x);
	
	// Lastly we have an assert for checking whether a value falls within a range, handy for checking parameters
	RC_ASSERT_MINMAX(x, 1, 100); // will fail if x < 1 or x > 100
	
	// Sometimes you still want to display some sort of error message conditionally,
	// but you don't want to halt the program, in that case, use RC_CHECK
	// This is available at error levels 2 and up, and will display warnings
	// when the condition is not met
	RC_CHECK(x > 0);
	RC_CHECK_MSG(x > 0, "Oh no! x (%d is not larger than 0!", x);
	RC_CHECK_MINMAX(x, 1, 100);
	
	// One last technical detail:
	// All the error strings you pass to these functions are automatically placed in PROGMEM
	// Filenames and line number are automatically generated and filenames are also in PROGMEM
	// Parameters are NOT placed in PROGMEM automatically, if you want to pass strings as
	// parameters, use the PSTR macro to place them in PROGMEM (only works for static strings)
	// and use %S as formatter instead of %s. For example:
	bool b = false;
	RC_DEBUG("b is %S", b ? PSTR("true") : PSTR("false"));
	
	// Now you might wonder, what debug level should I use?
	// During development, use at least level 2 or higher, this way you'll catch all the
	// asserts and warnings which could indicate programming errors.
	// When building a release build, turn all debugging features off to reduce
	// the memory footprint and increase performance
	
}

void loop()
{
	
}
