#include "linesensors.h"
#include <Arduino.h>

#define NUM_SENSORS 5
#define maxSpeed 300
#define maxSpeed2 200
#define maxSpeed3 100

int16_t LSLastError = 0;
unsigned int lineSensorValues[NUM_SENSORS];

Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;
Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;

void calibrateLineSensors() {
    delay(1000);
    for (int16_t i = 0; i < 120; i++) {
        if (i > 30 && i <= 90) {
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
    int16_t LSPosition = lineSensors.readLine(lineSensorValues); //Leser pos.
    int16_t LSError = LSPosition - 2000; // trekker fra 200, da det er midtpunkt
    int16_t speedDiff = LSError / 12 + 1 * (LSError - LSLastError); //Dette er PID regulering, uten I. funnet på nett. justert selv
    LSLastError = LSError;

    int16_t LSLeftSpeed = (int16_t)maxSpeed/2 + speedDiff;
    int16_t LSRightSpeed = (int16_t)maxSpeed/2 - speedDiff;

    LSLeftSpeed = constrain(LSLeftSpeed, 0, (int16_t)maxSpeed);
    LSRightSpeed = constrain(LSRightSpeed, 0, (int16_t)maxSpeed);

    motors.setSpeeds(LSLeftSpeed, LSRightSpeed);

   }

void followLine2() {
    int16_t LSPosition = lineSensors.readLine(lineSensorValues);
    int16_t LSError = LSPosition - 2000;
    int16_t speedDiff = LSError / 12 + 1 * (LSError - LSLastError);
    LSLastError = LSError;

    int16_t LSLeftSpeed = (int16_t)maxSpeed2/2 + speedDiff;
    int16_t LSRightSpeed = (int16_t)maxSpeed2/2 - speedDiff;

    LSLeftSpeed = constrain(LSLeftSpeed, 0, (int16_t)maxSpeed2);
    LSRightSpeed = constrain(LSRightSpeed, 0, (int16_t)maxSpeed2);

    motors.setSpeeds(LSLeftSpeed, LSRightSpeed);
}
void followLine3() {
    int16_t LSPosition = lineSensors.readLine(lineSensorValues);
    int16_t LSError = LSPosition - 2000;
    int16_t speedDiff = LSError / 12 + 1 * (LSError - LSLastError);
    LSLastError = LSError;

    int16_t LSLeftSpeed = (int16_t)maxSpeed3/2 + speedDiff;
    int16_t LSRightSpeed = (int16_t)maxSpeed3/2 - speedDiff;

    LSLeftSpeed = constrain(LSLeftSpeed, 0, (int16_t)maxSpeed3);
    LSRightSpeed = constrain(LSRightSpeed, 0, (int16_t)maxSpeed3);

    motors.setSpeeds(LSLeftSpeed, LSRightSpeed);
}


void rightTurn () {
    // int16_t LSPosition = lineSensors.readLine(lineSensorValues);
  
    if (lineSensorValues[4] > 925 ) { //&& LSPosition > 3400
        motors.setSpeeds(0,0);
        delay(50);
        motors.setSpeeds(200,0);
        delay(500);
        motors.setSpeeds(0,0);
    }
}
void leftTurn() {
    if (lineSensorValues[0] > 950  ) { //&& LSPosition < 400
        motors.setSpeeds(0,0);
        delay(50);
        motors.setSpeeds(0,200);
        delay(500);
        motors.setSpeeds(0,0);
    }
}
