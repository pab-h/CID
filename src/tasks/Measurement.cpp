#include "tasks/Measurement.hpp"
#include "globals.hpp"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>

namespace tasks {

    /*Inicialização padrão dos Handles*/
    TaskHandle_t xMeasureTemperatureTaskHandle = NULL;
    TaskHandle_t xMeasureHumidityTaskHandle = NULL;
    TaskHandle_t xMeasureSoilMoistureTaskHandle = NULL;
    TaskHandle_t xMeasureLuminosityTaskHandle = NULL;
    TaskHandle_t xTakePictureTaskHandle = NULL;

    void vMeasureTemperatureTask(void* pvParameters) {

        TickType_t lastExecution = 0;    
        const TickType_t minInterval = pdMS_TO_TICKS(2000);
    
        while (true) {

            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

            TickType_t now = xTaskGetTickCount();
            if (now - lastExecution < minInterval) {
                ESP_LOGW("TemperatureTask", "Chamada ignorada (intervalo < 2s)");
                continue;
            }
            lastExecution = now;

            //Suspende todas as tasks para assegurar a confiabilidade da medição
            vTaskSuspendAll(); 
            measurement.measureTemperature();
            xTaskResumeAll();
        }
    }

    void vMeasureHumidityTask(void* pvParameters) {

        TickType_t lastExecution = 0;
        const TickType_t minInterval = pdMS_TO_TICKS(2000);

        while (true) {
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

            TickType_t now = xTaskGetTickCount();
            if (now - lastExecution < minInterval) {
                ESP_LOGW("HumidityTask", "Chamada ignorada (intervalo < 2s)");
                continue;
            }
            lastExecution = now;

            //Suspende todas as tasks para assegurar a confiabilidade da medição
            vTaskSuspendAll();
            measurement.measureUmidity();
            xTaskResumeAll();
        }
    }

    void vMeasureSoilMoistureTask(void* pvParameters) {
        while (true) {
            // Executa apenas após a notificação
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

            measurement.measureMoisture();
        }
}

    void vMeasureLuminosityTask(void* pvParameters) {
        while (true) {
            // Executa apenas após a notificação
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

            measurement.measureLuminosity();
        }
    }

    //Melhorias no begin no início do estado de sensoriamento
    void vTakePictureTask(void* pvParameters) {
        while (true) {
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

            vTaskSuspendAll();
            measurement.takePicture();
            xTaskResumeAll();
        }
    }

}