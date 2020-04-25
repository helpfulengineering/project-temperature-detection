#ifndef USER_CONFIG_H
#define USER_CONFIG_H

// Switches
// #define ENABLE_SONAR 
// #define INVERT_INDICATORS

// Times (bauds and milliseconds)
#define SERIAL_MONITOR_SPEED        9600
#ifndef SENSOR_STABILIZATION_TIME
#define SENSOR_STABILIZATION_TIME   3500
#endif
#define TIME_BETWEEN_READINGS       500
#define DISPLAY_TIME                2000

// Sampling (count and milliseconds)
#define TEMPERATURE_SAMPLES         3
#define TEMPERATURE_INTERVAL        500
#define DISTANCE_SAMPLES            5
#define DISTANCE_INTERVAL           100 // >60 as per Sparkfun HC-SR04 datasheet

// Distances (centimeters)
#define OFF_DISTANCE                30
#define DETECTION_DISTANCE          15

// Temperatures (celsius degrees)
#define LIMIT_FEVER                 30

// Pins
#ifndef ULTRASOUND_TRIGGER_PIN
#define ULTRASOUND_TRIGGER_PIN      2
#endif
#ifndef ULTRASOUND_ECHO_PIN
#define ULTRASOUND_ECHO_PIN         3
#endif
#ifndef GREEN_INDICATOR_PIN
#define GREEN_INDICATOR_PIN         4
#endif
#ifndef ORANGE_INDICATOR_PIN
#define ORANGE_INDICATOR_PIN        5
#endif
#ifndef RED_INDICATOR_PIN
#define RED_INDICATOR_PIN           6 // 13 to use Arduino Uno builtin LED
#endif
#ifndef BUTTON_PIN
#define BUTTON_PIN                  7 // 37 to use BUTTON A on M5StickC
#endif
#ifdef ESP32
#define ESP32_SDA_PIN               0
#define ESP32_SCL_PIN               26
#endif

#endif
