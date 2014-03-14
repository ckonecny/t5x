#ifndef INC_RC_GYRO_H
#define INC_RC_GYRO_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Gyro.h
** Gyro functionality
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
 *  \brief     Class to encapsulate Gyroscope functionality.
 *  \details   This class provides gyro gain encoding.
 *  \author    Daniel van den Ouden
 *  \date      Feb-2012
 *  \copyright Public Domain.
 */
class Gyro : public OutputSource
{
public:
	enum Type //! Type of gyro
	{
		Type_Normal, //!< Normal (Rate mode) gyro
		Type_AVCS,   //!< Heading hold gyro, also capable of rate mode
		
		Type_Count
	};
	
	enum Mode //! Mode in which the gyro is operating, only for AVCS type gyros
	{
		Mode_Normal, //!< Normal mode (Rate mode)
		Mode_AVCS,   //!< AVCS mode (Heading hold mode)
		
		Mode_Count
	};
	
	
	/*! \brief Constructs a Gyro object
	    \param p_output Output destination.*/
	Gyro(Output p_output = Output_None);
	
	/*! \brief Sets gyro type
	    \param p_type Gyro mode to set.*/
	void setType(Type p_type);
	
	/*! \brief Gets gyro type.
	    \return The gyro type currently set.*/
	Type getType() const;
	
	/*! \brief Sets gyro mode.
	    \param p_mode The mode to set.*/
	void setMode(Mode p_mode);
	
	/*! \brief Gets gyro mode.
	    \return The gyro mode currently set.*/
	Mode getMode() const;
	
	/*! \brief Sets gyro gain.
	    \param p_gain The gain to set, range [0 - 100].*/
	void setGain(int8_t p_gain);
	
	/*! \brief Gets gyro gain.
	    \return The gyro gain currently set, range [0 - 100].*/
	int8_t getGain() const;
	
	/*! \brief Assignment operator, sets gain.
	    \param p_rhs The gain to set, range [0 - 100].
	    \return Reference to this object.*/
	Gyro& operator = (int8_t p_rhs);
	
	/*! \brief Cast operator, casts object to int8_t.
	    \return Current gain, range [0 - 100].*/
	operator int8_t () const;
	
	/*! \brief Applies gyro.
	    \return Normalized channel value, range [-256 - 256].*/
	int16_t apply() const;
	
private:
	Type   m_type;   //!< Gyro type
	Mode   m_mode;   //!< Mode of operation (in case of AVCS type)
	int8_t m_gain;   //!< Gain [0 - 100]
};
/** \example gyro_example.pde
 * This is an example of how to use the Gyro class.
 */


} // namespace end

#endif // INC_RC_GYRO_H
