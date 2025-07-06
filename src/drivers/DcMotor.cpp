#include <Arduino.h>
#include "drivers/DcMotor.hpp"

using namespace drivers;

DcMotor::DcMotor(uint8_t en, uint8_t inl, uint8_t inr) {

    this->power = 0x00;

    this->en  = en;
    this->inl = inl;
    this->inr = inr;

    pinMode(this->en , OUTPUT);
    pinMode(this->inl, OUTPUT);
    pinMode(this->inr, OUTPUT);

}

void DcMotor::clockwise() {

    digitalWrite(this->inl, HIGH);
    digitalWrite(this->inr, LOW);

}

void DcMotor::counterclockwise() {

    digitalWrite(this->inl, LOW);
    digitalWrite(this->inr, HIGH);

}

void DcMotor::setPower(uint8_t pwm) {

    this->power = pwm;

}

void DcMotor::disable() {

    analogWrite(this->en, 0x00);

}

void DcMotor::enable() {

    analogWrite(this->en, this->power);

}

