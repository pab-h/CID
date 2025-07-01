// Bibliotecas utilizadas
#include <Arduino.h>

// Importações
#include "application/ApiService.hpp"
#include "drivers/wifi.hpp"

// Declaração de funções

void wifiMonitorTask(void* pvParameters);
void TaskRouteReceiver(void* pvParameters);
void TaskSensorReader(void* pvParameters);
void TaskDataSender(void* pvParameters);

// Ainda não sei como chamar isso
TaskHandle_t sensorReaderHandle;
TaskHandle_t dataSenderHandle;

// using namespace drivers;
application::ApiService* api = nullptr;


void setup() {
    // Iniciando Monitor Serial
    Serial.begin(9600);
    api = new application::ApiService();



    // Tasks
    xTaskCreatePinnedToCore(wifiMonitorTask, "WiFi Manager", 4096, api, 2, NULL, 0);
    // xTaskCreatePinnedToCore(TaskRouteReceiver, "Receive Travel", 4096, api, 1, NULL, 0);
    xTaskCreatePinnedToCore(TaskSensorReader, "Read Sensors", 4096, api, 1, &sensorReaderHandle, 1);
    xTaskCreatePinnedToCore(TaskDataSender, "Send Sensors", 4096, api, 1, &dataSenderHandle, 1);

}

void loop() {  

}