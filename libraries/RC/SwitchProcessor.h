#ifndef INC_RC_SWITCHPROCESSOR_H
#define INC_RC_SWITCHPROCESSOR_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** SwitchProcessor.h
** Base class for classes taking switch input
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <switch.h>


namespace rc
{

/*! 
 *  \brief     Base class for classes taking switch input
 *  \details   If a class uses input from the switch storage, derive from this.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class SwitchProcessor
{
public:
	/*! \brief Sets the switch index.
	    \param p_source Index to use as source switch.
	    \note use Switch_None to force isActiveState to false.*/
	void setSource(Switch p_source);
	
	/*! \brief Gets the input index.
	    \return Index currently used as source input.*/
	Switch getSource() const;
	
	/*! \brief Sets the switch state at which processing is active.
	    \param p_state State at which processing is active, State_Disconnected for always (default).*/
	void setActiveState(SwitchState p_state);
	
	/*! \brief Gets the switch state at which processing is active.
	    \return State at which processing is active, State_Disconnected for always (default).*/
	SwitchState getActiveState() const;
	
protected:
	/*! \brief Constructs an SwitchProcessor object
	    \param p_source Index to use as source switch.
	    \param p_state State at which processing is active.*/
	SwitchProcessor(Switch p_source = Switch_None, SwitchState p_state = SwitchState_Disconnected);
	
	/*! \brief Tests if the switch is in active state.
	    \return True when active, false when inactive.*/
	bool isActiveState() const;
	
	Switch      m_source;      //!< Index of switch to use as source.
	SwitchState m_activeState; //!< State at which processing is active.
};


} // namespace end

#endif // INC_RC_SWITCHPROCESSOR_H
