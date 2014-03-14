/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** gimbal_example.pde
** Demonstrate gimbal functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Gimbal.h>

// We create a gimbal by specifying the horizontal and vertical hardware pin
// we also tell it whether it's the left (true) or right (false) gimbal
// and we can specify a layout mode which is used to determine which function
// each pin represents.
rc::Gimbal g_left(A0, A1, true, rc::Gimbal::Mode_2);
rc::Gimbal g_right(A2, A3, false, rc::Gimbal::Mode_2);

void setup()
{
	// each gimbal uses two AIPin object which can be get through getHorizontal and getVertical
	// so if you want to change the calibration you can simply do:
	g_left.getHorizontal().setCalibration(100, 520, 940);
	
	// if you want to change the mode at runtime use
	g_left.setMode(rc::Gimbal::Mode_1);
	g_right.setMode(rc::Gimbal::Mode_1);
	// just make sure that you update both gimbals
}

void loop()
{
	// read the gimbals
	g_left.read();
	g_right.read();
	
	// results are placed in rc::Input_AIL, rc::Input_ELE, rc::input_THR and rc::Input_RUD
	// and can be fetched with rc::getInput(rc::Input_XXX);
}
