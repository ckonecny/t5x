/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ThrottleMixBase.cpp
** Base class for programmable throttle mixes
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <stdlib.h>

#include <ThrottleMixBase.h>
#include <rc_debug_lib.h>
#include <util.h>


namespace rc
{

// Protected functions

ThrottleMixBase::ThrottleMixBase(int8_t p_posMix, int8_t p_negMix, int16_t p_offset)
:
MixBase(p_posMix, p_negMix, p_offset)
{
	
}


int16_t ThrottleMixBase::applyThrottleMix(int16_t p_master, int16_t p_throttle) const
{
	RC_ASSERT_MINMAX(p_master, -358, 358);
	RC_ASSERT_MINMAX(p_throttle, -256, 256);
	
	// mix is strongest around center throttle, no mix at full or no throttle.
	int16_t thr = 256 - abs(p_throttle);
	
	// apply offset
	p_master = rc::clamp140(p_master - m_offset);
	
	// we're going to have overflows if we multiply by thr, so we divide that by two
	// same as mix = (mix * thr) / 256; but without overflows
	p_master = (p_master * (thr / 2)) / 128;
	
	// now we need to apply the actual mixes
	return rc::clampNormalized(p_throttle + rc::mix(p_master, p_master < 0 ? m_negMix : m_posMix));
}


// namespace end
}
