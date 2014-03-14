/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Curve.cpp
** Curve functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <avr/pgmspace.h>

#include <Curve.h>
#include <rc_debug_lib.h>
#include <util.h>


namespace rc
{

// NOTE: this may give a warning:
// warning: only initialized variables can be placed into program memory area
// this may be safely ignored, it's a known compiler bug in arvgcc (which won't happen for .c files)
static const int16_t PROGMEM sc_defaults[Curve::DefaultCurve_Count][Curve::PointCount] =
{
	{-256, -192, -128, -64,   0,  64, 128, 192, 256}, // DefaultCurve_Linear
	{   0,   32,   64,  96, 128, 160, 192, 224, 256}, // DefaultCurve_HalfLinear
	{ 256,  192,  128,  64,   0,  64, 128, 192, 256}  // DefaultCurve_V
};


// Public functions

Curve::Curve(DefaultCurve p_curve, Input p_source, Input p_destination)
:
InputProcessor(p_source),
InputSource(p_destination),
m_lowTrim(0),
m_centerTrim(0),
m_highTrim(0)
{
	loadCurve(p_curve);
}


void Curve::loadCurve(DefaultCurve p_curve)
{
	RC_TRACE("load default: %d", p_curve);
	RC_ASSERT(p_curve < DefaultCurve_Count);
	
	memcpy_P(m_points, sc_defaults[p_curve], sizeof(int16_t) * PointCount);
}


void Curve::setPoint(uint8_t p_point, int16_t p_value)
{
	RC_TRACE("set point: %d : %d", p_point, p_value);
	RC_ASSERT(p_point < PointCount);
	RC_ASSERT_MINMAX(p_value, -256, 256);
	
	if (p_point < PointCount)
	{
		m_points[p_point] = p_value;
	}
}


int16_t Curve::getPoint(uint8_t p_point) const
{
	RC_ASSERT(p_point < PointCount);
	
	if (p_point < PointCount)
	{
		return m_points[p_point];
	}
	return 0;
}


int16_t& Curve::operator[](uint8_t p_index)
{
	RC_ASSERT(p_index < PointCount);
	
	return m_points[p_index];
}


const int16_t& Curve::operator[](uint8_t p_index) const
{
	RC_ASSERT(p_index < PointCount);
	
	return m_points[p_index];
}


void Curve::setLowTrim(int8_t p_trim)
{
	RC_TRACE("set low trim: %d", p_trim);
	RC_ASSERT_MINMAX(p_trim, -100, 100);
	
	m_lowTrim = p_trim;
}


int8_t Curve::getLowTrim() const
{
	return m_lowTrim;
}


void Curve::setCenterTrim(int8_t p_trim)
{
	RC_TRACE("set center trim: %d", p_trim);
	RC_ASSERT_MINMAX(p_trim, -100, 100);
	
	m_centerTrim = p_trim;
}


int8_t Curve::getCenterTrim() const
{
	return m_centerTrim;
}


void Curve::setHighTrim(int8_t p_trim)
{
	RC_TRACE("set high trim: %d", p_trim);
	RC_ASSERT_MINMAX(p_trim, -100, 100);
	
	m_highTrim = p_trim;
}


int8_t Curve::getHighTrim() const
{
	return m_highTrim;
}


void Curve::setAllTrim(int8_t p_trim)
{
	RC_TRACE("set all trim: %d", p_trim);
	RC_ASSERT_MINMAX(p_trim, -100, 100);
	
	m_lowTrim    = p_trim;
	m_centerTrim = p_trim;
	m_highTrim   = p_trim;
}


int16_t Curve::apply(int16_t p_value) const
{
	RC_ASSERT_MINMAX(p_value, -256, 256);
	
	p_value += 256; // range [0 - 512]
	uint8_t index = static_cast<uint8_t>(p_value >> 6);  // divide by 64, range [0 - 8]
	int8_t  rem   = static_cast<int8_t>(p_value & 0x3F); // remainder of division
	
	// linear interpolation on curve values
	int16_t lowval = getPointWithTrim(index);
	int16_t highval = getPointWithTrim(index + 1);
	
	lowval  = lowval * (64 - rem);
	highval = highval * rem;
	
	return writeInputValue((lowval + highval) >> 6); // weighted average
}


int16_t Curve::apply() const
{
	if (m_source != Input_None)
	{
		return apply(rc::getInput(m_source));
	}
	return 0;
}


// Private functions

int16_t Curve::getPointWithTrim(uint8_t p_index) const
{
	if (p_index > 8)
	{
		p_index = 8;
	}
	int16_t point = m_points[p_index];
	
	// apply low end and center trim (for low end)
	if (p_index < 4)
	{
		if (m_lowTrim != 0)
		{
			// index == 0 ? + 100% trim
			// index == 1 ? +  75% trim
			// index == 2 ? +  50% trim
			// index == 3 ? +  25% trim
			point += (static_cast<int16_t>(m_lowTrim) * (4 - p_index)) / 4;
		}
		if (m_centerTrim != 0)
		{
			// index == 0 ? +   0% trim
			// index == 1 ? +  25% trim
			// index == 2 ? +  50% trim
			// index == 3 ? +  75% trim
			point += (static_cast<int16_t>(m_centerTrim) * p_index) / 4;
		}
	}
	else // apply high end and center trim (for high end)
	{
		if (m_highTrim != 0)
		{
			// index == 8 ? + 100% trim
			// index == 7 ? +  75% trim
			// index == 6 ? +  50% trim
			// index == 5 ? +  25% trim
			// index == 4 ? +   0% trim
			point += (static_cast<int16_t>(m_highTrim) * (p_index - 4)) / 4;
		}
		if (m_centerTrim != 0)
		{
			// index == 8 ? +   0% trim
			// index == 7 ? +  25% trim
			// index == 6 ? +  50% trim
			// index == 5 ? +  75% trim
			// index == 4 ? + 100% trim
			point += (static_cast<int16_t>(m_centerTrim) * (8 - p_index)) / 4;
		}
	}
	return clampNormalized(point);
}


// namespace end
}
