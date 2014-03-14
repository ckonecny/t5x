#ifndef INC_RC_INPUTCHANNELSOURCE_H
#define INC_RC_INPUTCHANNELSOURCE_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** InputChannelSource.h
** Base class for classes acting as a source of input channel
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <inputchannel.h>


namespace rc
{

/*! 
 *  \brief     Base class for classes acting as a source of input channel
 *  \details   If a class can provide an input channel, derive from this.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class InputChannelSource
{
public:
	/*! \brief Sets the destination index.
	    \param p_index Index to use as destination for the input channel.*/
	void setDestination(InputChannel p_index);
	
	/*! \brief Gets the destination index.
	    \return Index currently used destination for the input channel.*/
	InputChannel getDestination() const;
	
protected:
	/*! \brief Constructs an InputChannelSource object
	    \param p_index Index to use as destination for the input channel.*/
	InputChannelSource(InputChannel p_index = InputChannel_None);
	
	/*! \brief Writes an input channel value to the destination.
	    \param p_value Value to write.
	    \return p_value.*/
	uint16_t writeInputChannelValue(uint16_t p_value) const;
	
	InputChannel m_destination; //!< Index of input channel to use as destination.
};


} // namespace end

#endif // INC_RC_INPUTCHANNELSOURCE_H
