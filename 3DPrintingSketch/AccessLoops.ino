/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

// DATABASE (ARRAY) ACCESS LOOPS!

// SEND A FLOAT VALUE TO THE MASTER ARRAY // 0 = GOOD / 1 = BAD
int sendtoarray(int commandtoanalyze, float valuetoinsert, int positiontoinsert) {
  switch (commandtoanalyze) {
    case 0:
      if ((analyzedgcodestack0[10] == 0 || analyzedgcodestack0[10] == 2) && analyzedgcodestack0[positiontoinsert] == 0) {
        analyzedgcodestack0[positiontoinsert] = valuetoinsert;
        return(0);
      } else {
        Serial.println(F("READ-ONLY ARRAY ACCESS DENIED (CACHE-0)!"));
        i2csend("READ-ONLY ARRAY ACCESS DENIED (CACHE-0)!", "", "", 0);
        return(1);
      }
      break;
    case 1:
      if ((analyzedgcodestack1[10] == 0 || analyzedgcodestack1[10] == 2) && analyzedgcodestack1[positiontoinsert] == 0) {
        analyzedgcodestack1[positiontoinsert] = valuetoinsert;
        return(0);
      } else {
        Serial.println(analyzedgcodestack1[positiontoinsert]);
        Serial.println(F("READ-ONLY ARRAY ACCESS DENIED (CACHE-1)!"));
        i2csend("READ-ONLY ARRAY ACCESS DENIED (CACHE-1)!", "", "", 0);
        return(1);
      }
      break;
    case 2:
      if ((analyzedgcodestack2[10] == 0 || analyzedgcodestack2[10] == 2) && analyzedgcodestack2[positiontoinsert] == 0) {
        analyzedgcodestack2[positiontoinsert] = valuetoinsert;
        return(0);
      } else {
        Serial.println(F("READ-ONLY ARRAY ACCESS DENIED (CACHE-2)!"));
        i2csend("READ-ONLY ARRAY ACCESS DENIED (CACHE-2)!", "", "", 0);
        return(1);
      }
      break;
    case 3:
      if ((analyzedgcodestack3[10] == 0 || analyzedgcodestack3[10] == 2) && analyzedgcodestack3[positiontoinsert] == 0) {
        analyzedgcodestack3[positiontoinsert] = valuetoinsert;
        return(0);
      } else {
        Serial.println(F("READ-ONLY ARRAY ACCESS DENIED (CACHE-3)!"));
        i2csend("READ-ONLY ARRAY ACCESS DENIED (CACHE-3)!", "", "", 0);
        return(1);
      }
      break;
    case 4:
      if ((analyzedgcodestack4[10] == 0 || analyzedgcodestack4[10] == 2) && analyzedgcodestack4[positiontoinsert] == 0) {
        analyzedgcodestack4[positiontoinsert] = valuetoinsert;
        return(0);
      } else {
        Serial.println(F("READ-ONLY ARRAY ACCESS DENIED (CACHE-4)!"));
        i2csend("READ-ONLY ARRAY ACCESS DENIED (CACHE-4)!", "", "", 0);
        return(1);
      }
      break;
    case 5:
      if ((analyzedgcodestack5[10] == 0 || analyzedgcodestack5[10] == 2) && analyzedgcodestack5[positiontoinsert] == 0) {
        analyzedgcodestack5[positiontoinsert] = valuetoinsert;
        return(0);
      } else {
        Serial.println(F("READ-ONLY ARRAY ACCESS DENIED (CACHE-5)!"));
        i2csend("READ-ONLY ARRAY ACCESS DENIED (CACHE-5)!", "", "", 0);
        return(1);
      }
      break;
    case 6:
      if ((analyzedgcodestack6[10] == 0 || analyzedgcodestack6[10] == 2) && analyzedgcodestack6[positiontoinsert] == 0) {
        analyzedgcodestack6[positiontoinsert] = valuetoinsert;
        return(0);
      } else {
        Serial.println(F("READ-ONLY ARRAY ACCESS DENIED (CACHE-6)!"));
        i2csend("READ-ONLY ARRAY ACCESS DENIED (CACHE-6)!", "", "", 0);
        return(1);
      }
      break;
    case 7:
      if ((analyzedgcodestack7[10] == 0 || analyzedgcodestack7[10] == 2) && analyzedgcodestack7[positiontoinsert] == 0) {
        analyzedgcodestack7[positiontoinsert] = valuetoinsert;
        return(0);
      } else {
        Serial.println(F("READ-ONLY ARRAY ACCESS DENIED (CACHE-7)!"));
        i2csend("READ-ONLY ARRAY ACCESS DENIED (CACHE-7)!", "", "", 0);
        return(1);
      }
      break;
    case 8:
      if ((analyzedgcodestack8[10] == 0 || analyzedgcodestack8[10] == 2) && analyzedgcodestack8[positiontoinsert] == 0) {
        analyzedgcodestack8[positiontoinsert] = valuetoinsert;
        return(0);
      } else {
        Serial.println(F("READ-ONLY ARRAY ACCESS DENIED (CACHE-8)!"));
        i2csend("READ-ONLY ARRAY ACCESS DENIED (CACHE-8)!", "", "", 0);
        return(1);
      }
      break;
    case 9:
      if ((analyzedgcodestack9[10] == 0 || analyzedgcodestack9[10] == 2) && analyzedgcodestack9[positiontoinsert] == 0) {
        analyzedgcodestack9[positiontoinsert] = valuetoinsert;
        return(0);
      } else {
        Serial.println(F("READ-ONLY ARRAY ACCESS DENIED (CACHE-9)!"));
        i2csend("READ-ONLY ARRAY ACCESS DENIED (CACHE-9)!", "", "", 0);
        return(1);
      }
      break;
    case 10:
      if ((analyzedgcodestack10[10] == 0 || analyzedgcodestack10[10] == 2) && analyzedgcodestack10[positiontoinsert] == 0) {
        analyzedgcodestack10[positiontoinsert] = valuetoinsert;
        return(0);
      } else {
        Serial.println(F("READ-ONLY ARRAY ACCESS DENIED (CACHE-10)!"));
        i2csend("READ-ONLY ARRAY ACCESS DENIED (CACHE-10)!", "", "", 0);
        return(1);
      }
      break;
  }
}

