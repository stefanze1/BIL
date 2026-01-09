#include <Arduino.h>
#include "Battery.h"

void setup() {
    Serial.begin(9600);

}

void loop() {
    motors.setSpeeds(50,50);    
    battery();

}