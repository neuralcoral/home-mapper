#include <Arduino.h>

#include "Servo.h"

Servo myServo;

void setup() {
    Serial.begin(9600);
    myServo.attach(3);
    Serial.println("Setting up at 3");
}

void moveTo(int pos)
{
    Serial.println("Starting move to " + String(pos));
    myServo.write(pos);
    delay(1000);

}

void loop() {

    for (int i = 0; i < 180; i += 15)
    {
        moveTo(i);
    }
}