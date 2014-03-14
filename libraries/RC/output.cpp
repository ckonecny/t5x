/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** output.cpp
** Place where the output of various functions are stored
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <output.h>
#include <rc_debug_lib.h>


namespace rc
{

static int16_t s_values[Output_Count] = { 0 };


void setOutput(Output p_output, int16_t p_value)
{
	RC_ASSERT(p_output < Output_Count);
	RC_ASSERT(p_value == Out_Max || p_value == Out_Min ||
	          (p_value >= -358 && p_value <= 358));
	s_values[p_output] = p_value;
}


int16_t getOutput(Output p_output)
{
	RC_ASSERT(p_output < Output_Count);
	return s_values[p_output];
}


// namespace end
}
