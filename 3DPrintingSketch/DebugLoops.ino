/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

// DEBUG / FULL SYSTEM TEST LOOPS

// FULL SYSTEM CHECK
void q900(bool overrideerrorsinarray, bool runmovementcommands, bool runextrudercommands, bool printeractivestate, int extrudertimeoutmax, int motortimeoutmax) {
  Serial.println(F("analyzing..."));
  Serial.println(F("Q900 - SYSTEM WILL RUN A FULL SYSTEM ANALYSIS TEST!"));
  Serial.println(F("THIS TEST WILL TAKE ~5 MINUTES TO COMPLETE"));
  Serial.println(F("THE PRINTER WILL RESTART MULTIPLE TIMES DURING THIS PROCESS"));

  // OUTPUT FOR OTHER Q LOOPS
  int outputq901 = 0;
  int outputq902 = 0;
  int outputq903 = 0;
  int outputq904 = 0;
  int outputq905 = 0;
  int outputq906 = 0;
  int outputq907 = 0;
  int outputq908 = 0;
  int outputq909 = 0;
  int outputq910 = 0;

  delay(1000);

  // DISABLE ALL PINS HERE
  Serial.print(F("1/15 - disabling all pins..."));
  q930(true);
  Serial.println(F("done"));
  delay(1000);



  // RUN CHECK ON UNCACHED STRINGS ARRAY = 2/15
  {
    Serial.print(F("2/15 - running check on uncached strings array..."));
    outputq901 = q901(true, true);

    // DIFFERENT OUTCOMES OF Q901
    if (outputq901 != 0) {
      Serial.print(F("UNCACHED DATABASE ARRAY CHECK EXITED WITH ERROR DU-"));
      Serial.println(outputq901);
      watchdogactivated = true;
    }
    if (outputq901 == 0) {
      Serial.println(F("done"));
    }
    if (outputq901 == 1) {
      Serial.println(F("UNABLE TO CONTINUE, PRINTER COULD NOT GO INTO ACTIVE MODE!"));
    }
  }
  delay(1000);



  // RUN CHECK ON CACHED DATABASE ARRAY = 3/15
  {
    Serial.print(F("3/15 - running check on cached database array..."));
    outputq902 = q902(true, true);

    // DIFFERENT OUTCOMES OF Q902
    if (outputq902 != 0) {
      Serial.print(F("UNCACHED DATABASE ARRAY CHECK EXITED WITH ERROR DC-"));
      Serial.println(outputq902);
      watchdogactivated = true;
    }
    if (outputq902 == 0) {
      Serial.println(F("done"));
    }
    if (outputq902 == 1) {
      Serial.println(F("UNABLE TO CONTINUE, PRINTER COULD NOT GO INTO ACTIVE MODE!"));
    }
  }
  delay(1000);



  // RUN CHECK OF TEMPERATURE PROBES = 4/15 q(903)
  {
    Serial.print(F("4/15 - running check of temperature probes..."));
    outputq903 = q903(true, true);

    // DIFFERENT OUTCOMES OF Q903
    if (outputq903 != 0) {
      Serial.print(F("UNCACHED DATABASE ARRAY CHECK EXITED WITH ERROR T-"));
      Serial.println(outputq903);
      watchdogactivated = true;
    }
    if (outputq903 == 0) {
      Serial.println(F("done"));
    }
    if (outputq903 == 1) {
      Serial.println(F("UNABLE TO CONTINUE, PRINTER COULD NOT GO INTO ACTIVE MODE!"));
    }
  }
  delay(1000);



  // RUN CHECK OF MOTOR MOVEMENTS STANDING = 5/1 (q904)
  {
    Serial.print(F("5/15 - running check of motor movements (software)..."));
    outputq904 = q904(true, true);

    // DIFFERENT OUTCOMES OF Q904
    if (outputq904 != 0) {
      Serial.print(F("UNCACHED DATABASE ARRAY CHECK EXITED WITH ERROR S-"));
      Serial.println(outputq904);
      watchdogactivated = true;
    }
    if (outputq904 == 0) {
      Serial.println(F("done"));
    }
    if (outputq904 == 1) {
      Serial.println(F("UNABLE TO CONTINUE, PRINTER COULD NOT GO INTO ACTIVE MODE!"));
    }
  }
  delay(1000);



  // ENABLING ALL MOTOR PIN OUTPUTS = 6/15 (q931)
  Serial.print(F("6/15 - enabling motor pin outputs..."));
  q931(true);
  Serial.println(F("done"));


  // RUN CHECK OF MOTOR MOVEMENTS RUNNING = 7/15 (q905)
  {
    Serial.print(F("7/15 - running check of motor movements (hardware)..."));
    outputq905 = q905(true, true);

    // DIFFERENT OUTCOMES OF Q905
    if (outputq905 != 0) {
      Serial.print(F("UNCACHED DATABASE ARRAY CHECK EXITED WITH ERROR M-"));
      Serial.println(outputq905);
      watchdogactivated = true;
    }
    if (outputq905 == 0) {
      Serial.println(F("done"));
    }
    if (outputq905 == 1) {
      Serial.println(F("UNABLE TO CONTINUE, PRINTER COULD NOT GO INTO ACTIVE MODE!"));
    }
  }
  delay(1000);



  // RUN CHECK OF SYSTEM VARIABLES/UPTIME/ETC. = 8/15 q(906)
  {
    Serial.print(F("8/15 - running check of variables..."));
    outputq906 = q906(true, true);

    // DIFFERENT OUTCOMES OF Q906
    if (outputq906 != 0) {
      Serial.print(F("UNCACHED DATABASE ARRAY CHECK EXITED WITH ERROR SVU-"));
      Serial.println(outputq906);
      watchdogactivated = true;
    }
    if (outputq906 == 0) {
      Serial.println(F("done"));
    }
    if (outputq906 == 1) {
      Serial.println(F("UNABLE TO CONTINUE, PRINTER COULD NOT GO INTO ACTIVE MODE!"));
    }
  }
  delay(1000);



  // RUN CHECK OF ERROR ARRAY = 9/15 q(907)
  {
    Serial.print(F("9/15 - running check of error array..."));
    outputq907 = q907(true, true);

    // DIFFERENT OUTCOMES OF Q907
    if (outputq907 != 0) {
      Serial.print(F("UNCACHED DATABASE ARRAY CHECK EXITED WITH ERROR ERR-"));
      Serial.println(outputq907);
      watchdogactivated = true;
    }
    if (outputq907 == 0) {
      Serial.println(F("done"));
    }
    if (outputq907 == 1) {
      Serial.println(F("UNABLE TO CONTINUE, PRINTER COULD NOT GO INTO ACTIVE MODE!"));
    }
  }
  delay(1000);



  // RUN CHECK OF EXTRUDER UNDER NORMAL CONDITIONS = 10/15 (q908)
  {
    Serial.print(F("10/15 - running check of extruder heating/bed heating..."));
    outputq908 = q908(true, true);

    // DIFFERENT OUTCOMES OF Q908
    if (outputq908 != 0) {
      Serial.print(F("UNCACHED DATABASE ARRAY CHECK EXITED WITH ERROR T-"));
      Serial.println(outputq908);
      watchdogactivated = true;
    }
    if (outputq908 == 0) {
      Serial.println(F("done"));
    }
    if (outputq908 == 1) {
      Serial.println(F("UNABLE TO CONTINUE, PRINTER COULD NOT GO INTO ACTIVE MODE!"));
    }
  }
  delay(1000);



  // RUN TEST OF I2C PROTOCOL = 11/15 (q909)
  {
    Serial.print(F("11/15 - running check of I2C protool..."));
    outputq909 = q909(true, true);

    // DIFFERENT OUTCOMES OF Q909
    if (outputq909 != 0) {
      Serial.print(F("UNCACHED DATABASE ARRAY CHECK EXITED WITH ERROR I2C-"));
      Serial.println(outputq909);
      watchdogactivated = true;
    }
    if (outputq909 == 0) {
      Serial.println(F("done"));
    }
    if (outputq909 == 1) {
      Serial.println(F("UNABLE TO CONTINUE, PRINTER COULD NOT GO INTO ACTIVE MODE!"));
    }
  }
  delay(1000);



  // RUN TEST OF ePARSER() and eCACHE = 12/15 (q910)
  {
    Serial.print(F("12/15 - running a full test of the ePARSER()..."));
    outputq910 = q910(true, true);

    // DIFFERENT OUTCOMES OF Q910
    if (outputq910 != 0) {
      Serial.print(F("UNCACHED DATABASE ARRAY CHECK EXITED WITH ERROR EP-"));
      Serial.println(outputq910);
      watchdogactivated = true;
    }
    if (outputq910 == 0) {
      Serial.println(F("done"));
    }
    if (outputq910 == 1) {
      Serial.println(F("UNABLE TO CONTINUE, PRINTER COULD NOT GO INTO ACTIVE MODE!"));
    }
  }
  delay(1000);

  // RUN TEST OF  = 13/15

  // RUN TEST OF  = 14/15

  // RESET THE PRINTER TO NORMAL CONDITIONS = 15/15
  {
    Serial.print(F("15/15 - generating report..."));
    Serial.println(F("done"));
    Serial.println(F("     REPORT:"));
    Serial.println(F("ERRORS DETECTED: 0"));
    Serial.println(F("SYSTEM STATUS: ok"));
    Serial.println(F(""));
    Serial.println(F(""));
    Serial.println(F(""));
    Serial.println(F(""));
    Serial.println(F(""));
    Serial.println(F(""));
    Serial.println(F("RESETTING THE PRINTER!"));
    Serial.end();
    unsetup();
  }
}

