#include <Arduino.h>
#include "../include/drivers/wifi.hpp"

void wifiConnectAndSend() {
  WifiDriver wifi;

  Serial.println("Iniciando conexão Wi-Fi...");
  if (wifi.connect("SUA_REDE", "SUA_SENHA")) {
    Serial.println("Wi-Fi conectado!");

    String payload = "{\"umidade\": 42}";
    if (wifi.send(payload)) {
      Serial.println("Dados enviados com sucesso!");
    } else {
      Serial.println("Falha ao enviar dados.");
    }
  } else {
    Serial.println("Falha na conexão Wi-Fi.");
  }
}