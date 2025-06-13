#include <Arduino.h>
#include <entity/Reference.hpp>

using namespace entity;

Reference::Reference(uint howLong, uint16_t atAngle) {

    this->howLong = howLong;
    this->atAngle = atAngle;

}

