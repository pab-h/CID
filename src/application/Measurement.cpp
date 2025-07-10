#include <application/Measurement.hpp>
#include <esp_log.h>
#include <Arduino.h>

using namespace application;

Measurement::Measurement(){

    dht.begin();

}

inline uint8_t Measurement::to_uint8(MeasurementError err) const{
    return static_cast<uint8_t>(err);
}

inline bool Measurement::hasError(uint8_t flags, MeasurementError error) const {
    return (flags & Measurement::to_uint8(error)) != 0;
}

inline void Measurement::addError(uint8_t &flags, MeasurementError error) {
    flags |= to_uint8(error);
}

inline void Measurement::removeError(uint8_t &flags, MeasurementError error) {
    flags &= ~Measurement::to_uint8(error);
}

inline void Measurement::printErrors(uint8_t flags) {

    Serial.println("Errors:");

    if (flags == 0) {
        Serial.println("NONE");
        return;
    }

    if (flags & static_cast<uint8_t>(MeasurementError::BUSY)) {
        Serial.println("BUSY");
    }
    if (flags & static_cast<uint8_t>(MeasurementError::INCOMPLETE)) {
        Serial.println("INCOMPLETE");
    }
    if (flags & static_cast<uint8_t>(MeasurementError::TEMPERATURE_FAIL)) {
        Serial.println("TEMPERATURE FAIL");
    }
    if (flags & static_cast<uint8_t>(MeasurementError::HUMIDITY_FAIL)) {
        Serial.println("HUMIDITY FAIL");
    }
    if (flags & static_cast<uint8_t>(MeasurementError::MOISTURE_FAIL)) {
        Serial.println("MOISTURE FAIL");
    }
    if (flags & static_cast<uint8_t>(MeasurementError::LUMINOSITY_FAIL)) {
        Serial.println("LUMINOSITY FAIL");
    }

    // if (static_cast<uint8_t>(flags & MeasurementError::CAMERA_FAIL)){
    //     Serial.println("- CAMERA FAIL")
    //};
}

void Measurement::resetStates() {

    sensorData = SensorData{};
    sensorStatus = SensorStatus{};
    sensorStatus.isSensing = false;
    sensorStatus.error = to_uint8(MeasurementError::NONE); 

}

bool Measurement::isAllReady() const {

    bool tempOk = sensorStatus.temperatureReady || hasError(sensorStatus.error, MeasurementError::TEMPERATURE_FAIL);
    bool humOk = sensorStatus.humidityReady || hasError(sensorStatus.error, MeasurementError::HUMIDITY_FAIL);
    bool moistOk = sensorStatus.moistureReady || hasError(sensorStatus.error, MeasurementError::MOISTURE_FAIL);
    bool lumiOk = sensorStatus.luminosityReady || hasError(sensorStatus.error, MeasurementError::LUMINOSITY_FAIL);

    return tempOk && humOk && moistOk && lumiOk;

}

void Measurement::measureTemperature() {

    sensorStatus.isSensing = true;
    float temp = dht.readTemperature();

    if (std::isnan(temp)) {

        addError(sensorStatus.error, MeasurementError::TEMPERATURE_FAIL);

        sensorStatus.temperatureReady = false;
        Serial.printf("Measurement %s", "Falha na leitura da temperatura \n");

    } else {

        removeError(sensorStatus.error, MeasurementError::TEMPERATURE_FAIL);

        sensorData.temperature = temp;
        sensorStatus.temperatureReady = true;

    }

    sensorStatus.isSensing = false;

}

void Measurement::measureHumidity() {

    sensorStatus.isSensing = true;
    float hum = dht.readHumidity();

    if (std::isnan(hum)) {
            
        addError(sensorStatus.error, MeasurementError::HUMIDITY_FAIL);
        
        sensorStatus.humidityReady = false;
        Serial.printf("Measurement %s", "Falha na leitura da umidade \n");

    } else {
        
        removeError(sensorStatus.error, MeasurementError::HUMIDITY_FAIL);

        sensorData.humidity = hum;
        sensorStatus.humidityReady = true;
    }

    sensorStatus.isSensing = false;

}

void Measurement::measureLuminosity() {

    sensorStatus.isSensing = true;
    uint8_t percentage = ldr.readPercentage();

    if (ldr.read() <= 1) {
        
        addError(sensorStatus.error, MeasurementError::LUMINOSITY_FAIL);
        
        sensorStatus.luminosityReady = false;
        Serial.printf("Measurement %s", "Falha na leitura da luminosidade (LDR provavelmente desconectado)\n");

    } else {

        removeError(sensorStatus.error, MeasurementError::LUMINOSITY_FAIL);

        sensorData.luminosity = percentage;
        sensorStatus.luminosityReady = true;

    }

    sensorStatus.isSensing = false;

}

void Measurement::measureMoisture() {

    sensorStatus.isSensing = true;
    uint16_t percentage = soil.readPercentage();

    if (soil.read() <= 3) {

        addError(sensorStatus.error, MeasurementError::MOISTURE_FAIL);

        sensorStatus.moistureReady = false;
        Serial.printf("Measurement %s", "Falha na leitura da umidade do solo (Sensor provavelmente desconectado)\n");

    } else {

        removeError(sensorStatus.error, MeasurementError::MOISTURE_FAIL);

        sensorData.soilMoisture = percentage;
        sensorStatus.moistureReady = true;
    }

    sensorStatus.isSensing = false;

}

MeasurementResponse Measurement::getMeasures() {

    MeasurementResponse response;

    if (sensorStatus.isSensing) {

        response.error = to_uint8(MeasurementError::BUSY);
        Serial.printf("Measurement %s", "Tentativa de enviar medidas enquanto sensores ainda estão medindo. \n");
        
        return response;

    }

    if (!isAllReady()) {

        addError(sensorStatus.error, MeasurementError::INCOMPLETE);
        Serial.printf("Measurement %s", "Tentativa de enviar medidas enquanto nem todas as medidas foram coletadas. \n");

    } else {

        removeError(sensorStatus.error, MeasurementError::INCOMPLETE);
        
    }

    if (sensorStatus.error != 0) {

        printErrors(sensorStatus.error);
        response.error = sensorStatus.error;


    }

    response.data = sensorData;
    response.error = sensorStatus.error;
    return response;

}