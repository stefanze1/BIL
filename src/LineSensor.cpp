#include "linesensors.h"
#include <Arduino.h>

#define NUM_SENSORS 5
#define maxSpeed 300
#define maxSpeed2 200
#define maxSpeed3 100

int16_t LSLastError = 0;
unsigned int lineSensorValues[NUM_SENSORS];

bool allWhite = true;


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
    int16_t LSError = LSPosition - 2000; // trekker fra 2000, da det er midtpunkt
    int16_t speedDiff = LSError / 12 + 0.5 * (LSError - LSLastError); //Dette er PID regulering, uten I. funnet på nett. justert selv
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
    int16_t speedDiff = LSError / 12 + 0.5 * (LSError - LSLastError);
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
    int16_t speedDiff = LSError / 12 + 0.5 * (LSError - LSLastError);
    LSLastError = LSError;

    int16_t LSLeftSpeed = (int16_t)maxSpeed3/2 + speedDiff;
    int16_t LSRightSpeed = (int16_t)maxSpeed3/2 - speedDiff;

    LSLeftSpeed = constrain(LSLeftSpeed, 0, (int16_t)maxSpeed3);
    LSRightSpeed = constrain(LSRightSpeed, 0, (int16_t)maxSpeed3);

    motors.setSpeeds(LSLeftSpeed, LSRightSpeed);
}

bool timer50ms() {
  static unsigned long currentTime = 0;
  
  if ((millis() - currentTime) >= 50){
  	currentTime = millis();
    return true;
  }
    return false;
}

bool timer500ms() {
  static unsigned long currentTime = 0;
  
  if ((millis() - currentTime) >= 500){
  	currentTime = millis();
    return true;
  }
  return false;
}

void rightTurn() {
     if (lineSensorValues[4] >= 925 ) { //&& LSPosition < 400
        motors.setSpeeds(0,0);
        delay(50);
        motors.setSpeeds(200,0);
        delay(500);
        motors.setSpeeds(0,0);
    }
}

void leftTurn() {
    if (lineSensorValues[0] >= 925 ) { //&& LSPosition < 400
        motors.setSpeeds(0,0);
        delay(50);
        motors.setSpeeds(0,200);
        delay(500);
        motors.setSpeeds(0,0);
    }
}

bool lostLine() { // brukes med if
    static uint8_t lostCounter = 0; // teller hvor lenge linjen er tapt

    bool anyDark = false;
    for (int i = 0; i < NUM_SENSORS; i++) {
        if (lineSensorValues[i] > 600) { // juster terskel etter behov
            anyDark = true;
            break;
        }
    }

    if (anyDark) {
        lostCounter = 0; // linjen er fortsatt der
        return false;
    }

    // hvis ingen sensorer ser svart
    lostCounter++;

    if (lostCounter >= 3) { // linjen har vært borte i flere målinger
        motors.setSpeeds(0, 0); // stopp motorene
        lostCounter = 0;
        return true;
    }

    return false;
}


