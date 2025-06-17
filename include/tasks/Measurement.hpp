#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

namespace tasks{

    extern TaskHandle_t xMeasureTempHumTaskHandle;
    extern TaskHandle_t xMeasureSoilMoistureTaskHandle;
    extern TaskHandle_t xMeasureLuminosityTaskHandle;
    extern TaskHandle_t xTakePictureTaskHandle;
    extern TaskHandle_t xSensorManagerTaskHandle;

    void vMeasureTemperatureHumidityTask(void* pvParameters);
    void vMeasureSoilMoistureTask(void* pvParameters);
    void vMeasureLuminosityTask(void* pvParameters);
    //void vTakePictureTask(void* pvParameters);
    void vSensorManagerTask(void* pvParameters);
    
}