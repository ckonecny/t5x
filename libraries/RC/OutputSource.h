#ifndef INC_RC_OUTPUTSOURCE_H
#define INC_RC_OUTPUTSOURCE_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** OutputSource.h
** Base class for classes acting as a source of output
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
 *  \brief     Base class for classes acting as a source of output
 *  \details   If a class can provide output, derive from this.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class OutputSource
{
public:
	/*! \brief Sets the destination index.
	    \param p_index Index to use as destination for the output.*/
	void setDestination(Output p_index);
	
	/*! \brief Gets the destination index.
	    \return Index currently used destination for the output.*/
	Output getDestination() const;
	
protected:
	/*! \brief Constructs an OutputSource object
	    \param p_index Index to use as destination for the output.*/
	OutputSource(Output p_index = Output_None);
	
	/*! \brief Writes an output value to the destination.
	    \param p_value Value to write.
	    \return p_value.*/
	int16_t writeOutputValue(int16_t p_value) const;
	
	Output m_destination; //!< Index of output to use as destination
};


} // namespace end

#endif // INC_RC_OUTPUTSOURCE_H
