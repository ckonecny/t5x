#ifndef INC_RC_OFFSET_H
#define INC_RC_OFFSET_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Offset.h
** Offset functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <InputModifier.h>
#include <SwitchProcessor.h>


namespace rc
{

/*! 
 *  \brief     Class to encapsulate offset.
 *  \details   Offsets are conditional trims, they may be activate by, for example, a flight mode switch.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class Offset : public InputModifier, public SwitchProcessor
{
public:
	/*! \brief Constructs an Offset object
	    \param p_offset The offset to set, range [-100 - 100].
	    \param p_index Input index to use as input/output.
	    \param p_switch The switch index to use as trigger.
	    \param p_state The switch state to use as trigger.*/
	Offset(int8_t p_offset = 0,
	       Input p_index = Input_None,
	       Switch p_switch = Switch_None,
	       SwitchState p_state = SwitchState_Disconnected);
	
	
	/*! \brief Sets the offset.
	    \param p_offset The offset to set, range [-100 - 100].*/
	void setOffset(int8_t p_offset);
	
	/*! \brief Gets offset.
	    \return The current offset, range [-100 - 100].*/
	int8_t getOffset() const;
	
	/*! \brief Applies offset.
	    \param p_value Source value to apply offset to, range [-256 - 256].
	    \return Offset applied p_value, range [-256 - 256].*/
	int16_t apply(int16_t p_value) const;
	
	/*! \brief Applies dual rates to configured input.*/
	void apply() const;
	
private:
	int8_t m_offset;
};
/** \example offset_example.pde
 * This is an example of how to use the Offset class.
 */


} // namespace end

#endif // INC_RC_OFFSET_H
