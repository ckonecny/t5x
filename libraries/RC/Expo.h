#ifndef INC_RC_EXPO_H
#define INC_RC_EXPO_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Expo.h
** Exponential functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <InputModifier.h>


namespace rc
{

/*! 
 *  \brief     Class to encapsulate Expo functionality.
 *  \details   This class provides exponential transformation.
 *  \author    Daniel van den Ouden
 *  \date      Feb-2012
 *  \copyright Public Domain.
 */
class Expo : public InputModifier
{
public:
	/*! \brief Constructs an Expo object
	    \param p_expo The expo to set, range [-100 - 100].
	    \param p_index Input index to use for input and output.*/
	Expo(int8_t p_expo = 0, Input p_index = Input_None);
	
	
	/*! \brief Sets the expo.
	    \param p_expo The expo to set, range [-100 - 100].*/
	void set(int8_t p_expo);
	
	/*! \brief Gets expo.
	    \return The current expo, range [-100 - 100].*/
	int8_t get() const;
	
	/*! \brief Copy assignment operator.
	    \param p_rhs Object to copy.
	    \return Reference to this object.*/
	Expo& operator = (const Expo& p_rhs);
	
	/*! \brief Assignment operator, sets expo.
	    \param p_rhs The expo to set, range [-100 - 100].
	    \return Reference to this object.*/
	Expo& operator = (int8_t p_rhs);
	
	/*! \brief Cast operator, casts object to int8_t.
	    \return Current expo, range [-100 - 100].*/
	operator int8_t () const;
	
	/*! \brief Reference operator, allow direct access to member through pointer for flexible get/set.
	    \return Pointer to expo.*/
	int8_t* operator &();
	
	/*! \brief Reference operator, allow direct access to member through pointer for flexible get/set.
	    \return Pointer to expo.*/
	const int8_t* operator &() const;
	
	/*! \brief Applies expo.
	    \param p_value Source value to apply expo to, range [-256 - 256].
	    \return expo applied to p_value.*/
	int16_t apply(int16_t p_value) const;
	
	/*! \brief Applies expo to the set input.*/
	void apply() const;
	
private:
	int8_t m_expo;
	
};
/** \example expo_example.pde
 * This is an example of how to use the Expo class.
 */
 

} // namespace end

#endif // INC_RC_EXPO_H
