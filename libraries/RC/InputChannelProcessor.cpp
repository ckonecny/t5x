/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** InputChannelProcessor.cpp
** Base class for classes reading an input channel
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <InputChannelProcessor.h>
#include <rc_debug_lib.h>


namespace rc
{

// Public functions

void InputChannelProcessor::setSource(InputChannel p_source)
{
	RC_TRACE("set source: %d", p_source);
	RC_ASSERT(p_source <= InputChannel_Count);
	
	m_source = p_source;
}


InputChannel InputChannelProcessor::getSource() const
{
	return m_source;
}


// Protected functions

InputChannelProcessor::InputChannelProcessor(InputChannel p_source)
:
m_source(p_source)
{
	
}


// namespace end
}
