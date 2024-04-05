/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////



// EMERGENCY PARSER WITH SELECT M/Z COMMANDS
int ePARSER(String commanding) {
  // SELECT M/Z CODE COMMANDS
  bool interpretedcompleted = false;

  // DETERMINE THE FIRST LETTER OF THE STRING
  String firstletter = commanding.substring(0, 1);

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

  // IF COMMAND STARTS WITH " ", REMOVE THE FRONT SPACE AND RESTART INTERPRETATION
  if (firstletter == " ") {
    interpretation(commanding.substring(1, 255));
    interpretedcompleted = true;
  }

  // EMERGENCY COMMANDS - SEND IMMEDIATELY TO MAIN LOOP
  if (firstletter == "E") {
    eShell(commanding);
  }

  // MODIFIER COMMANDS - DON'T TAKE LONG, RUN ANYWAY
  if (firstletter == "M") {
    mShell(commanding);
  }

  // IF COMMAND IS NOT RECOGNIZED IMMEDIATELY, SEND TO ECACHE TO BE CACHED AT END
  if (interpretedcompleted == false) {
    switch (numberinecache) {
      case 0:
        ecache0 = commanding;
        toecache = true;
        numberinecache = 1;
        Serial.println(F("ok"));
        return (3);
        break;
      case 1:
        ecache1 = commanding;
        toecache = true;
        numberinecache = 2;
        Serial.println(F("ok"));
        return (3);
        break;
      case 2:
        ecache2 = commanding;
        toecache = true;
        numberinecache = 3;
        Serial.println(F("ok"));
        return (3);
        break;
      case 3:
        ecache3 = commanding;
        toecache = true;
        numberinecache = 4;
        Serial.println(F("ok"));
        return (3);
        break;
      case 4:
        ecache4 = commanding;
        toecache = true;
        numberinecache = 5;
        Serial.println(F("ok"));
        return (3);
        break;
      case 5:
        Serial.println(F("ECACHE FULL! - TRUNKATING LAST COMMAND!"));
        Serial.println(F("ok"));
        return (5);
    }
  }
  return (1);
}

// ANALYZE THE ECACHE AND ESTACKS
int processECACHE() {
  if (toecache == true) {
    // IF CACHE HAS BEEN STORED, ANALYZE THAT HERE
    Serial.println(F("CLEARING E-CACHE!"));
    switch (numberinecache) {
      case 0:
        // ERROR EMPTY CASE
        Serial.println(F("ERROR E-201! EMPTY INTEGER FOUND IN ECACHE!"));
        watchdogactivated = true;
        numberinecache = 0;
        toecache = false;
        break;
      case 1:
        interpretation(readerrorsstackloop(0));
        clearerrorsstackloop(0);
        numberinecache = 0;
        toecache = false;
        break;
      case 2:
        interpretation(readerrorsstackloop(0));
        interpretation(readerrorsstackloop(1));
        clearerrorsstackloop(0);
        clearerrorsstackloop(1);
        numberinecache = 0;
        toecache = false;
        break;
      case 3:
        interpretation(readerrorsstackloop(0));
        interpretation(readerrorsstackloop(1));
        interpretation(readerrorsstackloop(2));
        clearerrorsstackloop(0);
        clearerrorsstackloop(1);
        clearerrorsstackloop(2);
        numberinecache = 0;
        toecache = false;
        break;
      case 4:
        interpretation(readerrorsstackloop(0));
        interpretation(readerrorsstackloop(1));
        interpretation(readerrorsstackloop(2));
        interpretation(readerrorsstackloop(3));
        clearerrorsstackloop(0);
        clearerrorsstackloop(1);
        clearerrorsstackloop(2);
        clearerrorsstackloop(3);
        numberinecache = 0;
        toecache = false;
        break;
      case 5:
        interpretation(readerrorsstackloop(0));
        interpretation(readerrorsstackloop(1));
        interpretation(readerrorsstackloop(2));
        interpretation(readerrorsstackloop(3));
        interpretation(readerrorsstackloop(4));
        clearerrorsstackloop(0);
        clearerrorsstackloop(1);
        clearerrorsstackloop(2);
        clearerrorsstackloop(3);
        clearerrorsstackloop(4);
        numberinecache = 0;
        toecache = false;
        break;
    }
  }
}

