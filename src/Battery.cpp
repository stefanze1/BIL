#include "battery.h"
#include <Arduino.h>


int rightTick;
int leftTick;

int rightTickCount = 0;
int leftTickCount = 0;

float batteryLevel = 100;
float newBatteryLevel = 0.00;

float batteryDrain = 0.05;


Zumo32U4Motors motors;
Zumo32U4Encoders encoders;


void battery() {

    rightTick = encoders.getCountsAndResetRight();
    leftTick = encoders.getCountsAndResetLeft();


    if (batteryLevel > 0) {
        rightTick = encoders.getCountsAndResetRight();
        leftTick = encoders.getCountsAndResetLeft();

        if (rightTick == 1) {
            rightTickCount += 1;
           
        }

        if (rightTickCount > 12) {
            batteryLevel -= batteryDrain;
            rightTickCount = 0;

            Serial.print(batteryLevel);
            Serial.print("  ");
        }

        if (leftTick == 1) {
            leftTickCount += 1;
        }

         if (rightTickCount > 12) {
            batteryLevel -= batteryDrain;
            leftTickCount = 0;

            Serial.print(batteryLevel);
            Serial.print("  ");
        }
        
    
    }

}

