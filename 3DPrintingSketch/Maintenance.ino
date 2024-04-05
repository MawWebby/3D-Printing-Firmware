// MAINTENANCE LOOP TO CLEAN UP EVERYTHING THAT IS NO LONGER NEEDED
int maintenance() {
  if (numberinecache != 0) {
    Serial.println(F("PROCESSING ECACHE"));
    processECACHE();
  }

  if (printfanon == false) {
    digitalWrite(FAN_PIN, LOW);
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
      digitalWrite(X_ENABLE_PIN, HIGH);
      digitalWrite(Y_ENABLE_PIN, HIGH);
      digitalWrite(Z_ENABLE_PIN, HIGH);
      digitalWrite(E_ENABLE_PIN, HIGH);
      digitalWrite(E1_ENABLE_PIN, HIGH);
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
}

// REAL TIME CLOCK
int realtimeclock() {
}


///////////////////////////////
//// DIFFERENCE TIME CLOCK ////
///////////////////////////////
// TIMERS - LOOP                - PURPOSE
// 0      - tempchange()        - THERMAL PROTECTION - EXTRUDER ON TIME
// 1      - startup()           - STARTUP TIME
// 2      - hbtempchange()      - HEATED BED THERMAL PROTECTION - HEATED BED ON TIME
// 3      -  
// 4      - 
// 5      - 
// 6      - 
// 7      - 
// 8      - 
// 9      - 
int targettimclock(int clocknumber, bool start, bool stop, bool alert) {

  // UPDATE REAL TIME CLOCK FOR UPDATED INFORMATION
  realtimeclock();

  // START TIMER
  if (start == true) {
    // UPDATE CLOCK NUMBERS ACCORDINGLY TO TARGETS
    switch (clocknumber) {
      case 0:
        if (start == true) {
          clocktimers[1] = millis();
        }
        break;
      case 1:

        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        break;
      case 5:
        break;
      case 6:
        break;
      case 7:
        break;
      case 8:
        break;
      case 9:
        break;
      case 10:
        break;
      case 11:
        break;
    }
  } else {

    // STOP TIMER
    if (stop == true) {
      
      // 
    } else {

      // 
    }
  }
}