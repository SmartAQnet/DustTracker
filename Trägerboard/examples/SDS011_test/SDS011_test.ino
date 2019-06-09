#include <U8x8lib.h>
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include "SdsDustSensor.h"
#include <SoftwareSerial.h>

#define A7_MODULE_ENABLE 2
#define A7_POWER_KEY 17

//hack cause of layout error
//GPIO 26 didnt work, possible due to LORA IRQ pin usage

#define A7_RESET_IN 36
#define A7_SLEEP_IN 37
#define TX_SDS011_PROT_IN 35

#define A7_RESET_OUT 14
#define A7_SLEEP_OUT 12
#define TX_SDS011_PROT_OUT 13
#define RX_SDS011 34
#define SDS011_ENABLE 27

//#define __DEBUG_SDS_DUST_SENSOR__

SoftwareSerial swSer(RX_SDS011, TX_SDS011_PROT_OUT, false, 256);
SdsDustSensor sds(swSer);


void setup() {
  pinMode(TX_SDS011_PROT_IN, INPUT);
  pinMode(SDS011_ENABLE, OUTPUT);
  digitalWrite(SDS011_ENABLE, HIGH); //switchs mosfet on
  
  Serial.begin(115200);
  sds.begin(9600); //pass 9600 bps here?
  
  delay(10000);
  Serial.println("Startup_completed");
 
  
  
  Serial.println("&swSer");
  int objectAddress = (int)&swSer;
  Serial.println(objectAddress, HEX);
  
  Serial.println("sds Object");
  int pointerToSDS = (int)&sds;
  Serial.println(pointerToSDS, HEX);
  Serial.println(sds.setQueryReportingMode().toString()); // prints firmware version
  //check if passed softserial object resides in SDS Sensor?
  //Serial.println("sds.abstractSerial->getStream()");
  //Serial.println((int)(sds.abstractSerial->getStream()), HEX);
  
  
  //ReportingModeResult result = sds.setQueryReportingMode();
  
  

  
  

}

void loop() {
  // put your main code here, to run repeatedly:
  swSer.write("sw active");
  //sds.queryFirmwareVersion();
  Serial.println(sds.queryFirmwareVersion().toString()); // prints firmware version
  PmResult pm = sds.queryPm();
  if (pm.isOk()) {
    Serial.print("PM2.5 = ");
    Serial.print(pm.pm25);
    Serial.print(", PM10 = ");
    Serial.println(pm.pm10);

    // if you want to just print the measured values, you can use toString() method as well
    //Serial.println(pm.toString());
  } else {
    Serial.print("Could not read values from sensor, reason: ");
    Serial.println(pm.statusToString());
  }
  /*Serial.println("sds.abstractSerial->getStream()");
  Serial.println((int)(sds.abstractSerial->getStream()), HEX);
  Serial.println("sds.sdsStream");
  Serial.println((int)(sds.sdsStream), HEX);*/
  //Serial.println(sds.queryFirmwareVersion().toString()); // prints firmware version
  //Serial.println("Main swSer.available() ");
  //Serial.println(swSer.available());
  
  delay(3000);
 

  
  

}
