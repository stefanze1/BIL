#include <Arduino.h> 
#include "display.h"
#include <U8g2lib.h>

// Batteriet starter på 90%
extern float batteryLevel;

// OLED-display: SH1106 128x64, SPI
U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI display(
  U8G2_R0,
  1,                 // clock (SCK)
  30,                // data (MOSI / PD5)
  U8X8_PIN_NONE,     // cs (ikke brukt)
  17,                // dc (PB0)
  0                  // reset (PD2)
);

int batteryPercent = 0;
bool blinkOn = true;

unsigned long now = 0;
unsigned long lastBlinkTime = 0;
unsigned long lastDrawTime = 0;
const unsigned long BLINK_INTERVAL = 400;
const unsigned long DRAW_INTERVAL  = 150; 

void screenStartup() {
  display.begin();
  display.setFont(u8g2_font_10x20_tf);
  display.drawStr(10, 20, "ZumoBil");
  display.sendBuffer();
  delay(2000);

  display.clearBuffer();
  display.sendBuffer();
}

void batteriDrain (){
    now = millis ();
    if (now - lastDrawTime < DRAW_INTERVAL){
        return;
    }
    lastDrawTime = now;
    
    if (batteryLevel < 0) batteryLevel = 0;
    if (batteryLevel > 100) batteryLevel = 100;
    batteryPercent = (int)(batteryLevel + 0.5f);
    
    if (batteryPercent <= 20) {
        if (now - lastBlinkTime > BLINK_INTERVAL) {
            blinkOn = !blinkOn;
            lastBlinkTime = now;
        }
    } else {
        blinkOn = true;
  }

  display.clearBuffer();
  display.setFont(u8g2_font_8x13_tf);

  display.drawStr(0, 12, BatteryLevel);

  char buf[10];
  snprintf(buf, sizeof(buf), "%d%%", batteryPercent);
  if (batteryPercent > 20 || blinkOn) {
    display.drawStr(70, 12, buf);
  }

  int blocks = batteryPercent / 10;
  display.drawStr(0, 40, "[##########]");

  for (int i = 0; i < blocks; i++) {
    display.drawStr(8 + i * 6, 40, "#");
  }

  if (batteryPercent <= 20 && blinkOn) {
    display.drawStr(0, 55, "Finn Ladestasjon");
  }

  display.sendBuffer();
}