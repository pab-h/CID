//Regras de Negócio
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>

#include "drivers/wifi.hpp"
#include "application/ApiService.hpp"
//#include "entity/SensorData.hpp"
#include "application/Measurement.hpp"

using namespace entity;
using namespace application;

extern TaskHandle_t sensorReaderHandle;
extern TaskHandle_t dataSenderHandle;

ApiService::ApiService() {

    this->wifi = new WifiDriver("Oie", "12345678");

    this->wifi->connect();

}

WifiDriver* ApiService::getWifi() {
    return this->wifi;
}

bool ApiService::deserializeSteps(const char* jsonBuffer, Step*& stepsOut, uint& countOut) {

    StaticJsonDocument<2048> doc; //Se precisar pode aumentar para receber o JSON

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

void ApiService::testDownloadJson() {

    Serial.println("Buscando dados da API ...");

    if (this->wifi->isConnected()) {
        WiFiClient client;
        HTTPClient http;
        http.begin(client, "http://run.mocky.io/v3/8b34fd7e-22d9-4f00-a27e-43d5af1b2d24");

        int httpCode = http.GET();

        if (httpCode > 0) {
            String payload = http.getString();
            Serial.println("Resposta da API:");
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

    Serial.println("Dados recebidos da API e convertidos com sucesso!");
    Serial.println("Chamando a task de enviar os dados para navegação ... ");
    xTaskNotifyGive(sensorReaderHandle);
    Serial.println("Acordei o preguiçoso!");

}

void ApiService::enviarDadosParaApi(SensorData leituras, uint count) {
    String json = gerarJson(leituras, count);
    Serial.println("JSON a ser enviado:");
    Serial.println(json);
    Serial.println("Simulação que o dado foi enviado corretamente!");
    // Para enviar via POST futuramente:
    /*
    if (WiFi.status() == WL_CONNECTED) {
        WiFiClient client;
        HTTPClient http;
        http.begin(client, "http://sua-api.com/dados");
        http.addHeader("Content-Type", "application/json");

        int httpResponseCode = http.POST(json);
        Serial.printf("Resposta da API: %d\n", httpResponseCode);

        http.end();
    } else {
        Serial.println("Wi-Fi não conectado.");
    }
    */
}

String ApiService::gerarJson(SensorData leituras, uint count) {

    StaticJsonDocument<512> doc;

    JsonArray array = doc.to<JsonArray>();


    JsonObject obj = array.createNestedObject();

    obj["temperature"] = leituras.temperature;
    obj["humidity"] = leituras.humidity;
    obj["moisture"] = leituras.soilMoisture;
    obj["luminosity"] = leituras.luminosity;

    String json;
    serializeJsonPretty(doc, json);
    Serial.println("Dados dos sensores foram devidamente recebidos e convertidos para JSON!");
    Serial.println("Chamando a task para enviar esses dados para API ...");

    // xTaskNotifyGive(dataSenderHandle); // a chamada para a proxima task
    Serial.println("Acordei o segundo preguiçoso!");
    return json;
}