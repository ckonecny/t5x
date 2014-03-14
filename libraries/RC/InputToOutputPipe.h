#ifndef INC_RC_INPUTTOOUTPUTPIPE_H
#define INC_RC_INPUTTOOUTPUTPIPE_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** InputToOutputPipe.h
** Class copying from input directly to output
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <InputProcessor.h>
#include <OutputSource.h>


namespace rc
{

/*! 
 *  \brief     Class for copying from input directly to output
 *  \details   Fetches input and puts it in output.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class InputToOutputPipe : public InputProcessor, public OutputSource
{
public:
	/*! \brief Constructs an InputToOutputPipe object
	    \param p_source Index to use as input source.
	    \param p_destination Index to use as output destination.*/
	InputToOutputPipe(Input p_source, Output p_destination);
	
	/*! \brief Fetches input and writes output.*/
	void apply() const;
	
};


} // namespace end

#endif // INC_RC_INPUTTOOUTPUTPIPE_H
