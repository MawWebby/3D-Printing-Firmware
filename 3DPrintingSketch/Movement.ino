/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

// STEPPER MOTOR CONTROLS
void movement() {

  Serial.print(F("move"));

  // VERIFY ENDSTOP POSITION
  endstops();

  // SET MOTOR OUTPUT PINS TO LOW!
  digitalWrite(X_STEP_PIN, LOW);
  digitalWrite(Y_STEP_PIN, LOW);
  digitalWrite(Z_STEP_PIN, LOW);
  digitalWrite(E_STEP_PIN, LOW);

  // MOVE TO NEW GCODE COMMAND IF CONDITIONS ARE MET
  if ((xstepstaken >= xstepsrequired && ystepstaken >= ystepsrequired && zstepstaken >= zstepsrequired && estepstaken >= estepsrequired) || (currentxdimension >= targetxdimension - 0.05 && currentxdimension <= targetxdimension + 0.05 && currentydimension >= targetydimension - 0.05 && currentydimension <= targetydimension + 0.05 && currentzdimension >= targetzdimension - 0.05 && currentzdimension <= targetzdimension + 0.05)) {
    movetonewgcodeformovement();
  } else {
    if (checklockstatus(currentgcodecommand) == 1) {
    }
  }

  /*
    // TIME THAT HAS ELAPSED SINCE PREVIOUS READINGS
    unsigned long long int timethathaselapsed = millis() - timesincelastmotorcurrent;
    float timethathaselapsedinseconds = timethathaselapsed / 1000;
  */


  // TAKE CARE OF DIRECTIONAL INPUTS HERE
  {
    if (xdisabled == false) {
      if (xmovingnegative == true) {
        digitalWrite(X_DIR_PIN, LOW);
        digitalWrite(X_ENABLE_PIN, LOW);
        steppermotorsdisabled = false;
        xdisabled = false;
        if (currentxdimension >= targetxdimension || xstepstaken <= xstepsrequired) {
          if (xcurrentstep >= xsteptimer) {
            if (xendstopminactive != true || xendstopmaxactive != true) {
              digitalWrite(X_STEP_PIN, HIGH);
              xstepstaken = xstepstaken + 1;
              xcurrentstep = 0;
              currentxdimension = currentxdimension - xmodifier;
            }
          }
        }
      }

      if (xmovingpositive == true) {
        digitalWrite(X_DIR_PIN, HIGH);
        digitalWrite(X_ENABLE_PIN, LOW);
        steppermotorsdisabled = false;
        xdisabled = false;
        if (currentxdimension <= targetxdimension || xstepstaken <= xstepsrequired) {
          if (xcurrentstep >= xsteptimer) {
            if (xendstopminactive != true || xendstopmaxactive != true) {
              digitalWrite(X_STEP_PIN, HIGH);
              xstepstaken = xstepstaken + 1;
              xcurrentstep = 0;
              currentxdimension = currentxdimension + xmodifier;
            }
          }
        } else {
          xmovingpositive = false;
        }
      }

      if (xmovingnegative == false && xmovingpositive == false) {
        digitalWrite(X_DIR_PIN, LOW);
        digitalWrite(X_ENABLE_PIN, LOW);
        steppermotorsdisabled = false;
        xdisabled = false;
      }
    }

    if (ydisabled == false) {
      if (ymovingnegative == true) {
        digitalWrite(Y_DIR_PIN, HIGH);
        digitalWrite(Y_ENABLE_PIN, LOW);
        steppermotorsdisabled = false;
        ydisabled = false;
        if (currentydimension >= targetydimension && ystepstaken <= ystepsrequired) {
          if (ycurrentstep >= ysteptimer) {
            if (yendstopminactive != true || yendstopmaxactive != true) {
              digitalWrite(Y_STEP_PIN, HIGH);
              ystepstaken = ystepstaken + 1;
              ycurrentstep = 0;
              currentydimension = currentydimension - ymodifier;
            }
          }
        }
      }

      if (ymovingpositive == true) {
        digitalWrite(Y_DIR_PIN, LOW);
        digitalWrite(Y_ENABLE_PIN, LOW);
        steppermotorsdisabled = false;
        ydisabled = false;
        if (currentydimension <= targetydimension && ystepstaken <= ystepsrequired) {
          if (ycurrentstep >= ysteptimer) {
            if (yendstopminactive != true || yendstopmaxactive != true) {
              digitalWrite(Y_STEP_PIN, HIGH);
              ystepstaken = ystepstaken + 1;
              ycurrentstep = 0;
              currentydimension = currentydimension + ymodifier;
            }
          }
        }
      }

      if (ymovingnegative == false && ymovingpositive == false) {
        digitalWrite(Y_DIR_PIN, LOW);
        digitalWrite(Y_ENABLE_PIN, LOW);
        steppermotorsdisabled = false;
        ydisabled = false;
      }
    }

    if (zdisabled == false) {
      if (zmovingnegative == true) {
        digitalWrite(Z_DIR_PIN, HIGH);
        digitalWrite(Z_ENABLE_PIN, LOW);
        steppermotorsdisabled = false;
        zdisabled = false;
        if (currentzdimension >= targetzdimension && zstepstaken <= zstepsrequired) {
          if (zcurrentstep >= zsteptimer) {
            if (zendstopminactive != true || zendstopmaxactive != true) {
              digitalWrite(Z_STEP_PIN, HIGH);
              zstepstaken = zstepstaken + 1;
              zcurrentstep = 0;
              currentzdimension = currentzdimension - zmodifier;
            }
          }
        }
      }

      if (zmovingpositive == true) {
        digitalWrite(Z_DIR_PIN, LOW);
        digitalWrite(Z_ENABLE_PIN, LOW);
        steppermotorsdisabled = false;
        zdisabled = false;
        if (currentzdimension <= targetzdimension && zstepstaken <= zstepsrequired) {
          if (zcurrentstep >= zsteptimer) {
            if (zendstopminactive != true || zendstopmaxactive != true) {
              digitalWrite(Z_STEP_PIN, HIGH);
              zstepstaken = zstepstaken + 1;
              zcurrentstep = 0;
              currentzdimension = currentzdimension + zmodifier;
            }
          }
        }
      }

      if (zmovingnegative == false && zmovingpositive == false) {
        digitalWrite(Z_DIR_PIN, LOW);
        digitalWrite(Z_ENABLE_PIN, LOW);
        steppermotorsdisabled = false;
        zdisabled = false;
      }
    }

    if (edisabled == false && simulationmode == false) {
      if (allowcoldextrusion == true || currente0temp >= 170) {
        if (e0movingnegative == true) {
          digitalWrite(E_DIR_PIN, LOW);
          digitalWrite(E_ENABLE_PIN, LOW);
          steppermotorsdisabled = false;
          edisabled = false;
          if (currente0motordimension >= targete0motordimension && estepstaken <= estepsrequired) {
            if (ecurrentstep >= esteptimer) {
              digitalWrite(E_STEP_PIN, HIGH);
              estepstaken = estepstaken + 1;
              ecurrentstep = 0;
              currente0motordimension = currente0motordimension - e0motormodifier;
            }
          }
        }

        if (e0movingpositive == true) {
          digitalWrite(E_DIR_PIN, HIGH);
          digitalWrite(E_ENABLE_PIN, LOW);
          steppermotorsdisabled = false;
          edisabled = false;
          if (currente0motordimension <= targete0motordimension && estepstaken <= estepsrequired) {
            if (ecurrentstep >= esteptimer) {
              digitalWrite(E_STEP_PIN, HIGH);
              estepstaken = estepstaken + 1;
              ecurrentstep = 0;
              currente0motordimension = currente0motordimension + e0motormodifier;
            }
          }
        }

        if (e0movingnegative == false && e0movingpositive == false) {
          digitalWrite(E_DIR_PIN, LOW);
          digitalWrite(E_ENABLE_PIN, LOW);
          steppermotorsdisabled = false;
          edisabled = false;
        }
      } else {
        if (e0movingnegative != false || e0movingpositive != false) {
          Serial.println(F("EXTRUDER CONDITIION NOT MET; FORCE RUNNING EXTRUDER HEATING"));
          tempsensing();
        }
      }
    }
  }


  // NEW TIMING VARIABLES
  if (xmovingpositive == true || xmovingnegative == true) {
    xcurrentstep = xcurrentstep + 1;
  }
  if (ymovingpositive == true || ymovingnegative == true) {
    ycurrentstep = ycurrentstep + 1;
  }
  if (zmovingpositive == true || zmovingnegative == true) {
    zcurrentstep = zcurrentstep + 1;
  }
  if (e0movingpositive == true || e0movingnegative == true) {
    ecurrentstep = ecurrentstep + 1;
  }



  // SOFTWARE MAXIMUM ENDSTOP
  if (currentxdimension >= xendstopmaxvalue) {
    xendstopmaxactive = true;
  }
  if (currentydimension >= yendstopmaxvalue) {
    yendstopmaxactive = true;
  }
  if (currentzdimension >= zendstopmaxvalue) {
    zendstopmaxactive = true;
  }
  if (currentxdimension <= xendstopmaxvalue) {
    xendstopmaxactive = false;
  }
  if (currentydimension <= yendstopmaxvalue) {
    yendstopmaxactive = false;
  }
  if (currentzdimension <= zendstopmaxvalue) {
    zendstopmaxactive = false;
  }


  if (debugserial == true) {
    Serial.print(" X: ");
    Serial.print(xstepstaken);
    Serial.print(" / ");
    Serial.print(xstepsrequired);
    Serial.print(" (");
    Serial.print(currentxdimension);
    Serial.print(" / ");
    Serial.print(targetxdimension);
    Serial.print("); Y: ");
    Serial.print(ystepstaken);
    Serial.print(" / ");
    Serial.print(ystepsrequired);
    Serial.print(" (");
    Serial.print(currentydimension);
    Serial.print(" / ");
    Serial.print(targetydimension);
    Serial.print("); Z: ");
    Serial.print(zstepstaken);
    Serial.print(" / ");
    Serial.print(zstepsrequired);
    Serial.print(" (");
    Serial.print(currentzdimension);
    Serial.print(" / ");
    Serial.print(targetzdimension);
    Serial.print("); E: ");
    Serial.print(estepstaken);
    Serial.print(" / ");
    Serial.print(estepsrequired);
    Serial.print(" (");
    Serial.print(currente0motordimension);
    Serial.print(" / ");
    Serial.println(targete0motordimension);
  }

  // RESET ALL STEP PINS
  digitalWrite(X_STEP_PIN, LOW);
  digitalWrite(Y_STEP_PIN, LOW);
  digitalWrite(Z_STEP_PIN, LOW);
  digitalWrite(E_STEP_PIN, LOW);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

// MOVE TO NEW GCODE FOR MOVEMENT
void movetonewgcodeformovement() {

  // DEBUG SERIAL FOR NEW GCODE PROMPT
  if (debugserial == true) {
    Serial.println(F("NEW_GCODE"));
  }

  // DETERMINE IF THE CONDITIONS ARE MET TO CONTINUE TO NEW GCODE COMMAND
  bool conditionsmetX = false;
  bool conditionsmetY = false;
  bool conditionsmetZ = false;
  bool conditionsmetE = false;



  // DIRECTIONAL MOVING VERIFICATION CODE
  {
    // X MOVING VERIFICATION CODE
    {
      if (xmovingpositive == true) {
        if (targetxdimension <= currentxdimension) {
          conditionsmetX = true;
        } else {
          conditionsmetX = false;
        }
      }

      if (xmovingnegative == true) {
        if (targetxdimension >= currentxdimension) {
          conditionsmetX = true;
        } else {
          conditionsmetX = false;
        }
      }

      if (xmovingpositive == false && xmovingnegative == false) {
        conditionsmetX = true;
      }
    }

    // Y MOVING VERIFCATION CODE
    {
      if (ymovingpositive == true) {
        if (targetydimension <= currentydimension) {
          conditionsmetY = true;
        } else {
          conditionsmetY = false;
        }
      }

      if (ymovingnegative == true) {
        if (targetydimension >= currentydimension) {
          conditionsmetY = true;
        } else {
          conditionsmetY = false;
        }
      }

      if (ymovingpositive == false && ymovingnegative == false) {
        conditionsmetY = true;
      }
    }
    // Z MOVING VERIFICATION CODE
    {
      if (zmovingpositive == true) {
        if (targetzdimension <= currentzdimension) {
          conditionsmetZ = true;
        } else {
          conditionsmetZ = false;
        }
      }

      if (zmovingnegative == true) {
        if (targetzdimension <= currentzdimension) {
          conditionsmetZ = true;
        } else {
          conditionsmetZ = false;
        }
      }

      if (zmovingnegative == false && zmovingpositive == false) {
        conditionsmetZ = true;
      }
    }

    // E0 MOVING VERIFICATION CODE
    {
      if (currente0motordimension == targete0motordimension) {
        conditionsmetE = true;
      } else {
        if (e0movingpositive == true) {
          if (targete0motordimension <= currente0motordimension) {
            conditionsmetE = true;
          } else {
            conditionsmetE = false;
          }
        }

        if (e0movingnegative == true) {
          if (targete0motordimension >= currente0motordimension) {
            conditionsmetE = true;
          } else {
            conditionsmetE = false;
          }
        }

        if (e0movingpositive == false && e0movingnegative == false) {
          conditionsmetE = true;
        }
      }
      if (simulationmode == true) {
        conditionsmetE = true;
      }
    }
    conditionsmetE = true;
  }

  // IF ALL THE CONDITIONS ARE MET, CONTINUE TO NEW GCODE
  if (conditionsmetX == true && conditionsmetY == true && conditionsmetZ == true && conditionsmetE && printingactive == true && checklockstatus(currentgcodecommand) == 1) {


    // SEND OKAY IF NOT PREVIOUSLY SENT
    if (currentlycachedgcodes <= 8) {
      Serial.println(F("ok"));
    } else {
      // SECOND CONDITION - SEND OKAY IF NOT PREVIOUSLY SENT
      if (readfromarray(currentgcodecommand, 9) == 0) {
        Serial.println(F("ok"));
      }
    }

    // MOVE TO NEW GCODE
    clearrowinarray(currentgcodecommand, true);

    /////////////////////////////////////////////
    //// RUN LONG LOOPS THAT COULDN'T BEFORE ////
    /////////////////////////////////////////////
    lcdEngine();
    tempsensing();

    // SET ALL MOVEMENT DIRECTIONS TO FALSE
    xmovingpositive = false;
    xmovingnegative = false;
    ymovingpositive = false;
    ymovingnegative = false;
    zmovingpositive = false;
    zmovingnegative = false;
    e0movingpositive = false;
    e0movingnegative = false;

    // FLIP TO NEXT GCODE COMMAND
    if (currentgcodecommand != 10) {
      currentgcodecommand = currentgcodecommand + 1;
    } else {
      currentgcodecommand = 0;
    }


    // SET NEW TARGET POSITIONS
    targetxdimension = readfromarray(currentgcodecommand, 0);
    targetydimension = readfromarray(currentgcodecommand, 1);
    targetzdimension = readfromarray(currentgcodecommand, 2);
    targete0motordimension = readfromarray(currentgcodecommand, 3);

    if (debugserial == true) {
      Serial.println(currentgcodecommand);
      Serial.print(targetxdimension);
      Serial.print(" ");
      Serial.print(targetydimension);
      Serial.print(" ");
      Serial.print(targetzdimension);
      Serial.print(" ");
      Serial.println(targete0motordimension);
    }


    // DECLARE DIFFERENCE VARIABLES
    float xdifference = 0;
    float ydifference = 0;
    float zdifference = 0;
    float edifference = 0;


    // RESET ALL VARIABLES BACK TO 0
    xsteptimer = 0;
    ysteptimer = 0;
    zsteptimer = 0;
    esteptimer = 0;
    xcurrentstep = 0;
    ycurrentstep = 0;
    zcurrentstep = 0;
    ecurrentstep = 0;
    xstepsrequired = 0;
    ystepsrequired = 0;
    zstepsrequired = 0;
    estepsrequired = 0;
    xstepstaken = 0;
    ystepstaken = 0;
    zstepstaken = 0;
    estepstaken = 0;

    // DIMENSION ANALYSIS AND STEP COUNTS
    {
      // X DIMENSION ANALYSIS AND STEP COUNTS
      if (targetxdimension > currentxdimension) {
        xdifference = targetxdimension - currentxdimension;
        xmovingpositive = true;
        xmovingnegative = false;
        xstepsrequired = xdifference / xmodifier;
        xdisabled = false;
      }
      if (targetxdimension == currentxdimension) {
        xdifference = 0;
        xstepsrequired = 0;
        xmovingpositive = false;
        xmovingnegative = false;
        xdisabled = false;
      }
      if (targetxdimension < currentxdimension) {
        xdifference = currentxdimension - targetxdimension;
        xmovingpositive = false;
        xmovingnegative = true;
        xstepsrequired = xdifference / xmodifier;
        xdisabled = false;
      }


      // Y DIMENSION ANALYSIS AND STEP COUNTS
      {
        if (targetydimension > currentydimension) {
          ydifference = targetydimension - currentydimension;
          ymovingpositive = true;
          ymovingnegative = false;
          ystepsrequired = ydifference / ymodifier;
          ydisabled = false;
        }
        if (targetydimension == currentydimension) {
          ydifference = 0;
          ystepsrequired = 0;
          ymovingpositive = false;
          ymovingnegative = false;
          ydisabled = false;
        }
        if (targetydimension < currentydimension) {
          ydifference = currentydimension - targetydimension;
          ymovingpositive = false;
          ymovingnegative = true;
          ystepsrequired = ydifference / ymodifier;
          ydisabled = false;
        }
      }

      // Z DIMENSION ANALYSIS AND STEP COUNTS
      {
        if (targetzdimension > currentzdimension) {
          zdifference = targetzdimension - currentzdimension;
          zmovingpositive = true;
          zmovingnegative = false;
          zstepsrequired = zdifference / zmodifier;
          zdisabled = false;
        }
        if (targetzdimension == currentzdimension) {
          zdifference = 0;
          zstepsrequired = 0;
          zmovingpositive = false;
          zmovingnegative = false;
          zdisabled = false;
        }
        if (targetzdimension < currentzdimension) {
          zdifference = currentzdimension - targetzdimension;
          zmovingpositive = false;
          zmovingnegative = true;
          zstepsrequired = zdifference / zmodifier;
          zdisabled = false;
        }
      }

      // E0 DIMENSION ANALYSIS AND STEP COUNTS
      {
        if (simulationmode == false) {
          if (targete0motordimension > currente0motordimension) {
            edifference = targete0motordimension - currente0motordimension;
            e0movingpositive = true;
            e0movingnegative = false;
            estepsrequired = edifference / e0motormodifier;
            edisabled = false;
          }
          if (targete0motordimension == currente0motordimension) {
            edifference = 0;
            estepsrequired = 0;
            e0movingpositive = false;
            e0movingnegative = false;
            edisabled = false;
          }
          if (targete0motordimension < currente0motordimension) {
            edifference = currente0motordimension - targete0motordimension;
            e0movingpositive = false;
            e0movingnegative = true;
            estepsrequired = edifference / e0motormodifier;
            edisabled = false;
          }
        }
      }
    }

    // DETERMINE WHICH OF THE FOLLOWING HAS THE GREATEST STEP COUNT REQUIRED AND BASE EVERYTHING ON THAT ONE AND DETERMINE X/Y/Z/ESTEPTIMERs
    {
      // IF X IS THE LARGEST, CONTINUE WITH THAT
      if (xstepsrequired >= ystepsrequired && xstepsrequired >= zstepsrequired && xstepsrequired >= estepsrequired) {
        xsteptimer = 1;
        ysteptimer = xstepsrequired / ystepsrequired;
        zsteptimer = xstepsrequired / zstepsrequired;
        esteptimer = xstepsrequired / estepsrequired;
      } else {
        // IF IT IS NOT X, IS IT Y
        if (ystepsrequired >= xstepsrequired && ystepsrequired >= zstepsrequired && ystepsrequired >= estepsrequired) {
          ysteptimer = 1;
          xsteptimer = ystepsrequired / xstepsrequired;
          zsteptimer = ystepsrequired / zstepsrequired;
          esteptimer = ystepsrequired / estepsrequired;
        } else {
          // IF IT IS NOT Y, IS IT Z
          if (zstepsrequired >= xstepsrequired && zstepsrequired >= ystepsrequired && zstepsrequired >= estepsrequired) {
            zsteptimer = 1;
            xsteptimer = zstepsrequired / xstepsrequired;
            ysteptimer = zstepsrequired / ystepsrequired;
            esteptimer = zstepsrequired / estepsrequired;
          } else {
            // IF IT IS NOT Z, IS IT E
            if (zstepsrequired >= xstepsrequired && zstepsrequired >= ystepsrequired && zstepsrequired >= estepsrequired) {
              esteptimer = 1;
              xsteptimer = estepsrequired / xstepsrequired;
              ysteptimer = estepsrequired / ystepsrequired;
              zsteptimer = estepsrequired / zstepsrequired;
              // IF IT IS NONE OF THE ABOVE, ERROR OUT
            } else {
              Serial.println(F("NEW COMMAND FOUND BUT COULD NOT BE SET!"));
              writeerrorsstackloop("E-M102: G FOUND BUT COULD NOT BE SET", 3, true, 0, true, true);
            }
          }
        }
      }
    }
  }
  // NEW COMMAND CALLED BUT NONE RECEIVED
  else {
    if (checklockstatus(currentgcodecommand) != 1) {
      printingactive = false;
    } 
    if (conditionsmetX == false) {
      xstepsrequired = xstepsrequired + 1;
    }
    if (conditionsmetY == false) {
      ystepsrequired = ystepsrequired + 1;
    }
    if (conditionsmetZ == false) {
      zstepsrequired = zstepsrequired + 1;
    }
    if (conditionsmetE == false) {
      estepsrequired = estepsrequired + 1;
    }
  }


  Serial.print(F("INFO: "));
  Serial.print(currentxdimension);
  Serial.print(F(" / "));
  Serial.print(targetxdimension);
  Serial.println(F(""));
  Serial.print(xstepsrequired);
  Serial.print(F(" "));
  Serial.print(ystepsrequired);
  Serial.print(F(" "));
  Serial.print(zstepsrequired);
  Serial.print(F(" "));
  Serial.println(estepsrequired);
  Serial.println(F(""));
  Serial.print(xmovingpositive);
  Serial.print(F(" "));
  Serial.print(xmovingnegative);
  Serial.print(F(" "));
  Serial.print(ymovingpositive);
  Serial.print(F(" "));
  Serial.print(ymovingnegative);
  Serial.print(F(" "));
  Serial.print(zmovingpositive);
  Serial.print(F(" "));
  Serial.print(zmovingnegative);
  Serial.print(F(" "));
  Serial.print(e0movingpositive);
  Serial.print(F(" "));
  Serial.print(e0movingnegative);
}



// CHECK NEXT LOCK STATUS LOOP TO DETERMINE IF NEXT GCODE IS READY OR NOT

int checklockstatus(int inputnumberstatus) {
  if (inputnumberstatus <= 9) {
    inputnumberstatus = inputnumberstatus + 1;
  } else {
    inputnumberstatus = 0;
  }
  return (readfromarray(inputnumberstatus, 10));
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

// ENDSTOPS
void endstops() {
  bool xcurrentend = digitalRead(X_MIN_PIN);
  bool ycurrentend = digitalRead(Y_MIN_PIN);
  bool zcurrentend = digitalRead(Z_MIN_PIN);

  // X MOTOR ENDSTOP
  if (xcurrentend != xendsetup) {
    xendstopminactive = true;
    // Serial.println(F("active"));
  } else {
    xendstopminactive = false;
    // Serial.println(F("not active"));
  }

  // Y MOTOR ENDSTOP
  if (ycurrentend != yendsetup) {
    yendstopmaxactive = true;
  } else {
    yendstopmaxactive = false;
  }

  // Z MOTOR ENDSTOP
  if (zcurrentend != zendsetup) {
    zendstopminactive = true;
  } else {
    zendstopminactive = false;
  }
}

// HOME ALL STEPPER MOTORS
void homeall() {
  xhome();
  yhome();
  zhome();

  xmovingnegative = false;
  xmovingpositive = false;
  ymovingnegative = false;
  ymovingpositive = false;
  zmovingnegative = false;
  zmovingpositive = false;
  e0movingnegative = false;
  e0movingpositive = false;
  printingactive = false;
}

// HOME X-AXIS
void xhome() {

  // SET VARIABLES
  currentxdimension = 0;
  targetxdimension = 0;
  printingactive = true;
  steppermotorsdisabled = false;
  xdisabled = false;

  // DECLARE VARIABLES
  bool finishedhomingx = false;
  bool finishedhomingy = false;
  bool finishedhomingz = false;
  bool xendstophitonce = false;
  bool yendstophitonce = false;
  bool zendstophitonce = false;
  bool xcompletion = false;
  bool ycompletion = false;
  bool zcompletion = false;
  bool xoutward = false;
  bool youtward = false;
  bool zoutward = false;
  int numberoftimeshoming = 0;
  int xtiming1000 = 0;
  int ytiming1000 = 0;
  int ztiming1000 = 0;

  // DETERMINE DIRECTIONAL PINS, ETC.
  digitalWrite(X_ENABLE_PIN, LOW);
  digitalWrite(X_DIR_PIN, LOW);
  if (watchdogactivated == true) {
    Serial.println(F("can't home x axis"));
    Serial.println(F("ok"));
  } else {

    // VERIFY ENDSTOP POSITION
    while (numberoftimeshoming <= 30000 && finishedhomingx == false) {

      endstops();
      eSERIALRECEIVER();

      // X HOMING SCRIPT
      if (xoutward == false) {
        if (finishedhomingx == false) {
          if (xendstopminactive == true) {
            if (xendstophitonce == true) {
              digitalWrite(X_DIR_PIN, LOW);
              digitalWrite(X_STEP_PIN, LOW);
              finishedhomingx = true;
            } else {
              xoutward = true;
            }
          } else {

            // CONTINUE MOVING TO ZERO FIRST TIME
            if (finishedhomingx != true) {
              digitalWrite(X_DIR_PIN, LOW);
              digitalWrite(X_STEP_PIN, HIGH);
              if (debugserial == true) {
                Serial.println(numberoftimeshoming);
              }
            }
          }
        } else {
          if (xendstopminactive == false) {
            Serial.println(F("NOT AT HOME AFTER HOMING ERROR (X)"));
            writeerrorsstackloop("X NOT AT HOME ERROR", 3, false, 0, false, false);
          } else {
            digitalWrite(X_DIR_PIN, LOW);
            digitalWrite(X_STEP_PIN, LOW);
            finishedhomingx = true;
          }
        }
      } else {
        digitalWrite(X_DIR_PIN, HIGH);
        digitalWrite(X_STEP_PIN, HIGH);
        xtiming1000 = xtiming1000 + 1;
        if (xtiming1000 >= 1500) {
          xoutward = false;
          xendstophitonce = true;
          xtiming1000 = 0;
        }
      }

      delayMicroseconds(500);
      numberoftimeshoming = numberoftimeshoming + 1;


      // TURN ALL STEP PINS TO LOW
      digitalWrite(X_STEP_PIN, LOW);

      if (watchdogactivated == true) {
        Serial.println(F("stopping homing"));
        Serial.println(F("ok"));
      }
    }


    delayMicroseconds(200);
    numberoftimeshoming = numberoftimeshoming + 1;


    // TURN ALL STEP PINS TO LOW
    digitalWrite(X_STEP_PIN, LOW);

    if (watchdogactivated == true) {
      Serial.println(F("stopping homing"));
      Serial.println(F("ok"));
    }
  }


  printingactive = false;
}

// HOME Y-AXIS
void yhome() {

  // SET VARIABLES
  currentydimension = 200;
  targetydimension = 200;
  printingactive = true;

  steppermotorsdisabled = false;
  ydisabled = false;

  // DECLARE VARIABLES
  bool finishedhomingx = false;
  bool finishedhomingy = false;
  bool finishedhomingz = false;
  bool xendstophitonce = false;
  bool yendstophitonce = false;
  bool zendstophitonce = false;
  bool xcompletion = false;
  bool ycompletion = false;
  bool zcompletion = false;
  bool xoutward = false;
  bool youtward = false;
  bool zoutward = false;
  int numberoftimeshoming = 0;
  int xtiming1000 = 0;
  int ytiming1000 = 0;
  int ztiming1000 = 0;

  // DETERMINE DIRECTIONAL PINS, ETC.
  digitalWrite(Y_ENABLE_PIN, LOW);
  digitalWrite(Y_DIR_PIN, LOW);

  if (watchdogactivated == true) {
    Serial.println(F("can't home y axis"));
    Serial.println(F("ok"));
  } else {

    // VERIFY ENDSTOP POSITION
    while (numberoftimeshoming <= 30000 && finishedhomingy == false) {

      endstops();
      eSERIALRECEIVER();

      // Y HOMING SCRIPT
      if (youtward == false) {
        if (finishedhomingy == false) {
          if (yendstopmaxactive == true) {
            if (yendstophitonce == true) {
              digitalWrite(Y_DIR_PIN, HIGH);
              digitalWrite(Y_STEP_PIN, LOW);
              finishedhomingy = true;
            } else {
              youtward = true;
            }
          } else {

            // CONTINUE MOVING TO ZERO FIRST TIME
            if (finishedhomingy != true) {
              digitalWrite(Y_DIR_PIN, LOW);
              digitalWrite(Y_STEP_PIN, HIGH);
              if (debugserial == true) {
                Serial.println(numberoftimeshoming);
              }
            }
          }
        } else {
          if (yendstopminactive == false) {
            Serial.println(F("NOT AT HOME AFTER HOMING ERROR (Y)"));
            writeerrorsstackloop("Y NOT AT HOME ERROR", 3, false, 0, false, false);
          } else {
            digitalWrite(Y_DIR_PIN, LOW);
            digitalWrite(Y_STEP_PIN, LOW);
            finishedhomingy = true;
          }
        }
      } else {
        digitalWrite(Y_DIR_PIN, HIGH);
        digitalWrite(Y_STEP_PIN, LOW);
        ytiming1000 = ytiming1000 + 1;
        if (ytiming1000 >= 500) {
          youtward = false;
          yendstophitonce = true;
          ytiming1000 = 0;
        }
      }

      delayMicroseconds(200);
      numberoftimeshoming = numberoftimeshoming + 1;


      // TURN ALL STEP PINS TO LOW
      digitalWrite(Y_STEP_PIN, LOW);

      if (watchdogactivated == true) {
        Serial.println(F("stopping homing"));
        Serial.println(F("ok"));
      }
    }
    digitalWrite(Y_STEP_PIN, LOW);
  }

  printingactive = false;
}

// HOME Z-AXIS
void zhome() {

  // SET VARIABLES
  currentzdimension = 0;
  targetzdimension = 0;
  printingactive = true;

  steppermotorsdisabled = false;
  zdisabled = false;

  // DECLARE VARIABLES
  bool finishedhomingx = false;
  bool finishedhomingy = false;
  bool finishedhomingz = false;
  bool xendstophitonce = false;
  bool yendstophitonce = false;
  bool zendstophitonce = false;
  bool xcompletion = false;
  bool ycompletion = false;
  bool zcompletion = false;
  bool xoutward = false;
  bool youtward = false;
  bool zoutward = false;
  int numberoftimeshoming = 0;
  int xtiming1000 = 0;
  int ytiming1000 = 0;
  int ztiming1000 = 0;

  // DETERMINE DIRECTIONAL PINS, ETC.
  digitalWrite(Z_ENABLE_PIN, LOW);
  digitalWrite(Z_DIR_PIN, HIGH);

  if (watchdogactivated == true) {
    Serial.println(F("can't home z axis"));
    Serial.println(F("ok"));
  } else {

    // VERIFY ENDSTOP POSITION
    while (numberoftimeshoming <= 50000 && finishedhomingz == false) {

      endstops();
      eSERIALRECEIVER();

      // Z HOMING SCRIPT
      if (zoutward == false) {
        if (finishedhomingz == false) {
          if (zendstopminactive == true) {
            if (zendstophitonce == true) {
              digitalWrite(Z_DIR_PIN, LOW);
              digitalWrite(Z_STEP_PIN, LOW);
              finishedhomingz = true;
            } else {
              zoutward = true;
            }
          } else {

            // CONTINUE MOVING TO ZERO FIRST TIME
            if (finishedhomingz != true) {
              digitalWrite(Z_DIR_PIN, HIGH);
              digitalWrite(Z_STEP_PIN, HIGH);
              if (debugserial == true) {
                Serial.println(numberoftimeshoming);
              }
            }
          }
        } else {
          if (zendstopminactive == false) {
            Serial.println(F("NOT AT HOME AFTER HOMING ERROR (Z)"));
            writeerrorsstackloop("Z NOT AT HOME ERROR", 3, false, 0, false, false);
          } else {
            digitalWrite(Z_DIR_PIN, HIGH);
            digitalWrite(Z_STEP_PIN, LOW);
            finishedhomingz = true;
          }
        }
      } else {
        digitalWrite(Z_DIR_PIN, LOW);
        digitalWrite(Z_STEP_PIN, LOW);
        ztiming1000 = ztiming1000 + 1;
        if (ztiming1000 >= 500) {
          zoutward = false;
          zendstophitonce = true;
          ztiming1000 = 0;
        }
      }


      // TURN ALL STEP PINS TO LOW
      digitalWrite(Z_STEP_PIN, LOW);

      delayMicroseconds(100);
      numberoftimeshoming = numberoftimeshoming + 1;

      if (watchdogactivated == true) {
        Serial.println(F("stopping homing"));
        Serial.println(F("ok"));
      }
    }
  }
  printingactive = false;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

// DEMO MODE
void demomode() {
}