//for ztp-115m
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("hello");
}
void loop() {
  // put your main code here, to run repeatedly:
  // read the input on analog ADC1_0:
  int sensorValue = analogRead(36);
  Serial.println("Sensor Value");
  Serial.println(sensorValue);
  float voltage;
  voltage = 3.3 * (sensorValue/4095.0);
  Serial.println("Voltage");
  Serial.println(voltage);
  float temperature;
  temperature = 8.294633642930862*10^(-5)*voltage^(2) + .0088*voltage + 1.2603;
  Serial.println("Temperature (degrees Celsisu): ");
  Serial.println(temperature);
  // print out the value you read:
  delay(1000);        // delay in between reads for stability
}
