#ifndef INC_RC_PPMIN_H
#define INC_RC_PPMIN_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** PPMIn.h
** Pulse Position Modulation Input functionality
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
 *  \brief     Class to encapsulate PPM Input functionality.
 *  \details   This class provides a way to decode a PPM signal.
 *  \author    Daniel van den Ouden
 *  \date      Feb-2012
 *  \copyright Public Domain.
 *  \warning   This class should <b>NOT</b> be used together with the standard Arduino Servo library,
 *             use rc::ServoOut instead.
 */
class PPMIn
{
public:
	/*! \brief Constructs a PPMIn object.*/
	PPMIn();
	
#ifdef RC_USE_PCINT
	/*! \brief Sets pin on which PPM signal is received.
	    \param p_pin The pin on which a PPM signal is received.*/
	void setPin(uint8_t p_pin);
	
	/*! \brief Gets pin on which PPM signal is received.
	    \return The pin on which a PPM signal is received.*/
	uint8_t getPin() const;
#endif
	
	/*! \brief Starts measuring.
	    \param p_high Whether the incoming signal has high or low pulses.
	    \note It doesn't really matter if the pulses are low or high,
	          but you may want to try changing this parameter if you experience an
	          unstable signal. This may be due to simultaneous interrupts, changing
	          the p_high parameter will make the interrupt handler respond to either
	          the high or low pin change and may thus reduce problems created by
	          simultaneous interrupts.
	    \note Will register pin change interrupt if you're using that.
	    \warning Do <b>NOT</b> use this together with the standard Arduino Servo library,
	             use rc::ServoOut instead.*/
	void start(bool p_high = false);
	
	/*! \brief Stops measuring.
	    \note Will unregister pin change interrupt if you're using that.*/
	void stop();
	
	/*! \brief Sets minimum pause length, including pulse, in microseconds.
	    \param p_length Minimum pause length in microseconds.*/
	void setPauseLength(uint16_t p_length);
	
	/*! \brief Gets minimum pause length in microseconds.
	    \return The minimum pause length in microseconds.*/
	uint16_t getPauseLength() const;
	
	/*! \brief Sets minimum amount of time without signal after which the signal is considered lost.
	    \param p_length Minimum timeout time in milliseconds.
	    \warning Don't set this lower than your expected frame length (total length of pause + channels). */
	void setTimeout(uint16_t p_length);
	
	/*! \brief Gets amount of time without signal after which the signal is considered lost.
	    \return The minimum timeout time in milliseconds.*/
	uint16_t getTimeout() const;
	
	/*! \brief Checks if the input signal is stable.
	    \return Return true if a stable signal has been received. */
	bool isStable() const;
	
	/*! \brief Checks if the input signal has been lost.
	    \return Return true if the signal has been lost. */
	bool isLost() const;
	
	/*! \brief Gets the number of channels in the signal.
	    \return The number of channels found in the last received signal. */
	uint8_t getChannels() const;
	
	/*! \brief Handles pin change interrupt.
	    \param p_high Whether the pin is high or not.
	    \note Call this from your interrupt handler if you're handling interrupts yourself.*/
	void pinChanged(bool p_high);
	
	/*! \brief Updates the result buffer with new values.
	    \return Whether anything has been updated.
	    \note Call this often to detect loss of signal early.*/
	bool update();
	
private:
	enum State
	{
		State_Startup,   //!< Just started, no signal received yet.
		State_Listening, //!< Received first end of frame.
		State_Stable,    //!< Received second end of frame, stable.
		State_Confused,  //!< Something unexpected happened.
		State_Lost       //!< Signal has been lost (no valid signal for a while).
	};
	
#ifdef RC_USE_PCINT
	static void isr(uint8_t p_pin, bool p_high, void* p_user);
#endif
	
	State    m_state;       //!< Current state of input signal.
	uint8_t  m_channels;    //!< Number of channels in input signal.
	uint16_t m_pauseLength; //!< Minimum pause length in microseconds.
	uint16_t m_timeout;     //!< Time in milliseconds without signal after which the signal is considered "lost".
	
	uint16_t m_work[RC_MAX_CHANNELS]; //!< Work buffer.
	uint8_t  m_idx;                   //!< Current index in buffer.
	
	volatile bool m_newFrame;      //!< Whether a new frame is available or not.
	uint16_t      m_lastFrameTime; //!< Last time a new frame has been found
	
	uint16_t m_lastTime; //!< Time of last interrupt.
	bool     m_high;     //!< Whether the incoming signal uses high pulses.

#ifdef RC_USE_PCINT
	uint8_t m_pin;
#endif
};
/** \example ppmin_example.pde
 * This is an example of how to use the PPMIn class.
 */
 

} // namespace end

#endif // INC_RC_PPMIN_H
