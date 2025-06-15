#pragma once

#include <Arduino.h>

#include "entity/Step.hpp"

namespace entity {

    class Travel {
        
        private:

            Step* steps;
            uint  lenght;
            uint  current;

        public: 

            Travel(Step* steps, uint lenght);

            Step* nextStep();

    };

}
