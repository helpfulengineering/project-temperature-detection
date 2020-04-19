#ifndef USER_CONFIG_H
#define USER_CONFIG_H

// Switches
#define ENABLE_SONAR

// Pins
#define ULTRASOUND_TRIGGER_PIN  2
#define ULTRASOUND_ECHO_PIN     3
#define GREEN_INDICATOR_PIN     4
#define ORANGE_INDICATOR_PIN    5
#define RED_INDICATOR_PIN       6 // 13 to use Arduino Uno builtin LED
#define BUTTON_PIN              7

// Times (bauds and milliseconds)
#define SERIAL_MONITOR_SPEED    9600
#define TIME_BETWEEN_READINGS   500
#define SENSOR_STABILIZATION    3500

// Sampling (count and milliseconds)
#define TEMPERATURE_SAMPLES     3
#define TEMPERATURE_INTERVAL    500
#define DISTANCE_SAMPLES        5
#define DISTANCE_INTERVAL       100 // > 60 as per Sparkfun HC-SR04 datasheet

// Distances (centimeters)
#define OFF_DISTANCE            30
#define DETECTION_DISTANCE      15

// Temperatures (celsius degrees)
#define LIMIT_FEVER             20

// ESP32-specific
#ifdef ESP32
#define ESP32_SDA_PIN           0
#define ESP32_SCL_PIN           26
#endif

#endif
