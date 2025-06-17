#pragma once

#include "drivers/Camera.hpp"
#include "drivers/TempSensor.hpp"
#include "drivers/LuminositySensor.hpp"
#include "drivers/MoistureSensor.hpp"


using namespace drivers;

namespace application{
    
    enum class MeasurementError {
        NONE            ,
        BUSY            ,
        INCOMPLETE      ,
        TEMPERATURE_FAIL,
        HUMIDITY_FAIL   ,
        MOISTURE_FAIL   ,
        LUMINOSITY_FAIL ,
        CAMERA_FAIL     ,
    };

    struct SensorData{
        float temperature = 0.0;
        float humidity = 0.0;
        uint16_t soilMoisture = 0;
        uint16_t luminositySensor = 0;
        camera_fb_t* image = nullptr;
    };

    struct SensorStatus{
        bool isSensing = false;
        bool temperatureReady = false;
        bool humidityReady = false;
        bool moistureReady = false;
        bool luminosityReady = false;
        bool pictureReady = false;

        MeasurementError error = MeasurementError::NONE;
    };

    struct MeasurementResponse{
        SensorData data;
        MeasurementError error = MeasurementError::NONE;
    };

    //Quando medir a temperatura e umidade do ar, precisa ficar parado apenas nessa função

    class Measurement {

        private:

            SensorData sensorData;
            SensorStatus sensorStatus;

            drivers::TempSensor dht;
            drivers::LuminositySensor ldr;
            drivers::MoistureSensor soil;
            //drivers::CameraOV7670 camera;

        public: 

            Measurement();

            void resetStates();
            bool isAllReady() const;  

            void measureTemperature();
            void measureUmidity();
            void measureLuminosity();
            void measureMoisture();
            void prepareCamera();
            void takePicture();

            MeasurementResponse getMeasures();

    };

};
