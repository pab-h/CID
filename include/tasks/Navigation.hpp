#pragma once

#include <freertos/FreeRTOS.h>

namespace tasks {

    extern TaskHandle_t xNavigationSetInsertionStateTaskHandle;
    extern TaskHandle_t xNavigationSetDisinsertionStateTaskHandle;

    void vNavigationTask(void* pvParameters);
    void vUpdateRotaryEncoderTask(void* pvParameters);
    void vNavigationNotificationsTask(void* pvParameters);
    void vNavigationSetInsertionStateTask(void* pvParameters);
    void vNavigationSetDisinsertionStateTask(void* pvParameters);

}
