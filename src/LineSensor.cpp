#include "linesensors.h"
#include <Arduino.h>

#define NUM_SENSORS 5
#define maxSpeed 400
#define maxSpeed2 300
#define maxSpeed3 220

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
            motors.setSpeeds(300, -300);
        } else {
            motors.setSpeeds(-300, 300
            );
        }
        lineSensors.calibrate();
        delay(20);
    }
    motors.setSpeeds(0, 0);
}

void followLine() {
    LSLastError = 0;
    int16_t LSPosition = lineSensors.readLine(lineSensorValues); //Leser posisjon
    int16_t LSError = LSPosition - 2000; // trekker fra 200, da det er midtpunkt
    int16_t speedDiff = LSError / 6 + 6 * (LSError - LSLastError); //Dette er PID regulering, uten I. funnet på nett.
    LSLastError = LSError;

    int16_t LSLeftSpeed = (int16_t)maxSpeed + speedDiff;
    int16_t LSRightSpeed = (int16_t)maxSpeed - speedDiff;

    LSLeftSpeed = constrain(LSLeftSpeed, 0, (int16_t)maxSpeed);
    LSRightSpeed = constrain(LSRightSpeed, 0, (int16_t)maxSpeed);

    motors.setSpeeds(LSLeftSpeed, LSRightSpeed);

    //test
    proxSensors.read();

    int8_t leftProx = proxSensors.countsFrontWithLeftLeds();
    int8_t rightProx = proxSensors.countsFrontWithRightLeds();

    // if (leftProx > 3 || rightProx > 3) { // 0 til 7
    //     motors.setSpeeds(0,0);
    //     delay(20000);
    // }

   }

void followLine2() {
    LSLastError = 0;
    int16_t LSPosition = lineSensors.readLine(lineSensorValues);
    int16_t LSError = LSPosition - 2000;
    int16_t speedDiff = LSError / 4 + 6 * (LSError - LSLastError);
    LSLastError = LSError;

    int16_t LSLeftSpeed = (int16_t)maxSpeed2 + speedDiff;
    int16_t LSRightSpeed = (int16_t)maxSpeed2 - speedDiff;

    LSLeftSpeed = constrain(LSLeftSpeed, 0, (int16_t)maxSpeed2);
    LSRightSpeed = constrain(LSRightSpeed, 0, (int16_t)maxSpeed2);

    motors.setSpeeds(LSLeftSpeed, LSRightSpeed);
}
void followLine3() {
    LSLastError = 0;
    int16_t LSPosition = lineSensors.readLine(lineSensorValues);
    int16_t LSError = LSPosition - 2000;
    int16_t speedDiff = LSError / 4 + 6 * (LSError - LSLastError);
    LSLastError = LSError;

    int16_t LSLeftSpeed = (int16_t)maxSpeed3 + speedDiff;
    int16_t LSRightSpeed = (int16_t)maxSpeed3 - speedDiff;

    LSLeftSpeed = constrain(LSLeftSpeed, 0, (int16_t)maxSpeed3);
    LSRightSpeed = constrain(LSRightSpeed, 0, (int16_t)maxSpeed3);

    motors.setSpeeds(LSLeftSpeed, LSRightSpeed);
}


void returnToCharger () {
    int16_t LSPosition = lineSensors.readLine(lineSensorValues);
     if (lineSensorValues[4] > 950 && LSPosition > 3900) {
        motors.setSpeeds(0,0);
        delay(500);
        motors.setSpeeds(200,0);
        delay(500);
        motors.setSpeeds(0,0);
    }
    else if (lineSensorValues[0] < 50 && LSPosition < 100) {
        motors.setSpeeds(0,0);
        delay(500);
        motors.setSpeeds(0,200);
        delay(500);
        motors.setSpeeds(0,0);
    
    }
}    

// void proxSensor() {
//     proxSensors.read();

//     int8_t leftProx = proxSensors.countsFrontWithLeftLeds();
//     int8_t rightProx = proxSensors.countsFrontWithRightLeds();

//     if (leftProx > 5 && rightProx > 5) { // 0 til 7
//         motors.setSpeeds(0,0);
//         delay(20000);
//     }
// }