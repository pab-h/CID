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

<<<<<<< HEAD
            DcMotor(u_int8_t en, u_int8_t inl, u_int8_t inr);
            //motor angle como parametro da função de rodar
=======
            DcMotor(uint8_t en, uint8_t inl, uint8_t inr);

>>>>>>> feat/wifi-module
            void clockwise();
            void counterclockwise();
            
            void setPower(uint8_t pwm);

            void disable();
            void enable();
            
    };

}
