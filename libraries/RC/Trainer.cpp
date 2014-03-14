/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Trainer.cpp
** Trainer port functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <rc_debug_lib.h>
#include <Trainer.h>
#include <util.h>


namespace rc
{

// Public functions

Trainer::Trainer(Switch p_source, SwitchState p_state, InputChannel p_channel)
:
SwitchProcessor(p_source, p_state),
InputChannelProcessor(p_channel),
m_enabled(false),
m_destination(0xFF),
m_studentRate(100),
m_teacherRate(0)
{
	
}


void Trainer::setEnabled(bool p_enabled)
{
	RC_TRACE("set enabled: %d", p_enabled);
	m_enabled = p_enabled;
}


bool Trainer::isEnabled() const
{
	return m_enabled;
}


void Trainer::setAsInputSource(Input p_destination)
{
	RC_TRACE("set as input source: %d", p_destination);
	RC_ASSERT(p_destination < Input_Count);
	
	m_destination = static_cast<uint8_t>(p_destination);
}


Input Trainer::getInputDestination() const
{
	if (m_destination & _BV(7) || m_destination == 0xFF)
	{
		return Input_None; // currently set as output source
	}
	return static_cast<Input>(m_destination);
}


void Trainer::setAsOutputSource(Output p_destination)
{
	RC_TRACE("set as output source: %d", p_destination);
	RC_ASSERT(p_destination < Output_Count);
	
	m_destination = static_cast<uint8_t>(p_destination) & _BV(7); // bit 7 is output flag
}


Output Trainer::getOutputDestination() const
{
	if ((m_destination & _BV(7)) == 0  || m_destination == 0xFF)
	{
		return Output_None; // currently set as output source
	}
	return static_cast<Output>(m_destination & 0x7F);
}


void Trainer::setStudentRate(uint8_t p_rate)
{
	RC_TRACE("set trainer rate: %u%%", p_rate);
	RC_ASSERT_MINMAX(p_rate, 0, 100);
	
	m_studentRate = p_rate;
}


uint8_t Trainer::getStudentRate() const
{
	return m_studentRate;
}


void Trainer::setTeacherRate(uint8_t p_rate)
{
	RC_TRACE("set source rate: %u%%", p_rate);
	RC_ASSERT_MINMAX(p_rate, 0, 100);
	
	m_teacherRate = p_rate;
}


uint8_t Trainer::getTeacherRate() const
{
	return m_teacherRate;
}


int16_t Trainer::apply(int16_t p_teacher, int16_t p_student, bool p_activeAndValid)
{
	if (m_enabled && p_activeAndValid)
	{
		return rc::clamp140(rc::mix(p_student, static_cast<int8_t>(m_studentRate)) +
		                    rc::mix(p_teacher, static_cast<int8_t>(m_teacherRate)));
	}
	return p_teacher;
}


void Trainer::apply(bool p_valid)
{
	if (p_valid && isActiveState() && InputChannelProcessor::m_source != InputChannel_None)
	{
		int16_t student = rc::microsToNormalized(rc::getInputChannel(InputChannelProcessor::m_source));
		Input i = getInputDestination();
		if (i != Input_None)
		{
			rc::setInput(i, apply(rc::getInput(i), student, p_valid));
		}
		Output o = getOutputDestination();
		if (o != Output_None)
		{
			rc::setOutput(o, apply(rc::getOutput(o), student, p_valid));
		}
	}
}


// namespace end
}
