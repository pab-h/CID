#include <Arduino.h>
#include <env.hpp>
#include "drivers/MoistureSensor.hpp"

using namespace drivers;

MoistureSensor::MoistureSensor(uint8_t pin) {

    this->pin = pin;

    this->minValue = MOISURE_MIN_VALUE;	
    this->maxValue = MOISURE_MAX_VALUE;

    this->calibrated = false;

    pinMode(this->pin, INPUT);
}

uint16_t MoistureSensor::read(){

    return analogRead(this->pin);

}

uint8_t MoistureSensor::readPercentage(){

    int percentage = map(this->read(), this->minValue, this->maxValue, 100, 0);

    return constrain(percentage, 0, 100);

}

void MoistureSensor::calibrate(uint16_t minValue, uint16_t maxValue){

    this->minValue = minValue;
    this->maxValue = maxValue;

    this->calibrated = true;

}