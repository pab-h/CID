//logica do que fazer com os dados
//pegar o texto e processar pra uma nova estrutura e passar pra camada de coisa

//Add o ngç de receber o json e mudar 

//enviar os dados

#include <ESP8266HTTPClient.h>

#include <ArduinoJson.h>

#include <WiFiClient.h>
#include <ESP8266WiFi.h> 

#include "entity/Step.hpp"
#include "entity/Travel.hpp"
#include "drivers/wifi.hpp"

using namespace entity;

void wifiConnectAndSend() {
  WifiDriver wifi;

  Serial.println("Iniciando conexão Wi-Fi...");

  if (wifi.connect("Oie", "12345678")) {
    Serial.println("Wi-Fi conectado!");

}

bool deserializeSteps(const char* jsonBuffer, Step*& stepsOut, uint& countOut) {
    StaticJsonDocument<1024> doc;

    DeserializationError error = deserializeJson(doc, jsonBuffer);
    if (error) {
        Serial.print(F("Erro de JSON: "));
        Serial.println(error.f_str());
        stepsOut = nullptr;
        countOut = 0;
        return false;
    }

    JsonArray array = doc.as<JsonArray>();
    uint count = array.size();
    stepsOut = new Step[count];

    for (uint i = 0; i < count; i++) {
        JsonObject obj = array[i];

        uint     howLong   = obj["howLong"] | 0;
        uint16_t atAngle   = obj["atAngle"] | 0;
        bool     isMeasure = obj["isMeasure"] | false;

        stepsOut[i] = Step(howLong, atAngle, isMeasure);
    }

    countOut = count;
    return true;
}
