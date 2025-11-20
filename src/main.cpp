#include <Arduino.h>
#include "display.h"   // vår egen header

void setup() {
  // Start skjermen og vis intro
  screenStartup();
}

void loop() {
  // Oppdater batteri og display hele tiden
  batteriDrain();

  // Her kan du senere legge inn knapper, motorer osv.
  delay(50); // liten pause for å ikke spamme CPU
}
