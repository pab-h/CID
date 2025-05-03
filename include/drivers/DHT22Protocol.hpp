#pragma once

#include <Arduino.h>

namespace drivers{

    struct DHT22Data{

        uint8_t bytes[5];
        bool success;

    };

    class DHT22Protocol{

        private:

            bool waitForLevel(uint8_t pin, uint8_t level, uint32_t timeout_us);
            bool verifyChecksum(const uint8_t data[5]);

        public:

            DHT22Data read(uint8_t pin);

    };

}