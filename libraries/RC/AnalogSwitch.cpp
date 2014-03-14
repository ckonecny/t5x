/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** DIPin.cpp
** Digital input read functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Arduino.h>

#include <AnalogSwitch.h>
#include <rc_debug_lib.h>
#include <util.h>


namespace rc
{

// Public functions

AnalogSwitch::AnalogSwitch(Switch p_source, Input p_destination)
:
SwitchProcessor(p_source),
InputSource(p_destination),
m_duration(0),
m_time(0xFFFF),
m_lastTime(0)
{
	
}


void AnalogSwitch::setDuration(uint16_t p_duration)
{
	RC_TRACE("set duration: %u", p_duration);
	RC_ASSERT_MINMAX(p_duration, 0, 10000);
	
	m_duration = p_duration;
	// instantly update, to prevent overflows and such
	m_time = 0xFFFF;
	update();
}


uint16_t AnalogSwitch::getDuration() const
{
	return m_duration;
}


int16_t AnalogSwitch::update(SwitchState p_state)
{
	uint16_t target = 0;
	switch (p_state)
	{
	case SwitchState_Up:
		target = m_duration;
		if (m_duration == 0 || m_time == 0xFFFF)
		{
			m_time = target;
			return writeInputValue(256);
		}
		break;
		
	case SwitchState_Center:
		target = m_duration / 2;
		if (m_duration == 0 || m_time == 0xFFFF)
		{
			m_time = target;
			return writeInputValue(0);
		}
		break;
		
	case SwitchState_Down:
		target = 0;
		if (m_duration == 0 || m_time == 0xFFFF)
		{
			m_time = target;
			return writeInputValue(-256);
		}
		break;
		
	default:
	case SwitchState_Disconnected:
		return writeInputValue(0);
	}
	
	uint16_t now = static_cast<uint16_t>(millis());
	uint16_t delta = now - m_lastTime;
	m_lastTime = now;
	
	if (m_time < target)
	{
		// move up
		m_time += delta;
		
		// clamp
		if (m_time > target)
		{
			m_time = target;
		}
	}
	else
	{
		// move down
		
		// clamp
		if (m_time > target + delta)
		{
			m_time = target;
		}
		else
		{
			m_time -= delta;
		}
	}
	return writeInputValue(rc::rangeToNormalized(m_time, m_duration));
}


int16_t AnalogSwitch::update()
{
	return update(getSwitchState(m_source));
}


// namespace end
}
