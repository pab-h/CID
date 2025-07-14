#pragma once
#include <freertos/task.h>


namespace tasks{
    
    /// Queue used for sending messages (status or sensor data) to the API service.
    extern QueueHandle_t apiQueue;

    extern TaskHandle_t sensorReaderHandle;
    extern TaskHandle_t dataSenderHandle;

    void wifiMonitorTask(void* pvParameters);
    void TaskRouteReceiver(void* pvParameters);
    void TaskSensorReader(void* pvParameters);
    void TaskDataSender(void* pvParameters);
    void TaskApiDispatcher(void* pvParameters);

} 

