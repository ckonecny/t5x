#ifndef INC_RC_INPUTSOURCE_H
#define INC_RC_INPUTSOURCE_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** InputSource.h
** Base class for classes acting as a source of input
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
 *  \brief     Base class for classes acting as a source of input
 *  \details   If a class can provide input, derive from this.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class InputSource
{
public:
	/*! \brief Sets the destination index.
	    \param p_index Index to use as destination for the input.*/
	void setDestination(Input p_index);
	
	/*! \brief Gets the destination index.
	    \return Index currently used destination for the input.*/
	Input getDestination() const;
	
protected:
	/*! \brief Constructs an InputSource object
	    \param p_index Index to use as destination for the input.*/
	InputSource(Input p_index = Input_None);
	
	/*! \brief Writes an input value to the destination.
	    \param p_value Value to write.
	    \return p_value.*/
	int16_t writeInputValue(int16_t p_value) const;
	
	Input m_destination; //!< Index of input to use as destination.
};


} // namespace end

#endif // INC_RC_INPUTSOURCE_H
