#ifndef LINESENSORS_H
#define LINESENSORS_H

#include <Zumo32U4.h>

#define NUM_SENSORS 5

extern Zumo32U4ButtonA buttonA;
extern Zumo32U4ButtonB buttonB;
extern Zumo32U4ButtonC buttonC;
extern Zumo32U4Motors motors;
extern Zumo32U4LineSensors lineSensors;
extern int junctionNum;
extern int rTrnState;
extern int lTrnState;
extern uint16_t lineSensorValues[NUM_SENSORS];

void calibrateLineSensors();
void followLine(); //(int16_t LSPosition)
void rightTurn();
void leftTurn();
bool lostLine();

#endif