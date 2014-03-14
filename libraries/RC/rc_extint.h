#ifndef INC_RC_EXTINT_H
#define INC_RC_EXTINT_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** rc_extint.h
** Global external interrupt handler
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

// include global config settings first
#include <rc_config.h>


#ifdef RC_USE_EXTINT

/*!
 *  \file      rc_extint.h
 *  \brief     Global external interrupt handler.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
*/

namespace rc {
namespace extint {

	/*! \brief Type definition for callback function
	    \param p_pin Hardware pin that changed
	    \param p_user User supplied data for callback.*/
	typedef void (*Callback)(uint8_t p_pin, void* p_user);
	
	enum ISC //!< Interrupt Sense Control
	{
		ISC_Low    = 0, //!< Low level of pin generates irq.
		ISC_Change = 1, //!< Any logical change of pin generates irq.
		ISC_Fall   = 2, //!< Falling edge of pin generates irq.
		ISC_Rise   = 3  //!< Rising edge of pin generates irq.
	};
	
	/*! \brief Checks if the pin supports external interrupts.
	    \param p_pin Hardware pin to check.
	    \return Whether external interrupts are supported for this pin.
	    \note Call this if you have trouble getting external interrupts to work.*/
	bool supported(uint8_t p_pin);
	
	/*! \brief Enable external interrupt and sets handler.
	    \param p_pin Hardware pin which supports external interrupt.
	    \param p_trigger State which triggers the interrupt.
	    \param p_callback Function to call on interrupt.
	    \param p_user User supplied data.
	    \note for Atmega 48/88/168/328 only pins 2 and 3 are available.
		      for Atmega 1280/2560 pins 2, 3, 21, 20, 19 and 18 are available.
		      for Atmega 32u4 pins 3, 2, 1 and 0 are available.
		      Consult the data sheets for more info.
		\warning This function does not make the pin a input pin! Call pinMode yourself.*/
	void enable(uint8_t p_pin, ISC p_trigger, Callback p_callback, void* p_user = 0);
	
	/*! \brief Disables pin change interrupt.
	    \param p_pin Hardware pin to disable change interrupts for.*/
	void disable(uint8_t p_pin);
	
} // extint
} // rc

/** \example extint_example.pde
 * This is an example of how to use the external interrupts functions.
 */
 
#endif // RC_USE_EXTINT

#endif // INC_RC_EXTINT_H
