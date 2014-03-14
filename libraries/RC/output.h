#ifndef INC_RC_OUTPUT_H
#define INC_RC_OUTPUT_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** output.h
** Place where the output of various functions are stored
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

/*!
 *  \file output.h
 *  \brief Function output include file.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
*/

namespace rc
{
	enum Output //! Output index
	{
		Output_AIL1, //!< Aileron output 1, Main aileron
		Output_AIL2, //!< Aileron output 2, Main aileron
		Output_AIL3, //!< Aileron output 3, Chip aileron
		Output_AIL4, //!< Aileron output 4, Chip aileron
		Output_ELE1, //!< Elevator output 1/V-Tail 1, aileron 5 at ailevator
		Output_ELE2, //!< Elevator output 2/V-Tail 2, aileron 6 at ailevator
		Output_RUD1, //!< Rudder output 1/V-Tail 2/Winglet
		Output_RUD2, //!< Rudder output 2/V-Tail 1/Winglet
		Output_FLP1, //!< Flap output 1, Camber flap
		Output_FLP2, //!< Flap output 2, Camber flap
		Output_FLP3, //!< Flap output 3, Brake flap
		Output_FLP4, //!< Flap output 4, Brake flap
		Output_BRK1, //!< Airbrake output 1
		Output_BRK2, //!< Airbrake output 2
		Output_THR1, //!< Throttle output 1
		Output_THR2, //!< Throttle output 2
		Output_THR3, //!< Throttle output 3
		Output_THR4, //!< Throttle output 4
		Output_PIT,  //!< Pitch output
		Output_GYR1, //!< Gyro gain output 1 (Rudder)
		Output_GYR2, //!< Gyro gain output 2 (Aileron)
		Output_GYR3, //!< Gyro gain output 3 (Elevator)
		Output_GEAR, //!< Landing gear output
		Output_DOOR, //!< Landing gear doors output
		Output_GOV,  //!< Governor speed output
		
		Output_Count,
		Output_None //!< No output, special case
	};
	
	enum
	{
		Out_Max =  32767, //!< Maximum value and ignore endpoints
		Out_Min = -32768  //!< Minimum value and ignore endpoints
	};
	
	
	/*! \brief Sets output value for a certain output.
	    \param p_output Output to set value of.
	    \param p_value Value to set, range 140% [-358 - 358].*/
	void setOutput(Output p_output, int16_t p_value);
	
	/*! \brief Gets value of a certain output.
	    \param p_output Output to get value of.*/
	int16_t getOutput(Output p_output);
	
}

#endif // INC_RC_OUTPUT_H
