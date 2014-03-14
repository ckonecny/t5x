#ifndef INC_RC_SWITCH_H
#define INC_RC_SWITCH_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** switch.h
** Place where the state of switches is stored
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

/*!
 *  \file      switch.h
 *  \brief     Switch state include file.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
*/

namespace rc
{
	enum Switch //! Switch index
	{
		Switch_A, //!< Switch A
		Switch_B, //!< Switch B
		Switch_C, //!< Switch C
		Switch_D, //!< Switch D
		Switch_E, //!< Switch E
		Switch_F, //!< Switch F
		Switch_G, //!< Switch G
		Switch_H, //!< Switch H
		
		Switch_Count,
		Switch_None //!< No switch, special case
	};
	
	enum SwitchState //! Switch state
	{
		SwitchState_Up,           //!< Switch up
		SwitchState_Center,       //!< Switch center position (tri-state only)
		SwitchState_Down,         //!< Switch down
		SwitchState_Disconnected, //!< Switch not connected (default state)
		
		SwitchState_Count
	};
	
	enum SwitchType //! Switch type
	{
		SwitchType_Disconnected, //!< No switch connected
		SwitchType_BiState,      //!< 2 positions alternating switch
		SwitchType_TriState,     //!< 3 positions alternating switch (e.g. flight mode)
		SwitchType_Momentary,    //!< 2 positions momentary switch; spring loaded (e.g. trainer switch)
		
		SwitchType_Count
	};
	
	
	/*! \brief Sets state for a certain switch.
	    \param p_switch Switch to set state of.
	    \param p_state State to set.*/
	void setSwitchState(Switch p_switch, SwitchState p_state);
	
	/*! \brief Gets state of a certain switch.
	    \param p_switch Switch to get state of.*/
	SwitchState getSwitchState(Switch p_switch);
	
	/*! \brief Sets type for a certain switch.
	    \param p_switch Switch to set type of.
	    \param p_type Type to set.*/
	void setSwitchType(Switch p_switch, SwitchType p_type);
	
	/*! \brief Gets type of a certain switch.
	    \param p_switch Switch to get type of.*/
	SwitchType getSwitchType(Switch p_switch);
	
}

#endif // INC_RC_SWITCH_H
