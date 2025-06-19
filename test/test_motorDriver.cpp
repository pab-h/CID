#include <Arduino.h>

#include "drivers/DcMotor.hpp"
#include "pins.hpp"

using namespace drivers;


DcMotor* motor;

void setup() {


    Serial.begin(9600);

    motor = new DcMotor(
        ENA_PIN,
        IN1_PIN,
        IN2_PIN
    );

}


void loop() {

    Serial.println("[TEST] Rodando os testes do Driver do motor");

    
    Serial.println("[TEST] Ativando o motor com 100% da potência");
    motor->setPower(0xFF);
    motor->enable();

    Serial.println("[TEST] Ativando o motor no sentido horário");
    motor->clockwise();
    delay(1000);

    Serial.println("[TEST] Ativando o motor no sentido anti-horário");
    motor->counterclockwise();
    delay(1000);


    Serial.println("[TEST] Ativando o motor com 25% da potência");
    motor->setPower(0x04);
    delay(1000);

    Serial.println("[TEST] Desativando o motor");
    motor->disable();
    delay(1000);

}

