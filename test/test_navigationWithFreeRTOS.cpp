#include <Arduino.h>

#include "drivers/RotaryEncoder.hpp"
#include "application/Navigation.hpp"
#include "entity/Travel.hpp"
#include "tasks/navigation.hpp"

#include "pins.hpp"

using namespace application;
using namespace drivers;
using namespace entity;
using namespace tasks;

Navigation     nav;
RotaryEncoder* encoder;

const char* stateToString(NavigationState state) {
    switch (state) {
        case NavigationState::IDLE   : return "IDLE";
        case NavigationState::MOVING : return "MOVING";
        case NavigationState::TURNING: return "TURNING";
        default                      : return "UNKNOWN";
    }
}

void serialMonitorTask(void* pvParameters) {

    RotaryEncoder* encoder = static_cast<RotaryEncoder*>(pvParameters);

    while (true) {
        Serial.print("STATE = ");
        Serial.print(stateToString(nav.getState()));
        Serial.print(" POSITION ENCODER = ");
        Serial.println(encoder->getPosition());
        vTaskDelay(pdMS_TO_TICKS(250)); 
    }
}

void setup() {

    Serial.begin(9600);

    Step* steps = new Step[3];
    
    steps[0] = Step(1, 0, false);
    steps[1] = Step(2, 0, false);
    steps[2] = Step(3, 0, false);

    Travel* travel = new Travel(steps, 3);

    nav.setTravel(travel);
    encoder = nav.getRotaryEncoder();

    delay(2000);
    Serial.println("Iniciando o teste com FreeRTOS");

    xTaskCreatePinnedToCore(vUpdateRotaryEncoderTask, "Encoder Task", 2048, &nav, 1, NULL, APP_CPU_NUM);
    xTaskCreatePinnedToCore(vNavigationTask, "Navigation Task", 2048, &nav, 1, NULL, APP_CPU_NUM);
    xTaskCreatePinnedToCore(serialMonitorTask, "Serial Monitor", 2048, encoder, 1, NULL, APP_CPU_NUM);

}

void loop() {
}
