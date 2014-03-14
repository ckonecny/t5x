#ifndef INC_RC_INPUTMODIFIER_H
#define INC_RC_INPUTMODIFIER_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** InputModifier.h
** Base class for classes having an input and performing operations on it
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <input.h>


namespace rc
{

/*! 
 *  \brief     Base class for classes having configurable input on which to perform operations
 *  \details   If a class can modify input, derive from this.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class InputModifier
{
public:
	/*! \brief Sets the input index.
	    \param p_index Index to use as source input.*/
	void setIndex(Input p_index);
	
	/*! \brief Gets the input index.
	    \return Index currently used as source input.*/
	Input getIndex() const;
	
protected:
	/*! \brief Constructs a InputModifier object
	    \param p_index Index to use as source input.*/
	InputModifier(Input p_index = Input_None);
	
	Input m_index; //!< Index of input to perform modification on
};


} // namespace end

#endif // INC_RC_INPUTMODIFIER_H
