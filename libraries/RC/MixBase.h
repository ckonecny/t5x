#ifndef INC_RC_MIXBASE_H
#define INC_RC_MIXBASE_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** MixBase.h
** Base class for normalized mixes
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>


namespace rc
{

/*! 
 *  \brief     Base class for normalized mixes.
 *  \details   This class provides basic mixing in the normalized domain.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class MixBase
{
public:
	/*! \brief Sets the amount of positive mix.
	    \param p_mix The amount of mix to use when the master is positive, range [-100 - 100].*/
	void setPosMix(int8_t p_mix);
	
	/*! \brief Gets the amount of positive mix.
	    \return The current amount of mix to use when the master is positive, range [-100 - 100].*/
	int8_t getPosMix() const;
	
	/*! \brief Sets the amount of negative mix.
	    \param p_mix The amount of mix to use when the master is negative, range [-100 - 100].*/
	void setNegMix(int8_t p_mix);
	
	/*! \brief Gets the amount of negative mix.
	    \return The current amount of mix to use when the master is negative, range [-100 - 100].*/
	int8_t getNegMix() const;
	
	/*! \brief Sets the master offset.
	    \param p_offset Offset for master input, range [-358 - 358].*/
	void setOffset(int16_t p_offset);
	
	/*! \brief Gets the master offset.
	    \return Master offset, range [-358 - 358].*/
	int16_t getOffset() const;
	
protected:
	/*! \brief Constructs an Mix object
	    \param p_posMix The amount of mix to use when master is positive, range [-100 - 100].
	    \param p_negMix The amount of mix to use when master is negative, range [-100 - 100].
	    \param p_offset Master offset, determines center point for master, range [-358 - 358].*/
	MixBase(int8_t p_posMix = 0,
	        int8_t p_negMix = 0,
	        int16_t p_offset= 0);
	
	/*! \brief Applies master-slave mix.
	    \param p_master Value that will be mixed, range [-358 - 358].
		\param p_slave Value that mix will be applied to, range [-358 - 358].
	    \return p_master mixed into p_slave, range [-358 - 358] (clamped).*/
	int16_t applyMix(int16_t p_master, int16_t p_slave) const;
	
	/*! \brief Applies offset mix.
	    \param p_slave Value that offset will be applied to, range [-358 - 358].
	    \return p_slave - offset, range [-358 - 358] (clamped).*/
	int16_t applyOffsetMix(int16_t p_slave) const;
	
	int8_t  m_posMix; //!< Amount of positive mix [-100 - 100].
	int8_t  m_negMix; //!< Amount of negative mix [-100 - 100].
	int16_t m_offset; //!< Master offset
};


} // namespace end


#endif // INC_RC_MIXBASE_H
