/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

// SERIAL INFORMATION
void serialReceiver() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    } else {
      receivedChars[ndx] = '\0';
      ndx = 0;
      newData = true;
      receivedSerial3000 = receivedChars;
      int working = interpretation(receivedSerial3000);
      newData = false;
      receivedSerial3000 = "";
      receivedChars == "";
    }
  }
}

int interpretation(String commanding) {
  if (commanding == "OK") {
    tempcalibration();
    digitalWrite(HEATER_0_PIN, LOW);
    digitalWrite(HEATER_1_PIN, LOW);
    digitalWrite(HEATER_HB_PIN, LOW);
  }

  if (commanding == "starte0") {
    Serial.println(F(""));
    Serial.println(F(""));
    Serial.println(F(""));
    Serial.println(F("STARTING EXTRUDER E0 HEATING IN 3 SECONDS"));
    Serial.println(F("3"));
    delay(1000);
    Serial.println(F("2"));
    delay(1000);
    Serial.println(F("1"));
    delay(1000);
    Serial.println(F("HEATING"));
    digitalWrite(HEATER_0_PIN, HIGH);
  }

  if (commanding == "starthb") {
    Serial.println(F(""));
    Serial.println(F(""));
    Serial.println(F(""));
    Serial.println(F("STARTING HEATED BED HEATING IN 3 SECONDS"));
    Serial.println(F("3"));
    delay(1000);
    Serial.println(F("2"));
    delay(1000);
    Serial.println(F("1"));
    delay(1000);
    Serial.println(F("HEATING"));
    digitalWrite(HEATER_HB_PIN, HIGH);
  }
}