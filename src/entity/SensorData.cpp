#include <Arduino.h>
#include "entity/SensorData.hpp"

using namespace entity;

SensorData::SensorData() {
    this->temperature = 0.0;
    this->moisture = 0.0;
    this->luminosity = 0;
    // this->motorVelocity = 0;
    // this->cameraImagemBase64 = "";

}

SensorData::SensorData(float temperature, float moisture, int luminosity) {
    this->temperature = temperature;
    this->moisture = moisture;
    this->luminosity = luminosity;
    // this->motorVelocity = motorVelocity;
    // this->cameraImagemBase64 = cameraImagemBase64;
}

