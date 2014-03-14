/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** OutputChannelProcessor.cpp
** Base class for classes reading an output channel
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <OutputChannelProcessor.h>
#include <rc_debug_lib.h>


namespace rc
{

// Public functions

void OutputChannelProcessor::setSource(OutputChannel p_source)
{
	RC_TRACE("set source: %d", p_source);
	RC_ASSERT(p_source <= OutputChannel_Count);
	
	m_source = p_source;
}


OutputChannel OutputChannelProcessor::getSource() const
{
	return m_source;
}


// Protected functions

OutputChannelProcessor::OutputChannelProcessor(OutputChannel p_source)
:
m_source(p_source)
{
	
}


// namespace end
}
