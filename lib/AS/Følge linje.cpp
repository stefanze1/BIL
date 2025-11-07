#include <Zumo32U4.h>
Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motors;
unsigned int lineSensorValues[5];
Zumo32U4ButtonA buttonA;
#define maxSpeed 400;
int LS.LastError = 0;


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
    int LS.Position = lineSensors.readLine(lineSensorValues);
    //Vet at verdien 2000 gir midten av streken
    int LS.Error = LS.Position - 2000;
    //For å holde den på linjen må motorene brukes, Sensorene er monotome så PID er fint..
    int speedDiff = LS.Error / 10 + 10 * (LS.Error - LS.LastError);
    LS.LastError = LS.Error;

}
