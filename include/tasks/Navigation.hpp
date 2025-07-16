#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

namespace tasks {

    TaskHandle_t xNavigationSetInsertionStateTaskHandle;
    TaskHandle_t xNavigationSetDisinsertionStateTaskHandle;

    void vNavigationTask(void* pvParameters);
    void vUpdateRotaryEncoderTask(void* pvParameters);
    void vNavigationNotificationsTask(void* pvParameters);
    void vNavigationSetInsertionStateTask(void* pvParameters);
    void vNavigationSetDisinsertionStateTask(void* pvParameters);

}
