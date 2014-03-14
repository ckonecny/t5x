/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** OutputToOutputChannelPipe.cpp
** Class copying from output directly to output channel
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <OutputToOutputChannelPipe.h>
#include <rc_debug_lib.h>
#include <util.h>


namespace rc
{

// Public functions

OutputToOutputChannelPipe::OutputToOutputChannelPipe(Output p_source, OutputChannel p_destination)
:
OutputProcessor(p_source),
OutputChannelSource(p_destination)
{
	
}


void OutputToOutputChannelPipe::apply() const
{
	if (m_source != Output_None)
	{
		writeOutputChannelValue(rc::normalizedToMicros(rc::getOutput(m_source)));
	}
}


// namespace end
}
