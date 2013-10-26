#include <Servo.h>
Servo myservo;
int pos = 0;

// LED leads connected to PWM pins
const int RED_LED_PIN = 9;
const int GREEN_LED_PIN = 10;
const int BLUE_LED_PIN = 11;

// Used to store the current intensity level of the individual LEDs
int redIntensity = 0;
int greenIntensity = 200;
int blueIntensity = 200;

int sensorPin = 0;
int sensorValue = 0;

void setup()
{
  myservo.attach(6);
  Serial.begin(9600);
}

void loop() 
{
  sensorValue = analogRead(sensorPin);
  redIntensity = map(sensorValue, 710, 850, 0, 254);
  pos = map(sensorValue, 710, 850, 0, 180);
  
  analogWrite(RED_LED_PIN, 0);
  analogWrite(BLUE_LED_PIN, 255 - redIntensity);
  analogWrite(GREEN_LED_PIN, redIntensity);
  myservo.write(pos);

Serial.println(sensorValue);
delay(10);
  
  
}
