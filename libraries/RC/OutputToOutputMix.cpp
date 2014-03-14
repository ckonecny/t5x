/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** OutputToOutputMix.cpp
** Generic output to output mix
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <OutputToOutputMix.h>
#include <rc_debug_lib.h>
#include <util.h>


namespace rc
{

// Public functions

OutputToOutputMix::OutputToOutputMix(int8_t p_posMix,
                                     int8_t p_negMix,
                                     int16_t p_offset,
                                     Output p_source,
                                     Output p_index)
:
OutputProcessor(p_source),
OutputModifier(p_index),
MixBase(p_posMix, p_negMix, p_offset)
{
	
}


int16_t OutputToOutputMix::apply(int16_t p_master, int16_t p_slave) const
{
	RC_ASSERT_MINMAX(p_master, -358, 358);
	RC_ASSERT_MINMAX(p_slave, -358, 358);
	
	return applyMix(p_master, p_slave);
}


int16_t OutputToOutputMix::applyOffset(int16_t p_slave) const
{
	RC_ASSERT_MINMAX(p_slave, -358, 358);
	
	return applyOffsetMix(p_slave);
}


void OutputToOutputMix::apply() const
{
	if (m_index != Output_None)
	{
		if (m_source != Output_None)
		{
			rc::setOutput(m_index,
			              apply(rc::getOutput(m_source),
			                    rc::getOutput(m_index)));
		}
		else
		{
			rc::setOutput(m_index, applyOffset(rc::getOutput(m_index)));
		}
	}
}


// namespace end
}
