#ifndef INC_RC_AIPINCALIBRATOR_H
#define INC_RC_AIPINCALIBRATOR_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** AIPinCalibrator.h
** Class for calibrating an AIPin
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
 *  \brief     Class for calibrating an AIPin
 *  \details   This class provides functionality to calibrate an AIPin object.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class AIPinCalibrator
{
public:
	/*! \brief Constructs an AIPinCalibrator object.
	    \param p_target The AIPin to calibrate.*/
	AIPinCalibrator(AIPin* p_target = 0);
	
	/*! \brief Sets the AIPin to calibrate.
	    \param p_pin The AIPin to calibrate.*/
	void setAIPin(AIPin* p_pin);
	
	/*! \brief Gets the AIPin currently calibrating.
	    \return The current AIPin.*/
	AIPin* getAIPin() const;
	
	/*! \brief Starts the calibration process.
	    \note Assumes the pin is in center position at start.*/
	void start();
	
	/*! \brief Updates the calibration process.
	    \note Call this plenty of times.*/
	void update();
	
	/*! \brief Indicates that the calibration process has been completed.
	    \return Whether calibration has been completed.
	    \note Only call stop() after this function returns true.*/
	bool isDone() const;
	
	/*! \brief Stops the calibration process.
	    \note Assumes the pin is in center position again.
	    \warning This function will do nothing as long as isDone does not return true
	    \see rc::AIPin::setCalibration */
	void stop();
	
private:
	enum
	{
		Minimum_Band   = 256, //!< Minimum difference between min and max
		Minimum_Center = 16,  //!< Range around center to stay in for completing calibration
		Center_Time    = 3000 //!< Number of milliseconds to stay in center before completing calibration
	};
	
	uint16_t read(); //!< Internal read function.
	
	AIPin* m_pin; //!< Target AIPin.
	
	bool     m_active; //!< Whether start has been called.
	uint16_t m_min;    //!< Lowest value measured.
	uint16_t m_max;    //!< Highest value measured.
	uint16_t m_center; //!< Center value.
	uint16_t m_start;  //!< Time at which center calibration started
	
};
/** \example aipincalibrator_example.pde
 * This is an example of how to use the AIPinCalibrator class.
 */


} // namespace end

#endif // INC_RC_AIPINCALIBRATOR_H
