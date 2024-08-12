#include <TM1637>
#include <Wire.h>

int trigPin = 23;
int echoPin = 22;
int distance;

int buttonPin = 35;
int buzzerPin = 25;
int lastState = LOW;
int counter = 0;
int buttonState = LOW;
unsigned long lastPressTime = 0; 
int ledPin = 15;
void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  lastState = digitalRead(buttonPin);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH && lastState == LOW){
  counter = 0;
  display.init();
  display.set(7);
  startTime = millis();
  lastState = buttonState; 
  go = true;
}
if go && millis - startTime < 60000{
  
}
}

void checkDistance(){
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  int duration = pulseIn(EchoPin, HIGH);
  distance = (duration * 0.034 / 2);
}
