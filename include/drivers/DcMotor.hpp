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
            uint8_t pwmChannel;
            
            uint8_t power;

        public:

            DcMotor();

            void setup(uint8_t en, uint8_t inl, uint8_t inr, uint8_t pwmChannel);

            void clockwise();
            void counterclockwise();
            
            void setPower(uint8_t pwm);
            void enable();
            void disable();
            
    };

}
