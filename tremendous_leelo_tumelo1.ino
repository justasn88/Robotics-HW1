int sensorPin = A0;   
int motorPin = 9;     

float voltage, temperatureC;

void setup() {
  pinMode(motorPin, OUTPUT);
  Serial.begin(1000);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  
  voltage = sensorValue * (5.0 / 1023.0);
  temperatureC = (voltage - 0.5) * 100.0; 
  
  int fanSpeed = map(temperatureC, 24, 50, 0, 255);
  fanSpeed = constrain(fanSpeed, 0, 255);
  analogWrite(motorPin, fanSpeed);
}
