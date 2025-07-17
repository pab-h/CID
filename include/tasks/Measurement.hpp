#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

namespace tasks{

    /*Handles*/

    /**
     * @brief Handle for the temperature and humidity measurement task (DHT11).
     */
    extern TaskHandle_t xMeasureTempHumTaskHandle;

    /**
     * @brief Handle for the soil moisture measurement task.
     */
    extern TaskHandle_t xMeasureSoilMoistureTaskHandle;

    /**
     * @brief Handle for the luminosity (LDR) measurement task.
     */
    extern TaskHandle_t xMeasureLuminosityTaskHandle;

    /**
     * @brief Handle for the picture task.
     */
    extern TaskHandle_t xTakePictureTaskHandle;

    /**
     * @brief Handle for the sensor manager task.
     */
    extern TaskHandle_t xSensorManagerTaskHandle;


    /*TASKS*/


    /**
     * @brief High-priority task responsible for reading temperature and humidity using a DHT11 sensor.
     * 
     * This task waits for a notification to start. It ensures a minimum interval between measurements,
     * performs temperature and humidity readings, and notifies the sensor manager task upon completion.
     * 
     * @param pvParameters Not used directly.
     */
    void vMeasureTemperatureHumidityTask(void* pvParameters);


    /**
     * @brief Task responsible for measuring soil moisture.
     * 
     * This task waits for a notification to start, performs the reading,
     * and notifies the sensor manager task when done.
     * 
     * @param pvParameters Not used directly.
     */
    void vMeasureSoilMoistureTask(void* pvParameters);

    /**
     * @brief Task responsible for measuring luminosity using an LDR.
     * 
     * This task waits for a notification to start, performs the reading,
     * and notifies either the sensor manager task or the main loop task.
     * 
     * @param pvParameters May contain the handle of the main loop task to be notified.
     */
    void vMeasureLuminosityTask(void* pvParameters);

    //void vTakePictureTask(void* pvParameters);

    /**
     * @brief Task responsible for coordinating the execution of all sensor measurement tasks.
     * 
     * This task manages the ordered execution of temperature/humidity, soil moisture,
     * and luminosity measurements by sending and waiting for notifications.
     * It will notify the main task (loop) after all measurements are complete.
     * 
     * @param pvParameters May contain the handle of the main loop task to be notified.
     */
    void vSensorManagerTask(void* pvParameters);
    
}