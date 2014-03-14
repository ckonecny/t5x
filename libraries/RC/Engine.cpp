/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Engine.cpp
** Engine functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Engine.h>
#include <rc_debug_lib.h>


namespace rc
{

// Public functions

Engine::Engine(Output p_destination, Switch p_source, SwitchState p_state)
:
InputProcessor(Input_THR),
OutputSource(p_destination),
ThrottleMixBase(0, 0, 0),
SwitchProcessor(p_source, p_state),
m_idle(-256),
m_rudMix(0)
{
	
}


void Engine::setRudderMix(int8_t p_mix)
{
	RC_TRACE("Set rudder mix: %d", p_mix);
	RC_ASSERT_MINMAX(p_mix, -100, 100);
	
	m_rudMix = p_mix;
	setPosMix(p_mix);
	setNegMix(p_mix);
}


int8_t Engine::getRudderMix() const
{
	return m_rudMix;
}


void Engine::setIdle(int16_t p_idle)
{
	RC_TRACE("Set idle: %d", p_idle);
	RC_ASSERT_MINMAX(p_idle, -256, 256);
	
	m_idle = p_idle;
}


int16_t Engine::getIdle() const
{
	return m_idle;
}


int16_t Engine::apply(int16_t p_thr, int16_t p_rud, bool p_cut) const
{
	if (p_cut)
	{
		return -256;
	}
	int16_t result = applyThrottleMix(p_rud, p_thr);
	return result < m_idle ? m_idle : result;
}


void Engine::apply() const
{
	writeOutputValue(apply(getInput(InputProcessor::m_source), getInput(Input_RUD), isActiveState()));
}


// namespace end
}

