#ifndef INC_RC_OUTPUTMODIFIER_H
#define INC_RC_OUTPUTMODIFIER_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** OutputModifier.h
** Base class for classes having an output and performing operations on it
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <output.h>


namespace rc
{

/*! 
 *  \brief     Base class for classes having configurable output on which to perform operations
 *  \details   If a class can modify output, derive from this.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class OutputModifier
{
public:
	/*! \brief Sets the output index.
	    \param p_index Index to use as source output.*/
	void setIndex(Output p_index);
	
	/*! \brief Gets the output index.
	    \return Index currently used as source output.*/
	Output getIndex() const;
	
protected:
	/*! \brief Constructs a OutputModifier object
	    \param p_index Index to use as source output.*/
	OutputModifier(Output p_index = Output_None);
	
	Output m_index; //!< Index of output to perform modification on
};


} // namespace end

#endif // INC_RC_OUTPUTMODIFIER_H
