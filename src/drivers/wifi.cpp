// class WifiDriver:
//  read() -> bytes
//  send(string mensagem)
//  connect(String nome da rede, String password)
//  disconnect()
#include <Arduino.h>
#include "../include/drivers/wifi.hpp"

#include <WiFiClient.h>

bool WifiDriver::connect(const String& ssid, const String& password) {
    WiFi.mode(WIFI_STA);  // <- Torna explícito que é Station
    WiFi.begin(ssid.c_str(), password.c_str());
    
    int tentativas = 0;

    while (WiFi.status() != WL_CONNECTED && tentativas < 10) {
        Serial.print(".");
        delay(1000);
        tentativas++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWi-Fi conectado com sucesso!");
        Serial.print("IP: ");
        Serial.println(WiFi.localIP());
        return true;
    } else {
        Serial.println("\nFalha ao conectar ao Wi-Fi.");
        return false;
    }
}

void WifiDriver::disconnect() {
  WiFi.disconnect();
  Serial.println("Wi-Fi desconectado.");
}

bool WifiDriver::send(const String& mensagem) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi não conectado. Impossível enviar.");
    return false;
  }

  WiFiClient client;
  const char* host = "api.exemplo.com";  // 🔁 Trocar pelo domínio real
  const int port = 80;

  if (!client.connect(host, port)) {
    Serial.println("Erro ao conectar com o servidor.");
    return false;
  }

  // Enviar requisição HTTP (POST)
  client.println("POST /dados HTTP/1.1");
  client.print("Host: ");
  client.println(host);
  client.println("Content-Type: application/json");
  client.print("Content-Length: ");
  client.println(mensagem.length());
  client.println(); // linha em branco obrigatória
  client.println(mensagem);

  Serial.println("Mensagem enviada:");
  Serial.println(mensagem);

  return true;
}

String WifiDriver::read() {
  WiFiClient client;
  if (client.available()) {
    return client.readString();
  }
  return "";
}
