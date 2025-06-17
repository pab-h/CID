#include "tasks/Measurement.hpp"
#include "globals.hpp"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <Arduino.h>

namespace tasks {

    /* Inicialização padrão dos Handles */
    TaskHandle_t xMeasureTempHumTaskHandle = nullptr;
    TaskHandle_t xMeasureSoilMoistureTaskHandle = nullptr;
    TaskHandle_t xMeasureLuminosityTaskHandle = nullptr;
    //TaskHandle_t xTakePictureTaskHandle = nullptr;
    TaskHandle_t xSensorManagerTaskHandle = nullptr;

    void vSensorManagerTask(void* pvParameters) {
    
        while (true) {

            Serial.println("Cheguei em 1");
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

            //measurement.prepareCamera();
            Serial.println("Cheguei em 2");
            xTaskNotifyGive(xMeasureTempHumTaskHandle);
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

            Serial.println("Cheguei em 3");
            xTaskNotifyGive(xMeasureSoilMoistureTaskHandle);
            xTaskNotifyGive(xMeasureLuminosityTaskHandle);
            
            Serial.println("Cheguei em 4");
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

            // xTaskNotifyGive(xTakePictureTaskHandle);
            // ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

            vTaskSuspend(NULL);
        }
    
    }

    // Alta prioridade
    void vMeasureTemperatureHumidityTask(void* pvParameters) {

        TickType_t lastExecution = 0;    
        const TickType_t minInterval = pdMS_TO_TICKS(2000);
    
        while (true) {
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);


            Serial.println("Cheguei na task de medir a temperatura");
            TickType_t now = xTaskGetTickCount();
            if (now - lastExecution < minInterval) {
                Serial.printf("TemperatureTask %s", "Chamada ignorada (intervalo < 2s)");
                // Notifica a manager que terminou para não travar o fluxo
                xTaskNotifyGive(xSensorManagerTaskHandle);
                continue;
            }
            lastExecution = now;

            vTaskSuspendAll();
            measurement.measureTemperature();
            measurement.measureUmidity();
            xTaskResumeAll();

            xTaskNotifyGive(xSensorManagerTaskHandle);
        }

    }

    void vMeasureSoilMoistureTask(void* pvParameters) {

        while (true) {
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
            Serial.println("Cheguei na task de medir o solo");
            measurement.measureMoisture();

            xTaskNotifyGive(xSensorManagerTaskHandle);
        }

    }

    void vMeasureLuminosityTask(void* pvParameters) {

        while (true) {
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
            Serial.println("Cheguei na task de medir a luminosidade");
            measurement.measureLuminosity();

            xTaskNotifyGive(xSensorManagerTaskHandle);
        }

    }

    // Alta prioridade
    void vTakePictureTask(void* pvParameters) {

        while (true) {
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

            vTaskSuspendAll();
            measurement.takePicture();
            xTaskResumeAll();

            xTaskNotifyGive(xSensorManagerTaskHandle);
        }
    }

}