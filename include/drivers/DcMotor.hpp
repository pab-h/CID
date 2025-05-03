#pragma once

#include <Arduino.h>

namespace drivers {

    /**
     * É assumido que esteja usando uma ponte-H
     */
    
    class DcMotor {

        private:

            uint8_t en;

            uint8_t inl;
            uint8_t inr;

            uint8_t power;

        public:

            DcMotor(u_int8_t en, u_int8_t inl, u_int8_t inr);

            void clockwise();
            void counterclockwise();
            
            void setPower(u_int8_t pwm);

            void disable();
            void enable();
            
    };

}
