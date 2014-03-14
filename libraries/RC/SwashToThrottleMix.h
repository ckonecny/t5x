#ifndef INC_RC_SWASHTOTHROTTLEMIX_H
#define INC_RC_SWASHTOTHROTTLEMIX_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** SwashToThrottleMix.h
** Swashplate to Throttle mix
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <input.h>
#include <ThrottleMixBase.h>


namespace rc
{

/*! 
 *  \brief     Class to encapsulate Swashplate to Throttle mixing.
 *  \details   Custom class for sw->thr mix.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class SwashToThrottleMix : public ThrottleMixBase
{
public:
	/*! \brief Constructs a SwashToThrottleMix object
	    \param p_ail Aileron mix, range [0 - 100].
	    \param p_ele Elevator mix, range [0 - 100].*/
	SwashToThrottleMix(uint8_t p_ail = 0, uint8_t p_ele = 0);
	
	/*! \brief Sets Aileron mix.
	    \param p_mix Aileron mix, range [0 - 100].*/
	void setAilMix(uint8_t p_mix);
	
	/*! \brief Gets aileron mix.
	    \return Aileron mix, range [0 - 100].*/
	uint8_t getAilMix() const;
	
	/*! \brief Sets elevator mix.
	    \param p_mix Elevator mix, range [0 - 100].*/
	void setEleMix(uint8_t p_mix);
	
	/*! \brief Gets elevator mix.
	    \return Elevator mix, range [0 - 100].*/
	uint8_t getEleMix() const;
	
	/*! \brief Applies swash to throttle mix.
	    \param p_thr Input throttle, range [-256 - 256].
	    \param p_ail Input aileron, range [-358 - 358].
	    \param p_ele Input elevator, range [-358 - 358].
	    \return Throttle with swash mix applied, range [-256 - 256].*/
	int16_t apply(int16_t p_thr, int16_t p_ail, int16_t p_ele) const;
	
	/*! \brief Applies swash to throttle mix through input system.
	    \warning For correct behavior, apply this mix BEFORE applying throttle curves or EXPO.*/
	void apply() const;
	
private:
	uint8_t m_ail;
	uint8_t m_ele;
	
};
/** \example swashtothrottlemix_example.pde
 * This is an example of how to use the SwashToThrottleMix class.
 */


} // namespace end

#endif // INC_RC_SWASHTOTHROTTLEMIX_H
