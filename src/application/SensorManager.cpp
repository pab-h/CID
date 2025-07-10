// src/application/SensorManager.cpp

#include "application/SensorManager.hpp"
#include "pins.hpp"      // Para as definições dos pinos
#include <Arduino.h>     // Para Serial.println, etc.

namespace application {

// Construtor do SensorManager
SensorManager::SensorManager()
    // Inicializa as instâncias dos drivers de sensor usando os pinos definidos em pins.hpp
    : ldrSensor(LDR_PIN),
      moistureSensor(SOIL_MOISTURE_PIN)
{
    Serial.println("[SensorManager] Drivers de sensores inicializados.");

    // Opcional: Você pode chamar a calibração aqui se tiver valores padrão ou lidos da EEPROM/Flash
    // Por exemplo, se LUMINOSITY_MIN_VALUE e LUMINOSITY_MAX_VALUE forem globais/constantes
    // ldrSensor.calibrate(LUMINOSITY_MIN_VALUE, LUMINOSITY_MAX_VALUE);
    // moistureSensor.calibrate(MOISURE_MIN_VALUE, MOISURE_MAX_VALUE);
}

// Método para ler dados de todos os sensores
entity::SensorData SensorManager::readSensorData() {
    Serial.println("[SensorManager] Coletando leituras dos sensores...");

    // Lê a luminosidade usando o driver LuminositySensor
    // Decida se quer a leitura bruta (read()) ou a porcentagem (readPercentage())
    // A sua entidade SensorData espera um 'int' para 'luminosity'.
    uint16_t luminosityRaw = ldrSensor.read();
    uint8_t luminosityPercentage = ldrSensor.readPercentage(); // Se preferir porcentagem

    // Lê a umidade do solo usando o driver MoistureSensor
    // A sua entidade SensorData espera um 'float' para 'moisture'.
    uint16_t moistureRaw = moistureSensor.read();
    uint8_t moisturePercentage = moistureSensor.readPercentage(); // Se preferir porcentagem

    // Por enquanto, temperatura e umidade do ar serão 0.0 e 0 (ou valores padrão)
    // até que você adicione um driver para DHT ou sensor similar.
    float temperature = 0.0; // Substitua pela leitura real
    float humidity = 0.0;    // Substitua pela leitura real

    Serial.print("Luminosidade (raw): "); Serial.println(luminosityRaw);
    Serial.print("Luminosidade (%): "); Serial.println(luminosityPercentage);
    Serial.print("Umidade do solo (raw): "); Serial.println(moistureRaw);
    Serial.print("Umidade do solo (%): "); Serial.println(moisturePercentage);


    // Retorna uma nova instância de SensorData com os valores coletados
    // Decida qual valor de luminosidade e umidade você quer enviar (raw ou percentage).
    // Vou usar a porcentagem para umidade do solo e a leitura bruta para luminosidade como exemplo.
    return entity::SensorData(temperature, (float)moisturePercentage, luminosityRaw, humidity);
}

// Implementação opcional dos métodos de calibração
void SensorManager::calibrateLuminosity(uint16_t minValue, uint16_t maxValue) {
    ldrSensor.calibrate(minValue, maxValue);
    Serial.println("[SensorManager] Sensor de luminosidade calibrado.");
}

void SensorManager::calibrateMoisture(uint16_t minValue, uint16_t maxValue) {
    moistureSensor.calibrate(minValue, maxValue);
    Serial.println("[SensorManager] Sensor de umidade do solo calibrado.");
}

} // namespace application