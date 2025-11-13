#include <Arduino.h>
#include "linesensors.h"

void setup() {
    lineSensors.initFiveSensors();
    buttonA.waitForButton();
    calibrateLineSensors();
}

void loop() {
    buttonA.waitForButton();
    while (!buttonA.isPressed()) {
        followLine();
    }
    motors.setSpeeds(0, 0);
}