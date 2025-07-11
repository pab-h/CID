#include "globals.hpp"
#include "pins.hpp"

application::Measurement  measurement;
application::SystemStatus systemStatus;
application::Navigation   navigation;

drivers::Display display;

void initGlobals() {

    Wire.begin(I2C_SDA, I2C_SCL);
    display.begin();

}