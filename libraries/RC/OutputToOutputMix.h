#ifndef INC_RC_OUTPUTTOOUTPUTMIX_H
#define INC_RC_OUTPUTTOOUTPUTMIX_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** OutputToOutputMix.h
** Generic output to output mix
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <MixBase.h>
#include <OutputProcessor.h>
#include <OutputModifier.h>


namespace rc
{

/*! 
 *  \brief     Class which mixes one output to another.
 *  \details   This class provides basic output to output mixing.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class OutputToOutputMix : public OutputProcessor, public OutputModifier, public MixBase
{
public:
	/*! \brief Constructs an OutputToOutputMix object
	    \param p_posMix The amount of mix to use when master is positive, range [-100 - 100].
	    \param p_negMix The amount of mix to use when master is negative, range [-100 - 100].
	    \param p_offset Master offset, range [-358 - 358].
	    \param p_source Output source: master.
	    \param p_index Index the mix should be applied to: slave.
	    \note When master = Output_None then an offset mix will be applied.*/
	OutputToOutputMix(int8_t p_posMix = 0,
	                  int8_t p_negMix = 0,
	                  int16_t p_offset = 0,
	                  Output p_source = Output_None,
	                  Output p_index = Output_None);
	
	
	/*! \brief Applies master-slave mix.
	    \param p_master Value that will be mixed, range [-358 - 358].
		\param p_slave Value that mix will be applied to, range [-358 - 358].
	    \return p_master mixed into p_slave, range [-358 - 358] (clamped).*/
	int16_t apply(int16_t p_master, int16_t p_slave) const;
	
	/*! \brief Applies offset mix.
		\param p_slave Value that mix will be applied to, range [-358 - 358].
	    \return p_slave - offset, range [-358 - 358] (clamped).*/
	int16_t applyOffset(int16_t p_slave) const;
	
	/*! \brief Applies mix to configured output.*/
	void apply() const;
	
private:

};
/** \example OutputToOutputMix_example.pde
 * This is an example of how to use the OutputToOutputMix class.
 */


} // namespace end


#endif // INC_RC_OUTPUTTOOUTPUTMIX_H
