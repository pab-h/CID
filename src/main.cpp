#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "application/Navigation.hpp"
#include "tasks/navigation.hpp"

using namespace application;
using namespace tasks;

void setup() {

    Navigation* nav = new Navigation();

    xTaskCreatePinnedToCore(
        vNavigationTask,
        "Navigation",
        2048,
        static_cast<void*>(nav),
        1,
        nullptr,
        1
    );
    
    xTaskCreatePinnedToCore(
        vUpdateRotaryEncoderTask,
        "UpdateEncoder",
        2048,
        static_cast<void*>(nav),
        1,
        nullptr,
        1
    );

}

void loop() {}