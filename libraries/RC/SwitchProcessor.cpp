/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** SwitchProcessor.cpp
** Base class for classes taking switch input
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <SwitchProcessor.h>
#include <rc_debug_lib.h>


namespace rc
{

// Public functions

void SwitchProcessor::setSource(Switch p_source)
{
	RC_TRACE("set source: %d", p_source);
	RC_ASSERT(p_source <= Switch_Count);
	
	m_source = p_source;
}


Switch SwitchProcessor::getSource() const
{
	return m_source;
}


void SwitchProcessor::setActiveState(SwitchState p_state)
{
	m_activeState = p_state;
}


SwitchState SwitchProcessor::getActiveState() const
{
	return m_activeState;
}


// Protected functions

SwitchProcessor::SwitchProcessor(Switch p_source, SwitchState p_state)
:
m_source(p_source),
m_activeState(p_state)
{
	
}


bool SwitchProcessor::isActiveState() const
{
	return m_source != Switch_None &&
		(m_activeState == SwitchState_Disconnected ||
		 getSwitchState(m_source) == m_activeState);
}


// namespace end
}
