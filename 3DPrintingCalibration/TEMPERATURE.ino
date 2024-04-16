void tempsensing() {
  rawsensore0 = 00.000;
  rawsensore1 = 00.000;
  rawsensorhb = 00.000;

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

  Serial.print(F("E0 RAW: "));
  Serial.print(rawsensore0);
  Serial.print(F(" HB RAW: "));
  Serial.print(rawsensorhb);
  Serial.print(F(" E1 RAW: "));
  Serial.print(rawsensore1);
  Serial.println(F(""));

  Serial.println(F("Once PLA is Melting, Type 'OK'"));

  if (rawsensore0 == 0) {
    Serial.println(F("RECEIVED A TEMP READING OF 0!"));
  }
  if (rawsensore1 == 0) {
    Serial.println(F("RECEIVED A TEMP READING OF 0!"));
  }
  if (rawsensorhb == 0) {
    Serial.println(F("RECEIVED A TEMP READING OF 0!"));
  }
}

void tempcalibration() {
  int testaway = 0;

  digitalWrite(HEATER_0_PIN, LOW);
  digitalWrite(HEATER_1_PIN, LOW);
  digitalWrite(HEATER_HB_PIN, LOW);

  delay(2000);

  rawsensore0 = 00.000;
  rawsensore1 = 00.000;
  rawsensorhb = 00.000;

  while (testaway <= 10) {
    testaway = testaway + 1;
    rawsensore0 = rawsensore0 + analogRead(TEMP_0_PIN);
    rawsensore1 = rawsensore1 + analogRead(TEMP_1_PIN);
    rawsensorhb = rawsensorhb + analogRead(TEMP_HB_PIN);
  }

  rawsensore0f = rawsensore0 / 10;
  rawsensore1f = rawsensore1 / 10;
  rawsensorhbf = rawsensorhb / 10;



  // CALIBRATE INITIAL!

  // ASSUMING THAT ROOM IS 72F (22.22222C)
  float e0roomoffsetpart1 = 1024 - rawsensore0in;
  float e1roomoffsetpart1 = 1024 - rawsensore1in;
  float hbroomoffsetpart1 = 1024 - rawsensorhbin;

  float e0roomoffsetpart2 = e0roomoffsetpart1 - 22.2222222;
  float e1roomoffsetpart2 = e1roomoffsetpart1 - 22.2222222;
  float hbroomoffsetpart2 = hbroomoffsetpart1 - 22.2222222;

  float e0roomoffsetpart3 = e0roomoffsetpart2 * -1;
  float e1roomoffsetpart3 = e1roomoffsetpart2 * -1;
  float hbroomoffsetpart3 = hbroomoffsetpart2 * -1;





  // CALIBRATE FINAL!

  // TAKE FINAL MEASUREMENTS
  while (testaway <= 10) {
    testaway = testaway + 1;
    rawsensore0 = rawsensore0 + analogRead(TEMP_0_PIN);
    rawsensore1 = rawsensore1 + analogRead(TEMP_1_PIN);
    rawsensorhb = rawsensorhb + analogRead(TEMP_HB_PIN);
  }


  // ASSUMING 200C
  float e0roomofffinpart1 = 1024 - rawsensore0in + e0roomoffsetpart3;
  float e1roomofffinpart1 = 1024 - rawsensore1in + e1roomoffsetpart3;


  // ASSUMING 60C
  float hbroomofffinpart1 = 1024 - rawsensorhbin + hbroomoffsetpart3;

  float e0roomofffinpart2 = e0roomofffinpart1 / 200;
  float e1roomofffinpart2 = e1roomofffinpart1 / 200;

  float hbroomofffinpart2 = hbroomofffinpart1 / 200;



  // PRINT SERIAL RESPONSE AND PROVIDE INSTRUCTIONS FROM RESULT OF THIS LOOP!
  Serial.println(F(""));
  Serial.println(F(""));
  Serial.println(F(""));
  Serial.println(F(""));
  Serial.println(F(""));
  Serial.println(F(""));
  Serial.println(F(""));
  Serial.println(F("// FINISHED CALIBRATING!"));
  Serial.println(F("// COPY AND PASTE THIS RESPONSE INTO LINES 29-34 IN 3DPrintingSketch.ino"));
  Serial.print(F("float e0intoffset = "));
  Serial.println(e0roomoffsetpart3);
  Serial.print(F("float e1intoffset = "));
  Serial.println(e1roomoffsetpart3);
  Serial.print(F("float e2intoffset = "));
  Serial.println(hbroomoffsetpart3);
  Serial.print(F("float e0tempmodifier = "));
  Serial.println(e0roomofffinpart2);
  Serial.print(F("float e1tempmodifier = "));
  Serial.println(hbroomofffinpart2);
  Serial.print(F("float hbtempmodifier = "));
  Serial.println(hbroomofffinpart2);
  Serial.println(F("// END OF OUTPUT"));
}


