#include <Arduino.h>

#include "drivers/RotaryEncoder.hpp"
#include "application/Navigation.hpp"
#include "entity/Travel.hpp"

#include "pins.hpp"

using namespace application;
using namespace drivers;
using namespace entity;

Navigation     nav;
RotaryEncoder* encoder;

const char* stateToString(NavigationState state) {

    switch (state) {
        case    NavigationState::IDLE    : return "IDLE";
        case    NavigationState::MOVING  : return "MOVING";
        case    NavigationState::TURNING : return "TURNING";
        default                          : return "UNKNOWN";
    }

}

void setup() {

    Serial.begin(9600);

    Step* steps = new Step[3];
    
    steps[0] = Step(1, 0, false);
    steps[1] = Step(2, 0, false);
    steps[2] = Step(3, 0, false);

    Travel* travel = new Travel(steps, 3);

    nav.setTravel(travel);

    encoder = nav.getRotaryEncoder();

    delay(2000);
    Serial.println("Iniciando o teste");

}

void loop() {

    encoder->read();
    nav.step();

    Serial.print("STATE            = " + String(stateToString(nav.getState())) + " ");
    Serial.print("POSITION ENCODER = " + String(encoder->getPosition())        + "\n");

    delay(250);

}