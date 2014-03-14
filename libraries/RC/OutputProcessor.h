#ifndef INC_RC_OUTPUTPROCESSOR_H
#define INC_RC_OUTPUTPROCESSOR_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** OutputProcessor.h
** Base class for classes using output as a source
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
 *  \brief     Base class for classes using output as a source
 *  \details   If a class uses output from the output storage, derive from this.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class OutputProcessor
{
public:
	/*! \brief Sets the source index.
	    \param p_source Index to use as source output.*/
	void setSource(Output p_source);
	
	/*! \brief Gets the source index.
	    \return Index currently used as source output.*/
	Output getSource() const;
	
protected:
	/*! \brief Constructs an OutputProcessor object
	    \param p_source Index to use as source output.*/
	OutputProcessor(Output p_source = Output_None);
	
	Output m_source; //!< Index of output to use as source.
};


} // namespace end

#endif // INC_RC_OUTPUTPROCESSOR_H
