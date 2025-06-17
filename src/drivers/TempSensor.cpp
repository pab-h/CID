#include "drivers/TempSensor.hpp"
#include <env.hpp>

using namespace drivers;

TempSensor::TempSensor(uint8_t pin) {
    this->pin = pin;
    this->dht = new DHT(pin, DHTTYPE);
}

void TempSensor::begin() {
    dht->begin();
}

float TempSensor::readTemperature(bool fahrenheit, bool force) const{
    return dht->readTemperature(fahrenheit, force);
}

float TempSensor::readHumidity(bool force) const{
    return dht->readHumidity(force);
}

bool TempSensor::isReady() const{
    float t = dht->readTemperature();
    float h = dht->readHumidity();
    return !isnan(t) && !isnan(h);
}

