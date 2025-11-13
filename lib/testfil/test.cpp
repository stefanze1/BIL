#include <Zumo32U4.h>
Zumo32U4Motors motors; 
Zumo32U4LineSensors lineSensors; 

unsigned int lineSensorValue[5];

bool hasStopped = false;


void setup() {
  lineSensors.initFiveSensors();
  lineSensors.calibrate();
  
  for(int i = 0; i < 100; i++){
    if(i > 30 && i <= 80 ){
      motors.setSpeeds(-200,200);
      
    } else {
      motors.setSpeeds(200,-200);

    }
    lineSensors.calibrate();
    delay(10);
  }
  motors.setSpeeds(50,50);

}

void loop() {
  
  lineSensors.read(lineSensorValue);
  unsigned int midSensor = lineSensorValue[2]; 

  if (midSensor < 200){
    motors.setSpeeds(50,50);
    hasStopped = false;
    

  } else if (midSensor > 850 && !hasStopped) {
    motors.setSpeeds(0,0);
    delay(2000); 
    motors.setSpeeds(50,50);
    hasStopped = true; 
  }
  delay(50);


}

