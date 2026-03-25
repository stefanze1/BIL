#include <Arduino.h>
#include "linesensors.h"

bool isStopped = false;
bool onJunction = false;
bool junctionCounted = false;


void setup() {
    proxSensors.initThreeSensors();
//     lineSensors.initFiveSensors();
    
//     delay(1000);
//     calibrateLineSensors();
//     delay(1000);    
}   

void loop() {
    motors.setSpeeds(100,100);
    proxSensor();

//     lineSensors.read(lineSensorValues);
//     // fortsett sving hvis den er i en svingsekvens
//     if (rTrnState != 0) {
//         rightTurn();
//         return;
//     }
//     if (lTrnState != 0) {
//         leftTurn();
//         return;
//     }
    
//     followLine();

// //Telle kryss
//     if (lineSensorValues[0] >= 960 || lineSensorValues[4] >= 960) {//er man på kryss?
//         onJunction = true; //925 merker tjukk teip
//     }

//     if (onJunction && !junctionCounted) {//hvis kryss, tell kryss
//         junctionNum++;
//         junctionCounted = true;
//     }

//     if (lineSensorValues[0] < 300 && lineSensorValues[4] < 300) {//resett onJunction når vi er på svart hvitt igjen
//         onJunction = false;
//     }

//     if (!onJunction && junctionCounted) {// ikke på kryss, restart tellestatus for å kunne telle neste kryss
//         junctionCounted = false;
//     }

// // Kryss logikk
//     if (junctionNum == 3) {
//         rightTurn();
//     }
//     if (junctionNum == 4) {
//         motors.setSpeeds(0,0);
//         delay(5000);
//     }
}