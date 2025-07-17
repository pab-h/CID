#include <env.hpp>
#include "drivers/TempHumSensor.hpp"

using namespace drivers;

TempHumSensor::TempHumSensor(uint8_t pin) {

    this->pin = pin;
    this->dht = new DHT(pin, DHTTYPE);

}

void TempHumSensor::begin() {
    dht->begin();
}

float TempHumSensor::readTemperature(bool fahrenheit, bool force) const{
    return dht->readTemperature(fahrenheit, force);
}

float TempHumSensor::readHumidity(bool force) const{
    return dht->readHumidity(force);
}

bool TempHumSensor::isReady() const{

    float t = dht->readTemperature();
    float h = dht->readHumidity();

    return !isnan(t) && !isnan(h);

}

