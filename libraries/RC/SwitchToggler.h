#ifndef INC_RC_SWITCHTOGGLER_H
#define INC_RC_SWITCHTOGGLER_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** SwitchToggler.h
** Class that acts like a switch, toggling state on specified switch input
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <SwitchModifier.h>


namespace rc
{

/*! 
 *  \brief     Class that acts like a switch, toggling state on switch input.
 *  \details   Used to toggle the state when a switch is set to a defined state.
 *             This may be used to make spring loaded switches act like normal switches.
 *             By holding the spring loaded switch shortly, the state of the toggler will change.
 *             By holding it again shortly, the state will change back.
 *             Similar to how pulling a cord once will turn on the light and pulling it again turns it off.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class SwitchToggler : public SwitchModifier
{
public:
	/*! \brief Constructs a SwitchToggler object
	    \param p_toggleState The state which triggers the toggle.
	    \param p_index Switch index to use for input and output.*/
	SwitchToggler(SwitchState p_toggleState, Switch p_index = Switch_None);
	
	
	/*! \brief Sets the toggle state.
	    \param p_state The state which triggers the toggle.*/
	void setToggleState(SwitchState p_state);
	
	/*! \brief Gets the toggle state.
	    \return The state which triggers the toggle.*/
	SwitchState getToggleState() const;
	
	/*! \brief Applies toggler.
	    \param p_state Input state.
	    \return Toggled state.*/
	SwitchState apply(SwitchState p_state);
	
	/*! \brief Applies toggler to the set input.*/
	void apply();
	
private:
	SwitchState m_toggle; //!< State at which to toggle
	SwitchState m_last;   //!< Last state
	SwitchState m_state;  //!< Current state
	
};
/** \example switchtoggler_example.pde
 * This is an example of how to use the SwitchToggler class.
 */
 

} // namespace end

#endif // INC_RC_SWITCHTOGGLER_H
