#ifndef INC_RC_RETRACTS_H
#define INC_RC_RETRACTS_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Retracts.h
** Retractable landing gear functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <SwitchProcessor.h>


namespace rc
{

/*! 
 *  \brief     Class to encapsulate retractable landing gear functionality.
 *  \details   This class provides controls for doors and landing gear.
 *  \author    Daniel van den Ouden
 *  \date      Oct-2012
 *  \copyright Public Domain.
 */
class Retracts : public SwitchProcessor
{
public:
	enum Type //! Type of retracts
	{
		Type_NoDoor, //!< Single servo, only landing gear (default)
		Type_Single, //!< Single servo controlling both doors and gear
		Type_Dual,   //!< Dual servos, one for the doors and one for the gear
		
		Type_Count
	};
	
	/*! \brief Constructs a Retracts object
	    \param p_type Retracts type.
	    \param p_source Switch to act on.
	    \param p_state  Switch state on which the gear should go down.*/
	Retracts(Type p_type = Type_NoDoor,
	         Switch p_source = Switch_None,
	         SwitchState p_state = SwitchState_Down);
	
	/*! \brief Sets retracts type
	    \param p_type Retracts type to set.*/
	void setType(Type p_type);
	
	/*! \brief Gets retracts type.
	    \return The retracts type currently set.*/
	Type getType() const;
	
	/*! \brief Sets the time which the doors take to open.
	    \param p_time The time to set, range [0 - 10000] (instant - 10 sec).*/
	void setDoorsSpeed(uint16_t p_time);
	
	/*! \brief Gets the time which the doors take to open.
	    \return The time the doors take to open, range [0 - 10000] (instant - 10 sec).*/
	uint16_t getDoorsSpeed() const;
	
	/*! \brief Sets the time which the gear takes to move.
	    \param p_time The time to set, range [0 - 10000] (instant - 10 sec).*/
	void setGearSpeed(uint16_t p_time);
	
	/*! \brief Gets the time which the doors take to open.
	    \return The time the gear takes to move, range [0 - 10000] (instant - 10 sec).*/
	uint16_t getGearSpeed() const;
	
	/*! \brief Sets the delay between the doors and the gear.
	    \param p_delay The delay in milliseconds, range [-10000 - 10000] (-10 - 10 sec).
	    \note A negative delay means the gear will lower before the doors have opened completely.
	          This can only be used in combination with a dual servo setup. The library will ensure
	          that the landing gear will not be lowered completely before the doors are completely open
	          and vice versa. */
	void setDelay(int16_t p_delay);
	
	/*! \brief Gets the delay between the doors and the gear.
	    \return The delay in milliseconds, range [-10000 - 10000] (-10 - 10 sec).*/
	int16_t getDelay() const;
	
	/*! \brief Opens the doors (if any) and lowers the gear.*/
	void down();
	
	/*! \brief Raises the gear and closes the doors (if any).*/
	void up();
	
	/*! \brief Only opens the doors (if any).
	    \note The gear will not be lowered.*/
	void openDoors();
	
	/*! \brief Closes the doors (if any).
	    \note The gear will be raised first if it hadn't been already.*/
	void closeDoors();
	
	/*! \brief Lowers the gear.
	    \note The doors will be opened first if they haven't been already.*/
	void lowerGear();
	
	/*! \brief Only raises the gear.
	    \note The doors will not be closed.*/
	void raiseGear();
	
	/*! \brief Returns whether the gear is _fully_ raised and the doors are completely closed.
	    \return whether the gear is _fully_ raised and the doors are completely closed.*/
	bool isUp() const;
	
	/*! \brief Returns whether the gear is _fully_ lowered and the doors are completely open.
	    \return whether the gear is _fully_ lowered and the doors are completely open.*/
	bool isDown() const;
	
	/*! \brief Returns whether the doors are _completely_ open.
	    \return whether the doors are _completely_ open.*/
	bool doorsAreOpen() const;
	
	/*! \brief Returns whether the doors are _completely_ closed.
	    \return whether the doors are _completely_ closed.*/
	bool doorsAreClosed() const;
	
	/*! \brief Returns whether the gear is _fully_ raised.
	    \return whether the gear is _fully_ raised.*/
	bool gearIsRaised() const;
	
	/*! \brief Returns whether the gear is _fully_ lowered.
	    \return whether the gear is _fully_ lowered.*/
	bool gearIsLowered() const;
	
	/*! \brief Updates the door and gear position.
	    \note  If a switch has been defined, up() or down() will be called in the update.*/
	void update();
	
	/*! \brief Gets the position of the doors servo.
	    \return Normalized channel value, range [-256 - 256].
		\note In a single servo setup this will return the same as getGearPosition(). */
	int16_t getDoorsPosition() const;
	
	/*! \brief Gets the position of the gear servo.
	    \return Normalized channel value, range [-256 - 256].
		\note In a single servo setup this will return the same as getDoorsPosition(). */
	int16_t getGearPosition() const;
	
private:
	void updateTimeline(); //!< Updates the internal timeline variables.
	
	Type m_type; //!< Retracts type
	
	uint16_t m_doorsSpeed; //!< Speed at which the doors open in milliseconds
	uint16_t m_gearSpeed;  //!< Speed at which the gear moves in milliseconds
	int16_t  m_delay;      //!< Delay between the doors and gear in milliseconds
	
	uint16_t m_lastTime; //!< Last time the update was called (used to calculate delta)
	
	int16_t m_time;       //!< Current position in the timeline
	int16_t m_moveTo;     //!< Position in timeline to move to
	int16_t m_doorsStart; //!< Time at which the doors start closing
	int16_t m_gearStart;  //!< Time at which the gear starts raising
	int16_t m_doorsEnd;   //!< Time at which the doors are closed
	int16_t m_gearEnd;    //!< Time at which the gear is raised
};

/** \example retracts_example.pde
 * This is an example of how to use the Retracts class.
 */


} // namespace end

#endif // INC_RC_RETRACTS_H
