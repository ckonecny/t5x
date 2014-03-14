/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** AIPinCalibrator.cpp
** Class for calibrating an AIPin
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Arduino.h>

#include <AIPinCalibrator.h>
#include <rc_debug_lib.h>


namespace rc
{

// Public functions

AIPinCalibrator::AIPinCalibrator(AIPin* p_target)
:
m_pin(p_target),
m_active(false),
m_min(0),
m_max(0),
m_center(0),
m_start(0)
{
	
}


void AIPinCalibrator::setAIPin(AIPin* p_pin)
{
	RC_TRACE("set AIPin: %p", p_pin);
	RC_ASSERT_MSG(m_active == false, "stop calibrator before setting pin");
	
	if (m_active == false)
	{
		m_pin = p_pin;
	}
}


AIPin* AIPinCalibrator::getAIPin() const
{
	return m_pin;
}


void AIPinCalibrator::start()
{
	RC_TRACE("start");
	RC_ASSERT_MSG(m_active == false, "calibrator already started");
	RC_ASSERT_MSG(m_pin != 0, "set pin before starting calibrator");
	
	if (m_active == false && m_pin != 0)
	{
		m_min = 1023;
		m_max = 0;
		m_center = 0;
		m_start = 0;
		
		m_active = true;
	}
}


void AIPinCalibrator::update()
{
	if (m_active)
	{
		uint16_t raw = read();
		if (raw > m_max)
		{
			m_max = raw;
		}
		if (raw < m_min)
		{
			m_min = raw;
		}
		
		// the average of min and max is a pretty darn good estimate for the center
		if (m_start == 0)
		{
			// initial value of the center
			m_center = (m_min + m_max) / 2;
			m_start  = static_cast<uint16_t>(millis());
		}
		
		// make sure a min and max are set and that they're far enough apart
		// then make sure the input is floating somewhere around the center for a period of time
		if (m_min < m_max && (m_max - m_min >= Minimum_Band) &&
		    (raw < m_center + Minimum_Center) && (raw > m_center - Minimum_Center))
		{
			// we use a weighted average of the previous center and current raw value
			m_center = ((m_center * 3) + raw) / 4;
		}
		else
		{
			m_start = 0;
		}
		RC_TRACE("Raw: %u Min: %u Max: %u Center: %u Delta: %u",
			raw, m_min, m_max, m_center, m_start == 0 ? 0 : static_cast<uint16_t>(millis()) - m_start);
	}
}


bool AIPinCalibrator::isDone() const
{
	return m_active && m_start != 0 && ((static_cast<uint16_t>(millis()) - m_start) >= Center_Time);
}


void AIPinCalibrator::stop()
{
	if (isDone())
	{
		m_pin->setCalibration(m_min, m_center, m_max);
	}
	m_active = false;
}


// Private functions

uint16_t AIPinCalibrator::read()
{
	return analogRead(m_pin->getPin());
}


// namespace end
}
