#include "linesensors.h"
#include <Arduino.h>

#define maxSpeed 300

Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;
Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;

int junctionNum = 0;

//Status variabler for å holde styr på hvor i svinge prosessen den er
int rTrnState = 0;
int lTrnState = 0;

int16_t LSLastError = 0;
uint16_t lineSensorValues[NUM_SENSORS];

void calibrateLineSensors() {
    delay(1000);// delay for å rekke å fjerne hånden før den begynner kalibreringen 

    for (int16_t i = 0; i < 120; i++) {//for løkke fordi delay ikke vil la sensorene kalibreres
        if (i > 30 && i <= 90) {
            motors.setSpeeds(200, -200);
        } else {
            motors.setSpeeds(-200, 200);
        }
        lineSensors.calibrate();//kalibrerer sensorer mens den svinger over svart på hvit strek
        delay(20);
    }
    motors.setSpeeds(0, 0);
}

void followLine() {
    int16_t LSPosition = lineSensors.readLine(lineSensorValues);
    int16_t LSError = LSPosition - 2000; // 2000 er midtpunktet av linjesensorene, så feilen er avviket fra midtpunkt.

    int16_t speedDiff = LSError / 12 + 0.5 * (LSError - LSLastError);//Nøye utrøvde verdier for stabilitet, PD, regulering.
    LSLastError = LSError;                                        //justerer sving basert på avvik
//14+0.5 litt hakkete|//12+0,5(ok, for lav) | 10+1,5 greit på høy 8 +1||0.5gjør den treg
    int16_t LSLeftSpeed = (int16_t)maxSpeed/2 + speedDiff;// Kjører halvparten av max fart + fartsforskjell
    int16_t LSRightSpeed = (int16_t)maxSpeed/2 - speedDiff;

    LSLeftSpeed = constrain(LSLeftSpeed, 0, (int16_t)maxSpeed);// sørger for at den kjører på max LS speed på en side om gangen
    LSRightSpeed = constrain(LSRightSpeed, 0, (int16_t)maxSpeed);// og at den aldri kjører bakover
    
    motors.setSpeeds(LSLeftSpeed, LSRightSpeed);//kjør med de begrensede og sensorbestemte hastighetene
}

void rightTurn() { 
    static unsigned long rTimer = 0; //timer for å unngå delay()

    if (rTrnState == 0 && lineSensorValues[4] >= 925) {// Ser kryss og ikke svinger så:
        rTrnState = 1;
        rTimer = millis();
    }

    if (rTrnState == 1) {//reset motorene før sving
        motors.setSpeeds(0, 0);
        if (millis() - rTimer >= 50) {
            rTrnState = 2;
            rTimer = millis();
        }
    }
    else if (rTrnState == 2) {//selve svingen
        motors.setSpeeds(200, 0);
        if (millis() - rTimer >= 500) {
            rTrnState = 3;
            rTimer = millis();
        }
    }
    else if (rTrnState == 3) { //resett motorene etter svingen
        motors.setSpeeds(0, 0);
        if (millis() - rTimer >= 50) {
            rTrnState = 0; //reset variabel til å kunne svinge igjen på et senere tidspunkt
        }
    }
}

void leftTurn() {
    static unsigned long lTimer = 0;

    if (lTrnState == 0 && lineSensorValues[0] >= 925) {
        lTrnState = 1;
        lTimer = millis();
    }

    if (lTrnState == 1) {
        motors.setSpeeds(0, 0);
        if (millis() - lTimer >= 50) {
            lTrnState = 2;
            lTimer = millis();
        }
    }
    else if (lTrnState == 2) {
        motors.setSpeeds(0, 200);
        if (millis() - lTimer >= 500) {
            lTrnState = 3;
            lTimer = millis();
        }
    }
    else if (lTrnState == 3) { 
        motors.setSpeeds(0, 0);
        if (millis() - lTimer >= 50) {
            lTrnState = 0;
        }
    }
}

bool allWhite = true;

bool lostLine() {
    static uint8_t lostCounter = 0;

    bool anyDark = false;
    for (int i = 0; i < NUM_SENSORS; i++) {
        if (lineSensorValues[i] > 600) {
            anyDark = true;
            break;
        }
    }

    if (anyDark) {
        lostCounter = 0;
        return false;
    }

    lostCounter++;

    if (lostCounter >= 3) {
        motors.setSpeeds(0, 0);
        lostCounter = 0;
        return true;
    }

    return false;
}