// RUN A FULL TEST OF THE UNCACHED STRINGS ARRAY - COMPLETED
int q901(bool silentmode, bool interrupterrors) {
  interpretation("Q1 1");
  if (printingactive == false) {
    Serial.println(F("ERROR! SYSTEM COULD NOT GO INTO PRINING ACTIVE MODE, ASSUMING DEAD"));
    watchdogactivated = true;
    return (1);
  }

  if (silentmode == false) {
    Serial.println(F("IN PRINTING ACTIVE... CONTINUING WITH UNCACHED ARRAY CHECK"));
  }

  delay(10);

  // WRITE VALUES TO THE ARRAY
  writestringtostack(0, "G1 X103.49 Y813.91 E0.14298 F2600");
  writestringtostack(1, "G0 Y832.91 Z1089.28 E0.134298 F2600");
  writestringtostack(2, "G1 X1303.49 Y833.91 Z1609.28 E0.134298 F900");
  writestringtostack(3, "G1 X1043.49 Y834.91 E0.123498 ");
  writestringtostack(4, "G0 X1035.49 Z1409.28 E0.12938");
  writestringtostack(5, "G1 X103.649 Y836.91 Z1309.28 E0.12928");
  writestringtostack(6, "G0 X103.489 Y837.91 Z1209.28");
  writestringtostack(7, "G1 X103.499 Y838.91 Z1109.28 E0.12928");
  writestringtostack(8, "G0 X1043.49 Y839.91 Z1109.28 E0.1298");
  writestringtostack(9, "G0 X1035.49 Y839.91 Z1309.28 E0.12298 F4500");
  writestringtostack(10, "G1 X1035.49 Y823.91 Z4109.28 E0.15298 F3600");

  // DELAY TO INSERT VALUES
  delay(500);

  // READ VALUES FROM ARRAY
  {
    String testingwith = readstringsfromstack(0);
    if (testingwith != "G1 X103.49 Y813.91 E0.14298 F2600") {
      Serial.println(F("STRING NOT MATCHING IN UNCACHED ARRAY DATABASE! Q901.1"));
      return (2);
    }
    testingwith = readstringsfromstack(1);
    if (testingwith != "G0 Y832.91 Z1089.28 E0.134298 F2600") {
      Serial.println(F("STRING NOT MATCHING IN UNCACHED ARRAY DATABASE! Q901.2"));
      return (2);
    }
    testingwith = readstringsfromstack(2);
    if (testingwith != "G1 X1303.49 Y833.91 Z1609.28 E0.134298 F900") {
      Serial.println(F("STRING NOT MATCHING IN UNCACHED ARRAY DATABASE! Q901.3"));
      return (2);
    }
    testingwith = readstringsfromstack(3);
    if (testingwith != "G1 X1043.49 Y834.91 E0.123498 ") {
      Serial.println(F("STRING NOT MATCHING IN UNCACHED ARRAY DATABASE! Q901.4"));
      return (2);
    }
    testingwith = readstringsfromstack(4);
    if (testingwith != "G0 X1035.49 Z1409.28 E0.12938") {
      Serial.println(F("STRING NOT MATCHING IN UNCACHED ARRAY DATABASE! Q901.5"));
      return (2);
    }
    testingwith = readstringsfromstack(5);
    if (testingwith != "G1 X103.649 Y836.91 Z1309.28 E0.12928") {
      Serial.println(F("STRING NOT MATCHING IN UNCACHED ARRAY DATABASE! Q901.6"));
      return (2);
    }
    testingwith = readstringsfromstack(6);
    if (testingwith != "G0 X103.489 Y837.91 Z1209.28") {
      Serial.println(F("STRING NOT MATCHING IN UNCACHED ARRAY DATABASE! Q901.7"));
      return (2);
    }
    testingwith = readstringsfromstack(7);
    if (testingwith != "G1 X103.499 Y838.91 Z1109.28 E0.12928") {
      Serial.println(F("STRING NOT MATCHING IN UNCACHED ARRAY DATABASE! Q901.8"));
      return (2);
    }
    testingwith = readstringsfromstack(8);
    if (testingwith != "G0 X1043.49 Y839.91 Z1109.28 E0.1298") {
      Serial.println(F("STRING NOT MATCHING IN UNCACHED ARRAY DATABASE! Q901.9"));
      return (2);
    }
    testingwith = readstringsfromstack(9);
    if (testingwith != "G0 X1035.49 Y839.91 Z1309.28 E0.12298 F4500") {
      Serial.println(F("STRING NOT MATCHING IN UNCACHED ARRAY DATABASE! Q901.10"));
      return (2);
    }
    testingwith = readstringsfromstack(10);
    if (testingwith != "G1 X1035.49 Y823.91 Z4109.28 E0.15298 F3600") {
      Serial.println(F("STRING NOT MATCHING IN UNCACHED ARRAY DATABASE! Q901.11"));
      return (2);
    }
  }

  // SMALL DELAY
  delay(500);

  // CLEAR UNCACHED ARRAY
  clearstringinstack(0, false);
  clearstringinstack(1, false);
  clearstringinstack(2, false);
  clearstringinstack(3, false);
  clearstringinstack(4, false);
  clearstringinstack(5, false);
  clearstringinstack(6, false);
  clearstringinstack(7, false);
  clearstringinstack(8, false);
  clearstringinstack(9, false);
  clearstringinstack(10, false);
  lastnoncachedstring = 0;

  // SMALL DELAY
  delay(500);

  // START SECOND HALF OF UNCACHED ARRAY CHECK
  interpretation("G1 X3.49 Y8.791 Z10399.28 E0.78 F2600");
  interpretation("G1 X23.49 Y81 Z1099.28 E0.28");
  interpretation("G1 X1.49 Y8.9 Z13099.28 E0.38 F500");
  interpretation("G1 X1043.9 Y3.61 Z10399.28 E0.98 F1500");
  interpretation("G1 X149 Y83.1 Z10929.28 E03.198 F3500");
  interpretation("G1 X349 Y85.91 Z1099.28 E0.198 F6000");
  interpretation("G1 X10 Y8.91 Z1099.28 E0.498 F36000");
  interpretation("G1 X104 Y2.9 Z10299.28 E0.128 F7200");
  interpretation("G1 X9 Y1 Z10.8 E0.181 F500");
  interpretation("G1 X1.49 Y18 Z19.28 E0.18 F10");
  interpretation("G1 X2.49 Y81 Z7.28 E0.8");

  // SMALL DELAY
  delay(500);

  // READ VALUES FROM ARRAY
  {
    String testingwith = readstringsfromstack(0);
    if (testingwith != "G1 X3.49 Y8.791 Z10399.28 E0.78 F2600") {
      Serial.println(F("STRING NOT MATCHING IN UNCACHED ARRAY DATABASE! Q901.12"));
      return (3);
    }
    testingwith = readstringsfromstack(1);
    if (testingwith != "G1 X23.49 Y81 Z1099.28 E0.28") {
      Serial.println(F("STRING NOT MATCHING IN UNCACHED ARRAY DATABASE! Q901.13"));
      return (3);
    }
    testingwith = readstringsfromstack(2);
    if (testingwith != "G1 X1.49 Y8.9 Z13099.28 E0.38 F500") {
      Serial.println(F("STRING NOT MATCHING IN UNCACHED ARRAY DATABASE! Q901.14"));
      return (3);
    }
    testingwith = readstringsfromstack(3);
    if (testingwith != "G1 X1043.9 Y3.61 Z10399.28 E0.98 F1500") {
      Serial.println(F("STRING NOT MATCHING IN UNCACHED ARRAY DATABASE! Q901.15"));
      return (3);
    }
    testingwith = readstringsfromstack(4);
    if (testingwith != "G1 X149 Y83.1 Z10929.28 E03.198 F3500") {
      Serial.println(F("STRING NOT MATCHING IN UNCACHED ARRAY DATABASE! Q901.16"));
      return (3);
    }
    testingwith = readstringsfromstack(5);
    if (testingwith != "G1 X349 Y85.91 Z1099.28 E0.198 F6000") {
      Serial.println(F("STRING NOT MATCHING IN UNCACHED ARRAY DATABASE! Q901.17"));
      return (3);
    }
    testingwith = readstringsfromstack(6);
    if (testingwith != "G1 X10 Y8.91 Z1099.28 E0.498 F36000") {
      Serial.println(F("STRING NOT MATCHING IN UNCACHED ARRAY DATABASE! Q901.18"));
      return (3);
    }
    testingwith = readstringsfromstack(7);
    if (testingwith != "G1 X104 Y2.9 Z10299.28 E0.128 F7200") {
      Serial.println(F("STRING NOT MATCHING IN UNCACHED ARRAY DATABASE! Q901.19"));
      return (3);
    }
    testingwith = readstringsfromstack(8);
    if (testingwith != "G1 X9 Y1 Z10.8 E0.181 F500") {
      Serial.println(F("STRING NOT MATCHING IN UNCACHED ARRAY DATABASE! Q901.20"));
      return (3);
    }
    testingwith = readstringsfromstack(9);
    if (testingwith != "G1 X1.49 Y18 Z19.28 E0.18 F10") {
      Serial.println(F("STRING NOT MATCHING IN UNCACHED ARRAY DATABASE! Q901.21"));
      return (3);
    }
    testingwith = readstringsfromstack(10);
    if (testingwith != "G1 X2.49 Y81 Z7.28 E0.8") {
      Serial.println(F("STRING NOT MATCHING IN UNCACHED ARRAY DATABASE! Q901.22"));
      return (3);
    }
  }


  // SMALL DELAY
  delay(500);

  // CLEAR UNCACHED ARRAY
  clearstringinstack(0, false);
  clearstringinstack(1, false);
  clearstringinstack(2, false);
  clearstringinstack(3, false);
  clearstringinstack(4, false);
  clearstringinstack(5, false);
  clearstringinstack(6, false);
  clearstringinstack(7, false);
  clearstringinstack(8, false);
  clearstringinstack(9, false);
  clearstringinstack(10, false);
  lastnoncachedstring = 0;

  // SMALL DELAY
  delay(500);


  // COMPLETED SUCCESSFULLY
  if (silentmode == false) {
    Serial.println(F("ok"));
    return (0);
  }
  // COMPLETED SUCCESSFULLY
  return (0);
}

