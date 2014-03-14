/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** rc_debug.cpp
** Global external interrupt handler
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Arduino.h>

#include <rc_debug_lib.h>
#include <rc_extint.h>


#ifdef RC_USE_EXTINT

namespace rc {
namespace extint {

enum
{
	ExtInts = 2
};

static volatile Callback s_callbacks[ExtInts] = { 0 }; //!< Callback functions
static volatile void*    s_userdata[ExtInts]  = { 0 }; //!< User data


// TODO: support more than Atmega328
bool supported(uint8_t p_pin)
{
	return p_pin == 2 || p_pin == 3;
}


// TODO: support more than Atmega328
void enable(uint8_t p_pin, ISC p_trigger, Callback p_callback, void* p_user)
{
	// we're not going to set the pin to input mode here since that disables
	// the pull-up resistor. Client code is responsible for setting the pin
	// to the correct mode.
	if (p_pin == 2)
	{
		s_callbacks[0] = p_callback;
		s_userdata[0]  = p_user;
		EICRA = (EICRA & ~(_BV(ISC00) | _BV(ISC01))) | ((static_cast<uint8_t>(p_trigger) & 0x03) << ISC00);
		EIMSK |= _BV(INT0);
	}
	else if (p_pin == 3)
	{
		s_callbacks[1] = p_callback;
		s_userdata[1]  = p_user;
		EICRA = (EICRA & ~(_BV(ISC10) | _BV(ISC11))) | ((static_cast<uint8_t>(p_trigger) & 0x03) << ISC10);
		EIMSK |= _BV(INT1);
	}
}


// TODO: support more than Atmega328
void disable(uint8_t p_pin)
{
	if (p_pin == 2)
	{
		EIMSK &= ~_BV(INT0);
		s_callbacks[0] = 0;
		s_userdata[0]  = 0;
	}
	else if (p_pin == 3)
	{
		EIMSK &= ~_BV(INT1);
		s_callbacks[1] = 0;
		s_userdata[1]  = 0;
	}
}


// namespace end
}
}


// External interrupt 0 handler
SIGNAL(INT0_vect)
{
	if (rc::extint::s_callbacks[0])
	{
		rc::extint::s_callbacks[0](2, const_cast<void*>(rc::extint::s_userdata[0]));
	}
}


// External interrupt 1 handler
SIGNAL(INT1_vect)
{
	if (rc::extint::s_callbacks[1])
	{
		rc::extint::s_callbacks[1](3, const_cast<void*>(rc::extint::s_userdata[1]));
	}
}

#endif // RC_USE_EXTINT
