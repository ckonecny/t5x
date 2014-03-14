#ifndef INC_RC_TIMER2_H
#define INC_RC_TIMER2_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Timer2.h
** Timer2 functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>


namespace rc
{

/*! 
 *  \brief     Class to encapsulate Timer2 functions.
 *  \details   This class provides centralised Timer2 controls.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \warning   This class should <b>NOT</b> be used together with the standard Arduino Tone functions,
 *             use rc::Buzzer or rc::Speaker instead.
 *  \copyright Public Domain.
 */
class Timer2
{
public:
	enum Prescaler //!< Timer prescaler
	{
		Prescaler_1    = 1, //!< F_CPU /    1
		Prescaler_8    = 2, //!< F_CPU /    8
		Prescaler_32   = 3, //!< F_CPU /   32
		Prescaler_64   = 4, //!< F_CPU /   64
		Prescaler_128  = 5, //!< F_CPU /  128
		Prescaler_256  = 6, //!< F_CPU /  256
		Prescaler_1024 = 7, //!< F_CPU / 1024
		
		Prescaler_Count
	};
	
	typedef void (*Callback)(void); //!< Callback function for interrupt routines
	
	/*! \brief Sets all default values, call this first.
	    \note  This function should be called prior to using any other Timer2 function.*/
	static void init();
	
	/*! \brief Starts timer2.
	    \param p_prescaler Prescaler to use.*/
	static void start(Prescaler p_prescaler = Prescaler_1024);
	
	/*! \brief Checks if timer2 is running.
	    \return Whether or not timer2 is running.*/
	static bool isRunning();
	
	/*! \brief Stops timer2.*/
	static void stop();
	
	/*! \brief Enables/Disables Compare Match Interrupt.
	    \param p_enable Whether to enable or disable Compare Match Interrupt.
	    \param p_OCIE2A Whether to use OCIE2A or OCIE2B.
	    \param p_callback Function to call at interrupt.*/
	static void setCompareMatch(bool p_enable, bool p_OCIE2A, Callback p_callback = 0);
		
	/*! \brief Enables/Disables Overflow Interrupt.
	    \param p_enable Whether to enable or disable Overflow Interrupt.
	    \param p_callback Function to call at interrupt.*/
	static void setOverflow(bool p_enable, Callback p_callback = 0);
	
	/*! \brief Enables/Disables Toggle pin on Compare Match A.
	    \param p_enable Whether to enable or disable toggle pin.
	    \param p_OC2A Whether to toggle OC2A or OC2B.*/
	static void setToggle(bool p_enable, bool p_OC2A);
	
	
private:
	Timer2(); //!< Not instantiable
	
};
/** \example timer2_example.pde
 * This is an example of how to use the Timer2 class.
 */


} // namespace end

#endif // INC_RC_TIMER1_H
