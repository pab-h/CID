#include <Arduino.h>

#include "entity/Step.hpp"

using namespace entity;

Step::Step() {

    this->howLong   = 0;
    this->atAngle   = 0;
    this->isMeasure = false;

}

Step::Step(uint howLong, uint16_t atAngle, bool isMeasure) {

    this->howLong   = howLong;
    this->atAngle   = atAngle;
    this->isMeasure = isMeasure;

}
