#pragma once

#include "drivers/DcMotor.hpp"
#include "drivers/RotaryEncoder.hpp"

#include "entity/Travel.hpp"

using namespace drivers;
using namespace entity;

namespace application {
    
    class Navigation {

        private:

            DcMotor* motorLeft;
            DcMotor* motorRight;

            RotaryEncoder* hodometer;

            Travel* travel;

            

        public:

            Navigation();
            ~Navigation();

            void setTravel(Travel* travel);
            void step();

    };

}