#ifndef CONFIG_H
#define CONFIG_H

// if enabled, data are stored in EEPROM and intended to be modified via external application
// if disabled, data are defined "hardcoded" in Profile.h and TxDeviceProperties.h files
#define T5X_USE_EEPROM

// if enabled, T5X will check during setup routine, if EEPROM version matches. 
//             In case it does not, EEPROM gets initialized with defaults
//             after the initialization of the EEPROM is done, this define can be disabled.
// if disabled, no check is done. this frees up some ROM and RAM
#define T5X_CONDITIONAL_INITIALIZE_EEPROM


// this should never be necessary to be changed
#define T5X_TX_VOLT_PIN    A7        // voltage sensor on A7 
#define T5X_TX_BUZZER_PIN   8        // buzzer connected to digital pin 8
#define T5X_TX_LED_PIN     13        // LED is on standard pin 13

// warning levels for Telemetry Stuff
#define T5X_CELLCOUNT  0
#define T5X_ORANGE     1
#define T5X_RED        2


// our output signal will lie between 800 and 2200 microseconds (1500 +/- 700)
#define T5X_PPM_CENTER 1500          // servo center point
#define T5X_PPM_TRAVEL  700          // max servo travel from center point


//////////////// MESSAGING BETWEEN CONFIGURATOR AND T5X
// Messages from TX to configurator application
#define T5X_MSG_TX_TO_CONFIGURATOR_PREAMBLE1         0xEF
#define T5X_MSG_TX_TO_CONFIGURATOR_PREAMBLE2         0xEF

#define T5X_MSG_PROFILE_DATA_INFO_MSGID              0x01   // report profile data to application
#define T5X_MSG_REALTIME_DATA_INFO_MSGID             0x02   // report realtime data to application
#define T5X_MSG_TXDEVICE_PROPERTIES_INFO_MSGID       0x03   // report device properties to application



// Messages from configurator application to TX
#define T5X_MSG_CONFIGURATOR_TO_TX_PREAMBLE1         0xFE
#define T5X_MSG_CONFIGURATOR_TO_TX_PREAMBLE2         0xFE

#define T5X_MSG_PROFILE_DATA_REQ_MSGID               0x41   // application requests profile data from tx
#define T5X_MSG_PROFILE_DATA_APPLY_MSGID             0x42   // application provides profile data to be applied to tx
#define T5X_MSG_TXDEVICE_PROPERTIES_REQ_MSGID        0x43   // application requests tx device properties from tx
#define T5X_MSG_TXDEVICE_PROPERTIES_APPLY_MSGID      0x44   // appliaction provides tx device properties to be applied to tx
#define T5X_MSG_SAVE_CONFIG_TO_EEPROM_MSGID          0x99   // appliaction tells tx to save configuration from RAM to EEPROM




#endif // ifndef CONFIG_H
