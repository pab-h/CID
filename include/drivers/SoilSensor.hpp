#pragma once

#include <Arduino.h>

namespace sensors{

    class SoilSensor{

    private:
    
        uint8_t pin;

        int offset;
        int minValue;
        int maxValue;
        
        bool calibrated;

    public:

        SoilSensor(uint8_t pin);

        int read();
        int readPercentage();

        void calibrate(int offset, int minValue, int maxValue);

    };
}