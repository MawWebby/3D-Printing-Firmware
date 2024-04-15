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
    zShell(commanding);
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

                // CONVERT FROM INCHES TO MM
                String xvalues = commanding.substring(startxdigit, gcodenumber);
                float xvaluestoinsert = xvalues.toFloat();
                if (currentunits == 1) {
                  xvaluestoinsert = xvaluestoinsert / millimeterstoinches;
                }
                if (absoluterelative == 1) {
                  float xpreviousvalue = -1;
                  if (analyzedCURRENTLYANALYZINGNUMBER == 0) {
                    xpreviousvalue = readfromarray(10, 0);
                  } else {
                    xpreviousvalue = readfromarray(analyzedCURRENTLYANALYZINGNUMBER - 1, 0);
                  }

                  if (xpreviousvalue == -1) {
                    Serial.println(F("COMMAND COULD NOT BE COMPLETED - PARSER ERROR!"));
                  } else {
                    xvaluestoinsert = xpreviousvalue + xvaluestoinsert;
                  }
                }
                sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, xvaluestoinsert, 0);
                xfinished = true;
                xstatement = true;
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

              // CONVERT FROM INCHES TO MM
              if (firstletter == " " || firstletter == "") {
                String yvalues = commanding.substring(startydigit, gcodenumber);
                float yvaluestoinsert = yvalues.toFloat();
                if (currentunits == 1) {
                  yvaluestoinsert = yvaluestoinsert / millimeterstoinches;
                }
                if (absoluterelative == 1) {
                  float ypreviousvalue = -1;
                  if (analyzedCURRENTLYANALYZINGNUMBER == 0) {
                    ypreviousvalue = readfromarray(10, 1);
                  } else {
                    ypreviousvalue = readfromarray(analyzedCURRENTLYANALYZINGNUMBER - 1, 1);
                  }

                  if (ypreviousvalue == -1) {
                    Serial.println(F("COMMAND COULD NOT BE COMPLETED - PARSER ERROR"));
                  } else {
                    yvaluestoinsert = ypreviousvalue + yvaluestoinsert;
                  }
                }
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
                if (currentunits == 0) {
                  String zvalues = commanding.substring(startzdigit, gcodenumber);
                  float zvaluestoinsert = zvalues.toFloat();
                  sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, zvaluestoinsert, 2);
                  zfinished = true;
                  zstatement = true;
                } else {
                  String zvalues = commanding.substring(startzdigit, gcodenumber);
                  float zvaluestoinsert = zvalues.toFloat();
                  zvaluestoinsert = zvaluestoinsert / millimeterstoinches;
                  sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, zvaluestoinsert, 2);
                  zfinished = true;
                  zstatement = true;
                }
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
                if (currentunits == 0) {
                  String evalues = commanding.substring(startedigit, gcodenumber);
                  float evaluestoinsert = evalues.toFloat();
                  sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, evaluestoinsert, 3);
                  efinished = true;
                  estatement = true;
                } else {
                  String evalues = commanding.substring(startedigit, gcodenumber);
                  float evaluestoinsert = evalues.toFloat();
                  evaluestoinsert = evaluestoinsert / millimeterstoinches;
                  sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, evaluestoinsert, 3);
                  efinished = true;
                  estatement = true;
                }
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

          bool xstatement = false;
          bool ystatement = false;
          bool zstatement = false;
          bool estatement = false;

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

                  // CONVERT FROM INCHES TO MM
                  if (currentunits == 0) {
                    String xvalues = commanding.substring(startxdigit, gcodenumber);
                    float xvaluestoinsert = xvalues.toFloat();
                    sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, xvaluestoinsert, 0);
                    xfinished = true;
                    xstatement = true;
                  } else {
                    String xvalues = commanding.substring(startxdigit, gcodenumber);
                    float xvaluestoinsert = xvalues.toFloat();
                    xvaluestoinsert = xvaluestoinsert / millimeterstoinches;
                    sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, xvaluestoinsert, 0);
                    xfinished = true;
                    xstatement = true;
                  }
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
                  if (currentunits == 0) {
                    String yvalues = commanding.substring(startydigit, gcodenumber);
                    float yvaluestoinsert = yvalues.toFloat();
                    sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, yvaluestoinsert, 1);
                    yfinished = true;
                    ystatement = true;
                  } else {
                    String yvalues = commanding.substring(startydigit, gcodenumber);
                    float yvaluestoinsert = yvalues.toFloat();
                    yvaluestoinsert = yvaluestoinsert / millimeterstoinches;
                    sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, yvaluestoinsert, 1);
                    yfinished = true;
                    ystatement = true;
                  }
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
                  if (currentunits == 0) {
                    String zvalues = commanding.substring(startzdigit, gcodenumber);
                    float zvaluestoinsert = zvalues.toFloat();
                    sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, zvaluestoinsert, 2);
                    zfinished = true;
                    zstatement = true;
                  } else {
                    String zvalues = commanding.substring(startzdigit, gcodenumber);
                    float zvaluestoinsert = zvalues.toFloat();
                    zvaluestoinsert = zvaluestoinsert / millimeterstoinches;
                    sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, zvaluestoinsert, 2);
                    zfinished = true;
                    zstatement = true;
                  }
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
                  if (currentunits == 0) {
                    String evalues = commanding.substring(startedigit, gcodenumber);
                    float evaluestoinsert = evalues.toFloat();
                    sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, evaluestoinsert, 3);
                    efinished = true;
                    estatement = true;
                  } else {
                    String evalues = commanding.substring(startedigit, gcodenumber);
                    float evaluestoinsert = evalues.toFloat();
                    evaluestoinsert = evaluestoinsert / millimeterstoinches;
                    sendtoarray(analyzedCURRENTLYANALYZINGNUMBER, evaluestoinsert, 3);
                    efinished = true;
                    estatement = true;
                  }
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
    }

    // G2*
    if (firstletter == "2") {

      // DETERINE THE THIRD LETTER OF THE SCRIPT
      firstletter = commanding.substring(2, 3);

      // G2 - CONTROLLED ARC MOVE COUNTER CLOCKWISE (NOT SUPPORTED)
      if (firstletter == " ") {
        Serial.println(F("error"));
        Serial.println(F("CONTROLLED ARC MOVE NOT SUPPORTED"));
      }

      // G20 - SET UNITS TO INCHES
      if (firstletter == "0") {
        Serial.println(F("ok"));
        currentunits = 1;
        interpretedcompleted = true;
        return (0);
      }

      // G21 - SET UNITS TO MM
      if (firstletter == "1") {
        Serial.println(F("ok"));
        currentunits = 0;
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

    // G3*
    if (firstletter == "3") {
    }

    // G4*
    if (firstletter == "4") {
    }

    // G5*
    if (firstletter == "5") {
    }

    // G6*
    if (firstletter == "6") {
    }

    // G7*
    if (firstletter == "7") {
    }

    // G8*
    if (firstletter == "8") {
    }

    // G9*
    if (firstletter == "9") {

      firstletter = commanding.substring(2, 3);

      // G92 - SET CURRENT MOTOR POSITIONS
      if (firstletter == "2") {

        // INITIAL TIMING VARIABLES
        int inittimingx92 = 5;
        int inittimingy92 = 5;
        int inittimingz92 = 5;
        int inittiminge92 = 5;

        // FIRSTLETTER DETERMINATION
        firstletter = commanding.substring(4, 5);

        // WHILE VARIABLES
        bool completionx92 = false;
        bool completiony92 = false;
        bool completionz92 = false;
        bool completione92 = false;

        // TIMING VARIABLES
        int timingx92 = 0;
        int timingy92 = 0;
        int timingz92 = 0;
        int timinge92 = 0;


        // SET X POSITION
        if (firstletter == "X") {

          while (completionx92 == false && timingx92 <= 20) {
            firstletter = commanding.substring(inittimingx92 + timingx92, inittimingx92 + 1 + timingx92);

            if (firstletter == " " || firstletter == "" || timingx92 == 19) {
              String currentx = commanding.substring(inittimingx92, inittimingx92 + timingx92);
              currentxdimension = currentx.toFloat();
              completionx92 = true;
              timingy92 = inittimingx92 + timingx92 + 1;
            }
          }
          firstletter = commanding.substring(timingy92, timingy92 + 1);
        }

        // SET Y POSITION
        if (firstletter == "Y") {

          while (completiony92 == false && timingy92 <= 20) {
            firstletter = commanding.substring(inittimingy92 + timingy92, inittimingy92 + 1 + timingy92);

            if (firstletter == " " || firstletter == "" || timingy92 == 19) {
              String currenty = commanding.substring(inittimingy92, inittimingy92 + timingy92);
              currentydimension = currenty.toFloat();
              completiony92 = true;
              timingz92 = inittimingy92 + timingy92 + 1;
            }
          }
          firstletter = commanding.substring(timingz92, timingz92 + 1);
        }

        // SET Z POSITION
        if (firstletter == "Z") {

          while (completionz92 == false && timingz92 <= 20) {
            firstletter = commanding.substring(inittimingz92 + timingz92, inittimingz92 + 1 + timingz92);

            if (firstletter == " " || firstletter == "" || timingz92 == 19) {
              String currentz = commanding.substring(inittimingz92, inittimingz92 + timingz92);
              currentzdimension = currentz.toFloat();
              completionz92 = true;
              timinge92 = inittimingz92 + timingz92 + 1;
            }
          }
          firstletter = commanding.substring(timinge92, timinge92 + 1);
        }

        // SET E POSITION
        if (firstletter == "E") {

          while (completione92 == false && timinge92 <= 20) {
            firstletter = commanding.substring(inittiminge92 + timinge92, inittiminge92 + 1 + timinge92);

            if (firstletter == " " || firstletter == "" || timinge92 == 19) {
              String currente = commanding.substring(inittiminge92, inittiminge92 + timinge92);
              currente0motordimension = currente.toFloat();
              completione92 = true;
            }
          }
        }

        Serial.println(F("ok"));
      }
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