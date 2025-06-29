#include <Arduino.h>

#include "drivers/DcMotor.hpp"
#include "pins.hpp"
#include "board.hpp"

using namespace drivers;


DcMotor* motor;

void setup() {

    Serial.begin(9600);

    motor = new DcMotor(
        ENA_PIN,
        IN1_PIN,
        IN2_PIN,
        PWM_CHANNEL_0
    );


    Serial.println("[TEST] Rodando os testes do Driver do motor");
    
    motor->setPower(0xFF);

    Serial.println("[TEST] Ativando o motor no sentido horário");

    motor->clockwise();
    motor->enable();

    delay(2000);

    Serial.println("[TEST] Ativando o motor no sentido anti-horário");

    motor->disable();
    delay(500);

    motor->counterclockwise();
    motor->enable();
    delay(2000);

    motor->disable();
    delay(500);

    Serial.println("[TEST] Decréscimo gradual até zerar a potência");

    for (int i = 255; i >= 0; i -= 25) {
        motor->setPower(i);
        motor->enable();

        delay(250);
    }

    Serial.println("[TEST] Desativando o motor");
    motor->disable();

}


void loop() {}

