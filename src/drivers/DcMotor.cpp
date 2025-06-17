#include <Arduino.h>
#include "drivers/DcMotor.hpp"

using namespace drivers;

DcMotor::DcMotor(uint8_t inl, uint8_t inr) {

    this->isClockwise = true;

    this->power = 0x00;

    this->inl = inl;
    this->inr = inr;

    pinMode(this->inl, OUTPUT);
    pinMode(this->inr, OUTPUT);

}

void DcMotor::clockwise() {

    digitalWrite(this->inl, this->power);
    digitalWrite(this->inr, 0x00);

    this->isClockwise = true;

}

void DcMotor::counterclockwise() {

    digitalWrite(this->inl, 0x00);
    digitalWrite(this->inr, this->power);

    this->isClockwise = false;

}

void DcMotor::setPower(uint8_t pwm) {

    this->power = pwm;

}

void DcMotor::disable() {

    analogWrite(this->inl, 0x00);
    analogWrite(this->inr, 0x00);

}

void DcMotor::enable() {

    if (this->isClockwise) {
        return this->clockwise();
    }

    this->counterclockwise();

}

