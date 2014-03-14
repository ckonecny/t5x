#ifndef INC_RC_SERVOIN_H
#define INC_RC_SERVOIN_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ServoIn.h
** Servo Signal Input functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>
#include <avr/pgmspace.h>

#include <rc_config.h>


namespace rc
{

/*! 
 *  \brief     Class to encapsulate Servo Signal Input functionality.
 *  \details   This class provides a way to read and decode a Servo signal.
 *  \author    Daniel van den Ouden
 *  \date      Feb-2012
 *  \warning   This class should <b>NOT</b> be used together with the standard Arduino Servo library,
 *             use rc::ServoOut instead.
 *  \copyright Public Domain.
 */
class ServoIn
{
public:
	
	/*! \brief Constructs a ServoIn object.*/
	ServoIn();
	
#ifdef RC_USE_PCINT
	/*! \brief Sets all pins.
	    \param p_pins Array of pins of RC_MAX_CHANNELS size located in PROGMEM!.
	    \note Will set all pins to INPUT mode.*/
	void setPins(const prog_uint8_t* p_pins);
	
	/*! \brief Sets single servo pin.
	    \param p_servo Servo of which to set the pin.
	    \param p_pin Pin to which the servo signal is attached.
	    \note Will set p_pin to INPUT mode.*/
	void setPin(uint8_t p_servo, uint8_t p_pin);
	
	/*! \brief Gets single servo pin.
	    \param p_servo Servo of which to get the pin.
	    \return Pin to which the servo signal is attached.*/
	uint8_t getPin(uint8_t p_servo) const;
#endif
	
	/*! \brief Starts measuring.
	    \param p_high Whether the incoming signal has high or low pulses.
	    \warning Do <b>NOT</b> use this together with the standard Arduino Servo library,
	             use rc::ServoOut instead.
	    \note Will register pin change interrupts when using the internal pcint handler.
	    \note Set pins before use.*/
	void start(bool p_high = true);
	
	/*! \brief Stops measuring.
	    \note Will unregister pin change interrupts when using the internal pcint handler.*/
	void stop();
	
#ifndef RC_USE_PCINT
	/*! \brief Handles pin change interrupt.
	    \param p_servo The servo that changed.
	    \param p_high Whether the pin is high or not.
	    \note Call this from your interrupt handler if you're using your own.*/
	void pinChanged(uint8_t p_servo, bool p_high);
#endif
	
	/*! \brief Updates output buffer with new values.*/
	void update();
	
private:
#ifdef RC_USE_PCINT
	void pinChanged(uint8_t p_pin, bool p_high); //!< Internal pin change interrupt handler
	static void isr(uint8_t p_pin, bool p_high, void* p_user); //!< ISR
#endif
	
	bool     m_high;                         //!< Whether pulses are high or low.
	uint16_t m_pulseStart[RC_MAX_CHANNELS];  //!< Last measured pulse start for each servo.
	uint16_t m_pulseLength[RC_MAX_CHANNELS]; //!< Last measured pulse length for each servo.
#ifdef RC_USE_PCINT
	uint8_t  m_lastPin;               //!< Last pin that was active.
	uint8_t  m_pins[RC_MAX_CHANNELS]; //!< List of pins to read from.
#endif
};
/** \example servoin_example.pde
 * This is an example of how to use the ServoIn class.
 */

} // namespace end

#endif // INC_RC_SERVOIN_H
