t5x
===

An Open Source RC Transmitter implementation for Arduino 328p (nano) based on [Arduino RC Library](http://sourceforge.net/projects/arduinorclib/) and inspired by [Der-Frickler.net](http://der-frickler.net/technik/9xown#simu_tx) approach.
Project Details to be found here: http://fpv-community.de/showthread.php?41460-Turnigy-5x-Arduino-RcLib-Hacking-Mainboard

Instructions: 
- extract the archive's content into your Arduino Project folder, e.g. C:\Users\<your username>\Documents\Arduino 
- upload AnalogReadSerial to your T5x transmitter, open serial monitor with 9600baud and note down your individual calibration values for each analog input.
  note: telemetry uses the same serial port. so either only connect USB but do not power on the transmitter, or disconnect telemetry while doing this step.
- make your configurations in config.h, compile and enjoy!

have fun,
Christian Konecny (kornetto)


