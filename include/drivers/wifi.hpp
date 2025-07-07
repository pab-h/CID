// Classe Wifi Driver //
#pragma once

#include <WiFi.h>

class WifiDriver {

  private:
    String ssid;
    String password;

  public:
     WifiDriver(const String& ssid, const String& password); 

     String getSSID();
     String getPassword();

     bool connect();
     void disconnect();
     bool reconnect();
     bool isConnected();
};
