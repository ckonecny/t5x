#ifndef INC_RC_INPUTSWITCH_H
#define INC_RC_INPUTSWITCH_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** InputSwitch.h
** Class which takes input from the input buffer and acts like a switch
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <InputProcessor.h>
#include <SwitchSource.h>


namespace rc
{

/*! 
 *  \brief     Class which takes input from the input buffer and acts like a bi-state switch.
 *  \details   Takes input from the input buffer and writes to the switch buffer.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class InputSwitch : public InputProcessor, public SwitchSource
{
public:
	/*! \brief Constructs an InputSwitch object
	    \param p_source Index to use as source input.
	    \param p_destination Switch to use as destination.*/
	InputSwitch(Input p_source = Input_None, Switch p_destination = Switch_None);
	
	/*! \brief Sets the mark at which input should be considered Up position (unless reversed).
	    \param p_mark Mark to set, range [-256 - 256].
	    \note default = 0.*/
	void setMark(int16_t p_mark);
	
	/*! \brief Gets the mark at which input should be considered Up position (unless reversed).
	    \return Mark, range [-256 - 256].*/
	int16_t getMark() const;
	
	/*! \brief Sets the dead band (hysteseris).
	    \param p_band Dead band width, range [0 - 255].
	    \note default = 0.
		\note When dead band = 2, state will change to Up when input >= Mark + 2 and down when input < Mark - 2.
	    \note Dead band is NOT active in ranged mode.*/
	void setDeadBand(uint8_t p_band);
	
	/*! \brief Gets the dead band (hysteseris).
	    \return p_band Dead band width, range [0 - 255].*/
	uint8_t getDeadBand() const;
	
	/*! \brief Sets reversing.
	    \param p_reverse True when up and down should be flipped.
	    \note default = false.*/
	void setReversed(bool p_reverse);
	
	/*! \brief Gets reversing.
	    \return True when up and down will be flipped.*/
	bool isReversed() const;
	
	/*! \brief Sets mirroring (symmetrical).
	    \param p_mirror True when mark should be mirrored around center.
	    \note default = false.
	    \note When mirrored, state will be Up when input between +Mark and -Mark (unless reversed).*/
	void setMirrored(bool p_mirror);
	
	/*! \brief Gets mirroring (symmetrical).
	    \return True when mark will be mirrored around center.*/
	bool isMirrored() const;
	
	/*! \brief Sets ranged mode (box).
	    \param p_ranged True when a second mark should be used.
	    \note default = false.
	    \note When ranged, state will be Up when input between Mark and Mark2 (unless reversed).
	    \note May be combined with mirroring.
	    \note Dead band is NOT active in ranged mode.*/
	void setRanged(bool p_ranged);
	
	/*! \brief Gets ranged mode (box).
	    \return True when second mark is active.*/
	bool isRanged() const;
	
	/*! \brief Sets the second mark (for ranged mode).
	    \param p_mark Mark to set, range [-256 - Mark].
	    \note default = Mark - 1.
	    \note only valid when ranged mode is on.
	    \note When Mark2 > Mark, Mark and Mark2 will be swapped.*/
	void setMark2(int16_t p_mark);
	
	/*! \brief Gets the second mark.
	    \return Second mark, range [-256 - Mark].*/
	int16_t getMark2() const;
	
	/*! \brief Reads and processes.
	    \param p_value Input value, range [-256 - 256].
	    \return Current switch state.*/
	SwitchState read(int16_t p_value) const;
	
	/*! \brief Reads and processes.
	    \return Current switch state.*/
	SwitchState read() const;
	
private:
	SwitchState write(bool p_up) const; //!< Helper function
	
	int16_t m_mark;  //!< Up mark
	int16_t m_mark2; //!< Second mark for ranged mode, always < Mark
	uint8_t m_dead;  //!< Dead band
	
	bool m_reverse; //!< Reversed
	bool m_mirror;  //!< Mirrored
	bool m_range;   //!< Ranged
};
/** \example inputswitch_example.pde
 * This is an example of how to use the InputSwitch class.
 */


} // namespace end

#endif // INC_RC_INPUTSWITCH_H
