#pragma once

#include "esp_camera.h"
#include <Arduino.h>

namespace drivers {

/**
 * @brief Driver for OV7670 camera module (without FIFO) in esp32 using esp32-camera library.
 * 
 * Allows you to initialize the camera, capture an image, turn it on and off (power down mode).
 */
class CameraOV7670 {
public:
    /**
     * @brief Constructor that defines the PWDN pin for power control.
     * @param pwdnPin GPIO connected to the camera's PWDN pin (use -1 if not using power control).
     */
    explicit CameraOV7670();

    /**
     * @brief Initializes the camera with the default settings for OV7670.
     * @return true if initialization successful, false otherwise.
     */
    bool begin();

    /**
     * @brief Captures a photo from the camera.
     *
     * @return Pointer to image buffer (camera_fb_t*), or nullptr on failure.
     * The user must release the buffer with releaseFrame().
     */
    camera_fb_t* capture();

    /**
     * @brief Releases the image buffer after use.
     * @param frame Pointer to buffer returned by capture().
     */
    void releaseFrame(camera_fb_t* frame);

    /**
     * @brief Puts the camera in power down mode.
     * Only works if pwdnPin is defined in the constructor.
     */
    void powerDown();

    /**
     * @brief Reactivates the camera from power down mode.
     * Only works if pwdnPin is defined in the constructor.
     */
    void wakeUp();

private:
    camera_config_t _config;
    bool _initialized;

    void setupPins();
};

}