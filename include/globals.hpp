#pragma once

#include "freertos/FreeRTOS.h"
#include <freertos/timers.h>
#include <Wire.h>
#include "application/Measurement.hpp"

extern application::Measurement measurement;
extern TwoWire DisplayWire;

void initGlobals();