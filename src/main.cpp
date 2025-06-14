#include <Arduino.h>

#include "drivers/LuminositySensor.hpp"
#include "drivers/TempSensor.hpp"
#include "pins.hpp"

using namespace drivers;

LuminositySensor luminositySensor = LuminositySensor(LDR_PIN);
TempSensor tempSensor = TempSensor(TEMP_PIN);

void setup() {

    Serial.begin(9600);
    delay(1000);

    Serial.print("Iniciando sensores...");

    tempSensor.begin();
    luminositySensor.calibrate(0,300);

}

void loop() {

    u_int8_t luminosity_percentage = luminositySensor.readPercentage();

    Serial.println("Luminosity: " + String(luminosity_percentage) + " %");
    
    float temperature = tempSensor.readTemperature();
    float humidity = tempSensor.readHumidity();

    Serial.println("Temperature: " + String(temperature) + " C°");
    Serial.println("Humidity: " + String(humidity) + "%");

    delay(2000);
}