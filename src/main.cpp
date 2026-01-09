#include <Zumo32U4Motors.h>
#include <test.h>
#include <Arduino.h>
#include "display.h"

void setup() {
  // Start skjermen og viser intro
  screenStartup();
}

void loop() {
  // Oppdaterer batteri og display hele tiden
  batteriDrain();

  }