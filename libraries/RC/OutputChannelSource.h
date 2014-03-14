#ifndef INC_RC_OUTPUTCHANNELSOURCE_H
#define INC_RC_OUTPUTCHANNELSOURCE_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** OutputChannelSource.h
** Base class for classes acting as a source of output channel
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <outputchannel.h>


namespace rc
{

/*! 
 *  \brief     Base class for classes acting as a source of output channel
 *  \details   If a class can provide an output channel, derive from this.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class OutputChannelSource
{
public:
	/*! \brief Sets the destination index.
	    \param p_index Index to use as destination for the output channel.*/
	void setDestination(OutputChannel p_index);
	
	/*! \brief Gets the destination index.
	    \return Index currently used destination for the output channel.*/
	OutputChannel getDestination() const;
	
protected:
	/*! \brief Constructs an OutputChannelSource object
	    \param p_index Index to use as destination for the output channel.*/
	OutputChannelSource(OutputChannel p_index = OutputChannel_None);
	
	/*! \brief Writes an output channel value to the destination.
	    \param p_value Value to write.
	    \return p_value.*/
	uint16_t writeOutputChannelValue(uint16_t p_value) const;
	
	OutputChannel m_destination; //!< Index of output channel to use as destination.
};


} // namespace end

#endif // INC_RC_OUTPUTCHANNELSOURCE_H
