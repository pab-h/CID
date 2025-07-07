#pragma once

#include <Arduino.h>

namespace entity {

    class SensorData {
        
        public:
            float temperature;
            float moisture;
            int luminosity;
            float humidity;
            // int motorVelocity;
            // String cameraImagemBase64;
            
            SensorData(); 

            SensorData(float temperature, float moisture, int luminosity, float humidity); // Construtor com parâmetros
    };
}
