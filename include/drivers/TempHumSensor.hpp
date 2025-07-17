#pragma once

#include <Arduino.h>
#include <pins.hpp>
#include <DHT.h>

namespace drivers{

    /**
     * @brief Driver for DHT temperature and humidity sensors.
     * 
     * This class wraps the DHT library to provide easy access to temperature and humidity
     * readings, as well as initialization and sensor readiness checking.
     */
    class   TempHumSensor{

        private:
            
            DHT *dht; ///< Pointer to internal DHT sensor object
            uint8_t pin; ///< Digital pin where the DHT sensor is connected

        public:

            /**
             * @brief Construct a new TempSensor object
             * 
             * @param pin GPIO pin connected to the DHT data pin (default is TEMP_PIN from pins.hpp)
             */
            TempHumSensor(uint8_t pin = TEMP_PIN);

            /**
             * @brief Initializes the DHT sensor.
             * 
             * This method must be called before reading temperature or humidity.
             */
            void begin();

            /**
             * @brief Reads temperature from the sensor.
             * 
             * @param fahrenheit If true, returns temperature in Fahrenheit. Otherwise, in Celsius.
             * @param force If true, forces a reading even if recent data is available.
             * @return float Temperature in °C or °F depending on parameter.
             */
            float readTemperature(bool fahrenheiy = false, bool force = false) const;

             /**
             * @brief Reads humidity from the sensor.
             * 
             * @param force If true, forces a reading even if recent data is available.
             * @return float Relative humidity percentage (0.0 to 100.0)
             */
            float readHumidity(bool force = false) const;

            /**
             * @brief Checks if the sensor is ready to be read.
             * 
             * @return true if the sensor is initialized and functional.
             * @return false if the sensor is not initialized or failed to respond.
             */
            bool isReady() const;

    };

}