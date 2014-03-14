/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** AIPin.cpp
** Analog input read functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Arduino.h>

#include <AIPin.h>
#include <rc_debug_lib.h>


namespace rc
{

// Public functions

AIPin::AIPin(uint8_t p_pin, Input p_destination)
:
InputSource(p_destination),
m_reversed(false),
m_trim(0),
m_center(511),
m_min(0),
m_max(1023)
{
	setPin(p_pin);
}


void AIPin::setPin(uint8_t p_pin)
{
	RC_TRACE("set pin: %u", p_pin);
	
	m_pin = p_pin;
	pinMode(p_pin, INPUT);
}


uint8_t AIPin::getPin() const
{
	return m_pin;
}


AIPin& AIPin::operator = (uint8_t p_rhs)
{
	setPin(p_rhs);
	return *this;
}


AIPin::operator uint8_t () const
{
	return m_pin;
}


void AIPin::setReverse(bool p_reversed)
{
	RC_TRACE("set reverse: %d", p_reversed);
	m_reversed = p_reversed;
}
	

bool AIPin::isReversed() const
{
	return m_reversed;
}


void AIPin::setTrim(int8_t p_trim)
{
	RC_TRACE("set trim: %d", p_trim);
	RC_ASSERT_MINMAX(p_trim, -100, 100);
	m_trim = p_trim;
}
	

int8_t AIPin::getTrim() const
{
	return m_trim;
}


void AIPin::setCenter(uint16_t p_center)
{
	RC_TRACE("set center: %u", p_center);
	RC_ASSERT_MINMAX(p_center, 0, 1023);
	m_center = p_center;
}


uint16_t AIPin::getCenter() const
{
	return m_center;
}


void AIPin::setMin(uint16_t p_min)
{
	RC_TRACE("set min: %d", p_min);
	RC_ASSERT_MINMAX(p_min, 0, 1023);
	m_min = p_min;
}


uint16_t AIPin::getMin() const
{
	return m_min;
}


void AIPin::setMax(uint16_t p_max)
{
	RC_TRACE("set max: %d", p_max);
	RC_ASSERT_MINMAX(p_max, 0, 1023);
	m_max = p_max;
}


uint16_t AIPin::getMax() const
{
	return m_max;
}


void AIPin::setCalibration(uint16_t p_min, uint16_t p_center, uint16_t p_max)
{
	RC_TRACE("set calibration");
	setMin(p_min);
	setCenter(p_center);
	setMax(p_max);
}


int16_t AIPin::read() const
{
	uint16_t raw = analogRead(m_pin);
	
	// reverse if needed
	if (m_reversed) raw = 1023 - raw;
	
	// apply trim
	raw += m_trim;
	
	// early abort
	if (raw <= m_min) return writeInputValue(-256);
	if (raw >= m_max) return writeInputValue( 256);
	
	// calculate distance from center and maximum distance from center
	uint16_t out = raw > m_center ?   raw - m_center : m_center -   raw;
	uint16_t max = raw > m_center ? m_max - m_center : m_center - m_min;
	
	// change the range from [0 - max] to [0 - 256]
	
	// first bring the value down to below 256, or we'll be getting overflows, we'll compensate later
	int bits = 0;
	while (out >= 256)
	{
		out >>= 1;
		++bits;
	}
	
	out <<= 8;  // multiply by 256
	out /= max; // bring down to new range
	
	// bring the value back up if we did any truncating before
	while (bits > 0)
	{
		out <<= 1;
		--bits;
	}
	
	return writeInputValue((raw < m_center) ? -out : out);
}


// namespace end
}
