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
#define THRESHOLD_DISTANCE          3

// Temperatures (celsius degrees)
#define LIMIT_FEVER                 30
#define WARNING_FEVER               28

// Pins
#ifndef ULTRASOUND_TRIGGER_PIN
#define ULTRASOUND_TRIGGER_PIN      2
#endif
#ifndef ULTRASOUND_ECHO_PIN
#define ULTRASOUND_ECHO_PIN         3
#endif
#ifndef TEMPERATURE_LOW_PIN
#define TEMPERATURE_LOW_PIN         4
#endif
#ifndef TEMPERATURE_MID_PIN
#define TEMPERATURE_MID_PIN         5
#endif
#ifndef TEMPERATURE_HIGH_PIN
#define TEMPERATURE_HIGH_PIN        6
#endif
#ifndef DISTANCE_FARTHER_PIN
#define DISTANCE_FARTHER_PIN        8 // FIXME: why skip the seventh pin?
#endif
#ifndef DISTANCE_STOP_PIN
#define DISTANCE_STOP_PIN           9
#endif
#ifndef DISTANCE_CLOSER_PIN
#define DISTANCE_CLOSER_PIN         10
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
