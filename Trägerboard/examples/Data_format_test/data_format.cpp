#include "data_format.h"
#include <string.h>

void SmartAQnetDataFrame::toSerializedStream(uint8_t* dataStream) {
      
      memcpy (dataStream, &encoding.value, sizeof(encoding.value) );
      dataStream = dataStream + sizeof(encoding.value);
      memcpy (dataStream, &imei, sizeof(imei));
      dataStream = dataStream + sizeof(imei);
      memcpy (dataStream, &UTCMillis, sizeof(UTCMillis));
      dataStream = dataStream + sizeof(UTCMillis);
      memcpy (dataStream, &UTCMillis, sizeof(payload.temperature));
      dataStream = dataStream + sizeof(payload.temperature);
      memcpy (dataStream, &UTCMillis, sizeof(payload.pressure));
      dataStream = dataStream + sizeof(payload.pressure);
      memcpy (dataStream, &UTCMillis, sizeof(payload.pm10));
      dataStream = dataStream + sizeof(payload.pm10);
      memcpy (dataStream, &UTCMillis, sizeof(payload.pm2_5));
      dataStream = dataStream + sizeof(payload.pm2_5);
      memcpy (dataStream, &UTCMillis, sizeof(payload.longitude));
      dataStream = dataStream + sizeof(payload.longitude);
      memcpy (dataStream, &UTCMillis, sizeof(payload.latitude));
      dataStream = dataStream + sizeof(payload.latitude);
      memcpy (dataStream, &UTCMillis, sizeof(payload.altitude));
      dataStream = dataStream + sizeof(payload.altitude);
      memcpy (dataStream, &UTCMillis, sizeof(payload.accuracy));
      dataStream = dataStream + sizeof(payload.accuracy);     
}
	

uint8_t SmartAQnetDataFrame::getFrameLengt() {
     
     uint8_t frameLength = sizeof(encoding.value) + sizeof(imei)+  sizeof(UTCMillis) + sizeof(payload.temperature)+
       + sizeof(payload.pressure) + sizeof(payload.pm10) + sizeof(payload.pm2_5) + sizeof(payload.longitude) 
       + sizeof(payload.latitude) + sizeof(payload.altitude) + sizeof(payload.accuracy); 

     return frameLength;
    }
