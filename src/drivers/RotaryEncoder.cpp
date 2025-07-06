#include <Arduino.h>
#include "drivers/RotaryEncoder.hpp"

using namespace drivers;

RotaryEncoder::RotaryEncoder(uint8_t siga, uint8_t sigb) {

    this->siga = siga;
    this->sigb = sigb;
    
    this->position         = 0;
    this->lastSigaState    = false;
    this->currentSigaState = false;

    pinMode(this->siga, INPUT);
    pinMode(this->sigb, INPUT);

}

int RotaryEncoder::getPosition() {
    return this->position;
}

void RotaryEncoder::read() {
    
    this->currentSigaState = digitalRead(this->siga);

    // check rising edge 
    if (!this->lastSigaState && this->currentSigaState) {
        // check direction
        if (digitalRead(this->sigb)) {
            this->position ++;
        } else {
            this->position --;
        }
    }

    this->lastSigaState = this->currentSigaState;

}
