#include "tasks/SystemStatus.hpp"
#include "application/SystemStatus.hpp"
#include "globals.hpp"
#include "pins.hpp"

using namespace application;

namespace tasks {

    TaskHandle_t xSystemStatusTaskHandle = nullptr;

    void vSystemStatusTask(void* pvParameters) {

        while (true) {

            systemStatus.measureAndUpdateBatteryLevel(BATTERY_PIN);
            systemStatus.updateConnectionFromWiFi();

            display.updateFromSystemStatus(systemStatus);

            //Enviar os dados para o sistema web

            vTaskDelay(pdMS_TO_TICKS(5000));
    
        }
    }

}
