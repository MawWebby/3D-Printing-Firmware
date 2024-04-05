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

  Serial.println(F("started"));
  lcd.clear();
  delay(1);
  lcdEngine();
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

    // DELAY FOR 60 SECONDS
    delay(60000);
    return;
    return;
    return;
    return;
  }

  // LOOPS TO FIRE
  serialReceiver();  // SERIAL RECEIVE LOOP
  realtimeclock();   // REAL TIME CLOCK IN MILLIS

  // ONLY CALL MOVEMENT/TEMPERATURE LOOP IF PRINTER IS ACTIVE AND SITTING IDLE
  if (printingactive == true && currentlylocked != true) {
    movement();  // STEPPER MOTOR MICROSTEP LOOP
  } else {
    delay(1);
  }

  // TEMP SENSING EVERY ONE-HUNDRED LOOPS
  if (tempsensingruntime == 250) {
    tempsensingruntime = 0;
    maintenance();      // MAINTENANCE LOOP
    litetempsensing();  // TEMPERATURE SENSING LOOP
    alerttimeclock();   // ALERT TIME CLOCK
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
