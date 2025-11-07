#include <Zumo32U4.h>
Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motors;
unsigned int lineSensorValues[5];
Zumo32U4ButtonA buttonA;
#define maxSpeed 200;
int LSLastError = 0;


void calibrateLineSensors() {
    delay(1000);
    for (int i = 0; i < 160; i++) {
        if (i < 40 && i >= 120) {
            motors.setSpeeds(200,-200);
        }
        else {
            delay(500);
            motors.setSpeeds(-200,200);
        }
        lineSensors.calibrate();
    }
    motors.setSpeeds(0,0);
}

void followLine() {
    //Leser av posisjon
    int LSPosition = lineSensors.readLine(lineSensorValues);
    //Vet at verdien 2000 gir midten av streken
    int LSError = LSPosition - 2000;
    //For å holde den på linjen må motorene brukes, Sensorene er monotome så PID er fint.. Linjene nedenfor er fra et eksempel
    int speedDiff = LSError / 10 + 10 * (LSError - LSLastError);
    LSLastError = LS.Error;

    int LSLeftSpeed = maxSpeed + speedDiff;
    int LSRigtSpeed = maxSpeed - speedDiff;

    LSLeftSpeed = constrain(LSLeftSpeed, 0, maxSpeed);
    LSRightSpeed = constrain(LSRightSpeed, 0, maxSpeed);

}
