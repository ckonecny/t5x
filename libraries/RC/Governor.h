#ifndef INC_RC_GOVERNOR_H
#define INC_RC_GOVERNOR_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Governor.h
** Governor functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <OutputSource.h>
#include <SwitchProcessor.h>
#include <ThrottleHold.h>


namespace rc
{

/*! 
 *  \brief     Class to encapsulate Governor functionality.
 *  \details   Provides Governor control. Rates may be set for three switch states and thottle hold.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class Governor : public SwitchProcessor, public OutputSource
{
public:
	/*! \brief Constructs a Governor object
	    \param p_source Source switch.
	    \param p_destination Where results should be written to.*/
	Governor(Switch p_source = Switch_None,
	         Output p_destination = Output_GOV);
	
	/*! \brief Sets rate for down position.
	    \param p_rate Rate for down position, range [0 - 100].
	    \note Default is 0%.*/
	void setDownRate(uint8_t p_rate);
	
	/*! \brief Gets down position rate.
	    \return Down position rate, range [0 - 100].*/
	uint8_t getDownRate() const;
	
	/*! \brief Sets rate for center position.
	    \param p_rate Rate for center position, range [0 - 100].
	    \note Default is 50%.*/
	void setCenterRate(uint8_t p_rate);
	
	/*! \brief Gets center position rate.
	    \return Center position rate, range [0 - 100].*/
	uint8_t getCenterRate() const;
	
	/*! \brief Sets rate for up position.
	    \param p_rate Rate for up position, range [0 - 100].
	    \note Default is 100%.*/
	void setUpRate(uint8_t p_rate);
	
	/*! \brief Gets up position rate.
	    \return Up position rate, range [0 - 100].*/
	uint8_t getUpRate() const;
	
	/*! \brief Sets whether to use positive or negative limit for throttle hold.
	    \param p_posLimit The when positive limit needs to be used, false for negative.
	    \note This determines in which extreme direction the governor speed setting
		      should go in case of throttle hold.
		      Normal governor speed setting conform to end points, hold overrides them.
	    \note Default is false (negative).*/
	void setHoldDirection(bool p_posLimit);
	
	/*! \brief Gets throttle hold limit direction.
	    \return True for positive, false for negative.*/
	bool getHoldDirection() const;
	
	/*! \brief Copies throttle hold settings from a throttle hold object.
	    \param p_hold Throttle hold object to copy settings from.*/
	void setHold(const ThrottleHold& p_hold);
	
	/*! \brief Removes hold settings.*/
	void disableHold();
	
	/*! \brief Applies governor.
	    \param p_state Switch state.
		\param p_hold Whether throttle hold is active
	    \return Governor speed settings, range [-256 - 256].*/
	int16_t apply(SwitchState p_state, bool p_hold = false) const;
	
	/*! \brief Applies governor based on configured input.
	    \return Governor speed settings, range [-256 - 256].*/
	int16_t apply() const;
	
private:
	uint8_t m_rates[3];
	bool    m_holdDirection;
	
	Switch      m_holdSwitch;
	SwitchState m_holdSwitchState;
};
/** \example governor_example.pde
 * This is an example of how to use the Governor class.
 */


} // namespace end


#endif // INC_RC_GOVERNOR_H
