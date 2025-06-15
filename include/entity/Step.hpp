#pragma once

#include <Arduino.h>

namespace entity {

    class Step {
        
        public:
        
            uint     howLong;
            uint16_t atAngle;
            bool     isMeasure;


            Step();
            Step(uint howLong, uint16_t atAngle, bool isMeasure);

    };

}
