#include <Adafruit_MLX90614.h>

typedef enum {
    OFF,
    FEVER_OK,
    FEVER_WARNING,
    DISTANCE_RIGHT,
    DISTANCE_NEARLY_RIGHT,
    DISTANCE_TOO_FAR
} indicator_status;

int ultrasound_measure_distance();
void set_indicator_status(indicator_status status);
Adafruit_MLX90614 temperature_sensor = Adafruit_MLX90614();

const int fever_indicator_pin = 8;
const int ultrasound_trigger_pin = 9;
const int ultrasound_echo_pin = 10;
const int orange_indicator_pin = 11;
const int red_indicator_pin = 12;
const int green_indicator_pin = 13;


void setup() {
    Serial.begin(9600);
    pinMode(ultrasound_echo_pin, INPUT);
    pinMode(ultrasound_trigger_pin, OUTPUT);
    pinMode(fever_indicator_pin, OUTPUT);
    pinMode(green_indicator_pin, OUTPUT);
    pinMode(orange_indicator_pin, OUTPUT);
    pinMode(red_indicator_pin, OUTPUT);
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
  
    delay(250);
    if (distance > 30) {
        set_indicator_status(OFF);
    } else if (distance > 20) {
        set_indicator_status(DISTANCE_TOO_FAR);
    } else if (distance > 15) {
        set_indicator_status(DISTANCE_NEARLY_RIGHT);
    } else if (distance <= 15) {
        set_indicator_status(DISTANCE_RIGHT);
        delay(1000);
        if (temperature_sensor.readObjectTempC() > 20) {
            set_indicator_status(FEVER_WARNING);
        } else {
            set_indicator_status(FEVER_OK);
        }
        // Wait for the person to go away
        while(distance < 20) delay(250);
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
            digitalWrite(red_indicator_pin, LOW);
            digitalWrite(orange_indicator_pin, LOW);
            digitalWrite(green_indicator_pin, LOW);
            digitalWrite(fever_indicator_pin, LOW);
            return;
        case DISTANCE_TOO_FAR:
            digitalWrite(red_indicator_pin, HIGH);
            digitalWrite(orange_indicator_pin, LOW);
            digitalWrite(green_indicator_pin, LOW);
            digitalWrite(fever_indicator_pin, LOW);
            return;
        case DISTANCE_NEARLY_RIGHT:
            digitalWrite(red_indicator_pin, LOW);
            digitalWrite(orange_indicator_pin, HIGH);
            digitalWrite(green_indicator_pin, LOW);
            digitalWrite(fever_indicator_pin, LOW);
            return;
        case DISTANCE_RIGHT:
            digitalWrite(red_indicator_pin, LOW);
            digitalWrite(orange_indicator_pin, LOW);
            digitalWrite(green_indicator_pin, HIGH);
            digitalWrite(fever_indicator_pin, LOW);
            return;
        case FEVER_OK:
            digitalWrite(red_indicator_pin, LOW);
            digitalWrite(orange_indicator_pin, LOW);
            digitalWrite(green_indicator_pin, LOW);
            digitalWrite(fever_indicator_pin, HIGH);
            return;
        case FEVER_WARNING:
            digitalWrite(red_indicator_pin, HIGH);
            digitalWrite(orange_indicator_pin, LOW);
            digitalWrite(green_indicator_pin, LOW);
            digitalWrite(fever_indicator_pin, HIGH);
            return;
    }
}
