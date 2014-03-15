t5x
===

An Open Source RC Transmitter implementation for Arduino 328p (nano) based on [Arduino RC Library](http://sourceforge.net/projects/arduinorclib/) and inspired by [Der-Frickler.net](http://der-frickler.net/technik/9xown#simu_tx) approach.
Project Details are described at [fpv-community.de](http://fpv-community.de/showthread.php?41460-Turnigy-5x-Arduino-RcLib-Hacking-Mainboard)

The software runs on an Arduino nano with any sort of transmitter hardware around basically.
There is a PCB for the [Turnigy 5x transmitter](https://www.hobbyking.com/hobbyking/store/__43854__Turnigy_5X_5Ch_Mini_Transmitter_and_Receiver_Mode_2_.html) that allows to directly connect the gimbals, two 3-pos switches, one 2-pos switch, a buzzer and a LED. There are also plans to add a sound-module lateron.
The board has also a voltage sensor for the transmitter battery as well as a level converter for Frsky Telemetry serial connection.


Instructions: 
- extract the archive's content into your Arduino Project folder, e.g. C:\Users\<your username>\Documents\Arduino 
- upload AnalogReadSerial to your T5x transmitter, open serial monitor with 9600baud and note down your individual calibration values for each analog input.
  note: telemetry uses the same serial port. so either only connect USB but do not power on the transmitter, or disconnect telemetry while doing this step.
- make your configurations in config.h, compile and enjoy!

have fun,
Christian Konecny (kornetto)


