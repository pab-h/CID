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
#include "application/Connection.hpp"

using namespace entity;

bool deserializeSteps(const char* jsonBuffer, Step*& stepsOut, uint& countOut) {
    // Ajuste o tamanho conforme o tamanho máximo esperado do JSON
    StaticJsonDocument<2048> doc;

    DeserializationError error = deserializeJson(doc, jsonBuffer);
    if (error) {
        Serial.print(F("Erro ao desserializar JSON: "));
        Serial.println(error.f_str());
        stepsOut = nullptr;
        countOut = 0;
        return false;
    }

    JsonArray array = doc.as<JsonArray>();
    countOut = array.size();
    stepsOut = new Step[countOut];  // alocação dinâmica

    for (uint i = 0; i < countOut; i++) {
        JsonObject obj = array[i];
        stepsOut[i] = Step(
            obj["howLong"] | 0,
            obj["atAngle"] | 0,
            obj["isMeasure"] | false
        );
    }

    return true;
}

void testDownloadJson() {
    WifiDriver wifi;

    Serial.println("Iniciando conexão Wi-Fi...");

        if (wifi.connect("Oie", "12345678")) {
            Serial.println("Wi-Fi conectado!");
        } else{
            Serial.println("nao deu certo conectar");
        }
        
    if (WiFi.status() == WL_CONNECTED) {
        WiFiClient client;
        HTTPClient http;
        http.begin(client, "http://run.mocky.io/v3/8b34fd7e-22d9-4f00-a27e-43d5af1b2d24");  // ✅ Forma correta

        int httpCode = http.GET();

        if (httpCode > 0) {
            String payload = http.getString();
            Serial.println("Resposta:");
            Serial.println(payload);

            Step* steps = nullptr;
            uint count = 0;

            if (deserializeSteps(payload.c_str(), steps, count)) {
                Serial.println("Parsing OK!");
                for (uint i = 0; i < count; i++) {
                    Serial.printf("Step %d: howLong=%u, atAngle=%u, isMeasure=%s\n",
                        i, steps[i].howLong, steps[i].atAngle,
                        steps[i].isMeasure ? "true" : "false");
                }
            } else {
                Serial.println("Erro ao parsear JSON.");
            }
        } else {
            Serial.printf("Erro HTTP: %d\n", httpCode);
        }

        http.end();
    } else {
        Serial.println("WiFi não conectado.");
    }
}

