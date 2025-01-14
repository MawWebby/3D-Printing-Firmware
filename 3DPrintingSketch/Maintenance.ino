// MAINTENANCE LOOP TO CLEAN UP EVERYTHING THAT IS NO LONGER NEEDED
int maintenance() {
  if (numberinecache != 0) {
    Serial.println(F("PROCESSING ECACHE"));
    processECACHE();
  }

  if (printfanon == false) {
    digitalWrite(FAN_PIN, LOW);
  }

  if (simulationmode == true) {
    targete0temp = 0;
    targete1temp = 0;
    targethbtemp = 0;
    digitalWrite(HEATER_0_PIN, LOW);
    digitalWrite(HEATER_1_PIN, LOW);
    digitalWrite(HEATER_HB_PIN, LOW);
    digitalWrite(E_ENABLE_PIN, LOW);
    edisabled = true;
  }

  e0max = false;
  ledpinblink = ledpinblink + 1;

  // LED PIN BLINK CODE FOR STATUS INDICATORS AND MAINTENANCE EVERY SECOND
  if (ledpinblink >= 5) {

    ledpinblink = 0;

    if (ledblink == true) {
      digitalWrite(ledpin, LOW);
      ledblink = false;
    } else {
      digitalWrite(ledpin, HIGH);
      ledblink = true;
    }

    // MAKE SURE STEPPER MOTORS ARE DISABLED IF STEPPER MOTORS ARE DISABLED
    if (steppermotorsdisabled == true) {
      if (xdisabled == true) {
        digitalWrite(X_ENABLE_PIN, HIGH);
      }
      if (ydisabled == true) {
        digitalWrite(Y_ENABLE_PIN, HIGH);
      }
      if (zdisabled == true) {
        digitalWrite(Z_ENABLE_PIN, HIGH);
      }
      if (edisabled == true) {
        digitalWrite(E_ENABLE_PIN, HIGH);
      }
    }

    // MAKE SURE IT IS DISABLED IF CURRENTLY LOCKED
    if (currentlylocked == true) {
      targete0temp = 0;
      targethbtemp = 0;
      digitalWrite(HEATER_0_PIN, LOW);
      digitalWrite(HEATER_1_PIN, LOW);
      digitalWrite(HEATER_HB_PIN, LOW);
      digitalWrite(X_ENABLE_PIN, LOW);
      digitalWrite(Y_ENABLE_PIN, LOW);
      digitalWrite(Z_ENABLE_PIN, LOW);
      digitalWrite(E_ENABLE_PIN, LOW);
      digitalWrite(E1_ENABLE_PIN, LOW);
      targetxdimension = currentxdimension;
      targetydimension = currentydimension;
      targetzdimension = currentzdimension;
    }
  }



  ///////////////////////////////////////////////
  // EXTRUDER THERMAL PROTECTION CODE (PART 1) //
  ///////////////////////////////////////////////
  {
    if (e0on == true) {
      if (e0onprevious == false) {
        startextrudertimeout = currenttimer;
        e0onprevious = false;
      } else {
        if (e0onprevious == true) {
          float timedifference = currenttimer - startextrudertimeout;
          timedifference = timedifference / 1000;
          if (timedifference >= extrudertimeout) {
            Serial.println(F("THERMAL RUNAWAY DETECTED! (E0)"));
            Serial.println(F("CALLING WATCHDOG!"));
            e0on = false;
            e0onprevious = false;
            digitalWrite(HEATER_0_PIN, LOW);
            watchdogactivated = true;
            return;
          }
        } else {
          Serial.println(F("TEMP VARIABLES NOT SET RIGHT/CALLING WATCHDOG FOR SAFETY!"));
          e0on = false;
          e0onprevious = false;
          digitalWrite(HEATER_0_PIN, LOW);
          watchdogactivated = true;
          return;
        }
      }
    } else {
      if (e0on == false) {
        e0onprevious = false;
        digitalWrite(HEATER_0_PIN, LOW);
      } else {
        Serial.println(F("TEMP VARIABLES NOT SET RIGHT/CALLING WATCHDOG FOR SAFETY!"));
        e0on = false;
        e0onprevious = false;
        digitalWrite(HEATER_0_PIN, LOW);
        watchdogactivated = true;
        return;
      }
    }
  }



  /////////////////////////////////////////////////
  // HEATED BED THERMAL PROTECTION CODE (PART 2) //
  /////////////////////////////////////////////////
  {
    if (hbon == true) {
      if (hbonprevious == false) {
        startheatedbedtimeout = currenttimer;
        hbonprevious = false;
      } else {
        if (hbonprevious == true) {
          float timedifference = currenttimer - startextrudertimeout;
          timedifference = timedifference / 1000;
          if (timedifference >= heatedbedtimeout) {
            Serial.println(F("THERMAL RUNAWAY DTECTED! (HB)"));
            Serial.println(F("CALLING WATCHDOG!"));
            hbon = false;
            hbonprevious = false;
            digitalWrite(HEATER_HB_PIN, LOW);
            digitalWrite(HEATER_0_PIN, LOW);
            watchdogactivated = true;
            return;
          }
        } else {
          Serial.println(F("TEMP VARIABLES NOT SET RIGHT/CALLING WATCHDOG FOR SAFETY!"));
          hbon = false;
          hbonprevious = false;
          digitalWrite(HEATER_HB_PIN, LOW);
          watchdogactivated = true;
          return;
        }
      }
    } else {
      if (hbon == false) {
        hbonprevious = false;
        digitalWrite(HEATER_HB_PIN, LOW);
      } else {
        Serial.println(F("TEMP VARIABLES NOT SET RIGHT/CALLING WATCHDOG FOR SAFETY!"));
        hbon = false;
        hbonprevious = false;
        digitalWrite(HEATER_HB_PIN, LOW);
        watchdogactivated = true;
        return;
      }
    }
  }
}

