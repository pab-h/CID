#include <Arduino.h>

#include "drivers/DcMotor.hpp"
#include "pins.hpp"

using namespace drivers;

DcMotor motorA(
    ENA_PIN,
    IN1_PIN,
    IN2_PIN
);

DcMotor motorB(
    ENB_PIN,
    IN3_PIN,
    IN4_PIN
);

void setup() {

    Serial.begin(9600);

    motorA.power(0xFF);
    motorB.power(0xFF);

}

void loop() {

    motorA.clockwise();
    delay(500);

    motorB.clockwise();
    delay(500);

    motorA.counterclockwise();
    delay(500);

}