#include "pins.hpp"
#include "env.hpp"
#include "board.hpp"

#include "application/Navigation.hpp"

#include "drivers/DcMotor.hpp"
#include "drivers/RotaryEncoder.hpp"

#include "entity/Travel.hpp"

using namespace application;
using namespace drivers;

Navigation::Navigation() {

    this->motorLeft  = new DcMotor(
        ENA_PIN,
        IN1_PIN,
        IN2_PIN,
        PWM_CHANNEL_0
    );
    this->motorRight = new DcMotor(
        ENB_PIN,
        IN3_PIN,
        IN4_PIN,
        PWM_CHANNEL_1
    );

    this->hodometer = new RotaryEncoder(
        SIGA_PIN,
        SIGB_PIN
    );

    this->motorLeft->disable();
    this->motorRight->disable();

    this->motorLeft->setPower(LEFT_MOTOR_PWM);
    this->motorRight->setPower(RIGHT_MOTOR_PWM);


    this->state         = State::IDLE;
    this->angle         = 0;
    this->travel        = nullptr;
    this->startAngle    = 0;
    this->startPosition = 0;
    this->currentStep   = nullptr;

}

Navigation::~Navigation() {

    delete this->motorLeft;
    delete this->motorRight;
    
    delete this->hodometer;

    delete this->travel;

}

Notifications* Navigation::getNotifications() {  
    return &this->notifications;
}

State Navigation::getState() {
    return this->state;
}

RotaryEncoder* Navigation::getRotaryEncoder() {
    return this->hodometer;
}

void Navigation::setTravel(Travel* travel) {

    this->travel = travel;

}

void Navigation::updateAngle(uint pulses) {

    this->angle = (float) pulses / PULSES_PER_DEGREE;

}

void Navigation::setupRotateMotors() {

    this->startAngle = this->angle;
    this->state      = State::TURNING;

    if (this->currentStep->direction > this->angle) {

        this->motorLeft->clockwise();
        this->motorRight->counterclockwise();

    }

    if (this->currentStep->direction < this->angle) {

        this->motorLeft->counterclockwise();
        this->motorRight->clockwise();

    }

    this->motorLeft->enable();
    this->motorRight->enable();

}

void Navigation::setupForwardMotors() {

    this->startPosition = this->hodometer->getPosition();

    this->motorLeft->clockwise();
    this->motorRight->clockwise();

    this->motorLeft->enable();
    this->motorRight->enable();

    this->state = State::MOVING;
    

}

void Navigation::stepIdle() {

    this->currentStep = this->travel->nextStep();

    if (this->currentStep == nullptr) {
        return;
    }

    if (this->currentStep->distance == 0 && this->currentStep->direction == this->angle) {
        return;
    }

    if (this->currentStep->direction != this->angle) {

        this->setupRotateMotors();

        return;
    }

    this->setupForwardMotors();

}

void Navigation::stepMoving() {

    int distance = this->hodometer->getPosition() - this->startPosition;

    if (distance <= this->currentStep->distance) {
        return;
    }

    this->motorLeft->disable();
    this->motorRight->disable();

    if (this->currentStep->toMeasure) {
        this->state = State::WAITING_MEASURE;
        return;
    }

    this->state = State::IDLE;

}

void Navigation::stepTurning() {

    int currentAngle = this->angle;  

    if (currentAngle >= this->currentStep->direction) {
        
        this->motorLeft->disable();
        this->motorRight->disable();

        this->setupForwardMotors();

    }

}

void Navigation::stepWaiting() {};


void Navigation::step() {

    switch (this->state) {
        case    State::IDLE             : return this->stepIdle();
        case    State::MOVING           : return this->stepMoving();
        case    State::TURNING          : return this->stepTurning();
        case    State::WAITING_MEASURE  : return this->stepWaiting();
        default                                   : return;
    }

}
