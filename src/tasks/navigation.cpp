#include <freertos/FreeRTOS.h>

#include "application/Navigation.hpp"
#include "tasks/navigation.hpp"

using namespace application;
using namespace drivers;

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
