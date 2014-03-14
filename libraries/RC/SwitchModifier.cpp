/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** SwitchModifier.cpp
** Base class for classes having switch input and performing operations on it
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <SwitchModifier.h>
#include <rc_debug_lib.h>


namespace rc
{

// Public functions

void SwitchModifier::setIndex(Switch p_index)
{
	RC_TRACE("set index: %d", p_index);
	RC_ASSERT(p_index <= Switch_Count);
	
	m_index = p_index;
}


Switch SwitchModifier::getIndex() const
{
	return m_index;
}


// Protected functions

SwitchModifier::SwitchModifier(Switch p_index)
:
m_index(p_index)
{
	
}


// namespace end
}
