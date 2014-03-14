#ifndef INC_RC_PLANEMODEL_H
#define INC_RC_PLANEMODEL_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** PlaneModel.h
** Wing types, rudder types and tail types.
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <output.h>


namespace rc
{

/*! 
 *  \brief     Class to encapsulate mixing for various plane models.
 *  \details   This class provides mixing for all sorts of plane models.
 *  \author    Daniel van den Ouden
 *  \date      Oct-2012
 *  \copyright Public Domain.
 */
class PlaneModel
{
public:
	enum WingType //! Type of wings
	{
		WingType_Tailed,   //!< Tailed setup with separate control surfaces for elevator, uses at least AIL1
		WingType_Tailless, //!< Tailless setup/Flying wing, uses elevon for combined aileron/elevator action, uses at least AIL1+2
		
		WingType_Count
	};
	
	enum TailType //! Type of tails, only for tailed wings
	{
		TailType_Normal,    //!< Normal tail with servo for elevator and rudder, uses ELE1 and RUD1
		TailType_VTail,     //!< V-Tail/Butterfly tail/Ruddervators setup with two servos for combined elevator and rudder, uses ELE1+RUD2 or RUD1+ELE2 (all valid)
		TailType_Ailevator, //!< Ailevator, three servos, one for tail, two for combined elevator and aileron. Uses ELE1+2 and RUD1
		
		TailType_Count
	};
	
	enum RudderType //! Type of rudder, only for tailless wings
	{
		RudderType_None,    //!< No rudder available
		RudderType_Normal,  //!< Single servo for rudder, uses RUD1
		RudderType_Winglet, //!< Dual servo for winglets (rudders on wingtips), uses RUD1+2
		
		RudderType_Count
	};
	
	enum AileronCount //! Number of Aileron servos
	{
		AileronCount_1 = 1, //!< Single aileron servo, not in combination with tailless wings or flaps, uses only AIL1
		AileronCount_2 = 2, //!< Dual aileron servos, uses AIL1+2
		AileronCount_4 = 4  //!< Four aileron servos, uses AIL1+2+3+4
	};
	
	enum FlapCount //! Number of Flap servos
	{
		FlapCount_0 = 0, //!< No flaps
		FlapCount_1 = 1, //!< Single Flap servo (single camber), uses FLP1
		FlapCount_2 = 2, //!< Dual Flap servos  (dual camber), uses FLP1+2
		FlapCount_4 = 4  //!< Four Flap servos  (dual camber + dual brake), uses FLP1+2+3+4
	};
	
	enum BrakeCount //! Number of airbrake servos
	{
		BrakeCount_0 = 0, //!< No airbrake servos
		BrakeCount_1 = 1, //!< Single airbrake servo, uses BRK1
		BrakeCount_2 = 2  //!< Dual airbrake servos, uses BRK1+2
	};
	
	/*! \brief Constructs a PlaneModel object*/
	PlaneModel();
	
	/*! \brief Sets wing type
	    \param p_type Wing type to set.*/
	void setWingType(WingType p_type);
	
	/*! \brief Gets wing type.
	    \return The wing type currently set.*/
	WingType getWingType() const;
	
	/*! \brief Sets tail type
	    \param p_type Tail type to set.*/
	void setTailType(TailType p_type);
	
	/*! \brief Gets tail type.
	    \return The tail type currently set.*/
	TailType getTailType() const;
	
	/*! \brief Sets rudder type
	    \param p_type Rudder type to set.*/
	void setRudderType(RudderType p_type);
	
	/*! \brief Gets rudder type.
	    \return The rudder type currently set.*/
	RudderType getRudderType() const;
	
	/*! \brief Sets the number of aileron servos
	    \param p_count Number of aileron servos.*/
	void setAileronCount(AileronCount p_count);
	
	/*! \brief Gets number of aileron servos.
	    \return The number of aileron servos.*/
	AileronCount getAileronCount() const;
	
	/*! \brief Sets the number of flap servos
	    \param p_count Number of flap servos.*/
	void setFlapCount(FlapCount p_count);
	
	/*! \brief Gets number of flap servos.
	    \return The number of flap servos.*/
	FlapCount getFlapCount() const;
	
	/*! \brief Sets the number of brake servos
	    \param p_count Number of brake servos.*/
	void setBrakeCount(BrakeCount p_count);
	
	/*! \brief Gets number of brake servos.
	    \return The number of brake servos.*/
	BrakeCount getBrakeCount() const;
	
	/*! \brief Sets the amount of aileron differential
	    \param p_rate The amount of aileron differential [-100 - 100].
	    \note Affects Aileron and Elevon, NOT Ailevator.*/
	void setAileronDifferential(int8_t p_rate);
	
	/*! \brief Gets the amount of aileron differential
	    \return The amount of aileron differential [-100 - 100].
	    \note Affects Aileron and Elevon, NOT Ailevator.*/
	int8_t getAileronDifferential() const;
	
	/*! \brief Sets the amount of winglet differential
	    \param p_rate The amount of winglet differential [-100 - 100].
	    \note Affects only models with RudderType_Winglet.*/
	void setWingletDifferential(int8_t p_rate);
	
	/*! \brief Gets the amount of winglet differential
	    \return The amount of winglet differential [-100 - 100].
	    \note Only valid for models with RudderType_Winglet.*/
	int8_t getWingletDifferential() const;
	
