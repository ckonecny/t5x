Version 0.4
- ADD: Debugging functions [#49]
- ADD: Calibration code for AIPin [#14]
- ADD: Servo speed [#50]
- ADD: Trainer port [#41]
- ADD: Input system for switches [#48]
- DEL: Removed DIPin and DAIPin, use BiStateSwitch and AnalogSwitch instead
- ADD: Offset [#7]
- ADD: Governor [#10]
- ADD: Input/Output system for channels [#52]
- ADD: Programmable mixes [#3]
- CHG: InputToInputMix derives from MixBase
- ADD: Swash to throttle mix [#9]
- ADD: Gimbal [#43]
- ADD: (Multi)Engine with idle, cut and rudder mix [#30]
- ADD: Programmable timer with Buzzer and Speaker [#53]
- ADD: Dead band for InputSwitch [#54]
- ADD: Rotary encoder [#39]
- ADD: Global pin change and external interrupt handlers

Version 0.3
- ADD: Landing gear support [#24]
- CHG: PPMOut may use any pin as output pin
- ADD: Wing type mixing [#25]
- ADD: Tail type mixing [#26]
- ADD: Flaps support [#27]
- ADD: Airbrake support [#29]
- BUG: PPMIn detects loss of signal [#34]
- ADD: Aileron differential [#35]
- ADD: FlycamOne support [#40]
- ADD: Smooth transitions on switches [#33]
- ADD: Throttle hold
- ADD: Input to input mix [#31]

Version 0.2
- BUG: Incorrect timings in PPMOut [#19]
- CHG: Use of Timer1 refactored for shared use [#18]
- CHG: Signal properties Center and Travel have been moved to utility functions [#20]
- ADD: PPMIn, PPM reader/decoder (trainer port) [#2]
- ADD: ServoIn, Servo signal reader/decoder [#16]
- ADD: ServoOut, Servo signal writer/encoder [#17]
- CHG: Remove all use of normalized values from Signal generating/reading code [#22]
- CHG: Timer1 code and interrupts moved to separate class [#23]

Version 0.1
- ADD: AIPin, analog input; trim, reverse, calibration
- ADD: Channel, transformations; end points, reverse, subtrim
- ADD: Curve, for throttle and pitch curves
- ADD: DIPin, digital input; reverse
- ADD: DualRates
- ADD: Expo, for exponential input
- ADD: Gyro, support AVCS and Normal gyros
- ADD: PPMOut, configurable PPM generator; channels, pulse length, servo center, servo travel, invert, pin
- ADD: Swashplate, support all common types and mixing