// READ A FLOAT VALUE FROM THE MASTER ARRAY
float readfromarray(int commandtoread, int positiontoread) {
  switch (commandtoread) {
    case 0:
      return (analyzedgcodestack0[positiontoread]);
      break;
    case 1:
      return (analyzedgcodestack1[positiontoread]);
      break;
    case 2:
      return (analyzedgcodestack2[positiontoread]);
      break;
    case 3:
      return (analyzedgcodestack3[positiontoread]);
      break;
    case 4:
      return (analyzedgcodestack4[positiontoread]);
      break;
    case 5:
      return (analyzedgcodestack5[positiontoread]);
      break;
    case 6:
      return (analyzedgcodestack6[positiontoread]);
      break;
    case 7:
      return (analyzedgcodestack7[positiontoread]);
      break;
    case 8:
      return (analyzedgcodestack8[positiontoread]);
      break;
    case 9:
      return (analyzedgcodestack9[positiontoread]);
      break;
    case 10:
      return (analyzedgcodestack10[positiontoread]);
      break;
  }
}

// CLEAR A ROW OF VALUES IN THE MASTER ARRAY
void clearrowinarray(int commandtoclear, bool removelock) {
  int timer = 0;
  switch (commandtoclear) {
    case 0:
      while (timer <= 11) {
        analyzedgcodestack0[timer] = 00.0000;
        timer = timer + 1;
      }
      if (removelock == true) {
        analyzedgcodestack0[11] = 0;
      }
      break;
    case 1:
      while (timer <= 11) {
        analyzedgcodestack1[timer] = 00.0000;
        timer = timer + 1;
      }
      break;
    case 2:
      while (timer <= 11) {
        analyzedgcodestack2[timer] = 00.0000;
        timer = timer + 1;
      }
      break;
    case 3:
      while (timer <= 11) {
        analyzedgcodestack3[timer] = 00.0000;
        timer = timer + 1;
      }
      break;
    case 4:
      while (timer <= 11) {
        analyzedgcodestack4[timer] = 00.0000;
        timer = timer + 1;
      }
      break;
    case 5:
      while (timer <= 11) {
        analyzedgcodestack5[timer] = 00.0000;
        timer = timer + 1;
      }
      break;
    case 6:
      while (timer <= 11) {
        analyzedgcodestack6[timer] = 00.0000;
        timer = timer + 1;
      }
      break;
    case 7:
      while (timer <= 11) {
        analyzedgcodestack7[timer] = 00.0000;
        timer = timer + 1;
      }
      break;
    case 8:
      while (timer <= 11) {
        analyzedgcodestack8[timer] = 00.0000;
        timer = timer + 1;
      }
      break;
    case 9:
      while (timer <= 11) {
        analyzedgcodestack9[timer] = 00.0000;
        timer = timer + 1;
      }
      break;
    case 10:
      while (timer <= 11) {
        analyzedgcodestack10[timer] = 00.0000;
        timer = timer + 1;
      }
      break;
  }
}

