#pragma once

#define INSERTING_PULSES 3

/* Conversion constants */
#define PULSES_TO_DEGREE      5.0
#define PULSES_TO_CENTIMETERS 1.0

/* Motor power */
#define LEFT_MOTOR_PWM  0x80 
#define RIGHT_MOTOR_PWM 0x80 

/* Temperature consts*/
#define DHTTYPE DHT11

/* Soil moisure default values */
#define MOISURE_MAX_VALUE 4095
#define MOISURE_MIN_VALUE 0

/* Luminosity default values */
#define LUMINOSITY_MAX_VALUE 4095
#define LUMINOSITY_MIN_VALUE 0

/*Display configurations*/
#define SCREEN_WIDTH   128    //< Display x max dimension
#define SCREEN_HEIGHT  64    //< Display y max dimension
#define OLED_RESET     -1    //< Display no reset pin
#define SCREEN_ADDRESS 0x3C //< Display I2C adress