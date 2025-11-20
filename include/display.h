#ifndef DISPLAY_H
#define DISPLAY_H

#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include <Zumo32U4.h> 

// Batteriverdi som hele programmet kan bruke
extern int batteri;

// OLED-display-objektet (defineres i display.cpp)
extern U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI display;

// Funksjoner som implementeres i display.cpp
void screenStartup();
void batteriDrain();

#endif
