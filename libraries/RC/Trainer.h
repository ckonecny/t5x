#ifndef INC_RC_TRAINER_H
#define INC_RC_TRAINER_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Trainer.h
** Trainer port functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <input.h>
#include <InputChannelProcessor.h>
#include <output.h>
#include <SwitchProcessor.h>


namespace rc
{

/*! 
 *  \brief     Class to encapsulate Trainer port functionality.
 *  \details   This class handles trainer port input.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class Trainer : public SwitchProcessor, public InputChannelProcessor
{
public:
	/*! \brief Constructs a Trainer object.
	    \param p_source Source switch.
	    \param p_state Switch state at which trainer is active.
	    \param p_channel Input channel from which to read student input.*/
	Trainer(Switch p_source = Switch_None,
	        SwitchState p_state = SwitchState_Down,
	        InputChannel p_channel = InputChannel_None);
	
	/*! \brief Enables or disables this trainer channel.
	    \param p_enabled Whether to enable or disable.*/
	void setEnabled(bool p_enabled);
	
	/*! \brief Gets whether the trainer functionality is enabled.
	    \return True when enabled.*/
	bool isEnabled() const;
	
	/*! \brief Sets which control should be overridden.
	    \param p_destination Index in the input buffer to write to (control to override)
	    \note This will undo previous calls to setAsOutputSource.*/
	void setAsInputSource(Input p_destination);
	
	/*! \brief Gets the index in the input buffer to which results will be written.
	    \return Index in input buffer (control to override), Input_None when set as output source.*/
	Input getInputDestination() const;
	
	/*! \brief Sets which channel should be overridden.
	    \param p_destination Index in the output buffer to write to (channel to override)
	    \note This will undo previous calls to setAsInputSource.*/
	void setAsOutputSource(Output p_destination);
	
	/*! \brief Gets the index in the output buffer to which results will be written.
	    \return Index in output buffer (channel to override), Output_None when set as input source.*/
	Output getOutputDestination() const;
	
	/*! \brief Sets the rate at which student input is applied.
	    \param p_rate Rate at which student input is applied, range [0 - 100], default 100.
	    \warning Do NOT set rate lower than 100 to Input_THR or Output_THRn! */
	void setStudentRate(uint8_t p_rate);
	
	/*! \brief Gets the rate at which student input is applied.
	    \return Rate at which student input is applied, range [0 - 100]. */
	uint8_t getStudentRate() const;
	
	/*! \brief Sets the rate at which teacher input is applied.
	    \param p_rate Rate at which teacher input is applied, range [0 - 100], default 0.
	    \note Setting this higher than 0 allows the teacher to make corrections while holding the trainer switch. 
		\warning Don't use this for Input_THR or Output_THRn! */
	void setTeacherRate(uint8_t p_rate);
	
	/*! \brief Gets the rate at which teacher input is applied.
	    \return Rate at which teacher input is applied, range [0 - 100]. */
	uint8_t getTeacherRate() const;
	
	/*! \brief Applies p_student input to teacher input.
	    \param p_teacher Teacher input, range [-358 - 358]
		\param p_student Student input, range [-358 - 358]
		\param p_activeAndValid True when trainer switch is being held and student input is valid.
	    \return Result.*/
	int16_t apply(int16_t p_teacher, int16_t p_student, bool p_activeAndValid);
	
	/*! \brief Applies student input to existing teacher input.
		\param p_valid True when student input is valid.
	    \return Result.*/
	void apply(bool p_valid);
	
private:
	bool    m_enabled;     //!< Whether trainer port is enabled (for this channel)
	uint8_t m_destination; //!< Input or Output index
	uint8_t m_studentRate; //!< Rate at which student input is applied
	uint8_t m_teacherRate; //!< Rate at which teacher input is applied
};
/** \example trainer_example.pde
 * This is an example of how to use the Trainer class.
 */
 

} // namespace end

#endif // INC_RC_TRAINER_H