// REAL TIME CLOCK
int realtimeclock() {
  currenttimer = millis();
  if (millis() <= 0) {
    currenttimer = -1;
  }
}

// ALERT TIME CLOCK
int alerttimeclock() {
  if (targettime[0] != -1) {
    if (targettime <= (currenttimer - currenttimer)) {
      // TIME HAS EXCEEDED
      targettime[0] = -1;
      digitalWrite(TEMP_0_PIN, LOW);
      targettimeclock(0, -1, false, true);

      // CALL TO SERVICE END
    }
  }
  if (targettime[1] != -1) {
    if (targettime <= (currenttimer - currenttimer)) {
      // TIME HAS EXCEEDED
      targettime[1] = -1;
      targettimeclock(1, -1, false, true);

      // CALL TO SERVICE END
    }
  }
  if (targettime[2] != -1) {
    if (targettime <= (currenttimer - currenttimer)) {
      // TIME HAS EXCEEDED
      targettime[2] = -1;
      digitalWrite(TEMP_1_PIN, LOW);
      targettimeclock(2, -1, false, true);

      // CALL TO SERVICE END
    }
  }
  if (targettime[3] != -1) {
    if (targettime <= (currenttimer - currenttimer)) {
      // TIME HAS EXCEEDED
      targettime[3] = -1;
      digitalWrite(TEMP_1_PIN, LOW);
      targettimeclock(3, -1, false, true);

      // CALL TO SERVICE END
    }
  }
  if (targettime[4] != -1) {
    if (targettime <= (currenttimer - currenttimer)) {
      // TIME HAS EXCEEDED
      targettime[4] = -1;
      digitalWrite(TEMP_1_PIN, LOW);
      targettimeclock(4, -1, false, true);

      // CALL TO SERVICE END
    }
  }
  if (targettime[5] != -1) {
    if (targettime <= (currenttimer - currenttimer)) {
      // TIME HAS EXCEEDED
      targettime[5] = -1;
      digitalWrite(TEMP_1_PIN, LOW);
      targettimeclock(5, -1, false, true);

      // CALL TO SERVICE END
    }
  }
  if (targettime[6] != -1) {
    if (targettime <= (currenttimer - currenttimer)) {
      // TIME HAS EXCEEDED
      targettime[6] = -1;
      digitalWrite(TEMP_1_PIN, LOW);
      targettimeclock(6, -1, false, true);

      // CALL TO SERVICE END
    }
  }
  if (targettime[7] != -1) {
    if (targettime <= (currenttimer - currenttimer)) {
      // TIME HAS EXCEEDED
      targettime[7] = -1;
      digitalWrite(TEMP_1_PIN, LOW);
      targettimeclock(7, -1, false, true);

      // CALL TO SERVICE END
    }
  }
  if (targettime[8] != -1) {
    if (targettime <= (currenttimer - currenttimer)) {
      // TIME HAS EXCEEDED
      targettime[8] = -1;
      digitalWrite(TEMP_1_PIN, LOW);
      targettimeclock(8, -1, false, true);

      // CALL TO SERVICE END
    }
  }
  if (targettime[9] != -1) {
    if (targettime <= (currenttimer - currenttimer)) {
      // TIME HAS EXCEEDED
      targettime[9] = -1;
      digitalWrite(TEMP_1_PIN, LOW);
      targettimeclock(9, -1, false, true);

      // CALL TO SERVICE END
    }
  }
}



///////////////////////////////
//// DIFFERENCE TIME CLOCK ////
///////////////////////////////
// TIMERS - LOOP                - PURPOSE
// 0      - tempchange()        - THERMAL PROTECTION - EXTRUDER ON TIME
// 1      - startup()           - STARTUP TIME
// 2      - hbtempchange()      - HEATED BED THERMAL PROTECTION - HEATED BED ON TIME
// 3      - tempreporting()     - TIME TO REPORT TEMPERATURES AUTOMATICALLY (M155)
// 4      - printTimer()        - Print Timer as Requested by M75/76
// 5      -
// 6      -
// 7      -
// 8      -
// 9      -


