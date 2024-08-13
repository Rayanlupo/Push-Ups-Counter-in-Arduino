#include <TM1637.h>
#include <Wire.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>
TM1637 display(13, 12);
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
bool go;
//Adafruit_SSD1306 display(128, 64, &Wire, -1);
void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lastState = digitalRead(buttonPin);
 
  Serial.print("START");
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH && lastState == LOW) {
    counter = 0;
    startTime = millis();
    lastState = buttonState; 
    go = true;
    Serial.print("pressed");
  }
  delay(10);
  if (go && millis() - startTime < 60000) {
    checkDistance();
    if (distance <= 15) {
       
      counter += 1;
      Serial.print("counter:");
      Serial.print(counter);
      delay(100);
    }
    display.display(3, counter);
    if (counter < 10) {
      display.display(3, counter);
    } else if (counter >= 10 && counter <= 99) {
      display.display(2, counter / 10);
      display.display(3, counter % 10);
    } else if (counter >= 100 && counter <= 999) {
      display.display(1, counter / 100);
      display.display(2, (counter / 10) % 10);
      display.display(3, counter % 10);
    }
    delay(10);
  } 
  else {
    delay(1000);
    Serial.println("nope");
  }
  
  delay(10);
  lastState = buttonState;
}

void checkDistance() {
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

