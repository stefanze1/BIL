#include <Arduino.h>
#include "Battery.h"

void setup() {¨
    serial.begin(9600);

    lineSensors.initFiveSensors();
    proxSensors.initThreeSensors();

    
    buttonA.waitForButton();
    calibrateLineSensors();
}

void loop() {
    
    void Battery();

    if (buttonA.getSingleDebouncedPress()) {
        while (!buttonA.getSingleDebouncedPress()) {
        followLine();
    }
    
    motors.setSpeeds(0, 0);
    }

}