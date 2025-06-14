#include "drivers/Camera.hpp"
#include <esp_log.h>
#include <driver/rtc_io.h>
#include <pins.hpp>

namespace drivers {

CameraOV7670::CameraOV7670(int8_t pwdnPin)
    : _pwdnPin(pwdnPin), _initialized(false)
{
    _config.ledc_channel = LEDC_CHANNEL_0;
    _config.ledc_timer = LEDC_TIMER_0;

    _config.pin_d0 = C_D0;
    _config.pin_d1 = C_D1;
    _config.pin_d2 = C_D2;
    _config.pin_d3 = C_D3;
    _config.pin_d4 = C_D4;
    _config.pin_d5 = C_D5;
    _config.pin_d6 = C_D6;
    _config.pin_d7 = C_D7;

    _config.pin_xclk = XCLK;
    _config.pin_pclk = PCLK;
    _config.pin_vsync = VSYNC;
    _config.pin_href = HREF;

    _config.pin_sccb_sda = CAM_SDA;
    _config.pin_sccb_scl = CAM_SCL;

    _config.pin_pwdn = (pwdnPin >= 0) ? pwdnPin : -1;
    _config.pin_reset = -1;

    _config.xclk_freq_hz = 20000000;
    _config.pixel_format = PIXFORMAT_RGB565;
    _config.frame_size = FRAMESIZE_QVGA;
    _config.jpeg_quality = 10;
    _config.fb_count = 1;
}

bool CameraOV7670::begin() {
    setupPins();

    esp_err_t err = esp_camera_init(&_config);
    if (err != ESP_OK) {
        ESP_LOGE("CameraOV7670", "Camera init failed with error 0x%x", err);
        _initialized = false;
        return false;
    }

    _initialized = true;
    return true;
}

camera_fb_t* CameraOV7670::capture() {
    if (!_initialized) {
        ESP_LOGW("CameraOV7670", "Camera not initialized");
        return nullptr;
    }

    camera_fb_t* frame = esp_camera_fb_get();
    if (!frame) {
        ESP_LOGE("CameraOV7670", "Failed to get frame buffer");
        return nullptr;
    }

    return frame;
}

void CameraOV7670::releaseFrame(camera_fb_t* frame) {
    if (frame) {
        esp_camera_fb_return(frame);
    }
}

void CameraOV7670::powerDown() {
    if (_pwdnPin < 0) {
        ESP_LOGW("CameraOV7670", "PWDN pin not configured");
        return;
    }

    gpio_set_level((gpio_num_t)_pwdnPin, 1);
    _initialized = false;
}

void CameraOV7670::wakeUp() {
    if (_pwdnPin < 0) {
        ESP_LOGW("CameraOV7670", "PWDN pin not configured");
        return;
    }

    gpio_set_level((gpio_num_t)_pwdnPin, 0);
    // Precisa reinicializar a câmera após acordar
    begin();
}

void CameraOV7670::setupPins() {
    if (_pwdnPin >= 0) {
        gpio_reset_pin((gpio_num_t)_pwdnPin);
        gpio_set_direction((gpio_num_t)_pwdnPin, GPIO_MODE_OUTPUT);
        gpio_set_level((gpio_num_t)_pwdnPin, 0);
    }
}

} // namespace drivers