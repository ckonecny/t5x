/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** SwitchToggler.cpp
** Class that acts like a switch, toggling state on specified switch input
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <SwitchToggler.h>
#include <rc_debug_lib.h>


namespace rc
{

// Public functions

SwitchToggler::SwitchToggler(SwitchState p_toggleState, Switch p_index)
:
SwitchModifier(p_index),
m_toggle(p_toggleState),
m_last(p_toggleState),
m_state(p_toggleState)
{
	
}


void SwitchToggler::setToggleState(SwitchState p_state)
{
	RC_TRACE("set toggle state: %d", p_state);
	RC_ASSERT(p_state < SwitchState_Count);
	
	m_toggle = p_state;
	m_last = p_state;
	m_state = p_state;
}


SwitchState SwitchToggler::getToggleState() const
{
	return m_toggle;
}


SwitchState SwitchToggler::apply(SwitchState p_state)
{
	RC_ASSERT(p_state < SwitchState_Count);
	
	if (p_state != m_last)
	{
		m_last = p_state;
		if (p_state == m_toggle)
		{
			// toggle state matched, toggle!
			m_state = m_state == SwitchState_Up ? SwitchState_Down : SwitchState_Up;
		}
	}
	
	return m_state;
}


void SwitchToggler::apply()
{
	if (m_index != Switch_None)
	{
		rc::setSwitchState(m_index, apply(rc::getSwitchState(m_index)));
	}
}


// namespace end
}
