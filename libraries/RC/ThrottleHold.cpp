/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ThrottleHold.cpp
** Throttle hold functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <rc_debug_lib.h>
#include <ThrottleHold.h>


namespace rc
{
// Public functions

ThrottleHold::ThrottleHold(int16_t p_throttle, Switch p_source, SwitchState p_state)
:
InputModifier(Input_THR),
SwitchProcessor(p_source, p_state),
m_throttle(p_throttle)
{
	
}


void ThrottleHold::setThrottle(int16_t p_throttle)
{
	RC_TRACE("set throttle: %d", p_throttle);
	RC_ASSERT_MINMAX(p_throttle, -256, 256);
	
	m_throttle = p_throttle;
}


int16_t ThrottleHold::getThrottle() const
{
	return m_throttle;
}


int16_t ThrottleHold::apply(bool p_enabled, int16_t p_throttle) const
{
	RC_ASSERT_MINMAX(p_throttle, -256, 256);
	
	return p_enabled ? m_throttle : p_throttle;
}


void ThrottleHold::apply() const
{
	if (m_index != Input_None)
	{
		rc::setInput(m_index, apply(isActiveState(), rc::getInput(m_index)));
	}
}


// namespace end
}
