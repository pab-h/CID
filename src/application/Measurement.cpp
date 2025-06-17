#include <application/Measurement.hpp>
#include <esp_log.h>

using namespace application;

Measurement::Measurement(){

    resetStates();

    // if (!camera.begin()) {
    //     ESP_LOGE("Measurement", "Falha ao inicializar a câmera");
    //     sensorStatus.error = MeasurementError::CAMERA_FAIL;
    // }

    dht.begin();

}

void Measurement::resetStates() {

    sensorData = SensorData{};
    sensorStatus = SensorStatus{};
    sensorStatus.isSensing = false;
    sensorStatus.error = MeasurementError::NONE;

}

bool Measurement::isAllReady() const {

    return sensorStatus.temperatureReady &&
           sensorStatus.humidityReady &&
           sensorStatus.moistureReady &&
           sensorStatus.luminosityReady &&
           sensorStatus.pictureReady;

}

void Measurement::measureTemperature() {

    sensorStatus.isSensing = true;

    float temp = dht.readTemperature();
    if (std::isnan(temp)) {
        sensorStatus.error = MeasurementError::TEMPERATURE_FAIL;
        sensorStatus.temperatureReady = false;
        ESP_LOGE("Measurement", "Falha na leitura da temperatura");
    } else {
        sensorData.temperature = temp;
        sensorStatus.temperatureReady = true;
    }

    sensorStatus.isSensing = false;

}

void Measurement::measureUmidity() {

    sensorStatus.isSensing = true;

    float hum = dht.readHumidity();
    if (std::isnan(hum)) {
        sensorStatus.error = MeasurementError::HUMIDITY_FAIL;
        sensorStatus.humidityReady = false;
        ESP_LOGE("Measurement", "Falha na leitura da umidade");
    } else {
        sensorData.humidity = hum;
        sensorStatus.humidityReady = true;
    }

    sensorStatus.isSensing = false;

}

void Measurement::measureLuminosity() {

    sensorStatus.isSensing = true;

    uint8_t percentage = ldr.readPercentage();
    if (ldr.read() <= 3) {
        sensorStatus.error = MeasurementError::LUMINOSITY_FAIL;
        sensorStatus.luminosityReady = false;
        ESP_LOGE("Measurement", "Falha na leitura da luminosidade (LDR provavelmente desconectado)");
    } else {
        sensorData.luminositySensor = percentage;
        sensorStatus.luminosityReady = true;
    }

    sensorStatus.isSensing = false;

}

void Measurement::measureMoisture() {

    sensorStatus.isSensing = true;

    uint16_t percentage = soil.readPercentage();
    if (soil.read() <= 3) {
        sensorStatus.error = MeasurementError::MOISTURE_FAIL;
        sensorStatus.moistureReady = false;
        ESP_LOGE("Measurement", "Falha na leitura da umidade do solo (Sensor provavelmente desconectado)");
    } else {
        sensorData.soilMoisture = percentage;
        sensorStatus.moistureReady = true;
    }

    sensorStatus.isSensing = false;

}

//O Ideal seria ligar a câmera assim que o CID entrasse no modo de sensoriamento
void Measurement::takePicture() {
    camera.wakeUp();

    if (!camera.begin()) {
        ESP_LOGE("Measurement", "Camera init failed");
        return;
    }

    camera_fb_t* frame = camera.capture();
    if (!frame) {
        ESP_LOGE("Measurement", "Failed to capture image");
        return;
    }

    camera.powerDown();
}

MeasurementResponse Measurement::getMeasures() {
    MeasurementResponse response;

    if (sensorStatus.isSensing) {
        ESP_LOGW("Measurement", "Tentativa de enviar medidas enquanto sensores ainda estão medindo.");
        response.error = MeasurementError::BUSY;
        return response;
    }

     if (!isAllReady()) {
        if (sensorStatus.error != MeasurementError::NONE) {
            ESP_LOGE("Measurement", "Erro na medição: %d", static_cast<int>(sensorStatus.error));
            response.error = sensorStatus.error;
        } else {
            ESP_LOGW("Measurement", "Medição incompleta: nem todos sensores estão prontos");
            response.error = MeasurementError::INCOMPLETE;
        }
        return response;
    }

    response.data = sensorData;
    response.error = sensorStatus.error;
    return response;
}