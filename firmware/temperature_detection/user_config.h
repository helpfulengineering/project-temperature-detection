#ifndef user_config_h
#define user_config_h

#define serial_monitor_speed    9600 // serial monitor speed
#define time_between_readings   500 // time between sensors readings in ms
#define time_before_leaving     250 // time between sensors readings in ms
#define time_before_sensor_stab 3500

// Pins definition
#define ultrasound_trigger_pin  2
#define ultrasound_echo_pin     3
#define green_indicator_pin     4
#define orange_indicator_pin    5
#define red_indicator_pin       6 // if you want to use the built in UNO led you can set 13

// Sampling average size
#define temperature_samples  3
#define distance_samples     5

#ifdef ESP32 // pin definition for ESP32 only
#define sda_pin                 0
#define scl_pin                 26
#endif

// Distances limits in cm
#define off_distance            30
#define dectection_distance     20
#define limit_distance          15
#define next_person_distance    25

// Temperature limits
#define limit_fever             20

#endif
