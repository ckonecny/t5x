/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Governor.cpp
** Governor functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Governor.h>
#include <rc_debug_lib.h>
#include <util.h>


namespace rc
{

// Public functions

Governor::Governor(Switch p_source, Output p_destination)
:
SwitchProcessor(p_source),
OutputSource(p_destination),
m_holdDirection(false),
m_holdSwitch(Switch_None),
m_holdSwitchState(SwitchState_Down)
{
	m_rates[rc::SwitchState_Down]   = 0;
	m_rates[rc::SwitchState_Center] = 50;
	m_rates[rc::SwitchState_Up]     = 100;
}


void Governor::setDownRate(uint8_t p_rate)
{
	RC_TRACE("set down rate: %u", p_rate);
	RC_ASSERT_MINMAX(p_rate, 0, 100);
	
	m_rates[rc::SwitchState_Down] = p_rate;
}


uint8_t Governor::getDownRate() const
{
	return m_rates[rc::SwitchState_Down];
}


void Governor::setCenterRate(uint8_t p_rate)
{
	RC_TRACE("set center rate: %u", p_rate);
	RC_ASSERT_MINMAX(p_rate, 0, 100);
	
	m_rates[rc::SwitchState_Center] = p_rate;
}


uint8_t Governor::getCenterRate() const
{
	return m_rates[rc::SwitchState_Center];
}


void Governor::setUpRate(uint8_t p_rate)
{
	RC_TRACE("set up rate: %u", p_rate);
	RC_ASSERT_MINMAX(p_rate, 0, 100);
	
	m_rates[rc::SwitchState_Up] = p_rate;
}


uint8_t Governor::getUpRate() const
{
	return m_rates[rc::SwitchState_Up];
}


void Governor::setHoldDirection(bool p_posLimit)
{
	m_holdDirection = p_posLimit;
}


bool Governor::getHoldDirection() const
{
	return m_holdDirection;
}


void Governor::setHold(const ThrottleHold& p_hold)
{
	m_holdSwitch      = p_hold.getSource();
	m_holdSwitchState = p_hold.getActiveState();
}


void Governor::disableHold()
{
	m_holdSwitch = Switch_None;
}


int16_t Governor::apply(SwitchState p_state, bool p_hold) const
{
	if (p_hold)
	{
		return m_holdDirection ? Out_Max : Out_Min;
	}
	if (p_state == SwitchState_Disconnected)
	{
		return 0;
	}
	
	int8_t rate = (static_cast<int8_t>(m_rates[p_state]) - 50) * 2; // [-100 - 100]
	
	return rc::mix(256, rate);
}


int16_t Governor::apply() const
{
	if (m_source != Switch_None)
	{
		bool hold = 
			m_holdSwitch != Switch_None &&
			(m_holdSwitchState == SwitchState_Disconnected ||
			getSwitchState(m_holdSwitch) == m_holdSwitchState);
		return writeOutputValue(apply(getSwitchState(m_source), hold));
	}
	return 0;
}

// namespace end
}
