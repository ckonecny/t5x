#ifndef INC_RC_BISTATESWITCH_H
#define INC_RC_BISTATESWITCH_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** BiStateSwitch.h
** Bi state switch (momentary or alternating)
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <SwitchSource.h>


namespace rc
{

/*! 
 *  \brief     Momentary or alternating bi state switch.
 *  \details   Abstraction of an ordinary or spring loaded 2 position switch.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class BiStateSwitch : public SwitchSource
{
public:
	/*! \brief Constructs a BiStateSwitch object
	    \param p_pin Input pin.
		\param p_destination Index to use as destination for the switch.
	    \param p_momentary True if the switch is spring loaded.
	    \param p_reversed Whether the switch is mounted up side down.*/
	BiStateSwitch(uint8_t p_pin,
	              Switch p_destination = Switch_None,
	              bool p_momentary = false,
	              bool p_reversed = false);
	
	/*! \brief Sets the hardware pin to use.
	    \param p_pin The hardware pin to use.*/
	void setPin(uint8_t p_pin);
	
	/*! \brief Gets the hardware pin.
	    \return Current hardware pin.*/
	uint8_t getPin() const;
	
	/*! \brief Sets whether the input should be reversed or not.
	    \param p_reverse Whether to reverse the input or not.*/
	void setReverse(bool p_reverse);
	
	/*! \brief Gets whether the input is reversed.
	    \return Whether the input is reversed or not.*/
	bool isReversed() const;
	
	/*! \brief Reads and processes.
	    \return Current switch state.*/
	SwitchState read() const;
	
private:
	uint8_t  m_pin;      //!< Hardware pin.
	bool     m_reversed; //!< Input reverse.
};
/** \example switch_example.pde
 * This is an example of how to use the BiStateSwitch and TriStateSwitch classes.
 */


} // namespace end

#endif // INC_RC_BISTATESWITCH_H
