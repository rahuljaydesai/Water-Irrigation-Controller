#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  // put your setup code here, to run once:
  
  Wire.begin();
  lcd.begin(20, 4);
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Auto Water Control");
  delay(3000);
  lcd.clear();
  Serial.begin(9600);
  
}

void loop() {
  
  boolean isPrinted = false;
  if (Serial.available() > 0) {
    int data = Serial.read();
     
    while (data == '0') {
      
      if (isPrinted == false) {
        lcd.clear();
        lcd.print("Reading Data...");
        isPrinted = true;
       }
       data = Serial.read();
    }
    
    while (data == '1') {
       if (isPrinted == false) {
         lcd.clear();
         lcd.print("Water for 5 min");
         isPrinted = true;
       }
       data = Serial.read();
    }

    while (data == '2') {
       if (isPrinted == false) {
         lcd.clear();
         lcd.print("Water for 3 min.");
         isPrinted = true;
       }
       data = Serial.read();
    }

    while (data == '3') {
       if (isPrinted == false) {
         lcd.clear();
         lcd.print("No need to Water");
         isPrinted = true;
       }
       data = Serial.read();
    }

    while (data == '4') {
       if (isPrinted == false) {
         lcd.clear();
         lcd.print("Too much Water");
         isPrinted = true;
       }
       data = Serial.read();
    }

    while (data == '5') {
       if (isPrinted == false) {
         lcd.clear();
         lcd.print("Too Hot to Water");
         isPrinted = true;
       }
       data = Serial.read();
    }
  }

}
