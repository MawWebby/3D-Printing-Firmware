/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

// TEMP SENSING LOOP
void litetempsensing() {

  currente0temp = analogRead(TEMP_0_PIN);
  currente1temp = analogRead(TEMP_1_PIN);
  currenthbtemp = analogRead(TEMP_HB_PIN);

  // DEGREES CELSIUS
  currente0temp = e0tempmodifier * (1023 - currente0temp);
  currente1temp = e1tempmodifier * (1023 - currente1temp);
  currenthbtemp = hbtempmodifier * (1023 - currenthbtemp);
  currenthbtemp = currente1temp;

  //  tempchange();
  //  hbtempchange();

  if (currente0temp >= targete0temp - 10) {
    digitalWrite(HEATER_0_PIN, LOW);
  }

  if (currenthbtemp >= targethbtemp - 4) {
    digitalWrite(HEATER_HB_PIN, LOW);
  }
}

void tempsensing() {
  float rawsensore0 = 00.000;
  float rawsensore1 = 00.000;
  float rawsensorhb = 00.000;

  int testaway = 0;

  while (testaway <= 10) {
    testaway = testaway + 1;
    rawsensore0 = rawsensore0 + analogRead(TEMP_0_PIN);
    rawsensore1 = rawsensore1 + analogRead(TEMP_1_PIN);
    rawsensorhb = rawsensorhb + analogRead(TEMP_HB_PIN);
  }

  rawsensore0 = rawsensore0 / 10;
  rawsensore1 = rawsensore1 / 10;
  rawsensorhb = rawsensorhb / 10;

  // DEGREES CELSIUS
  currente0temp = e0tempmodifier * (1023 - rawsensore0);
  currente1temp = e1tempmodifier * (1023 - rawsensore1);
  currenthbtemp = hbtempmodifier * (1023 - rawsensorhb);
  currenthbtemp = currente1temp;

  if (simulationmode == false) {
    tempchange();
    hbtempchange();
  } else {
    digitalWrite(HEATER_0_PIN, LOW);
    digitalWrite(HEATER_1_PIN, LOW);
    digitalWrite(HEATER_HB_PIN, LOW);
  }
}

