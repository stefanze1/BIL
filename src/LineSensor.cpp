#include "linesensors.h"
#include <Arduino.h>

#define NUM_SENSORS 5
#define maxSpeed 400

int16_t LSLastError = 0;
unsigned int lineSensorValues[NUM_SENSORS];

// Opprett objektene som ble erklært som extern
Zumo32U4ButtonA buttonA;
Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;

void calibrateLineSensors() {
    delay(1000);
    for (int16_t i = 0; i < 80; i++) {
        if (i > 20 && i <= 60) {
            motors.setSpeeds(200, -200);
        } else {
            motors.setSpeeds(-200, 200);
        }
        lineSensors.calibrate();
        delay(20);
    }
    motors.setSpeeds(0, 0);
}

void followLine() {
    int16_t LSPosition = lineSensors.readLine(lineSensorValues);
    int16_t LSError = LSPosition - 2000;
    int16_t speedDiff = LSError / 4 + 6 * (LSError - LSLastError);
    LSLastError = LSError;

    int16_t LSLeftSpeed = (int16_t)maxSpeed + speedDiff;
    int16_t LSRightSpeed = (int16_t)maxSpeed - speedDiff;

    LSLeftSpeed = constrain(LSLeftSpeed, 0, (int16_t)maxSpeed);
    LSRightSpeed = constrain(LSRightSpeed, 0, (int16_t)maxSpeed);

    motors.setSpeeds(LSLeftSpeed, LSRightSpeed);
}