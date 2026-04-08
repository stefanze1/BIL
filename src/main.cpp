#include "Battery.h"
#include "display.h"
#include "bank.h"

#define balance
#include <Arduino.h>
#include "speed.h"
#include <Zumo32U4.h>

Zumo32U4Encoders encoders;

void setup() {
    Serial.begin(115200);
}

void loop() {
    float speed = Speed();
   
    motors.setSpeeds(100, 100);
    battery() ;
    Serial.println(batteryLevel);
}