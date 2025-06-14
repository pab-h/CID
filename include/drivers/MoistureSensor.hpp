#pragma once

#include <Arduino.h>

namespace drivers{

    class MoistureSensor{
        
        /**
         * @brief Driver for analog soil moisture sensor.
         * 
         * This class provides methods to read raw and percentage values from
         * an analog soil moisture sensor. Supports manual calibration.
         */

        private:
        
            uint8_t pin; ///< Analog pin conected to sensor
            u_int16_t minValue; ///< Calibrated value for dry soil.
            u_int16_t maxValue; ///< Calibrated value for wet soil.
            bool calibrated; ///< Indicates if sensor is been calibrated.

        public:
            
            /**
             * @brief Construct a new MoistureSensor object.
             * 
             * @param pin Analog pin number where the sensor is connected.
             */
            MoistureSensor(uint8_t pin);

            /**
             * @brief Read raw analogic value from the sensor.
             */
            uint16_t read();

            /**
            * @brief Read soil sensor value as a percentage.MoistureSensor
            * 
            * Uses minValue and maxValue to map the raw reading to 0-100%.MoistureSensor
            * 
            * Return uint_16 Percentage of moisure (0 = full dry, 100% = full wet).
            */
            uint8_t readPercentage();


            /**
            * @brief  Calibrate the sensor readings.MoistureSensor
            * 
            * Sets the mininum and maximum expected values from the sensor.
            * 
            * @param minValue ADC value corresponding to dry soil.
            * @param maxValue ADC value corresponding to wet soil.
            */
            void calibrate(uint16_t minValue, uint16_t maxValue);

        };
}