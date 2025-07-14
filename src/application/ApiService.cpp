#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include "drivers/Wifi.hpp"
#include "application/ApiService.hpp"
#include "application/Measurement.hpp"

//using namespace entity;
using namespace application;

extern TaskHandle_t sensorReaderHandle;
extern TaskHandle_t dataSenderHandle;

ApiService::ApiService() {}

void ApiService::begin(String ssid, String password) {

    this->wifi = new WifiDriver(ssid, password);
    this->wifi->connect();

}

WifiDriver* ApiService::getWifi() {

    return this->wifi;

}

uint8_t ApiService::getSignalLevel() {
    
    if (!wifi || !wifi->isConnected()) return 0;

    int rssi = WiFi.RSSI();
    if (rssi >= -50) return 4;
    else if (rssi >= -60) return 3;
    else if (rssi >= -70) return 2;
    else if (rssi >= -80) return 1;
    else return 0;

}

bool ApiService::deserializeSteps(const char* jsonBuffer, Step*& stepsOut, uint& countOut) {

    StaticJsonDocument<2048> doc;

    DeserializationError error = deserializeJson(doc, jsonBuffer);

    if (error) {
        Serial.println("[API Service] Erro ao desserializar JSON:");
        Serial.println(error.f_str());
        stepsOut = nullptr;
        countOut = 0;
        return false;
    }

    JsonArray array = doc.as<JsonArray>();
    countOut = array.size();
    stepsOut = new Step[countOut];

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

    Serial.println("[API Service] Buscando dados da API ...");

    if (this->wifi->isConnected()) {
        WiFiClient client;
        HTTPClient http;
        http.begin(client, "http://run.mocky.io/v3/8b34fd7e-22d9-4f00-a27e-43d5af1b2d24");

        int httpCode = http.GET();

        if (httpCode > 0) {
            Serial.println("[API Service] Resposta da API:");
            String payload = http.getString();
            Serial.println(payload);

            Step* steps = nullptr;
            uint count = 0;

            if (deserializeSteps(payload.c_str(), steps, count)) {
                Serial.println("[API Service] Parsing OK!");
                for (uint i = 0; i < count; i++) {
                    Serial.printf("Step %d: howLong=%u, atAngle=%u, isMeasure=%s\n",
                        i, steps[i].howLong, steps[i].atAngle,
                        steps[i].isMeasure ? "true" : "false");
                }
            } else {
                Serial.println("[API Service] Erro ao parsear JSON.");
            }
        } else {
            Serial.print("[API Service] Erro HTTP: ");
            Serial.println(httpCode);
        }

        http.end();
    } else {
        Serial.println("[API Service] WiFi não conectado.");
    }

    Serial.println("[API Service] Dados recebidos da API e convertidos com sucesso!");
    Serial.println("[API Service] Chamando a task de enviar os dados para navegação ... ");
    xTaskNotifyGive(sensorReaderHandle);
    Serial.println("[API Service] Acordei o preguiçoso!");

}

void ApiService::sendDataToApi(const MeasurementResponse& resp) {

    Serial.println("[API Service] JSON a ser enviado:");
    String json = generateJson(resp);
    Serial.println(json);
    Serial.println("[API Service] Simulação que o dado foi enviado corretamente!");

    // Para enviar via POST futuramente:
    /*
    if (WiFi.status() == WL_CONNECTED) {
        WiFiClient client;
        HTTPClient http;
        http.begin(client, "http://sua-api.com/dados");
        http.addHeader("Content-Type", "application/json");

        int httpResponseCode = http.POST(json);
        Serial.print("[API Service] Resposta da API: ");
        Serial.println(httpResponseCode);

        http.end();
    } else {
        Serial.println("[API Service] Wi-Fi não conectado.");
    }
    */

}

void ApiService::sendDataToApi(const StatusData& status) {

    Serial.println("[API Service] JSON do Status a ser enviado:");
    String json = generateJson(status);
    Serial.println(json);
    Serial.println("[API Service] Simulação que o status foi enviado corretamente!");

    // Aqui você pode implementar o envio real via HTTP POST, por exemplo:
    /*
    if (wifi && wifi->isConnected()) {
        WiFiClient client;
        HTTPClient http;
        http.begin(client, "http://sua-api.com/status");
        http.addHeader("Content-Type", "application/json");
        int httpResponseCode = http.POST(json);
        Serial.printf("[API Service] Código resposta: %d\n", httpResponseCode);
        http.end();
    } else {
        Serial.println("[API Service] Wi-Fi não conectado.");
    }
    */

}


String ApiService::generateJson(const MeasurementResponse& resp) {
    
    StaticJsonDocument<512> doc;
    JsonObject root = doc.to<JsonObject>();

    JsonObject data = root.createNestedObject("data");
    data["temperature"] = resp.data.temperature;
    data["humidity"] = resp.data.humidity;
    data["soilMoisture"] = resp.data.soilMoisture;
    data["luminosity"] = resp.data.luminosity;

    JsonArray errors = root.createNestedArray("errors");

    if (resp.error == static_cast<uint8_t>(MeasurementError::NONE)) {
        errors.add("NONE");
    } else {
        if (resp.error & static_cast<uint8_t>(MeasurementError::BUSY)) errors.add("BUSY");
        if (resp.error & static_cast<uint8_t>(MeasurementError::INCOMPLETE)) errors.add("INCOMPLETE");
        if (resp.error & static_cast<uint8_t>(MeasurementError::TEMPERATURE_FAIL)) errors.add("TEMPERATURE_FAIL");
        if (resp.error & static_cast<uint8_t>(MeasurementError::HUMIDITY_FAIL)) errors.add("HUMIDITY_FAIL");
        if (resp.error & static_cast<uint8_t>(MeasurementError::MOISTURE_FAIL)) errors.add("MOISTURE_FAIL");
        if (resp.error & static_cast<uint8_t>(MeasurementError::LUMINOSITY_FAIL)) errors.add("LUMINOSITY_FAIL");
    }

    String json;
    serializeJsonPretty(doc, json);

    Serial.println("[ApiService] JSON do Measurement gerado:");
    Serial.println(json);

    return json;

}


String ApiService::generateJson(const StatusData& status) {

    StaticJsonDocument<256> doc;

    doc["batteryLevel"] = status.batteryLevel;
    doc["connectionLevel"] = status.connectionLevel;
    doc["currentActivity"] = static_cast<int>(status.currentActivity);
    doc["currentSector"] = status.currentSector;

    String json;
    serializeJsonPretty(doc, json);

    Serial.println("[ApiService] JSON do Status gerado:");
    Serial.println(json);

    return json;

}