 #ifndef DISPLAY_H
#define DISPLAY_H

#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include <Arduino.h>

extern int batteri;

extern U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI display;

// Funksjoner som implementeres i display.cpp
void screenStartup();
void batteriDrain();

#endif