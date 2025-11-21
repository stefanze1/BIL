#include <Arduino.h> 
#include "display.h"
#include <U8g2lib.h>

#include "linesensors.h"

// Batteriet starter på 90%
int batteri = 90;

// OLED-display: SH1106 128x64, SPI
U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI display(
  U8G2_R0,
  1,                 // clock (SCK)
  30,                // data (MOSI / PD5)
  U8X8_PIN_NONE,     // cs (ikke brukt)
  17,                // dc (PB0)
  0                  // reset (PD2)
);


unsigned long lastDrainTime = 0;
const unsigned long DRAIN_INTERVAL = 3000;   // hvert 3. sekund

bool blinkOn = true;
unsigned long lastBlinkTime = 0;
const unsigned long BLINK_INTERVAL = 400;   // blink hver 0,4 s

void screenStartup() {
  display.begin();
  display.setFont(u8g2_font_10x20_tf);
  display.drawStr(10, 20, "ZumoBil");
  display.sendBuffer();
  delay(2000);

  display.clearBuffer();
  display.setFont(u8g2_font_8x13_tf);
  display.drawFrame(88, 2, 38, 21);
  display.drawStr(95, 16, "90%");
  display.sendBuffer();
  display.clearBuffer();
  delay(2000);
}

void batteriDrain() {
  unsigned long now = millis();

  // Simulert batteriforbruk
  if (now - lastDrainTime >= DRAIN_INTERVAL && batteri > 0) {
    int drain = 5;   // enkel: trekk 5% hver 3. sekund f.eks.

    batteri -= drain;
    if (batteri < 0) batteri = 0;

    lastDrainTime = now;
  }

  // Blink når batteri er lavt
  if (batteri <= 20) {
    if (now - lastBlinkTime > BLINK_INTERVAL) {
      blinkOn = !blinkOn;
      lastBlinkTime = now;
      
    }
  } else {
    blinkOn = true;
  }

  // TEGN DISPLAYET HVER GANG
  display.clearBuffer();
  display.setFont(u8g2_font_8x13_tf);

  // Batteriprosent
  char buf[12];
  snprintf(buf, sizeof(buf), "%d%%", batteri);
  display.drawStr(0, 12, "Batteri:");
  display.drawStr(70, 12, buf);

  // Varsel ved lavt batteri
  if (batteri <= 20 && blinkOn) {
    display.drawStr(0, 30, "Finn Ladestasjon");
    followLine2();
    returnToCharger();

  }

  display.sendBuffer();
}