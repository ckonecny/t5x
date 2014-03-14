#ifndef INC_RC_OUTPUTCHANNELPROCESSOR_H
#define INC_RC_OUTPUTCHANNELPROCESSOR_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** OutputChannelProcessor.h
** Base class for classes reading an output channel
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
 *  \brief     Base class for classes reading an output channel
 *  \details   If a class uses output from the output channel storage, derive from this.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class OutputChannelProcessor
{
public:
	/*! \brief Sets the output channel index.
	    \param p_source Index to use as source output channel.*/
	void setSource(OutputChannel p_source);
	
	/*! \brief Gets the output channel index.
	    \return Index currently used as source output channel.*/
	OutputChannel getSource() const;
	
protected:
	/*! \brief Constructs an OutputChannelProcessor object
	    \param p_source Index to use as source output channel.*/
	OutputChannelProcessor(OutputChannel p_source = OutputChannel_None);
	
	OutputChannel m_source; //!< Index of output channel to use as source.
};


} // namespace end

#endif // INC_RC_OUTPUTCHANNELPROCESSOR_H
