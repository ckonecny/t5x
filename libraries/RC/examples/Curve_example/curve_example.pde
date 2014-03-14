/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** curve_example.pde
** Demonstrate Curve functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Curve.h>


rc::Curve g_curve;

void setup()
{
	// by default we have a linear curve from -256 to 256
	// it looks like -256, -192, -128, -64, 0, 64, 128, 192, 256
	// for this example we create a V shaped curve,
	// for stunt mode throttle on a heli
	g_curve[0] = 256;
	g_curve[1] = 192;
	g_curve[2] = 128;
	g_curve[3] = 64;
	// in this case we don't need to set the rest of the values since they're
	// already correct, so our final curve looks like
	// 256, 192, 128, 64, 0, 64, 128, 192, 256
	// we could also load the default V curve (which is identical) like this:
	// g_curve.loadCurve(rc::Curve::DefaultCurve_V);
	
	// it is also possible to use Curves in combination with the input system
	// you can specify a source and destination (which may be the same)
	// g_curve.setSource(rc::Input_AIL);
	// g_curve.setDestination(rc::Input_AIL);
	// you can also specify the source and destination as a constructor parameter
	
	// In case we want to make some temporary adjustments to our curve, we can set
	// some trims on the curve.
	// There are three trims: low, center and high
	// The low trim affects the four lowest curve points (0 - 3), and affects point 0 the most
	// The center trim affects the seven center curve points (1 - 7), and affects point 4 the most
	// The high trim affects the four highest curve points (5 - 8), and affects point 8 the most
	// When setting all trims to the same number, the entire curve is moved up or down by that amount
	//
	// For now let's say we want to move the center of our curve up by a small amount
	// because of weather conditions for example
	g_curve.setCenterTrim(16);
	// this would make our final curve
	// 256, 192, 128,  64,   0,  64, 128, 192, 256
	//  +0   +4   +8  +12  +16  +12   +8   +4   +0  // the center point is affected the most
	// 256, 196, 136,  76,  16,  76, 136, 196, 256
	//
	// the results for low trim would have been:
	// 256, 192, 128,  64,   0,  64, 128, 192, 256
	// +16, +12,  +8,  +4,  +0,  +0,  +0,  +0,  +0
	// 256, 204, 136,  68,   0,  64, 128, 192, 256
	//
	// the results for high trim would have been:
	// 256, 192, 128,  64,   0,  64, 128, 192, 256
	//  +0,  +0,  +0,  +0,  +0,  +4,  +8, +12, +16
	// 256, 192, 128,  64,   0,  68, 136, 204, 256
	//
	// the results for all trim would have been:
	// 256, 192, 128,  64,   0,  64, 128, 192, 256
	// +16, +16, +16, +16, +16, +16, +16, +16, +16
	// 256, 208, 144,  80,  16,  80, 144, 208, 256
	//
	// as you can see, values won't go higher than 256 (or lower than -256)
}

void loop()
{
	// we use A0 as input pin, we map raw input values (0 - 1024) to normalized
	// values (-256 - 256)
	int16_t normalized = map(analogRead(A0), 0, 1024, -256, 256);
	
	// and apply the curve
	normalized = g_curve.apply(normalized);
	
	// if you had used the input system you would not have needed to specify any parameters
	// g_curve.apply();
	// will get it's input from the input system and write it back to the input system
	// it'll still return the result though, in case you want it or didn't specify a destination
	
	// we can then use the transformed value for further modification
	// or we can transmit it using the PPMOut class
}
