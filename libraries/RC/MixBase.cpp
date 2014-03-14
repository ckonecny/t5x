/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** MixBase.cpp
** Base class for programmable mixes
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <MixBase.h>
#include <rc_debug_lib.h>
#include <util.h>


namespace rc
{

// Public functions

void MixBase::setPosMix(int8_t p_mix)
{
	RC_TRACE("set pos mix: %d", p_mix);
	RC_ASSERT_MINMAX(p_mix, -100, 100);
	m_posMix = p_mix;
}


int8_t MixBase::getPosMix() const
{
	return m_posMix;
}


void MixBase::setNegMix(int8_t p_mix)
{
	RC_TRACE("set neg mix: %d", p_mix);
	RC_ASSERT_MINMAX(p_mix, -100, 100);
	m_negMix = p_mix;
}


int8_t MixBase::getNegMix() const
{
	return m_negMix;
}


void MixBase::setOffset(int16_t p_offset)
{
	RC_TRACE("set offset: %d", p_offset);
	RC_ASSERT_MINMAX(p_offset, -358, 258);
	m_offset = p_offset;
}


int16_t MixBase::getOffset() const
{
	return m_offset;
}


// Protected functions

MixBase::MixBase(int8_t p_posMix, int8_t p_negMix, int16_t p_offset)
:
m_posMix(p_posMix),
m_negMix(p_negMix),
m_offset(p_offset)
{
	
}


int16_t MixBase::applyMix(int16_t p_master, int16_t p_slave) const
{
	RC_ASSERT_MINMAX(p_master, -358, 358);
	RC_ASSERT_MINMAX(p_slave, -358, 358);
	p_master = rc::clamp140(p_master - m_offset);
	return rc::clamp140(p_slave + rc::mix(p_master, p_master < 0 ? m_negMix : m_posMix));
}


int16_t MixBase::applyOffsetMix(int16_t p_slave) const
{
	RC_ASSERT_MINMAX(p_slave, -358, 358);
	return rc::clamp140(p_slave - m_offset);
}


// namespace end
}
