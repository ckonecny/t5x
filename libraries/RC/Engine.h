#ifndef INC_RC_ENGINE_H
#define INC_RC_ENGINE_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Engine.h
** Engine functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <InputProcessor.h>
#include <OutputSource.h>
#include <SwitchProcessor.h>
#include <ThrottleMixBase.h>


namespace rc
{

/*! 
 *  \brief     Class to encapsulate engine(s).
 *  \details   Takes THR input and writes to THRn output.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class Engine : public InputProcessor, public OutputSource, public ThrottleMixBase, public SwitchProcessor
{
public:
	/*! \brief Constructs an Engine object.
	    \param p_destination Output destination.
		\param p_switch Throttle cut switch.
	    \param p_state Throttle cut switch state.*/
	Engine(Output p_destination,
	       Switch p_switch = Switch_None,
	       SwitchState p_state = SwitchState_Down);
	
	/*! \brief Sets rudder mix.
	    \param p_mix Amount of rudder to mix, range [-100 - 100].
	    \note default is 0.*/
	void setRudderMix(int8_t p_mix);
	
	/*! \brief Gets rudder mix.
	    \return Amount of rudder to mix, range [-100 - 100].*/
	int8_t getRudderMix() const;
	
	/*! \brief Sets idle level.
	    \param p_idle Engine idle level, range [-256 - 256].
	    \note default is -256.*/
	void setIdle(int16_t p_idle);
	
	/*! \brief Gets idle level.
	    \return Engine idle level, range [-256 - 256].*/
	int16_t getIdle() const;
	
	/*! \brief Applies engine mix.
	    \param p_thr Source throttle input, range [-256 - 256].
		\param p_rud Source rudder input, range [-256 - 256].
	    \param p_cut Whether to apply throttle cut.
	    \return Mixed output, range [-256 - 256].*/
	int16_t apply(int16_t p_thr, int16_t p_rud, bool p_cut = false) const;
	
	/*! \brief Applies throttle.*/
	void apply() const;
	
private:
	int16_t m_idle;   //!< Idle throttle level
	int8_t  m_rudMix; //!< Rudder mix, range [-100 - 100].
};
/** \example engine_example.pde
 * This is an example of how to use the Engine class.
 */


} // namespace end

#endif // INC_RC_ENGINE_H
