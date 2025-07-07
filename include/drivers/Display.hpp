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
         * @brief Renders a Wi-Fi signal strength icon based on the given level.
         * @param level Connection quality (0–4).
         */
        void showWiFiSignal(uint8_t level);

        /**
         * @brief Draws a battery icon with fill level based on the battery percentage.
         * @param percentage Battery level (0–100).
         */
        void showBatteryIcon(uint8_t percentage);

        /**
         * @brief displays the current activity performed by the system
         * @param activity Activity description string.
         */
        void showActivity(const std::string& activity);

        /**
         * @brief Displays the current location of cid.
         * @param  Activity description string.
         */
        void showLocation(const std::string& location);

        /**
         * @brief Updates the entire screen using the current data from the global SystemStatus instance.
         */
        void updateFromSystemStatus(const application::SystemStatus& status);

    private:

        Adafruit_SSD1306 display;  ///< Internal SSD1306 display object.

        /**
         * @brief Draws a filled arc between two radius and angle ranges.
         * 
         * This function renders a thick arc by drawing pixels from radius rStart to rEnd,
         * covering the angle range from start_angle to end_angle.
         *
         * @param x0 Center X coordinate of the arc.
         * @param y0 Center Y coordinate of the arc.
         * @param rStart Inner radius where the arc begins.
         * @param rEnd Outer radius where the arc ends.
         * @param start_angle Starting angle in degrees (e.g., 0 to 360).
         * @param end_angle Ending angle in degrees.
         * @param color Color of the arc (usually SSD1306_WHITE).
         */
        void drawArc(uint8_t x0, uint8_t y0, uint8_t rStart, uint8_t rEnd, int16_t start_angle, int16_t end_angle, uint16_t color);

        /**
         * @brief Draws a monochrome bitmap icon at a specified position.
         * 
         * @param x Horizontal position on the display.
         * @param y Vertical position on the display.
         * @param bitmap Pointer to a PROGMEM bitmap array.
         * @param w Width of the bitmap in pixels.
         * @param h Height of the bitmap in pixels.
         */
        void drawIcon(uint8_t x, uint8_t y, const uint8_t* bitmap, uint8_t w, uint8_t h);

        void drawRadius(uint8_t x, uint8_t y, uint8_t rInit, uint8_t rEnd, int16_t start_angle, int16_t end_angle, uint16_t color);
    };

}
