/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** OutputSource.cpp
** Base class for classes acting as a source for output
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <OutputSource.h>
#include <rc_debug_lib.h>


namespace rc
{

// Public functions

void OutputSource::setDestination(Output p_destination)
{
	RC_TRACE("set destination: %d", p_destination);
	RC_ASSERT(p_destination <= Output_Count);
	m_destination = p_destination;
}


Output OutputSource::getDestination() const
{
	return m_destination;
}


// Protected functions

OutputSource::OutputSource(Output p_index)
:
m_destination(p_index)
{
	
}


int16_t OutputSource::writeOutputValue(int16_t p_value) const
{
	RC_ASSERT_MINMAX(p_value, -358, 358);
	if (m_destination != Output_None)
	{
		RC_ASSERT(m_destination < Output_Count);
		rc::setOutput(m_destination, p_value);
	}
	return p_value;
}


// namespace end
}
