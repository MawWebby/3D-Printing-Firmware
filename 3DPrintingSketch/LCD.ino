/////////////////////////////////////
///// LCD LIQUIDCRYSTAL DISPLAY /////
/////////////////////////////////////

// LCD ENGINE
void lcdEngine() {
  if (watchdogactivated == true) {
    lcd.clear();
    lcd.setCursor(1, 3);
    lcd.print(F("WATCHDOG ACTIVATED"));
    lcd.setCursor(2, 3);
    lcd.print(errorstack0);
  } else {
    if (settingsactivated == true) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("General"));
    } else {
      switch (lcddisplaytoshow) {
        // DEFAULT VIEW
        case 0:
          // DEFAULT VIEW
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("X");
          lcd.print(currentxdimensionLCD);
          lcd.setCursor(0, 1);
          lcd.print("Y");
          lcd.print(currentydimensionLCD);
          lcd.setCursor(0, 2);
          lcd.print("Z");
          lcd.print(currentzdimensionLCD);

          if (currentlylocked == true) {
            if (steppermotorsdisabled == true) {
              lcd.setCursor(4, 3);
              lcd.print(F("DISABLED"));
            }
          } else {
            if (steppermotorsdisabled == true) {
              lcd.setCursor(2, 3);
              lcd.print(F("STEPPER DISABLED"));
            } else {
              if (printingactive == false) {
                lcd.setCursor(8, 3);
                lcd.print(F("IDLE"));
              }
              if (printingactive == true) {
                lcd.setCursor(6, 3);
                lcd.print(F("PRINTING"));
              }
            }
          }

          lcd.setCursor(12, 0);
          if (currente0temp >= 50) {
            if (numbertoshow == 0 || numbertoshow == 1) {
              lcd.write(byte(5));
            } else {
              if (numbertoshow == 2 || numbertoshow == 3) {
                lcd.write(byte(6));
              } else {
                lcd.write(byte(5));
              }
            }
          } else {
            lcd.write(byte(4));
          }

          lcd.setCursor(12, 1);
          if (currenthbtemp >= 40) {
            if (numbertoshow == 0 || numbertoshow == 1) {
              lcd.write(byte(2));
            } else {
              if (numbertoshow == 2 || numbertoshow == 3) {
                lcd.write(byte(3));
              } else {
                if (numbertoshow == 4) {
                  numbertoshow = -1;
                  lcd.write(byte(3));
                }
              }
            }
          } else {
            lcd.write(byte(1));
          }

          numbertoshow = numbertoshow + 1;

          lcd.setCursor(13, 0);
          lcd.print(currente0temp);
          lcd.setCursor(13, 1);
          lcd.print(currenthbtemp);
          //          Serial.print(currente0temp);
          //         Serial.print(F(" "));
          //        Serial.println(currenthbtemp);
          //       lcd.setCursor(13, 3);
          //          lcd.print();
          break;
        case 1:
          lcd.clear();
          lcd.setCursor(0, 4);
          lcd.print(F("Printer Status"));
          {
            byte fullbar[8] = {
              B00000,
              B10001,
              B00000,
              B00000,
              B10001,
              B01110,
              B00000,
            };
            byte fourfifthbar[8] = {
              B00000,
              B10001,
              B00000,
              B00000,
              B10001,
              B01110,
              B00000,
            };
            byte threefifthbar[8] = {
              B00000,
              B10001,
              B00000,
              B00000,
              B10001,
              B01110,
              B00000,
            };
            byte twofifthbar[8] = {
              B00000,
              B00000,
              B00000,
              B00000,
              B00000,
              B00000,
              B00000,
            };
            byte onefifthbar[8] = {
              B10000,
              B10000,
              B10000,
              B10000,
              B10000,
              B10000,
              B10000,
            };
            byte zerofifthbar[8] = {
              B00000,
              B00000,
              B00000,
              B00000,
              B00000,
              B00000,
              B00000,
            };

            lcd.createChar(0, fullbar);
            lcd.createChar(1, fourfifthbar);
            lcd.createChar(2, threefifthbar);
            lcd.createChar(3, twofifthbar);
            lcd.createChar(4, onefifthbar);
            lcd.createChar(5, zerofifthbar);
          }


          break;
      }
    }
  }
}
