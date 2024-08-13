#include <TM1637.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



TM1637 tmDisplay(13, 12);
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
Adafruit_SSD1306 oledDisplay(128, 64, &Wire, -1);

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
  oledDisplay.clearDisplay();
  oledDisplay.setTextSize(1);
  oledDisplay.setTextColor(SSD1306_WHITE);
  oledDisplay.setCursor(0, 0);
  tmDisplay.set(7);
  tmDisplay.init();
  oledDisplay.display();
  oledDisplay.print("Push-up counter");

}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH && lastState == LOW) {
    oledDisplay.print("JUST DO IT");
    counter = 0;
    startTime = millis();
    lastState = buttonState; 
    go = true;
    Serial.print("pressed");
    delay(10);
  }
  delay(10);
  if (go && millis() - startTime < 60000) {
    
    checkDistance();
    delay(10);
  if (distance <= 15) {
      counter += 1;
      Serial.print("counter:");
      Serial.print(counter);
      digitalWrite(ledPin, HIGH);
      tone(buzzerPin, 256);
      delay(10);
    }
    if (counter < 10) {
      tmDisplay.display(3, counter);
    } else if (counter >= 10 && counter <= 99) {
      tmDisplay.display(2, counter / 10);
      tmDisplay.display(3, counter % 10);
    } else if (counter >= 100 && counter <= 999) {
      tmDisplay.display(1, counter / 100);
      tmDisplay.display(2, (counter / 10) % 10);
      tmDisplay.display(3, counter % 10);
    }
    delay(10);
    digitalWrite(ledPin, LOW);
      noTone(buzzerPin);
      delay(1000);
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
  tmDisplay.display(clearData);
}
