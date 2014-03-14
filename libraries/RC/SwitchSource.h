#ifndef INC_RC_SWITCHSOURCE_H
#define INC_RC_SWITCHSOURCE_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** SwitchSource.h
** Base class for classes acting as a switch
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
 *  \brief     Base class for classes acting as a switch
 *  \details   If a class can act like a switch, derive from this.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class SwitchSource
{
public:
	/*! \brief Sets the destination index.
	    \param p_index Index to use as destination for the switch.*/
	void setDestination(Switch p_index);
	
	/*! \brief Gets the destination index.
	    \return Index currently used destination for the switch.*/
	Switch getDestination() const;
	
protected:
	/*! \brief Constructs a SwitchSource object
	    \param p_index Index to use as destination for the switch.
	    \param p_type  Type of switch.*/
	SwitchSource(SwitchType p_type, Switch p_index = Switch_None);
	
	/*! \brief Writes a switch state to the destination.
	    \param p_state State to write.
	    \return p_state.*/
	SwitchState writeSwitchState(SwitchState p_state) const;
	
	Switch     m_destination; //!< Index of switch to use as destination.
	SwitchType m_type;        //!< Type of switch
};


} // namespace end

#endif // INC_RC_SWITCHSOURCE_H
