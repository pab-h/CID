#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "application/Navigation.hpp"
#include "tasks/navigation.hpp"

#include "entity/Travel.hpp"
#include "entity/Step.hpp"

using namespace application ;
using namespace tasks       ;
using namespace entity      ;

void setup() {

    Serial.begin(9600);

    Step* steps = new Step[3];
    
    steps[0] = Step(10,  0, false);
    steps[1] = Step( 1, 90, false);
    steps[2] = Step(10,  0, false);

    Travel* travel = new Travel(steps, 3);

    Navigation* nav = new Navigation();

    nav->setTravel(travel);

    xTaskCreatePinnedToCore(
        vNavigationTask         ,
        "Navigation"            ,
        2048                    ,
        static_cast<void*>(nav) ,
        1                       ,
        nullptr                 ,
        1
    );
    
    xTaskCreatePinnedToCore(
        vUpdateRotaryEncoderTask ,
        "UpdateRotaryEncoder"    ,
        2048                     ,
        static_cast<void*>(nav)  ,
        1                        ,
        nullptr                  ,
        1
    );

}

void loop() {}