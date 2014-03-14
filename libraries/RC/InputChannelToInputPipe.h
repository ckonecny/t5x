#ifndef INC_RC_INPUTCHANNELTOINPUTPIPE_H
#define INC_RC_INPUTCHANNELTOINPUTPIPE_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** InputChannelToInputPipe.h
** Class copying from input channel buffer directly to input buffer
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <InputChannelProcessor.h>
#include <InputSource.h>


namespace rc
{

/*! 
 *  \brief     Class for copying from input channel directly to input
 *  \details   Fetches input channel and puts it in input.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class InputChannelToInputPipe : public InputChannelProcessor, public InputSource
{
public:
	/*! \brief Constructs an InputChannelToInputPipe object
	    \param p_source Index to use as input channel source.
	    \param p_destination Index to use as input destination.*/
	InputChannelToInputPipe(InputChannel p_source, Input p_destination);
	
	/*! \brief Fetches input channel and writes input.*/
	void apply() const;
	
};


} // namespace end

#endif // INC_RC_INPUTCHANNELTOINPUTPIPE_H
