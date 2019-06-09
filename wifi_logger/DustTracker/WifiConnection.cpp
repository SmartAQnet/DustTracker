#include "WifiConnection.h"

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiUdp.h>
#include "Logger.h"


// global variables

const String invalidString = "__invalid_string__";


// static variables

const String WifiConnection::tag = "WifiConnection";
const Logger WifiConnection::log = Logger("WifiConnection");

String WifiConnection::ssid = invalidString;
String WifiConnection::password = invalidString;
bool WifiConnection::connected = false;
bool WifiConnection::scanning = false;

IPAddress WifiConnection::ip = IPAddress(0, 0, 0, 0);

WiFiUDP WifiConnection::udp = WiFiUDP();
int WifiConnection::udpListenPort = -1;


// constructors

WifiConnection::WifiConnection() {
}


WifiConnection::WifiConnection(const String & ssid, const String & password) {
  this->ssid = ssid;
  this->password = password;
}


// public functions

bool WifiConnection::setSSID(const String & ssid) {
  if(canSetConnectionData() == false) {
    log.w("in setSSID(): Cannot set ssid: " + ssid);
    return false;
  }

  this->ssid = ssid;
  return true;
}


bool WifiConnection::setPassword(const String & password) {
  if(canSetConnectionData() == false) {
    log.w("in setPassword(): Cannot set password: " + password);
    return false;
  }

  this->password = password;
  return true;
}


String WifiConnection::getSSID() const {
  return this->ssid;
}


String WifiConnection::getPassword() const {
  return this-> password;
}


bool WifiConnection::initConnection() {
  if(hasValidConnectionData() == false) {
    log.e("in initConnection(): Cannot initialize connection due to invalid connection data");
    return false;
  }
  
  WiFi.setAutoReconnect(true);
  WiFi.onEvent(this->ConnectionEventHandler);

  return connect();
}


bool WifiConnection::disconnect() {
  this->ip = IPAddress(0, 0, 0, 0);
  this->udp.stop();
  WiFi.disconnect(true);

  this->scanning = false;
  this->connected = false;
  
  return true;
}


bool WifiConnection::connect() {
  if(hasValidConnectionData() == false) {
    log.e("in connect(): Cannot start connection due to invalid connection data");
    return false;
  }

  bool retval = disconnect();
  if(retval == false) {
    log.c("in connect(): Cannot close previous connection");
    return false;
  }

  this->scanning = true;
  this->connected = false;

  WiFi.begin(this->ssid.c_str(), this->password.c_str());
  log.i("in connect(): Scanning for Wifi network: " + this->ssid);
  
  return true;
}


bool WifiConnection::hasValidConnectionData() const {
  if(this->ssid == invalidString || this->password == invalidString) {
    return false;
  }

  return true;
}


bool WifiConnection::canSetConnectionData() const {
  if(this->scanning == true || this->connected == true) {
    return false;
  }

  return true;
}


bool WifiConnection::isConnected() const {
  return connected;
}


bool WifiConnection::isScanning() const {
  return scanning;
}


bool WifiConnection::sendUDP(const String & host, const unsigned int port, const void * buff, size_t bufflen) const {
  int retval = 0;
  const char * chost = host.c_str();

  retval = this->udp.beginPacket(chost, port);
  if(retval == 0) {
    log.e("in sendUDP(): Cannot resolve host \"" + host + "\" with port " + String(port));
    return false;
  }

  retval = this->udp.write((const uint8_t*) buff, bufflen);
  if(retval != bufflen) {
    log.w("in sendUDP(): could only write " + String(retval) + "/" + String(bufflen) + " bytes. Packet might be corrupted.");
  }

  retval = this->udp.endPacket();
  if(retval == 0) {
    log.c("in sendUDP(): Cannot send packet to " + host + ":" + String(port));
    return false;
  }

  return true;
}


int WifiConnection::getUDPListenPort() const {
  return this->udpListenPort;
}


IPAddress WifiConnection::getIP() const {
  return this->ip;
}


// private functions

void WifiConnection::ConnectionEventHandler(WiFiEvent_t event) {
  switch(event) {
    case SYSTEM_EVENT_STA_GOT_IP:
      scanning = false;
      connected = true;

      ip = WiFi.localIP();
      log.i("in ConnectionEventHandler(): Wifi connected to IP address " + ip.toString());

      udp.stop();
      udpListenPort = random(49152, 65535);
      udp.begin(ip, udpListenPort);

      log.i("in ConnectionEventHandler(): UDP listening on port " + String(udpListenPort));
      break;

    case SYSTEM_EVENT_STA_DISCONNECTED:
      scanning = true;
      connected = false;
      
      log.w("in ConnectionEventHandler(): Wifi lost connection");
      WiFi.disconnect(true);
      
      delay(100000);

      WiFi.begin(ssid.c_str(), password.c_str());
      log.i("in ConnectionEventHandler(): trying to reconnect to WiFi");
      break;

    case SYSTEM_EVENT_STA_CONNECTED:
      scanning = false;
      
      log.i("in ConnectionEventHandler(): Wifi found connection");
      break;
  }
}

