#include <Arduino.h>
#include "drivers/DcMotor.hpp"

using namespace drivers;

DcMotor::DcMotor(u_int8_t en, u_int8_t inl, u_int8_t inr) {

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

void DcMotor::power(u_int8_t pwm) {

    analogWrite(this->en, pwm);

}

void DcMotor::disable() {

    digitalWrite(this->inl, LOW);
    digitalWrite(this->inr, LOW);

}