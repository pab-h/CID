#pragma once

#include <Arduino.h>

namespace drivers{

    class TempSensor{

        private:

            uint8_t pin;

        public:

            TempSensor(u_int8_t pin);

            float readTemp();
            float readHumidity();

    };

}