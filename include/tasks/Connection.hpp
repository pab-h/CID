#pragma once

#ifndef CONNECTION_HPP
#define CONNECTION_HPP

void wifiConnectAndSend();
void TaskWiFiManager(void* pvParameters);
void TaskRouteReceiver(void* pvParameters);
void TaskSensorReader(void* pvParameters);
void TaskDataSender(void* pvParameters);

#endif