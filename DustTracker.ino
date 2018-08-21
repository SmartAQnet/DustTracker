#include <stdint.h>

#include "WifiConnection.h"
#include "Logger.h"

String networkName = String("teco");
String networkPassword = String("HMaRBAcdowHino");

struct __attribute__((__packed__)) transfer_struct {
  uint8_t border; // byteorder flag
  int16_t two;
  int32_t four;
  char buff[32];
  uint32_t ufour;
};

void setup() {
  Serial.begin(115200);
  Logger log("setup");
  delay(10);
  Serial.println();
  
  log.i("ESP32 started.");

  WifiConnection WC(networkName, networkPassword);
  WC.initConnection();
}

void loop() {
  Logger log("loop");
  WifiConnection WC;

  String message = "eine nachricht!";

  transfer_struct data;
  data.border = 1;
  data.two = 27137;
  data.four = -7231337;
  data.ufour = 7231337;
  strncpy(data.buff, message.c_str(), 31);
  data.buff[31] = '\0';


  WC.sendUDP("win10-koepke.teco.edu", 1337, & data, sizeof(transfer_struct));

  log.i("now waiting");
  delay(5000);
}

