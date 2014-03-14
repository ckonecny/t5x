/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** inputchannel.cpp
** Place where incoming channel data is stored
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inputchannel.h>
#include <rc_debug_lib.h>


namespace rc
{

static uint16_t s_values[InputChannel_Count] = { 0 };


void setInputChannel(InputChannel p_channel, uint16_t p_value)
{
	RC_ASSERT(p_channel < InputChannel_Count);
	RC_CHECK_MINMAX(p_value, 750, 2250);
	s_values[p_channel] = p_value;
}


uint16_t getInputChannel(InputChannel p_channel)
{
	RC_ASSERT(p_channel < InputChannel_Count);
	return s_values[p_channel];
}


uint16_t* getRawInputChannels()
{
	return s_values;
}


// namespace end
}
