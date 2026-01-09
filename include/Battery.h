#ifndef LINESENSORS_H
#define LINESENSORS_H

#include <Zumo32U4.h>

extern Zumo32U4ButtonA buttonA;
extern Zumo32U4Motors motors;
extern Zumo32U4LineSensors lineSensors;

extern Zumo32U4Encoders Encoders;

void calibrateLineSensors();
void followLine();
void turnLeft();
void turnRight();
void returnToCharger();


#endif