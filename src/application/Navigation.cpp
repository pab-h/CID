#include "pins.hpp"

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
        IN2_PIN
    );
    this->motorRight = new DcMotor(
        ENB_PIN,
        IN3_PIN,
        IN4_PIN   
    );

    this->hodometer = new RotaryEncoder(
        SIGA_PIN,
        SIGB_PIN
    );

}

Navigation::~Navigation() {

    delete this->motorLeft;
    delete this->motorRight;
    
    delete this->hodometer;

    delete this->travel;

}

void Navigation::setTravel(Travel* travel) {

    this->travel = travel;

}

void Navigation::step() {
    
    // Todo: Percorrer caminho reto

}
