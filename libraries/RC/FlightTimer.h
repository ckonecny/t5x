#ifndef INC_RC_FLIGHTTIMER_H
#define INC_RC_FLIGHTTIMER_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** FlightTimer.h
** Programmable timer functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <SwitchProcessor.h>


namespace rc
{

/*! 
 *  \brief     Programmable timer.
 *  \details   A programmable timer with alarm.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class FlightTimer : public SwitchProcessor
{
public:
	/*! \brief Creates a FlightTimer object.
	    \param p_source Switch to trigger timer.
	    \param p_state Switch state to trigger timer.*/
	FlightTimer(Switch p_source = Switch_None, SwitchState p_state = SwitchState_Disconnected);
	
	/*! \brief Sets the target time for the timer.
	    \param p_seconds The target time in seconds, range [1 - 18000] (up to 5 hours).
	    \note Will reset the timer.*/
	void setTarget(uint16_t p_seconds);
	
	/*! \brief Gets the target time for the timer.
	    \return The target time in seconds, range [1 - 18000] (up to 5 hours).*/
	uint16_t getTarget() const;
	
	/*! \brief Sets the direction the timer will be counting in.
	    \param p_up True when the timer should start at 0 and count up,
		            false when the timer should start at target and count down.
	    \note Will reset the timer.*/
	void setDirection(bool p_up);
	
	/*! \brief Gets the direction the timer will be counting in.
	    \return True when the timer should start at 0 and count up,
		        false when the timer should start at target and count down.*/
	bool getDirection() const;
	
	/*! \brief Gets the current time of the timer.
	    \return The current time in seconds, may be negative when counting down.*/
	int16_t getTime() const;
	
	/*! \brief Resets the timer.*/
	void reset();
	
	/*! \brief Updates the timer.
	    \param p_active True if the timer is active, false if it's paused.*/
	void update(bool p_active);
	
	/*! \brief Updates the timer.*/
	void update();
	
private:
	int16_t  m_time;   //!< current time in seconds.
	int16_t  m_target; //!< target time in seconds.
	uint16_t m_millis; //!< millisecond state of time.
	uint16_t m_last;   //!< millisecond state of last update.
	bool     m_up;     //!< true if direction is up.
};
/** \example flighttimer_example.pde
 * This is an example of how to use the FlightTimer class.
 */


} // namespace end

#endif // INC_RC_FLIGHTTIMER_H
