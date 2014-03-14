#ifndef INC_RC_AIPIN_H
#define INC_RC_AIPIN_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** AIPin.h
** Analog input pin functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <InputSource.h>


namespace rc
{

/*! 
 *  \brief     Class to encapsulate analog input functionality.
 *  \details   This class provides functionality for reading analog input.
 *  \author    Daniel van den Ouden
 *  \date      Feb-2012
 *  \copyright Public Domain.
 */
class AIPin : public InputSource
{
public:
	/*! \brief Constructs an AIPin object.
	    \param p_pin The hardware pin to use.
	    \param p_destination The index to use as destination.*/
	AIPin(uint8_t p_pin, Input p_destination = Input_None);
	
	/*! \brief Sets the hardware pin to use.
	    \param p_pin The hardware pin to use.*/
	void setPin(uint8_t p_pin);
	
	/*! \brief Gets the hardware pin.
	    \return The current hardware pin.*/
	uint8_t getPin() const;
	
	/*! \brief Assignment operator, sets hardware pin.
	    \param p_pin The hardware pin to use.
	    \return Reference to AIPin object.*/
	AIPin& operator = (uint8_t p_pin);
	
	/*! \brief Cast operator, casts object to uint8_t.
	    \return Current hardware pin.*/
	operator uint8_t () const;
	
	/*! \brief Sets whether the input should be reversed or not.
	    \param p_reverse Whether to reverse the input or not.*/
	void setReverse(bool p_reverse);
	
	/*! \brief Gets whether the input is reversed.
	    \return Whether the input is reversed or not.*/
	bool isReversed() const;
	
	/*! \brief Sets the trim.
	    \param p_trim The trim, range [-100 - 100].*/
	void setTrim(int8_t p_trim);
	
	/*! \brief Gets the trim.
	    \return The trim, range [-100 - 100].*/
	int8_t getTrim() const;
	
	/*! \brief Sets the calibration center.
	    \param p_center The raw center, range [0 - 1023].*/
	void setCenter(uint16_t p_center);
	
	/*! \brief Gets the calibration center.
	    \return The center, range [0 - 1023].*/
	uint16_t getCenter() const;
	
	/*! \brief Sets the calibration minimum.
	    \param p_min The raw minimum, range [0 - 1023].*/
	void setMin(uint16_t p_min);
	
	/*! \brief Gets the calibration minimum.
	    \return The minimum, range [0 - 1023].*/
	uint16_t getMin() const;
	
	/*! \brief Sets the calibration maximum.
	    \param p_max The raw maximum, range [0 - 1023].*/
	void setMax(uint16_t p_max);
	
	/*! \brief Gets the calibration maximum.
	    \return The maximum, range [0 - 1023].*/
	uint16_t getMax() const;
	
	/*! \brief Sets the calibration values.
	    \param p_min The raw minimum, range [0 - p_center].
		\param p_center The raw center, range [p_min - p_max].
		\param p_max The raw maximum, range [p_center - 1023].*/
	void setCalibration(uint16_t p_min, uint16_t p_center, uint16_t p_max);
	
	/*! \brief Reads and processes.
	    \return Processed value, range [-256 - 256].*/
	int16_t read() const;
	
private:
	uint8_t  m_pin;      //!< Hardware pin.
	bool     m_reversed; //!< Input reverse.
	int8_t   m_trim;     //!< Trim.
	uint16_t m_center;   //!< Calibration center.
	uint16_t m_min;      //!< Calibration minimum.
	uint16_t m_max;      //!< Calibration maximum.
};
/** \example aipin_example.pde
 * This is an example of how to use the AIPin class.
 */


} // namespace end

#endif // INC_RC_AIPIN_H