// CLOCK MANAGER
int targettimeclock(int clocknumber, int targettime2, bool start, bool stop) {
  switch (clocknumber) {
    case 0:
      if (start == true) {
        clocktimers[0] = millis();
        targettime[0] = targettime2;
      }
      if (stop == true) {
        int timers = millis() - clocktimers[0];
        clocktimers[0] = 0;
        return (timers);
      }
      break;
    case 1:
      if (start == true) {
        clocktimers[1] = millis();
        targettime[1] = targettime2;
      }
      if (stop == true) {
        int timers = millis() - clocktimers[0];
        clocktimers[0] = 0;
        return (timers);
      }
      break;
    case 2:
      if (start == true) {
        clocktimers[2] = millis();
        targettime[2] = targettime2;
      }
      if (stop == true) {
        int timers = millis() - clocktimers[2];
        clocktimers[2] = 0;
        return (timers);
      }
      break;
    case 3:
      if (start == true) {
        clocktimers[3] = millis();
        targettime[3] = targettime2;
      }
      if (stop == true) {
        int timers = millis() - clocktimers[3];
        clocktimers[3] = 0;
        return (timers);
      }
      break;
    case 4:
      if (start == true) {
        clocktimers[4] = millis();
        targettime[4] = targettime2;
      }
      if (stop == true) {
        int timers = millis() - clocktimers[4];
        clocktimers[4] = 0;
        return (timers);
      }
      break;
    case 5:
      if (start == true) {
        clocktimers[5] = millis();
        targettime[5] = targettime2;
      }
      if (stop == true) {
        int timers = millis() - clocktimers[5];
        clocktimers[5] = 0;
        return (timers);
      }
      break;
    case 6:
      if (start == true) {
        clocktimers[6] = millis();
        targettime[6] = targettime2;
      }
      if (stop == true) {
        int timers = millis() - clocktimers[6];
        clocktimers[6] = 0;
        return (timers);
      }
      break;
    case 7:
      if (start == true) {
        clocktimers[7] = millis();
        targettime[7] = targettime2;
      }
      if (stop == true) {
        int timers = millis() - clocktimers[7];
        clocktimers[7] = 0;
        return (timers);
      }
      break;
    case 8:
      if (start == true) {
        clocktimers[8] = millis();
        targettime[8] = targettime2;
      }
      if (stop == true) {
        int timers = millis() - clocktimers[8];
        clocktimers[8] = 0;
        return (timers);
      }
      break;
    case 9:
      if (start == true) {
        clocktimers[9] = millis();
        targettime[9] = targettime2;
      }
      if (stop == true) {
        int timers = millis() - clocktimers[9];
        clocktimers[9] = 0;
        return (timers);
      }
      break;
    case 10:
      if (start == true) {
        clocktimers[10] = millis();
        targettime[10] = targettime2;
      }
      if (stop == true) {
        int timers = millis() - clocktimers[10];
        clocktimers[10] = 0;
        return (timers);
      }
      break;
    case 11:
      if (start == true) {
        clocktimers[11] = millis();
        targettime[11] = targettime2;
      }
      if (stop == true) {
        int timers = millis() - clocktimers[11];
        clocktimers[11] = 0;
        return (timers);
      }
      break;
  }
}




///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// RETURN OF SUCCESSFUL PRINTS ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
int readsuccessprints() {
  int times256 = EEPROM.read(11);
  times256 = times256 * 256;
  times256 = times256 + EEPROM.read(12);
  return (times256);
}

int updatesuccessprints() {
  if (EEPROM.read(12) == 255) {
    EEPROM.update(11, EEPROM.read(11) + 1);
    EEPROM.update(12, 0);
  } else {
    EEPROM.update(12, EEPROM.read(12) + 1);
  }
}

int readbadprints() {
  int times256 = EEPROM.read(13);
  times256 = times256 * 256;
  times256 = times256 + EEPROM.read(14);
  return (times256);
}

int updatebadprints() {
  if (EEPROM.read(14) == 255) {
    EEPROM.update(13, EEPROM.read(13) + 1);
    EEPROM.update(14, 0);
  } else {
    EEPROM.update(14, EEPROM.read(14) + 1);
  }
}

float printsuccess() {
  int times256 = EEPROM.read(11);
  times256 = times256 * 256;
  times256 = times256 + EEPROM.read(12);

  int times25 = EEPROM.read(13);
  times25 = times25 * 256;
  times25 = times25 + EEPROM.read(14);

  float percentage = times256 / times25;
  return (percentage);
}