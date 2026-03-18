#include <Arduino.h>
#include "linesensors.h"

bool isStopped = false;



void setup() {
    lineSensors.initFiveSensors();
    
    delay(1000);
    calibrateLineSensors();
    delay(1000);    
}   

void loop() {
    
        followLine();
        // rightTurn();
        // leftTurn();
        // motors.setSpeeds(0, 0);
        // followLine();
        // isLineLost();

}