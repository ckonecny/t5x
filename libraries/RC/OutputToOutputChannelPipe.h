#ifndef INC_RC_OUTPUTTOOUTPUTCHANNELPIPE_H
#define INC_RC_OUTPUTTOOUTPUTCHANNELPIPE_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** OutputToOutputChannelPipe.h
** Class copying from output buffer directly to output channel buffer
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <OutputProcessor.h>
#include <OutputChannelSource.h>


namespace rc
{

/*! 
 *  \brief     Class for copying from output directly to output channel
 *  \details   Fetches output and puts it in output buffer.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class OutputToOutputChannelPipe : public OutputProcessor, public OutputChannelSource
{
public:
	/*! \brief Constructs an OutputToOutputChannelPipe object
	    \param p_source Index to use as output source.
	    \param p_destination Index to use as output channel destination.*/
	OutputToOutputChannelPipe(Output p_source, OutputChannel p_destination);
	
	/*! \brief Fetches output and writes output channel.*/
	void apply() const;
	
};


} // namespace end

#endif // INC_RC_OUTPUTTOOUTPUTCHANNELPIPE_H
