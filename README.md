t5x
===

An Arduino based Open Source RC Transmitter


T5x Version 1.2:

implementation for Arduino 328p (nano) based on Arduino RC Library and inspired by Der-Frickler.net's approach.
Project Details to be found here: http://fpv-community.de/showthread.php?41460-Turnigy-5x-Arduino-RcLib-Hacking-Mainboard

Instructions: 
- extract the archive's content into your Arduino Project folder, e.g. C:\Users\<your username>\Documents\Arduino 
- upload AnalogReadSerial to your T5x transmitter, open serial monitor with 9600baud and note down your individual calibration values for each analog input.
  note: telemetry uses the same serial port. so either only connect USB but do not power on the transmitter, or disconnect telemetry while doing this step.
- make your configurations in config.h, compile and enjoy!

have fun,
Christian Konecny (kornetto)



---------------------------------------------
Version History:

12-03-2014:
1.0 reworked sketch from frickler
    added channel 7 and 8
    removed throttle hold
    read switch state during setup() to find active profile
    buzzer beeps the selected profile id
    telemetry V_A1 and V_TX works successfully tested
    applying Expo/DR from within nested objects does not seem to work

12-03-2014:
1.1 reworked the profiles

13-03-2014:
1.2 moving most configuration relevant parts to config.h
    reworking DualRate & Expo, Calibration Settings, transmitter voltage warning thresholds
    known issues: - RSSI Telemetry not successfully tested
                  - Flight Timer not implemented yet
