#include <Arduino.h>

#include "drivers/DcMotor.hpp"
#include "pins.hpp"

// #include "tasks/connection.hpp"  // ou o caminho correto da sua task
#include "application/Connection.hpp"


void TaskWiFiManager(void* pvParameters);
void TaskRouteReceiver(void* pvParameters);
void TaskSensorReader(void* pvParameters);
void TaskDataSender(void* pvParameters);

TaskHandle_t sensorReaderHandle;
TaskHandle_t dataSenderHandle;


using namespace drivers;



void setup() {

    Serial.begin(9600);


    xTaskCreatePinnedToCore(TaskWiFiManager, "WiFi Manager", 4096, NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(TaskRouteReceiver, "Receive Travel", 4096, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(TaskSensorReader, "Read Sensors", 4096, NULL, 1, &sensorReaderHandle, 1);
    xTaskCreatePinnedToCore(TaskDataSender, "Send Sensors", 4096, NULL, 1, &dataSenderHandle, 1);

}

void loop() {

    

}