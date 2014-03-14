/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** InputModifier.cpp
** Base class for classes having an input and performing operations on it
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <InputModifier.h>
#include <rc_debug_lib.h>


namespace rc
{

// Public functions

void InputModifier::setIndex(Input p_index)
{
	RC_TRACE("set index: %d", p_index);
	RC_ASSERT(p_index <= Input_Count);
	
	m_index = p_index;
}


Input InputModifier::getIndex() const
{
	return m_index;
}


// Protected functions

InputModifier::InputModifier(Input p_index)
:
m_index(p_index)
{
	
}


// namespace end
}
