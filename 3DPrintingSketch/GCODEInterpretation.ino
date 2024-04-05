//////////////////////
///// DICTIONARY /////
//////////////////////

// INTERPRETATION LOOP
int interpretation(String commanding) {
  bool interpretedcompleted = false;
  String firstletter = commanding.substring(0, 1);

  // PASSWORD PROTECTED SERIAL DECODER
  if (currentlylocked == true) {
    firstletter = commanding.substring(0, 1);
    if (firstletter == "M") {
      firstletter = commanding.substring(1, 2);
      if (firstletter == "5") {
        firstletter = commanding.substring(2, 3);
        if (firstletter == "1") {
          firstletter = commanding.substring(3, 4);
          if (firstletter == "1") {
            firstletter = commanding.substring(4, 5);
            if (firstletter == " ") {
              if (cpswd != "") {
                String tpswd = commanding.substring(5, 100);
                if (tpswd == cpswd) {
                  Serial.println(F("unlock"));
                  currentlylocked = false;
                  return (0);
                } else {
                  Serial.println(F("locked - M511"));
                  currentlylocked = true;
                  return (2);
                }
              } else {
                String tpswd = commanding.substring(5, 100);
                if (tpswd == dpswd) {
                  Serial.println(F("unlock"));
                  currentlylocked = false;
                  return (0);
                } else {
                  Serial.println(F("locked - M511"));
                  currentlylocked = true;
                  return (2);
                }
              }
            } else {
              Serial.println(F("NO ARGS WERE PASSED!"));
              currentlylocked = true;
              return (2);
            }
          }
        }
      }
    }
    Serial.println(F("lock - M511"));
    Serial.println(F("CURRENTLY LOCKED! - M511"));
    ePARSER(commanding);
    return (2);
  }

  //. IF COMMAND STARTS WITH " ", REMOVE THE FRONT SPACE AND RESTART INTERPRETATION
  if (firstletter == " ") {
    interpretation(commanding.substring(1, 255));
    interpretedcompleted = true;
  }

  // IF COMMAND STARTS WITH N, REMOVE LINE NUMBERS AND RESTART INTERPRETATION
  if (firstletter == "N") {

    // VARIABLES
    bool finished = false;
    String fixin = "";
    int prisms = 1;

    // WHILE THE COMMAND IS TRUE FOR BOTH CASES (supports up to 1 * 10^30)
    while (finished != true && prisms != 100) {
      fixin = commanding.substring(prisms, prisms + 1);

      if (fixin == " ") {
        fixin = commanding.substring(prisms + 1, 255);
        int testers = interpretation(fixin);
        finished = true;
        interpretedcompleted = true;
        return (testers);
      }
      prisms = prisms + 1;
    }
    interpretedcompleted = true;
  }

  // IF COMMAND STARTS WITH E, RUN IMMEDIATELY!
  if (firstletter == "E") {
    eShell(commanding);
  }
  

  // IF COMMAND STARTS WITH Q, EVALUATE WHAT IT ACTUALLY MEANS
  if (firstletter == "Z") {

    // DETERMINE THE SECOND LETTER OF THE STRING
    firstletter = commanding.substring(1, 2);

    // Z0 - LOAD FILAMENT AND UNLOAD FILAMENT
    if (firstletter == "0") {

      // DETERMINE THE INPUT STRING
      firstletter = commanding.substring(3, 4);

      if (firstletter == "" || firstletter == " ") {
        Serial.println(F("NO COMMAND RECEIVED! IGNORING TYPE EXTRUSION"));
        Serial.println(F("0 - UNLOAD FILAMENT / 1 - LOAD FILAMENT"));
        return (2);
      }

      // Z0 0 - UNLOAD FILAMENT
      if (firstletter == "0") {
        Serial.println(F("PLEASE WAIT"));
        lcd.clear();
        lcd.setCursor(4, 1);
        lcd.print(F("PLEASE WAIT"));

        int timertest9800 = 0;
        bool totemp = false;

        while (timertest9800 < extrusiontimeout && totemp == false) {
          digitalWrite(HEATER_0_PIN, HIGH);
          lcd.setCursor(5, 2);
          currente0temp = (1010 - TEMP_0_PIN) * e0tempmodifier;
          lcd.print(currente0temp);
          if (TEMP_0_PIN > 250) {
            totemp = true;
          }
          timertest9800 = timertest9800 + 1;
          delay(1000);
          eSERIALRECEIVER();
        }

        digitalWrite(E_ENABLE_PIN, HIGH);
        digitalWrite(E_STEP_PIN, HIGH);
        digitalWrite(E_DIR_PIN, LOW);
        digitalWrite(HEATER_0_PIN, LOW);

        Serial.println(F("PLEASE REMOVE THE FILAMENT NOW"));
        lcd.clear();
        lcd.setCursor(4, 1);
        lcd.print(F("REMOVE FILAMENT NOW"));

        delay(5000);

        digitalWrite(E_ENABLE_PIN, LOW);
        digitalWrite(E_STEP_PIN, LOW);
        digitalWrite(E_DIR_PIN, LOW);
        digitalWrite(HEATER_0_PIN, LOW);
      }

      // Z0 1 - LOAD FILAMENT
      if (firstletter == "0") {
        Serial.println(F("PLEASE WAIT"));
        lcd.clear();
        lcd.setCursor(4, 1);
        lcd.print(F("PLEASE WAIT"));

        int timertest9800 = 0;
        bool totemp = false;

        while (timertest9800 < extrusiontimeout && totemp == false) {
          digitalWrite(HEATER_0_PIN, HIGH);
          lcd.setCursor(5, 2);
          currente0temp = (1010 - TEMP_0_PIN) * e0tempmodifier;
          lcd.print(currente0temp);
          if (TEMP_0_PIN > 250) {
            totemp = true;
          }
          timertest9800 = timertest9800 + 1;
          delay(1000);
          eSERIALRECEIVER();
        }

        digitalWrite(E_ENABLE_PIN, HIGH);
        digitalWrite(E_STEP_PIN, HIGH);
        digitalWrite(E_DIR_PIN, HIGH);
        digitalWrite(HEATER_0_PIN, LOW);

        Serial.println(F("PLEASE REMOVE THE FILAMENT NOW"));
        lcd.clear();
        lcd.setCursor(4, 1);
        lcd.print(F("REMOVE FILAMENT NOW"));

        delay(5000);

        digitalWrite(E_ENABLE_PIN, LOW);
        digitalWrite(E_STEP_PIN, LOW);
        digitalWrite(E_DIR_PIN, LOW);
        digitalWrite(HEATER_0_PIN, LOW);
      }
    }

    // Z1* - IF THE SECOND NUMBER IS A "1" CONTINUE
    if (firstletter == "1") {

      // DETERMINE THE THIRD LETTER OF THE STRING
      firstletter = commanding.substring(2, 3);

      // Z1 - IS THE PRINTER ACTIVE?
      if (firstletter == " " || firstletter == "") {

        if (firstletter != " ") {
          Serial.println(F("Z1 - NO ARGS PASSED! Skipping..."));
          return (2);
        }

        firstletter = commanding.substring(3, 4);
        printingactive = firstletter.toInt();

        if (printingactive == true) {
          Serial.println(F("PRINTING ACTIVE"));
          return (0);
        }

        if (printingactive == false) {
          Serial.println(F("printer no longer active"));
          return (0);
        }
        return (2);
      }

      // Z10*
      if (firstletter == "0") {

        // READ THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // Z10 - EMERGENCY SHUTOFF MODE
        if (firstletter == "" || firstletter == " ") {
          watchdogactivated = true;
          Serial.println(F("EMERGENCY SHUTDOWN MODE ACTIVATED"));
          return (0);
        }
      }

      // Z11*
      if (firstletter == "1") {
        Serial.println(F("Z11 NO LONGER SUPPORTED"));
        return (0);
      }

      // Z12*
      if (firstletter == "2") {

        // READ THE FOURTH LETTER OF TEH STRING
        firstletter = commanding.substring(3, 4);

        // Z12 - FULL DEBUG OF MOTOR MOVEMENT OVER SERIAL
        if (firstletter == "" || firstletter == " ") {
          Serial.println(F("ok"));
          Serial.println(currente0temp);
          Serial.println(currente1temp);
          Serial.println(currenthbtemp);
          Serial.println(F("RAW"));
          Serial.println(analogRead(TEMP_0_PIN));
          Serial.println(analogRead(TEMP_1_PIN));
          Serial.println(analogRead(TEMP_HB_PIN));
          return (0);
        }
      }

      // Z13*
      if (firstletter == "3") {

        // READ THE FORUTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
        if (firstletter == " ") {
          String modmod = commanding.substring(4, 100);

          // SET MODIFIERS BUTTON
        }

        if (firstletter == "") {
          Serial.println(F("NO ARGS PASSED FOR TEMPERATURE MODIFICATION"));
          Serial.println(F("ok"));
          return (2);
        }
      }

      // Z14*
      if (firstletter == "4") {

        // READ ALL VARIABLES RELATING TO CACHING
        return (0);
      }

      // Z15*
      if (firstletter == "5") {

        // READ ALL VARIABLES RELATING TO CACHING (FINAL)
        return (0);
      }
    }

    // Z2* -
    if (firstletter == "2") {

      // DETERMINE THE THIRD LETTER OF THE STRING
      firstletter = commanding.substring(2, 3);

      if (firstletter == " " || firstletter == "") {
        // Z2 - PRINT ENTIRE CACHED ARRAY TO SERIAL

        int greatnumber6000 = 0;
        while (greatnumber6000 <= 12) {
          Serial.print(analyzedgcodestack0[greatnumber6000]);
          greatnumber6000 = greatnumber6000 + 1;
          Serial.print(F(" "));
        }
        Serial.println();
        greatnumber6000 = 0;
        while (greatnumber6000 <= 12) {
          Serial.print(analyzedgcodestack1[greatnumber6000]);
          greatnumber6000 = greatnumber6000 + 1;
          Serial.print(F(" "));
        }
        Serial.println();
        greatnumber6000 = 0;
        while (greatnumber6000 <= 12) {
          Serial.print(analyzedgcodestack2[greatnumber6000]);
          greatnumber6000 = greatnumber6000 + 1;
          Serial.print(F(" "));
        }
        Serial.println();
        greatnumber6000 = 0;
        while (greatnumber6000 <= 12) {
          Serial.print(analyzedgcodestack3[greatnumber6000]);
          greatnumber6000 = greatnumber6000 + 1;
          Serial.print(F(" "));
        }
        Serial.println();
        greatnumber6000 = 0;
        while (greatnumber6000 <= 12) {
          Serial.print(analyzedgcodestack4[greatnumber6000]);
          greatnumber6000 = greatnumber6000 + 1;
          Serial.print(F(" "));
        }
        Serial.println();
        greatnumber6000 = 0;
        while (greatnumber6000 <= 12) {
          Serial.print(analyzedgcodestack5[greatnumber6000]);
          greatnumber6000 = greatnumber6000 + 1;
          Serial.print(F(" "));
        }
        Serial.println();
        greatnumber6000 = 0;
        while (greatnumber6000 <= 12) {
          Serial.print(analyzedgcodestack6[greatnumber6000]);
          greatnumber6000 = greatnumber6000 + 1;
          Serial.print(F(" "));
        }
        Serial.println();
        greatnumber6000 = 0;
        while (greatnumber6000 <= 12) {
          Serial.print(analyzedgcodestack7[greatnumber6000]);
          greatnumber6000 = greatnumber6000 + 1;
          Serial.print(F(" "));
        }
        Serial.println();
        greatnumber6000 = 0;
        while (greatnumber6000 <= 12) {
          Serial.print(analyzedgcodestack8[greatnumber6000]);
          greatnumber6000 = greatnumber6000 + 1;
          Serial.print(F(" "));
        }
        Serial.println();
        greatnumber6000 = 0;
        while (greatnumber6000 <= 12) {
          Serial.print(analyzedgcodestack9[greatnumber6000]);
          greatnumber6000 = greatnumber6000 + 1;
          Serial.print(F(" "));
        }
        Serial.println();
        greatnumber6000 = 0;
        while (greatnumber6000 <= 12) {
          Serial.print(analyzedgcodestack10[greatnumber6000]);
          greatnumber6000 = greatnumber6000 + 1;
          Serial.print(F(" "));
        }
        Serial.println();
        return (0);
      }

      // Z20* - CONTINUE
      if (firstletter == "0") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // Z200 - MOVE X-AXIS TO CERTAIN POSITION
        if (firstletter == "0") {

          // DETERMINE THE FIFTH LETTER OF THE STRING
          firstletter = commanding.substring(4, 5);

          // CHECK AND SEE IF THERE ARE ARGS THAT ARE PASSED
          if (firstletter == "") {
            xhome();
            interpretedcompleted = true;
            return (1);
          }

          // IF THERE ARE ARGS, SET X TO THAT POSITION AND CONTINUE
          if (firstletter == " ") {
            String xtargett = firstletter.substring(5, 125);
            targetxdimension = xtargett.toFloat();
            Serial.println(F("ok"));
            interpretedcompleted = true;
          }
        }

        // Z201 - MOVE Y-AXIS TO CERTAIN POSITION
        if (firstletter == "1") {

          // DETERMINE THE FIFTH LETTER OF THE STRING
          firstletter = commanding.substring(4, 5);

          // CHECK AND SEE IF THERE ARE ARGS THAT ARE PASSED
          if (firstletter == "") {
            yhome();
            interpretedcompleted = true;
            return (1);
          }

          // IF THERE ARE ARGS, SET X TO THAT POSITION AND CONTINUE
          if (firstletter == " ") {
            String ytargett = firstletter.substring(5, 125);
            targetydimension = ytargett.toFloat();
            Serial.println(F("ok"));
            interpretedcompleted = true;
          }
        }

        // Z202 - MOVE Z-AXIS TO CERTAIN POSITION
        if (firstletter == "2") {

          // DETERMINE THE FIFTH LETTER OF THE STRING
          firstletter = commanding.substring(4, 5);

          // CHECK AND SEE IF THERE ARE ARGS THAT ARE PASSED
          if (firstletter == "") {
            zhome();
            interpretedcompleted = true;
            return (1);
          }

          // IF THERE ARE ARGS, SET X TO THAT POSITION AND CONTINUE
          if (firstletter == " ") {
            String ztargett = firstletter.substring(5, 125);
            targetzdimension = ztargett.toFloat();
            Serial.println(F("ok"));
            interpretedcompleted = true;
          }
        }

        // Z203 - MOVE E-AXIS TO CERTAIN POSITION
        if (firstletter == "3") {

          // DETERMINE THE FIFTH LETTER OF THE STRING
          firstletter = commanding.substring(4, 5);

          // CHECK AND SEE IF THERE ARE ARGS THAT ARE PASSED
          if (firstletter == "") {
            Serial.println(F("NO ARGS PASSED! CANT CONTINUE!"));
            interpretedcompleted = true;
            return (1);
          }

          // IF THERE ARE ARGS, SET X TO THAT POSITION AND CONTINUE
          if (firstletter == " ") {
            String etargett = firstletter.substring(5, 125);
            targete0motordimension = etargett.toFloat();
            Serial.println(F("ok"));
            interpretedcompleted = true;
          }
        }

        // Z204 - HOME ALL
        if (firstletter == "4") {
          homeall();
        }

        // Z205 - MOVE ALL DIMENSIONS TO A CERTAIN POSITION (XYZE)
        if (firstletter == "5") {
          String xtarget = firstletter.substring(5, 11);
          String ytarget = firstletter.substring(10, 16);
          String ztarget = firstletter.substring(16, 22);
          String etarget = firstletter.substring(22, 28);
          Serial.println(xtarget);
          Serial.println(ytarget);
          Serial.println(ztarget);
          Serial.println(etarget);
          targetxdimension = xtarget.toFloat();
          targetydimension = ytarget.toFloat();
          targetzdimension = ztarget.toFloat();
          targete0motordimension = etarget.toFloat();
          movetonewgcodeformovement(false);
          interpretedcompleted = true;
        }
      }
    }

    // Z3* -
    if (firstletter == "3") {

      // DETERMINE THE THIRD LETTER OF THE STRING
      firstletter = commanding.substring(2, 3);

      if (firstletter == "") {
        Serial.println(F("Q3 - NO ARGS PASSED! Skipping..."));
        return (2);
      }

      if (firstletter == " ") {
        // Q3 - TURN DEBUGGING FEATURE ON OR OFF TO SERIAL INTERFACE
        firstletter = commanding.substring(3, 4);
        debugserial = firstletter.toInt();
        return (0);
      }
    }

    // Z4* -
    if (firstletter == "4") {

      // DETERMINE THE THIRD LETTER OF THE STRING
      firstletter = commanding.substring(2, 3);

      if (firstletter == "") {
        // Q4 - READ THE UNCACHED DATA ARRAY TO SERIAL BUS
        Serial.println(gcodestack0);
        Serial.println(gcodestack1);
        Serial.println(gcodestack2);
        Serial.println(gcodestack3);
        Serial.println(gcodestack4);
        Serial.println(gcodestack5);
        Serial.println(gcodestack6);
        Serial.println(gcodestack7);
        Serial.println(gcodestack8);
        Serial.println(gcodestack9);
        Serial.println(gcodestack10);
        return (0);
      }
      return (2);
    }

    // Z5* -
    if (firstletter == "5") {

      // DETERMINE THE THIRD LETTER OF THE STRING
      firstletter = commanding.substring(2, 3);

      if (firstletter == "") {
        // Q5 - READ VARIABLES RELATING TO CACHING ARRAY
        return (0);
      }
      return (0);
    }

    // Z6* -
    if (firstletter == "6") {
      Serial.println(currentxdimension);
      Serial.println(currentydimension);
      Serial.println(currentzdimension);
      Serial.println(currente0motordimension);
      Serial.println(currente1motordimension);
      return (0);
    }

    // Z7* -
    if (firstletter == "7") {
      Serial.println(F("ADD ENDSTOPS HERE EVENTUALLY"));
      return (0);
    }

    // Z8* -
    if (firstletter == "8") {
      Serial.println(currente0temp);
      Serial.println(currente1temp);
      Serial.println(currenthbtemp);
      return (0);
    }

    // Z9* -
    if (firstletter == "9") {

      // DETERMINE THE THIRD LETTER OF THE STRING
      firstletter = commanding.substring(2, 3);

      // Z99*
      if (firstletter == "9") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // Z999 - PRINT ENTIRE DATABASE TO SERIAL BUS/OTHER DATABASE OPERATIONS
        if (firstletter == "9") {

          // DETERMINE THE FIFTH LETTER OF THE STRING
          firstletter = commanding.substring(4, 5);

          if (firstletter == "") {

            Serial.println(printingactive);

            for (int i = 0; i < 11; i++) {
              Serial.print(analyzedgcodestack0[i]);
              Serial.print(F(" "));
            }
            Serial.println(F(""));
            for (int i = 0; i < 11; i++) {
              Serial.print(analyzedgcodestack1[i]);
              Serial.print(F(" "));
            }
            Serial.println(F(""));
            for (int i = 0; i < 11; i++) {
              Serial.print(analyzedgcodestack2[i]);
              Serial.print(F(" "));
            }
            Serial.println(F(""));
            for (int i = 0; i < 11; i++) {
              Serial.print(analyzedgcodestack3[i]);
              Serial.print(F(" "));
            }
            Serial.println(F(""));
            for (int i = 0; i < 11; i++) {
              Serial.print(analyzedgcodestack4[i]);
              Serial.print(F(" "));
            }
            Serial.println(F(""));
            for (int i = 0; i < 11; i++) {
              Serial.print(analyzedgcodestack5[i]);
              Serial.print(F(" "));
            }
            Serial.println(F(""));
            for (int i = 0; i < 11; i++) {
              Serial.print(analyzedgcodestack6[i]);
              Serial.print(F(" "));
            }
            Serial.println(F(""));
            for (int i = 0; i < 11; i++) {
              Serial.print(analyzedgcodestack7[i]);
              Serial.print(F(" "));
            }
            Serial.println(F(""));
            for (int i = 0; i < 11; i++) {
              Serial.print(analyzedgcodestack8[i]);
              Serial.print(F(" "));
            }
            Serial.println(F(""));
            for (int i = 0; i < 11; i++) {
              Serial.print(analyzedgcodestack9[i]);
              Serial.print(F(" "));
            }
            Serial.println(F(""));
            for (int i = 0; i < 11; i++) {
              Serial.print(analyzedgcodestack10[i]);
              Serial.print(F(" "));
            }
            Serial.println(F(""));
            Serial.println(F("ok"));
          }

          if (firstletter == ".") {

            // DETERMINE THE SIXTH LETTER OF THE STRING
            firstletter = commanding.substring(5, 6);

            // Z999.1 - CLEAR ENTIRE DATABASE
            if (firstletter == "1") {
              Serial.println(F("CLEARING DATABAE!"));

              delay(100);
              /////////////////////////////////////
              // DO A FRESH WIPE OF MASTER ARRAY //
              /////////////////////////////////////
              clearrowinarray(0, true);
              clearrowinarray(1, true);
              clearrowinarray(2, true);
              clearrowinarray(3, true);
              clearrowinarray(4, true);

              delay(1000);

              clearrowinarray(5, true);
              clearrowinarray(6, true);
              clearrowinarray(7, true);
              clearrowinarray(8, true);
              clearrowinarray(9, true);
              clearrowinarray(10, true);

              Serial.println(F("DONE!"));
              Serial.println(F("ok"));
            }
          }
        }
      }
      return (0);
    }
  }

  //  IF COMMAND STARTS WITH G, CACHE TO BE FURTHER ANALYZED
  if (firstletter == "G") {

    // DETERMINE THE SECOND LETTER OF THE STRING
    firstletter = commanding.substring(1, 2);

    // G0 - MOVEMENT COMMAND WITH NO EXTRUSION
    if (firstletter == "0") {

      // DETERMINE THE SECOND LETTER OF THE STRING
      firstletter = commanding.substring(2, 3);

      // PRINTER ACTIVE
      printingactive = true;

      if (firstletter == "") {
        Serial.println(F("EMPTY G0 COMMAND RECEIVED - IGNORING"));
        return (2);
      }
      if (firstletter == " ") {

        commanding = commanding + " ";

        // ANALYZING QUICK COMMANDS
        bool gcodecomplete = false;
        int gcodenumber = 3;
        int executionnumber = 0;

      // analyzedCURRENTLYANALYZINGNUMBER FLIP
        while (readfromarray(analyzedCURRENTLYANALYZINGNUMBER, 10) == 1) {
          analyzedCURRENTLYANALYZINGNUMBER = analyzedCURRENTLYANALYZINGNUMBER + 1;
          if (analyzedCURRENTLYANALYZINGNUMBER == 11) {
            analyzedCURRENTLYANALYZINGNUMBER = 0;
          }
        }

        bool xstatement = false;
        bool ystatement = false;
        bool zstatement = false;
        bool estatement = false;

        // MAIN ANALYZE GCODE LOOP
        while (gcodecomplete != true && executionnumber <= 25) {

          // EMERGENCY LOOP
          eSERIALRECEIVER();

          // DETERMINE THE NEXT LETTER IN THE STRING
          firstletter = commanding.substring(gcodenumber, gcodenumber + 1);

          // IF IT IS " ", MOVE ON TO NEXT CHARACTER
          if (firstletter == " ") {
            gcodenumber = gcodenumber + 1;
            firstletter = commanding.substring(gcodenumber, gcodenumber + 1);
          }

          // IF IT IS "", FINISH LOOP AND HEAD BACK TO MAIN LOOP
          if (firstletter == "") {
            Serial.println(F("ok"));
            gcodecomplete = true;
          }

          // IF IT IS A "X", DETERMINE NUMBER OF CHARACTERS, THEN SAVE TO DB ARRAY
          if (firstletter == "X") {
            int startxdigit = gcodenumber + 1;
            gcodenumber = gcodenumber + 1;
            int finalxdigit = 0;
            bool xfinished = false;
            int xexecutionnumber = 0;

            while (xfinished != true && xexecutionnumber <= 10) {
              // DETERMINE THE NEXT CHARACTER IN THE STRING
              firstletter = commanding.substring(gcodenumber, gcodenumber + 1);

              // WAIT UNTIL CHARACTER RECEIVED IS A " ", THEN END THIS WHILE LOOP
              if (firstletter == " " || firstletter == "") {
                String xvalues = commanding.substring(startxdigit, gcodenumber);
                float xvaluestoinsert = xvalues.toFloat();
                sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, xvaluestoinsert, 0);
                xfinished = true;
                xstatement = true;
                //                targetxdimension = xvaluestoinsert;
              }

              gcodenumber = gcodenumber + 1;
              xexecutionnumber = xexecutionnumber + 1;
            }
            firstletter = commanding.substring(gcodenumber, gcodenumber + 1);
          }

          // IF IT IS A "Y", DETERMINE NUMBER OF CHARACTERS, THEN SAVE TO DB ARRAY
          if (firstletter == "Y") {
            int startydigit = gcodenumber + 1;
            gcodenumber = gcodenumber + 1;
            int finalydigit = 0;
            bool yfinished = false;
            int yexecutionnumber = 0;

            while (yfinished != true && yexecutionnumber <= 10) {
              // DETERMINE THE NEXT CHARACTER IN THE STRING
              firstletter = commanding.substring(gcodenumber, gcodenumber + 1);

              // WAIT UNTIL CHARACTER RECEIVED IS A " ", THEN END THIS WHILE LOOP
              if (firstletter == " " || firstletter == "") {
                String yvalues = commanding.substring(startydigit, gcodenumber);
                float yvaluestoinsert = yvalues.toFloat();
                sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, yvaluestoinsert, 1);
                yfinished = true;
                ystatement = true;
              }

              gcodenumber = gcodenumber + 1;
              yexecutionnumber = yexecutionnumber + 1;
            }
            firstletter = commanding.substring(gcodenumber, gcodenumber + 1);
          }

          // IF IT IS A "Z", DETERMINE NUMBER OF CHARACTERS, THEN SAVE TO DB ARRAY
          if (firstletter == "Z") {
            int startzdigit = gcodenumber + 1;
            gcodenumber = gcodenumber + 1;
            int finalzdigit = 0;
            bool zfinished = false;
            int zexecutionnumber = 0;

            while (zfinished != true && zexecutionnumber <= 10) {
              // DETERMINE THE NEXT CHARACTER IN THE STRING
              firstletter = commanding.substring(gcodenumber, gcodenumber + 1);

              // WAIT UNTIL CHARACTER RECEIVED IS A " ", THEN END THIS WHILE LOOP
              if (firstletter == " " || firstletter == "") {
                String zvalues = commanding.substring(startzdigit, gcodenumber);
                float zvaluestoinsert = zvalues.toFloat();
                sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, zvaluestoinsert, 2);
                zfinished = true;
                zstatement = true;
              }

              gcodenumber = gcodenumber + 1;
              zexecutionnumber = zexecutionnumber + 1;
            }
            firstletter = commanding.substring(gcodenumber, gcodenumber + 1);
          }

          // IF IT IS A "E", DETERMINE NUMBER OF CHARACTERS, THEN SAVE TO DB ARRAY
          if (firstletter == "E") {
            Serial.println(F("G0 COMMANDS DO NOT CONTAIN E VALUES!"));
            int startedigit = gcodenumber + 1;
            gcodenumber = gcodenumber + 1;
            int finaledigit = 0;
            bool efinished = false;
            int eexecutionnumber = 0;

            while (efinished != true && eexecutionnumber <= 10) {
              // DETERMINE THE NEXT CHARACTER IN THE STRING
              firstletter = commanding.substring(gcodenumber, gcodenumber + 1);

              // WAIT UNTIL CHARACTER RECEIVED IS A " ", THEN END THIS WHILE LOOP
              if (firstletter == " " || firstletter == "") {
                String evalues = commanding.substring(startedigit, gcodenumber);
                float evaluestoinsert = evalues.toFloat();
                sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, evaluestoinsert, 3);
                efinished = true;
                estatement = true;
              }

              gcodenumber = gcodenumber + 1;
              eexecutionnumber = eexecutionnumber + 1;
            }
            firstletter = commanding.substring(gcodenumber, gcodenumber + 1);
          }

          // IF IT IS A "E", DETERMINE NUMBER OF CHARACTERS, THEN SAVE TO DB ARRAY
          if (firstletter == "F") {
            // FEEDRATE VARIABLES
            gcodecomplete = true;
          }

          // TIME UP VARIABLES
          gcodenumber = gcodenumber + 1;
          executionnumber = executionnumber + 1;
        }

        // DECLARE PREVIOUS INFORMATION IN NEW SCRIPT IF NO INFORMATION WAS GIVEN PREVIOUSLY!
        if (xstatement == false) {
          if (analyzedCURRENTLYANALYZINGNUMBER == 0) {
            sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, readfromarray(10, 0), 0);
          } else {
            sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, readfromarray(analyzedCURRENTLYANALYZINGNUMBER - 1, 0), 0);
          }
        }
        if (ystatement == false) {
          if (analyzedCURRENTLYANALYZINGNUMBER == 0) {
            sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, readfromarray(10, 1), 1);
          } else {
            sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, readfromarray(analyzedCURRENTLYANALYZINGNUMBER - 1, 1), 1);
          }
        }
        if (zstatement == false) {
          if (analyzedCURRENTLYANALYZINGNUMBER == 0) {
            sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, readfromarray(10, 2), 2);
          } else {
            sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, readfromarray(analyzedCURRENTLYANALYZINGNUMBER - 1, 2), 2);
          }
        }
        if (estatement == false) {
          if (analyzedCURRENTLYANALYZINGNUMBER == 0) {
            sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, readfromarray(10, 3), 3);
          } else {
            sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, readfromarray(analyzedCURRENTLYANALYZINGNUMBER - 1, 3), 3);
          }
        }

        

        // SEND CURRENT GCODE COMMAND TO BE OK IF THERE ARE LESS THAN 8 CURRENTLY CACHED GCODE COMMANDS
        if (currentlycachedgcodes <= 8) {
          Serial.println(F("ok"));
          sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, 1, 9);
        } else {
          sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, 0, 9);
        }

        // CURRENTLY CACHED GCODES!
        currentlycachedgcodes = currentlycachedgcodes + 1;

        // SEND LOCK TO ARRAY TO FINISH GCODE ANALYZING
        sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, 1, 10);

        // GCODE COMPLETE
        interpretedcompleted = true;
      }
    }

    // G1*
    if (firstletter == "1") {

      // DETERMINE THE THIRD LETTER OF THE STRING
      firstletter = commanding.substring(2, 3);

      // "" - EMPTY G1 COMMAND
      if (firstletter == "") {
        Serial.println(F("EMPTY GCODE COMMAND!"));
        Serial.println(F("OK"));
        interpretedcompleted = true;
      }

      // G1 - MOVEMENT COMMAND WITH EXTRUSION
      if (firstletter == " ") {

        // DETERMINE THE SECOND LETTER OF THE STRING
        firstletter = commanding.substring(2, 3);

        // PRINTER ACTIVE
        printingactive = true;

        if (firstletter == "") {
          Serial.println(F("EMPTY G1 COMMAND RECEIVED - IGNORING"));
          return (2);
        }
        if (firstletter == " ") {

          commanding = commanding + " ";

          // ANALYZING QUICK COMMANDS
          bool gcodecomplete = false;
          int gcodenumber = 3;
          int executionnumber = 0;

          while (readfromarray(analyzedCURRENTLYANALYZINGNUMBER, 10) == 1) {
            analyzedCURRENTLYANALYZINGNUMBER = analyzedCURRENTLYANALYZINGNUMBER + 1;
            if (analyzedCURRENTLYANALYZINGNUMBER == 11) {
              analyzedCURRENTLYANALYZINGNUMBER = 0;
            }
          }

          while (gcodecomplete != true && executionnumber <= 25) {

            // EMERGENCY LOOP
            eSERIALRECEIVER();

            // DETERMINE THE NEXT LETTER IN THE STRING
            firstletter = commanding.substring(gcodenumber, gcodenumber + 1);

            // IF IT IS " ", MOVE ON TO NEXT CHARACTER
            if (firstletter == " ") {
              gcodenumber = gcodenumber + 1;
              firstletter = commanding.substring(gcodenumber, gcodenumber + 1);
            }

            // IF IT IS "", FINISH LOOP AND HEAD BACK TO MAIN LOOP
            if (firstletter == "") {
              Serial.println(F("ok"));
              gcodecomplete = true;
            }

            // IF IT IS A "X", DETERMINE NUMBER OF CHARACTERS, THEN SAVE TO DB ARRAY
            if (firstletter == "X") {
              int startxdigit = gcodenumber + 1;
              gcodenumber = gcodenumber + 1;
              int finalxdigit = 0;
              bool xfinished = false;
              int xexecutionnumber = 0;

              while (xfinished != true && xexecutionnumber <= 10) {
                // DETERMINE THE NEXT CHARACTER IN THE STRING
                firstletter = commanding.substring(gcodenumber, gcodenumber + 1);

                // WAIT UNTIL CHARACTER RECEIVED IS A " ", THEN END THIS WHILE LOOP
                if (firstletter == " " || firstletter == "") {
                  String xvalues = commanding.substring(startxdigit, gcodenumber);
                  float xvaluestoinsert = xvalues.toFloat();
                  sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, xvaluestoinsert, 0);
                  xfinished = true;
                  //                targetxdimension = xvaluestoinsert;
                }

                gcodenumber = gcodenumber + 1;
                xexecutionnumber = xexecutionnumber + 1;
              }
              firstletter = commanding.substring(gcodenumber, gcodenumber + 1);
            }

            // IF IT IS A "Y", DETERMINE NUMBER OF CHARACTERS, THEN SAVE TO DB ARRAY
            if (firstletter == "Y") {
              int startydigit = gcodenumber + 1;
              gcodenumber = gcodenumber + 1;
              int finalydigit = 0;
              bool yfinished = false;
              int yexecutionnumber = 0;

              while (yfinished != true && yexecutionnumber <= 10) {
                // DETERMINE THE NEXT CHARACTER IN THE STRING
                firstletter = commanding.substring(gcodenumber, gcodenumber + 1);

                // WAIT UNTIL CHARACTER RECEIVED IS A " ", THEN END THIS WHILE LOOP
                if (firstletter == " " || firstletter == "") {
                  String yvalues = commanding.substring(startydigit, gcodenumber);
                  float yvaluestoinsert = yvalues.toFloat();
                  sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, yvaluestoinsert, 1);
                  yfinished = true;
                }

                gcodenumber = gcodenumber + 1;
                yexecutionnumber = yexecutionnumber + 1;
              }
              firstletter = commanding.substring(gcodenumber, gcodenumber + 1);
            }

            // IF IT IS A "Z", DETERMINE NUMBER OF CHARACTERS, THEN SAVE TO DB ARRAY
            if (firstletter == "Z") {
              int startzdigit = gcodenumber + 1;
              gcodenumber = gcodenumber + 1;
              int finalzdigit = 0;
              bool zfinished = false;
              int zexecutionnumber = 0;

              while (zfinished != true && zexecutionnumber <= 10) {
                // DETERMINE THE NEXT CHARACTER IN THE STRING
                firstletter = commanding.substring(gcodenumber, gcodenumber + 1);

                // WAIT UNTIL CHARACTER RECEIVED IS A " ", THEN END THIS WHILE LOOP
                if (firstletter == " " || firstletter == "") {
                  String zvalues = commanding.substring(startzdigit, gcodenumber);
                  float zvaluestoinsert = zvalues.toFloat();
                  sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, zvaluestoinsert, 2);
                  zfinished = true;
                }

                gcodenumber = gcodenumber + 1;
                zexecutionnumber = zexecutionnumber + 1;
              }
              firstletter = commanding.substring(gcodenumber, gcodenumber + 1);
            }

            // IF IT IS A "E", DETERMINE NUMBER OF CHARACTERS, THEN SAVE TO DB ARRAY
            if (firstletter == "E") {
              int startedigit = gcodenumber + 1;
              gcodenumber = gcodenumber + 1;
              int finaledigit = 0;
              bool efinished = false;
              int eexecutionnumber = 0;

              while (efinished != true && eexecutionnumber <= 10) {
                // DETERMINE THE NEXT CHARACTER IN THE STRING
                firstletter = commanding.substring(gcodenumber, gcodenumber + 1);

                // WAIT UNTIL CHARACTER RECEIVED IS A " ", THEN END THIS WHILE LOOP
                if (firstletter == " " || firstletter == "") {
                  String evalues = commanding.substring(startedigit, gcodenumber);
                  float evaluestoinsert = evalues.toFloat();
                  sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, evaluestoinsert, 3);
                  efinished = true;
                }

                gcodenumber = gcodenumber + 1;
                eexecutionnumber = eexecutionnumber + 1;
              }
              firstletter = commanding.substring(gcodenumber, gcodenumber + 1);
            }

            // IF IT IS A "E", DETERMINE NUMBER OF CHARACTERS, THEN SAVE TO DB ARRAY
            if (firstletter == "F") {
              // FEEDRATE VARIABLES
              gcodecomplete = true;
              Serial.println(F("ok"));
            }

            // TIME UP VARIABLES
            gcodenumber = gcodenumber + 1;
            executionnumber = executionnumber + 1;
          }

          sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, 1, 10);

          interpretedcompleted = true;
        }
      }
    }

    if (firstletter == "2") {

      // DETERINE THE THIRD LETTER OF THE SCRIPT
      firstletter = commanding.substring(2, 3);

      // G2 - CONTROLLED ARC MOVE COUNTER CLOCKWISE (NOT SUPPORTED)
      if (firstletter == " ") {
        Serial.println(F("error"));
        Serial.println(F("CONTROLLED ARC MOVE NOT SUPPORTED"));
      }

      // G20 - SET UNITS TO INCHES (NOT SUPPORTED)
      if (firstletter == "0") {
        Serial.println(F("ok"));
        interpretedcompleted = true;
        return (0);
      }

      // G21 - SET UNITS TO MM (NOT SUPPORTED)
      if (firstletter == "1") {
        Serial.println(F("ok"));
        interpretedcompleted = true;
        return (0);
      }

      // G22 - DO A RETRACTION MOVE AUTOMATICALLY (NOT SUPPORTED)
      if (firstletter == "2") {
        Serial.println(F("ok"));
        interpretedcompleted = true;
        return (0);
      }

      // G23 - FIRMWARE RECOVER MOVE
      if (firstletter == "3") {
        maintenance();
        lcdEngine();
        Serial.println(F("ok"));
        interpretedcompleted = true;
        return (0);
      }

      // G27 - PARK TOOLHEAD
      if (firstletter == "7") {
        xhome();
        yhome();
        Serial.println(F("ok"));
        interpretedcompleted = true;
        return (0);
      }

      // G28 - MOVE TO HOME
      if (firstletter == "8") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // IF " ", THEN ONLY HOME THE SELECTED AXIS, OTHERWISE, HOME ALL
        if (firstletter == " ") {

          // DETERMINE THE FIFTH LETTER OF THE STRING
          firstletter = commanding.substring(4, 5);

          if (firstletter == "X") {
            xhome();
          }
          if (firstletter == "Y") {
            yhome();
          }
          if (firstletter == "Z") {
            zhome();
          }
          Serial.println(F("ok"));
          interpretedcompleted = true;
          return (0);
        } else {
          homeall();
          Serial.println(F("ok"));
          interpretedcompleted = true;
          return (0);
        }
      }
    }

    if (firstletter == "3") {
    }

    if (firstletter == "4") {
    }

    if (firstletter == "5") {
    }

    if (firstletter == "6") {
    }

    if (firstletter == "7") {
    }

    if (firstletter == "8") {
    }

    if (firstletter == "9") {
    }
  }

  // IF COMMAND STARTS WITH M, EVALUATE WHAT IT ACTUALLY MEANS
  if (firstletter == "M") {
    mShell(commanding);
  }

  if (firstletter == "T") {
    String actively21 = commanding.substring(1, 2);
    currentactiveextruder = actively21.toInt();
    Serial.println(F("ok"));
    return;
    return;
    return;
  }
}