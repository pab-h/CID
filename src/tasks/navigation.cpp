// #include <freertos/FreeRTOS.h>
#include "application/Navigation.hpp"

using namespace application;

void vNavigationTask(void* pvParaments) {

    Navigation* navigation = (Navigation*) pvParaments;

    while(true) {

        navigation->step();
        // vTaskDelay(pdMS_TO_TICKS(3));
    
    }

}

void vUpdateRotaryEncoderTask(void* pvParaments) {
    
    Navigation* navigation = (Navigation*) pvParaments;

    while(true) {

        navigation->getRotaryEncoder()->read();
        // vTaskDelay(pdMS_TO_TICKS(3));
    
    }

}
