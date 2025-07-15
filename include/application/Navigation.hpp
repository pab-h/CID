#pragma once

#include "entity/Travel.hpp"

#include "drivers/DcMotor.hpp"
#include "drivers/RotaryEncoder.hpp"

using namespace drivers;
using namespace entity;

namespace application {

    enum States {
        PULLING      ,
        FORWARD      ,
        WAITING      ,
        INSERTING    ,
        DISINSERTION ,
        SPINNING     ,
    };

    class Notifications {
        public: 

            bool isSendWaitingAlert;
            bool isSendInsertinDoneAlert;
            bool isSendDesinsertinDoneAlert;

    };

    class Navigation {

        private:

            DcMotor       motorLeft;
            DcMotor       motorRight;
            RotaryEncoder hodometer;

            Notifications notifications;
            States        state;
            Travel*       travel;
            Step*         currentStep;
            uint16_t      direction;
            int           lastStepPosition;

            
            int  getLastStepDistance();
            int  getMisalignment();
            void pulling();
            void forward();
            void spinning();
            void waiting();
            void inserting();
            void disinserting();

        public:

            Navigation();
            ~Navigation();

            RotaryEncoder* getRotaryEncoder();
            Notifications* getNotifications();
            void           setTravel(Travel* travel);
            void           step();

    };

}