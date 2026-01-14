#include <Arduino.h>
#include "Battery.h"
#include "display.h"

void setup() {
    Serial.begin(9600);
    screenStartup();
}

void loop() {
    motors.setSpeeds(50,50);    
    battery();
    batteryDrain();
}