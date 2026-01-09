#include "Battery.h"
#include <Arduino.h>


int rightTick;
int leftTick;

float batteryLevel = 100.000;
float newBatteryLevel = 0;


Zumo32U4Motors motors;
Zumo32U4Encoders encoders;


void battery() {

    rightTick = encoders.getCountsAndResetRight();
    leftTick = encoders.getCountsAndResetLeft();

    while (batteryLevel > 0) {
        if (rightTick == 1 || leftTick == 1) {        
        newBatteryLevel = (batteryLevel - 1.0);
        batteryLevel = newBatteryLevel;
        Serial.print(batteryLevel);
        }
        else {
            break;
        }

    }

}