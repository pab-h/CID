#include <application/Measurement.hpp>
#include <esp_log.h>
#include <Arduino.h>

using namespace application;

Measurement::Measurement(){

    //resetStates();

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
           sensorStatus.luminosityReady; //&&
           //sensorStatus.pictureReady;

}

void Measurement::measureTemperature() {

    sensorStatus.isSensing = true;

    float temp = dht.readTemperature();
    if (std::isnan(temp)) {
        sensorStatus.error = MeasurementError::TEMPERATURE_FAIL;
        sensorStatus.temperatureReady = false;
        Serial.printf("Measurement %s", "Falha na leitura da temperatura");
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
        Serial.printf("Measurement %s", "Falha na leitura da umidade");
    } else {
        sensorData.humidity = hum;
        sensorStatus.humidityReady = true;
    }

    sensorStatus.isSensing = false;

}

void Measurement::measureLuminosity() {

    sensorStatus.isSensing = true;

    uint8_t percentage = ldr.readPercentage();
    //ldr.read() <= 3
    if (false) {
        sensorStatus.error = MeasurementError::LUMINOSITY_FAIL;
        sensorStatus.luminosityReady = false;
        Serial.printf("Measurement %s", "Falha na leitura da luminosidade (LDR provavelmente desconectado)");
    } else {
        sensorData.luminositySensor = percentage;
        Serial.printf("Valor da temperatura: %d", percentage);
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
        Serial.printf("Measurement %s", "Falha na leitura da umidade do solo (Sensor provavelmente desconectado)");
    } else {
        sensorData.soilMoisture = percentage;
        sensorStatus.moistureReady = true;
    }

    sensorStatus.isSensing = false;

}

// void Measurement::prepareCamera() {

//     camera.wakeUp();
//     if (!camera.begin()) {
//         sensorStatus.error = MeasurementError::CAMERA_FAIL;
//         ESP_LOGE("Measurement", "Falha ao iniciar a câmera no modo de sensoriamento");
//     }

// }

// void Measurement::takePicture() {
//     sensorStatus.isSensing = true;

//     camera_fb_t* frame = camera.capture();
//     if (!frame) {
//         sensorStatus.error = MeasurementError::CAMERA_FAIL;
//         sensorStatus.pictureReady = false;
//         ESP_LOGE("Measurement", "Falha ao capturar imagem");
//     } else {
//         sensorStatus.pictureReady = true;
//     }

//     camera.powerDown();
//     sensorStatus.isSensing = false;
// }

MeasurementResponse Measurement::getMeasures() {
    MeasurementResponse response;

    if (sensorStatus.isSensing) {
        Serial.printf("Measurement %s", "Tentativa de enviar medidas enquanto sensores ainda estão medindo.");
        response.error = MeasurementError::BUSY;
        return response;
    }

     if (!isAllReady()) {
        if (sensorStatus.error != MeasurementError::NONE) {
            Serial.printf("Measurement %s", "Erro na medição: %d", static_cast<int>(sensorStatus.error));
            response.error = sensorStatus.error;
        } else {
            Serial.printf("Measurement %s", "Medição incompleta: nem todos sensores estão prontos");
            response.error = MeasurementError::INCOMPLETE;
        }
        return response;
    }

    response.data = sensorData;
    response.error = sensorStatus.error;
    return response;
}