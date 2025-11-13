#include <Arduino.h>
#include "linesensors.h"

void setup() {
    lineSensors.initFiveSensors();
    buttonA.waitForButton();
    calibrateLineSensors();
}

void loop() {
    
    if (buttonA.isPressed()) {
        while (!buttonA.isPressed()) {
        followLine();
    }
    
    motors.setSpeeds(0, 0);
}

    if (buttonB.isPressed()) {
        while (!buttonB.isPressed()) {
            followLine2();
        }
    motors.setSpeeds(0,0);
    }

    if (buttonC.isPressed()) {
        while (!buttonC.isPressed()) {
            followLine3();
        }
    motors.setSpeeds(0,0);
    }
}