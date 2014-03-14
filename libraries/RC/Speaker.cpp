/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Speaker.cpp
** Speaker functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Arduino.h>

#include <rc_debug_lib.h>
#include <Speaker.h>
#include <Timer2.h>

#ifdef RC_USE_SPEAKER


namespace rc
{

static volatile uint8_t* s_port = 0;
static          uint8_t  s_mask = 0;
static          uint32_t s_count = 0;
static          uint16_t s_repeat = 0;
static          uint32_t s_duration = 0;
static          uint32_t s_pause = 0;
static          uint8_t  s_cr = 0;


// Public functions

Speaker::Speaker(uint8_t p_pin)
:
m_pin(p_pin)
{
	setPin(m_pin);
}


void Speaker::setPin(uint8_t p_pin)
{
	RC_TRACE("set pin: %u", p_pin);
	
	stop();
	
	m_pin = p_pin;
	pinMode(m_pin, OUTPUT);
	digitalWrite(m_pin, LOW);
}


uint8_t Speaker::getPin() const
{
	return m_pin;
}


void Speaker::beep(uint16_t p_freq, uint8_t p_duration, uint8_t p_pause, uint8_t p_repeat)
{
	RC_TRACE("beep freq: %u dur: %u pause: %u rep: %u", p_freq, p_duration, p_pause, p_repeat);
	RC_ASSERT_MINMAX(p_freq, 35, 20000);
	RC_ASSERT_MINMAX(p_duration, 1, 250);
	RC_ASSERT_MINMAX(p_pause, 0, 250);
	
	Timer2::stop();
	
	// stop any active speaker
	if (s_port != 0)
	{
		// put pin low
		*(s_port + 2) &= ~s_mask;
	}
	
	// we'll need to find a decent prescaler
	uint32_t prescaler = 1;
	Timer2::Prescaler pre = Timer2::Prescaler_1;
	s_cr = 0;
	
	// precalculated
	//    1/ = 16000000 Hz = 0.0000000625 * 256 = 0.000016 = 62500    Hz / 2 = 31250 Hz
    //    8/ =  2000000 Hz = 0.0000005    * 256 = 0.000128 =  7812.5  Hz / 2 =  3906 Hz
	//   32/ =   500000 Hz = 0.000002     * 256 = 0.000512 =  1953.13 Hz / 2 =   976 Hz
	//   64/ =   250000 Hz = 0.000004     * 256 = 0.001024 =   976.56 Hz / 2 =   488 Hz
	//  128/ =   125000 Hz = 0.000008     * 256 = 0.002048 =   488.28 Hz / 2 =   244 Hz
	//  256/ =    62500 Hz = 0.000016     * 256 = 0.004096 =   244.14 Hz / 2 =   122 Hz
	// 1024/ =    15625 Hz = 0.000064     * 256 = 0.016384 =    61.04 Hz / 2 =    30 Hz
	if (p_freq > 3906)
	{
		prescaler = 8;
		pre = Timer2::Prescaler_8;
	}
	else if (p_freq > 976)
	{
		prescaler = 32;
		pre = Timer2::Prescaler_32;
	}
	else if (p_freq > 488)
	{
		prescaler = 64;
		pre = Timer2::Prescaler_64;
	}
	else if (p_freq > 244)
	{
		prescaler = 128;
		pre = Timer2::Prescaler_128;
	}
	else if (p_freq > 122)
	{
		prescaler = 256;
		pre = Timer2::Prescaler_256;
	}
	else if (p_freq > 30)
	{
		prescaler = 1024;
		pre = Timer2::Prescaler_1024;
	}
	else
	{
		return;
	}
	s_cr = F_CPU / (p_freq * 2 * prescaler);
	
	// calculate number of interrupts per second
	uint32_t intPerSec =  (F_CPU / prescaler) / (s_cr == 0 ? 256 : s_cr);
	
	// calculate number of interrupts for pause and duration
	s_duration = (p_duration * intPerSec) / 100;
	s_pause    = (p_pause * intPerSec) / 100;
	
	s_port = portInputRegister(digitalPinToPort(m_pin));
	s_mask = digitalPinToBitMask(m_pin);
	s_repeat = p_repeat * 2;
	s_count = s_duration;
	
	Timer2::setCompareMatch(true, true, Speaker::isr);
	OCR2A = s_cr; // overflow every 0.009984 seconds, 0.16% deviation
	TCNT2 = 0;
	
	Timer2::start(pre);
}


void Speaker::stop()
{
	RC_TRACE("stop");
	
	// stop only this speaker
	if (s_port == portInputRegister(digitalPinToPort(m_pin)))
	{
		Timer2::stop();
	}
	digitalWrite(m_pin, LOW);
}


void Speaker::isr()
{
	OCR2A += s_cr;
	
	--s_count;
	if (s_count == 0)
	{
		if (s_repeat == 0)
		{
			// done
			Timer2::stop();
			
			// pin low
			*(s_port + 2) &= ~s_mask; // Hackery; PORTx = PINx + 2 for Atmega328p
		}
		--s_repeat;
		if (s_repeat & 1)
		{
			// pin low
			*(s_port + 2) &= ~s_mask; 
			
			s_count = s_pause;
			
		}
		else
		{
			// pin high
			*(s_port + 2) |= s_mask;
			
			s_count = s_duration;
		}
	}
	else if ((s_repeat & 1) == 0)
	{
		// toggle pin
		*s_port = s_mask;
	}
}

// Preinstantiated objects

Speaker g_Speaker(8);


// namespace end
}

#endif // RC_USE_SPEAKER
