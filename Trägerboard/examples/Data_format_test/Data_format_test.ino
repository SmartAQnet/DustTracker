#include <U8x8lib.h>
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include "data_format.h"
#include "virtual_sensor_node.h"
#include "wlan_credentials.h"
//#define BME_SCK 19
//#define BME_MOSI 22


Adafruit_BME280 bme; //default constructor for I2C, default I2C ports are included in Wire.h
VirtualSensor virtualNode1;
VirtualSensor virtualNode2;


const char* remoteIP = "129.13.169.197";
int remotePort = 12345;

//const char* remoteIP = "192.168.43.1";
//int remotePort = 12345;

WiFiUDP udp;

//VirtualSensor virtualNode1();
// the OLED used
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16);

void sendUDPDummy() {
  byte message[2];
  message[0] = 0x41;
  message[1] = 0x42;
  
 
  
  udp.beginPacket(remoteIP,remotePort);
  udp.write(message,sizeof(message));
  udp.endPacket(); 
  Serial.print("UDP sent");   
}

void setup() {

  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);
  //Wire.begin(21,22);
  Wire.begin(22,23);
  //testhalber wirering ändern
  
 String testString;
   
   //virtualNode1.setTemperatureRange(0.0, 100.0);
   




  
  /*SmartAQnetDataFrame dataFrame;
  dataFrame.encoding.value = Encoding::REGULAR_FIR;
  //uint8_t test = Encoding::REGULAR_FIR;
  dataFrame.imei = 0xFF0A0B0C;
  dataFrame.UTCMillis = 1534156365193;
  uint8_t serializedData[10];
  dataFrame.toSerializedStream(serializedData);

  Serial.print("serializedData: ");
  for(int i=0; i<10; i++) {
    Serial.write(serializedData[i]);
  }
  
  
  Serial.print("Encoding: ");
  Serial.print(sizeof(Encoding));
  Serial.print("SmartAQnetDataFrame: ");
  Serial.write(sizeof(SmartAQnetDataFrame));
  
  Serial.print(" ");
  Serial.print("TestCharacter: ");
  uint8_t testCharacter = 0x4A;
  char dataArray[10];
  memcpy (dataArray, &testCharacter, 1 );
  //data[0] = 'A';
  Serial.print(dataArray[0]);
  Serial.print(" ");*/

  
  u8x8.begin();
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0, 1, "Display initialized");
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

   //This initializes udp and transfer buffer
  udp.begin(12345); //local port
  

  
  

}

void loop() {
  
    
  Serial.println("I'm the esp32, take care of me!");
  sendUDPDummy();
  //float currentTemperature = virtualNode1.getTemperature();
  
  //Serial.print(virtualNode1.getAllParametersInHumanReadableForm());
   /*Serial.print("ID: ");
   Serial.print(virtualNode1.getImei());
   Serial.print("Temperatur: ");
   Serial.print(virtualNode1.getTemperature());*/

   /*Serial.print("ID: ");
   Serial.print(virtualNode2.getImei());
   Serial.print("Temperatur: ");
   Serial.print(virtualNode2.getTemperature());*/
  delay(2000);

}
