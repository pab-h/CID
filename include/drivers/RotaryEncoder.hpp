#pragma once

#include <Arduino.h>

namespace drivers {

    class RotaryEncoder {

        private:

            /*
            * siga: Signal of change
            * sigb: Signal of direction change
            */

            u_int8_t siga;
            u_int8_t sigb;

            int position;

            bool lastSigaState;
            bool currentSigaState;

        public:

            RotaryEncoder(u_int8_t siga, u_int8_t sigb);

            /**
             * If possible, link read to a change 
             * interrupt using siga pin for better
             * precision
             */
            void read();
            int  getPosition();

    };
    

}
