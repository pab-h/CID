#include <freertos/FreeRTOS.h>

#include "application/Navigation.hpp"
#include "tasks/Navigation.hpp"

using namespace application;
using namespace drivers;
using namespace tasks;

void tasks::vNavigationSetInsertionStateTask(void* pvParameters) {

    Navigation* navigation = static_cast<Navigation*>(pvParameters);

    while (true) {

        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        navigation->setInsertionState();

    }

}

void tasks::vNavigationSetDisinsertionStateTask(void* pvParameters) {

    Navigation* navigation = static_cast<Navigation*>(pvParameters);

    while (true) {

        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        navigation->setDisinsertionState();

    }

}

void tasks::vNavigationNotificationsTask(void* pvParameters) {

    Navigation*    navigation    = static_cast<Navigation*>(pvParameters);
    Notifications* notifications = navigation->getNotifications();

    while (true) {

        if (notifications->isSendWaitingAlert) {
            Serial.println("[Application::Navigation] Notificação de espera enviada");
            // xTaskNotify
            notifications->isSendWaitingAlert = false;
        }

        if (notifications->isSendInsertinDoneAlert) {
            Serial.println("[Application::Navigation] Notificação de inserção completa enviada");
            // xTaskNotify
            notifications->isSendInsertinDoneAlert = false;
        }

        if(notifications->isSendDesinsertinDoneAlert) {
            Serial.println("[Application::Navigation] Notificação de retirada completa enviada");
            // xTaskNotify
            notifications->isSendDesinsertinDoneAlert = false;
        }

        vTaskDelay(pdMS_TO_TICKS(50));

    }

}

void tasks::vUpdateRotaryEncoderTask(void* pvParameters) {
    
    Navigation*    navigation = static_cast<Navigation*>(pvParameters);
    RotaryEncoder* encoder    = navigation->getRotaryEncoder();
    
    while (true) {
        encoder->read();
        vTaskDelay(pdMS_TO_TICKS(50));
    }

}

void tasks::vNavigationTask(void* pvParameters) {
    
    Navigation* navigation = static_cast<Navigation*>(pvParameters);

    while (true) {
        navigation->step();
        vTaskDelay(pdMS_TO_TICKS(100));
    }

}
