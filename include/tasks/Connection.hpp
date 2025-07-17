#pragma once
#include <freertos/task.h>

namespace tasks {

    /// @brief Queue used to send API requests containing sensor or status data.
    extern QueueHandle_t apiQueue;

    /// @brief Task handle for the sensor reading task.
    extern TaskHandle_t sensorReaderHandle;

    /// @brief Task handle for the data sender task.
    extern TaskHandle_t dataSenderHandle;

    /**
     * @brief Periodically checks Wi-Fi connection status and attempts reconnection if disconnected.
     * 
     * @param pvParameters Pointer to the ApiService instance.
     */
    void wifiMonitorTask(void* pvParameters);

    /**
     * @brief Downloads a new route from the API after confirming Wi-Fi is connected.
     *        Deletes itself after execution.
     * 
     * @param pvParameters Pointer to the ApiService instance.
     */
    void TaskRouteReceiver(void* pvParameters);

    /**
     * @brief Reads sensor data, generates the JSON, and prints it to Serial.
     *        Designed for single execution and deletes itself after running.
     * 
     * @param pvParameters Pointer to the ApiService instance.
     */
    void TaskSensorReader(void* pvParameters);

    /**
     * @brief Placeholder task for sending data to the API. Currently prints a message and exits.
     * 
     * @param pvParameters Unused.
     */
    void TaskDataSender(void* pvParameters);

    /**
     * @brief Listens to the API queue and dispatches messages to the appropriate API method
     *        depending on their type (measurement or status).
     * 
     * @param pvParameters Unused.
     */
    void TaskApiDispatcher(void* pvParameters);

}