// FULL DATABASE READ FOR DEBUGGING PURPOSES
void fulldatabaseread() {
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
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

// STACK ACCESS LOOPS!

// READ A CHARACTER FROM THE STACK
String readcharactersfromstack(int commandtoanalyze, int charactertoanalyze, int characterend) {
  switch (commandtoanalyze) {
    case 0:
      character = gcodestack0.substring(charactertoanalyze, charactertoanalyze + 1);
      break;
    case 1:
      character = gcodestack1.substring(charactertoanalyze, charactertoanalyze + 1);
      break;
    case 2:
      character = gcodestack2.substring(charactertoanalyze, charactertoanalyze + 1);
      break;
    case 3:
      character = gcodestack3.substring(charactertoanalyze, charactertoanalyze + 1);
      break;
    case 4:
      character = gcodestack4.substring(charactertoanalyze, charactertoanalyze + 1);
      break;
    case 5:
      character = gcodestack5.substring(charactertoanalyze, charactertoanalyze + 1);
      break;
    case 6:
      character = gcodestack6.substring(charactertoanalyze, charactertoanalyze + 1);
      break;
    case 7:
      character = gcodestack7.substring(charactertoanalyze, charactertoanalyze + 1);
      break;
    case 8:
      character = gcodestack8.substring(charactertoanalyze, charactertoanalyze + 1);
      break;
    case 9:
      character = gcodestack9.substring(charactertoanalyze, charactertoanalyze + 1);
      break;
    case 10:
      character = gcodestack10.substring(charactertoanalyze, charactertoanalyze + 1);
      break;
  }
}

// READ THE STRING FROM THE STACK
String readstringsfromstack(int commandtoanalyze) {
  switch (commandtoanalyze) {
    case 0:
      stringfromstack = gcodestack0;
      break;
    case 1:
      stringfromstack = gcodestack1;
      break;
    case 2:
      stringfromstack = gcodestack2;
      break;
    case 3:
      stringfromstack = gcodestack3;
      break;
    case 4:
      stringfromstack = gcodestack4;
      break;
    case 5:
      stringfromstack = gcodestack5;
      break;
    case 6:
      stringfromstack = gcodestack6;
      break;
    case 7:
      stringfromstack = gcodestack7;
      break;
    case 8:
      stringfromstack = gcodestack8;
      break;
    case 9:
      stringfromstack = gcodestack9;
      break;
    case 10:
      stringfromstack = gcodestack10;
      break;
  }
}

// CLEAR A STRING FROM THE STACK
void clearstringinstack(int commandtoanalyze, bool replacetoQNN) {
  switch (commandtoanalyze) {
    case 0:
      if (replacetoQNN == true) {
        gcodestack0 = "QNNNNNNNNNNNNNNNNNNNNNNNNN";
      } else {
        gcodestack0 = "";
      }
      break;
    case 1:
      if (replacetoQNN == true) {
        gcodestack1 = "QNNNNNNNNNNNNNNNNNNNNNNNNN";
      } else {
        gcodestack1 = "";
      }
      break;
    case 2:
      if (replacetoQNN == true) {
        gcodestack2 = "QNNNNNNNNNNNNNNNNNNNNNNNNN";
      } else {
        gcodestack2 = "";
      }
      break;
    case 3:
      if (replacetoQNN == true) {
        gcodestack3 = "QNNNNNNNNNNNNNNNNNNNNNNNNN";
      } else {
        gcodestack3 = "";
      }
      break;
    case 4:
      if (replacetoQNN == true) {
        gcodestack4 = "QNNNNNNNNNNNNNNNNNNNNNNNNN";
      } else {
        gcodestack4 = "";
      }
      break;
    case 5:
      if (replacetoQNN == true) {
        gcodestack5 = "QNNNNNNNNNNNNNNNNNNNNNNNNN";
      } else {
        gcodestack5 = "";
      }
      break;
    case 6:
      if (replacetoQNN == true) {
        gcodestack6 = "QNNNNNNNNNNNNNNNNNNNNNNNNN";
      } else {
        gcodestack6 = "";
      }
      break;
    case 7:
      if (replacetoQNN == true) {
        gcodestack7 = "QNNNNNNNNNNNNNNNNNNNNNNNNN";
      } else {
        gcodestack7 = "";
      }
      break;
    case 8:
      if (replacetoQNN == true) {
        gcodestack8 = "QNNNNNNNNNNNNNNNNNNNNNNNNN";
      } else {
        gcodestack8 = "";
      }
      break;
    case 9:
      if (replacetoQNN == true) {
        gcodestack9 = "QNNNNNNNNNNNNNNNNNNNNNNNNN";
      } else {
        gcodestack9 = "";
      }
      break;
    case 10:
      if (replacetoQNN == true) {
        gcodestack10 = "QNNNNNNNNNNNNNNNNNNNNNNNNN";
      } else {
        gcodestack10 = "";
      }
      break;
  }
}

// WRITE A STRING TO THE STACK
void writestringtostack(int commandtoanalyze, String stringvaluetoinsert) {
  switch (commandtoanalyze) {
    case 0:
      gcodestack0 = stringvaluetoinsert;
      break;
    case 1:
      gcodestack1 = stringvaluetoinsert;
      break;
    case 2:
      gcodestack2 = stringvaluetoinsert;
      break;
    case 3:
      gcodestack3 = stringvaluetoinsert;
      break;
    case 4:
      gcodestack4 = stringvaluetoinsert;
      break;
    case 5:
      gcodestack5 = stringvaluetoinsert;
      break;
    case 6:
      gcodestack6 = stringvaluetoinsert;
      break;
    case 7:
      gcodestack7 = stringvaluetoinsert;
      break;
    case 8:
      gcodestack8 = stringvaluetoinsert;
      break;
    case 9:
      gcodestack9 = stringvaluetoinsert;
      break;
    case 10:
      gcodestack10 = stringvaluetoinsert;
      break;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

// ERROR STACK LOOPS!

// LOGS ERRORS INTO A STRING STACK
void writeerrorsstackloop(String errortoinput, int severity, bool activatewatchdog, int errornumber, bool overflowtowatchdog, bool repeats) {
  if (errorstack0 != "ZNONE" || errorstack0 != "") {
    if (errorstack1 != "ZNONE" || errorstack1 != "") {
      if (errorstack2 != "ZNONE" || errorstack2 != "") {
        if (errorstack3 != "ZNONE" || errorstack3 != "") {
          if (errorstack4 != "ZNONE" || errorstack4 != "") {
            if (errorstack5 != "ZNONE" || errorstack5 != "") {
              if (errorstack6 != "ZNONE" || errorstack6 != "") {
                if (errorstack7 != "ZNONE" || errorstack7 != "") {
                  if (errorstack8 != "ZNONE" || errorstack8 != "") {
                    if (errorstack9 != "ZNONE" || errorstack9 != "") {
                      if (errorstack10 != "ZNONE" || errorstack10 != "") {
                        //                        Serial.println(F("OVERFLOW ERROR!"));
                        if (overflowtowatchdog == true) {
                          watchdogactivated = true;
                          //                          Serial.println(F("OVERFLOW ERROR!"));
                          errorstack10 = "OVERFLOW ERROR IN ERROR LOOP!";
                        }
                      } else {
                        // WRITE TO ERROR STACK TEN
                        errorstack10 = errortoinput;
                      }
                    } else {
                      // WRITE TO ERROR STACK NINE
                      errorstack9 = errortoinput;
                    }
                  } else {
                    // WRITE TO ERROR STACK EIGHT
                    errorstack8 = errortoinput;
                  }
                } else {
                  // WRITE TO ERROR STACK SEVEN
                  errorstack7 = errortoinput;
                }
              } else {
                // WRITE TO ERROR STACK SIX
                errorstack6 = errortoinput;
              }
            } else {
              // WRITE TO ERROR STACK FIVE
              errorstack5 = errortoinput;
            }
          } else {
            // WRITE TO ERROR STACK FOUR
            errorstack4 = errortoinput;
          }
        } else {
          // WRITE TO ERROR STACK THREE
          errorstack3 = errortoinput;
        }
      } else {
        // WRITE TO ERROR STACK TWO
        errorstack2 = errortoinput;
      }
    } else {
      // WRITE TO ERROR STACK ONE
      errorstack1 = errortoinput;
    }
  } else {
    // WRITE TO ERROR STACK ZERO
    errorstack0 = errortoinput;
  }
}

// READ ERRORS FROM THE STRING STACK OR REPORT "OK"
String readerrorsstackloop(int stacknumbertoread) {
  switch (stacknumbertoread) {
    case 0:
      readerrorfromstack = errorstack0;
      break;
    case 1:
      readerrorfromstack = errorstack1;
      break;
    case 2:
      readerrorfromstack = errorstack2;
      break;
    case 3:
      readerrorfromstack = errorstack3;
      break;
    case 4:
      readerrorfromstack = errorstack4;
      break;
    case 5:
      readerrorfromstack = errorstack5;
      break;
    case 6:
      readerrorfromstack = errorstack6;
      break;
    case 7:
      readerrorfromstack = errorstack7;
      break;
    case 8:
      readerrorfromstack = errorstack8;
      break;
    case 9:
      readerrorfromstack = errorstack9;
      break;
    case 10:
      readerrorfromstack = errorstack10;
      break;
  }
}

// CLEAR ALL RECOVERABLE ERRORS FROM THE LOG
void clearerrorsstackloop(int stacknumbertoclear) {
  switch (stacknumbertoclear) {
    case 0:
      errorstack0 = "";
      break;
    case 1:
      errorstack1 = "";
      break;
    case 2:
      errorstack2 = "";
      break;
    case 3:
      errorstack3 = "";
      break;
    case 4:
      errorstack4 = "";
      break;
    case 5:
      errorstack5 = "";
      break;
    case 6:
      errorstack6 = "";
      break;
    case 7:
      errorstack7 = "";
      break;
    case 8:
      errorstack8 = "";
      break;
    case 9:
      errorstack9 = "";
      break;
    case 10:
      errorstack10 = "";
      break;
  }
}