// MODIFIER COMMANDS NEW SHELL FOR BOTH ePARSER() and interpretation()
int mShell(String commanding) {

  bool interpretedcompleted = false;

  // DETERMINE FIRST LETTER
  String firstletter = commanding.substring(0, 1);

  // IF COMMAND STARTS WITH M, EVALUATE WHAT IT ACTUALLY MEANS
  if (firstletter == "M") {

    // DETERMINE THE SECOND LETTER OF THE STRING
    firstletter = commanding.substring(1, 2);

    // M0 - UNCONDITIONAL STOP
    if (firstletter == "0") {
      timeinwatchdoginseconds = -1;
      watchdogactivated = true;
      Serial.println(F("WATCHDOG ACTIVATED!"));
      Serial.println(F("SHUTTING DOWN..."));
      return;
      return;
      return;
    }

    // IF IT IS "M1*", CONTINUE ON EVALUATING
    if (firstletter == "1") {

      // DETERMINE THE SECOND LETTER OF THE STRING
      firstletter = commanding.substring(2, 3);

      // M1 - CONDITIONAL STOP
      if (firstletter == "" || firstletter == " ") {
        firstletter = commanding.substring(3, 6);
        if (firstletter == "") {
          timeinwatchdoginseconds = 300;
        } else {
          timeinwatchdoginseconds = firstletter.toInt();
        }
        watchdogactivated = true;
        Serial.println(F("CONDITIONAL STOP"));
        Serial.println(F("ok"));
        return;
        return;
        return;
      }

      // M10*
      if (firstletter == "0") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M103 - TURN ALL EXTRUDERS OFF, EXTRUDER RETRACTION
        if (firstletter == "3") {
          extruderemergencyretraction();
          targete0temp = 0.0;
          targete1temp = 0.0;
          extrudersactive = false;
          Serial.println(F("ok"));
          return;
          return;
          return;
        }

        // M104 - SET EXTRUDER TEMPERATURE
        if (firstletter == "4") {

          // DETERMINE IF ARGS ARE PASSED
          firstletter = commanding.substring(4, 5);
          if (firstletter == " ") {
            // CONTINUE ON SETTING TEMPERATURE
            String extemp = commanding.substring(5, 100);
            if (currentactiveextruder == 0) {
              targete0temp = extemp.toFloat();
              Serial.println(F("ok"));
              return;
              return;
              return;
            }
            if (currentactiveextruder == 1) {
              targete1temp = extemp.toFloat();
              Serial.println(F("ok"));
              return;
              return;
              return;
            }
            Serial.println(F("INVALID EXTRUDER ACTIVE!"));
            return;
            return;
            return;
          } else {
            Serial.println(F("NO ARGS PASSED! - TYPE EXTRUDER HEAT"));
            return;
            return;
            return;
          }
        }

        // M105 - GET EXTRUDER TEMPERATURE
        if (firstletter == "5") {
          /* - `T:` - Hotend (actual / target)
        - `B:` - Bed (actual / target)
        - `Tx:` - x Tool (actual / target)
        - `@:` - Hotend power
        - `B@:` - Bed power
        - `P:` - PINDAv2 actual (only MK2.5/s and MK3/s)
        - `A:` - Ambient actual (only MK3/s)
        
        _Example:_
        
        ok T:20.2 /0.0 B:19.1 /0.0 T0:20.2 /0.0 @:0 B@:0 P:19.8 A:26.4
        */
          Serial.print(F("T:"));
          Serial.print(currente0temp);
          Serial.print(F(" /"));
          Serial.print(targete0temp);
          Serial.print(F(" B:"));
          Serial.print(currenthbtemp);
          Serial.print(F(" /"));
          Serial.print(targethbtemp);
          Serial.println(F(" @:0 B@:0"));
          Serial.println(F("ok"));
          interpretedcompleted = true;
          return;
          return;
          return;
        }

        // M106 - EXTRUDER FAN ON
        if (firstletter == "6") {
          exfanpowerstate = true;
          Serial.println(F("ok"));
          return;
          return;
          return;
        }

        // M107 - EXTRUDER FAN OFF
        if (firstletter == "7") {
          exfanpowerstate = false;
          Serial.println(F("ok"));
          return;
          return;
          return;
        }

        // M108 - CANCEL EMERGENCY HEATING
        if (firstletter == "8") {
          watchdogactivated = true;
          Serial.println(F("ok"));
          Serial.println(F("lock"));
          currentlylocked = true;
          i2csend("EMERGENCY STOP (HEATING) ACTIVATED!", "", "", 0);
          return;
          return;
          return;
        }

        // M109 - SET EXTRUDER TEMPERATURE AND WAIT
        if (firstletter == "9") {

          // DETERMINE IF ARGS ARE PASSED
          firstletter = commanding.substring(4, 5);
          if (firstletter == " ") {
            // CONTINUE ON SETTING TEMPERATURE
            String extemp = commanding.substring(6, 100);
            if (currentactiveextruder == 0) {
              targete0temp = extemp.toFloat();
              Serial.println(F("ok"));
              return;
              return;
              return;
            }
            if (currentactiveextruder == 1) {
              targete1temp = extemp.toFloat();
              Serial.println(F("ok"));
              return;
              return;
              return;
            }
            Serial.println(F("INVALID EXTRUDER ACTIVE!"));
            return;
            return;
            return;
          } else {
            Serial.println(F("NO ARGS PASSED! - TYPE EXTRUDER HEAT"));
            return;
            return;
            return;
          }
        }
      }

      // M11*
      if (firstletter == "1") {

        // DETERMINE THE THIRD LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M110 - SET CURRENT LINE NUMBER
        if (firstletter == "0") {

          firstletter = commanding.substring(4, 5);
          if (firstletter == "") {
            Serial.println(F("NO ARGS PASSED! - TYPE SETTING LINE NUMBER"));
            writeerrorsstackloop("ERROR E110 - NO ARGS PASSED ON TYPE LINE NUMBERS!", 3, false, 9110, false, false);
            return;
            return;
            return;
          }
          if (firstletter == " ") {
            String settings110 = commanding.substring(4, 100);
            gcodenumber0 = settings110.toInt();
            gcodenumber1 = gcodenumber0 + 1;
            gcodenumber2 = gcodenumber1 + 1;
            gcodenumber3 = gcodenumber2 + 1;
            gcodenumber4 = gcodenumber3 + 1;
            gcodenumber5 = gcodenumber4 + 1;
            gcodenumber6 = gcodenumber5 + 1;
            gcodenumber7 = gcodenumber6 + 1;
            gcodenumber8 = gcodenumber7 + 1;
            gcodenumber9 = gcodenumber8 + 1;
            gcodenumber10 = gcodenumber9 + 1;
            Serial.println(F("ok"));
            return;
            return;
            return;
          }
        }

        // M111 - SET CURRENT DEBUG LEVEL
        if (firstletter == "1") {
          firstletter = commanding.substring(4, 5);

          // DEBUG LEVEL THROUGH THIS METHOD IS NOT GOING TO BE USED
          Serial.println(F("ok"));
          return;
          return;
          return;
        }

        // M112 - EMERGENCY STOP
        if (firstletter == "2") {
          watchdogactivated = true;
          Serial.println(F("WATCHDOG EMERGENCY SHUTDOWN ACTIVATED!"));
          Serial.println(F("ENDING SERIAL INTERFACE W/ CONTROLLER"));
          Serial.println(F("ok"));
          Serial.end();
          return;
          return;
          return;
        }

        // M113 - HOST KEEPALIVE
        if (firstletter == "3") {
          Serial.println(F("ok"));
          return;
          return;
          return;
        }

        // M114 - GET CURRENT POSITION
        if (firstletter == "4") {
          Serial.print(currentxdimension);
          Serial.print(F(" "));
          Serial.print(currentydimension);
          Serial.print(F(" "));
          Serial.print(currentzdimension);
          Serial.println(F(" "));
          Serial.println(F("ok"));
          return;
          return;
          return;
        }

        // M115 - GET FIRMWARE EVRSION AND CAPABILITIES
        if (firstletter == "5") {
          Serial.println(F("{firmware_version: 1.0.0; firmware_name: QUADSKETCH; other_firmware_information: G,M,Z,T COMMANDS; network_support: NO; sd_card_support: NO"));
          Serial.println(F("ok"));
          return;
          return;
          return;
        }

        // M116 - WAIT FOR FUTURE COMMANDS
        if (firstletter == "6") {
          safetytimeout = 0;
          Serial.println(F("ok"));
          return;
          return;
          return;
        }

        // M117 - DISPLAY MESSAGE ON LCD SCREEN
        if (firstletter == "7") {

          firstletter = commanding.substring(4, 5);
          if (firstletter == "") {
            Serial.println(F("NO ARGS PASSED! - TYPE LCD"));
            Serial.println(F("ok"));
            writeerrorsstackloop("ERROR E117 - NO ARGS PASSED LCD SCREEN", 0, false, 9117, false, false);
            return;
            return;
            return;
          }
          if (firstletter == " ") {
            // MESSAGE TO DISPLAY
            messagetodisplay = commanding.substring(5, 100);
            Serial.println(F("ok"));
            return;
            return;
            return;
          }
        }

        // M118 - ECHO MESSAGE ON HOST
        if (firstletter == "8") {
          Serial.println(errorstack0);
          Serial.println(F("ok"));
          return;
          return;
          return;
        }

        // M119 - GET ENDSTOP STATUS
        if (firstletter == "9") {
          if (xendstopminactive == true) {
            Serial.print(F("1 "));
          } else {
            Serial.print(F("0 "));
          }
          if (xendstopmaxactive == true) {
            Serial.print(F("1 "));
          } else {
            Serial.print(F("0 "));
          }
          if (yendstopminactive == true) {
            Serial.print(F("1 "));
          } else {
            Serial.print(F("0 "));
          }
          if (yendstopmaxvalue == true) {
            Serial.print(F("1 "));
          } else {
            Serial.print(F("0 "));
          }
          if (zendstopminactive == true) {
            Serial.print(F("1 "));
          } else {
            Serial.print(F("0 "));
          }
          if (zendstopmaxactive == true) {
            Serial.println(F("1 "));
          } else {
            Serial.println(F("0 "));
          }
          Serial.println(F("ok"));
          return;
          return;
          return;
        }
      }

      // M12*
      if (firstletter == "2") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M120 - ENABLE ENDSTOP DETECTION
        if (firstletter == "0") {
          endstopdetection = true;
          Serial.println(F("ok"));
          return;
          return;
          return;
        }

        // M121 - DISABLE ENDSTOP DETECTION
        if (firstletter == "1") {
          Serial.println(F("DISABLING ENDSTOP DETECTION!"));
          Serial.println(F("THIS IS NOT RECOMMENDED AS IT CAN DESTROY THE PRINTER!"));
          endstopdetection = false;
          Serial.println(F(""));
          Serial.println(F(""));
          Serial.println(F("ok"));
          return;
          return;
          return;
        }

        // M122 - SET SOFTWARE ENDSTOPS
        if (firstletter == "2") {

          // DETERMINE IF THERE IS ARGS
          firstletter = commanding.substring(4, 5);

          if (firstletter == "") {
            Serial.println(F("NO ARGS PASSED! - CANNOT SET SOFTWARE ENDSTOPS!"));
            watchdogactivated = true;
            return;
            return;
            return;
          }

          if (firstletter == " ") {
            String xmaxvalue = commanding.substring(5, 10);
            String ymaxvalue = commanding.substring(11, 15);
            String zmaxvalue = commanding.substring(16, 20);
            xendstopmaxvalue = xmaxvalue.toFloat();
            yendstopmaxvalue = ymaxvalue.toFloat();
            zendstopmaxvalue = zmaxvalue.toFloat();
            Serial.println(F("ok"));
            return;
            return;
            return;
          }
        }

        // M124 - EMERGENCY MOTOR STOP
        if (firstletter == "4") {
          watchdogactivated = true;
          Serial.println(F("M124 - EMERGENCY WATCHDOG ACTIVATED"));
          return;
          return;
          return;
        }

        // M126 - SET FAN SPEED CUSTOM
        if (firstletter == "6") {

          // DETERMINE THE NEXT LETTER OF THE STRING
          firstletter = commanding.substring(6, 7);
          printfanon = true;
          if (firstletter == "0" || firstletter == "" || firstletter == " ") {
            printfanon = false;
            analogWrite(FAN_PIN, 0);
          } else {
            printfanon = true;
            digitalWrite(FAN_PIN, HIGH);
          }
          interpretedcompleted = true;
          return (0);
          return (0);
          return (0);
        }
      }

      // M13*
      if (firstletter == "3") {

        // DETERMINE THE FOURTH LETTER IN A STRING
        firstletter = commanding.substring(3, 4);
      }

      // M14*
      if (firstletter == "4") {

        // DETERMINE THE FOURTH LETTER IN A STRING
        firstletter = commanding.substring(3, 4);

        // M140 - SET BED TEMPERATURE
        if (firstletter == "0") {
          firstletter = commanding.substring(4, 5);
          if (firstletter == "") {
            Serial.println(F("NO ARGS PASSED! - HEATING BED NOT SPECIFIED!"));
            return;
            return;
            return;
          }
          if (firstletter == " ") {
            String bedtemp = commanding.substring(5, 100);
            targethbtemp = bedtemp.toFloat();
            Serial.println(F("ok"));
            return;
            return;
            return;
          }
        }

        // M143 - MAXIMUM HEATER TEMPERATURE
        if (firstletter == "3") {
          firstletter = commanding.substring(4, 5);

          if (firstletter == "") {
            Serial.println(F("NO ARGS PASSED! - MAX HEATIN TEMPERATURE"));
            return;
            return;
            return;
          }
          if (firstletter == " ") {
            String e0maxtemp = commanding.substring(6, 15);
            String e1maxtemp = commanding.substring(16, 30);
            String hbmaxtemp = commanding.substring(31, 45);
            maxe0temp = e0maxtemp.toFloat();
            maxe1temp = e1maxtemp.toFloat();
            maxhbtemp = hbmaxtemp.toFloat();
            Serial.println(F("ok"));
            return;
            return;
            return;
          }
        }

        // M144 - BED STANDBY
        if (firstletter == "4") {
          targethbtemp = 000.0001;
          Serial.println(F("ok"));
          return;
          return;
          return;
        }

        // M149 - SET TEMPERATURE UNITS
        if (firstletter == "9") {
          firstletter = commanding.substring(4, 5);
          if (firstletter == "") {
            Serial.println(F("NO ARGS PASSED! - TEMPERATURE UNITS"));
            return;
            return;
            return;
          }
          if (firstletter == " ") {
            firstletter = commanding.substring(5, 6);
            if (firstletter == "C") {
              currenttempunits = 1;
              Serial.println(F("ok"));
              return;
              return;
              return;
            }
            if (firstletter == "F") {
              currenttempunits = 3;
              Serial.println(F("ok"));
              return;
              return;
              return;
            }
            if (firstletter == "K") {
              currenttempunits = 2;
              Serial.println(F("ok"));
              return;
              return;
              return;
            }
          }
        }
      }

      // M15*
      if (firstletter == "5") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M154 - AUTO REPORT POSITION
        if (firstletter == "4") {
        }

        // M155 - AUTO REPORT TEMPERATURE
        if (firstletter == "5") {
        }
      }

      // M16 - "EXPECTED PRINTER" CHECK
      if (firstletter == "6") {

        // DETERMINE THE THIRD LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        if (firstletter == "" || firstletter == " ") {
          String checking = commanding.substring(3, 125);
          if (printerhostname == checking) {
            // CONTINUE
            Serial.println(F("ok"));
            Serial.println(F("valid"));
          } else {
            if (type == 2) {
              watchdogactivated = true;
              timeinwatchdoginseconds = -1;
              Serial.println(F("printer mismatch detected - type strict"));
              Serial.println(F("ending serial communication"));
              return;
              return;
              return;
            } else {
              if (type == 1) {
                watchdogactivated = true;
                timeinwatchdoginseconds = 300;
                Serial.println(F("printer mismatch detected - type debug"));
                return;
                return;
                return;
              } else {
                if (type == 0) {
                  watchdogactivated = false;
                  timeinwatchdoginseconds = -1;
                  Serial.println(F("printer mismatch detected - type ignore"));
                  return;
                  return;
                  return;
                }
              }
            }
          }
        }
      }

      // M17 - ENABLE/DISABLE ALL STEPPER MOTORS
      if (firstletter == "7") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        steppermotorsdisabled = true;

        if (firstletter == "" || firstletter == " ") {
          if (enablemotors == true) {
            steppermotorsdisabled = true;
            Serial.println(F("ok"));
            return;
            return;
            return;
          }
          if (enablemotors == false) {
            enablemotors = true;
            Serial.println(F("ok"));
            return;
            return;
            return;
          }
        }
      }

      // M18 - DISABLE STEPPER MOTORS
      if (firstletter == "8") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        steppermotorsdisabled = false;

        if (firstletter == "" || firstletter == " ") {
          enablemotors = false;
          Serial.println(F("ok"));
          return;
          return;
          return;
        }
      }

      // M19*
      if (firstletter == "9") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M190 - WAIT FOR BED TEMP TO REACH TARGET TEMP
        if (firstletter == "0") {

          // DETERMINE THE FIFTH LETTER OF TEH STRING
          firstletter = commanding.substring(4, 5);

          if (firstletter == "") {
            Serial.println(F("NO ARGS PASSED! - UNABLE TO PROCEED WITH BED WARMING!"));
            Serial.println(F("ok"));
            return;
            return;
            return;
          }
          if (firstletter == " ") {
            String btemp = commanding.substring(5, 125);
            targethbtemp = btemp.toFloat();
            Serial.println(F("ok"));
            return;
            return;
            return;
          }
        }
      }
    }

    // IF IT IS "M2*", CONTINUE ON EVALUATING
    if (firstletter == "2") {

      // DETERMINE THE THIRD LETTER OF THE STRING
      firstletter = commanding.substring(2, 3);

      // M2 - PROGRAM END
      if (firstletter == "" || firstletter == " ") {
        printingactive = false;
        Serial.println(F("ok"));
        Serial.println(F("PROGRAM END"));
      }

      // M20*
      if (firstletter == "0") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M20 - LIST SD CARDS
        if (firstletter == "" || firstletter == " ") {
          Serial.println(F("ok"));
          Serial.println(F("sd init fail"));
          return;
          return;
          return;
        }

        // M200 - SET FILAMENT DIAMETER
        if (firstletter == "0") {

          // DETERMINE THE FIFTH LETTER OF THE STRING
          firstletter = commanding.substring(4, 5);

          if (firstletter == "") {
            Serial.println(F("NO ARGS PASSED! - UNABLE TO SET FILAMENT DIAMETER"));
            Serial.println(F("ok"));
            return;
            return;
            return;
          }

          if (firstletter == " ") {

            // DETERMINE FLOAT FILAMENT DIAMETER
            String fildim = commanding.substring(5, 125);
            filamentdiam = fildim.toFloat();
            Serial.println(F("ok"));
            return;
            return;
            return;
          }
        }

        // M201 - SET MAX ACCELERATION
        if (firstletter == "1") {

          // DETERMINE THE FIFTH LETTER OF THE STRING
          firstletter = commanding.substring(4, 5);

          if (firstletter == "") {
            Serial.println(F("NO ARGS PASSED! - COULDN'T SET MAX ACCELERATION"));
            Serial.println(F("ok"));
            return;
            return;
            return;
          }

          if (firstletter == " ") {
            String maxac = commanding.substring(5, 125);
            maxacceleration = maxac.toFloat();
            Serial.println(F("ok"));
            return;
            return;
            return;
          }
        }

        // M202 - SET MAX TRAVEL ACCELERATION
        if (firstletter == "2") {

          // DETERMINE THE FIFTH CHARACTER OF THE STRING
          firstletter = commanding.substring(4, 5);

          if (firstletter != " ") {
            Serial.println(F("NO ARGS PASSED! - UNABLE TO SET MAX TRAVEL SPEED"));
            Serial.println(F("ok"));
            return;
            return;
            return;
          }

          if (firstletter == " ") {
            String maxtr = commanding.substring(5, 125);
            maxtravelspeed = maxtr.toFloat();
            Serial.println(F("ok"));
            return;
            return;
            return;
          }
        }

        // M203 - SET MAXIMUM FEEDRATE
        if (firstletter == "3") {

          // DETERMINE THE FIFTH CHARACTER OF THE STRING
          firstletter = commanding.substring(4, 5);

          if (firstletter != " ") {
            Serial.println(F("NO ARGS PASSED! - UNABLE TO PROCEED WITH MAX FEEDRATE"));
            Serial.println(F("ok"));
            return;
            return;
            return;
          }

          if (firstletter == " ") {
            String extrafeed = commanding.substring(5, 125);
            maxfeedratespeed = extrafeed.toFloat();
            Serial.println(F("ok"));
            return;
            return;
            return;
          }
        }

        // M204 - SET DEFAULT ACCELERATION
        if (firstletter == "4") {

          // DETERMINE THE FIFTH CHARACTER OF THE STRING
          firstletter = commanding.substring(4, 5);

          if (firstletter != " ") {
            Serial.println(F("NO ARGS PASSED! - UNABEL TO PROCEED WITH DEF ACCELERATION"));
            Serial.println(F("ok"));
            return;
            return;
            return;
          }

          if (firstletter == " ") {
            String bluedef = commanding.substring(5, 125);
            defaultaccelerationspeed = bluedef.toFloat();
            Serial.println(F("ok"));
            return;
            return;
            return;
          }
        }

        // M206 - ADVANCED SETTINGS (MIN SPEEDS)
        if (firstletter == "6") {
          Serial.println(F("ok"));
          return;
          return;
          return;
        }

        // M207 - SET RETRACTION LENGTH
        if (firstletter == "7") {

          // DETERMINE THE FIFTH CHARACTER OF THE STRING
          firstletter = commanding.substring(4, 5);

          if (firstletter != " ") {
            Serial.println(F("NO ARGS PASSED! - UNABLE TO SET RETRACT LENGTH"));
            Serial.println(F("ok"));
            return;
            return;
            return;
          }

          if (firstletter == " ") {
            String retlen = commanding.substring(5, 125);
            retractionlength = retlen.toFloat();
            Serial.println(F("ok"));
            return;
            return;
            return;
          }
        }

        // M208 - SET EXTRUSION LENGTH
        if (firstletter == "8") {

          // DETERMINE THE FIFTH CHARACTER OF THE STRING
          firstletter = commanding.substring(4, 5);

          if (firstletter != " ") {
            Serial.println(F("NO ARGS PASSED! - UNABLE TO SET EXTRUSION LENGTH"));
            Serial.println(F("ok"));
            return;
            return;
            return;
          }

          if (firstletter == " ") {
            String exlen = commanding.substring(5, 125);
            extrusionlength = exlen.toFloat();
            Serial.println(F("ok"));
            return;
            return;
            return;
          }
        }
      }

      // M21*
      if (firstletter == "1") {
        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M21 - INITIALIZE SD CARD
        if (firstletter == "" || firstletter == " ") {
          Serial.println(F("ok"));
          Serial.println(F("sd init fail"));
          return;
          return;
          return;
        }

        // M211 - DISABLE/ENABLE SOFTWARE ENDSTOPS
        if (firstletter == "1") {
          if (softwareendstops == true) {
            softwareendstops = false;
            Serial.println(F(""));
            Serial.println(F(""));
            Serial.println(F(""));
            Serial.println(F(""));
            Serial.println(F("DISABLING THE SOFTWARE ENDSTOPS!"));
            Serial.println(F(""));
            Serial.println(F(""));
            Serial.println(F(""));
            Serial.println(F(""));
            Serial.println(F("IT IS NOT RECOMMENDED TO DISABLE THE SOFTWARE ENDSTOPS!"));
            Serial.println(F(""));
            Serial.println(F(""));
            Serial.println(F(""));
            Serial.println(F(""));
            Serial.println(F("ok"));
            return;
            return;
            return;
          }
          if (softwareendstops == false) {
            softwareendstops = true;
            Serial.println(F("ok"));
            return;
            return;
            return;
          }
          softwareendstops = true;
          return;
          return;
          return;
        }
      }

      // M22*
      if (firstletter == "2") {
        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M22 - RELEASE SD CARD
        if (firstletter == "" || firstletter == " ") {
          Serial.println(F("ok"));
          return;
          return;
          return;
        }

        // M226 - GCODE INITIATED PAUSE
        if (firstletter == "6") {
          Serial.println(F("ok"));
          return;
          return;
          return;
        }
      }

      // M23*
      if (firstletter == "3") {
        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M23 - SELECT SD FILE
        if (firstletter == "" || firstletter == " ") {
          Serial.println(F("ok"));
          Serial.println(F("sd init fail"));
          return;
          return;
          return;
        }
      }

      // M24*
      if (firstletter == "4") {
        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M24 - START/RESUME SD PRINT
        if (firstletter == "" || firstletter == " ") {
          Serial.println(F("ok"));
          Serial.println(F("sd init fail"));
          return;
          return;
          return;
        }
      }

      // M25*
      if (firstletter == "5") {
        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M25 - PAUSE SD PRINT
        if (firstletter == "" || firstletter == " ") {
          Serial.println(F("ok"));
          Serial.println(F("sd init fail"));
          return;
          return;
          return;
        }
      }

      // M26*
      if (firstletter == "6") {
        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M26 - SET SD POSITION
        if (firstletter == "" || firstletter == " ") {
          Serial.println(F("ok"));
          Serial.println(F("sd init fail"));
          return;
          return;
          return;
        }

        // M260 - SEND OVER I2C PROTOCOL
        if (firstletter == "0") {
          // DETERMINE THE FIFTH LETTER OF THE STRING
          firstletter = commanding.substring(4, 5);

          if (firstletter == "") {
            Serial.println(F("NO ARGS PASSED FOR I2C PROTOCOL!"));
            return (2);
          }
          if (firstletter == " ") {
            String send2i2c = commanding.substring(5, 125);
            i2csend(send2i2c, send2i2c, send2i2c, 2);
            return (0);
          }
        }

        // M261 - REQUEST I2C INFORMATION
        if (firstletter == "1") {
          // DETERMINE THE FIFTH LETTER OF THE STRING
          firstletter = commanding.substring(4, 5);

          if (firstletter == "") {
            Serial.println(F("ok"));
            Serial.println(F("NO ARGS RECEIVED?"));
            return (0);
          }

          if (firstletter == " ") {
            Serial.println(F("ok"));
            Serial.println(F("M261 NOT SUPPORTED BY CURRENT I2C PROTOCOL VERSION"));
            return (0);
          }
        }
      }

      // M27*
      if (firstletter == "7") {
        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M27 - REPORT SD PRINT STATUS
        if (firstletter == "" || firstletter == " ") {
          Serial.println(F("sd init fail"));
          return;
          return;
          return;
        }
      }

      // M28*
      if (firstletter == "8") {
        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M28 - BEGIN WRITE TO SD CARD
        if (firstletter == "" || firstletter == " ") {
          Serial.println(F("sd init fail"));
          return;
          return;
          return;
        }

        // M280* - SET SERVO POSITION
        if (firstletter == "0") {

          // DETERMINE THE SERVO POSITION
          firstletter = commanding.substring(4, 5);
          if (firstletter == "") {
            Serial.println(F("NO ARGS PASSED! CANT SET SERVO POSITION"));
            return (2);
          }

          if (firstletter == " ") {

            // DETERMINE THE NEXT LETTER
            firstletter = commanding.substring(5, 6);

            int stringnumber = 6;
            if (firstletter == "X") {
              String xpos = commanding.substring(stringnumber, stringnumber + 5);
              currentxdimension = xpos.toFloat();
              stringnumber = stringnumber + 6;
              firstletter = commanding.substring(stringnumber, stringnumber + 1);
            }

            if (firstletter == "Y") {
              String ypos = commanding.substring(stringnumber, stringnumber + 5);
              currentydimension = ypos.toFloat();
              stringnumber = stringnumber + 6;
              firstletter = commanding.substring(stringnumber, stringnumber + 1);
            }

            if (firstletter == "Z") {
              String zpos = commanding.substring(stringnumber, stringnumber + 5);
              currentzdimension = zpos.toFloat();
              stringnumber = stringnumber + 6;
              firstletter = commanding.substring(stringnumber, stringnumber + 1);
            }

            if (firstletter == "E") {
              String epos = commanding.substring(stringnumber, stringnumber + 5);
              currente0motordimension = epos.toFloat();
              stringnumber = stringnumber + 6;
              firstletter = commanding.substring(stringnumber, stringnumber + 1);
            }

            Serial.println(F("ok"));
            return (0);
          }
          return (2);
        }

        // M282* - DETACH SERVO
        if (firstletter == "2") {

          // DETERMINE THE FIFTH LETTER OF THE STRING
          firstletter = commanding.substring(4, 5);

          if (firstletter == "") {
            Serial.println(F("ok"));
            return (0);
          }

          if (firstletter == " ") {
            Serial.println(F("ok"));
            return (0);
          }
        }
      }

      // M29*
      if (firstletter == "9") {
        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M29 - STOP WRITING TO SD CARD
        if (firstletter == "" || firstletter == " ") {
          Serial.println(F("sd init fail"));
          return (0);
        }
      }
    }

    // IF IT IS "M3*", CONTINUE ON EVALUATING
    if (firstletter == "3") {

      // DETERMINE THE THIRD LETTER OF THE STRING
      firstletter = commanding.substring(2, 3);

      // M30*
      if (firstletter == "0") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M302
        if (firstletter == "2") {
        }
      }

      // M31*
      if (firstletter == "1") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M31 - OUTPUT TIME SINCE LAST M109
        if (firstletter == "" || firstletter == " ") {
          Serial.print(timesincelastM109inseconds);
          return;
          return;
          return;
        }
      }

      // M32*
      if (firstletter == "2") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M32 - ELECT FILE AND START SD PRINT
        if (firstletter == "" || firstletter == " ") {
          Serial.println(F("sd init fail"));
          return;
          return;
          return;
        }
      }

      // M33*
      if (firstletter == "3") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M33.1 - GET THE LONG ANEM FOR AN SD CARD FILE OR FOLDER
        // M33.2 - STOP AND CLOSE FILE AND SAVE RESTART.GCODE
        if (firstletter == "" || firstletter == " ") {
        }
      }

      // M34*
      if (firstletter == "4") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M34 - SET SD FILE SORTING OPTIONS
        if (firstletter == "" || firstletter == " ") {
          Serial.println(F("sd init fail"));
          return;
          return;
          return;
        }
      }

      // M35*
      if (firstletter == "5") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
      }

      // M36*
      if (firstletter == "6") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
      }

      // M37*
      if (firstletter == "7") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M37 - SIMULATION MODE (NO EXTRUSION)
        if (firstletter == " ") {
          firstletter = commanding.substring(4, 5);
          if (firstletter == "S") {
            firstletter = commanding.substring(5, 6);
            simulationmode = firstletter.toInt();
            return;
            return;
            return;
          } else {
            Serial.println(F("NO ARGS PASSED! M37 - TYPE SIMULATION"));
            return;
            return;
            return;
          }
        } else {
          if (firstletter == "") {
            Serial.println(F("NO ARGS PASSED! M37 - TYPE SIMULATION"));
            return;
            return;
            return;
          }
        }
      }

      // M38*
      if (firstletter == "8") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // COMPUTE SHA1 HASH OF TARGET FILE ON SD CARD
        if (firstletter == " ") {
          Serial.println(F("ok"));
          Serial.println(F("sd init fail"));
          return;
          return;
          return;
        }
      }

      // M39*
      if (firstletter == "9") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M39 - REPORT SD CARD INFORMATION
        if (firstletter == "" || firstletter == " ") {
          Serial.println(F("sd init fail"));
          return;
          return;
          return;
        }
      }
    }

    // IF IT IS "M4*", CONTINUE ON EVALUATING
    if (firstletter == "4") {

      // DETERMINE THE THIRD LETTER OF THE STRING
      firstletter = commanding.substring(2, 3);

      // IF IT IS M40*, CONTINUE
      if (firstletter == "0") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M40 - EJECT SD CARD
        if (firstletter == "" || firstletter == " ") {
          Serial.println(F("ok"));
          return;
          return;
          return;
        }
      }

      // IF IT IS M41*, CONTINUE
      if (firstletter == "1") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
      }

      // IF IT IS M42*, CONTINUE
      if (firstletter == "2") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
      }

      // IF IT IS M43*, CONTINUE
      if (firstletter == "3") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M43 - PIN REPORT AND DEBUG
        Serial.println(F("REPORT GENERATING..."));
        Serial.println(F("COMMAND NOT CURRENTLY SUPPORTED"));
        Serial.println(F("ok"));
        return;
        return;
        return;
      }

      // IF IT IS M44*, CONTINUE
      if (firstletter == "4") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
      }

      // IF IT IS M45*, CONTINUE
      if (firstletter == "5") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
      }

      // IF IT IS M46*, CONTINUE
      if (firstletter == "6") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
      }

      // IF IT IS M47*, CONTINUE
      if (firstletter == "7") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
      }

      // IF IT IS M48*, CONTINUE
      if (firstletter == "8") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
      }

      // IF IT IS M49*, CONTINUE
      if (firstletter == "9") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
      }
    }

    // IF IT IS A "5", CONTINUE ON EVALUATING
    if (firstletter == "5") {
    }

    // IF IT IS A "6", CONTINUE ON EVALUATING
    if (firstletter == "6") {
    }

    // IF IT IS "M7*", CONTINUE ON EVALUATING
    if (firstletter == "7") {

      // DETERMINE THE THIRD LETTER OF THE STRING
      firstletter = commanding.substring(2, 3);

      // M70*
      if (firstletter == "0") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M70 - DISPLAY MESSAGE ON LCD DISPLAY
        if (firstletter == "") {
          Serial.println(F("NO ARGS PASSED! IGNORING - TYPE LCD"));
          return;
          return;
          return;
        }
        if (firstletter == " ") {
          timetodisplaylcdinseconds = 60;
          messagetodisplay = commanding.substring(5, 100);
          Serial.println(F("ok"));
          return;
          return;
          return;
        }
      }

      // M71*
      if (firstletter == "1") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
      }

      // M72*
      if (firstletter == "2") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
      }

      // M73*
      if (firstletter == "3") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M73 - SET/GET BUILD PERCENTAGE
        if (firstletter == "" || firstletter == " ") {
          Serial.println(F("ok"));
          Serial.println(F("sd init fail"));
          return;
          return;
          return;
        }
      }

      // M74*
      if (firstletter == "4") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
      }

      // M75*
      if (firstletter == "5") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M75 - START PRINT JOB TIMER
        if (firstletter == "" || firstletter == " ") {
          printjobtimeractive = true;
          Serial.println(F("ok"));
          return;
          return;
          return;
        }
      }

      // M76*
      if (firstletter == "6") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M76 - PAUSE PRINT JOB TIMER
        if (firstletter == "" || firstletter == " ") {
          printjobtimeractive = false;
          Serial.println(F("ok"));
          return;
          return;
          return;
        }
      }

      // M77*
      if (firstletter == "7") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M77 - STOP PRINT JOB TIMER
        if (firstletter == "" || firstletter == " ") {
          printjobtimeractive = false;
          printjobtimerinseconds = 0;
          Serial.println(F("ok"));
          return;
          return;
          return;
        }
      }

      // M78*
      if (firstletter == "8") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M78 - SHOW STATISTICAL INFORMATION ABOUT THE PRINT JOBS
        if (firstletter == "" || firstletter == " ") {
          Serial.println(F("M78 - STATISTICS IS NOT SUPPORTED"));
          Serial.println(F("ok"));
          return;
          return;
          return;
        }
      }

      // M79*
      if (firstletter == "9") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
      }
    }

    // IF IT IS A "8", CONTINUE ON EVALUATING
    if (firstletter == "8") {

      // DETERMINE THE THIRD LETTER OF THE STRING
      firstletter = commanding.substring(2, 3);

      // M80*
      if (firstletter == "0") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M80 - ATX POWER ON
        if (firstletter == "" || firstletter == " ") {
          atxpoweron = true;
          Serial.println(F("ok"));
          return;
          return;
          return;
        }
      }

      // M81*
      if (firstletter == "1") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M81 - ATX POWER OFF
        if (firstletter == "" || firstletter == " ") {
          atxpoweron = false;
          Serial.println(F("ok"));
          return;
          return;
          return;
        }
      }

      // M82*
      if (firstletter == "2") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M82 - SET EXTRUDER MODE TO ABSOLUTE POSITIONING
        if (firstletter == "" || firstletter == " ") {
          absolutepositioning = true;
          relativepositioning = false;
          Serial.println(F("ok"));
          return;
          return;
          return;
        }
      }

      // M83*
      if (firstletter == "3") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M83 - SET EXTRUDER TO RELATIVE POSITIONING
        if (firstletter == "" || firstletter == " ") {
          absolutepositioning = false;
          relativepositioning = true;
          Serial.println(F("ok"));
          return;
          return;
          return;
        }
      }

      // M84*
      if (firstletter == "4") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M84 - IDLE STEPPER MOTOR TIMEOUT
        if (firstletter == "") {
          Serial.println(F("NO ARGS PASSED! IGNORING - TYPE MOVEMENT"));
          return;
          return;
          return;
        }

        if (firstletter == " ") {
          String timeout99 = commanding.substring(5, 100);
          idlesteppermotortimeoutinseconds = timeout99.toInt();
          Serial.println(F("ok"));
          return;
          return;
          return;
        }
      }

      // M85*
      if (firstletter == "5") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M85 - SET INACTIVITY MOTOR TIMEOUT
        if (firstletter == "" || firstletter == " ") {
          Serial.println(F("INACTIVITY NOT SUPPORTED ON PLATFORM! USE LOCKS OR SAFETY TIMEOUT INSTEAD"));
          Serial.println(F("ok"));
          return;
          return;
          return;
        }
      }

      // M86*
      if (firstletter == "6") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M86 - SET SAFETY TIMEOUT
        if (firstletter == "") {
          Serial.println(F("M86 - NO ARGS PASSED! IGNORING - TYPE SAFETY"));
          return;
          return;
          return;
        }
        if (firstletter == " ") {
          String satisfying = commanding.substring(5, 100);
          safetytimeout = satisfying.toInt();
          Serial.println(F("ok"));
          return;
          return;
          return;
        }
      }

      // M87*
      if (firstletter == "7") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);

        // M87 - CANCEL SAFETY TIMER
        if (firstletter == "" || firstletter == " ") {
          currentsafetytimer = 0;
          currentextrudertimer = 0;
          Serial.println(F("ok"));
          return;
          return;
          return;
        }
      }

      // M88*
      if (firstletter == "8") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
      }

      // M89*
      if (firstletter == "9") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
      }
    }

    // IF IT IS A "9", CONTINUE ON EVALUATING
    if (firstletter == "9") {

      // DETERMINE THE THIRD LETTER OF THE STRING
      firstletter = commanding.substring(2, 3);

      // M90*
      if (firstletter == "0") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
      }

      // M91**
      if (firstletter == "1") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
      }

      // M92**
      if (firstletter == "2") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
      }

      // M93**
      if (firstletter == "3") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
      }

      // M94**
      if (firstletter == "4") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
      }

      // M95**
      if (firstletter == "5") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
      }

      // M96**
      if (firstletter == "6") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
      }

      // M97**
      if (firstletter == "7") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
      }

      // M98**
      if (firstletter == "8") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
      }

      // M99**
      if (firstletter == "9") {

        // DETERMINE THE FOURTH LETTER OF THE STRING
        firstletter = commanding.substring(3, 4);
      }
    }
  }
}

// EMERGENCY COMMANDS RUN IMMEDIATELY
int eShell(String commanding) {

  bool interpretedcompleted = false;
  
  // DETERMINE THE FIRST LETTER
  String firstletter = commanding.substring(0, 1);

  // IF E, EMERGENCY COMMANDS!
  if (firstletter == "E") {

    // DETERMINE THE SECOND LETTER OF THE STRING
    firstletter = commanding.substring(1, 2);

    // E0 - DISABLE ALL MOTOR ENABLE PINS!
    if (firstletter == "0") {
      watchdogactivated = true;
      digitalWrite(X_ENABLE_PIN, HIGH);
      digitalWrite(Y_ENABLE_PIN, HIGH);
      digitalWrite(Z_ENABLE_PIN, HIGH);
      digitalWrite(E_ENABLE_PIN, HIGH);
    }

    // E1 - DISABLE ALL TEMPERATURE PINS!
    if (firstletter == "1") {
      watchdogactivated = true;
      digitalWrite(HEATER_0_PIN, HIGH);
      digitalWrite(HEATER_1_PIN, HIGH);
      digitalWrite(HEATER_HB_PIN, HIGH);
    }
  }
}