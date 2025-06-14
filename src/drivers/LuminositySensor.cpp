#include <Arduino.h>
#include <drivers/LuminositySensor.hpp>

using namespace drivers;

LuminositySensor::LuminositySensor(u_int8_t pin){

    this->pin = pin;
    
    this->minValue = 0;
    this->maxValue = 4095;

    this-> calibrated = false;

}

uint16_t LuminositySensor::read(){

    return analogRead(this->pin);

}

uint8_t LuminositySensor::readPercentage(){

    uint8_t percentage = map(this->read(), this->minValue, this->maxValue, 0, 100);
    
    return constrain(percentage, 0, 100);

}

//Gostaria de guardar esses valores na memória flash do esp32
void LuminositySensor::calibrate(u_int16_t minValue, u_int16_t maxValue){

    this->minValue = minValue;
    this->maxValue = maxValue;
    this->calibrated = true;

}