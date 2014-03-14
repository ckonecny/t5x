#ifndef INC_RC_SERIAL_H
#define INC_RC_SERIAL_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** rc_uart.h
** Basic uart communications for Atmega328p
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

/*!
 *  \file   rc_uart.h
 *  \brief  Basic uart communications for Atmega328p
 *  \author Daniel van den Ouden
 *  \date   Nov-2012
 *  \copyright Public Domain.
*/


namespace rc
{
namespace uart
{
	/*! \brief Initializes uart
		\param p_baud Baud rate.*/
	void init(uint16_t p_baud);
	
	/*! \brief Writes one byte
		\param p_byte byte to write.*/
	void put(uint8_t p_byte);
	
	/*! \brief Reads one byte
		\return Byte read.*/
	uint8_t get();
	
	/*! \brief Sets uart as stdout file*/
	void setStdOut();
	
	/*! \brief Sets uart as stdin file*/
	void setStdIn();
	
// namespace end
}
}

#endif // INC_RC_SERIAL_H