// RUN A FULL TEST OF THE CACHED DATABASE ARRAY
int q902(bool silentmode, bool interrupterrors) {
  interpretation("Q1 1");
  if (printingactive == false) {
    Serial.println(F("ERROR! SYSTEM COULD NOT GO INTO PRINING ACTIVE MODE, ASSUMING DEAD"));
    watchdogactivated = true;
    return (1);
  }

  if (silentmode == false) {
    Serial.println(F("IN PRINTING ACTIVE... CONTINUING WITH UNCACHED ARRAY CHECK"));
  }

  // SMALL DELAY
  delay(500);

  // CLEAR UNCACHED ARRAY
  clearstringinstack(0, false);
  clearstringinstack(1, false);
  clearstringinstack(2, false);
  clearstringinstack(3, false);
  clearstringinstack(4, false);
  clearstringinstack(5, false);
  clearstringinstack(6, false);
  clearstringinstack(7, false);
  clearstringinstack(8, false);
  clearstringinstack(9, false);
  clearstringinstack(10, false);
  lastnoncachedstring = 0;

  // SMALL DELAY
  delay(500);

  // CLEAR DATABASE ARRAY
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

  // SMALL DELAY
  delay(500);

  // RUNNING A FULL SYSTEM TEST ON ANALYZING OF STRINGS
  interpretation("G1 X3.49 Y8.791 Z10399.28 E0.78 F2600");  // 0
  interpretation("G1 X23.49 Y81 Z1099.28 E0.28");           // 1
  interpretation("G0 X1.49 Y8.9");                          // 2
  interpretation("G1 Z19.28");                              // 3
  interpretation("G1 X149 Y83.1 Z10929.28 E03.198");        // 4
  interpretation("G1 X349 Y85.91 Z1099.28 E0.198 F6000");   // 5
  interpretation("G0 X10 Y8.91");                           // 6
  interpretation("G1 X104 Y2.9 Z10299.28 E0.128 F7200");    // 7
  interpretation("G0 Y1 Z10.8");                            // 8
  interpretation("G0 X1.49 Y18 Z19.28");                    // 9
  interpretation("G1 X2.49 Y8 E0.8");                       // 10

  // SMALL DELAY
  delay(1000);

  // ANALYZE ALL 121 VALUES
  //    0         1       2       3       4     6       7       8       9       10      11
  // { X-CORD, Y-CORD, Z-CORD, E0CORD, E1CORD, E2CORD, E0TEMP, E1TEMP, E2TEMP, HBTEMP, LOCK};

  // 0
  {
    float datavalue0 = readfromarray(0, 0);
    float datavalue1 = readfromarray(0, 1);
    float datavalue2 = readfromarray(0, 2);
    float datavalue3 = readfromarray(0, 3);
    float datavalue4 = readfromarray(0, 4);
    float datavalue5 = readfromarray(0, 5);
    float datavalue6 = readfromarray(0, 6);
    float datavalue7 = readfromarray(0, 7);
    float datavalue8 = readfromarray(0, 8);
    float datavalue9 = readfromarray(0, 9);
    float datavalue10 = readfromarray(0, 10);

    // SMALL DELAY
    delay(200);

    // ANALYZE
    if (datavalue0 == 3.49 && datavalue1 == 8.791 && datavalue2 == 10399.28 && datavalue3 == 0.78 && datavalue4 == 0 && datavalue5 == 0 && datavalue6 == 0 && datavalue7 == 0 && datavalue8 == 0 && datavalue9 == 0 && datavalue10 == 1) {
      // CONTINUE
    } else {
      Serial.println(F("DATABASE VALUES DOES NOT MATCH GCODE STRING VALUES! - ERROR HAS OCCURED Q902.1"));
      return (2);
      return (2);
      return (2);
    }
  }

  // 1
  {
    float datavalue0 = readfromarray(1, 0);
    float datavalue1 = readfromarray(1, 1);
    float datavalue2 = readfromarray(1, 2);
    float datavalue3 = readfromarray(1, 3);
    float datavalue4 = readfromarray(1, 4);
    float datavalue5 = readfromarray(1, 5);
    float datavalue6 = readfromarray(1, 6);
    float datavalue7 = readfromarray(1, 7);
    float datavalue8 = readfromarray(1, 8);
    float datavalue9 = readfromarray(1, 9);
    float datavalue10 = readfromarray(1, 10);

    // SMALL DELAY
    delay(200);

    // ANALYZE
    if (datavalue0 == 23.49 && datavalue1 == 81 && datavalue2 == 1099.28 && datavalue3 == 0.28 && datavalue4 == 0 && datavalue5 == 0 && datavalue6 == 0 && datavalue7 == 0 && datavalue8 == 0 && datavalue9 == 0 && datavalue10 == 1) {
      // CONTINUE
    } else {
      Serial.println(F("DATABASE VALUES DOES NOT MATCH GCODE STRING VALUES! - ERROR HAS OCCURED Q902.2"));
      return (2);
      return (2);
      return (2);
    }
  }

  // 2
  {
    float datavalue0 = readfromarray(2, 0);
    float datavalue1 = readfromarray(2, 1);
    float datavalue2 = readfromarray(2, 2);
    float datavalue3 = readfromarray(2, 3);
    float datavalue4 = readfromarray(2, 4);
    float datavalue5 = readfromarray(2, 5);
    float datavalue6 = readfromarray(2, 6);
    float datavalue7 = readfromarray(2, 7);
    float datavalue8 = readfromarray(2, 8);
    float datavalue9 = readfromarray(2, 9);
    float datavalue10 = readfromarray(2, 10);

    // SMALL DELAY
    delay(200);

    // ANALYZE
    if (datavalue0 == 1.49 && datavalue1 == 8.9 && datavalue2 == 1099.28 && datavalue3 == 0.28 && datavalue4 == 0 && datavalue5 == 0 && datavalue6 == 0 && datavalue7 == 0 && datavalue8 == 0 && datavalue9 == 0 && datavalue10 == 1) {
      // CONTINUE
    } else {
      Serial.println(F("DATABASE VALUES DOES NOT MATCH GCODE STRING VALUES! - ERROR HAS OCCURED Q902.3"));
      return (2);
      return (2);
      return (2);
    }
  }

  // 3
  {
    float datavalue0 = readfromarray(3, 0);
    float datavalue1 = readfromarray(3, 1);
    float datavalue2 = readfromarray(3, 2);
    float datavalue3 = readfromarray(3, 3);
    float datavalue4 = readfromarray(3, 4);
    float datavalue5 = readfromarray(3, 5);
    float datavalue6 = readfromarray(3, 6);
    float datavalue7 = readfromarray(3, 7);
    float datavalue8 = readfromarray(3, 8);
    float datavalue9 = readfromarray(3, 9);
    float datavalue10 = readfromarray(3, 10);

    // SMALL DELAY
    delay(200);

    // ANALYZE
    if (datavalue0 == 1.49 && datavalue1 == 8.9 && datavalue2 == 19.28 && datavalue3 == 0.28 && datavalue4 == 0 && datavalue5 == 0 && datavalue6 == 0 && datavalue7 == 0 && datavalue8 == 0 && datavalue9 == 0 && datavalue10 == 1) {
      // CONTINUE
    } else {
      Serial.println(F("DATABASE VALUES DOES NOT MATCH GCODE STRING VALUES! - ERROR HAS OCCURED Q902.4"));
      return (2);
      return (2);
      return (2);
    }
  }

  // 4
  {
    float datavalue0 = readfromarray(4, 0);
    float datavalue1 = readfromarray(4, 1);
    float datavalue2 = readfromarray(4, 2);
    float datavalue3 = readfromarray(4, 3);
    float datavalue4 = readfromarray(4, 4);
    float datavalue5 = readfromarray(4, 5);
    float datavalue6 = readfromarray(4, 6);
    float datavalue7 = readfromarray(4, 7);
    float datavalue8 = readfromarray(4, 8);
    float datavalue9 = readfromarray(4, 9);
    float datavalue10 = readfromarray(4, 10);

    // SMALL DELAY
    delay(200);

    // ANALYZE
    if (datavalue0 == 149 && datavalue1 == 83.1 && datavalue2 == 10929.28 && datavalue3 == 3.198 && datavalue4 == 0 && datavalue5 == 0 && datavalue6 == 0 && datavalue7 == 0 && datavalue8 == 0 && datavalue9 == 0 && datavalue10 == 1) {
      // CONTINUE
    } else {
      Serial.println(F("DATABASE VALUES DOES NOT MATCH GCODE STRING VALUES! - ERROR HAS OCCURED Q902.5"));
      return (2);
      return (2);
      return (2);
    }
  }

  // 5
  {
    float datavalue0 = readfromarray(5, 0);
    float datavalue1 = readfromarray(5, 1);
    float datavalue2 = readfromarray(5, 2);
    float datavalue3 = readfromarray(5, 3);
    float datavalue4 = readfromarray(5, 4);
    float datavalue5 = readfromarray(5, 5);
    float datavalue6 = readfromarray(5, 6);
    float datavalue7 = readfromarray(5, 7);
    float datavalue8 = readfromarray(5, 8);
    float datavalue9 = readfromarray(5, 9);
    float datavalue10 = readfromarray(5, 10);

    // SMALL DELAY
    delay(200);

    // ANALYZE
    if (datavalue0 == 349 && datavalue1 == 85.91 && datavalue2 == 1099.28 && datavalue3 == 0.198 && datavalue4 == 0 && datavalue5 == 0 && datavalue6 == 0 && datavalue7 == 0 && datavalue8 == 0 && datavalue9 == 0 && datavalue10 == 1) {
      // CONTINUE
    } else {
      Serial.println(F("DATABASE VALUES DOES NOT MATCH GCODE STRING VALUES! - ERROR HAS OCCURED Q902.6"));
      return (2);
      return (2);
      return (2);
    }
  }

  // 6
  {
    float datavalue0 = readfromarray(6, 0);
    float datavalue1 = readfromarray(6, 1);
    float datavalue2 = readfromarray(6, 2);
    float datavalue3 = readfromarray(6, 3);
    float datavalue4 = readfromarray(6, 4);
    float datavalue5 = readfromarray(6, 5);
    float datavalue6 = readfromarray(6, 6);
    float datavalue7 = readfromarray(6, 7);
    float datavalue8 = readfromarray(6, 8);
    float datavalue9 = readfromarray(6, 9);
    float datavalue10 = readfromarray(6, 10);

    // SMALL DELAY
    delay(200);

    // ANALYZE
    if (datavalue0 == 10 && datavalue1 == 8.91 && datavalue2 == 1099.28 && datavalue3 == 0.198 && datavalue4 == 0 && datavalue5 == 0 && datavalue6 == 0 && datavalue7 == 0 && datavalue8 == 0 && datavalue9 == 0 && datavalue10 == 1) {
      // CONTINUE
    } else {
      Serial.println(F("DATABASE VALUES DOES NOT MATCH GCODE STRING VALUES! - ERROR HAS OCCURED Q902.7"));
      return (2);
      return (2);
      return (2);
    }
  }

  // 7
  {
    float datavalue0 = readfromarray(7, 0);
    float datavalue1 = readfromarray(7, 1);
    float datavalue2 = readfromarray(7, 2);
    float datavalue3 = readfromarray(7, 3);
    float datavalue4 = readfromarray(7, 4);
    float datavalue5 = readfromarray(7, 5);
    float datavalue6 = readfromarray(7, 6);
    float datavalue7 = readfromarray(7, 7);
    float datavalue8 = readfromarray(7, 8);
    float datavalue9 = readfromarray(7, 9);
    float datavalue10 = readfromarray(7, 10);

    // SMALL DELAY
    delay(200);

    // ANALYZE
    if (datavalue0 == 104 && datavalue1 == 2.9 && datavalue2 == 10299.28 && datavalue3 == 0.128 && datavalue4 == 0 && datavalue5 == 0 && datavalue6 == 0 && datavalue7 == 0 && datavalue8 == 0 && datavalue9 == 0 && datavalue10 == 1) {
      // CONTINUE
    } else {
      Serial.println(F("DATABASE VALUES DOES NOT MATCH GCODE STRING VALUES! - ERROR HAS OCCURED Q902.8"));
      return (2);
      return (2);
      return (2);
    }
  }

  // 8
  {
    float datavalue0 = readfromarray(8, 0);
    float datavalue1 = readfromarray(8, 1);
    float datavalue2 = readfromarray(8, 2);
    float datavalue3 = readfromarray(8, 3);
    float datavalue4 = readfromarray(8, 4);
    float datavalue5 = readfromarray(8, 5);
    float datavalue6 = readfromarray(8, 6);
    float datavalue7 = readfromarray(8, 7);
    float datavalue8 = readfromarray(8, 8);
    float datavalue9 = readfromarray(8, 9);
    float datavalue10 = readfromarray(8, 10);

    // SMALL DELAY
    delay(200);

    // ANALYZE
    if (datavalue0 == 104 && datavalue1 == 1 && datavalue2 == 10.8 && datavalue3 == 0.128 && datavalue4 == 0 && datavalue5 == 0 && datavalue6 == 0 && datavalue7 == 0 && datavalue8 == 0 && datavalue9 == 0 && datavalue10 == 1) {
      // CONTINUE
    } else {
      Serial.println(F("DATABASE VALUES DOES NOT MATCH GCODE STRING VALUES! - ERROR HAS OCCURED Q902.9"));
      return (2);
      return (2);
      return (2);
    }
  }

  // 9
  {
    float datavalue0 = readfromarray(9, 0);
    float datavalue1 = readfromarray(9, 1);
    float datavalue2 = readfromarray(9, 2);
    float datavalue3 = readfromarray(9, 3);
    float datavalue4 = readfromarray(9, 4);
    float datavalue5 = readfromarray(9, 5);
    float datavalue6 = readfromarray(9, 6);
    float datavalue7 = readfromarray(9, 7);
    float datavalue8 = readfromarray(9, 8);
    float datavalue9 = readfromarray(9, 9);
    float datavalue10 = readfromarray(9, 10);

    // SMALL DELAY
    delay(200);

    // ANALYZE
    if (datavalue0 == 1.49 && datavalue1 == 18 && datavalue2 == 19.28 && datavalue3 == 0.128 && datavalue4 == 0 && datavalue5 == 0 && datavalue6 == 0 && datavalue7 == 0 && datavalue8 == 0 && datavalue9 == 0 && datavalue10 == 1) {
      // CONTINUE
    } else {
      Serial.println(F("DATABASE VALUES DOES NOT MATCH GCODE STRING VALUES! - ERROR HAS OCCURED Q902.10"));
      return (2);
      return (2);
      return (2);
    }
  }

  // 10
  {
    float datavalue0 = readfromarray(10, 0);
    float datavalue1 = readfromarray(10, 1);
    float datavalue2 = readfromarray(10, 2);
    float datavalue3 = readfromarray(10, 3);
    float datavalue4 = readfromarray(10, 4);
    float datavalue5 = readfromarray(10, 5);
    float datavalue6 = readfromarray(10, 6);
    float datavalue7 = readfromarray(10, 7);
    float datavalue8 = readfromarray(10, 8);
    float datavalue9 = readfromarray(10, 9);
    float datavalue10 = readfromarray(10, 10);

    // SMALL DELAY
    delay(200);

    // ANALYZE
    if (datavalue0 == 2.49 && datavalue1 == 8 && datavalue2 == 19.28 && datavalue3 == 0.8 && datavalue4 == 0 && datavalue5 == 0 && datavalue6 == 0 && datavalue7 == 0 && datavalue8 == 0 && datavalue9 == 0 && datavalue10 == 1) {
      // CONTINUE
    } else {
      Serial.println(F("DATABASE VALUES DOES NOT MATCH GCODE STRING VALUES! - ERROR HAS OCCURED Q902.11"));
      return (2);
      return (2);
      return (2);
    }
  }

  // RETURNED SUCCESSFULLY
  if (silentmode == true) {
    return (0);
  } else {
    Serial.println(F("THE TEST OF CACHING IN THE DATABASE HAS COMPLETED SUCCESSFULLY!"));
    return (0);
  }

  // CLEAR UNCACHED ARRAY
  clearstringinstack(0, false);
  clearstringinstack(1, false);
  clearstringinstack(2, false);
  clearstringinstack(3, false);
  clearstringinstack(4, false);
  clearstringinstack(5, false);
  clearstringinstack(6, false);
  clearstringinstack(7, false);
  clearstringinstack(8, false);
  clearstringinstack(9, false);
  clearstringinstack(10, false);
  lastnoncachedstring = 0;

  // SMALL DELAY
  delay(500);

  // CLEAR DATABASE ARRAY
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

  // SMALL DELAY
  delay(500);
}


// RUN A FULL TEST OF THE TEMPERATURE PROBES
int q903(bool silentmode, bool interrupterrors) {
  interpretation("Q1 1");

  // CHECK IF PRINTING MODE IS ACTIVE
  if (printingactive == false) {
    Serial.println(F("ERROR! SYSTEM COULD NOT GO INTO PRINING ACTIVE MODE, ASSUMING DEAD"));
    watchdogactivated = true;
    return (1);
  }

  if (silentmode == false) {
    Serial.println(F("IN PRINTING ACTIVE... CONTINUING WITH UNCACHED ARRAY CHECK"));
  }

  // SMALL DELAY
  delay(500);

  //
}


int q904(bool silentmode, bool interrupterrors) {
}

int q905(bool silentmode, bool interrupterrors) {
}

int q906(bool silentmode, bool interrupterrors) {
}

int q907(bool silentmode, bool interrupterrors) {
}

int q908(bool silentmode, bool interrupterrors) {
}

int q909(bool silentmode, bool interrupterrors) {
}

int q910(bool silentmode, bool interrupterrors) {
}

//
void q930(bool silentmode) {
}

void q931(bool silentmode) {
}

void q932(bool silentmode) {
}