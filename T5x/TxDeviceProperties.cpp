#include "TxDeviceProperties.h"
#include "config.h"
#include "util.h"

#define T5X_DEVICE_PROPS_EEPROM_STARTADDR  0

namespace t5x
{

void TxDeviceProperties::load()
{
#ifdef T5X_USE_EEPROM
  EEPROM_readAnything(T5X_DEVICE_PROPS_EEPROM_STARTADDR, m_Properties); 
#else
  m_Properties = gDefaultDeviceSettings;
#endif
}



void TxDeviceProperties::save()
{
#ifdef T5X_USE_EEPROM
  EEPROM_writeAnything(T5X_DEVICE_PROPS_EEPROM_STARTADDR, m_Properties); 
#endif  
}

void TxDeviceProperties::init()
{
#ifdef T5X_CONDITIONAL_INITIALIZE_EEPROM
  EEPROM_writeAnything(T5X_DEVICE_PROPS_EEPROM_STARTADDR, gDefaultDeviceSettings); 
#endif  
}


void TxDeviceProperties::send()
{
    Serial.write(T5X_MSG_TX_TO_CONFIGURATOR_PREAMBLE1);          // MsgPreamble
    Serial.write(T5X_MSG_TX_TO_CONFIGURATOR_PREAMBLE2);          // MsgPreamble
    Serial.write(T5X_MSG_TXDEVICE_PROPERTIES_INFO_MSGID);        // MsgId

    char tBuffer[sizeof(m_Properties)];
    memcpy(tBuffer, &m_Properties,sizeof(m_Properties));
    
    for (int i=0;i<sizeof(m_Properties);i++)
    {
      Serial.write(tBuffer[i]);
    }        
}


void TxDeviceProperties::receive(byte aMsg[])
{
  memcpy(&m_Properties, aMsg+3,sizeof(m_Properties));
}

} // namespace end
