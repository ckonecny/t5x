/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** InputChannelToInputPipe.cpp
** Class copying from input channel directly to input
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <InputChannelToInputPipe.h>
#include <rc_debug_lib.h>
#include <util.h>


namespace rc
{

// Public functions

InputChannelToInputPipe::InputChannelToInputPipe(InputChannel p_source, Input p_destination)
:
InputChannelProcessor(p_source),
InputSource(p_destination)
{
	
}


void InputChannelToInputPipe::apply() const
{
	if (m_source != InputChannel_None)
	{
		writeInputValue(rc::microsToNormalized(rc::getInputChannel(m_source)));
	}
}


// namespace end
}
