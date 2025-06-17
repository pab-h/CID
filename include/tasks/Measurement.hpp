#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

namespace tasks{

    extern TaskHandle_t xMeasureTemperatureTaskHandle;
    extern TaskHandle_t xMeasureHumidityTaskHandle;
    extern TaskHandle_t xMeasureSoilMoistureTaskHandle;
    extern TaskHandle_t xMeasureLuminosityTaskHandle;
    extern TaskHandle_t xTakePictureTaskHandle;

    void vMeasureTemperatureTask(void* pvParameters);
    void vMeasureHumidityTask(void* pvParameters);
    void vMeasureSoilMoistureTask(void* pvParameters);
    void vMeasureLuminosityTask(void* pvParameters);

    void vTakePictureTask(void* pvParameters);
}