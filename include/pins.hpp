#pragma once

/* Pinos do sensor de umidade*/
#define SOIL_MOISTURE_PIN 4 //pino analógico

/* Pinos do sensor de luminosidade*/
#define LDR_PIN  6  // Pino analógico

/* Pinos do sensor de temperatura*/
#define TEMP_PIN 5 // Pino digital

/* Pinos I2C*/
#define I2C_SCL 7
#define I2C_SDA 15

/* Pino de nível da bateria */
#define BATERY_PIN 34 // A DEFINIR

// /* Pinos da câmera*/
// #define CAM_SDA         15   // Pino de dados I2C
// #define CAM_SCL         7  // Pino de clock I2C
// #define CAM_VSYNC       16  // Sincronia vertical
// #define CAM_HREF        17  // Referência horizontal (indica inicio/fim da linha)
// #define CAM_PCLK        18  // Clock do pixel
// #define CAM_XCLK        8   // Clock externo
// #define CAM_PWDN        48  // Power down (desliga)
// #define CAM_RESET       47  // Reset da câmera

// // Pinos de dados da câmera
// #define CAM_D0 35
// #define CAM_D1 36
// #define CAM_D2 37
// #define CAM_D3 38
// #define CAM_D4 39
// #define CAM_D5 40
// #define CAM_D6 41
// #define CAM_D7 42


/* H-Bridge pins */

// #define ENA_PIN 0x77
// #define ENB_PIN 0x77

// #define IN1_PIN 0x77
// #define IN2_PIN 0x77
// #define IN3_PIN 0x77
// #define IN4_PIN 0x77

#define IN1_PIN 0x77 //apague
#define IN2_PIN 0x77
#define IN3_PIN 0x77
#define IN4_PIN 0x77


/* Rotary Encoder pins */

#define SIGA_PIN 0x77
#define SIGB_PIN 0x77
