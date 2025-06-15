#include <Arduino.h>
#include "drivers/DcMotor.hpp"

using namespace drivers;

DcMotor::DcMotor(uint8_t en, uint8_t inl, uint8_t inr) {

    this->power = 0;

    this->en  = en;
    this->inl = inl;
    this->inr = inr;

    pinMode(this->en , OUTPUT);
    pinMode(this->inl, OUTPUT);
    pinMode(this->inr, OUTPUT);

}

void DcMotor::clockwise() {

    analogWrite(this->inl, this->power);
    analogWrite(this->inr, 0x00);

}

void DcMotor::counterclockwise() {

    analogWrite(this->inl, 0x00);
    analogWrite(this->inr, this->power);

}

void DcMotor::setPower(uint8_t pwm) {

    this->power = power;

}

void DcMotor::disable() {

    digitalWrite(this->en, LOW);

}

void DcMotor::enable() {

    digitalWrite(this->en, HIGH);

}
