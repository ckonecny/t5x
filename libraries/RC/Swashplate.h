#ifndef INC_RC_SWASHPLATE_H
#define INC_RC_SWASHPLATE_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Swashplate.h
** Swashplate functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>


namespace rc
{

/*! 
 *  \brief     Class to encapsulate Swashplate functionality.
 *  \details   This class provides swashplate mixing.
 *  \author    Daniel van den Ouden
 *  \date      Feb-2012
 *  \copyright Public Domain.
 */
class Swashplate
{
public:
	enum Type //! Swashplate types, see http://www.futaba-rc.com/faq/faq-q1056.html
	{
		Type_H1,   //!< Independent servo for each axis
		Type_H2,   //!< Aileron and Pitch at 180 deg, mixed. Elevator independent. Pitch left, Ail right.
		Type_HE3,  //!< Same as above, but with elevator between ail and pit (at the rear), these are not needed for elevator
		Type_HR3,  //!< 120 degrees setup, pitch front left, ail front right, ele back.
		Type_HN3,  //!< Same as HN3 but rotated 150 deg ccw. Ail left, pit right back, ele right front.
		Type_H3,   //!< Same as HR3 but 140 degrees, square swash
		Type_H4,   //!< Same as HE3 but with second ele servo at front, 90 degree four servo setup
		Type_H4X,  //!< Same as H4 but rotated 45 deg ccw
		
		Type_Count
	};
	
	
	/*! \brief Constructs a Swashplate object
	*/
	Swashplate();
	
	/*! \brief Sets swash type
	    \param p_type Swashplate type to set.*/
	void setType(Type p_type);
	
	/*! \brief Gets swashplate type.
	    \return The swashplate type currently set.*/
	Type getType() const;
	
	/*! \brief Sets aileron mix.
	    \param p_mix The amount of aileron mix to set, range [-100 - 100].*/
	void setAilMix(int8_t p_mix);
	
	/*! \brief Gets aileron mix.
	    \return The current amount of aileron mix, range [-100 - 100].*/
	int8_t getAilMix() const;
	
	/*! \brief Sets elevator mix.
	    \param p_mix The amount of elevator mix to set, range [-100 - 100].*/
	void setEleMix(int8_t p_mix);
	
	/*! \brief Gets elevator mix.
	    \return The current amount of elevator mix, range [-100 - 100].*/
	int8_t getEleMix() const;
	
	/*! \brief Sets pitch mix.
	    \param p_mix The amount of pitch mix to set, range [-100 - 100].*/
	void setPitMix(int8_t p_mix);
	
	/*! \brief Gets pitch mix.
	    \return The current amount of pitch mix, range [-100 - 100].*/
	int8_t getPitMix() const;
	
	/*! \brief Applies swashplate mixing.
	    \param p_ail The amount of aileron input, range 140% [-358 - 358].
	    \param p_ele The amount of elevator input, range 140% [-358 - 358].
	    \param p_pit The amount of pitch input, range 140% [-358 - 358].
	    \param p_ailOUT Aileron servo, range 140% [-358 - 358].
	    \param p_eleOUT Elevator servo, range 140% [-358 - 358].
	    \param p_pitOUT Pitch servo, range 140% [-358 - 358].
	    \param p_ele2OUT Elevator servo 2, range 140% [-358 - 358].*/
	void apply(int16_t p_ail,
	           int16_t p_ele,
	           int16_t p_pit,
	           int16_t& p_ailOUT,
	           int16_t& p_eleOUT,
	           int16_t& p_pitOUT,
	           int16_t& p_ele2OUT) const;
			   
	/*! \brief Applies swashplate mixing.
	    \param p_ail The amount of aileron input, range 140% [-358 - 358].
	    \param p_ele The amount of elevator input, range 140% [-358 - 358].
	    \param p_pit The amount of pitch input, range 140% [-358 - 358].*/
	void apply(int16_t p_ail, int16_t p_ele, int16_t p_pit) const;
	
	/*! \brief Applies swashplate mixing. Fetches input from input system.*/
	void apply() const;
	
private:
	Type  m_type;    //!< Swashplate type
	int8_t m_ailMix; //!< Amount of aileron mix
	int8_t m_eleMix; //!< Amount of elevator mix
	int8_t m_pitMix; //!< Amount of pitch mix
};
/** \example swashplate_example.pde
 * This is an example of how to use the Swashplate class.
 */


} // namespace end

#endif // INC_RC_SWASHPLATE_H
