#ifndef WIFI_DRIVER_HPP
#define WIFI_DRIVER_HPP

#include <WiFi.h>

class WifiDriver {
  public:
    bool connect(const String& ssid, const String& password);
    void disconnect();
    bool send(const String& mensagem);
    String read();
};

#endif
