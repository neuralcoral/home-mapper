#include <Arduino.h>

#include "Servo.h"

Servo myServo;

void setup() {
    Serial.begin(115200);
    myServo.attach(3);
    Serial.println("--- ESP8266 Connectivity Test ---");
    Serial.println("Type 'AT' in the monitor and hit enter.");
}

void moveTo(int pos)
{
    Serial.println("Starting move to " + String(pos));
    myServo.write(pos);
    delay(1000);

}

void loop() {

    if (Serial.available())
    {
        char c = Serial.read();
        Serial.write(c);
    }
}