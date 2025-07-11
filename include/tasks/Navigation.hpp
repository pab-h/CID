#pragma once

#include <freertos/queue.h>

namespace tasks {

    QueueHandle_t xTravelQueue;

    void vNavigationTask(void* pvParameters);
    void vUpdateRotaryEncoderTask(void* pvParameters);
    void vNavigationNotificationsTask(void* pvParameters);
    void vUpdateTravelNavigationTask(void* pvParameters);

}
