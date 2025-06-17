#include <Arduino.h>
#include "globals.hpp"
#include "tasks/Measurement.hpp"
#include "application/Measurement.hpp"

using namespace application;

void setup(){

    Serial.begin(9600);
    while (!Serial){}

    // Criando as tasks
    xTaskCreatePinnedToCore(tasks::vSensorManagerTask, "SensorManager", 4096, NULL, 2, &tasks::xSensorManagerTaskHandle, 0);
    xTaskCreatePinnedToCore(tasks::vMeasureTemperatureHumidityTask, "MeasureTempHum", 2048, NULL, 3, &tasks::xMeasureTempHumTaskHandle, 0);
    xTaskCreatePinnedToCore(tasks::vMeasureSoilMoistureTask, "MeasureSoilMoisture", 2048, NULL, 2, &tasks::xMeasureSoilMoistureTaskHandle, 0);
    xTaskCreatePinnedToCore(tasks::vMeasureLuminosityTask, "MeasureLuminosity", 2048, NULL, 2, &tasks::xMeasureLuminosityTaskHandle, 0);
    // Não criei a task da camera

    Serial.println("Setup concluído, tasks criadas.");
}

void loop() {
    // Iniciando a medição dos sensores
    xTaskNotifyGive(tasks::xSensorManagerTaskHandle);

    // Esperando um tempo para as tasks processarem
    vTaskDelay(pdMS_TO_TICKS(3000));

    // Exibindo os dados
    MeasurementResponse resp = measurement.getMeasures();

    // if (resp.error == MeasurementError::NONE) {
    Serial.printf("Temperatura: %.2f C\n", resp.data.temperature);
    Serial.printf("Umidade: %.2f %%\n", resp.data.humidity);
    Serial.printf("Umidade do solo: %d %%\n", resp.data.soilMoisture);
    Serial.printf("Luminosidade: %d %%\n", resp.data.luminositySensor);
    Serial.println("---------------------");
    // } else {
    //     Serial.printf("Erro na medição: %d\n", static_cast<int>(resp.error));
    // }

    // Aguarda próximo ciclo
    vTaskDelay(pdMS_TO_TICKS(2000));
}