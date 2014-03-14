/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** SwitchSource.cpp
** Base class for classes acting as a switch
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <SwitchSource.h>
#include <rc_debug_lib.h>


namespace rc
{

// Public functions

void SwitchSource::setDestination(Switch p_destination)
{
	RC_TRACE("set destination: %d", p_destination);
	RC_ASSERT(p_destination <= Switch_Count);
	
	m_destination = p_destination;
	if (m_destination != Switch_None)
	{
		setSwitchType(p_destination, m_type);
	}
}


Switch SwitchSource::getDestination() const
{
	return m_destination;
}


// Protected functions

SwitchSource::SwitchSource(SwitchType p_type, Switch p_destination)
:
m_destination(p_destination),
m_type(p_type)
{
	if (m_destination != Switch_None)
	{
		setSwitchType(m_destination, m_type);
	}
}


SwitchState SwitchSource::writeSwitchState(SwitchState p_state) const
{
	RC_ASSERT(p_state < SwitchState_Count);
	
	if (m_destination != Switch_None)
	{
		RC_ASSERT(m_destination < Switch_Count);
		rc::setSwitchState(m_destination, p_state);
	}
	return p_state;
}


// namespace end
}
