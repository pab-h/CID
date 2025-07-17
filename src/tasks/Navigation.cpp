#include <freertos/FreeRTOS.h>

#include "application/Navigation.hpp"
#include "tasks/Navigation.hpp"
#include "tasks/Measurement.hpp"

using namespace application;
using namespace drivers;

namespace tasks {

    TaskHandle_t xNavigationSetInsertionStateTaskHandle = nullptr;
    TaskHandle_t xNavigationSetDisinsertionStateTaskHandle = nullptr;

    void vNavigationSetInsertionStateTask(void* pvParameters) {

        Navigation* navigation = static_cast<Navigation*>(pvParameters);

        while (true) {

            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

            navigation->setInsertionState();

        }

    }

    void vNavigationSetDisinsertionStateTask(void* pvParameters) {

        Navigation* navigation = static_cast<Navigation*>(pvParameters);

        while (true) {

            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

            navigation->setDisinsertionState();

        }

    }

    void vNavigationNotificationsTask(void* pvParameters) {

        Navigation*    navigation    = static_cast<Navigation*>(pvParameters);
        Notifications* notifications = navigation->getNotifications();

        while (true) {

            if (notifications->isSendWaitingAlert) {
                Serial.println("[Application::Navigation] Notificação de espera enviada");
                xTaskNotifyGive(xSensorManagerTaskHandle);
                notifications->isSendWaitingAlert = false;
            }

            if (notifications->isSendInsertinDoneAlert) {
                Serial.println("[Application::Navigation] Notificação de inserção completa enviada");
                xTaskNotifyGive(xMeasureSoilMoistureTaskHandle);
                notifications->isSendInsertinDoneAlert = false;
            }

            if(notifications->isSendDesinsertinDoneAlert) {
                Serial.println("[Application::Navigation] Notificação de retirada completa enviada");
                xTaskNotifyGive(xMeasureSoilMoistureTaskHandle);
                notifications->isSendDesinsertinDoneAlert = false;
            }

            vTaskDelay(pdMS_TO_TICKS(50));

        }

    }

// void tasks::vUpdateRotaryEncoderTask(void* pvParameters) {
    
//     Navigation*    navigation = static_cast<Navigation*>(pvParameters);
//     RotaryEncoder* encoder    = navigation->getRotaryEncoder();
    
//     while (true) {
//         encoder->read();
//         vTaskDelay(pdMS_TO_TICKS(50));
//     }

// }

    void vNavigationTask(void* pvParameters) {
        
        Navigation* navigation = static_cast<Navigation*>(pvParameters);

        while (true) {
            navigation->step();
            vTaskDelay(pdMS_TO_TICKS(100));
        }

    }


}