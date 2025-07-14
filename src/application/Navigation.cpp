#include <Arduino.h>

#include "pins.hpp"
#include "board.hpp"
#include "env.hpp"

#include "application/Navigation.hpp"

#include "drivers/DcMotor.hpp"
#include "drivers/RotaryEncoder.hpp"

using namespace application;
using namespace drivers;

Navigation::Navigation() {

    this->motorLeft.setup(
        ENA_PIN,
        IN1_PIN,
        IN2_PIN,
        PWM_CHANNEL_0
    );
    this->motorRight.setup(
        ENB_PIN,
        IN3_PIN,
        IN4_PIN,
        PWM_CHANNEL_1
    );
    this->hodometer.setup(
        SIGA_PIN,
        SIGB_PIN
    );

    this->state            = States::PULLING;
    this->travel           = nullptr;
    this->currentStep      = nullptr;
    this->direction        = 0;
    this->lastStepPosition = 0;

    this->notifications.isSendWaitingAlert      = false;
    this->notifications.isSendInsertinDoneAlert = false;


    this->motorLeft.setPower(LEFT_MOTOR_PWM);
    this->motorRight.setPower(RIGHT_MOTOR_PWM);

    this->motorLeft.clockwise();
    this->motorRight.clockwise();

    this->motorLeft.disable();
    this->motorRight.disable();

}

Navigation::~Navigation() {

    if (this->travel != nullptr) {
        delete this->travel;
    }

}


void Navigation::pulling() {

    if (this->travel == nullptr) {

        Serial.println("[Application::Navigation] Nenhum rota foi definida");

        return;
    }

    if (!this->travel->hasMore()) {

        Serial.println("[Application::Navigation] Não há novos passos");
        
        return;
    }

    this->currentStep = this->travel->nextStep();

    if (this->getMisalignment() != 0) {
        
        Serial.println("[Application::Navigation] Direção desalinha... ajustando");
        this->state = States::SPINNING;

        return;
    }

    Serial.println("[Application::Navigation] Iniciando a caminhada");
    this->state = States::FORWARD;

}

void Navigation::forward() {

    this->motorLeft.enable();
    this->motorRight.enable();

    this->motorRight.clockwise();
    this->motorLeft.clockwise();

    Step* step           = this->currentStep;
    int lastStepDistance = this->getLastStepDistance(); 

    if (!(lastStepDistance >= step->distance)) {

        Serial.print("[Application::Navigation] Ainda não chegou no objetivo. ");
        Serial.print(lastStepDistance);
        Serial.print(" passos de ");
        Serial.println(step->distance);

        return;
    }

    this->motorRight.disable();
    this->motorLeft.disable();

    this->lastStepPosition = this->hodometer.getPosition();

    if (step->toMeasure) {

        this->state                            = States::WAITING;
        this->notifications.isSendWaitingAlert = true;

        Serial.print("[Application::Navigation] Modo de espera ativado. Setor = ");
        Serial.println(this->currentStep->sector);

        return;
    }

    this->state = States::PULLING;

}

void Navigation::spinning() {

    Serial.print("[Application::Navigation] Ajustando a direção atual de ");
    Serial.print(this->direction);
    Serial.print(" para ");
    Serial.println(this->currentStep->direction);

    uint16_t misalignment = this->getMisalignment();

    if (misalignment == 0) {

        this->motorRight.disable();
        this->motorLeft.disable();
        
        this->state     = States::FORWARD;
        this->direction = this->currentStep->direction;

        Serial.println("[Application::Navigation] Alinhamento completo");

        return;
    }

    if (misalignment > 0) {

        this->motorRight.clockwise();
        this->motorLeft.counterclockwise();

    }

    if (misalignment < 0) {

        this->motorRight.counterclockwise();
        this->motorLeft.clockwise();
        
    }

    this->motorRight.enable();
    this->motorLeft.enable();

}

void Navigation::waiting() {
    Serial.println("[Application::Navigation] Esperando o sistema de sensoriamento");
}

void Navigation::inserting() {

    Serial.println("[Application::Navigation] Inserindo o sendor de humidade no solo...");

    this->motorLeft.enable();
    this->motorRight.enable();

    if (!(this->getLastStepDistance() >= INSERTING_PULSES)) {
        return;
    }

    this->state                                 = States::WAITING;
    this->notifications.isSendInsertinDoneAlert = true;

    Serial.println("[Application::Navigation] Inserção concluída");

}

int Navigation::getMisalignment() {
    return this->direction - this->currentStep->direction;
}

int Navigation::getLastStepDistance() {
    return this->hodometer.getPosition() - this->lastStepPosition;
}


Notifications* Navigation::getNotifications() {
    return &this->notifications;
}

RotaryEncoder* Navigation::getRotaryEncoder() {
    return &this->hodometer;
}

void Navigation::setTravel(Travel* travel) {

    if (this->travel != nullptr) {
        delete this->travel;
    }

    this->travel = travel;

    Serial.println("[Application::Navigation] Nova viagem inserida");

}

void Navigation::step() {

    if (this->state == States::PULLING) {
        return this->pulling();
    }

    if (this->state == States::FORWARD) {
        return this->forward();
    }

    if (this->state == States::SPINNING) {
        return this->spinning();
    }

    if (this->state == States::WAITING) {
        return this->waiting();
    }

    if (this->state == States::INSERTING) {
        return this->inserting();
    }

}
