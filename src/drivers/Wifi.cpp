#include <Arduino.h>
#include <WiFiClient.h>
#include <WiFi.h>

#include "drivers/Wifi.hpp"

using namespace drivers;

String WifiDriver::getSSID() {
  return this->ssid;
}

String WifiDriver::getPassword() {
  return this->password;
}

WifiDriver::WifiDriver(const String& ssid, const String& password) {

  this->ssid     = ssid;
  this->password = password;

}

bool WifiDriver::connect() {

    if (this->ssid == "" || this->password == "") {
      Serial.println("[WiFi]: SSID ou password não configurado! Favor inserir dados na main() ^^");
      return false;
    }

    WiFi.mode(WIFI_STA);  

    WiFi.begin(
      this->ssid.c_str(), 
      this->password.c_str()
    );
    
    int tentativas = 0;

    while (!this->isConnected() && tentativas < 10) {
        delay(1000);
        tentativas++;
        Serial.println("Tentando conexão ... " + String(tentativas) + "/10");
    }

    if (!this->isConnected()) {
        Serial.println("\nFalha ao conectar ao Wi-Fi.");
        return false;
    }

    Serial.println("\nWi-Fi conectado com sucesso!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    return true;

}

void WifiDriver::disconnect() {
  WiFi.disconnect();
  Serial.println("Wi-Fi desconectado.");
}

bool WifiDriver::reconnect(){
  if (this->isConnected()) return true;

  Serial.println("Reconectando Wi-fi ...");
  this->disconnect();
  return this->connect();
}

bool WifiDriver::isConnected(){
  return WiFi.status() == WL_CONNECTED;
}

int WifiDriver::getRSSI() const {

    if (WiFi.status() != WL_CONNECTED) return -127;
    return WiFi.RSSI();

}

// // Inicializa os atributos estáticos
// String WifiDriver::_ssid = "";
// String WifiDriver::_password = "";

// // Funções da classe WifiDriver:
// void WifiDriver::begin(const String& ssid, const String& password) {
//     _ssid = ssid;
//     _password = password;
// }

// bool WifiDriver::connect() {
    
//     if (_ssid == "" || _password == "") {
//       Serial.println("[WiFi]: SSID ou password não configurado! Favor inserir dados na main() ^^");
//       return false;
//     }

//     WiFi.mode(WIFI_STA);  

//     WiFi.begin(_ssid.c_str(), _password.c_str());
    
//     int tentativas = 0;

//     while (WiFi.status() != WL_CONNECTED && tentativas < 10) {
//         delay(1000);
//         tentativas++;
//         Serial.println("Tentando conexão ... " + String(tentativas) + "/10");
//     }

//     if (WiFi.status() == WL_CONNECTED) {
//         Serial.println("\nWi-Fi conectado com sucesso!");
//         Serial.print("IP: ");
//         Serial.println(WiFi.localIP());
//         return true;
//     } else {
//         Serial.println("\nFalha ao conectar ao Wi-Fi.");
//         return false;
//     }
// }

// void WifiDriver::disconnect() {
//   WiFi.disconnect();
//   Serial.println("Wi-Fi desconectado.");
// }

// bool WifiDriver::isConnected(){
//   return WifiDriver::isConnected();
// }

// bool WifiDriver::reconnect(const String& ssid, const String& password){
//   if (isConnected()) return true;

//   Serial.println("Reconectando Wi-fi ...");
//   disconnect();
//   return connect();
// }

// String WifiDriver::getSSID() {
//     return _ssid;
// }

// String WifiDriver::getPassword() {
//     return _password;
// }