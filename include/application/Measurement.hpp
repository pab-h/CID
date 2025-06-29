#pragma once

#include "drivers/TempHumSensor.hpp"
#include "drivers/LuminositySensor.hpp"
#include "drivers/MoistureSensor.hpp"


using namespace drivers;

namespace application{
    
    /** 
     * @brief Enumeration representing possible errors in measurements.
     * Each value indicates a specific type of fault or condition.
     */
    enum class MeasurementError {
        NONE                = 0,        /**< No error */
        BUSY                = 1,        /**< Sensor busy */
        INCOMPLETE          = 1<<1,     /**< The measures are not yet complete */
        TEMPERATURE_FAIL    = 1<<2,     /**< Temperature measurement failed */
        HUMIDITY_FAIL       = 1<<3,     /**< Humidity measurement failed  */
        MOISTURE_FAIL       = 1<<4,     /**< Soil moisture measurement failed */
        LUMINOSITY_FAIL     = 1<<5,     /**< Brightness measurement failed */
        //CAMERA_FAIL         = 1<<6      /**< Camera capture failed */
    };

    /**
     * @brief Structure that stores the data collected from the sensors.
     */
    struct SensorData{
        float temperature = 0.0;    /**< Temperature in °C */
        float humidity = 0.0;       /**< Air humidity % */
        uint16_t soilMoisture = 0;  /**< Soil moisture (normalizated %) */
        uint16_t luminosity = 0;    /**< Luminosity (normalizated %) */
    };

    /**
     * @brief Structure representing the current status of sensors.
     */
    struct SensorStatus{
        bool isSensing = false;         /**< Indicates if measurements are in progress */
        bool temperatureReady = false;  /**< Indicates temperature measurement completed */
        bool humidityReady = false;     /**< Indicates humidity measurement completed */
        bool moistureReady = false;     /**< Indicates soil moisture measurement completed */
        bool luminosityReady = false;   /**< Indicates luminosity measurement completed */
        bool pictureReady = false;      /**< Indicates picture capture completed */

        uint8_t error = static_cast<uint8_t>(MeasurementError::NONE); /**< Current error flags */
    };

    /**
     * @brief Structure used to return measurement results and errors.
     */
    struct MeasurementResponse{
        SensorData data;               /**< Sensor measurement data */
         uint8_t error = static_cast<uint8_t>(MeasurementError::NONE); /**< Detected errors */
    };

    /**
     * @brief Class responsible for performing sensor measurements.
     * 
     * Provides methods for measuring temperature, humidity, luminosity, and soil moisture,
     * as well as managing states and errors.
     */
    class Measurement {

        private:

            SensorData sensorData;       /**< Collected sensor data */
            SensorStatus sensorStatus;   /**< Current sensor status */

            drivers::TempSensor dht;         /**< Temperature and humidity sensor */
            drivers::LuminositySensor ldr;   /**< Luminosity sensor */
            drivers::MoistureSensor soil;    /**< Soil moisture sensor */

            /**
             * @brief Converts a MeasurementError enum value to its underlying uint8_t representation.
             * @param err The MeasurementError to convert.
             * @return The uint8_t bitmask of the error.
             */
            inline uint8_t to_uint8(MeasurementError err);

            /**
             * @brief Checks if a specific error flag is set.
             * @param flags Current error flags.
             * @param error Error flag to check.
             * @return True if the error flag is present, false otherwise.
             */
            inline bool hasError(uint8_t flags, MeasurementError error);

            /**
             * @brief Adds an error flag to the current flags.
             * @param flags Reference to the current error flags to modify.
             * @param error Error flag to add.
             */
            inline void addError(u_int8_t &flags, MeasurementError error);

            /**
             * @brief Removes an error flag from the current flags.
             * @param flags Reference to the current error flags to modify.
             * @param error Error flag to remove.
             */
            inline void removeError(u_int8_t &flags, MeasurementError error);

            /**
             * @brief Prints all active error flags in human-readable form.
             *
             * This function receives the raw 8-bit error flags and prints the names
             * of each error currently set.
             *
             * @param flags Bitmask representing the current measurement errors.
             */
            void printErrors(uint8_t flags);

        public: 

            /**
             * @brief Default constructor. Initializes sensors.
             */
            Measurement();

            /**
             * @brief Resets all internal states, clearing data, status, and errors.
             */
            void resetStates();

            /**
             * @brief Checks if all measurements are complete and ready.
             * @return True if all sensors have finished measurements successfully.
             */
            bool isAllReady() const;  

            /**
             * @brief Performs temperature measurement.
             */
            void measureTemperature();
            
            /**
             * @brief Performs humidity measurement.
             */
            void measureHumidity();

            /**
             * @brief Performs luminosity measurement.
             */
            void measureLuminosity();

             /**
             * @brief Performs soil moisture measurement.
             */
            void measureMoisture();

            /**
             * @brief Returns the current measurement data and any errors.
             * @return A MeasurementResponse containing sensor data and errors.
             */
            MeasurementResponse getMeasures();

    };

};
