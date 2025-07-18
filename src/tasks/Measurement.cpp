#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "tasks/Measurement.hpp"
#include "tasks/Connection.hpp" 
#include "tasks/Navigation.hpp"
#include "application/ApiService.hpp" 
#include "globals.hpp"


namespace tasks {

    /* Inicialização padrão dos Handles */
    TaskHandle_t xSensorManagerTaskHandle = nullptr;
    TaskHandle_t xMeasureTempHumTaskHandle = nullptr;
    TaskHandle_t xMeasureSoilMoistureTaskHandle = nullptr;
    TaskHandle_t xMeasureLuminosityTaskHandle = nullptr;
    //TaskHandle_t xTakePictureTaskHandle = nullptr;

    void vSensorManagerTask(void* pvParameters) {

        TaskHandle_t xMainHandle = static_cast<TaskHandle_t>(pvParameters);
    
        while (true) {

            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

            //measurement.prepareCamera();
            xTaskNotifyGive(xMeasureTempHumTaskHandle);
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

            xTaskNotifyGive(xMeasureSoilMoistureTaskHandle);
            xTaskNotifyGive(xMeasureLuminosityTaskHandle);
            
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

            // xTaskNotifyGive(xTakePictureTaskHandle);
            // ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

            application::ApiMessage msg;
            msg.type = application::ApiRequestType::SendMeasurement;
            msg.measurement = measurement.getMeasures();

            BaseType_t sent = xQueueSend(tasks::apiQueue, &msg, portMAX_DELAY);
            if (sent != pdTRUE) {
                Serial.println("[vSensorManagerTask] Erro ao enviar mensagem para fila da API!");
            }
            
            xTaskNotifyGive(xMainHandle);
    
        }
    
    }

    void vMeasureTemperatureHumidityTask(void* pvParameters) {

        TickType_t lastExecution = 0;    
        const TickType_t minInterval = pdMS_TO_TICKS(2000);
    
        while (true) {

            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

            TickType_t now = xTaskGetTickCount();

            if (now - lastExecution < minInterval) {

                Serial.printf("TemperatureTask %s", "Chamada ignorada (intervalo < 2s)");
                xTaskNotifyGive(xSensorManagerTaskHandle);
                continue;
    
            }
    
            lastExecution = now;

            measurement.measureTemperature();
            measurement.measureHumidity();

            xTaskNotifyGive(xSensorManagerTaskHandle);

        }

    }

    void vMeasureSoilMoistureTask(void* pvParameters) {

        while (true) {

            // Espera notificação do manager
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

            // Move o servo pra baixo

            // Notifica a classe de navegação (Inserir sensor de umidade)
            xTaskNotifyGive(xNavigationSetInsertionStateTaskHandle);
            
            // Espera a notificação da navegação (Sensor já inserido)
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);    

            // Mede a umidade do solo
            measurement.measureMoisture();

            // Notifica a navegação (Retirar a inserção do sensor de umidade)
            xTaskNotifyGive(xNavigationSetDisinsertionStateTaskHandle);

            // Move o servo pra cima

            // Espera a notificação da navegação (Sensor já retirado)
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY); 

            // Notifica a task manager
            xTaskNotifyGive(xSensorManagerTaskHandle);

        }

    }

    void vMeasureLuminosityTask(void* pvParameters) {

        while (true) {
            
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

            measurement.measureLuminosity();

            xTaskNotifyGive(xSensorManagerTaskHandle);
            
        }

    }

}