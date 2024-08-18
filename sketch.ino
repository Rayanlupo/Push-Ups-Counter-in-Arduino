#include <TM1637.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

TM1637 tmDisplay(13, 12);
int trigPin = 23;
int echoPin = 26;
int distance;
int buttonPin = 34;
int buzzerPin = 25;
int lastState = LOW;
int counter = 0;
int buttonState = LOW;
unsigned long lastPressTime = 0; 
int startTime;
int ledPin = 15;
int lastDistance;
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
  Serial.println("START");

  if(!oledDisplay.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Initialize OLED
    Serial.println(F("SSD1306 allocation failed"));
  }

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
    Serial.print("pressed");
    oledDisplay.clearDisplay();
    oledDisplay.setCursor(0, 0);
    oledDisplay.print("JUST DO IT");
    oledDisplay.display();
    counter = 0;
    startTime = millis();
    go = true;
  }
  

  if (go && millis() - startTime < 60000) {
    checkDistance();
    if (distance <= 15 && lastDistance >= 25) {
      counter += 1;
      Serial.print("Counter: ");
      Serial.println(counter);
      digitalWrite(ledPin, HIGH);
      tone(buzzerPin, 256);

    

    updateDisplay(counter);
    delay(500);
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    }
  } 
  lastState = buttonState;
  lastDistance = distance;
  if (buttonState != lastState) {
    lastState = buttonState;
  }
  delay(500);
}

void checkDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5); 
  digitalWrite(trigPin, LOW);
  int duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034 / 2);
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);
} 

void updateDisplay(int counter) {
  static int lastCounter = -1;
  if (counter != lastCounter) {
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
    lastCounter = counter;
  }
  delay(100);
  
}

void clearDisplay() {
  int8_t clearData[4] = { 0x7F, 0x7F, 0x7F, 0x7F }; 
  tmDisplay.display(clearData);
  delay(100);
}
