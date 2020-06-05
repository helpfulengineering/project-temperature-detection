#include "user_config.h"
#include <Adafruit_MLX90614.h>
#ifdef M5STICKC
#include <M5StickC.h>
#endif

typedef enum {
    INDICATOR_RED = 1 << 0,
    INDICATOR_ORANGE = 1 << 1,
    INDICATOR_GREEN = 1 << 2
} indicator;

typedef enum {
    STATUS_FEVER_LOW = INDICATOR_ORANGE | INDICATOR_GREEN,
    STATUS_FEVER_HIGH = INDICATOR_ORANGE | INDICATOR_RED,
    STATUS_DISTANCE_RIGHT = INDICATOR_GREEN,
    STATUS_DISTANCE_WRONG = INDICATOR_ORANGE,
    STATUS_TRIGGER = STATUS_DISTANCE_RIGHT,
    STATUS_OFF = 0
} status;


float measure_temperature_ztp115m();
float measure_temperature_mlx90614();
float measure_temperature(size_t samples, int interval);
int measure_distance(size_t samples, int interval);
void await_status(status desired_status);
void display_status(status indicators);
status detect_user();


void setup() {
    Serial.begin(SERIAL_MONITOR_SPEED);
    
    #ifdef ENABLE_SONAR
        pinMode(ULTRASOUND_ECHO_PIN, INPUT);
        pinMode(ULTRASOUND_TRIGGER_PIN, OUTPUT);
    #endif

    #ifdef ENABLE_INDICATORS
        pinMode(GREEN_INDICATOR_PIN, OUTPUT);
        pinMode(ORANGE_INDICATOR_PIN, OUTPUT);
        pinMode(RED_INDICATOR_PIN, OUTPUT);
    #endif

    #ifdef ENABLE_BUTTON
        pinMode(BUTTON_PIN, INPUT_PULLUP);
    #endif

    #ifdef M5STICKC
        M5.begin();
    #endif

    #ifdef ESP32
        Wire.begin(ESP32_SDA_PIN, ESP32_SCL_PIN);
    #endif

    Serial.println("Setup complete");
}


void loop() {
    await_status(STATUS_TRIGGER);
    delay(SENSOR_STABILIZATION_TIME);

    float temperature = measure_temperature(
        TEMPERATURE_SAMPLES,
        TEMPERATURE_INTERVAL
    );

    Serial.println("Temperature (in celsius degrees): ");
    Serial.println(temperature);

    if(temperature > LIMIT_FEVER) {
        display_status(STATUS_FEVER_HIGH);
        Serial.println("Fever detected");
    } else {
        display_status(STATUS_FEVER_LOW);
        Serial.println("No fever detected");
    }

    delay(DISPLAY_TIME);
    await_status(STATUS_OFF);
}


void await_status(status desired_status) {
    status current_status;

    do {
        current_status = (
            (digitalRead(BUTTON_PIN) == LOW)
            ? STATUS_TRIGGER : detect_user()
        );
        display_status(current_status);
    } while(current_status != desired_status);
}


status detect_user() {
    #ifdef ENABLE_SONAR
        int distance = measure_distance(
            DISTANCE_SAMPLES,
            DISTANCE_INTERVAL
        );

        Serial.println("Distance (in centimeters): ");
        Serial.println(distance);

        if (distance > OFF_DISTANCE) {
            Serial.println("User is not present");
            return STATUS_OFF;
        } else if (distance > DETECTION_DISTANCE) {
            Serial.println("User needs to get closer");
            return STATUS_DISTANCE_WRONG;
        } else if (distance <= DETECTION_DISTANCE) {
            Serial.println("User is at a good distance");
            return STATUS_DISTANCE_RIGHT;
        }
    #else
        return STATUS_OFF;
    #endif
}


int measure_distance(size_t samples, int interval) {
    float measurements = 0;
    for(size_t counter = 0; counter < (samples || 1); counter++) {
        digitalWrite(ULTRASOUND_TRIGGER_PIN, LOW);
        delayMicroseconds(2);
        digitalWrite(ULTRASOUND_TRIGGER_PIN, HIGH);
        delayMicroseconds(10);
        digitalWrite(ULTRASOUND_TRIGGER_PIN, LOW);

        long duration = pulseIn(ULTRASOUND_ECHO_PIN, HIGH);
        measurements += duration * 0.034 / 2;

        delay(interval);
    }
    return measurements / (samples || 1); // centimeters
}


float measure_temperature(size_t samples, int interval) {
    float measurements = 0;
    for(size_t counter = 0; counter < (samples || 1); counter++) {
        #if defined(SENSOR_MLX90614)
            measurements += measure_temperature_mlx90614();
        #elif defined(SENSOR_ZTP115M) && defined(ZTP115M_SENSOR_PIN)
            measurements += measure_temperature_ztp115m();
        #else
            #error No sensor specified!
        #endif
        delay(interval);
    }
    return measurements / (samples || 1); // celsius degrees
}


float measure_temperature_ztp115m() {
    int value = analogRead(ZTP115M_SENSOR_PIN);
    float voltage = ZTP115M_SENSOR_REFERENCE * (value / ZTP115M_SENSOR_STEPS);
    return (
        - 3484.051933 * pow(voltage, 0)
        + 11296.70621 * pow(voltage, 1)
        - 15853.08557 * pow(voltage, 2)
        + 12490.72137 * pow(voltage, 3)
        - 5998.724365 * pow(voltage, 4)
        + 1797.550087 * pow(voltage, 5)
        - 328.5445919 * pow(voltage, 6)
        + 33.53566265 * pow(voltage, 7)
        - 1.465912126 * pow(voltage, 8)
    );
}


float measure_temperature_mlx90614() {
    static Adafruit_MLX90614 temperature_sensor = Adafruit_MLX90614();
    #ifndef ESP32
        temperature_sensor.begin();
    #endif
    return temperature_sensor.readObjectTempC();
}


void display_status(status indicators) {
    #ifdef INVERT_INDICATORS
        indicators = (status)~indicators;
    #endif
    #ifdef M5STICKC
        M5.Lcd.fillRect(0, 0, 80, 53,
            (indicators & INDICATOR_RED)
            ? TFT_RED : TFT_BLACK
        );
        M5.Lcd.fillRect(0, 53, 80, 53,
            (indicators & INDICATOR_ORANGE)
            ? TFT_ORANGE : TFT_BLACK
        );
        M5.Lcd.fillRect(0, 106, 80, 54,
            (indicators & INDICATOR_GREEN)
            ? TFT_GREEN : TFT_BLACK
        );
    #endif
    digitalWrite(
        RED_INDICATOR_PIN,
        (indicators & INDICATOR_RED)
        ? HIGH : LOW
    );
    digitalWrite(
        ORANGE_INDICATOR_PIN,
        (indicators & INDICATOR_ORANGE)
        ? HIGH : LOW
    );
    digitalWrite(
        GREEN_INDICATOR_PIN,
        (indicators & INDICATOR_GREEN)
        ? HIGH : LOW
    );
}

