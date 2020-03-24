#include <LiquidCrystal.h>
#include <Adafruit_MLX90614.h>

typedef enum {
    OFF,
    FEVER_OK,
    FEVER_WARNING,
    DISTANCE_RIGHT,
    DISTANCE_TOO_FAR,
    DISTANCE_TOO_CLOSE,
    DISTANCE_NEARLY_RIGHT,
} indicator_status;

int ultrasound_measure_distance();
void set_indicator_status(indicator_status status);
Adafruit_MLX90614 temperature_sensor = Adafruit_MLX90614();

const int no_fever_indicator_pin = 8;
const int ultrasound_trigger_pin = 9;
const int ultrasound_echo_pin = 10;
const int too_close_indicator_pin = 11;
const int too_far_indicator_pin = 12;
const int right_distance_indicator_pin = 13;


void setup() {
    Serial.begin(9600);
    pinMode(ultrasound_echo_pin, INPUT);
    pinMode(ultrasound_trigger_pin, OUTPUT);
    pinMode(no_fever_indicator_pin, OUTPUT);
    pinMode(right_distance_indicator_pin, OUTPUT);
    pinMode(too_close_indicator_pin, OUTPUT);
    pinMode(too_far_indicator_pin, OUTPUT);
    temperature_sensor.begin();
}


void loop() {
    int distance = ultrasound_measure_distance();
    int ambient_temperature = temperature_sensor.readAmbientTempC();
    int object_temperature = temperature_sensor.readObjectTempC();
    
    Serial.print("Distance (centimeters): ");
    Serial.println(distance);
    Serial.print("Ambient temperature (celsius degrees): ");
    Serial.print(ambient_temperature);
    Serial.print("Object temperature (celsius degrees): ");
    Serial.print(object_temperature);
  
    if (distance >= 20) {
        set_indicator_status(DISTANCE_TOO_FAR);
        delay(1000);
    } else if (distance >= 15) {
        set_indicator_status(DISTANCE_NEARLY_RIGHT);
        delay(1000);
    } else if (distance < 15) {
        set_indicator_status(DISTANCE_RIGHT);
        delay(3000);
        if (temperature_sensor.readObjectTempC() > 20) {
            set_indicator_status(FEVER_WARNING);
        } else {
            set_indicator_status(FEVER_OK);
        }
        delay(3000);
    }
}


int ultrasound_measure_distance() {
    digitalWrite(ultrasound_trigger_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(ultrasound_trigger_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(ultrasound_trigger_pin, LOW);
    long duration = pulseIn(ultrasound_echo_pin, HIGH);
    int distance = duration * 0.034 / 2;
    return distance; // in centimeters
}


void set_indicator_status(indicator_status status) {
    switch(status) {
        case OFF:
            digitalWrite(too_far_indicator_pin, LOW);
            digitalWrite(too_close_indicator_pin, LOW);
            digitalWrite(right_distance_indicator_pin, LOW);
            digitalWrite(no_fever_indicator_pin, LOW);
            return;
        case DISTANCE_TOO_FAR:
            digitalWrite(too_far_indicator_pin, HIGH);
            digitalWrite(too_close_indicator_pin, LOW);
            digitalWrite(right_distance_indicator_pin, LOW);
            digitalWrite(no_fever_indicator_pin, LOW);
            return;
        case DISTANCE_TOO_CLOSE:
            digitalWrite(too_far_indicator_pin, LOW);
            digitalWrite(too_close_indicator_pin, HIGH);
            digitalWrite(right_distance_indicator_pin, LOW);
            digitalWrite(no_fever_indicator_pin, LOW);
            return;
        case DISTANCE_RIGHT:
            digitalWrite(too_far_indicator_pin, LOW);
            digitalWrite(too_close_indicator_pin, LOW);
            digitalWrite(right_distance_indicator_pin, HIGH);
            digitalWrite(no_fever_indicator_pin, LOW);
            return;
        case FEVER_OK:
            digitalWrite(too_far_indicator_pin, LOW);
            digitalWrite(too_close_indicator_pin, LOW);
            digitalWrite(right_distance_indicator_pin, LOW);
            digitalWrite(no_fever_indicator_pin, HIGH);
            return;
        case FEVER_WARNING:
            digitalWrite(too_far_indicator_pin, HIGH);
            digitalWrite(too_close_indicator_pin, HIGH);
            digitalWrite(right_distance_indicator_pin, HIGH);
            digitalWrite(no_fever_indicator_pin, HIGH);
            return;
    }
}
