#include <Arduino.h>

#include "drivers/DcMotor.hpp"
#include "board.hpp"

using namespace drivers;

DcMotor::DcMotor(uint8_t en, uint8_t inl, uint8_t inr, uint8_t pwmChannel) {

    this->en         = en;
    this->inl        = inl;
    this->inr        = inr;
    this->pwmChannel = pwmChannel;

    pinMode(this->inl, OUTPUT);
    pinMode(this->inr, OUTPUT);

    ledcSetup(this->pwmChannel, PWM_FREQUENCY, PWM_RESOLUTION);
    ledcAttachPin(this->en, this->pwmChannel);

    this->disable();
    this->clockwise();

}

void DcMotor::clockwise() {

    digitalWrite(this->inl, HIGH);
    digitalWrite(this->inr, LOW);

}

void DcMotor::counterclockwise() {

    digitalWrite(this->inl, LOW);
    digitalWrite(this->inr, HIGH);

}

void DcMotor::enable() {

    ledcWrite(this->pwmChannel, this->power);

}

void DcMotor::disable() {

    ledcWrite(this->pwmChannel, 0x0000);

}

void DcMotor::setPower(uint8_t pwm) {

    this->power = pwm;

}

