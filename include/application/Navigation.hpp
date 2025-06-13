#include "drivers/DcMotor.hpp"
#include "drivers/RotaryEncoder.hpp"

#include "entity/Reference.hpp"

using namespace drivers;
using namespace entity;

namespace application {
    
    class Navigation {

        private:

            Reference* travel;
            uint       travelLenght;

            DcMotor* motorLeft;
            DcMotor* motorRight;

            RotaryEncoder* hodometer;

        public:

            Navigation();
            ~Navigation();

    };

}