#include "virtual_sensor_node.h"
#include <limits.h>
#include <Arduino.h>



int VirtualSensor::imeicounter = 0;

//default values
const float VirtualSensor::MIN_TEMP = 10;
const float VirtualSensor::MAX_TEMP = 30;
const float VirtualSensor::MIN_PRESSURE = 950;
const float VirtualSensor::MAX_PRESSURE = 1050;
const float VirtualSensor::MIN_HUMIDITY = 30;
const float VirtualSensor::MAX_HUMIDITY = 100;
const float VirtualSensor::MIN_PM10 = 0;
const float VirtualSensor::MAX_PM10 = 80;
const float VirtualSensor::MIN_PM2_5 = 0;
const float VirtualSensor::MAX_PM2_5 = 100;
const uint16_t VirtualSensor::GPS_VARIATION = 10;
const long int VirtualSensor::TIME_OFFSET = 0L;

VirtualSensor::VirtualSensor() {
	imei = ++imeicounter;
	temperatureRange[0] = MIN_TEMP;
	temperatureRange[1] = MAX_TEMP;
	pressureRange[0] = MIN_PRESSURE;
	pressureRange[1] = MAX_PRESSURE;
	humidityRange[0] = MIN_HUMIDITY;
	humidityRange[1] = MAX_HUMIDITY;
	pm10Range[0] = MIN_PM10;
	pm10Range[1] = MAX_PM10;
	pm2_5Range[0] = MIN_PM2_5;
	pm2_5Range[1] = MAX_PM2_5;
	gpsVariation = GPS_VARIATION;
	timeOffset = TIME_OFFSET;
}

float VirtualSensor::getTemperature() {
	return randomf(temperatureRange[0],temperatureRange[1]);
}

float VirtualSensor::getPressure() {
	return randomf(pressureRange[0],pressureRange[1]);
}

float VirtualSensor::getHumidity() {
	return randomf(humidityRange[0],humidityRange[1]);
}

float VirtualSensor::getpm10() {
	return randomf(pm10Range[0], pm10Range[1]);
}

float VirtualSensor::getpm2_5() {
	return randomf(pm2_5Range[0], pm2_5Range[1]);
}

long VirtualSensor::getImei() {
	return imei;
}

String VirtualSensor::getAllParametersInHumanReadableForm() {
	const int decimalPrecision = 2;
	String output;
	output =  output + "IMEI: " +String(getImei(), decimalPrecision) + " ";
	output =  output + "Temperature: " +String(getTemperature(), decimalPrecision) + " ";
	output =  output + "Pressure: " +String(getPressure(), decimalPrecision) + " "; 
	output =  output + "Humidity: " +String(getHumidity(), decimalPrecision) + " ";
	output =  output + "Humidity: " +String(getHumidity(), decimalPrecision) + " ";
	output =  output + "PM10: " +String(getpm10(), decimalPrecision) + " ";
 	output =  output + "PM2.5: " +String(getpm2_5(), decimalPrecision) + " ";
	return output;
}


void VirtualSensor::setTimeOffset(long millis) {
	this->timeOffset = millis;
}

float VirtualSensor::randomf(float min, float max) {
	float randomNumber = min + static_cast <float> (random(LONG_MAX)) /( static_cast <float> (LONG_MAX/(max-min)));
	return randomNumber;
}

void VirtualSensor::setTemperatureRange(float min, float max) {
	this->temperatureRange[0] = min;
	this->temperatureRange[1] = max;
}

void VirtualSensor::setPressureRange(float min, float max) {
	this->pressureRange[0] = min;
	this->pressureRange[1] = max;
}

void VirtualSensor::setHumidityRange(float min, float max) {
	this->humidityRange[0] = min;
	this->humidityRange[1] = max;
}

void VirtualSensor::setpm10Range(uint16_t min, uint16_t max) {
	this->pm10Range[0] = min;
	this->pm10Range[1] = max;
}

void VirtualSensor::setpm2_5Range(uint16_t min, uint16_t max) {
	this->pm2_5Range[0] = min;
	this->pm2_5Range[1] = max;
}

void VirtualSensor::setGPSVariation(uint16_t meter) {
	this->gpsVariation = meter;
}




