#include <Arduino.h>

#include "application/ApiService.hpp"
#include "application/Measurement.hpp"
#include "drivers/Display.hpp"
#include "tasks/Connection.hpp"
#include "tasks/Measurement.hpp"
#include "tasks/SystemStatus.hpp"
#include "globals.hpp"

void setup() {

    Serial.begin(115200);
    while (!Serial){}

    initGlobals();

    TaskHandle_t loopHandle = xTaskGetCurrentTaskHandle();

    xTaskCreatePinnedToCore(wifiMonitorTask, "WiFi Manager", 8192, &api, 2, NULL, 0);
    // xTaskCreatePinnedToCore(TaskRouteReceiver, "Receive Travel", 4096, api, 1, NULL, 0);
    xTaskCreatePinnedToCore(TaskSensorReader, "Read Sensors", 4096, &api, 1, &sensorReaderHandle, 1);
    xTaskCreatePinnedToCore(TaskDataSender, "Send Sensors", 4096, &api, 1, &dataSenderHandle, 1);

    xTaskCreatePinnedToCore(tasks::vSensorManagerTask, "SensorManager", 4096, loopHandle, 2, &tasks::xSensorManagerTaskHandle, 0);
    xTaskCreatePinnedToCore(tasks::vMeasureTemperatureHumidityTask, "MeasureTempHum", 2048, NULL, 3, &tasks::xMeasureTempHumTaskHandle, 0);
    xTaskCreatePinnedToCore(tasks::vMeasureSoilMoistureTask, "MeasureSoilMoisture", 2048, NULL, 2, &tasks::xMeasureSoilMoistureTaskHandle, 0);
    xTaskCreatePinnedToCore(tasks::vMeasureLuminosityTask, "MeasureLuminosity", 2048, NULL, 2, &tasks::xMeasureLuminosityTaskHandle, 0);
    xTaskCreatePinnedToCore(tasks::vSystemStatusTask, "SystemMonitor", 2048, NULL, 1, &tasks::xSystemStatusTaskHandle, 1);


    Serial.println("Setup concluído, tasks criadas.");

}

using namespace application;

void loop() {

    xTaskNotifyGive(tasks::xSensorManagerTaskHandle);
    ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(3000));

    MeasurementResponse resp = measurement.getMeasures();

    Serial.printf("Temperatura: %.2f C\n", resp.data.temperature);
    Serial.printf("Umidade: %.2f %%\n", resp.data.humidity);
    Serial.printf("Umidade do solo: %d %%\n", resp.data.soilMoisture);
    Serial.printf("Luminosidade: %d %%\n", resp.data.luminosity);
    Serial.printf("WIFI LEVEL: %s", String(systemStatus.getConnectionLevel()));
    
    Serial.println("-----------------------");

    vTaskDelay(pdMS_TO_TICKS(2000));

}