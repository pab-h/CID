// Bibliotecas utilizadas
#include <Arduino.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Importações
#include "drivers/Wifi.hpp"
#include "entity/Travel.hpp"
#include "application/ApiService.hpp"
#include "application/Measurement.hpp"
#include "globals.hpp"

//using namespace entity;
using namespace application; 

namespace tasks{

  QueueHandle_t apiQueue = nullptr;

  TaskHandle_t sensorReaderHandle;
  TaskHandle_t dataSenderHandle;

  //Usando a entidade global para armazenar os valores lidos nos sensores
  const int numLeituras = 5;

  //Função para manter a Wifi conectada
  void wifiMonitorTask(void* pvParameters) {
    application::ApiService* api = static_cast<application::ApiService*> (pvParameters);
    WifiDriver*             wifi = api->getWifi(); 

    vTaskDelay(1);
    while (true) {
    
      if (!wifi->isConnected()) {
          Serial.println("[WiFiMonitor] Wi-Fi desconectado! Tentando reconectar...");
          wifi->reconnect();
      }

      vTaskDelay(pdMS_TO_TICKS(5000)); // espera 5 segundos antes de checar de novo

    }
  
  }


  void TaskRouteReceiver(void* pvParameters) {

    application::ApiService* api = static_cast<application::ApiService*> (pvParameters);
    WifiDriver*             wifi = api->getWifi(); 

    vTaskDelay(1);

    while (!wifi->isConnected()) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    Serial.println("[Route] Baixando rota...");
    api->testDownloadJson();
    vTaskDelete(nullptr); 

  }

  void TaskSensorReader(void* pvParameters) {
  
    application::ApiService* api = static_cast<application::ApiService*> (pvParameters);
    WifiDriver*             wifi = api->getWifi(); 

    //SensorManager sensorManager;

    vTaskDelay(1);

    // ulTaskNotifyTake(pdTRUE, portMAX_DELAY);  // espera ser acionada
    // ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    Serial.println("[TaskSensorReader] Dispositivo parou! Iniciando leitura e envio único...");

    application::MeasurementResponse currentSensorData = measurement.getMeasures();
    // Simulando leitura real
    // sensorArray[0] = SensorData(25.5, 65.2, 300, 22.6);
    // sensorArray[1] = SensorData(26.0, 64.0, 320, 24.5);
    // sensorArray[2] = SensorData(24.8, 70.5, 280, 21.2);
    // sensorArray[3] = SensorData(25.2, 63.3, 310, 27.6);
    // sensorArray[4] = SensorData(26.1, 66.7, 305, 22.6);

    // vTaskDelay(2000 / portTICK_PERIOD_MS);
    

    String json = api->generateJson(currentSensorData);
    // gerarJson(&globalSensorData, 1);
    // String json = gerarJson(&globalSensorData, 1);
    Serial.println("[Sensor] JSON gerado:");
    Serial.println("[TaskSensorReader] Leitura e envio concluídos. Deletando task.");

    Serial.println(json);

    vTaskDelete(NULL);
    
  }

  void TaskDataSender(void* pvParameters) {

    vTaskDelay(1);
      
    // ulTaskNotifyTake(pdTRUE, portMAX_DELAY);  // espera leitura terminar

    Serial.println("[API] Dados prontos, convertendo para JSON...");

    vTaskDelete(NULL);
      
  }

  void TaskApiDispatcher(void* pvParameters) {

    (void) pvParameters;

    while (true) {
      ApiMessage message;

      if (xQueueReceive(apiQueue, &message, portMAX_DELAY) == pdTRUE) {
        switch (message.type) {
            case ApiRequestType::SendMeasurement:
                api.sendDataToApi(message.measurement);
                break;
            case ApiRequestType::SendStatus:
                api.sendDataToApi(message.status);
                break;
        }
      }
    }
  }

}
