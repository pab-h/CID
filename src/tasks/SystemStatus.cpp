#include "tasks/SystemStatus.hpp"
#include "application/SystemStatus.hpp"
#include "tasks/Connection.hpp"
#include "application/ApiService.hpp"
#include "globals.hpp"
#include "pins.hpp"

using namespace application;

namespace tasks {

    TaskHandle_t xSystemStatusTaskHandle = nullptr;

    void vSystemStatusTask(void* pvParameters) {

        while (true) {

            systemStatus.measureAndUpdateBatteryLevel(BATTERY_PIN);
            systemStatus.setConnectionLevel(api.getSignalLevel());

            display.updateFromSystemStatus(systemStatus);

            application::ApiMessage msg;
            msg.type = application::ApiRequestType::SendStatus;
            msg.status = systemStatus.getStatusData();

            if (xQueueSend(tasks::apiQueue, &msg, 0) != pdTRUE) {
                Serial.println("[SystemStatusTask] Fila cheia, status não enviado");
            }

            vTaskDelay(pdMS_TO_TICKS(5000));
    
        }
    }

}
