#ifndef USER_CONFIG_H
#define USER_CONFIG_H

// Switches
// #define ENABLE_SONAR 
// #define INVERT_INDICATORS
// #define SENSOR_ZTP115M // See also ZTP115M_SENSOR_* defines
#define SENSOR_MLX90614


// Boards
// #define M5STICKC 
// #define ANOTHER 

#ifdef M5STICKC
    #define ENABLE_BUTTON
    #define INVERT_INDICATORS
    #undef ENABLE_INDICATORS
    #undef ENABLE_SONAR
#endif

#ifdef ANOTHER
    #define ENABLE_BUTTON
    #define ENABLE_INDICATORS
    #define ENABLE_SONAR
#endif

// Times (bauds and milliseconds)
#define SERIAL_MONITOR_SPEED        115200
#define SENSOR_STABILIZATION_TIME   100
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
#ifndef ZTP115M_SENSOR_PIN
#define ZTP115M_SENSOR_PIN          36
#endif
#ifdef ESP32
#define ESP32_SDA_PIN               0
#define ESP32_SCL_PIN               26
#endif

// ZTP115M-specific ADC settings
#ifdef ESP32

#ifndef ZTP115M_SENSOR_REFERENCE
#define ZTP115M_SENSOR_REFERENCE    3.3
#endif
#ifndef ZTP115M_SENSOR_STEPS
#define ZTP115M_SENSOR_STEPS        4096
#endif

#else

#ifndef ZTP115M_SENSOR_REFERENCE
#define ZTP115M_SENSOR_REFERENCE    5
#endif
#ifndef ZTP115M_SENSOR_STEPS
#define ZTP115M_SENSOR_STEPS        1024 // Might not offer enough resolution.
#endif

#endif

#endif
