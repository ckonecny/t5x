/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** TriStateSwitch.cpp
** Tri state switch (alternating)
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Arduino.h>

#include <TriStateSwitch.h>
#include <rc_debug_lib.h>


namespace rc
{

// Public functions

TriStateSwitch::TriStateSwitch(uint8_t p_upPin, uint8_t p_downPin, Switch p_destination, bool p_reversed)
:
SwitchSource(SwitchType_TriState, p_destination),
m_upPin(p_upPin),
m_downPin(p_downPin),
m_reversed(p_reversed)
{
	setUpPin(p_upPin);
	setDownPin(p_downPin);
}


void TriStateSwitch::setUpPin(uint8_t p_pin)
{
	RC_TRACE("set up pin: %u", p_pin);
	m_upPin = p_pin;
	pinMode(m_upPin, INPUT);
}


uint8_t TriStateSwitch::getUpPin() const
{
	return m_upPin;
}


void TriStateSwitch::setDownPin(uint8_t p_pin)
{
	RC_TRACE("set down pin: %u", p_pin);
	m_downPin = p_pin;
	pinMode(m_downPin, INPUT);
}


uint8_t TriStateSwitch::getDownPin() const
{
	return m_downPin;
}


void TriStateSwitch::setReverse(bool p_reversed)
{
	RC_TRACE("set reverse: %d", p_reversed);
	m_reversed = p_reversed;
}
	

bool TriStateSwitch::isReversed() const
{
	return m_reversed;
}


SwitchState TriStateSwitch::read() const
{
	bool up   = digitalRead(m_upPin);
	bool down = digitalRead(m_downPin);
	
	// this may need some explaining
	// if up and down are equal, they're either both high or both low: so center position
	// if up is high and reverse is false: up position
	// if up is high and reverse is true: down position
	// if down is high (and up is low) and reverse is false: down position
	// if down is high (and up is low) and reverse is true: up position
	return writeSwitchState(up == down ? SwitchState_Center :
	                        (up == m_reversed ? SwitchState_Down : SwitchState_Up));
}


// namespace end
}
