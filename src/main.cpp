#include <Arduino.h>
#include "linesensors.h"

void setup() {
    lineSensors.initFiveSensors();
    proxSensors.initThreeSensors();
    
    buttonA.waitForButton();
    calibrateLineSensors();
}

void loop() {
    
    if (buttonA.getSingleDebouncedPress()) {
        while (!buttonA.getSingleDebouncedPress()) {
        followLine();
        returnToCharger();
    }
    
    motors.setSpeeds(0, 0);
}

    if (buttonB.getSingleDebouncedPress()) {
        while (!buttonB.getSingleDebouncedPress()) {
            followLine2();
        }
    motors.setSpeeds(0,0);
    }

    if (buttonC.getSingleDebouncedPress()) {
        while (!buttonC.getSingleDebouncedPress()) {
            followLine3();
        }
    motors.setSpeeds(0,0);
    }
}