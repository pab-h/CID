// include/application/SensorManager.hpp

#ifndef SENSOR_MANAGER_HPP
#define SENSOR_MANAGER_HPP

#include "entity/SensorData.hpp"
#include "drivers/LuminositySensor.hpp"
#include "drivers/MoistureSensor.hpp"

namespace application {

class SensorManager {
private:
    drivers::LuminositySensor ldrSensor;
    drivers::MoistureSensor moistureSensor;

public:
    // Construtor: Inicializa os drivers de sensor com seus respectivos pinos
    SensorManager();

    // Método para ler dados de todos os sensores e retornar um SensorData
    entity::SensorData readSensorData();

    // Opcional: Métodos para calibrar sensores, se você quiser expor isso
    void calibrateLuminosity(uint16_t minValue, uint16_t maxValue);
    void calibrateMoisture(uint16_t minValue, uint16_t maxValue);
};

} // namespace application

#endif // SENSOR_MANAGER_HPP