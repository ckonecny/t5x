/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** BiStateSwitch.cpp
** Base class for classes acting as a switch
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Arduino.h>

#include <BiStateSwitch.h>
#include <rc_debug_lib.h>


namespace rc
{

// Public functions

BiStateSwitch::BiStateSwitch(uint8_t p_pin, Switch p_destination, bool p_momentary, bool p_reversed)
:
SwitchSource(p_momentary ? SwitchType_Momentary : SwitchType_BiState, p_destination),
m_pin(p_pin),
m_reversed(p_reversed)
{
	setPin(p_pin);
}


void BiStateSwitch::setPin(uint8_t p_pin)
{
	RC_TRACE("set pin: %u", p_pin);
	m_pin = p_pin;
	pinMode(p_pin, INPUT);
}


uint8_t BiStateSwitch::getPin() const
{
	return m_pin;
}


void BiStateSwitch::setReverse(bool p_reversed)
{
	RC_TRACE("set reverse: %d", p_reversed);
	m_reversed = p_reversed;
}
	

bool BiStateSwitch::isReversed() const
{
	return m_reversed;
}


SwitchState BiStateSwitch::read() const
{
	// pin high and reversed false: up position
	// pin high and reversed true: down position
	// pin low and reversed false: down position
	// pin low and reversed true: up position
	return writeSwitchState(digitalRead(m_pin) == m_reversed ? SwitchState_Down : SwitchState_Up);
}


// namespace end
}
