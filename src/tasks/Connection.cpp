#include <Arduino.h>
#include "drivers/wifi.hpp"
#include <WiFiClient.h>
// #include <ESP8266WiFi.h>
// #include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
// #include "tasks/Tasks.hpp"
#include "entity/Travel.hpp"
#include "entity/SensorData.hpp"
#include "application/Connection.hpp"

#include <WiFi.h>
#include <HTTPClient.h>


using namespace entity;

extern TaskHandle_t sensorReaderHandle;
extern TaskHandle_t dataSenderHandle;
// TaskHandle_t sensorReaderHandle = nullptr;
// TaskHandle_t dataSenderHandle = nullptr;
SensorData globalSensorData;

void wifiConnectAndSend() {
  WifiDriver wifi;

  Serial.println("Iniciando conexão Wi-Fi...");

  if (wifi.connect("Oie", "12345678")) {
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

void TaskWiFiManager(void* pvParameters) {
    WifiDriver wifi;
    while (true) {
        if (WiFi.status() != WL_CONNECTED) {
            Serial.println("[WiFi] Conectando...");
            wifi.connect("Oie", "12345678");
        }
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void TaskRouteReceiver(void* pvParameters) {
    // Aguarda conexão
    while (WiFi.status() != WL_CONNECTED) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    Serial.println("[Route] Baixando rota...");
    testDownloadJson();  

    vTaskDelete(nullptr); 
    vTaskDelete(NULL);
}


void TaskSensorReader(void* pvParameters) {
    
        // ulTaskNotifyTake(pdTRUE, portMAX_DELAY);  // espera ser acionada
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        Serial.println("[Sensor] Lendo sensores...");

        // Simulando leitura real
        globalSensorData = SensorData(
            25.5,      // temperatura
            65.2,      // umidade
            300        // luminosidade
        );

        vTaskDelay(2000 / portTICK_PERIOD_MS);
        // gerarJson(&globalSensorData, 1);
        String json = gerarJson(&globalSensorData, 1);
        Serial.println("[Sensor] JSON gerado:");
        Serial.println(json);
    
    vTaskDelete(NULL);
}
void TaskDataSender(void* pvParameters) {
    
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);  // espera leitura terminar

        Serial.println("[API] Dados prontos, convertendo para JSON...");

        vTaskDelete(NULL);
    
}