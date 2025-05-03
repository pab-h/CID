#include <Arduino.h>
#include "drivers/SoilSensor.hpp"

using namespace sensors;

//Adicionar validações de calibração
SoilSensor::SoilSensor(uint8_t pin) {

    this->pin = pin;

    this->offset = 0;
    this->minValue = 0;	
    this->maxValue = 4095;

    this->calibrated = false;

    pinMode(this->pin, INPUT);
}

int SoilSensor::read(){

    return max(analogRead(this->pin) - this->offset, 0);

}

int SoilSensor::readPercentage(){

    int percentage = map(this->read(), this->minValue, this->maxValue, 0, 100);
    percentage = constrain(percentage, 0, 100);

    return percentage;

}

void SoilSensor::calibrate(int offset, int minValue, int maxValue){

    this->offset = offset;

    this->minValue = minValue;
    this->maxValue = maxValue;

    this->calibrated = true;

}