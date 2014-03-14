#ifndef INC_RC_INPUTCHANNEL_H
#define INC_RC_INPUTCHANNEL_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** inputchannel.h
** Place where incoming channel data is stored
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <rc_config.h>


/*!
 *  \file      inputchannel.h
 *  \brief     Incoming channel data include file.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
*/

namespace rc
{
	enum InputChannel //! InputChannel index
	{
		InputChannel_1,  //!< Input Channel 1
		InputChannel_2,  //!< Input Channel 2
		InputChannel_3,  //!< Input Channel 3
		InputChannel_4,  //!< Input Channel 4
#if RC_MAX_CHANNELS >= 5
		InputChannel_5,  //!< Input Channel 5
#endif
#if RC_MAX_CHANNELS >= 6
		InputChannel_6,  //!< Input Channel 6
#endif
#if RC_MAX_CHANNELS >= 7
		InputChannel_7,  //!< Input Channel 7
#endif
#if RC_MAX_CHANNELS >= 8
		InputChannel_8,  //!< Input Channel 8
#endif
#if RC_MAX_CHANNELS >= 9
		InputChannel_9,  //!< Input Channel 9
#endif
#if RC_MAX_CHANNELS >= 10
		InputChannel_10, //!< Input Channel 10
#endif
#if RC_MAX_CHANNELS >= 11
		InputChannel_11, //!< Input Channel 11
#endif
#if RC_MAX_CHANNELS >= 12
		InputChannel_12, //!< Input Channel 12
#endif
#if RC_MAX_CHANNELS >= 13
		InputChannel_13, //!< Input Channel 13
#endif
#if RC_MAX_CHANNELS >= 14
		InputChannel_14, //!< Input Channel 14
#endif
#if RC_MAX_CHANNELS >= 15
		InputChannel_15, //!< Input Channel 15
#endif
#if RC_MAX_CHANNELS >= 16
		InputChannel_16, //!< Input Channel 16
#endif
#if RC_MAX_CHANNELS >= 17
		InputChannel_17, //!< Input Channel 17
#endif
#if RC_MAX_CHANNELS >= 18
		InputChannel_18, //!< Input Channel 18
#endif
		
		InputChannel_Count,
		InputChannel_None //!< No input channel, special case
	};
	
	
	/*! \brief Sets value for a certain input channel.
	    \param p_channel Input to set value of.
	    \param p_value Value to set in microseconds, range [750 - 2250].*/
	void setInputChannel(InputChannel p_channel, uint16_t p_value);
	
	/*! \brief Gets value of a certain input channel.
	    \param p_channel Input channel to get value of.
	    \return value of the channel in microseconds, range [750 - 2250].*/
	uint16_t getInputChannel(InputChannel p_channel);
	
	/*! \brief Gets a pointer to the raw input channels buffer.
	    \return Pointer to input channels buffer.*/
	uint16_t* getRawInputChannels();
}

#endif // INC_RC_INPUTCHANNEL_H
