#ifndef INC_RC_ROTARYENCODER_H
#define INC_RC_ROTARYENCODER_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** RotaryEncoder.h
** Class to read rotary encoder.
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>


namespace rc
{

/*! 
 *  \brief     Rotary Encoder.
 *  \details   A class for reading a rotary encoder.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class RotaryEncoder
{
public:
	/*! \brief Creates a RotaryEncoder object.
	    \param p_pinA Digital input pin A.
	    \param p_pinB Digital input pin B.
	    \param p_pullUp True if pull-up resistors should be enabled on input pins.
	    \note Will set up external interrupts for the pins.
	    \warning Only use pins that support external interrupts.*/
	RotaryEncoder(uint8_t p_pinA = 2, uint8_t p_pinB = 3, bool p_pullUp = false);
	
	/*! \brief Sets the hardware pin to use for pin A.
	    \param p_pin The hardware pin to use which supports external interrupts.
	    \note Will set up external interrupts for the pin.
	    \warning Only use external interrupts, not pin change interrupts!*/
	void setPinA(uint8_t p_pin);
	
	/*! \brief Gets hardware pin A.
	    \return Current hardware pin A.*/
	uint8_t getPinA() const;
	
	/*! \brief Sets the hardware pin to use for pin B.
	    \param p_pin The hardware pin to use which supports external interrupts.
	    \note Will set up external interrupts for the pin.
	    \warning Only use external interrupts, not pin change interrupts!*/
	void setPinB(uint8_t p_pin);
	
	/*! \brief Gets hardware pin B.
	    \return Current hardware pin B.*/
	uint8_t getPinB() const;
	
	/*! \brief Sets minimum value.
	    \param p_min Minimum value, range [-128 - 127].
	    \note default is -128.*/
	void setMin(int8_t p_min);
	
	/*! \brief Gets minimum value.
	    \return Minimum value, range [-128 - 127].*/
	int8_t getMin() const;
	
	/*! \brief Sets maximum value.
	    \param p_max Maximum value, range [-128 - 127].
	    \note default is 127.*/
	void setMax(int8_t p_max);
	
	/*! \brief Gets maximum value.
	    \return Maximum value, range [-128 - 127].*/
	int8_t getMax() const;
	
	/*! \brief Sets whether position wraps around.
	    \param p_wrap True if position should wrap around.
	    \note default is true.*/
	void setWrap(bool p_wrap);
	
	/*! \brief Gets whether position wraps around.
	    \return True if position wraps around.*/
	bool isWrap() const;
	
	/*! \brief Sets whether direction should be reversed.
	    \param p_reverse True if rotation should be reversed.
	    \note default is false.*/
	void setReversed(bool p_reverse);
	
	/*! \brief Gets whether direction is reversed.
	    \return True if direction is reversed.*/
	bool isReversed() const;
	
	/*! \brief Sets position to 0 (unless min > 0 or max < 0)
	    \note when min > 0, position = min
	          when max < 0, position = max.*/
	void reset();
	
	/*! \brief Reads number of "steps" since last read.
	    \return Number of "steps" since last read.
	    \note A 12 step encoder will read 12 steps in a full turn.*/
	int8_t readSteps();
	
	/*! \brief Reads absolute position in "steps".
	    \return Absolute position in steps.
	    \note A 12 step encoder will read 12 steps in a full turn.*/
	int8_t readPosition() const;
	
	/*! \brief External interrupt callback function.
	    \note Call this from your interrupt handler if you're using your own.
		      Make sure you set the interrupt trigger to pin change.*/
	void pinChanged();
	
private:
	/*! \brief External interrupt callback function.
	    \param p_pin The hardware pin that changed.
	    \param p_user User data (pointer to RotaryEncoder object).*/
	static void isr(uint8_t p_pin, void* p_user);
	
	uint8_t m_pinA;    //!< Hardware pin A.
	uint8_t m_pinB;    //!< Hardware pin B.
	uint8_t m_last;    //!< Last pin states.
	int8_t  m_counter; //!< Internal counter.
	bool    m_pullUp;  //!< Whether pull-up resistors are enabled.
	
	int8_t m_min;      //!< Min value.
	int8_t m_max;      //!< Max value.
	bool   m_wrap;     //!< Whether position wraps around at min or max.
	bool   m_reversed; //!< Whether the operation should be reversed.
	
	int8_t m_pos;   //!< Current position.
	int8_t m_steps; //!< Number of steps since last readSteps.
};
/** \example rotaryencoder_example.pde
 * This is an example of how to use the RotaryEncoder class.
 */
 
} // namespace end


#endif // INC_RC_ROTARYENCODER_H
