#include "tasks/SystemStatus.hpp"
#include "application/SystemStatus.hpp"
#include "globals.hpp"
#include "pins.hpp"

using namespace application;

namespace tasks {

    TaskHandle_t xSystemStatusTaskHandle = nullptr;

    void vSystemStatusTask(void* pvParameters) {

        const int batteryAdcPin = BATERY_PIN;  

        while (true) {

            // usar namespace globals?
            systemStatus.measureAndUpdateBatteryLevel(batteryAdcPin);
            systemStatus.updateConnectionFromWiFi();

            display.updateFromSystemStatus(systemStatus);

            //Enviar os dados para o sistema web

            vTaskDelay(pdMS_TO_TICKS(2000));
        }
    }

}
