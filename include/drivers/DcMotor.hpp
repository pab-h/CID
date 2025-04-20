#pragma once

#include <Arduino.h>

namespace drivers {

    /**
     * É assumido que esteja usando uma ponte-H
     */
    
    class DcMotor {

        private:

            u_int8_t en;

            u_int8_t inl;
            u_int8_t inr;

        public:

            DcMotor(u_int8_t en, u_int8_t inl, u_int8_t inr);

            void clockwise();
            void counterclockwise();
            
            void power(u_int8_t pwm);
            void disable();
            
    };

}
