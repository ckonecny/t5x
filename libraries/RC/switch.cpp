/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** switch.cpp
** Place where the state of switches is stored
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <switch.h>
#include <rc_debug_lib.h>


namespace rc
{

// we only need four bits per switch, but we'll use 8 to make life easier
// maybe this can be changed to be more memory friendly
static uint8_t s_values[Switch_Count] = { 0 };


void setSwitchState(Switch p_switch, SwitchState p_state)
{
	RC_ASSERT(p_switch < Switch_Count);
	RC_ASSERT(p_state < SwitchState_Count);
	RC_CHECK_MSG(p_state == SwitchState_Disconnected || getSwitchType(p_switch) != SwitchType_Disconnected,
	             "Setting state of disconnected switch %d", p_switch);
	
	s_values[p_switch] = (s_values[p_switch] & ~0x03) | static_cast<uint8_t>(p_state);
}


SwitchState getSwitchState(Switch p_switch)
{
	RC_ASSERT(p_switch < Switch_Count);
	if (getSwitchType(p_switch) == SwitchType_Disconnected)
	{
		return SwitchState_Disconnected;
	}
	return static_cast<SwitchState>(s_values[p_switch] & 0x03);
}


void setSwitchType(Switch p_switch, SwitchType p_type)
{
	RC_ASSERT(p_switch < Switch_Count);
	RC_ASSERT(p_type < SwitchType_Count);
	
	s_values[p_switch] = (s_values[p_switch] & ~0x0C) | (static_cast<uint8_t>(p_type) << 2);
}


SwitchType getSwitchType(Switch p_switch)
{
	RC_ASSERT(p_switch < Switch_Count);
	return static_cast<SwitchType>((s_values[p_switch] & 0x0C) >> 2);
}


// namespace end
}
