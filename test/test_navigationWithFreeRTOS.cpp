#include <Arduino.h>

#include "drivers/RotaryEncoder.hpp"
#include "application/Navigation.hpp"
#include "entity/Travel.hpp"
#include "tasks/Navigation.hpp"

#include "pins.hpp"

using namespace application;
using namespace drivers;
using namespace entity;
using namespace tasks;

Navigation     nav;
RotaryEncoder* encoder;

void setup() {

    Serial.begin(9600);

    Step* steps = new Step[3];
    
    steps[0]           = Step();
    steps[0].distance  = 1;
    steps[0].direction = 0;
    steps[0].sector    = "";
    steps[0].toMeasure = false;

    steps[1]           = Step();
    steps[1].distance  = 5;
    steps[1].direction = 0;
    steps[1].sector    = "Brazil";
    steps[1].toMeasure = true;

    steps[2]           = Step();
    steps[2].distance  = 10;
    steps[2].direction = 10;
    steps[2].sector    = "";
    steps[2].toMeasure = false;

    Travel* travel = new Travel(steps, 3);

    nav.setTravel(travel);
    encoder = nav.getRotaryEncoder();

    delay(2000);
    Serial.println("Iniciando o teste com FreeRTOS");

    xTaskCreatePinnedToCore(
        vUpdateRotaryEncoderTask, 
        "Encoder Task", 
        2048, 
        &nav, 
        1, 
        NULL, 
        APP_CPU_NUM
    );
    xTaskCreatePinnedToCore(
        vNavigationTask, 
        "Navigation Task", 
        2048, 
        &nav, 
        1, 
        NULL, 
        APP_CPU_NUM
    );
    xTaskCreatePinnedToCore(
        vNavigationNotificationsTask, 
        "Notifications navigation Task", 
        2048, 
        &nav, 
        1, 
        NULL, 
        APP_CPU_NUM
    );

}

void loop() {
}
