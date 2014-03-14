#ifndef INC_RC_GIMBAL_H
#define INC_RC_GIMBAL_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Gimbal.h
** Gimbal abstraction
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <AIPin.h>


namespace rc
{

/*! 
 *  \brief     Class to encapsulate gimbal input functionality.
 *  \details   This class provides functionality for reading gimbals.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class Gimbal
{
public:
	enum Mode //! Physical layout mode
	{
		Mode_1, //!< Left ELE + RUD, Right THR + AIL
		Mode_2, //!< Left THR + RUD, Right ELE + AIL
		Mode_3, //!< Left ELE + AIL, Right THR + RUD
		Mode_4, //!< Left THR + AIL, Right ELE + RUD
		
		Mode_Count
	};
	
	/*! \brief Constructs a Gimbal object.
	    \param p_horizPin The hardware pin to use for horizontal movement.
		\param p_vertiPin The hardware pin to use for vertical movement
	    \param p_left True if this is the left gimbal, false if it's the right one.
	    \param p_mode Layout mode 1/2/3/4.
	    \note Default mode is Mode 2.*/
	Gimbal(uint8_t p_horizPin, uint8_t p_vertiPin, bool p_left, Mode p_mode = Mode_2);
	
	/*! \brief Sets gimbal position left/right.
	    \param p_left True if this is the left gimbal, false if it's the right one.*/
	void setLeft(bool p_left);
	
	/*! \brief Gets gimbal position left/right.
	    \return True if this is the left gimbal, false if it's the right one.*/
	bool isLeft() const;
	
	/*! \brief Sets physical layout.
	    \param p_mode Layout mode 1/2/3/4.*/
	void setMode(Mode p_mode);
	
	/*! \brief Gets physical layout.
	    \return Layout mode 1/2/3/4.*/
	Mode getMode() const;
	
	/*! \brief Gets horizontal AIPin.
	    \return The AIPin for horizontal movement.*/
	AIPin& getHorizontal();
	
	/*! \brief Gets horizontal AIPin.
	    \return The AIPin for horizontal movement.*/
	const AIPin& getHorizontal() const;
	
	/*! \brief Gets vertical AIPin.
	    \return The AIPin for vertical movement.*/
	AIPin& getVertical();
	
	/*! \brief Gets vertical AIPin.
	    \return The AIPin for vertical movement.*/
	const AIPin& getVertical() const;
	
	
	/*! \brief Reads and processes.*/
	void read() const;
	
private:
	void updateLayout(); //!< updates pin layout
	
	AIPin m_hor; //!< Horizontal AIPin
	AIPin m_ver; //!< Vertical AIPin
	
	bool m_left; //!< Whether this is the left gimbal
	Mode m_mode; //!< Layout mode
	
};
/** \example gimbal_example.pde
 * This is an example of how to use the Gimbal class.
 */


} // namespace end

#endif // INC_RC_GIMBAL_H
