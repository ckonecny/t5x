#ifndef INC_RC_TRISTATESWITCH_H
#define INC_RC_TRISTATESWITCH_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** TriStateSwitch.h
** Tri state switch (alternating)
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
 *  \brief     Alternating tri state switch.
 *  \details   Abstraction of an ordinary or 3 position switch.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class TriStateSwitch : public SwitchSource
{
public:
	/*! \brief Constructs a TriStateSwitch object
	    \param p_upPin Up position pin.
		\param p_downPin Down position pin.
		\param p_destination Index to use as destination for the switch.
	    \param p_reversed Whether the switch is mounted up side down.*/
	TriStateSwitch(uint8_t p_upPin,
	               uint8_t p_downPin,
	               Switch p_destination = Switch_None,
	               bool p_reversed = false);
	
	
	/*! \brief Sets the hardware pin to use for up position.
	    \param p_pin The hardware pin to use.*/
	void setUpPin(uint8_t p_pin);
	
	/*! \brief Gets the hardware pin for up position.
	    \return Current hardware pin used for up position.*/
	uint8_t getUpPin() const;
	
	/*! \brief Sets the hardware pin to use for down position.
	    \param p_pin The hardware pin to use.*/
	void setDownPin(uint8_t p_pin);
	
	/*! \brief Gets the hardware pin for down position.
	    \return Current hardware pin used for down position.*/
	uint8_t getDownPin() const;
	
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
	uint8_t  m_upPin;    //!< Hardware pin for up position.
	uint8_t  m_downPin;  //!< Hardware pin for down position.
	bool     m_reversed; //!< Input reverse.
};
/** \example switch_example.pde
 */


} // namespace end

#endif // INC_RC_TRISTATESWITCH_H
