#include <Arduino.h>
#include "entity/Step.hpp"

using namespace entity;

Step::Step() {

    this->direction = 0;
    this->distance  = 0;
    this->sector    = "";
    this->toMeasure = false;

}
