#ifndef VIRTUALSENSOR_H
#define VIRTUALSENSOR_H

#include <stdint.h>
#include <Arduino.h> //for string usage

class VirtualSensor { //
  
  private:
	static const float MIN_TEMP;
	static const float MAX_TEMP;
	static const float MIN_PRESSURE;
	static const float MAX_PRESSURE;
	static const float MIN_HUMIDITY;
	static const float MAX_HUMIDITY;
	static const float MIN_PM10;
	static const float MAX_PM10;
	static const float MIN_PM2_5;
	static const float MAX_PM2_5;
	static const uint16_t GPS_VARIATION;
	static const long int TIME_OFFSET;
	
  private:
	static int imeicounter;
	long imei;
	float temperatureRange[2];
	float pressureRange[2];
	float humidityRange[2];
	float pm10Range[2];
	float pm2_5Range[2];
	uint16_t gpsVariation;
	long timeOffset;
	
	float randomf(float min, float max);
	
  public:
	float getTemperature();
	float getPressure();
	float getHumidity();
    float getpm10();
    float getpm2_5();
    float getLongitude(); 
    float getLatitude(); 
    float getAltitude();
    float getAccuracy();
	long getImei();
	long getTime();
	String getAllParametersInHumanReadableForm();
	
	void setTemperatureRange(float min, float max);  //take care, precision is finite
	void setPressureRange(float min, float max);
	void setHumidityRange(float min, float max);
	void setpm10Range(uint16_t min, uint16_t max);
	void setpm2_5Range(uint16_t min, uint16_t max);
	void setGPSVariation(uint16_t meter);
	void setTimeOffset(long millis); 
	//you can set the node to a different time offset than the system time,
	//offset is added to the system time if read out. Offset can be negative
	VirtualSensor();
	
	
};

#endif