#include "RealtimeData.h"

namespace t5x
{
  

void RealtimeData::send()
{
    Serial.write(T5X_MSG_TX_TO_CONFIGURATOR_PREAMBLE1);     // MsgPreamble
    Serial.write(T5X_MSG_TX_TO_CONFIGURATOR_PREAMBLE2);     // MsgPreamble
    Serial.write(T5X_MSG_REALTIME_DATA_INFO_MSGID);         // MsgId
    
    char tBuffer[sizeof(m_Data)];
    
    memcpy(tBuffer, &m_Data,sizeof(m_Data));
    
    for (int i=0;i<sizeof(m_Data);i++)
    {
//      Serial.write((char*)&m_Data+i);  
      Serial.write(tBuffer[i]);
    }        
}


} // namespace end
