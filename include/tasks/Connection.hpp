#pragma once

#ifndef CONNECTION_HPP
#define CONNECTION_HPP

void wifiMonitorTask(void* pvParameters)
void TaskRouteReceiver(void* pvParameters);
void TaskSensorReader(void* pvParameters);
void TaskDataSender(void* pvParameters);

#endif