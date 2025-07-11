#pragma once
#include <freertos/task.h>

extern TaskHandle_t sensorReaderHandle;
extern TaskHandle_t dataSenderHandle;

void wifiMonitorTask(void* pvParameters);
void TaskRouteReceiver(void* pvParameters);
void TaskSensorReader(void* pvParameters);
void TaskDataSender(void* pvParameters);