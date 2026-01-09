#include "Battery.h"
#include <Arduino.h>

#define NUM_SENSORS 5

#define maxSpeed2 200

int16_t LSLastError = 0;
unsigned int lineSensorValues[NUM_SENSORS];

Zumo32U4ButtonA buttonA;
Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;
Zumo32U4Encoders encoders;


void Battery(); {
    motors.setSpeeds(50);
    a = encoders.getCountsRight();
    b = encoders.getCountsLeft();
    Serial.println(a);
    Serial.println(b);

}




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



void turnRight () {
    // int16_t LSPosition = lineSensors.readLine(lineSensorValues);
  
    if (lineSensorValues[4] > 925 ) { //&& LSPosition > 3400
        motors.setSpeeds(0,0);
        delay(50);
        motors.setSpeeds(200,0);
        delay(500);
        motors.setSpeeds(0,0);
    }
}
  
void turnLeft() {
      if (lineSensorValues[0] > 925  ) { //&& LSPosition < 400
        motors.setSpeeds(0,0);
        delay(50);
        motors.setSpeeds(0,200);
        delay(500);
        motors.setSpeeds(0,0);
    }
}

