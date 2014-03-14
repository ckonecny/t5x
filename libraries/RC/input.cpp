/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** input.cpp
** Place where the input for various functions are stored
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <input.h>
#include <rc_debug_lib.h>


namespace rc
{

static int16_t s_values[Input_Count] = { 0 };


void setInput(Input p_input, int16_t p_value)
{
	RC_ASSERT(p_input < Input_Count);
	RC_ASSERT_MINMAX(p_value, -358, 358);
	s_values[p_input] = p_value;
}


int16_t getInput(Input p_input)
{
	RC_ASSERT(p_input < Input_Count);
	return s_values[p_input];
}


// namespace end
}
