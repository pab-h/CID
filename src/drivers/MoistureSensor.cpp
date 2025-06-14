#include <Arduino.h>
#include "drivers/MoistureSensor.hpp"

using namespace drivers;

MoistureSensor::MoistureSensor(uint8_t pin) {

    this->pin = pin;

    this->minValue = 0;	
    this->maxValue = 4095;

    this->calibrated = false;

    pinMode(this->pin, INPUT);
}

uint16_t MoistureSensor::read(){

    return analogRead(this->pin);

}

uint8_t MoistureSensor::readPercentage(){

    int percentage = map(this->read(), this->minValue, this->maxValue, 0, 100);
    percentage = constrain(percentage, 0, 100);

    return percentage;

}

void MoistureSensor::calibrate(uint16_t minValue, uint16_t maxValue){

    this->minValue = minValue;
    this->maxValue = maxValue;

    this->calibrated = true;

}