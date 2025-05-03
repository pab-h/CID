#pragma once

#include <Arduino.h>

namespace drivers {

    class RotaryEncoder {

        private:

            /*
            * siga: Signal of change
            * sigb: Signal of direction change
            */

            uint8_t siga;
            uint8_t sigb;

            int position;

            bool lastSigaState;
            bool currentSigaState;

        public:

            RotaryEncoder(uint8_t siga, uint8_t sigb);

            /**
             * If possible, link read to a change 
             * interrupt using siga pin for better
             * precision
             */
            void read();
            int  getPosition();

    };
    

}
