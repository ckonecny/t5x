/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** FlightTimer.cpp
** Programmable Flight Timer functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Arduino.h>

#include <rc_debug_lib.h>
#include <FlightTimer.h>

// these need to be included after rc_debug_lib.h
#include <Buzzer.h>
#include <Speaker.h>


namespace rc
{

// Public functions

FlightTimer::FlightTimer(Switch p_source, SwitchState p_state)
:
SwitchProcessor(p_source, p_state),
m_time(0),
m_target(0),
m_millis(0),
m_last(0),
m_up(true)
{
	
}


void FlightTimer::setTarget(uint16_t p_target)
{
	RC_TRACE("set target: %u", p_target);
	RC_ASSERT_MINMAX(p_target, 1, 18000);
	
	m_target = static_cast<int16_t>(p_target);
	reset();
}


uint16_t FlightTimer::getTarget() const
{
	return static_cast<uint16_t>(m_target);
}


void FlightTimer::setDirection(bool p_up)
{
	RC_TRACE("set direction: %d", p_up);
	
	m_up = p_up;
	reset();
}


bool FlightTimer::getDirection() const
{
	return m_up;
}


int16_t FlightTimer::getTime() const
{
	// the direction is purely cosmetical :)
	if (m_up)
	{
		return m_time;
	}
	else
	{
		return m_target - m_time;
	}
}


void FlightTimer::reset()
{
	RC_TRACE("reset");
	
	// the direction is only cosmetical, we always start at 0 and count up
	m_time = 0;
	m_millis = 0;
	m_last = static_cast<uint16_t>(millis());
}


void FlightTimer::update(bool p_active)
{
	if (p_active)
	{
		uint16_t now = static_cast<uint16_t>(millis());
		if (now == m_last)
		{
			// called too fast
			return;
		}
		uint16_t delta = now - m_last;
		m_last = now;
		
		m_millis += delta;
		while (m_millis >= 1000)
		{
			// another second (or more? very unlikely) has passed
			m_millis -= 1000;
			
			// always count up, makes life easier
			++m_time;
			
			if (m_time == m_target)
			{
				// one second beep
			#ifdef RC_USE_BUZZER
				g_Buzzer.beep(100);
			#endif
			#ifdef RC_USE_SPEAKER
				g_Speaker.beep(4000, 100);
			#endif
				
			}
			else if (m_time < m_target && (m_target- m_time) <= 10)
			{
				// double short beep
			#ifdef RC_USE_BUZZER
				g_Buzzer.beep(10, 10, 1);
			#endif
			#ifdef RC_USE_SPEAKER
				g_Speaker.beep(4000, 10, 10, 1);
			#endif
			}
			else if ((m_time % 60) == 0)
			{
				// single short beep
			#ifdef RC_USE_BUZZER
				g_Buzzer.beep(10);
			#endif
			#ifdef RC_USE_SPEAKER
				g_Speaker.beep(4000, 10);
			#endif
			}
		}
	}
}


void FlightTimer::update()
{
	update(isActiveState());
}


// namespace end
}
