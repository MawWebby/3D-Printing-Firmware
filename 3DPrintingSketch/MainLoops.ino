// SETUP LOOP
void setup() {

  ////////////////////////////////
  // BEGIN SERIAL COMMUNICATION //
  ////////////////////////////////
  Serial.begin(115200);



  ///////////////////////////
  // DELAY 10 MILLISECONDS //
  ///////////////////////////
  delay(10);
  Serial.println(F("start"));



  ///////////////////////
  // START LCD DISPLAY //
  ///////////////////////
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.print("starting...");



  //////////////////////////
  /// SETUP I2C PROTOCOL ///
  //////////////////////////
  Wire.begin(MASTERADDRESS);
  Wire.onReceive(i2creceive);



  /////////////////////////////////////
  /// ALLOCATE MEMORY GCODE CACHING ///
  /////////////////////////////////////
  inputString.reserve(200);
  gcodestack0.reserve(200);
  gcodestack1.reserve(200);
  gcodestack2.reserve(200);
  gcodestack3.reserve(200);
  gcodestack4.reserve(200);
  gcodestack5.reserve(200);
  gcodestack6.reserve(200);
  gcodestack7.reserve(200);
  gcodestack8.reserve(200);
  gcodestack9.reserve(200);
  gcodestack10.reserve(200);



  /////////////////////////////////////
  /// ALLOCATE MEMORY ERROR CACHING ///
  /////////////////////////////////////
  errorstack0.reserve(100);
  errorstack1.reserve(100);
  errorstack2.reserve(100);
  errorstack3.reserve(100);
  errorstack4.reserve(100);
  errorstack5.reserve(100);
  errorstack6.reserve(100);
  errorstack7.reserve(100);
  errorstack8.reserve(100);
  errorstack9.reserve(100);
  errorstack10.reserve(100);



  //////////////////////////////////
  // SET DIGITAL PINMODE OUTPUTS ///
  //////////////////////////////////
  pinMode(ledpin, OUTPUT);         // PIN MODE FOR LEDPIN
  pinMode(X_STEP_PIN, OUTPUT);     // SET X-AXIS MOTOR PINMODE OUTPUTS
  pinMode(X_DIR_PIN, OUTPUT);      // SET X-AXIS MOTOR PINMODE OUTPUTS
  pinMode(X_ENABLE_PIN, OUTPUT);   // SET X-AXIS MOTOR PINMODE OUTPUTS
  pinMode(Y_STEP_PIN, OUTPUT);     // SET Y-AXIS MOTOR PINMODE OUTPUTS
  pinMode(Y_DIR_PIN, OUTPUT);      // SET Y-AXIS MOTOR PINMODE OUTPUTS
  pinMode(Y_ENABLE_PIN, OUTPUT);   // SET Y-AXIS MOTOR PINMODE OUTPUTS
  pinMode(Z_STEP_PIN, OUTPUT);     // SET Z-AXIS MOTOR PINMODE OUTPUTS
  pinMode(Z_DIR_PIN, OUTPUT);      // SET Z-AXIS MOTOR PINMODE OUTPUTS
  pinMode(Z_ENABLE_PIN, OUTPUT);   // SET Z-AXIS MOTOR PINMODE OUTPUTS
  pinMode(E_STEP_PIN, OUTPUT);     // SET E0 MOTOR PINMODE OUTPUTS
  pinMode(E_DIR_PIN, OUTPUT);      // SET E0 MOTOR PINMODE OUTPUTS
  pinMode(E_ENABLE_PIN, OUTPUT);   // SET E0 MOTOR PINMODE OUTPUTS
  pinMode(E1_STEP_PIN, OUTPUT);    // SET E1 MOTOR PINMODE OUTPUTS
  pinMode(E1_DIR_PIN, OUTPUT);     // SET E1 MOTOR PINMODE OUTPUTS
  pinMode(E1_ENABLE_PIN, OUTPUT);  // SET E1 MOTOR PINMODE OUTPUTS
  pinMode(HEATER_0_PIN, OUTPUT);   // SET HEATER MOTOR PINMODE OUTPUTS
  pinMode(HEATER_1_PIN, OUTPUT);   // SET HEATER MOTOR PINMODE OUTPUTS
  pinMode(X_MIN_PIN, INPUT);       // ENDSTOPS PINMODE INPUT
  pinMode(Y_MIN_PIN, INPUT);       // ENDSTOPS PINMODE INPUT
  pinMode(Z_MIN_PIN, INPUT);       // ENDSTOPS PINMODE INPUT
  pinMode(TEMP_0_PIN, INPUT);      // ANALOG TEMPERATURE INPUTS
  pinMode(TEMP_1_PIN, INPUT);      // ANALOG TEMPERATURE INPUTS
  pinMode(FAN_PIN, OUTPUT);        // SETUP FAN ON EXTRUDER
  pinMode(PS_ON_PIN, OUTPUT);      // SETUP PINMODE FOR POWER SUPPLY



  ///////////////////////////////////////
  //// GCODE/SERIAL STARTUP COMMANDS ////
  ///////////////////////////////////////
  Serial.println(F("0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000"));
  Serial.println(F("SD init fail"));
  Serial.println(F("ok"));



  //////////////////////////////////
  // SET ALL PINS TO LOW AT START //
  //////////////////////////////////
  digitalWrite(X_ENABLE_PIN, HIGH);
  digitalWrite(Y_ENABLE_PIN, HIGH);
  digitalWrite(Z_ENABLE_PIN, HIGH);
  digitalWrite(E_ENABLE_PIN, HIGH);
  digitalWrite(E1_ENABLE_PIN, HIGH);
  digitalWrite(ledpin, LOW);
  digitalWrite(X_STEP_PIN, LOW);
  digitalWrite(X_DIR_PIN, LOW);
  digitalWrite(Y_STEP_PIN, LOW);
  digitalWrite(Y_DIR_PIN, LOW);
  digitalWrite(Z_STEP_PIN, LOW);
  digitalWrite(Z_DIR_PIN, LOW);
  digitalWrite(E_STEP_PIN, LOW);
  digitalWrite(E_DIR_PIN, LOW);
  digitalWrite(E1_STEP_PIN, LOW);
  digitalWrite(E1_DIR_PIN, LOW);
  digitalWrite(HEATER_0_PIN, LOW);
  digitalWrite(HEATER_1_PIN, LOW);
  digitalWrite(FAN_PIN, LOW);
  digitalWrite(PS_ON_PIN, LOW);


  /////////////////////////////////////////////
  // FIRMWARE CHECKS AND DATABASE MIGRATIONS //
  /////////////////////////////////////////////
  bool olderversion = false;
  bool newerversion = false;
  bool versionmatchmajor = false;
  bool versionmatchminor = false;
  watchdogactivated = true;

  // EEPROM-9 - FIRMWARE MAJOR VERSION
  if (EEPROM.read(9) << MAJORVERSION) {
    Serial.println(F("OLDER VERSION DETECTED"));
    olderversion = true;
  } else {
    if (EEPROM.read(9) >> MAJORVERSION) {
      Serial.println(F("NEWER VERSION DETECTED"));
      newerversion = false;
    } else {
      if (EEPROM.read(9) == MAJORVERSION) {
        versionmatchmajor = true;
      } else {
        Serial.println(F("EEPROM-9 NOT SET/CONFIGURING"));
        delay(3000);
        EEPROM.update(9, MAJORVERSION);
        delay(3000);
        Serial.println(F("RESTARTING"));
        setup();
      }
    }
  }

  // EEPROM-10 - FIRMWARE MINOR VERSION
  if (EEPROM.read(10) << MINORVERSION) {
    Serial.println(F("OLDER VERSION DETECTED"));
    if (newerversion == false && olderversion == false) {
      olderversion = true;
    }
  } else {
    if (EEPROM.read(10) >> MINORVERSION) {
      Serial.println(F("NEWER VERSION DETECTED"));
      if (newerversion == false && olderversion == false) {
        newerversion = false;
      }
    } else {
      if (EEPROM.read(10) == MINORVERSION) {
        versionmatchminor = true;
      } else {
        Serial.println(F("EEPROM-10 NOT SET/CONFIGURING"));
        delay(3000);
        EEPROM.update(10, MINORVERSION);
        delay(3000);
        Serial.println(F("restarting"));
        setup();
      }
    }
  }

  // IF VERSION MATCH IS TRUE, CONTINUE; ELSE RECONFIGURE
  if (versionmatchmajor == true && versionmatchminor == true) {
    watchdogactivated = true;
  } else {

    // OLDER VERSION IS TRUE
    if (olderversion == true) {
      if (allowolderversions == true) {
        watchdogactivated = true;
        if (EEPROM.read(9) == 255 || EEPROM.read(10) == 255) {
          Serial.println(F("OLDER VERSIONS ARE NOT SUPPORTED, RESETTING DATABASE AND RESTARTING"));

          // PUT SPECIFIC INFORMATION HEAR
          if (MAJORVERSION == 0) {
            if (MINORVERSION == 1 || MINORVERSION == 2 || MINORVERSION == 3) {

              int reseteeprom = 0;
              while (reseteeprom <= 30) {
                if (reseteeprom == 9) {
                  EEPROM.update(9, MAJORVERSION);
                } else {
                  if (reseteeprom == 10) {
                    EEPROM.update(10, MINORVERSION);
                  } else {
                    EEPROM.update(reseteeprom, 0);
                  }
                }
                reseteeprom = reseteeprom + 1;
                delay(2500);
              }

              delay(3000);
              Serial.println(F("RESTARTING!"));
              delay(1000);
              setup();
            }
          }
        }
      }
    }

    // NEWER VERSION IS TRUE
    if (newerversion == true) {
      Serial.println(F("NEW VERSION DETECTED"));
      delay(3000);

      // VERSION 0.X - NO DB UPRGADE REQUIRED/UPGRADE EEPROM VALUES
      if (EEPROM.read(9) == 0) {
        if (EEPROM.read(10) == 2) {
          Serial.print(F("allocating new storage..."));
          delay(1000);
          EEPROM.update(15, 0);
          delay(1000);
          EEPROM.update(16, 0);
          delay(1000);
          EEPROM.update(17, 0);
          delay(1000);
          EEPROM.update(18, 0);
          delay(1000);
          EEPROM.update(19, 0);
          delay(1000);
          EEPROM.update(20, 0);
          Serial.println(F("done"));
          delay(4000);
          Serial.print(F("configuring new values..."));

          // ADD MORE HERE LATER

          Serial.println(F("done"));

          delay(1000);

          Serial.print(F("finishing upgrade scripts (0.3)..."));

          delay(1000);

          Serial.println(F("done"));

          delay(1000);

          setup();

        } else {
          Serial.print(F("running upgrade scripts (0.2)..."));
          EEPROM.update(9, MAJORVERSION);
          delay(1000);
          EEPROM.update(10, MINORVERSION);
          delay(1000);
          Serial.println(F("done"));
          delay(1000);
          Serial.println(F("restarting"));
          setup();
        }
      }
    }
  }


  //////////////////////////////////////////////////////////////
  //// READ THE INITIAL STATE OF THE ENDSTOPS AND EXTRUDERS ////
  //////////////////////////////////////////////////////////////
  delay(500);
  xendsetup = digitalRead(X_MIN_PIN);
  yendsetup = digitalRead(Y_MIN_PIN);
  zendsetup = digitalRead(Z_MIN_PIN);
  anae0read = analogRead(TEMP_0_PIN);
  anahbread = analogRead(TEMP_HB_PIN);



  /////////////////////////////////////
  // DO A FRESH WIPE OF MASTER ARRAY //
  /////////////////////////////////////
  clearrowinarray(0, true);
  clearrowinarray(1, true);
  clearrowinarray(2, true);
  clearrowinarray(3, true);
  clearrowinarray(4, true);
  clearrowinarray(5, true);
  clearrowinarray(6, true);
  clearrowinarray(7, true);
  clearrowinarray(8, true);
  clearrowinarray(9, true);
  clearrowinarray(10, true);



  /////////////////////////////////////
  // DO A FRESH WIPE OF MASTER ARRAY //
  /////////////////////////////////////
  clearerrorsstackloop(0);
  clearerrorsstackloop(1);
  clearerrorsstackloop(2);
  clearerrorsstackloop(3);
  clearerrorsstackloop(4);
  clearerrorsstackloop(5);
  clearerrorsstackloop(6);
  clearerrorsstackloop(7);
  clearerrorsstackloop(8);
  clearerrorsstackloop(9);
  clearerrorsstackloop(10);



  //////////////////////////////
  // FINISH LCD STARTUP TASKS //
  //////////////////////////////
  {
    byte smiley[8] = {
      B00000,
      B10001,
      B00000,
      B00000,
      B10001,
      B01110,
      B00000,
    };
    byte coldbed[8] = {
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B11111,
    };
    byte hotbed1[8] = {
      B10010,
      B01001,
      B01001,
      B10010,
      B01001,
      B00000,
      B11111,
    };
    byte hotbed2[8] = {
      B01001,
      B10010,
      B10010,
      B01001,
      B10010,
      B00000,
      B11111,
    };
    byte extrudercold[8] = {
      B11111,
      B10001,
      B10001,
      B10001,
      B10001,
      B01010,
      B00100,
    };
    byte extruderhot1[8] = {
      B11111,
      B11001,
      B10101,
      B11001,
      B10101,
      B01010,
      B00100,
    };
    byte extruderhot2[8] = {
      B11111,
      B10101,
      B11001,
      B10101,
      B11001,
      B01010,
      B00100,
    };
    byte fan567[8] = {
      B11111,
      B11011,
      B10101,
      B11111,
      B10101,
      B11011,
      B11111,
    };

    // CREATE CHARACTERS
    lcd.createChar(0, smiley);
    lcd.createChar(1, coldbed);
    lcd.createChar(2, hotbed1);
    lcd.createChar(3, hotbed2);
    lcd.createChar(4, extrudercold);
    lcd.createChar(5, extruderhot1);
    lcd.createChar(6, extruderhot2);
    lcd.createChar(7, fan567);
  }



  //////////////////////////////
  // SETUP EEPROM WITH VALUES //
  //////////////////////////////
  {
    // EEPROM-1 - Debug Serial
    if (EEPROM.read(1) == 1) {

      // IF RESTART EEPROM EQUAL 1, THEN SET Debug EQUAL TO TRUE
      debugserial = true;
      Serial.println(F(""));
      Serial.println(F("Debug Serial (EEPROM-1)"));
    } else {
      if (EEPROM.read(1) != 0) {

        // Debug Serial VARIABLE NOT SET, SETTING AND RESTARTING
        Serial.println(F("SETTING EEPROM-1"));
        delay(3000);
        EEPROM.update(1, 0);
        delay(3000);
        Serial.println(F("restart"));
        delay(500);
        setup();
      }
    }

    // EEPROM-2 - RESTART FROM POWER LOSS
    if (EEPROM.read(2) == 1) {

      // IF RESTART EEPROM EQUAL 1, THEN SET Printer Active EQUAL TO TRUE
      printingactive = true;
      Serial.println(F(""));
      Serial.println(F("Printer Active (EEPROM-2)"));
    } else {
      if (EEPROM.read(2) != 0) {

        // Printer Active VARIABLE NOT SET, SETTING AND RESTARTING
        Serial.println(F("SETTING EEPROM-2"));
        delay(3000);
        EEPROM.update(2, 0);
        delay(3000);
        Serial.println(F("restart"));
        delay(500);
        setup();
      }
    }

    // EEPROM-3 - CURRENTLY LOCKED
    if (EEPROM.read(3) == 1) {

      // IF RESTART EEPROM EQUAL 1, THEN SET CURRENTLYLOCKED EQUAL TO TRUE
      currentlylocked = true;
      Serial.println(F("locked"));
      Serial.println(F("LOCKED (EEPROM-3)"));
    } else {
      if (EEPROM.read(3) != 0) {

        // CURRENTLY LOCKED VARIABLE NOT SET, SETTING AND RESTARTING
        Serial.println(F("SETTING EEPROM-3"));
        delay(3000);
        EEPROM.update(3, 0);
        delay(3000);
        Serial.println(F("restart"));
        delay(500);
        setup();
      }
    }

    // CHECK FOR 0 VALUES, OTHERWISE, CREATE QUICK SYSTEM REPORT OVER SERIAL
    bool failedsystemcheckcomplete = false;

    // EEPROM-4 - WATCHDOG ERRORS
    if (EEPROM.read(4) != 0) {
      failedsystemcheckcomplete = true;
    }

    // EEPROM-5 - TEMPERATURE ERRORS
    if (EEPROM.read(5) != 0) {
      failedsystemcheckcomplete = true;
    }

    // EEPROM-6 - G-PARSER ERRORS
    if (EEPROM.read(6) != 0) {
      failedsystemcheckcomplete = true;
    }

    // EEPROM-7 - M-PARSER ERRORS
    if (EEPROM.read(7) != 0) {
      failedsystemcheckcomplete = true;
    }

    // EEPROM-8 - MOVEMENT ERRORS
    if (EEPROM.read(8) != 0) {
      failedsystemcheckcomplete = true;
    }

    if (skipsystemcheck == true) {
      Serial.println(F("SKIPPING SYSTEM CHECK!"));
      delay(100);
    } else {
      if (failedsystemcheckcomplete == true && watchdogactivated == false) {
        quickprint();
      }
    }



    // EEPROM-11 - SUCCESS PRINTS (256)
    if (EEPROM.read(11) == "") {
      Serial.println(F("EEPROM-11 NOT SET - CONFIGURING"));
      delay(3000);
      EEPROM.update(11, 0);
      delay(3000);
      Serial.println(F("restarting"));
      setup();
    }


    // EEPROM-12 - SUCCESS PRINTS (1)
    if (EEPROM.read(12) == "") {
      Serial.println(F("EEPROM-12 NOT SET - CONFIGURING"));
      delay(3000);
      EEPROM.update(12, 0);
      delay(3000);
      Serial.println(F("restarting"));
      setup();
    }


    // EEPROM-13 - BAD PRINTS (256)
    if (EEPROM.read(13) == "") {
      Serial.println(F("EEPROM-13 NOT SET - CONFIGURING"));
      delay(3000);
      EEPROM.update(13, 0);
      delay(3000);
      Serial.println(F("restarting"));
      setup();
    }


    // EEPROM-14 - BAD PRINTS (1)
    if (EEPROM.read(14) == "") {
      Serial.println(F("EEPROM-14 NOT SET - CONFIGURING"));
      delay(3000);
      EEPROM.update(14, 0);
      delay(3000);
      Serial.println(F("restarting"));
      setup();
    }
  }


  Serial.println(F("started"));
  lcd.clear();
  delay(1);
  lcdEngine();

  // EEPROM-0 - WATCHDOG CONTINUING THROUGH REBOOT
  if (EEPROM.read(0) == 1) {

    // IF WATCHDOG EEPROM EQUAL 1, THEN SET WATCHDOG ACTIVATED EQUAL TO TRUE
    watchdogactivated = true;
    Serial.println(F("error"));
    Serial.println(F("WATCHDOG LOCK! (EEPROM-0)"));
    EEPROM.update(0, 1);

  } else {
    if (EEPROM.read(0) != 0) {

      // WATCHDOG VARIABLE NOT SET, SETTING AND RESTARTING
      Serial.println(F("SETTING EEPROM-0"));
      delay(3000);
      EEPROM.update(0, 0);
      delay(3000);
      Serial.println(F("restart"));
      delay(500);
      setup();
    } else {
      watchdogactivated = false;
    }
  }

  watchdogactivated = false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

// MAIN LOOP
void loop() {
  // IF WATCHDOG ACTIVATED EQUALS TO TRUE, THEN DON'T FIRE REST OF LOOP
  if (watchdogactivated == true) {

    // SEND SERIAL WARNING OF CURRENT STATE
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println(F("WATCHDOG ACTIVATED = TRUE!"));
    Serial.println(F("THIS WILL PREVENT THE PRINTER FROM CONTINUING!"));
    Serial.println();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F("WATCHDOG ACTIVATED"));

    // SETTING ALL PINS TO LOW
    digitalWrite(ledpin, LOW);
    digitalWrite(X_STEP_PIN, LOW);
    digitalWrite(X_DIR_PIN, LOW);
    digitalWrite(X_ENABLE_PIN, HIGH);
    digitalWrite(Y_STEP_PIN, LOW);
    digitalWrite(Y_DIR_PIN, LOW);
    digitalWrite(Y_ENABLE_PIN, HIGH);
    digitalWrite(Z_STEP_PIN, LOW);
    digitalWrite(Z_DIR_PIN, LOW);
    digitalWrite(Z_ENABLE_PIN, HIGH);
    digitalWrite(E_STEP_PIN, LOW);
    digitalWrite(E_DIR_PIN, LOW);
    digitalWrite(E_ENABLE_PIN, HIGH);
    digitalWrite(E1_STEP_PIN, LOW);
    digitalWrite(E1_DIR_PIN, LOW);
    digitalWrite(E1_ENABLE_PIN, HIGH);
    digitalWrite(HEATER_0_PIN, LOW);
    digitalWrite(HEATER_1_PIN, LOW);
    digitalWrite(FAN_PIN, LOW);
    digitalWrite(PS_ON_PIN, LOW);

    // SET UPDATED FLAG IN EEPROM FOR WATCHDOG!
    if (EEPROM.read(0) != 1) {
      EEPROM.update(0, 1);
    }

    // DELAY FOR 0.5 Seconds
    delay(500);

    // START 3RD SERIAL RECEIVER
    watchdogserialReceiver();

  } else {

    // LOOPS TO FIRE
    serialReceiver();  // SERIAL RECEIVE LOOP
    realtimeclock();   // REAL TIME CLOCK IN MILLIS

    // ONLY CALL MOVEMENT/TEMPERATURE LOOP IF PRINTER IS ACTIVE AND SITTING IDLE
    if (printingactive == true && currentlylocked != true) {
      movement();  // STEPPER MOTOR MICROSTEP LOOP
    } else {
      tempsensing();
      lcdEngine();
    }

    // TEMP SENSING EVERY ONE-HUNDRED LOOPS
    if (tempsensingruntime == 250) {
      tempsensingruntime = 0;
      maintenance();      // MAINTENANCE LOOP
      litetempsensing();  // TEMPERATURE SENSING LOOP
      alerttimeclock();   // ALERT TIME CLOCK
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

// I2C SEND LOOP
void i2csend(String i2cDEBUG, String i2cLCD, String i2cSD, int override) {
  // DEBUG SENDING IF I2C STRING IS NOT EMPTY

  // NO OVERRIDE/NORMAL OPERATION
  if (override == 0) {
    if (debugserial == false) {
      // I2C DEBUG LOOP
      if (i2cDEBUG != "") {
        Wire.beginTransmission(DEBUGARDUINO);
        Wire.write(i2cDEBUG.c_str());
        Wire.endTransmission();
        i2cDEBUG = "";
      }

      // I2C LCD LOOP
      if (i2cLCD != "") {
        Wire.beginTransmission(LCDARDUINO);
        Wire.write(i2cLCD.c_str());
        Wire.endTransmission();
        i2cLCD = "";
      }

      // I2C SD LOOP
      if (i2cSD != "") {
        Wire.beginTransmission(SDARDUINO);
        Wire.write(i2cSD.c_str());
        Wire.endTransmission();
        i2cSD = "";
      }
      return;
      return;
    }
    if (debugserial == true) {
      Serial.println(i2cDEBUG);
      return;
      return;
    }
  }

  // I2C OVERRIDE TO SERIAL DEBUG ANYWAY
  if (override == 1) {
    Serial.println(i2cDEBUG);
  }

  // SEND TO I2C ANYWAY REGARDLESS OF OVERRIDE
  if (override == 2) {
    if (i2cDEBUG != "") {
      Wire.beginTransmission(DEBUGARDUINO);
      Wire.write(i2cDEBUG.c_str());
      Wire.endTransmission();
      i2cDEBUG = "";
    }

    // I2C LCD LOOP
    if (i2cLCD != "") {
      Wire.beginTransmission(LCDARDUINO);
      Wire.write(i2cLCD.c_str());
      Wire.endTransmission();
      i2cLCD = "";
    }

    // I2C SD LOOP
    if (i2cSD != "") {
      Wire.beginTransmission(SDARDUINO);
      Wire.write(i2cSD.c_str());
      Wire.endTransmission();
      i2cSD = "";
    }
    return;
    return;
  }
}

// I2C RECEIVE LOOP
void i2creceive() {
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

// SERIAL INFORMATION
void serialReceiver() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    } else {
      receivedChars[ndx] = '\0';  // terminate the string
      ndx = 0;
      newData = true;
      receivedSerial3000 = receivedChars;
      int working = interpretation(receivedSerial3000);
      //if (working != 0 && working != 2) {
      //  Serial.println(F("GCODE COMMAND NOT RECOGNIZED!"));
      //}
      // if working == 2, then no args were passed
      // if working == 0, the command was initiated successfully
      newData = false;
      receivedSerial3000 = "";
      receivedChars == "";
    }
  }
}

// EMERGENCY SERIAL RECEIVER
void eSERIALRECEIVER() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    } else {
      receivedChars[ndx] = '\0';  // terminate the string
      ndx = 0;
      newData = true;
      receivedSerial3000 = receivedChars;
      ePARSER(receivedSerial3000);
      newData = false;
      receivedSerial3000 = "";
      receivedChars == "";
    }
  }
}

