#include "linesensors.h"
#include <Arduino.h>
#define NUM_SENSORS 5
#define maxSpeed 300
#define maxSpeed2 200
#define maxSpeed3 120

int16_t LSLastError = 0;
unsigned int lineSensorValues[NUM_SENSORS];

Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;
Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;
Zumo32U4ProximitySensors proxSensors;

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
bool isLineLost() {
    static uint8_t lostCounter = 0;

    bool anyDark = false;
    for (int i = 0; i < NUM_SENSORS; i++) {
        if (lineSensorValues[i] > 600) {
            anyDark = true;
        }
    }

    if (anyDark) {
        lostCounter = 0;
        return false;
    }

    lostCounter++;

    if (lostCounter >= 3) {
        lostCounter = 0;
        return true;
    }

    return false;
}

void followLine() {
   
    int16_t LSPosition = lineSensors.readLine(lineSensorValues);

    
    bool allWhite = true;
    for (int i = 0; i < NUM_SENSORS; i++) {
        if (lineSensorValues[i] > 200) {
            allWhite = false;
            break;
        }
    }
    
    if (allWhite && abs(LSLastError) < 700) {  
       
        motors.setSpeeds(0, 0);
        return;
    }

   
    int16_t LSError = LSPosition - 2000;

    float Kp = 0.08;
    float Kd = 0.30;

    float speedDiffF = Kp * LSError + Kd * (LSError - LSLastError);
    LSLastError = LSError;
    int16_t speedDiff = (int16_t)speedDiffF;

    
    int16_t base = maxSpeed / 2;

    int16_t left = base + speedDiff;
    int16_t right = base - speedDiff;

    left = constrain(left, 0, maxSpeed);
    right = constrain(right, 0, maxSpeed);

    motors.setSpeeds(left, right);
}
void followLine2() {
    int16_t LSPosition = lineSensors.readLine(lineSensorValues);

    bool allWhite = true;
    for (int i = 0; i < NUM_SENSORS; i++) {
        if (lineSensorValues[i] > 200) { allWhite = false; break; }
    }

    if (allWhite && abs(LSLastError) < 700) {
        motors.setSpeeds(0, 0);
        return;
    }

    int16_t LSError = LSPosition - 2000;

    float Kp = 0.07;
    float Kd = 0.28;

    float speedDiffF = Kp * LSError + Kd * (LSError - LSLastError);
    LSLastError = LSError;
    int16_t speedDiff = (int16_t)speedDiffF;

    int16_t base = maxSpeed2 / 2;

    int16_t left = base + speedDiff;
    int16_t right = base - speedDiff;

    left = constrain(left, 0, maxSpeed2);
    right = constrain(right, 0, maxSpeed2);

    motors.setSpeeds(left, right);
}

void followLine3() {
    int16_t LSPosition = lineSensors.readLine(lineSensorValues);

    bool allWhite = true;
    for (int i = 0; i < NUM_SENSORS; i++) {
        if (lineSensorValues[i] > 200) { allWhite = false; break; }
    }

    if (allWhite && abs(LSLastError) < 700) {
        motors.setSpeeds(0, 0);
        return;
    }

    int16_t LSError = LSPosition - 2000;

    float Kp = 0.06;
    float Kd = 0.25;

    float speedDiffF = Kp * LSError + Kd * (LSError - LSLastError);
    LSLastError = LSError;
    int16_t speedDiff = (int16_t)speedDiffF;

    int16_t base = maxSpeed3 / 2;

    int16_t left = base + speedDiff;
    int16_t right = base - speedDiff;

    left = constrain(left, 0, maxSpeed3);
    right = constrain(right, 0, maxSpeed3);

    motors.setSpeeds(left, right);
}

void returnToCharger () {
    
  
    if (lineSensorValues[4] > 925 ) { 
        motors.setSpeeds(0,0);
        delay(50);
        motors.setSpeeds(200,0);
        delay(500);
        motors.setSpeeds(0,0);
    }
    if (lineSensorValues[0] > 950  ) { 
        motors.setSpeeds(0,0);
        delay(50);
        motors.setSpeeds(0,200);
        delay(500);
        motors.setSpeeds(0,0);
    }
}
