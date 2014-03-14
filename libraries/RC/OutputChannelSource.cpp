/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** OutputChannelSource.cpp
** Base class for classes acting as a source of output channel
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <OutputChannelSource.h>
#include <rc_debug_lib.h>


namespace rc
{

// Public functions

void OutputChannelSource::setDestination(OutputChannel p_destination)
{
	RC_TRACE("set destination: %d", p_destination);
	RC_ASSERT(p_destination <= OutputChannel_Count);
	
	m_destination = p_destination;
}


OutputChannel OutputChannelSource::getDestination() const
{
	return m_destination;
}


// Protected functions

OutputChannelSource::OutputChannelSource(OutputChannel p_destination)
:
m_destination(p_destination)
{
	
}


uint16_t OutputChannelSource::writeOutputChannelValue(uint16_t p_value) const
{
	RC_ASSERT_MINMAX(p_value, 750, 2250);
	
	if (m_destination != OutputChannel_None)
	{
		RC_ASSERT(m_destination < OutputChannel_Count);
		rc::setOutputChannel(m_destination, p_value);
	}
	return p_value;
}


// namespace end
}
