/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Expo.cpp
** Exponential functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Expo.h>
#include <rc_debug_lib.h>


namespace rc
{

enum
{
	EXPO_POINTS = 15 //!< number of points to interpolate over, not including 0 and 1
};


// Pre-calculated expo points based on x^3 and x^(1/3)
static const uint8_t s_expoPos[EXPO_POINTS] = {0, 1, 2, 4, 8, 14, 21, 32, 46, 63, 83, 108, 137, 171, 210};
static const uint8_t s_expoNeg[EXPO_POINTS] = {101, 128, 147, 161, 174, 185, 194, 203, 211, 219, 226, 232, 239, 245, 251};


// Public functions

Expo::Expo(int8_t p_expo, Input p_index)
:
InputModifier(p_index),
m_expo(p_expo)
{
	
}


void Expo::set(int8_t p_expo)
{
	RC_TRACE("set expo: %d", p_expo);
	RC_ASSERT_MINMAX(p_expo, -100, 100);
	
	m_expo = p_expo;
}


int8_t Expo::get() const
{
	return m_expo;
}


Expo& Expo::operator = (int8_t p_rhs)
{
	RC_ASSERT_MINMAX(p_rhs, -100, 100);
	
	m_expo = p_rhs;
	return *this;
}


Expo& Expo::operator = (const Expo& p_rhs)
{
	m_expo  = p_rhs.m_expo;
	m_index = p_rhs.m_index;
	return *this;
}


Expo::operator int8_t () const
{
	return m_expo;
}


int8_t* Expo::operator & ()
{
	return &m_expo;
}


const int8_t* Expo::operator & () const
{
	return &m_expo;
}


int16_t Expo::apply(int16_t p_value) const
{
	RC_ASSERT_MINMAX(p_value, -256, 256);
	
	if (m_expo == 0)
	{
		// early abort
		return p_value;
	}
	
	int8_t expo = m_expo;
	
	// select the expo array
	const uint8_t* exparr = expo > 0 ? s_expoPos : s_expoNeg;
	if (expo < 0)
	{
		// ABS
		expo = -expo;
	}
	
	// save sign
	int16_t neg = p_value < 0 ? 1 : 0;
	if (neg)
	{
		p_value = -p_value;
	}
	
	uint8_t index = p_value >> 4;   // divide by EXPO_POINTS + 1
	uint8_t rem   = p_value & 0x0F; // remainder of divide by EXPO_POINTS + 1
	
	// linear interpolation on array values
	uint16_t lowval = static_cast<uint16_t>(index == 0 ? 0 : (index > EXPO_POINTS ? 256 : exparr[index - 1]));
	++index;
	uint16_t highval = static_cast<uint16_t>(index == 0 ? 0 : (index > EXPO_POINTS ? 256 : exparr[index - 1]));
	
	lowval  = lowval * ((EXPO_POINTS + 1) - rem);
	highval = highval * rem;
	
	uint16_t expoval = (lowval + highval) >> 4; // divide by EXPO_POINTS + 1
	
	// get weighted average between linear and expo value
	uint16_t out = ((p_value * (100 - expo)) + (expoval * expo)) / 100;
	
	return neg ? -out : out;
}


void Expo::apply() const
{
	if (m_index != Input_None)
	{
		rc::setInput(m_index, apply(rc::getInput(m_index)));
	}
}


// namespace end
}
