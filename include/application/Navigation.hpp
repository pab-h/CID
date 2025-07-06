#pragma once

#include "drivers/DcMotor.hpp"
#include "drivers/RotaryEncoder.hpp"

#include "entity/Travel.hpp"

using namespace drivers;
using namespace entity;

namespace application {
    
    enum class NavigationState {
        IDLE   ,
        MOVING ,
        TURNING
    };

    class Navigation {

        private:

            DcMotor* motorLeft;
            DcMotor* motorRight;
            RotaryEncoder* hodometer;

            NavigationState state;
            float           angle;
            float           startAngle;
            Travel*         travel;
            Step*           currentStep;
            int             startPosition;

            void stepIdle();
            void stepMoving();
            void stepTurning();

            void setupRotateMotors();
            void setupForwardMotors();

        public:

            Navigation();
            ~Navigation();

            RotaryEncoder* getRotaryEncoder();
            void updateAngle(uint pulses);
            void setTravel(Travel* travel);
            void step();


    };

}