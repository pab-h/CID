#pragma once

#include <Arduino.h>
#include <DHT.h>


namespace drivers{

    class TempSensor{

        private:
            
            DHT *dht;
            uint8_t pin;

        public:

            TempSensor(u_int8_t pin);

            void begin();
            float readTemperature(bool fahrenheiy = false, bool force = false) const;
            float readHumidity(bool force = false) const;
            bool isReady() const;

    };

}