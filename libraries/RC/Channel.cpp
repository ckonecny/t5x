/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Channel.cpp
** Channel functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Arduino.h>

#include <Channel.h>
#include <rc_debug_lib.h>
#include <util.h>


namespace rc
{

// Public functions

Channel::Channel(Output p_source, OutputChannel p_destination)
:
OutputProcessor(p_source),
OutputChannelSource(p_destination),
m_reversed(false),
m_epMin(100),
m_epMax(100),
m_subtrim(0),
m_speed(0),
m_time(0),
m_last(0xFFFF)
{
	
}


void Channel::setReverse(bool p_reversed)
{
	RC_TRACE("set reverse: %d", p_reversed);
	m_reversed = p_reversed;
}
	

bool Channel::isReversed() const
{
	return m_reversed;
}

	
void Channel::setSubtrim(int8_t p_subtrim)
{
	RC_TRACE("set subtrim %d", p_subtrim);
	RC_ASSERT_MINMAX(p_subtrim, -100, 100);
	m_subtrim = p_subtrim;
}
	

int8_t Channel::getSubtrim() const
{
	return m_subtrim;
}


void Channel::setEndPointMin(uint8_t p_endPoint)
{
	RC_TRACE("set ep min %u", p_endPoint);
	RC_ASSERT_MINMAX(p_endPoint, 0, 140);
	m_epMin = p_endPoint;
}
	

uint8_t Channel::getEndPointMin() const
{
	return m_epMin;
}


void Channel::setEndPointMax(uint8_t p_endPoint)
{
	RC_TRACE("set ep max %u", p_endPoint);
	RC_ASSERT_MINMAX(p_endPoint, 0, 140);
	m_epMax = p_endPoint;
}
	

uint8_t Channel::getEndPointMax() const
{
	return m_epMax;
}


void Channel::setSpeed(uint8_t p_speed)
{
	RC_TRACE("set speed: %u", p_speed);
	RC_ASSERT_MINMAX(p_speed, 0, 100);
	m_speed = p_speed;
	m_time  = static_cast<uint8_t>(millis());
}


uint8_t Channel::getSpeed() const
{
	return m_speed;
}


uint16_t Channel::apply(int16_t p_value)
{
	if (p_value == Out_Max)
	{
		return 256;
	}
	if (p_value == Out_Min)
	{
		return -256;
	}
	RC_ASSERT_MINMAX(p_value, -358, 358);
	
	// apply subtrim
	p_value += m_subtrim;

	// apply endpoints
	uint8_t ep = (p_value > 0) ? m_epMax : m_epMin;
	
	// we're running the risk of overflows here, so add a bit of precision
	bool neg = p_value < 0;
	uint16_t val = static_cast<uint16_t>(neg ? (-p_value) : p_value);
	val = (val * ep) / 140;
	
	// clamp values
	if (val > 256) val = 256;
	p_value = neg ? -static_cast<int>(val) : static_cast<int>(val);
	
	// apply channel reverse and servo speed
	return writeOutputChannelValue(rc::normalizedToMicros(applySpeed(m_reversed ? -p_value : p_value)));
}


uint16_t Channel::apply()
{
	  return apply(rc::getOutput(m_source));
}


// private functions

int16_t Channel::applySpeed(int16_t p_target)
{
	// we use 0xFFFF as an indicator that applySpeed has never been called yet
	// in that case we want to set the servo position immediately to the requested position
	if (m_speed == 0 || p_target == m_last || m_last == int16_t(0xFFFF))
	{
		m_last = p_target;
		return p_target;
	}
	// we might as well use 8 bit for times, just make sure to update at least 4 times per second
	// (1000 ms / 256 = 3.9 overflows per second)
	uint8_t now = static_cast<uint8_t>(millis());
	uint8_t delta = now - m_time;
	
	// the total amount traveled in the past delta time is:
	// (full throw / time which it takes to travel) * delta time
	// or
	// (512 / (m_speed * 100)) * delta
	// that'll result in 0 for any speed above 5, so let's not do that
	// but the following is the same:
	// (delta * 512) / (m_speed * 100)
	// but this will overflow for delta >= 128
	// But, hooray for math, we may divide the numerator and denominator by the same value and
	// we'll still get the right result, let's use four, I like four
	// (delta* (512 / 4)) / (m_speed * (100 / 4))
	uint16_t travel = (delta * 128) / (m_speed * 25);
	if (travel == 0)
	{
		// on some occasions (for example a small delta and very high speed)
		// it may be possible that the result of the division is 0
		// in those cases we won't do anything and wait for the next update
		// since we don't store the time, the delta will grow and hopefully with the next
		// update travel will be > 0
		return m_last;
	}
	m_time = now;
	
	// now that we know how far we can travel in this update, let's see in which direction we'll need to go
	if (m_last > p_target)
	{
		if (static_cast<uint16_t>(m_last - p_target) < travel)
		{
			m_last = p_target;
		}
		else
		{
			m_last = m_last - static_cast<int16_t>(travel);
		}
	}
	else
	{
		if (static_cast<uint16_t>(p_target - m_last) < travel)
		{
			m_last = p_target;
		}
		else
		{
			m_last = m_last + static_cast<int16_t>(travel);
		}
	}
	return m_last;
}


// namespace end
}

