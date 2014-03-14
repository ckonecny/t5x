/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** trainer_example.pde
** Demonstrate Trainer port functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <AIPin.h>
#include <BiStateSwitch.h>
#include <PPMIn.h>
#include <Timer1.h>
#include <Trainer.h>
#include <util.h>


#define CHANNELS 4


// PPM related variables

rc::PPMIn g_PPMIn;


// Hardware input

rc::AIPin g_pins[CHANNELS] =
{
	rc::AIPin(A0, rc::Input_AIL),
	rc::AIPin(A1, rc::Input_ELE),
	rc::AIPin(A2, rc::Input_THR),
	rc::AIPin(A3, rc::Input_RUD)
};

rc::BiStateSwitch g_switch(3, rc::Switch_A); // use pin 3 as trainer switch and store the result as Switch A


// Trainer objects

rc::Trainer g_trainer[CHANNELS] = // Trainer object for every channel
{
	rc::Trainer(rc::Switch_A, rc::SwitchState_Down, rc::InputChannel_1), // We can specify a switch and state for which the
	rc::Trainer(rc::Switch_A, rc::SwitchState_Down, rc::InputChannel_2), // student input should be used
	rc::Trainer(rc::Switch_A, rc::SwitchState_Down, rc::InputChannel_3), // in this case we use Switch A in the Down position
	rc::Trainer(rc::Switch_A, rc::SwitchState_Down, rc::InputChannel_4)  // We could use a different switch for some functions, but we won't
};


void setup()
{
	// set up trainer data, we handle incoming trainer data as control input
	// this way we can still use things like expo, curves, etc
	// it's also possible to directly use trainer input as channel output
	// in that case use setAsOutputSource
	g_trainer[0].setAsInputSource(rc::Input_AIL);
	g_trainer[1].setAsInputSource(rc::Input_ELE);
	g_trainer[2].setAsInputSource(rc::Input_THR);
	g_trainer[3].setAsInputSource(rc::Input_RUD);
	
	// let's say we want the student to only be able to control aileron and elevator,
	// then we only enable those trainer objects and leave the rest disabled
	g_trainer[0].setEnabled(true);
	g_trainer[1].setEnabled(true);
	
	// and let's dumb down the controls for our poor student down a bit
	g_trainer[0].setStudentRate(75); // only allow 75% servo throw
	g_trainer[1].setStudentRate(75);
	
	// As a teacher, we might want to be able to make some corrections without having
	// to let go of the trainer switch, in that case we can specify how much of the
	// teacher's input should be mixed into the final result
	g_trainer[0].setTeacherRate(100); // full teacher input added to signal
	g_trainer[0].setTeacherRate(100);
	
	// Quick but important note:
	// Do NOT set rates on the throttle input or throttle channels!
	// Since student and teacher input is added to eachother during mixing
	// this may have some unexpected and unwanted results for throttle!
	
	// Initialize timer1, this is required for all features that use Timer1
	// (PPMIn/PPMOut/ServoIn/ServoOut)
	rc::Timer1::init();
	
	// We use pin 8 as PPM input pin
	g_PPMIn.setPin(8);

	// set a timeout (default 500 milliseconds)
	g_PPMIn.setTimeout(1000);
	
	// start listening
	g_PPMIn.start();
}


void loop()
{
	// read teacher input
	for (uint8_t i = 0; i < CHANNELS; ++i)
	{
		g_pins[i].read(); // will write to rc::Input_xxx
	}
	g_switch.read(); // will write to rc::Switch_A
	
	// update incoming values
	g_PPMIn.update();
	
	// check if we have a stable student signal
	bool validStudent = g_PPMIn.isStable();
	
	// apply student input
	for (uint8_t i = 0; i < CHANNELS; ++i)
	{
		// note that the state of the switch will be read from rc::Switch_A
		// teacher input will be read from rc::Input_xxx
		// student input will be read from rc::InputChannel_N
		g_trainer[i].apply(validStudent);
	}
	
	// Done! At this point the results are available in the global input buffer
	// and can be used for further processing.
	// see:
	// rc::getInput(rc::Input_AIL)
	// rc::getInput(rc::Input_ELE)
	// rc::getInput(rc::Input_THR)
	// rc::getInput(rc::Input_RUD)
}
