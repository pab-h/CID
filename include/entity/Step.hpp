#pragma once

#include <Arduino.h>

namespace entity {

    class Step {
        
        public:
        
            uint     distance;
            uint16_t direction;
            String   sector;   
            bool     toMeasure;

            Step();

    };

}
