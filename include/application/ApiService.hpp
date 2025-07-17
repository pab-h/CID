#pragma once

#include "entity/Step.hpp"  
#include "application/Measurement.hpp" 
#include "SystemStatus.hpp"
#include <ArduinoJson.h> 

#include "drivers/Wifi.hpp"

using namespace entity;

namespace application {

    /**
     * @brief Enumerates the types of requests that can be sent via the API.
     */
    enum class ApiRequestType {
        SendMeasurement,  /**< Represents a request to send sensor measurement data */
        SendStatus        /**< Represents a request to send system status data */
    };

    /**
     * @brief Structure that encapsulates a message to be sent to the API dispatcher.
     * 
     * Depending on the value of `type`, only one of the following fields will be used:
     * - If `type == SendMeasurement`, the `measurement` field is valid.
     * - If `type == SendStatus`, the `status` field is valid.
     */
    struct ApiMessage {
        ApiRequestType type;                /**< Type of the API request */
        MeasurementResponse measurement;    /**< Sensor measurement data (valid if type == SendMeasurement) */
        StatusData status;                  /**< System status data (valid if type == SendStatus) */
    };

    /**
     * @brief Class responsible for the API service, including Wi-Fi connection,
     *        JSON data handling, sending and receiving.
     */
    class ApiService {

        private:

            WifiDriver* wifi;  /**< Driver for Wi-Fi connection */

        public:

            /**
             * @brief Default constructor for ApiService class.
             */
            ApiService();

            /**
             * @brief Initializes Wi-Fi connection with given SSID and password.
             * 
             * @param ssid Wi-Fi network name.
             * @param password Wi-Fi network password.
             */
            void begin(String ssid, String password);

            /**
             * @brief Returns the pointer to the Wi-Fi driver in use.
             * 
             * @return Pointer to WifiDriver.
             */
            WifiDriver* getWifi();

            /**
             * @brief Gets the current Wi-Fi signal strength level (0–4).
             * 
             * RSSI is mapped into:
             * - ≥ -50 dBm → 4 (excellent)
             * - ≥ -60 dBm → 3 (good)
             * - ≥ -70 dBm → 2 (fair)
             * - ≥ -80 dBm → 1 (weak)
             * - < -80 dBm → 0 (very weak)
             * 
             * @return uint8_t Signal strength level.
             */
            uint8_t getSignalLevel();

            /**
             * @brief Generates a JSON string from the measurement response.
             * 
             * @param resp Constant reference to the measurement response structure.
             * @return String containing the formatted JSON.
             */
            String generateJson(const MeasurementResponse& resp);

            /**
             * @brief Generates a JSON string from the System Status.
             * 
             * @param resp Constant reference to the measurement StatusData structure.
             * @return String containing the formatted JSON.
             */
            String generateJson(const StatusData& status);

            /**
             * @brief Deserializes a JSON buffer into a dynamic array of Steps.
             * 
             * @param jsonBuffer Buffer containing JSON to be deserialized.
             * @param stepsOut Reference to the pointer that will receive the allocated Steps array.
             * @param countOut Reference to the variable that will receive the number of Steps deserialized.
             * @return true if deserialization succeeds, false otherwise.
             */
            bool deserializeSteps(const char* jsonBuffer, Step*& stepsOut, uint& countOut);

            /**
             * @brief Example method to download JSON from an external API, deserialize it,
             *        and notify the sensor reading task.
             */
            void testDownloadJson();

            /**
             * @brief Sends measurement data to the API, serializing it as JSON.
             * 
             * @param resp Structure containing measurement data to send.
             */
            void sendDataToApi(const MeasurementResponse& resp);

            /**
             * @brief Sends StatusData to the API, serializing it as JSON.
             * 
             * @param resp Structure containing measurement data to send.
             */
            void sendDataToApi(const StatusData& status);

    };

}