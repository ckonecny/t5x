#include "Profile.h"
#include "config.h"
#include "util.h"

#define T5X_PROFILE_EEPROM_STARTADDR      192    // EEPROM address-range 192 -> 192+9*88=984 is reserved for storing of profiles
#define T5X_PROFILE_EEPROM_RESERVED_BYTES  88    // 88 bytes per profile reserved, 9 profiles


namespace t5x
{
  
void Profile::load(uint8_t aProfileId=0)
{
#ifdef T5X_USE_EEPROM
  EEPROM_readAnything(T5X_PROFILE_EEPROM_STARTADDR+aProfileId*T5X_PROFILE_EEPROM_RESERVED_BYTES, m_Data); 
#else
  m_Data = gDefaultProfile;
#endif
}



void Profile::save(uint8_t aProfileId=0)
{
#ifdef T5X_USE_EEPROM
  EEPROM_writeAnything(T5X_PROFILE_EEPROM_STARTADDR+aProfileId*T5X_PROFILE_EEPROM_RESERVED_BYTES, m_Data); 
#endif
}


void Profile::init()
{
#ifdef T5X_CONDITIONAL_INITIALIZE_EEPROM
  for(int i=0;i<9;i++)
  {
    EEPROM_writeAnything(T5X_PROFILE_EEPROM_STARTADDR+i*T5X_PROFILE_EEPROM_RESERVED_BYTES, gDefaultProfile); 
  } 
#endif  
}

void Profile::send()
{
    Serial.write(T5X_MSG_TX_TO_CONFIGURATOR_PREAMBLE1);     // MsgPreamble
    Serial.write(T5X_MSG_TX_TO_CONFIGURATOR_PREAMBLE2);     // MsgPreamble
    Serial.write(T5X_MSG_PROFILE_DATA_INFO_MSGID);          // MsgId
    
    
    char tBuffer[sizeof(m_Data)];
    memcpy(tBuffer, &m_Data,sizeof(m_Data));
    
    for (int i=0;i<sizeof(m_Data);i++)
    {
      Serial.write(tBuffer[i]);
    }    
 
}

void Profile::receive(byte aMsg[])
{
  memcpy(&m_Data, aMsg+3,sizeof(m_Data));
}

} // namespace end
