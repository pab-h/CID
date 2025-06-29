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

    this->motorLeft->setPower(0xFF);
    this->motorRight->setPower(0xFF);


    this->state         = NavigationState::IDLE;
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
    this->state      = NavigationState::TURNING;

    if (this->currentStep->atAngle > this->angle) {

        this->motorLeft->clockwise();
        this->motorRight->counterclockwise();

    }

    if (this->currentStep->atAngle < this->angle) {

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

    this->state = NavigationState::MOVING;
    

}

void Navigation::stepIdle() {

    this->currentStep = this->travel->nextStep();

    if (this->currentStep == nullptr) {
        return;
    }

    if (this->currentStep->howLong == 0 && this->currentStep->atAngle == this->angle) {
        return;
    }

    if (this->currentStep->atAngle != this->angle) {

        this->setupRotateMotors();

        return;
    }

    this->setupForwardMotors();

}

void Navigation::stepMoving() {

    int distance = this->hodometer->getPosition() - this->startPosition;

    if (distance >= this->currentStep->howLong) {

        this->motorLeft->disable();
        this->motorRight->disable();

        this->state = NavigationState::IDLE;

    }

}

void Navigation::stepTurning() {

    int currentAngle = this->angle;  

    if (currentAngle >= this->currentStep->atAngle) {
        
        this->motorLeft->disable();
        this->motorRight->disable();

        this->setupForwardMotors();

    }

}


void Navigation::step() {

    if (this->state == NavigationState::IDLE) {

        this->stepIdle();

        return;
    }

    if (this->state == NavigationState::MOVING) {

        this->stepMoving();

        return;
    }

    if (this->state == NavigationState::TURNING) {

        this->stepTurning();

        return;
    }

}
