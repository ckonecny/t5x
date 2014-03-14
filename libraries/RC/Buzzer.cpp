/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Buzzer.cpp
** Buzzer functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Arduino.h>

#include <rc_debug_lib.h>
#include <Buzzer.h>
#include <Timer2.h>

#ifdef RC_USE_BUZZER


namespace rc
{

static volatile uint8_t* s_port = 0;
static          uint8_t  s_mask = 0;
static          uint8_t  s_count = 0;
static          uint16_t s_repeat = 0;
static          uint8_t  s_duration = 0;
static          uint8_t  s_pause = 0;


// Public functions

Buzzer::Buzzer(uint8_t p_pin)
:
m_pin(p_pin)
{
	setPin(m_pin);
}


void Buzzer::setPin(uint8_t p_pin)
{
	RC_TRACE("set pin: %u", p_pin);
	
	stop();
	
	m_pin = p_pin;
	pinMode(m_pin, OUTPUT);
	digitalWrite(m_pin, LOW);
}


uint8_t Buzzer::getPin() const
{
	return m_pin;
}


void Buzzer::beep(uint8_t p_duration, uint8_t p_pause, uint8_t p_repeat)
{
	RC_TRACE("beep dur: %u pause: %u rep: %u", p_duration, p_pause, p_repeat);
	RC_ASSERT_MINMAX(p_duration, 1, 250);
	RC_ASSERT_MINMAX(p_pause, 0, 250);
	
	Timer2::stop();
	
	// stop any active buzzer
	if (s_port != 0)
	{
		*(s_port + 2) &= ~s_mask;
	}
	
	s_port = portInputRegister(digitalPinToPort(m_pin));
	s_mask = digitalPinToBitMask(m_pin);
	s_repeat = p_repeat * 2;
	s_duration = p_duration;
	s_pause = p_pause;
	s_count = s_duration;
	
	Timer2::setCompareMatch(true, true, Buzzer::isr);
	OCR2A = 156; // overflow every 0.009984 seconds, 0.16% deviation
	TCNT2 = 0;
	
	digitalWrite(m_pin, HIGH);
	Timer2::start();
}


void Buzzer::stop()
{
	RC_TRACE("stop");
	
	if (s_port == portInputRegister(digitalPinToPort(m_pin)))
	{
		Timer2::stop();
	}
	digitalWrite(m_pin, LOW);
}


void Buzzer::isr()
{
	OCR2A += 156;
	
	--s_count;
	if (s_count == 0)
	{
		// toggle pin
		*s_port = s_mask;
		if (s_repeat == 0)
		{
			// done
			Timer2::stop();
		}
		--s_repeat;
		if (s_repeat & 1)
		{
			s_count = s_pause;
		}
		else
		{
			s_count = s_duration;
		}
	}
}

// Preinstantiated objects

Buzzer g_Buzzer(8);


// namespace end
}

#endif // RC_USE_BUZZER
