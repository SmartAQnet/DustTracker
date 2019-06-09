#ifndef DATA_FORMAT_H
#define DATA_FORMAT_H

#include <stdint.h>

class Encoding { //using an enum instead not possible due to enum is 32bit type, heare we only use 
  
  public:
	static const uint8_t REGULAR = 0;
	static const uint8_t REGULAR_FIR = 1;
	static const uint8_t REGULAR_NO_GPS = 2;
	static const uint8_t REGULAR_NO_GPS_FIR = 3;
	static const uint8_t BIG_ENDIAN_AQ = 0;
	static const uint8_t LITTLE_ENDIAN_AQ = 1;
  public:
	uint8_t endianness;
	uint8_t value;
   
};

//values rely on Adafruit BME280 library
class sensorPayload {
  
  public:
    float temperature; //uses max 20 bits
    float pressure; //uses max 20 bits
    float humidity;
    float pm10;
    float pm2_5;
    float longitude; //positive and negative
    float latitude; //positive and negative
    float altitude;
    float accuracy;
};

class SmartAQnetDataFrame {
  
  public:
    Encoding encoding;
    uint64_t imei;
    uint64_t UTCMillis;
    sensorPayload payload;;
 
    void toSerializedStream(uint8_t* dataStream);

    uint8_t getFrameLengt();
};

#endif