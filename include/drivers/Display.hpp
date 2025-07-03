/**
 * @file Display.hpp
 * @brief OLED display driver for rendering system status information.
 * 
 * This class wraps the Adafruit_SSD1306 display library and provides higher-level
 * rendering functions for showing battery level, Wi-Fi signal strength, and
 * current system activity. It integrates with the global SystemStatus instance
 * to keep the user informed about the current state of the device.
 */

#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string>
#include "application/SystemStatus.hpp" 

namespace drivers {

    /**
     * @class Display
     * @brief High-level interface for displaying system information on an SSD1306 OLED.
     * 
     * The Display class encapsulates the rendering of system metrics such as battery
     * percentage, Wi-Fi signal strength, and operational activity. It uses the I2C-based
     * Adafruit_SSD1306 driver internally and provides custom drawing routines like arcs
     * and battery icons. It is intended to be used as a singleton, globally accessible 
     * through the `globals` namespace.
     */
    class Display {

    public:

        /**
         * @brief Constructs the Display instance.
         */
        Display();

        /**
         * @brief Initializes the display hardware and prepares it for rendering.
         */
        void begin();

        /**
         * @brief Shows the battery percentage as plain text.
         * @param percentage Battery level (0–100).
         */
        void showBatteryLevel(int percentage);

        /**
         * @brief Draws a battery icon with fill level based on the battery percentage.
         * @param percentage Battery level (0–100).
         */
        void showBatteryIcon(int percentage);

        /**
         * @brief Displays the current system activity (e.g., Moving, Sensing).
         * @param status Activity description string.
         */
        void showActivity(const std::string& status);

        /**
         * @brief Renders a Wi-Fi signal strength icon based on the given level.
         * @param level Connection quality (0–4).
         */
        void showWiFiSignal(int level);

        /**
         * @brief Updates the entire screen using the current data from the global SystemStatus instance.
         */
        void updateFromSystemStatus(const application::SystemStatus& status);

    private:

        Adafruit_SSD1306 display;  ///< Internal SSD1306 display object.

        /**
         * @brief Helper function to draw an arc from start_angle to end_angle.
         * @param x0 Center X
         * @param y0 Center Y
         * @param r Radius
         * @param start_angle Start angle in degrees
         * @param end_angle End angle in degrees
         * @param color Color of the arc (usually SSD1306_WHITE)
         */
        void drawArc(int16_t x0, int16_t y0, int16_t r, int16_t start_angle, int16_t end_angle, uint16_t color);
    };

}
