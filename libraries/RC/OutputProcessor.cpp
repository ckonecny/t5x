/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** OutputProcessor.cpp
** Base class for classes taking output
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <OutputProcessor.h>
#include <rc_debug_lib.h>


namespace rc
{

// Public functions

void OutputProcessor::setSource(Output p_source)
{
	RC_TRACE("set source: %d", p_source);
	RC_ASSERT(p_source <= Output_Count);
	
	m_source = p_source;
}


Output OutputProcessor::getSource() const
{
	return m_source;
}


// Protected functions

OutputProcessor::OutputProcessor(Output p_source)
:
m_source(p_source)
{
	
}


// namespace end
}
