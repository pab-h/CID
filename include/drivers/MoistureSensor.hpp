#pragma once

#include <Arduino.h>

namespace drivers{

    class MoistureSensor{

        private:
        
            uint8_t pin;

            int offset;
            int minValue;
            int maxValue;
            
            bool calibrated;

        public:

            MoistureSensor(uint8_t pin);

            int read();
            int readPercentage();

            void calibrate(int offset, int minValue, int maxValue);

        };
}