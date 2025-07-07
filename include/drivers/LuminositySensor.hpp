#pragma once

#include <Arduino.h>
#include <pins.hpp>

namespace drivers{


    /**
     * @brief Driver for analog luminosity sensor.
     * 
     * This class provides methods to read raw and percentage values from
     * an analog LuminositySensor. Supports manual calibration.
     */
    class LuminositySensor{

        private:

            uint8_t pin; ///< Analog pin conected to sensor
            uint16_t minValue; ///< Calibrated value for dry soil.
            uint16_t maxValue; ///< Calibrated value for wet soil.
            bool calibrated; ///< Indicates if sensor is been calibrated.

        public:

            /**
             * @brief Construct a new LuminositySensor object.
             * 
             * @param pin Analog pin number where the sensor is connected.
             */
            LuminositySensor(u_int8_t pin = LDR_PIN);

            /**
             * @brief Read raw analogic value from the sensor.
             */
            uint16_t read();

            /**
            * @brief Read soil sensor value as a percentage.
            * 
            * Uses minValue and maxValue to map the raw reading to 0-100%.
            * 
            * Return uint_8 Percentage of luminosity (0 = darkest, 100% = brightest).
            */
            uint8_t readPercentage();


            /**
             * @brief  Calibrate the LDR sensor readings.
             * 
             * Sets the minimum and maximum expected analog values for the LDR sensor,
             * which are used to normalize light levels into a percentage.
             * 
             * @param minValue ADC value corresponding to darkest condition (lowest light).
             * @param maxValue ADC value corresponding to brightest condition (highest light).
             */
            void calibrate(uint16_t minValue, uint16_t maxValue);

    };

}