#include <Arduino.h>
#include "Battery.h"
#include "display.h"
#include "bank.h"

#define balance

void setup() {
    Serial.begin(9600);
    screenStartup();
}

void loop() {
    // motors.setSpeeds(50,50);    
    // battery();
    // batteryDrain();
    updateBalance();
    Serial.println(balance);
}