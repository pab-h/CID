#include <Arduino.h>

#include "pins.hpp"
#include "drivers/RotaryEncoder.hpp"

using namespace drivers;

RotaryEncoder encoder(SIGA_PIN, SIGB_PIN);

void setup() {

    Serial.begin(9600);

    pinMode(SIGA_PIN, INPUT);
    pinMode(SIGB_PIN, INPUT);

}

void loop() {

    int siga = digitalRead(SIGA_PIN);
    int sigb = digitalRead(SIGB_PIN);

    Serial.print("siga = " + String(siga) + " ");
    Serial.print("sigb = " + String(sigb) + " ");

    encoder.read();

    Serial.println("position = " + String(encoder.getPosition()));

    delay(500);

}