#ifndef INC_RC_UTIL_H
#define INC_RC_UTIL_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** util.h
** Utility include file
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

/*!
 *  \file util.h
 *  \brief Utility include file.
 *  \author    Daniel van den Ouden
 *  \date      Feb-2012
 *  \copyright Public Domain.
*/

namespace rc
{
	/*! \brief convert microseconds to a normalized value [-256 - 256].
	    \param p_micros Input in microseconds.
	    \return Normalized value, range [-256 - 256].*/
	int16_t microsToNormalized(uint16_t p_micros);
	
	/*! \brief convert a normalized value [-256 - 256] to microseconds.
	    \param p_normal Normalized value, range [-256 - 256].
	    \return Microseconds.*/
	uint16_t normalizedToMicros(int16_t p_normal);
	
	/*! \brief convert a certain range to a normalized value [-256 - 256].
	    \param p_value Value within range [0 - p_range].
	    \param p_range Max value in the range [1 - 65535].
	    \return Normalized value, range [-256 - 256].*/
	int16_t rangeToNormalized(uint16_t p_value, uint16_t p_range);
	
	/*! \brief convert a normalized value [-256 - 256] to range.
	    \param p_normal Normalized value, range [-256 - 256].
	    \param p_range Max value in the range [1 - 65535].
	    \return Value in range.*/
	uint16_t normalizedToRange(int16_t p_normal, uint16_t p_range);
	
	/*! \brief Clamp a normalized value to the [-256 - 256] range.
	    \param p_value Any value which is supposed to be inside the [-256 - 256] range but may not be.
	    \return Value clamped to the range [-256 - 256].*/
	int16_t clampNormalized(int16_t p_value);
	
	/*! \brief Clamp a 140% value to the [-358 - 358] range.
	    \param p_value Any value which is supposed to be inside the [-358 - 358] range but may not be.
	    \return Value clamped to the 140% range [-358 - 358].*/
	int16_t clamp140(int16_t p_value);
	
	/*! \brief Mix a value.
	    \param p_value A value in the 140% range [-358 - 358].
	    \param p_mix An amount of mix [-100 - 100]
	    \return Mix applied to value.*/
	int16_t mix(int16_t p_value, int8_t p_mix);
	
	/*! \brief Sets servo center.
	    \param p_center Center of servo in microseconds.*/
	void setCenter(uint16_t p_center);
	
	/*! \brief Gets the servo center.
	    \return The servo center in microseconds.*/
	uint16_t getCenter();
	
	/*! \brief Sets maximum travel from center.
	    \param p_travel Travel of servo in microseconds.*/
	void setTravel(uint16_t p_travel);
	
	/*! \brief Gets maximum travel from center.
	    \return Travel of servo in microseconds.*/
	uint16_t getTravel();
	
	/*! \brief Sets timings according to Futaba standards, center 1520, travel 600.*/
	void loadFutaba();
	
	/*! \brief Sets timings according to JR standards, center 1500, travel 600.*/
	void loadJR();
}

#endif // INC_RC_UTIL_H
