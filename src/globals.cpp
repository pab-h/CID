#include "globals.hpp"
#include "pins.hpp"

// Instancia global da classe de medição
application::Measurement measurement;

void initGlobals() {
    Wire.begin(I2C_SDA, I2C_SCL);
}