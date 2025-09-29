#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2);

int TmpSensorPin = A0;    
int motorPin = 9;       
int HumSensorPin = A1;

float voltage, temperatureC;
int fanSpeed;

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  int TmpSensorValue = analogRead(TmpSensorPin);
  int HumSensorValue = analogRead(HumSensorPin);
  
  voltage = TmpSensorValue * (5.0 / 1023.0);
  temperatureC = (voltage - 0.5) * 100.0;  
  
  int humidityPercentage = map(HumSensorValue, 0, 1023, 10, 70);
  
  int baseFanSpeed = map(temperatureC, 24, 50, 0, 255);
  
  if (humidityPercentage > 50) {
    int humidityBoost = map(humidityPercentage, 50, 79, 0, 100);
    fanSpeed = baseFanSpeed + humidityBoost;
  }
  else {
    fanSpeed = baseFanSpeed;
  }
  
  lcd.clear();
  
  fanSpeed = constrain(fanSpeed, 0, 255);
  analogWrite(motorPin, fanSpeed);
  
  lcd.setCursor(0, 0); 
  lcd.print("Temp: ");
  lcd.print(temperatureC);
  lcd.print(" C");

  lcd.setCursor(0, 1); 
  lcd.print("Dregme: ");
  lcd.print(humidityPercentage);
  lcd.print(" %");
  
  delay(1000);
}
