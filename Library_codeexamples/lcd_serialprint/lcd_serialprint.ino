/* Demonstration sketch for PCF8574T I2C LCD Backpack 
Uses library from https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads GNU General Public License, version 3 (GPL-3.0) */
#include <Wire.h>
//#include <LCD.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C	lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the I2C bus address of backpack by default

void setup()
{
  // activate LCD module
  lcd.begin (16,2); // for 16 x 2 LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  Serial.begin(9600);
}

void loop()

{ 

  if (Serial.available()) 
  {
    delay(100);// wait a bit for the entire message to arrive
    lcd.clear();// clear the screen
    // read all the available characters
    while (Serial.available() > 0) 
    {
      // display each character to the LCD
      lcd.write(Serial.read());
    }
  }
}




