#pragma once

#include <Arduino.h>

namespace drivers {

    /**
     * It is assumed that you are using an H-bridge
     */
    
    class DcMotor {

        private:

            uint8_t en;

            uint8_t inl;
            uint8_t inr;

            uint8_t power;

        public:

            DcMotor(uint8_t en, uint8_t inl, uint8_t inr);

            void clockwise();
            void counterclockwise();
            
            void setPower(uint8_t pwm);

            void disable();
            void enable();
            
    };

}
