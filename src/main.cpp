#include <Arduino.h>
#include "globals.hpp"
#include "tasks/Measurement.hpp"
#include "application/Measurement.hpp"
#include "drivers/Display.hpp"

using namespace application;

Display display;

void setup(){

    Serial.begin(115200);
    while (!Serial){}

    initGlobals();
    display.begin();

    TaskHandle_t loopHandle = xTaskGetCurrentTaskHandle();

    // Criando as tasks
    xTaskCreatePinnedToCore(tasks::vSensorManagerTask, "SensorManager", 4096, loopHandle, 2, &tasks::xSensorManagerTaskHandle, 0);
    xTaskCreatePinnedToCore(tasks::vMeasureTemperatureHumidityTask, "MeasureTempHum", 2048, NULL, 3, &tasks::xMeasureTempHumTaskHandle, 0);
    xTaskCreatePinnedToCore(tasks::vMeasureSoilMoistureTask, "MeasureSoilMoisture", 2048, NULL, 2, &tasks::xMeasureSoilMoistureTaskHandle, 0);
    xTaskCreatePinnedToCore(tasks::vMeasureLuminosityTask, "MeasureLuminosity", 2048, NULL, 2, &tasks::xMeasureLuminosityTaskHandle, 0);


    Serial.println("Setup concluído, tasks criadas.");

    display.showBatteryIcon(95);
    display.showSystemStatus("Sensoriando");

    
}

void loop() {

    xTaskNotifyGive(tasks::xSensorManagerTaskHandle);
    ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(3000));

    MeasurementResponse resp = measurement.getMeasures();

    Serial.printf("Temperatura: %.2f C\n", resp.data.temperature);
    Serial.printf("Umidade: %.2f %%\n", resp.data.humidity);
    Serial.printf("Umidade do solo: %d %%\n", resp.data.soilMoisture);
    Serial.printf("Luminosidade: %d %%\n", resp.data.luminosity);
    
    Serial.println("-----------------------");

    vTaskDelay(pdMS_TO_TICKS(2000));

}