#pragma once

#include "drivers/DcMotor.hpp"
#include "drivers/RotaryEncoder.hpp"

#include "entity/Travel.hpp"

using namespace drivers;
using namespace entity;

namespace application {
    
    enum class State   {
        IDLE           ,
        MOVING         ,
        TURNING        ,
        WAITING_MEASURE
    };
    
    class Notifications {
        public:
            bool isMeasureSend;
    };

    class Navigation {

        private:

            Notifications notifications;

            DcMotor*       motorLeft;
            DcMotor*       motorRight;
            RotaryEncoder* hodometer;

            State   state;
            float   angle;
            float   startAngle;
            Travel* travel;
            Step*   currentStep;
            int     startPosition;

            void stepIdle();
            void stepMoving();
            void stepTurning();
            void stepWaiting();

            void setupRotateMotors();
            void setupForwardMotors();

        public:

            Navigation();
            ~Navigation();

            RotaryEncoder* getRotaryEncoder();
            State          getState();
            Notifications  getNotifications();

            void updateAngle(uint pulses);
            void setTravel(Travel* travel);
            void step();

    };

}