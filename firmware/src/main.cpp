#include <Arduino.h>
#include <Servo.h>

#define START_PIN 2
#define END_PIN 13
#define SERVO_COUNT (END_PIN - START_PIN + 1)

Servo legServos[SERVO_COUNT];

void setup() {
    Serial.begin(115200);
    while(!Serial);

    Serial.println("--- Hexapod Interactive Calibration ---");
    Serial.println("Commands:");
    Serial.println("  [0-180] : Set current servo to that angle");
    Serial.println("  'y'     : Lock in and move to NEXT servo");

    for (int i = 0; i < SERVO_COUNT; i++) {
        int pin = START_PIN + i;
        int currentAngle = 90; // Default starting point

        legServos[i].attach(pin);
        legServos[i].write(currentAngle);

        Serial.print("\n>>>> CONTROLLING PIN: ");
        Serial.println(pin);

        bool movingToNext = false;
        while (!movingToNext) {
            if (Serial.available() > 0) {
                // Check if the first character is 'y'
                char firstChar = Serial.peek();

                if (firstChar == 'y' || firstChar == 'Y') {
                    Serial.read(); // Clear the 'y' from buffer
                    Serial.print("Pin ");
                    Serial.print(pin);
                    Serial.println(" locked. Moving on...");
                    movingToNext = true;
                }
                else if (isdigit(firstChar)) {
                    int inputAngle = Serial.parseInt();

                    if (inputAngle >= 0 && inputAngle <= 180) {
                        currentAngle = inputAngle;
                        legServos[i].write(currentAngle);
                        Serial.print("  -> Pin ");
                        Serial.print(pin);
                        Serial.print(" set to: ");
                        Serial.println(currentAngle);
                    } else {
                        Serial.println("  !! Angle must be 0-180");
                    }
                }
                else {
                    // Clear junk characters (like spaces or newlines)
                    Serial.read();
                }
            }
        }
    }
    Serial.println("\nAll servos calibrated. Setup complete.");
}

void loop() {
    // Keep alive
}