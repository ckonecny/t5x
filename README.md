t5x
===

An Open Source RC Transmitter implementation for Arduino 328p (nano) based on [Arduino RC Library](http://sourceforge.net/projects/arduinorclib/) and inspired by [Frickler's SimuTx](http://der-frickler.net/technik/9xown#simu_tx) approach.
Project Details are described at [fpv-community.de](http://fpv-community.de/showthread.php?41460-Turnigy-5x-Arduino-RcLib-Hacking-Mainboard) as well as on the [project's wiki](https://github.com/ckonecny/t5x/wiki)

The software runs on an Arduino nano with any sort of transmitter hardware around basically.
There is a PCB for the [Turnigy 5x transmitter](https://www.hobbyking.com/hobbyking/store/__43854__Turnigy_5X_5Ch_Mini_Transmitter_and_Receiver_Mode_2_.html) that allows to directly connect the gimbals, two 3-pos switches, one 2-pos switch, a buzzer and a LED. There are also plans to add a sound-module lateron.
The board has also a voltage sensor for the transmitter battery as well as a level converter for Frsky Telemetry serial connection.


Instructions: 
- extract the archive's content into your Arduino Project folder, e.g. C:\Users\<your username>\Documents\Arduino 
- compile and upload to your transmitter
- connect with [t5x configurator](https://github.com/ckonecny/t5x_configurator) while the transmitter is turned off
- do your configuration. hit apply button to see changes immediatly, press save button to save the settings into EEPROM
- enjoy your T5x.
- HINT: If you want - there is no need to - you can comment out after the first successful boot of the t5x in config.h the line
#define T5X_CONDITIONAL_INITIALIZE_EEPROM 
compile again and upload to the transmitter. doing that way results in smaller ROM-file and more RAM available.
- if you have problems with the configurator, or just want a simple setup with all that bells and whistles, config.h allows to disable EEPROM handling by commenting out the line
#define T5X_USE_EEPROM
when doing that, configuration can be done hardcoded via TxDeviceProperties.h and Profile.h by modifying the default structures for both.


have fun & great greetings from vienna, austria!
Christian Konecny (alias kornetto)


