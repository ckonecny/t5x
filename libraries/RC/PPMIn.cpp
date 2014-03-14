/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** PPMIn.cpp
** Pulse Position Modulation Input functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Arduino.h>

#include <inputchannel.h>
#include <PPMIn.h>
#include <rc_debug_lib.h>
#include <Timer1.h>
#include <rc_pcint.h>


namespace rc
{

// Public functions

PPMIn::PPMIn()
:
m_state(State_Startup),
m_channels(0),
m_pauseLength(8000),
m_timeout(500),
m_idx(0),
m_newFrame(false),
m_lastFrameTime(0),
m_lastTime(0),
m_high(false)
#ifdef RC_USE_PCINT
,m_pin(0)
#endif
{
	
}


#ifdef RC_USE_PCINT
void PPMIn::setPin(uint8_t p_pin)
{
	RC_TRACE("set pin: %u", p_pin);
	
	m_pin = p_pin;
}


uint8_t PPMIn::getPin() const
{
	return m_pin;
}
#endif // RC_USE_PCINT


void PPMIn::start(bool p_high)
{
	RC_TRACE("start, signal high: %d", p_high);
	m_high = p_high;
	
	// check if Timer 1 is running or not
	rc::Timer1::start();

#ifdef RC_USE_PCINT
	// register pin change interrupt
	if (m_pin != 0)
	{
		pcint::enable(m_pin, PPMIn::isr, this);
	}
#endif // RC_USE_PCINT
}


void PPMIn::stop()
{
#ifdef RC_USE_PCINT
	if (m_pin != 0)
	{
		pcint::disable(m_pin);
	}
#endif // RC_USE_PCINT
}


void PPMIn::setPauseLength(uint16_t p_length)
{
	RC_TRACE("set pause length: %u us", p_length);
	RC_ASSERT_MINMAX(p_length, 0, 32766);
	
	m_pauseLength = p_length << 1;
}


uint16_t PPMIn::getPauseLength() const
{
	return m_pauseLength >> 1;
}


void PPMIn::setTimeout(uint16_t p_length)
{
	RC_TRACE("set timeout: %u us", p_length);
	RC_ASSERT_MINMAX(p_length, 0, 32766);
	
	m_timeout = p_length;
}


uint16_t PPMIn::getTimeout() const
{
	return m_timeout;
}


bool PPMIn::isStable() const
{
	return m_state == State_Stable;
}


bool PPMIn::isLost() const
{
	return m_state == State_Lost;
}


uint8_t PPMIn::getChannels() const
{
	return m_channels;
}


void PPMIn::pinChanged(bool p_high)
{
	if (p_high != m_high)
	{
		return;
	}
	
	// first things first, get Timer 1 count
	uint8_t oldSREG = SREG;
	cli();
	uint16_t cnt = TCNT1;
	SREG = oldSREG;
	
	switch (m_state)
	{
	default:
	case State_Startup:
	case State_Lost:
		{
			if (cnt - m_lastTime >= m_pauseLength)
			{
				m_state = State_Listening;
				m_channels = 0;
			}
		}
		break;
	
	case State_Listening:
		{
			if (cnt - m_lastTime >= m_pauseLength)
			{
				m_state = State_Stable;
				m_idx = 0;
				m_newFrame = true;
			}
			else
			{
				if (m_channels < RC_MAX_CHANNELS)
				{
					m_work[m_channels] = cnt - m_lastTime;
				}
				++m_channels;
			}
		}
		break;
	
	case State_Stable:
		{
			if (cnt - m_lastTime >= m_pauseLength)
			{
				if (m_idx == m_channels)
				{
					m_idx = 0;
					m_newFrame = true;
				}
				else
				{
					m_state = State_Confused;
				}
			}
			else
			{
				if (m_idx < RC_MAX_CHANNELS)
				{
					m_work[m_idx] = cnt - m_lastTime;
				}
				++m_idx;
			}
		}
		break;
	}
	m_lastTime = cnt;
}


bool PPMIn::update()
{
	if (m_newFrame)
	{
		RC_TRACE("received new frame");
		m_newFrame = false;
		m_lastFrameTime = static_cast<uint16_t>(millis());
		uint16_t* results = getRawInputChannels();
		for (uint8_t i = 0; i < m_channels && i < RC_MAX_CHANNELS; ++i)
		{
			results[i] = m_work[i] >> 1;
		}
		return true;
	}
	else if (m_state == State_Stable)
	{
		uint16_t delta = static_cast<uint16_t>(millis()) - m_lastFrameTime;
		if (delta >= m_timeout)
		{
			// signal lost
			RC_TRACE("lost signal");
			m_state = State_Lost;
		}
	}
	return false;
}


// Private functions

#ifdef RC_USE_PCINT
void PPMIn::isr(uint8_t p_pin, bool p_high, void* p_user)
{
	reinterpret_cast<PPMIn*>(p_user)->pinChanged(p_high);
}
#endif // RC_USE_PCINT


// namespace end
}
