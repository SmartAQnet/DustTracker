#ifndef __WIFI_H__
#define __WIFI_H__

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "Logger.h"


class WifiConnection {
  private:
    static const String tag;
    static const Logger log;
    
    static String ssid;
    static String password;
    static bool connected;
    static bool scanning;

    static IPAddress ip;

    static WiFiUDP udp;
    static int udpListenPort;

  public:
    WifiConnection();
    WifiConnection(const String & ssid, const String & password);

    bool setSSID(const String & ssid);
    bool setPassword(const String & password);
    String getSSID() const;
    String getPassword() const;

    bool initConnection();
    bool disconnect();
    bool connect();

    bool hasValidConnectionData() const;
    bool canSetConnectionData() const;
    bool isConnected() const;
    bool isScanning() const;

    bool sendUDP(const String & host, const unsigned int port, const void * buff, size_t bufflen) const;
    int getUDPListenPort() const;
    IPAddress getIP() const;

  private:
    static void ConnectionEventHandler(WiFiEvent_t event);
};

#endif
