/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Timer2.cpp
** Timer2 functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Arduino.h>

#include <rc_debug_lib.h>
#include <Timer2.h>


// Static variables
static rc::Timer2::Callback s_TOIE2Callback = 0;
static rc::Timer2::Callback s_OCI2ACallback = 0;
static rc::Timer2::Callback s_OCI2BCallback = 0;

namespace rc
{

// Public functions

void Timer2::init()
{
	RC_TRACE("init");
	TCCR2A = 0;
	TCCR2B = 0;
	TIMSK2 = 0;
	OCR2A = 0;
	OCR2B = 0;
	TCNT2 = 0;
}


void Timer2::start(Prescaler p_prescaler)
{
	RC_TRACE("start");
	RC_ASSERT_MINMAX(p_prescaler, Prescaler_1, Prescaler_1024);
	
	TCCR2B = static_cast<uint8_t>(p_prescaler);
}


bool Timer2::isRunning()
{
	return TCCR2B != 0;
}


void Timer2::stop()
{
	RC_TRACE("stop");
	TCCR2B = 0;
}


void Timer2::setCompareMatch(bool p_enable, bool p_OCIE2A, Callback p_callback)
{
	RC_TRACE("set compare match enable: %d OCIE2A: %d Callback: %p", p_enable, p_OCIE2A, p_callback);
	if (p_enable)
	{
		if (p_OCIE2A)
		{
			s_OCI2ACallback = p_callback;
			TIMSK2 |= _BV(OCIE2A);
		}
		else
		{
			s_OCI2BCallback = p_callback;
			TIMSK2 |= _BV(OCIE2B);
		}
	}
	else
	{
		if (p_OCIE2A)
		{
			TIMSK2 &= ~_BV(OCIE2A);
			s_OCI2ACallback = 0;
		}
		else
		{
			TIMSK2 &= ~_BV(OCIE2B);
			s_OCI2BCallback = 0;
		}
	}
}


void Timer2::setOverflow(bool p_enable, Callback p_callback)
{
	RC_TRACE("set overflow enable: %d Callback: %p", p_enable, p_callback);
	if (p_enable)
	{
		s_TOIE2Callback = p_callback;
		TIMSK2 |= _BV(TOIE2);
	}
	else
	{
		TIMSK2 &= ~_BV(TOIE2);
		s_TOIE2Callback = 0;
	}
}


void Timer2::setToggle(bool p_enable, bool p_OC2A)
{
	RC_TRACE("set toggle enable: %d OC2A: %d", p_enable, p_OC2A);
	if (p_enable)
	{
		TCCR2A |= p_OC2A ? _BV(COM2A0) : _BV(COM2B0);
	}
	else
	{
		TCCR2A &= p_OC2A ? ~_BV(COM2A0) : ~_BV(COM2B0);
	}
}

// namespace end
}


// Interrupt service routines

ISR(TIMER2_OVF_vect)
{
	if (s_TOIE2Callback != 0)
	{
		s_TOIE2Callback();
	}
}


ISR(TIMER2_COMPA_vect)
{
	if (s_OCI2ACallback != 0)
	{
		s_OCI2ACallback();
	}
}


ISR(TIMER2_COMPB_vect)
{
	if (s_OCI2BCallback != 0)
	{
		s_OCI2BCallback();
	}
}
