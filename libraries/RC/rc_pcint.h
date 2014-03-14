#ifndef INC_RC_PCINT_H
#define INC_RC_PCINT_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** rc_pcint.h
** Global pin change interrupt handler
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

// include global config settings first
#include <rc_config.h>


#ifdef RC_USE_PCINT

/*!
 *  \file      rc_pcint.h
 *  \brief     Global pin change interrupt handler.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
*/

namespace rc {
namespace pcint {

	/*! \brief Type definition for callback function
	    \param p_pin Hardware pin that changed
		\param p_high Whether the pin became high or low.
	    \param p_user User supplied data for callback.*/
	typedef void (*Callback)(uint8_t p_pin, bool p_high, void* p_user);
	
	/*! \brief Enable pin change interrupt and sets handler.
	    \param p_pin Hardware pin to enable pin change interrupt for.
	    \param p_callback Function to call on interrupt.
	    \param p_user User supplied data.*/
	void enable(uint8_t p_pin, Callback p_callback, void* p_user = 0);
	
	/*! \brief Disables pin change interrupt.
	    \param p_pin Hardware pin to disable change interrupts for.*/
	void disable(uint8_t p_pin);
	
} // pcint
} // rc

/** \example pcint_example.pde
 * This is an example of how to use the pin change interrupt functions.
 */
 
#endif // RC_USE_PCINT

#endif // INC_RC_PCINT_H
