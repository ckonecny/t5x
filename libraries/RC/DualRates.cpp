/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** DualRates.cpp
** Dual Rates functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <DualRates.h>
#include <rc_debug_lib.h>


namespace rc
{

// Public functions

DualRates::DualRates(uint8_t p_rate, Input p_index)
:
InputModifier(p_index),
m_rate(p_rate)
{
	
}


void DualRates::set(uint8_t p_rate)
{
	RC_TRACE("set rate: %d%%", p_rate);
	RC_ASSERT_MINMAX(p_rate, 0, 140);
	
	m_rate = p_rate;
}


uint8_t DualRates::get() const
{
	return m_rate;
}


DualRates& DualRates::operator = (uint8_t p_rhs)
{
	m_rate = p_rhs;
	return *this;
}


DualRates& DualRates::operator = (const DualRates& p_rhs)
{
	m_rate = p_rhs.m_rate;
	return *this;
}


DualRates::operator uint8_t () const
{
	return m_rate;
}


uint8_t* DualRates::operator & ()
{
	return &m_rate;
}


const uint8_t* DualRates::operator & () const
{
	return &m_rate;
}


int16_t DualRates::apply(int16_t p_value) const
{
	RC_ASSERT_MINMAX(p_value, -256, 256);
	
	// there's a risk in overflows here, since 256 * 140 > 32K
	// so we do this unsigned..
	uint8_t neg = p_value < 0;
	uint16_t val = static_cast<uint16_t>(neg ? (-p_value) : p_value);
	val = (val * m_rate) / 100;
	return neg ? -static_cast<int16_t>(val) : static_cast<int16_t>(val);
}


void DualRates::apply() const
{
	if (m_index != Input_None)
	{
		rc::setInput(m_index, apply(rc::getInput(m_index)));
	}
}


// namespace end
}
