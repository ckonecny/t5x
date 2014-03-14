/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Offset.cpp
** Offset functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Offset.h>
#include <rc_debug_lib.h>
#include <util.h>


namespace rc
{

// Public functions

Offset::Offset(int8_t p_offset, Input p_index, Switch p_switch, SwitchState p_state)
:
InputModifier(p_index),
SwitchProcessor(p_switch, p_state),
m_offset(p_offset)
{
	
}


void Offset::setOffset(int8_t p_offset)
{
	RC_TRACE("set offset: %d%%", p_offset);
	RC_ASSERT_MINMAX(p_offset, -100, 100);
	
	m_offset = p_offset;
}


int8_t Offset::getOffset() const
{
	return m_offset;
}


int16_t Offset::apply(int16_t p_value) const
{
	RC_ASSERT_MINMAX(p_value, -256, 256);
	
	return rc::clampNormalized(p_value + m_offset);
}


void Offset::apply() const
{
	if (m_index != Input_None && isActiveState())
	{
		rc::setInput(m_index, apply(rc::getInput(m_index)));
	}
}


// namespace end
}
