#ifndef LINESENSORS_H
#define LINESENSORS_H

#include <Zumo32U4.h>

extern Zumo32U4ButtonA buttonA;
extern Zumo32U4ButtonB buttonB;
extern Zumo32U4ButtonC buttonC;
extern Zumo32U4Motors motors;
extern Zumo32U4LineSensors lineSensors;
extern Zumo32U4ProximitySensors proxSensors;

void calibrateLineSensors();
void followLine();
void followLine2();
void followLine3();
void returnToCharger();


#endif