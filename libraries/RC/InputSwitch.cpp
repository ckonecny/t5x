/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** InputSwitch.cpp
** Class which takes input from the input buffer and acts like a switch
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <InputSwitch.h>
#include <rc_debug_lib.h>


namespace rc
{

// Public functions

InputSwitch::InputSwitch(Input p_source, Switch p_destination)
:
InputProcessor(p_source),
SwitchSource(SwitchType_BiState, p_destination),
m_mark(0),
m_mark2(-1),
m_dead(0),
m_reverse(0),
m_mirror(0),
m_range(0)
{
	
}


void InputSwitch::setMark(int16_t p_mark)
{
	RC_TRACE("set mark: %d", p_mark);
	RC_ASSERT_MINMAX(p_mark, -256, 256);
	m_mark = p_mark;
}


int16_t InputSwitch::getMark() const
{
	return m_mark;
}


void InputSwitch::setDeadBand(uint8_t p_band)
{
	RC_TRACE("set dead band: %u", p_band);
	
	m_dead = p_band;
}


uint8_t InputSwitch::getDeadBand() const
{
	return m_dead;
}


void InputSwitch::setReversed(bool p_reversed)
{
	RC_TRACE("set reversed: %d", p_reversed);
	
	m_reverse = p_reversed;
}


bool InputSwitch::isReversed() const
{
	return m_reverse;
}


void InputSwitch::setMirrored(bool p_mirrored)
{
	RC_TRACE("set mirrored: %d", p_mirrored);
	
	m_mirror = p_mirrored;
}


bool InputSwitch::isMirrored() const
{
	return m_mirror;
}


void InputSwitch::setRanged(bool p_ranged)
{
	RC_TRACE("set ranged: %d", p_ranged);
	
	m_range = p_ranged;
}


bool InputSwitch::isRanged() const
{
	return m_range;
}


void InputSwitch::setMark2(int16_t p_mark)
{
	RC_TRACE("set mark 2: %d", p_mark);
	RC_ASSERT_MINMAX(p_mark, -256, 256);
	if (p_mark > m_mark)
	{
		m_mark2 = m_mark;
		m_mark = p_mark;
	}
	else
	{
		m_mark2 = p_mark;
	}
}


int16_t InputSwitch::getMark2() const
{
	return m_mark2;
}


SwitchState InputSwitch::read(int16_t p_value) const
{
	// we need to fetch the previous state for dead band handling
	SwitchState state = getSwitchState(m_destination);
	
	if (m_range)
	{
		// handle range
		if (m_mirror)
		{
			return write((p_value <= m_mark && p_value >= m_mark2) ||
			             (p_value >= -m_mark && p_value <= -m_mark2));
		}
		else
		{
			return write(p_value <= m_mark && p_value >= m_mark2);
		}
	}
	else
	{
		// normal mode
		if (m_mirror)
		{
			if (p_value >= m_mark + m_dead || p_value <= -(m_mark + m_dead))
			{
				return write(true);
			}
			else if (p_value <= m_mark - m_dead && p_value >= -(m_mark - m_dead))
			{
				return write(false);
			}
		}
		else
		{
			if (p_value >= m_mark + m_dead)
			{
				return write(true);
			}
			else if (p_value < m_mark - m_dead)
			{
				return write(false);
			}
		}
	}
	
	// no change, in case of dead band handling
	return writeSwitchState(state);
}


SwitchState InputSwitch::read() const
{
	if (m_source == Input_None)
	{
		return writeSwitchState(SwitchState_Disconnected);
	}
	return read(getInput(m_source));
}


// Private functions

SwitchState InputSwitch::write(bool p_up) const
{
	return writeSwitchState(p_up == m_reverse ? SwitchState_Down : SwitchState_Up);
}


// namespace end
}
