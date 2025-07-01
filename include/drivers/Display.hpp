#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string>
#include "globals.hpp"


class Display {

public:

    Display();

    void begin();
    void showBatteryLevel(int percentage);
    void showSystemStatus(const std::string& status);
    void showBatteryIcon(int percentage);

private:

    Adafruit_SSD1306 display;

};