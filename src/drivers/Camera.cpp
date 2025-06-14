// #include "drivers/Camera.hpp"
// #include <esp_log.h>
// #include <driver/rtc_io.h>
// #include <pins.hpp>

// namespace drivers {

// CameraOV7670::CameraOV7670()
//     : _initialized(false)
// {
//     _config.ledc_channel = LEDC_CHANNEL_0;
//     _config.ledc_timer = LEDC_TIMER_0;

//     _config.pin_d0 = CAM_D0;
//     _config.pin_d1 = CAM_D1;
//     _config.pin_d2 = CAM_D2;
//     _config.pin_d3 = CAM_D3;
//     _config.pin_d4 = CAM_D4;
//     _config.pin_d5 = CAM_D5;
//     _config.pin_d6 = CAM_D6;
//     _config.pin_d7 = CAM_D7;

//     _config.pin_xclk = CAM_XCLK;
//     _config.pin_pclk = CAM_PCLK;
//     _config.pin_vsync = CAM_VSYNC;
//     _config.pin_href = CAM_HREF;

//     _config.pin_sccb_sda = CAM_SDA;
//     _config.pin_sccb_scl = CAM_SCL;

//     _config.pin_pwdn = CAM_PWDN;
//     _config.pin_reset = CAM_RESET;

//     _config.xclk_freq_hz = 20000000;
//     _config.pixel_format = PIXFORMAT_RGB565;
//     _config.frame_size = FRAMESIZE_QVGA;
//     _config.jpeg_quality = 10;
//     _config.fb_count = 1;
// }

// bool CameraOV7670::begin() {
//     setupPins();

//     esp_err_t err = esp_camera_init(&_config);
//     if (err != ESP_OK) {
//         ESP_LOGE("CameraOV7670", "Camera init failed with error 0x%x", err);
//         _initialized = false;
//         return false;
//     }

//     _initialized = true;
//     return true;
// }

// camera_fb_t* CameraOV7670::capture() {
//     if (!_initialized) {
//         ESP_LOGW("CameraOV7670", "Camera not initialized");
//         return nullptr;
//     }

//     camera_fb_t* frame = esp_camera_fb_get();
//     if (!frame) {
//         ESP_LOGE("CameraOV7670", "Failed to get frame buffer");
//         return nullptr;
//     }

//     return frame;
// }

// void CameraOV7670::releaseFrame(camera_fb_t* frame) {
//     if (frame) {
//         esp_camera_fb_return(frame);
//     }
// }

// void CameraOV7670::powerDown() {
//     gpio_set_level((gpio_num_t)CAM_PWDN, 1);
//     _initialized = false;
// }

// void CameraOV7670::wakeUp() {
//     gpio_set_level((gpio_num_t)CAM_PWDN, 0);
//     begin();  // reinicializa a câmera
//     // Aplicar um pequeno delay depois de inicializala
// }

// void CameraOV7670::setupPins() {
//     gpio_reset_pin((gpio_num_t)CAM_PWDN);
//     gpio_set_direction((gpio_num_t)CAM_PWDN, GPIO_MODE_OUTPUT);
//     gpio_set_level((gpio_num_t)CAM_PWDN, 0);
// }

// } // namespace drivers