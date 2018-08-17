#include "WifiConnection.h"

String networkName = String("teco");
String networkPassword = String("HMaRBAcdowHino");

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println("ESP32 started.");

  WifiConnection WC(networkName, networkPassword);
  WC.initConnection();
  log_e("test");
}

void loop() {
  WifiConnection WC;
  

  String message = "eine nächricht!";
  WC.sendUDP("129.13.170.75", 1337, message.c_str(), message.length());
  Serial.println("now waiting");
  delay(2000);
}

