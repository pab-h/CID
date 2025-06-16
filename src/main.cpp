#include <Arduino.h>

#include "drivers/DcMotor.hpp"
#include "pins.hpp"

// #include "tasks/connection.hpp"  // ou o caminho correto da sua task
#include "application/Connection.hpp"

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

    motorA.setPower(0xFF);
    motorB.setPower(0xFF);

    motorA.enable();
    motorB.enable();

    // wifiConnectAndSend(); // apenas chama a função
    testDownloadJson();

}

void loop() {

    motorA.clockwise();
    delay(500);

    motorB.clockwise();
    delay(500);

    motorA.counterclockwise();
    delay(500);

}