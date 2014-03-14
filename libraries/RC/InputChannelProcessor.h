#ifndef INC_RC_INPUTCHANNELPROCESSOR_H
#define INC_RC_INPUTCHANNELPROCESSOR_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** InputChannelProcessor.h
** Base class for classes reading an input channel
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
 *  \brief     Base class for classes reading an input channel
 *  \details   If a class uses input from the input channel storage, derive from this.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class InputChannelProcessor
{
public:
	/*! \brief Sets the input channel index.
	    \param p_source Index to use as source input channel.*/
	void setSource(InputChannel p_source);
	
	/*! \brief Gets the input channel index.
	    \return Index currently used as source input channel.*/
	InputChannel getSource() const;
	
protected:
	/*! \brief Constructs an InputChannelProcessor object
	    \param p_source Index to use as source input channel.*/
	InputChannelProcessor(InputChannel p_source = InputChannel_None);
	
	InputChannel m_source; //!< Index of input channel to use as source.
};


} // namespace end

#endif // INC_RC_INPUTCHANNELPROCESSOR_H
