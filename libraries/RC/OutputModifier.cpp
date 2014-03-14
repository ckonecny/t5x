/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** OutputModifier.cpp
** Base class for classes having an output and performing operations on it
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <OutputModifier.h>
#include <rc_debug_lib.h>


namespace rc
{

// Public functions

void OutputModifier::setIndex(Output p_index)
{
	RC_TRACE("set index: %d", p_index);
	RC_ASSERT(p_index <= Output_Count);
	
	m_index = p_index;
}


Output OutputModifier::getIndex() const
{
	return m_index;
}


// Protected functions

OutputModifier::OutputModifier(Output p_index)
:
m_index(p_index)
{
	
}


// namespace end
}
