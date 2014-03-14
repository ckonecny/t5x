#ifndef INC_RC_BUZZER_H
#define INC_RC_BUZZER_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Buzzer.h
** Class to control piezo buzzer/sounder,
** not to be confused with a transducer/speaker.
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <rc_config.h>

#ifdef RC_USE_BUZZER

namespace rc
{

/*! 
 *  \brief     Piezo Buzzer.
 *  \details   A class for controlling a piezo buzzer.
 *             Please note that a buzzer has a built in oscillator and simply
 *             requires a DC signal voltage to produce sound.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 *  \warning   This class uses Timer 2 and can not be used together with other classes that use that timer.
 */
class Buzzer
{
public:
	/*! \brief Creates a Buzzer object.
	    \param p_pin Pin on which the buzzer is connected.
		\warning This class uses Timer 2 and can not be used together with any other class that
		      uses timer 2, this includes the standard Arduino Tone functions.*/
	Buzzer(uint8_t p_pin);
	
	/*! \brief Sets the hardware pin to use.
	    \param p_pin The hardware pin to use.
	    \note Will stop THIS buzzer if it was active.*/
	void setPin(uint8_t p_pin);
	
	/*! \brief Gets the hardware pin.
	    \return Current hardware pin.*/
	uint8_t getPin() const;
	
	/*! \brief Perform a beep.
	    \param p_duration Duration of the beep in centiseconds (0.01 sec), range [1 - 250] (0.01 - 2.50 sec).
	    \param p_pause Pause between beeps in centiseconds, range [1 - 250].
	    \param p_repeat Number of times the beep should be repeated, range [0 - 255].
	    \note Total number of beeps is p_repeat + 1.
	    \note Will stop ANY currently active buzzer.*/
	void beep(uint8_t p_duration, uint8_t p_pause = 0, uint8_t p_repeat = 0);
	
	/*! \brief Stops this buzzer.
	    \note Will only stop THIS buzzer if it was active.*/
	void stop();
	
private:
	static void isr(); //!< Interrupt Service Routine
	
	uint8_t m_pin;    //!< Hardware pin.
	uint8_t m_repeat; //!< Internal counter;
};
/** \example buzzer_example.pde
 * This is an example of how to use the Buzzer class.
 */
 
 extern Buzzer g_Buzzer; //!< Global buzzer object on pin 8, change if needed


} // namespace end

#endif // RC_USE_BUZZER

#endif // INC_RC_BUZZER_H
