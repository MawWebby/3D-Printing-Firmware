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

  while (testaway <= 9) {
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

  // ADD SAFETY PRECAUTION HERE FROM TURNING ON FOR NEGATIVE VALUES OR 0!!!
  if (targete0temp == 0 || currente0temp <= 0) {
    digitalWrite(HEATER_0_PIN, LOW);
    e0on = false;
    return;
  }

  if (targete0temp <= currente0temp) {
    digitalWrite(HEATER_0_PIN, LOW);
    cooldown true;
    e0ontime = 0;
    e0on = false;
    currentextrudertimer = 0;
    currentextrudertimeout2 = 0;
    differenceintime = 0;
    currentextrudertimer = 0;
    e0delaytime = 2;
  }

  if (currente0temp - 10 >= targete0temp && currente0temp + 10 <= targete0temp) {
    maintaintemp = true;
    if (debugserial == true) {
      Serial.println(F("MAINTAIN TEMP"));
    }
  }



  // E0 ACTIVATION LOOP
  if (maintaintemp == true) {

  } else {
    if (e0on == false && cooldown == false) {

      if (currente0temp == 0) {
        digitalWrite(HEATER_0_PIN, LOW);
        e0on = false;
        return;
      }

      if (targete0temp == 0) {
        digitalWrite(HEATER_0_PIN, LOW);
        e0on = false;
        return;
      }

      // CURRENT E0 TEMP IS SUFFICIENT FOR TARGET TEMPEARTURE
      if (currente0temp >= targete0temp) {
        digitalWrite(HEATER_0_PIN, LOW);
        e0on = false;
        return (0);
      }

      // CURRENT E0 TEMP IS LESS THAN TARGET TEMPERATURE
      if (currente0temp < targete0temp && currente0temp > 0 && targete0temp != 0) {
        // SET EXTRUDER TIMEOUT START VARIABLE
        startextrudertimeout = millis();

        // RUN THROUGH VARIOUS USE CASES FOR EXTRUDER
        if (currente0temp + 90 < targete0temp) {
          digitalWrite(TEMP_0_PIN, HIGH);
          e0on = true;
          e0ontime = 10;
          return;
        }
        if (currente0temp + 90 > targete0temp) {
          digitalWrite(TEMP_0_PIN, HIGH);
          e0on = true;
          e0ontime = 7;
          return;
        }
        if (currente0temp + 70 > targete0temp) {
          digitalWrite(TEMP_0_PIN, HIGH);
          e0on = true;
          e0ontime = 5;
          return;
        }
        if (currente0temp + 50 > targete0temp) {
          digitalWrite(TEMP_0_PIN, HIGH);
          e0on = true;
          e0ontime = 4;
          return;
        }
        if (currente0temp + 30 > targete0temp) {
          digitalWrite(TEMP_0_PIN, HIGH);
          e0on = true;
          e0ontime = 2;
          return;
        }
        if (currente0temp + 10 > targete0temp) {
          digitalWrite(TEMP_0_PIN, HIGH);
          e0on = true;
          e0ontime = 1;
          return;
        }
      }

    } else {
      if (e0on == true && cooldown == false) {

        unsigned long long int currentextrudertimeout2 = micros();
        unsigned long long int differenceintime = currentextrudertimeout2 - startextrudertimeout;
        currentextrudertimer = differenceintime / 1000;

        // IF E0ONTIME = 300, THEN WAIT TILL THE XTRUDER IS WITHIN 30 AND THEN SET TO LOW
        if (e0ontime == 300) {
          if (currente0temp + 50 >= targete0temp) {
            e0max = true;
            digitalWrite(HEATER_0_PIN, LOW);
            Serial.println(F("REACHED SUFFICIENT TEMPERATURE!"));
            e0on = false;
            cooldown = true;
            startextrudertimeout = millis();
            e0delaytime = 6;
            return (0);
          }
        }

        // IF E0ONTIME IS GREATER THAN CURRENT EXTRUDER TIMER
        if (e0ontime > currentextrudertimer) {
          digitalWrite(HEATER_0_PIN, LOW);
          e0ontime = 0;
          e0on = false;
          currentextrudertimer = 0;
          currentextrudertimeout2 = 0;
          differenceintime = 0;
          currentextrudertimer = 0;
          startextrudertimeout = millis();
          cooldown = true;
          e0delaytime = 6;
          return (1);
        }

        // IF E0ONTIME IS LESS THAN CURRENT EXTRUDER TIMER
        if (e0ontime <= currentextrudertimer) {
          digitalWrite(HEATER_0_PIN, HIGH);
          e0on = true;
          return (0);
        }

        // CURRENT EXTRUDER TIMEOUT (TEMP WATCHDOG)(THERMAL PROTECTION)
        if (currentextrudertimer >= extrudertimeout) {
          Serial.println(F("ERROR! - EXTRUDER HAS BEEN ON FOR WAY TOO LONG!"));
          Serial.println(F("TURNING OFF PRINTER!"));
          watchdogactivated = true;
          e0on = false;
          digitalWrite(HEATER_0_PIN, LOW);
          return (3);
        }
      } else {
        if (cooldown == true) {
          unsigned long long int currentextrudertimeout2 = micros();
          unsigned long long int differenceintime = currentextrudertimeout2 - startextrudertimeout;
          currentextrudertimer = differenceintime / 1000;

          if (currentextrudertimer >= e0delaytime) {
            cooldown = false;
            e0ontime = 0;
            e0on = false;
            currentextrudertimer = 0;
            currentextrudertimeout2 = 0;
            differenceintime = 0;
            currentextrudertimer = 0;
          }
        } else {
          Serial.println(F("TEMP CIRCUIT FAILED ALL CONDITIONS!"));
          digitalWrite(HEATER_0_PIN, LOW);
          watchdogactivated = true;
          return;
        }
      }
    }
  }

  // CHANGE HOTEND PINS IF THE TEMPERATURE IS HIGHER THAN TARGET
  if (targete0temp < currente0temp) {
    digitalWrite(HEATER_0_PIN, LOW);
    e0on = false;
    cooldown = true;
    e0delaytime = 10;
  }
}

// TEMP CHANGING HOTBED LOOP
void hbtempchange() {
  if (targethbtemp > currenthbtemp) {
    digitalWrite(HEATER_HB_PIN, HIGH);
    digitalWrite(HEATER_1_PIN, HIGH);
    hbon = true;
    return;
  }
  if (targethbtemp <= currenthbtemp) {
    digitalWrite(HEATER_HB_PIN, LOW);
    digitalWrite(HEATER_1_PIN, LOW);
    hbon = false;
    return;
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

void tempreporting() {
  Serial.println(F(""));
  Serial.print(F("T:"));
  Serial.print(currente0temp);
  Serial.print(F(" /"));
  Serial.print(targete0temp);
  Serial.print(F(" B:"));
  Serial.print(currenthbtemp);
  Serial.print(F(" /"));
  Serial.print(targethbtemp);
  Serial.print(F(" @:"));
  if (e0on == true) {
    Serial.print(F("255"));
  } else {
    Serial.print(F("0"));
  }
  Serial.print(F(" B@:"));
  if (hbon == true) {
    Serial.print(F("255"));
  } else {
    Serial.print(F("0"));
  }
  Serial.print(F(" A:"));
  Serial.println(currente1temp);
  return;
}