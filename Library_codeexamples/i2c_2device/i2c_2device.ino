#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Address,EN,RW , RS, D4,D5,D6,D7,BackLight,BL_Polarity
LiquidCrystal_I2C lcd1(0x26, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
LiquidCrystal_I2C lcd2(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

void setup()
{
 lcd1.begin(20,4); 
 lcd1.backlight();
 lcd1.print("LCD 20 X 4 ");
 lcd1.setCursor(0,1);
 lcd1.print("I2C Address 0x26");
 lcd1.setCursor(0,2);
 lcd1.print("Line 3");
 lcd1.setCursor(0,3);
 lcd1.print("Line 4");

 lcd2.begin(16,2); 
 lcd2.backlight();
 lcd2.print("LCD 16 x 2");
 lcd2.setCursor(0,1);
 lcd2.print("I2C Address 0x27");
 
}

void loop()
{
}
