#include <Arduino.h>
#include "display.h"

// Battery.cpp
void battery();

void setup() {
  screenStartup();
}

void loop() {
  battery();        // oppdaterer batteryLevel
  batteriDrain();   // viser batteryLevel på display
}
