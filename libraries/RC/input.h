#ifndef INC_RC_INPUT_H
#define INC_RC_INPUT_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** input.h
** Place where the input for various functions are stored
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

/*!
 *  \file      input.h
 *  \brief     Function input include file.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
*/

namespace rc
{
	enum Input //! Input index
	{
		Input_AIL, //!< Aileron input
		Input_ELE, //!< Elevator input
		Input_THR, //!< Throttle input
		Input_RUD, //!< Rudder input
		Input_FLP, //!< Flap input
		Input_BRK, //!< Airbrake input
		Input_PIT, //!< Pitch input
		
		Input_Count,
		Input_None //!< No input, special case
	};
	
	
	/*! \brief Sets value for a certain input.
	    \param p_input Input to set value of.
	    \param p_value Value to set, range 140% [-358 - 358].*/
	void setInput(Input p_input, int16_t p_value);
	
	/*! \brief Gets value of a certain input.
	    \param p_input Input to get value of.*/
	int16_t getInput(Input p_input);
	
}

#endif // INC_RC_INPUT_H
