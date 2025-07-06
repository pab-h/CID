#pragma once

#include <Arduino.h>

namespace entity {

    class SensorData {
        
        public:
            float temperature;
            float moisture;
            int luminosity;
            // int motorVelocity;
            // String cameraImagemBase64;
            
            SensorData(); 

            SensorData(float temperature, float moisture, int luminosity); // Construtor com parâmetros
    };
}
