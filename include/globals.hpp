/**
 * @file globals.hpp
 * @brief Declares global instances and the initialization routine used throughout the system.
 * 
 * This header provides access to globally shared components such as the measurement manager,
 * system status tracker, and display controller. These instances are initialized in `initGlobals()`
 * and are used across multiple modules including tasks, drivers, and application logic.
 */

#pragma once

#include "freertos/FreeRTOS.h"
#include <freertos/timers.h>
#include "application/Measurement.hpp"
#include "application/SystemStatus.hpp"
#include "application/ApiService.hpp"
#include "drivers/Display.hpp"

/// Global instance for managing environmental measurements.
extern application::Measurement measurement;

/// Global instance for tracking the current state of the system (battery, activity, connectivity, etc).
extern application::SystemStatus systemStatus;

/// Global instance for managing API communication
extern application::ApiService api;

/// Global instance for handling the OLED display interface.
extern drivers::Display display;

/**
 * @brief Initializes global components such as I2C and display.
 * 
 * This function must be called early in setup() to ensure that all
 * global hardware interfaces and modules are properly initialized.
 */
void initGlobals();