// TEMP CHANGING EXTRUDER LOOP
void tempchange() {
  // CHANGE HOTEND PINS IF THE TEMPERATURE IS LOWER THAN TARGET


  // E0 ACTIVATION LOOP
  if (e0on == false) {

    if (currente0temp == 0) {
      digitalWrite(HEATER_0_PIN, LOW);
      return;
    }

    // CURRENT E0 TEMP IS SUFFICIENT FOR TARGET TEMPEARTURE
    if (currente0temp >= targete0temp) {
      digitalWrite(HEATER_0_PIN, LOW);
      return (0);
      if (printingactive == true || targete0temp >= 150) {
        if (currente0temp + 5 >= targete0temp) {
          digitalWrite(HEATER_0_PIN, HIGH);
        }
      }
    }

    // CURRENT E0 TEMP IS LESS THAN TARGET TEMPERATURE
    if (currente0temp < targete0temp) {
      // SET EXTRUDER TIMEOUT START VARIABLE
      startextrudertimeout = millis();

      // RUN THROUGH VARIOUS USE CASES FOR EXTRUDER
      {
        // EXTRUDER IS WITHIN 10 OF TARGET TEMP IN CELSIUS
        if (currente0temp + 10 > targete0temp) {
          Serial.println(F("within 10 - pin high for 5 seconds"));
          digitalWrite(HEATER_0_PIN, HIGH);
          e0ontime = 5;
          return (1);
        }

        // EXTRUDER IS WITHIN 30 OF TARGET TEMP IN CELSIUS
        if (currente0temp + 30 > targete0temp) {
          Serial.println(F("within 30 - pin high for 9 seconds"));
          digitalWrite(HEATER_0_PIN, HIGH);
          e0ontime = 9;
          return (1);
        }

        // EXTRUDER IS WITHIN 50 OF TARGET TEMP IN CELSIUS
        if (currente0temp + 50 > targete0temp) {
          Serial.println(F("within 50 - pin high for 12 seconds"));
          digitalWrite(HEATER_0_PIN, HIGH);
          e0ontime = 12;
          return (1);
        }

        // EXTRUDER IS BEYOND THIS POINT
        Serial.println(F("beyond 50 - settings to reach -30"));
        digitalWrite(HEATER_0_PIN, HIGH);
        e0ontime = 300;
        e0max = true;
        return (1);
      }
    }


  } else {
    unsigned long long int currentextrudertimeout2 = micros();
    unsigned long long int differenceintime = currentextrudertimeout2 - startextrudertimeout;
    currentextrudertimer = differenceintime / 1000;

    // IF E0ONTIME = 300, THEN WAIT TILL THE XTRUDER IS WITHIN 30 AND THEN SET TO LOW
    if (e0ontime == 300) {
      if (currente0temp + 30 >= targete0temp) {
        e0max = true;
        digitalWrite(HEATER_0_PIN, LOW);
        Serial.println(F("REACHED SUFFICIENT TEMPERATURE!"));
        return (0);
      }
    }

    // IF E0ONTIME IS LESS THAN CURRENT EXTRUDER TIMER, PROCEED WITH EXTRUDER PIN HIGH
    if (e0ontime > currentextrudertimer) {
      digitalWrite(HEATER_0_PIN, HIGH);
      Serial.println(F("PIN ON"));
      return (1);
    }

    // IF E0ONTIME IS GREATER THAN CURRENT EXTRUDER TIMER, THEN TURN OFF EXTRUDER AND REMOVE VARIABLES TO PREVENT WATCHDOG ACTIVATION
    if (e0ontime <= currentextrudertimer) {
      digitalWrite(HEATER_0_PIN, LOW);
      Serial.println(F("PIN OFF"));
      e0ontime = 0;
      e0on = false;
      currentextrudertimer = 0;
      currentextrudertimeout2 = 0;
      differenceintime = 0;
      currentextrudertimer = 0;
      startextrudertimeout = 0;
      return (0);
    }

    // CURRENT EXTRUDER TIMEOUT (TEMP WATCHDOG)(THERMAL PROTECTION)
    if (currentextrudertimer >= extrudertimeout) {
      Serial.println(F("ERROR! - EXTRUDER HAS BEEN ON FOR WAY TOO LONG!"));
      Serial.println(F("TURNING OFF PRINTER!"));
      watchdogactivated = true;
      return (3);
    }
  }
  //  digitalWrite(HEATER_0_PIN, HIGH);
  //  Serial.println(F("PIN HIGH"));

  if (targete1temp > currente1temp) {
    i2csend("E1 NOT SUPPORTED", "", "", 0);
  }
  if (targethbtemp > currenthbtemp) {
    digitalWrite(HEATER_1_PIN, HIGH);
  }

  // CHANGE HOTEND PINS IF THE TEMPERATURE IS HIGHER THATN TARGET
  if (targete0temp < currente0temp) {
    digitalWrite(HEATER_0_PIN, LOW);
    Serial.println(F("PIN LOW"));
  }
  if (targete1temp < currente1temp) {
    if (targete1temp != 0) {
      i2csend("E1 NOT SUPPORTED", "", "", 0);
    }
  }
  if (targethbtemp < currenthbtemp) {
    digitalWrite(HEATER_1_PIN, LOW);
  }
}

// TEMP CHANGING HOTBED LOOP
void hbtempchange() {
  if (targethbtemp > currenthbtemp) {
    digitalWrite(HEATER_HB_PIN, HIGH);
    digitalWrite(HEATER_1_PIN, HIGH);
  }
  if (targethbtemp <= currenthbtemp) {
    digitalWrite(HEATER_HB_PIN, LOW);
    digitalWrite(HEATER_1_PIN, LOW);
  }
}

// EMERGENCY EXTRUDER RETRACTION
void extruderemergencyretraction() {
  Serial.println(F("EMERGENCY RETRACTION!"));
  int t = 0;

  while (currente0temp < 200) {
    digitalWrite(HEATER_0_PIN, HIGH);
  }

  digitalWrite(HEATER_0_PIN, LOW);

  while (t <= 1000) {
    digitalWrite(E_ENABLE_PIN, LOW);
    digitalWrite(E_STEP_PIN, HIGH);
    digitalWrite(E_DIR_PIN, LOW);

    t = t + 1;

    delayMicroseconds(500);

    digitalWrite(E_STEP_PIN, LOW);
  }
}