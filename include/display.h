#ifndef DISPLAY_H
#define DISPLAY_H

#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include <Arduino.h>

// Batteriverdi som hele programmet kan bruke
extern int batteri;

// OLED-display
extern U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI display;

void screenStartup();
void batteryDrain();

#endif