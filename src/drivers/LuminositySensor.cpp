#include <Arduino.h>
#include <drivers/LuminositySensor.hpp>
#include <env.hpp>

using namespace drivers;

LuminositySensor::LuminositySensor(uint8_t pin){

    this->pin = pin;
    
    this->minValue = LUMINOSITY_MIN_VALUE;
    this->maxValue = LUMINOSITY_MAX_VALUE;

    this-> calibrated = false;

}

uint16_t LuminositySensor::read(){

    // return analogRead(this->pin);
    return 500;

}

uint8_t LuminositySensor::readPercentage(){

    // uint8_t percentage = map(this->read(), this->minValue, this->maxValue, 0, 100);
    
    // return constrain(percentage, 0, 100);

    return 75; 

}

//Gostaria de guardar esses valores na memória flash do esp32
void LuminositySensor::calibrate(uint16_t minValue, uint16_t maxValue){

    this->minValue = minValue;
    this->maxValue = maxValue;
    
    this->calibrated = true;

}