// WATCHDOG SERIAL INFORMATION
void watchdogserialReceiver() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    } else {
      receivedChars[ndx] = '\0';  // terminate the string
      ndx = 0;
      newData = true;
      receivedSerial3000 = receivedChars;
      int working = watchdoginterpretation(receivedSerial3000);
      //if (working != 0 && working != 2) {
      //  Serial.println(F("GCODE COMMAND NOT RECOGNIZED!"));
      //}
      // if working == 2, then no args were passed
      // if working == 0, the command was initiated successfully
      newData = false;
      receivedSerial3000 = "";
      receivedChars == "";
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

// CLEAR AND MOVE ON TO NEW GCODE COMMAND
void movetonewgcode(int commandtoanalyze) {
  if (currentxdimension == targetxdimension || currentydimension == targetydimension) {
    // ASSUME COMMAND IS DONE AND MOVE TO NEW COMMAND
    switch (commandtoanalyze) {
      case 0:
        clearrowinarray(0, true);
        currentgcodecommand = 1;
        currentlycachedgcodes = -1;
        break;
      case 1:
        clearrowinarray(1, true);
        currentgcodecommand = 2;
        currentlycachedgcodes = -1;
        break;
      case 2:
        clearrowinarray(2, true);
        currentgcodecommand = 3;
        currentlycachedgcodes = -1;
        break;
      case 3:
        clearrowinarray(3, true);
        currentgcodecommand = 4;
        currentlycachedgcodes = -1;
        break;
      case 4:
        clearrowinarray(4, true);
        currentgcodecommand = 5;
        currentlycachedgcodes = -1;
        break;
      case 5:
        clearrowinarray(5, true);
        currentgcodecommand = 6;
        currentlycachedgcodes = -1;
        break;
      case 6:
        clearrowinarray(6, true);
        currentgcodecommand = 7;
        currentlycachedgcodes = -1;
        break;
      case 7:
        clearrowinarray(7, true);
        currentgcodecommand = 8;
        currentlycachedgcodes = -1;
        break;
      case 8:
        clearrowinarray(8, true);
        currentgcodecommand = 9;
        currentlycachedgcodes = -1;
        break;
      case 9:
        clearrowinarray(9, true);
        currentgcodecommand = 10;
        currentlycachedgcodes = -1;
        break;
      case 10:
        clearrowinarray(10, true);
        currentgcodecommand = 0;
        currentlycachedgcodes = -1;
        break;
    }
  }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

// RESTART THE CONTROLLER
void unsetup() {
  Serial.println(F("RESETTING 3D PRINTER!"));
  Serial.println(F("..."));

  delay(1000);

  Serial.end();

  delay(1000);

  digitalWrite(ledpin, LOW);

  delay(1000);

  setup();
}
