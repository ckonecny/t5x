/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ServoIn.cpp
** Servo Signal Input functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Arduino.h>

#include <inputchannel.h>
#include <rc_debug_lib.h>
#include <ServoIn.h>
#include <Timer1.h>
#include <rc_pcint.h>


namespace rc
{

// Public functions

ServoIn::ServoIn()
:
m_high(true)
{
	
}


#ifdef RC_USE_PCINT
void ServoIn::setPins(const prog_uint8_t* p_pins)
{
	for (uint8_t i = 0; i < RC_MAX_CHANNELS; ++i)
	{
		m_pins[i] = pgm_read_byte(p_pins + i);
	}
}


void ServoIn::setPin(uint8_t p_servo, uint8_t p_pin)
{
	RC_TRACE("set servo %u to pin %u", p_servo, p_pin);
	RC_ASSERT(p_servo < RC_MAX_CHANNELS);
	
	m_pins[p_servo] = p_pin;
}


uint8_t ServoIn::getPin(uint8_t p_servo) const
{
	RC_ASSERT(p_servo < RC_MAX_CHANNELS);
	return m_pins[p_servo];
}
#endif // RC_USE_PCINT


void ServoIn::start(bool p_high)
{
	RC_TRACE("start high: %d", p_high);
	m_high = p_high;
	
	// clean buffers
	uint16_t* results = getRawInputChannels();
	for (uint8_t i = 0; i < RC_MAX_CHANNELS; ++i)
	{
		m_pulseStart[i]  = 0;
		m_pulseLength[i] = 0;
		results[i]       = 0;
	}
	
	// start Timer 1
	rc::Timer1::start();
	
#ifdef RC_USE_PCINT
	// register pin change interrupts
	m_lastPin = 0;
	for (uint8_t i = 0; i < RC_MAX_CHANNELS; ++i)
	{
		if (m_pins[i] != 0)
		{
			pcint::enable(m_pins[i], ServoIn::isr, this);
		}
	}
#endif // RC_USE_PCINT
}


void ServoIn::stop()
{
	// stop Timer 1
	rc::Timer1::stop();
	
#ifdef RC_USE_PCINT
	// unregister pin change interrupts
	for (uint8_t i = 0; i < RC_MAX_CHANNELS; ++i)
	{
		if (m_pins[i] != 0)
		{
			pcint::disable(m_pins[i]);
		}
	}
#endif // RC_USE_PCINT
}


#ifndef RC_USE_PCINT
void ServoIn::pinChanged(uint8_t p_servo, bool p_high)
{
	// first things first, get Timer 1 count
	uint8_t oldSREG = SREG;
	cli();
	uint16_t cnt = TCNT1;
	SREG = oldSREG;
	
	if (p_high == m_high)
	{
		// start of pulse, cheat half a microsecond so we can detect errors
		m_pulseStart[p_servo] = (cnt == 0) ? 1 : cnt;
	}
	else
	{
		// end of pulse, clear length on error
		m_pulseLength[p_servo] = (m_pulseStart[p_servo] == 0) ? 0 : (cnt - m_pulseStart[p_servo]);
	}
}
#endif // NOT RC_USE_PCINT


void ServoIn::update()
{
	uint16_t* results = getRawInputChannels();
	for (uint8_t i = 0; i < RC_MAX_CHANNELS; ++i)
	{
		results[i] = m_pulseLength[i] >> 1;
	}
}


// private functions

#ifdef RC_USE_PCINT
void ServoIn::pinChanged(uint8_t p_pin, bool p_high)
{
	// first things first, get Timer 1 count
	uint8_t oldSREG = SREG;
	cli();
	uint16_t cnt = TCNT1;
	SREG = oldSREG;
	
	// find the servo
	uint8_t servo = m_lastPin;
	for (;;)
	{
		if (m_pins[servo] == p_pin)
		{
			break;
		}
		++servo;
		if (servo >= RC_MAX_CHANNELS)
		{
			servo = 0;
		}
		if (servo == m_lastPin)
		{
			// pin not found
			return;
		}
	}
	
	if (p_high == m_high)
	{
		// start of pulse, cheat half a microsecond so we can detect errors
		m_pulseStart[servo] = (cnt == 0) ? 1 : cnt;
	}
	else
	{
		// end of pulse, clear length on error
		m_pulseLength[servo] = (m_pulseStart[servo] == 0) ? 0 : (cnt - m_pulseStart[servo]);
		m_lastPin = servo;
	}
}


void ServoIn::isr(uint8_t p_pin, bool p_high, void* p_user)
{
	reinterpret_cast<ServoIn*>(p_user)->pinChanged(p_pin, p_high);
}
#endif // RC_USE_PCINT

// namespace end
}