	/*! \brief Sets the amount of aileron mix for elevon
	    \param p_rate The amount of aileron to mix into the elevators [-100 - 100].
	    \note Only used in combination with WingType_Tailless.*/
	void setElevonAileronMix(int8_t p_rate);
	
	/*! \brief Gets the amount of aileron mix for elevon
	    \return The amount of aileron to mix into the elevators [-100 - 100].
	    \note Only used in combination with WingType_Tailless.*/
	int8_t getElevonAileronMix() const;
	
	/*! \brief Sets the amount of elevator mix for elevon
	    \param p_rate The amount of elevator to mix into the elevators [-100 - 100].
	    \note Only used in combination with WingType_Tailless.*/
	void setElevonElevatorMix(int8_t p_rate);
	
	/*! \brief Gets the amount of elevator mix for elevon
	    \return The amount of elevator to mix into the elevators [-100 - 100].
	    \note Only used in combination with WingType_Tailless.*/
	int8_t getElevonElevatorMix() const;
	
	/*! \brief Sets the amount of aileron mix for ailevator
	    \param p_rate The amount of aileron to mix into the elevators [-100 - 100].
	    \note Only used in combination with TailType_Ailevator.*/
	void setAilevatorMix(int8_t p_rate);
	
	/*! \brief Gets the amount of aileron mix for ailevator
	    \return The amount of aileron to mix into the elevators [-100 - 100].
	    \note Only used in combination with TailType_Ailevator.*/
	int8_t getAilevatorMix() const;
	
	/*! \brief Sets the amount of aileron differential for ailevator
	    \param p_rate The amount of aileron differential for the elevators [-100 - 100].
	    \note Only used in combination with TailType_Ailevator.*/
	void setAilevatorDifferential(int8_t p_rate);
	
	/*! \brief Gets the amount of aileron differential for ailevator
	    \return The amount of aileron differential for the elevators [-100 - 100].
	    \note Only used in combination with TailType_Ailevator.*/
	int8_t getAilevatorDifferential() const;
	
	/*! \brief Sets the amount of elevator mix for V-Tail
	    \param p_rate The amount of elevator to mix into the rudders [-100 - 100].
	    \note Only used in combination with WingType_VTail.*/
	void setVTailElevatorMix(int8_t p_rate);
	
	/*! \brief Gets the amount of elevator mix for V-Tail
	    \return The amount of elevator to mix into the rudders [-100 - 100].
	    \note Only used in combination with WingType_VTail.*/
	int8_t getVTailElevatorMix() const;
	
	/*! \brief Sets the amount of rudder mix for V-Tail
	    \param p_rate The amount of rudder to mix into the rudders [-100 - 100].
	    \note Only used in combination with WingType_VTail.*/
	void setVTailRudderMix(int8_t p_rate);
	
	/*! \brief Gets the amount of rudder mix for V-Tail
	    \return The amount of rudder to mix into the rudders [-100 - 100].
	    \note Only used in combination with WingType_VTail.*/
	int8_t getVTailRudderMix() const;
	
	/*! \brief Applies input to the servos.
	    \param p_ail Aileron input, range 140% [-358 - 358].
	    \param p_ele Elevator input, range 140% [-358 - 358].
	    \param p_rud Rudder input, range 140% [-358 - 358].
	    \param p_flp Camber (flap) input, range 140% [-358 - 358].
	    \param p_brk Airbrake (+ flap) input, range 140% [-358 - 358].*/
	void apply(int16_t p_ail,
	           int16_t p_ele,
	           int16_t p_rud,
	           int16_t p_flp,
	           int16_t p_brk);
	
	/*! \brief Applies input from input system to the servos.*/
	void apply();
	
private:
	void applyTail(int16_t p_ail, int16_t p_ele, int16_t p_rud);
	void applyRudder(int16_t p_rud);
	void applyFlaps(int16_t p_flp, int16_t p_brk);
	void applyBrakes(int16_t p_brk);
	
	int16_t applyDiff(int16_t p_input, int8_t p_diff) const;
	
	WingType     m_wing;     //!< Wing type
	TailType     m_tail;     //!< Tail type
	RudderType   m_rudder;   //!< Rudder type
	AileronCount m_ailerons; //!< Number of aileron servos
	FlapCount    m_flaps;    //!< Number of flap servos
	BrakeCount   m_brakes;   //!< Number of airbrake servos
	
	int8_t m_ailDiff;     //!< Amount of aileron differential
	int8_t m_wingletDiff; //!< Amount of winglet differential
	
	int8_t m_elevonAil; //!< Amount of aileron mixing in ailevon (tailless wings)
	int8_t m_elevonEle; //!< Amount of elevator mixing in ailevon (tailless wings)
	
	int8_t m_ailevator;     //!< Amount of aileron to elevator mix
	int8_t m_ailevatorDiff; //!< Amount of aileron differential for ailevator
	
	int8_t m_vtailEle; //!< Amount of elevator mix in V-Tail
	int8_t m_vtailRud; //!< Amount of rudder mix in V-Tail
};

/** \example planemodel_example.pde
 * This is an example of how to use the PlaneModel class.
 */


} // namespace end

#endif // INC_RC_PLANEMODEL_H
