#include "user_config.h"
#include <Adafruit_MLX90614.h>


typedef enum {
    INDICATOR_RED = 1 << 0,
    INDICATOR_ORANGE = 1 << 1,
    INDICATOR_GREEN = 1 << 2
} indicator;

typedef enum {
    STATUS_FEVER_LOW = INDICATOR_ORANGE || INDICATOR_GREEN,
    STATUS_FEVER_HIGH = INDICATOR_ORANGE || INDICATOR_RED,
    STATUS_DISTANCE_RIGHT = INDICATOR_GREEN,
    STATUS_DISTANCE_WRONG = INDICATOR_RED,
    STATUS_OFF = 0
} status;


int measure_distance();
float measure_temperature();
void display_status(status indicators);
Adafruit_MLX90614 temperature_sensor = Adafruit_MLX90614();

void setup() {    
    pinMode(ultrasound_echo_pin, INPUT);
    pinMode(ultrasound_trigger_pin, OUTPUT);
    pinMode(green_indicator_pin, OUTPUT);
    pinMode(orange_indicator_pin, OUTPUT);
    pinMode(red_indicator_pin, OUTPUT);

    Serial.begin(serial_monitor_speed);
    
    #ifdef ESP32
        Wire.begin(sda_pin,scl_pin);
    #else
        temperature_sensor.begin();
    #endif
}


void loop() {
    int distance = measure_distance();

    delay(time_between_readings);
    if (distance > off_distance) {
        display_status(STATUS_OFF);
    } else if (distance > dectection_distance) {
        display_status(STATUS_DISTANCE_WRONG);
    } else if (distance <= dectection_distance) {
        display_status(STATUS_DISTANCE_RIGHT);
        delay(time_before_sensor_stab); // Wait for the sensor to stabilize.
        display_status(
            (measure_temperature() > limit_fever)
            ? STATUS_FEVER_HIGH : STATUS_FEVER_LOW
        );
        // Wait for the person to go away...
        while(measure_distance() <= 25) delay(time_before_leaving);
    }
}


int measure_distance() {
    digitalWrite(ultrasound_trigger_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(ultrasound_trigger_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(ultrasound_trigger_pin, LOW);
    long duration = pulseIn(ultrasound_echo_pin, HIGH);
    int distance = duration * 0.034 / 2;
    return distance; // in centimeters
}


float measure_temperature() {
    return temperature_sensor.readObjectTempC(); // in celsius degrees
}


void display_status(status indicators) {
    digitalWrite(
        red_indicator_pin,
        (indicators && INDICATOR_RED) ? HIGH : LOW
    );
    digitalWrite(
        orange_indicator_pin,
        (indicators && INDICATOR_ORANGE) ? HIGH : LOW
    );
    digitalWrite(
        green_indicator_pin,
        (indicators && INDICATOR_GREEN) ? HIGH : LOW
    );
}
