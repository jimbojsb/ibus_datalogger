#include "SPI.h"
#include "SD.h"

#define PIN_CS 10
#define LED_PIN 7
#define LED_BLINK_DURATION 50

File ibusLog;
int incomingByte;
int ledMillis;

void setup() {
    Serial.begin(9600, SERIAL_8E1);
    SD.begin(PIN_CS);
    if (SD.exists("ibuslog.txt")) {
      SD.remove("ibuslog.txt");  
    }
    ibusLog = SD.open("ibuslog.txt", FILE_WRITE);
    pinMode(LED_PIN, OUTPUT);
    ledMillis = 0;
    digitalWrite(LED_PIN, HIGH);
}

void loop() {
  if (millis() - ledMillis > LED_BLINK_DURATION) {
    digitalWrite(LED_PIN, LOW);  
  }
  if (Serial.available()) {
    incomingByte = Serial.read();
    ibusLog.print(incomingByte, HEX);
    ibusLog.print(" ");  
    ibusLog.flush();
    digitalWrite(LED_PIN, HIGH);
  }  
}
