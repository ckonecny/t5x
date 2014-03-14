#ifndef INC_RC_SERVOOUT_H
#define INC_RC_SERVOOUT_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ServoOut.h
** Servo Signal Output functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <rc_config.h>


namespace rc
{

/*! 
 *  \brief     Class to encapsulate Servo Signal Output functionality.
 *  \details   This class provides a way to generate a Servo signal.
 *  \author    Daniel van den Ouden
 *  \date      Feb-2012
 *  \warning   This class should <b>NOT</b> be used together with the standard Arduino Servo library.
 *  \copyright Public Domain.
 */
class ServoOut
{
public:
	
	/*! \brief Constructs a ServoOut object.
	    \param p_pins Input buffer of pins to connect servos to.*/
	ServoOut(const uint8_t* p_pins);
	
	/*! \brief Starts timers and output.*/
	void start();
	
	/*! \brief Sets the minimum length between pulses on a pin.
	    \param p_length The minimum length between two pulses in microseconds.*/
	void setPauseLength(uint16_t p_length);
	
	/*! \brief Gets the minimum length between pulses on a pin.
	    \return The minimum length between two pulses in microseconds.*/
	uint16_t getPauseLength() const;
	
	/*! \brief Updates all internal timings.
	    \param p_pinsChanged If any pins have changed, set this to true.*/
	void update(bool p_pinsChanged = false);
	
	/*! \brief Handles timer interrupt.*/
	static void handleInterrupt();
	
private:
	/*! \brief Internal interrupt handling. */
	void isr();
	
	uint16_t m_pauseLength; //!< Minimal length of pause between pulses on a pin in microseconds.
	
	const uint8_t* m_pins;   //!< External buffer defining pins to use.
	
	volatile uint16_t m_timings[RC_MAX_CHANNELS]; //!< Work buffer containing timings.
	volatile uint8_t  m_ports[RC_MAX_CHANNELS];   //!< Work buffer containing port addresses.
	volatile uint8_t  m_masks[RC_MAX_CHANNELS];   //!< Work buffer containing bitmasks.
	
	volatile uint8_t* m_activePort; //!< Address of port of currently active (high) pin.
	         uint8_t  m_activeMask; //!< Inverted bitmask of currently active (high) pin.
	volatile uint8_t* m_nextPort;   //!< Address of port of next active (high) pin.
	         uint8_t  m_nextMask;   //!< Bitmask of next active (high) pin.
	
	uint8_t m_idx; //!< Next index in work buffers.
	
	static ServoOut* s_instance; //!< Singleton instance.
};
/** \example servoout_example.pde
 * This is an example of how to use the ServoOut class.
 */

} // namespace end

#endif // INC_RC_SERVOOUT_H
