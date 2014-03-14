/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** InputChannelSource.cpp
** Base class for classes acting as a source of input channel
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <InputChannelSource.h>
#include <rc_debug_lib.h>


namespace rc
{

// Public functions

void InputChannelSource::setDestination(InputChannel p_destination)
{
	RC_TRACE("set destination: %d", p_destination);
	RC_ASSERT(p_destination <= InputChannel_Count);
	
	m_destination = p_destination;
}


InputChannel InputChannelSource::getDestination() const
{
	return m_destination;
}


// Protected functions

InputChannelSource::InputChannelSource(InputChannel p_destination)
:
m_destination(p_destination)
{
	
}


uint16_t InputChannelSource::writeInputChannelValue(uint16_t p_value) const
{
	RC_ASSERT_MINMAX(p_value, 750, 2250);
	
	if (m_destination != InputChannel_None)
	{
		RC_ASSERT(m_destination < InputChannel_Count);
		rc::setInputChannel(m_destination, p_value);
	}
	return p_value;
}


// namespace end
}
