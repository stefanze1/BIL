#ifndef LINESENSORS_H
#define LINESENSORS_H
#include <Zumo32U4.h>

extern Zumo32U4ButtonA buttonA;
extern Zumo32U4Motors motors;
extern Zumo32U4LineSensors lineSensors;

void calibrateLineSensors();
void followLine();


#endif


// må fikses