#include <freertos/FreeRTOS.h>
#include "application/Navigation.hpp"
#include "tasks/Navigation.hpp"

using namespace application;
using namespace drivers;
using namespace tasks;

void tasks::vNavigationNotificationsTask(void* pvParameters) {

    Navigation*    navigation    = static_cast<Navigation*>(pvParameters);
    Notifications* notifications = navigation->getNotifications();

    while (true) {

        if (navigation->getState() == State::WAITING_MEASURE && !notifications->isMeasureSend) {

            // xTaskNotify

            notifications->isMeasureSend = true;
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
