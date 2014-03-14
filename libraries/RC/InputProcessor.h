#ifndef INC_RC_INPUTPROCESSOR_H
#define INC_RC_INPUTPROCESSOR_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** InputProcessor.h
** Base class for classes taking input
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
 *  \brief     Base class for classes taking input
 *  \details   If a class uses input from the input storage, derive from this.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class InputProcessor
{
public:
	/*! \brief Sets the input index.
	    \param p_source Index to use as source input.*/
	void setSource(Input p_source);
	
	/*! \brief Gets the input index.
	    \return Index currently used as source input.*/
	Input getSource() const;
	
protected:
	/*! \brief Constructs an InputProcessor object
	    \param p_source Index to use as source input.*/
	InputProcessor(Input p_source = Input_None);
	
	Input m_source; //!< Index of input to use as source.
};


} // namespace end

#endif // INC_RC_INPUTPROCESSOR_H
