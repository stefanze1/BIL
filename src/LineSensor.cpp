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

void followLine() {
    // LSLastError = 0;
    int16_t LSPosition = lineSensors.readLine(lineSensorValues); //Leser posisjon
    int16_t LSError = LSPosition - 2000; // trekker fra 200, da det er midtpunkt
    int16_t speedDiff = LSError / 12 + 1 * (LSError - LSLastError); //Dette er PID regulering, uten I. funnet på nett.
    LSLastError = LSError;

    int16_t LSLeftSpeed = (int16_t)maxSpeed/2 + speedDiff;
    int16_t LSRightSpeed = (int16_t)maxSpeed/2 - speedDiff;

    LSLeftSpeed = constrain(LSLeftSpeed, 0, (int16_t)maxSpeed);
    LSRightSpeed = constrain(LSRightSpeed, 0, (int16_t)maxSpeed);

    motors.setSpeeds(LSLeftSpeed, LSRightSpeed);

   }

void followLine2() {
    LSLastError = 0;
    int16_t LSPosition = lineSensors.readLine(lineSensorValues);
    int16_t LSError = LSPosition - 2000;
    int16_t speedDiff = LSError / 8 + 1 * (LSError - LSLastError);
    LSLastError = LSError;

    int16_t LSLeftSpeed = (int16_t)maxSpeed2/2 + speedDiff;
    int16_t LSRightSpeed = (int16_t)maxSpeed2/2 - speedDiff;

    LSLeftSpeed = constrain(LSLeftSpeed, 0, (int16_t)maxSpeed2);
    LSRightSpeed = constrain(LSRightSpeed, 0, (int16_t)maxSpeed2);

    motors.setSpeeds(LSLeftSpeed, LSRightSpeed);
}
void followLine3() {
    LSLastError = 0;
    int16_t LSPosition = lineSensors.readLine(lineSensorValues);
    int16_t LSError = LSPosition - 2000;
    int16_t speedDiff = LSError / 8 + 1 * (LSError - LSLastError);
    LSLastError = LSError;

    int16_t LSLeftSpeed = (int16_t)maxSpeed3/2 + speedDiff;
    int16_t LSRightSpeed = (int16_t)maxSpeed3/2 - speedDiff;

    LSLeftSpeed = constrain(LSLeftSpeed, 0, (int16_t)maxSpeed3);
    LSRightSpeed = constrain(LSRightSpeed, 0, (int16_t)maxSpeed3);

    motors.setSpeeds(LSLeftSpeed, LSRightSpeed);
}


void returnToCharger () {
    int16_t LSPosition = lineSensors.readLine(lineSensorValues);
     if (lineSensorValues[4] > 600 ) { //&& LSPosition > 3600
        motors.setSpeeds(0,0);
        delay(50);
        motors.setSpeeds(200,0);
        delay(500);
        motors.setSpeeds(0,0);
        if (lineSensorValues[0] < 150 && lineSensorValues[1] < 150 && lineSensorValues[2] < 150 && 
            lineSensorValues[3] < 150 && lineSensorValues[4] < 150) {
            motors.setSpeeds(0,0);
            delay(5000);
        }
    }
    else if (lineSensorValues[0] < 400 ) { //&& LSPosition < 600
        motors.setSpeeds(0,0);
        delay(50);
        motors.setSpeeds(0,200);
        delay(500);
        motors.setSpeeds(0,0);
        if (lineSensorValues[0] < 150 && lineSensorValues[1] < 150 && lineSensorValues[2] < 150 && 
            lineSensorValues[3] < 150 && lineSensorValues[4] < 150) {
            motors.setSpeeds(0,0);
            delay(5000);
        }
    }
}    

// void proxSensor() {
//     proxSensors.read();
//     proxSensors.read();

//     int8_t leftProx = proxSensors.countsFrontWithLeftLeds();
//     int8_t rightProx = proxSensors.countsFrontWithRightLeds();

//     if (leftProx > 5 || rightProx > 5) { // 0 til 7 
//         motors.setSpeeds(0,0);
//         delay(10000);
//     }     
// }