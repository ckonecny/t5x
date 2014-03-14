/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** InputSource.cpp
** Base class for classes acting as a source of input
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <InputSource.h>
#include <rc_debug_lib.h>


namespace rc
{

// Public functions

void InputSource::setDestination(Input p_destination)
{
	RC_TRACE("set destination: %d", p_destination);
	RC_ASSERT(p_destination <= Input_Count);
	
	m_destination = p_destination;
}


Input InputSource::getDestination() const
{
	return m_destination;
}


// Protected functions

InputSource::InputSource(Input p_destination)
:
m_destination(p_destination)
{
	
}


int16_t InputSource::writeInputValue(int16_t p_value) const
{
	RC_ASSERT_MINMAX(p_value, -358, 358);
	
	if (m_destination != Input_None)
	{
		RC_ASSERT(m_destination < Input_Count);
		rc::setInput(m_destination, p_value);
	}
	return p_value;
}


// namespace end
}
