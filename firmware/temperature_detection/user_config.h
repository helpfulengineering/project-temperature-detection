#ifndef USER_CONFIG_H
#define USER_CONFIG_H

// Switches
//#define ENABLE_SONAR // Uncomment to enable SONAR if you are using arduino IDE

// Pins
#define ULTRASOUND_TRIGGER_PIN  2
#define ULTRASOUND_ECHO_PIN     3
#ifndef GREEN_INDICATOR_PIN
#define GREEN_INDICATOR_PIN     4
#endif
#ifndef GREEN_INDICATOR_OFF
#define GREEN_INDICATOR_OFF     0 // define if the LED status is HIGH (1) or LOW (0) when OFF
#endif
#ifndef ORANGE_INDICATOR_PIN
#define ORANGE_INDICATOR_PIN    5
#endif
#ifndef ORANGE_INDICATOR_OFF
#define ORANGE_INDICATOR_OFF    0 // define if the LED status is HIGH (1) or LOW (0) when OFF
#endif
#ifndef RED_INDICATOR_PIN
#define RED_INDICATOR_PIN       6 // 13 to use Arduino Uno builtin LED
#endif
#ifndef RED_INDICATOR_OFF
#define RED_INDICATOR_OFF       0 // define if the LED status is HIGH (1) or LOW (0) when OFF
#endif
#define BUTTON_PIN              37 // 37 Btn A on M5StickC
#ifndef BUTTON_PIN_ON
#define BUTTON_PIN_ON           1 // define if the button has a LOW (0) or HIGH(1) status when pressed
#endif
// Times (bauds and milliseconds)
#define SERIAL_MONITOR_SPEED    9600
#define TIME_BETWEEN_READINGS   500

#ifdef ENABLE_SONAR // if the sonar is not used we don't need to wait
#define SENSOR_STABILIZATION    3500
#else
#define SENSOR_STABILIZATION    0
#endif

#ifndef DISPLAY_TIME // Time defining the ms of LED are ON
#define DISPLAY_TIME            2000
#endif

// Sampling (count and milliseconds)
#define TEMPERATURE_SAMPLES     3
#define TEMPERATURE_INTERVAL    500
#define DISTANCE_SAMPLES        5
#define DISTANCE_INTERVAL       100 // > 60 as per Sparkfun HC-SR04 datasheet

// Distances (centimeters)
#define OFF_DISTANCE            30
#define DETECTION_DISTANCE      15

// Temperatures (celsius degrees)
#define LIMIT_FEVER             30

// ESP32-specific
#ifdef ESP32
#define ESP32_SDA_PIN           0
#define ESP32_SCL_PIN           26
#endif

#endif
