#ifndef INC_RC_SWITCHMODIFIER_H
#define INC_RC_SWITCHMODIFIER_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** SwitchModifier.h
** Base class for classes having switch input and performing operations on it
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
 *  \brief     Base class for classes having configurable switch input on which to perform operations
 *  \details   If a class can modify switch input, derive from this.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class SwitchModifier
{
public:
	/*! \brief Sets the switch index.
	    \param p_index Index to use as source input.*/
	void setIndex(Switch p_index);
	
	/*! \brief Gets the switch index.
	    \return Index currently used as source input.*/
	Switch getIndex() const;
	
protected:
	/*! \brief Constructs a SwitchModifier object
	    \param p_index Index to use as source input.*/
	SwitchModifier(Switch p_index = Switch_None);
	
	Switch m_index; //!< Index of switch to perform modification on
};


} // namespace end

#endif // INC_RC_SWITCHMODIFIER_H
