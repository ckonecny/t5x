#ifndef INC_RC_INPUTTOINPUTMIX_H
#define INC_RC_INPUTTOINPUTMIX_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** InputToInputMix.h
** Generic input to input mix
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <InputProcessor.h>
#include <InputModifier.h>
#include <MixBase.h>


namespace rc
{

/*! 
 *  \brief     Class which mixes one input to another.
 *  \details   This class provides basic input to input mixing.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class InputToInputMix : public InputProcessor, public InputModifier, public MixBase
{
public:
	/*! \brief Constructs an InputToInputMix object
	    \param p_posMix The amount of mix to use when master is positive, range [-100 - 100].
	    \param p_negMix The amount of mix to use when master is negative, range [-100 - 100].
	    \param p_offset Master offset, range [-358 - 358].
	    \param p_source Input source: master.
	    \param p_index Index the mix should be applied to: slave.
	    \note When master = Input_None then an offset mix will be applied.*/
	InputToInputMix(int8_t p_posMix = 0,
	                int8_t p_negMix = 0,
	                int16_t p_offset = 0,
	                Input p_source = Input_None,
	                Input p_index = Input_None);
	
	/*! \brief Applies mix.
	    \param p_master Value that will be mixed, range [-358 - 358].
		\param p_slave Value that mix will be applied to, range [-358 - 358].
	    \return p_master mixed into p_slave, range [-358 - 358] (clamped).*/
	int16_t apply(int16_t p_master, int16_t p_slave) const;
	
	/*! \brief Applies offset mix.
		\param p_slave Value that mix will be applied to, range [-358 - 358].
	    \return p_slave - offset, range [-358 - 358] (clamped).*/
	int16_t applyOffset(int16_t p_slave) const;
	
	/*! \brief Applies mix to configured input.*/
	void apply() const;
	
private:
	
};
/** \example inputtoinputmix_example.pde
 * This is an example of how to use the InputToInputMix class.
 */


} // namespace end


#endif // INC_RC_INPUTTOINPUTMIX_H
