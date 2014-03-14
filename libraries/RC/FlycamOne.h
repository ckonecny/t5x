#ifndef INC_RC_FLYCAMONE_H
#define INC_RC_FLYCAMONE_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** FlycamOne.h
** Class to control FlycamOne eco V2 on board camera
** See also: http://www.flycamone.com/
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <OutputSource.h>


namespace rc
{

/*! 
 *  \brief     Class to control FlycamOne eco V2 on board camera.
 *  \details   This class provides control functions for an on board camera.
 *  \see       http://www.flycamone.com/
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class FlycamOne : public OutputSource
{
public:
	enum CamMode        //! Camera operating mode
	{
		CamMode_Video,  //!< Video recording
		CamMode_Serial, //!< Serial photography
		CamMode_Photo,  //!< Single photo
		
		CamMode_Count
	};
	
	enum SensorMode        //! Sensor mode
	{
		SensorMode_Normal,  //!< Normally mounted
		SensorMode_Flipped, //!< Flipped 180 degrees (mounted upside down)
		
		SensorMode_Count
	};
	
	/*! \brief Constructs a FlycamOne object.
	    \param p_destination Output destination.*/
	FlycamOne(Output p_destination = Output_None);
	
	/*! \brief Sets Camera mode
	    \param p_mode Camera mode to set.
	    \return false when busy or recording, true on success.*/
	bool setCamMode(CamMode p_mode);
	
	/*! \brief Gets Camera mode.
	    \return The Camera mode currently set.*/
	CamMode getCamMode() const;
	
	/*! \brief Sets Sensor mode.
	    \param p_mode Sensor mode to set.
		\return false when busy or recording, true on success.*/
	bool setSensorMode(SensorMode p_mode);
	
	/*! \brief Gets Sensor mode.
	    \return The Sensor mode currently set.*/
	SensorMode getSensorMode() const;
	
	/*! \brief Starts recording.
	    \return Whether it successfully started recording.
	    \note Only works when cam mode is CamMode_Video or CamMode_Serial
	          and not already recording and not busy.*/
	bool startRecording();
	
	/*! \brief Stops recording.
	    \return Whether it successfully stopped recording.
	    \note Only works when cam mode is CamMode_Video or CamMode_Serial
	          and while recording and not busy.*/
	bool stopRecording();
	
	/*! \brief Checks if it's currently recording.
	    \return Whether it is currently recording.*/
	bool isRecording() const;
	
	/*! \brief Takes a photo.
	    \return Whether it successfully took a photo.
	    \note Only works when cam mode is CamMode_Photo.*/
	bool takePhoto();
	
	/*! \brief Checks if it's currently sending a command.
	    \return Whether it's sending a command.
	    \note While a command is being sent, no other commands can be issued.*/
	bool isBusy() const;
	
	/*! \brief Updates internal states.
	    \return Normalized channel value, range [-256 - 256].
	    \note Call this regularly.*/
	int16_t update();
	
private:
	enum Command //! Internal commands
	{
		Command_Idle,               //!< Do nothing
		Command_ChangeCamMode,      //!< Change camera mode
		Command_ChangeCamModeTwice, //!< Change camera mode twice
		Command_ChangeSensorMode,   //!< Flip sensor
		Command_StartStop           //!< Start/Stop recording/Take photo
	};
	
	enum
	{
		Timing_CamMode    = 3250,  //!< 3 seconds and a bit
		Timing_SensorMode = 10250, //!< 10 seconds and a bit
		Timing_StartStop  = 250,   //!< a bit of a second
		Timing_CoolDown   = 250    //!< a bit of a second
	};
	
	enum
	{
		Value_Low  = -256,
		Value_High =  256
	};
	
	void setCommand(Command p_command);
	Command getChangeCamCommand(CamMode p_mode) const;
	void handleChangeCam();
	void handleChangeSensor();
	void handleStartStop();
	
	CamMode    m_camMode;    //!< Camera operating mode.
	SensorMode m_sensorMode; //!< Sensor mode.
	bool       m_recording;  //!< Whether it's recording.
	
	Command  m_command;   //!< Current command
	uint16_t m_startTime; //!< Time at which the command started
	uint16_t m_duration;  //!< Duration of command in milliseconds
	bool     m_coolDown;  //!< In cooldown period after command
	
	int16_t m_value; //!< Normalized channel value.
};
/** \example flycamone_example.pde
 * This is an example of how to use the FlycamOne class.
 */
 

} // namespace end

#endif // INC_RC_FLYCAMONE_H
