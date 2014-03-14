#ifndef INC_RC_SPEAKER_H
#define INC_RC_SPEAKER_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Speaker.h
** Class to control piezo speaker/transducer,
** not to be confused with a buzzer/sounder.
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <rc_config.h>

#ifdef RC_USE_SPEAKER

namespace rc
{

/*! 
 *  \brief     Piezo Speaker.
 *  \details   A class for controlling a piezo speaker.
 *             Please note the difference beween a speaker and a buzzer. A buzzer
 *             has an internal oscillator and simply needs a DC voltage to oparete,
 *             a speaker requires a waveform of some sort.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 *  \warning   This class uses Timer 2 and can not be used together with other classes that use that timer.
 */
class Speaker
{
public:
	/*! \brief Creates a Speaker object.
	    \param p_pin Pin to which the speaker is connected.
		\warning This class uses Timer 2 and can not be used together with any other class that
		         uses timer 2, this includes the standard Arduino Tone functions and rc::Buzzer.*/
	Speaker(uint8_t p_pin);
	
	/*! \brief Sets the hardware pin to use.
	    \param p_pin The hardware pin to use.
	    \note Will stop THIS speaker if it was active.*/
	void setPin(uint8_t p_pin);
	
	/*! \brief Gets the hardware pin.
	    \return Current hardware pin.*/
	uint8_t getPin() const;
	
	/*! \brief Perform a beep.
	    \param p_freq The frequency of the beep in Hz, range [31 - 20000].
	    \param p_duration Duration of the beep in centiseconds (0.01 sec), range [1 - 250] (0.01 - 2.50 sec).
	    \param p_pause Pause between beeps in centiseconds, range [1 - 250].
	    \param p_repeat Number of times the beep should be repeated, range [0 - 255].
	    \note Total number of beeps is p_repeat + 1.
	    \note Can't go below 31 Hz because of hardware limitations, above 20000 is hardly audible nor useful.
	    \note Will stop ANY active speaker.*/
	void beep(uint16_t p_freq, uint8_t p_duration, uint8_t p_pause = 0, uint8_t p_repeat = 0);
	
	/*! \brief Stops this speaker.
	    \note Will only stop THIS speaker.*/
	void stop();
	
private:
	static void isr(); //!< Interrupt Service Routine
	
	uint8_t m_pin;    //!< Hardware pin.
	uint8_t m_repeat; //!< Internal counter;
};
/** \example speaker_example.pde
 * This is an example of how to use the Speaker class.
 */
 
 extern Speaker g_Speaker; //!< Global speaker object on pin 8, change if needed


} // namespace end

#endif // RC_USE_SPEAKER

#endif // INC_RC_SPEAKER_H
