#include <Arduino.h>
#include <Zumo32U4.h>
#include "speed.h"
#include "Battery.h"


float Speed() {

    static unsigned long previousTime = 0;
    static int previousCount = 0;

    const float wheelDiameter = 3.2;
    const float wheelCircumferance = 3.1416 * wheelDiameter;
    const int countsPerRevolution = 909;

    unsigned long currentTime = millis();

    if (currentTime - previousTime >= 500) {

        int rightTick = encoders.getCountsAndResetRight();
        int leftTick  = encoders.getCountsAndResetLeft();
        Serial.print("Right");
        Serial.println("rightTick");
        Serial.print("Left");
        Serial.println("leftTick");

        float currentCount = (rightTick + leftTick) / 2.0;
        int deltaCount = currentCount ;
        unsigned long deltaTime = currentTime - previousCount;

        float rounds = (float)deltaCount / countsPerRevolution;

        if(rounds<0) rounds=0;
        float distance = rounds * wheelCircumferance;

        Serial.print("currentCount");
        Serial.println(currentCount);
        Serial.print("deltaCount");
        Serial.println(deltaCount);
        Serial.print("deltaTime");
        Serial.println(deltaTime);
        Serial.print("rounds");
        Serial.println(rounds);
        Serial.print("distance");
        Serial.println(distance);


        float speed = 0;

        if (deltaTime > 0) {
            speed = distance / (deltaTime / 1000.0);
        }

        previousCount = currentCount;
        previousTime = currentTime;

        return speed;
    }

    return -1;
}