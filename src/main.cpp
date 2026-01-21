#include <Arduino.h>
#include "linesensors.h"

bool isStopped = false;

void setup() {
    lineSensors.initFiveSensors();
    
    // buttonA.waitForButton();
    // calibrateLineSensors();
}

void loop() {
    
//     if (buttonA.getSingleDebouncedPress()) {
//         while (!buttonA.getSingleDebouncedPress()) {
//         followLine();
//         rightTurn();
//         leftTurn();
//         // isLineLost();
//     }
// }
    motors.setSpeeds(200,200);
    if(Delay(500)) {
    motors.setSpeeds(0,0);
    }
    Delay(500);
}