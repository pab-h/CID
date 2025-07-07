#pragma once

#include <Arduino.h>

namespace tasks {

    extern TaskHandle_t xSystemStatusTaskHandle;

    /**
     * @brief Task que atualiza o status do sistema e o display a cada 2 segundos.
     */
    void vSystemStatusTask(void* pvParameters);

}