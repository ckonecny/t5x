/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** RotaryEncoder.cpp
** Rotary Encoder functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Arduino.h>

#include <rc_debug_lib.h>
#include <RotaryEncoder.h>
#include <rc_extint.h>


namespace rc
{

// Public functions

RotaryEncoder::RotaryEncoder(uint8_t p_pinA, uint8_t p_pinB, bool p_pullUp)
:
m_pinA(0),
m_pinB(0),
m_last(p_pullUp ? 3 : 0),
m_counter(0),
m_pullUp(p_pullUp),
m_min(-128),
m_max(127),
m_wrap(true),
m_reversed(false),
m_pos(0),
m_steps(0)
{
	setPinA(p_pinA);
	setPinB(p_pinB);
}


void RotaryEncoder::setPinA(uint8_t p_pin)
{
	RC_TRACE("set pin A: %u", p_pin);
	RC_ASSERT(p_pin != m_pinB);
	
#ifdef RC_USE_EXTINT
	if (p_pin != m_pinA)
	{
		extint::disable(m_pinA);
#endif
		m_pinA = p_pin;
		pinMode(m_pinA, m_pullUp ? INPUT_PULLUP : INPUT);
#ifdef RC_USE_EXTINT
		extint::enable(m_pinA, extint::ISC_Change, RotaryEncoder::isr, this);
	}
#endif
}


uint8_t RotaryEncoder::getPinA() const
{
	return m_pinA;
}


void RotaryEncoder::setPinB(uint8_t p_pin)
{
	RC_TRACE("set pin B: %u", p_pin);
	RC_ASSERT(p_pin != m_pinA);
	
#ifdef RC_USE_EXTINT
	if (p_pin != m_pinB)
	{
		extint::disable(m_pinB);
#endif
		m_pinB = p_pin;
		pinMode(m_pinB, m_pullUp ? INPUT_PULLUP : INPUT);
#ifdef RC_USE_EXTINT
		extint::enable(m_pinB, extint::ISC_Change, RotaryEncoder::isr, this);
	}
#endif
}


uint8_t RotaryEncoder::getPinB() const
{
	return m_pinB;
}


void RotaryEncoder::setMin(int8_t p_min)
{
	RC_TRACE("set min: %d", p_min);
	
	m_min = p_min;
}


int8_t RotaryEncoder::getMin() const
{
	return m_min;
}


void RotaryEncoder::setMax(int8_t p_max)
{
	RC_TRACE("set max: %d", p_max);
	
	m_max = p_max;
}


int8_t RotaryEncoder::getMax() const
{
	return m_max;
}


void RotaryEncoder::setWrap(bool p_wrap)
{
	RC_TRACE("set wrap: %d", p_wrap);
	
	m_wrap = p_wrap;
}


bool RotaryEncoder::isWrap() const
{
	return m_wrap;
}


void RotaryEncoder::setReversed(bool p_reverse)
{
	RC_TRACE("set reversed: %d", p_reverse);
	
	m_reversed = p_reverse;
}


bool RotaryEncoder::isReversed() const
{
	return m_reversed;
}


void RotaryEncoder::reset()
{
	m_pos   = m_min > 0 ? m_min : (m_max < 0 ? m_max : 0);
	m_steps = 0;
}


int8_t RotaryEncoder::readSteps()
{
	int8_t steps = m_steps;
	m_steps = 0;
	return steps;
}


int8_t RotaryEncoder::readPosition() const
{
	return m_pos;
}


void RotaryEncoder::pinChanged()
{
	m_last <<= 2;
	if (digitalRead(m_pinA))
	{
		m_last |= m_reversed ? _BV(0) : _BV(1);
	}
	if (digitalRead(m_pinB))
	{
		m_last |= m_reversed ? _BV(1) : _BV(0);
	}
	
	static const int8_t states[] PROGMEM = {  0, -1,  1,  0,  1,  0,  0, -1, -1,  0,  0,  1,  0,  1, -1,  0};
	m_counter += static_cast<int8_t>(pgm_read_byte(states + (m_last & 0x0F)));
	
	// we need to assert that at position 00 or 11 (depending on m_pullUp) the counter %4 = 0
	if ((m_counter & 3) != 0) // counter not multiple of 4
	{
		if ((m_last & 3) == (m_pullUp ? 3 : 0))
		{
			// counter is not a multiple of 4
			// and both pins are not high or low (depending on m_pullUp)
			// so something must have gone wrong, we probably missed an interrupt
			// reset the counter, don't move anything
			m_counter = 0;
		}
	}
	else if (m_counter > 0) // counter == 4
	{
		// move up
		if (m_pos < m_max)
		{
			++m_pos;
			++m_steps;
		}
		else if (m_wrap)
		{
			// wrap around
			m_pos = m_min;
			++m_steps;
		}
		m_counter -= 4;
	}
	else if (m_counter < 0) // counter == -4
	{
		// move down
		if (m_pos > m_min)
		{
			--m_pos;
			--m_steps;
		}
		else if (m_wrap)
		{
			// wrap around
			m_pos = m_max;
			--m_steps;
		}
		m_counter += 4;
	}
}


// Private functions



#ifdef RC_USE_EXTINT
void RotaryEncoder::isr(uint8_t, void* p_user)
{
	reinterpret_cast<RotaryEncoder*>(p_user)->pinChanged();
}
#endif


// namespace end
}

