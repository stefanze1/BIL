#include <Arduino.h>
#include <Zumo32U4Motors.h>
#include <FollowLine.h>




void setup() {
lineSensors.initFiveSensors();
buttonA.waitForButton();
calibrateLineSensors();

}

void loop() {
buttonA.waitForButton();
followLine(); // ikke ferdig

}