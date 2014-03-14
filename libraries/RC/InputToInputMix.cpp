/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** InputToInputMix.cpp
** Generic input to input mix
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <InputToInputMix.h>
#include <rc_debug_lib.h>
#include <util.h>


namespace rc
{

// Public functions

InputToInputMix::InputToInputMix(int8_t p_posMix,
                                 int8_t p_negMix,
                                 int16_t p_offset,
                                 Input p_source,
                                 Input p_index)
:
InputProcessor(p_source),
InputModifier(p_index),
MixBase(p_posMix, p_negMix, p_offset)
{
	
}


int16_t InputToInputMix::apply(int16_t p_master, int16_t p_slave) const
{
	RC_ASSERT_MINMAX(p_master, -358, 358);
	RC_ASSERT_MINMAX(p_slave, -358, 358);
	
	return applyMix(p_master, p_slave);
}


int16_t InputToInputMix::applyOffset(int16_t p_slave) const
{
	RC_ASSERT_MINMAX(p_slave, -358, 358);
	
	return applyOffsetMix(p_slave);
}


void InputToInputMix::apply() const
{
	if (m_index != Input_None)
	{
		if (m_source != Input_None)
		{
			rc::setInput(m_index,
			             apply(rc::getInput(m_source),
			                   rc::getInput(m_index)));
		}
		else
		{
			rc::setInput(m_index, applyOffset(rc::getInput(m_index)));
		}
	}
}


// namespace end
}
