#pragma once

#include <Arduino.h>

namespace tasks {

    extern TaskHandle_t xSystemStatusTaskHandle;

    /**
     * @brief Task that updates the system status and the display every 5 seconds.
     */
    void vSystemStatusTask(void* pvParameters);

}