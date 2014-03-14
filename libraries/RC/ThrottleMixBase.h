#ifndef INC_RC_THROTTLEMIXBASE_H
#define INC_RC_THROTTLEMIXBASE_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ThrottleMixBase.h
** Base class for throttle mixes
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <MixBase.h>


namespace rc
{

/*! 
 *  \brief     Base class for throttle mixes.
 *  \details   This class provides basic mixing for throttle.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class ThrottleMixBase : public MixBase
{
protected:
	/*! \brief Constructs an Mix object
	    \param p_posMix The amount of mix to use when master is positive, range [-100 - 100].
	    \param p_negMix The amount of mix to use when master is negative, range [-100 - 100].
	    \param p_offset Master offset, determines center point for master, range [-358 - 358].*/
	ThrottleMixBase(int8_t p_posMix = 0,
	                int8_t p_negMix = 0,
	                int16_t p_offset= 0);
	
	/*! \brief Applies master-throttle mix.
	    \param p_master Value that will be mixed, range [-358 - 358].
		\param p_throttle Value that mix will be applied to, range [-256 - 256].
	    \return p_master mixed into p_throttle, range [-256 - 256] (clamped).*/
	int16_t applyThrottleMix(int16_t p_master, int16_t p_throttle) const;
	
};


} // namespace end


#endif // INC_RC_THROTTLEMIXBASE_H
