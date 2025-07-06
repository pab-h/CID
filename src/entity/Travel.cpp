#include "entity/Travel.hpp"
#include "entity/Step.hpp"

using namespace entity;

Travel::Travel(Step* steps, uint lenght) {

    this->lenght  = lenght;
    this->current = 0;

    this->steps = new Step[lenght];
    
    for (uint i = 0; i < lenght; i++) {
        this->steps[i] = steps[i];
    }

}

Travel::~Travel() {

    delete[] this->steps;

}

Step* Travel::nextStep() {

    if (this->current >= this->lenght) {
        return nullptr;
    }

    Step* step = &this->steps[this->current];
    
    this->current++;

    return step;
}
