#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include "Symbols.h"
 
U8G2_SH1107_SEEED_128X128_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);
 
void setup(void) {
  u8g2.begin();
}
 
void loop(void) {
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_pressstart2p_8f);
    u8g2.drawStr(0,10,"Abcdefghijklmnop");
    u8g2.drawStr(0,20,"Hello World!");
    u8g2.drawStr(0,30,"Hello World!");
    u8g2.drawStr(0,40,"Hello World!");
    u8g2.drawStr(0,50,"Hello World!");
    u8g2.drawStr(0,60,"Hello World!");
    u8g2.drawStr(0,70,"Hello World!");
    u8g2.drawStr(0,80,"Hello World!");
    u8g2.drawStr(0,90,"Hello World!");
    u8g2.drawStr(0,100,"Hello World!");
    u8g2.drawStr(0,110,"Hello World!");
    u8g2.drawStr(0,120,"Hello World!");

  } while ( u8g2.nextPage() );
}
