#include <TM1637.h>
#include <Wire.h>
TM1637 display(12, 13);
int trigPin = 23;
int echoPin = 22;
int distance;
int buttonPin = 21;
int buzzerPin = 25;
int lastState = LOW;
int counter = 0;
int buttonState = LOW;
unsigned long lastPressTime = 0; 
int startTime;
int ledPin = 15;
int go;
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
  Serial.print("pressed");
}
if (go && millis() - startTime < 60000){
checkDistance();
if (distance <= 15){
counter += 1;
}
if (counter < 10){
  display.display(3, counter);
}
else if (10 <= counter <= 99){
  display.display(2, counter / 10);
  display.display(3, counter % 10);
}
if (100 <= counter <= 999){
  display.display(1, counter / 100);
  display.display(2, (counter / 100) % 10);
  display.display(3, counter / 10);
}

delay(10);

}
else{
  go = false;
  clearDisplay();
}

delay(10);
}


void checkDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  int duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034 / 2);
  Serial.println(distance);
}
void clearDisplay() {
  int8_t clearData[4] = { 0x7F, 0x7F, 0x7F, 0x7F }; 
  display.display(clearData);
}
