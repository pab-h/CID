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

void setup() {

    Serial.begin(9600);

    Step* steps = new Step[3];
    
    steps[0]           = Step();
    steps[0].distance  = 1;
    steps[0].direction = 0;
    steps[0].sector    = "";
    steps[0].toMeasure = false;

    steps[1]           = Step();
    steps[1].distance  = 5;
    steps[1].direction = 0;
    steps[1].sector    = "Brazil";
    steps[1].toMeasure = true;

    steps[2]           = Step();
    steps[2].distance  = 10;
    steps[2].direction = 10;
    steps[2].sector    = "";
    steps[2].toMeasure = false;


    Travel* travel = new Travel(steps, 3);

    nav.setTravel(travel);

    encoder = nav.getRotaryEncoder();

    delay(2000);
    Serial.println("Iniciando o teste");

}

void loop() {

    encoder->read();
    nav.step();

    delay(250);

}