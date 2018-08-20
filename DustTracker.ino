#include "WifiConnection.h"
#include "Logger.h"

String networkName = String("teco");
String networkPassword = String("HMaRBAcdowHino");

void setup() {
  Serial.begin(115200);
  Logger log("setup");
  delay(10);
  Serial.println();
  
  log.i("ESP32 started.");

  WifiConnection WC(networkName, networkPassword);
  WC.initConnection();
  log_e("test");
}

void loop() {
  Logger log("loop");
  
  WifiConnection WC;
  
  String message = "eine nachricht!";
  WC.sendUDP("129.13.170.75", 1337, message.c_str(), message.length());

  log.i("now waiting");
  delay(2000);
}

