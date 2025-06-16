#include <freertos/FreeRTOS.h>
#include "application/Navigation.hpp"
#include "tasks/navigation.hpp"

using namespace application;

void tasks::vNavigationTask(void* pvParameters) {
    
    Navigation* navigation = static_cast<Navigation*>(pvParameters);

    while (true) {
        navigation->step();
        vTaskDelay(pdMS_TO_TICKS(3));
    }

}

void tasks::vUpdateRotaryEncoderTask(void* pvParameters) {
    
    Navigation* navigation = static_cast<Navigation*>(pvParameters);
    
    while (true) {
        navigation->getRotaryEncoder()->read();
        vTaskDelay(pdMS_TO_TICKS(3));
    }

}
