#ifndef INC_RC_ANALOGSWITCH_H
#define INC_RC_ANALOGSWITCH_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** AnalogSwitch.h
** Switch which acts as analog input
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <InputSource.h>
#include <SwitchProcessor.h>


namespace rc
{

/*! 
 *  \brief     Class to which takes a switch as input and acts as analog input.
 *  \details   This class provides functionality for using a switch as analog input.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class AnalogSwitch : public SwitchProcessor, public InputSource
{
public:
	/*! \brief Constructs an AnalogSwitch object.
	    \param p_source The switch to use.
	    \param p_destination Index to use as destination for the input.*/
	AnalogSwitch(Switch p_source = Switch_None, Input p_destination = Input_None);
	
	/*! \brief Sets the time it takes to transition between states.
	    \param p_time The duration of the transition in milliseconds, range [0 - 10000] (instant - 10 sec).*/
	void setDuration(uint16_t p_time);
	
	/*! \brief Gets the time it takes to transition between states.
	    \return The duration of the transition in milliseconds, range [0 - 10000] (instant - 10 sec).*/
	uint16_t getDuration() const;
	
	/*! \brief Updates internal state.
	    \param p_state Input switch state.
	    \return Current position, normalized [-256 - 256].*/
	int16_t update(SwitchState p_state);
	
	/*! \brief Updates internal state.
	    \return Current position, normalized [-256 - 256].*/
	int16_t update();
	
private:
	uint16_t m_duration; //!< Time which it takes to transition in milliseconds (0 = instant)
	uint16_t m_time;     //!< Current position in timeline.
	uint16_t m_lastTime; //!< Time at which previous update was called.
};
/** \example analogswitch_example.pde
 * This is an example of how to use the AnalogSwitch class.
 */
 

} // namespace end

#endif // INC_RC_ANALOGSWITCH_H
