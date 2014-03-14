/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Gimbal.cpp
** Gimbal abstraction
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Gimbal.h>
#include <rc_debug_lib.h>


namespace rc
{

// Public functions

Gimbal::Gimbal(uint8_t p_horizPin, uint8_t p_vertiPin, bool p_left, Mode p_mode)
:
m_hor(p_horizPin, p_left && (p_mode == Mode_1 || p_mode == Mode_2) ? Input_RUD : Input_AIL),
m_ver(p_vertiPin, p_left && (p_mode == Mode_1 || p_mode == Mode_3) ? Input_ELE : Input_THR),
m_left(p_left),
m_mode(p_mode)
{
	
}


void Gimbal::setLeft(bool p_left)
{
	RC_TRACE("set left: %d", p_left);
	
	m_left = p_left;
	updateLayout();
}


bool Gimbal::isLeft() const
{
	return m_left;
}


void Gimbal::setMode(Mode p_mode)
{
	RC_TRACE("set mode: %d", p_mode + 1);
	RC_ASSERT(p_mode < Mode_Count);
	
	m_mode = p_mode;
	updateLayout();
}


Gimbal::Mode Gimbal::getMode() const
{
	return m_mode;
}


AIPin& Gimbal::getHorizontal()
{
	return m_hor;
}


const AIPin& Gimbal::getHorizontal() const
{
	return m_hor;
}


AIPin& Gimbal::getVertical()
{
	return m_ver;
}


const AIPin& Gimbal::getVertical() const
{
	return m_ver;
}


void Gimbal::read() const
{
	m_hor.read();
	m_ver.read();
}


// Private functions

void Gimbal::updateLayout()
{
	m_hor.setDestination(m_left && (m_mode == Mode_1 || m_mode == Mode_2) ? Input_RUD : Input_AIL);
	m_ver.setDestination(m_left && (m_mode == Mode_1 || m_mode == Mode_3) ? Input_ELE : Input_THR);
}


// namespace end
}
