void quickprint() {
  Serial.println(F("QUICK SYSTEM TEST CALLED!"));
  Serial.println(F("GENERATING REPORT..."));

  delay(1000);

  Serial.println(F("SYSTEM REPORT OF 3D PRINTER:"));
  Serial.print(F("Printer Hostname: "));
  Serial.println(printerhostname);
  Serial.print(F("Printer MAC Address: "));
  Serial.println(printerMACaddress);
  Serial.print(F("Printer Version: "));
  Serial.println(PRINTERVERSION);

  Serial.println(F(""));

  Serial.print(F("Passwords: "));
  if (dpswd == "HIMRANDERSON" && cpswd == "" && tpswd == "" && pswd6 == "") {
    Serial.println(F("NO"));
  } else {
    Serial.println(F("Yes"));
  }

  Serial.println(F(""));

  Serial.println(F("GENERAL INFORMATION"));

  Serial.print(F("Time Since Startup: "));
  Serial.println(timesincestartup);
  Serial.print(F("Watchdog Activated: "));
  Serial.println(watchdogactivated);
  Serial.print(F("Debug Serial: "));
  Serial.println(debugserial);
  Serial.print(F("Restart from Power Loss: "));
  Serial.println(printingactive);
  Serial.print(F("Currently Locked: "));
  Serial.println(currentlylocked);

  Serial.println(F("EEPROM_INFORMATION"));

  bool variablesnotset = false;
  bool errorsfound = false;






  if (errorsfound == true) {
    Serial.println(F("ERRORS FOUND: "));
    if (variablesnotset == true) {
      Serial.println(F("   - VAR - Variables Not Set in EEPROM"));
      Serial.println(F("           Setting EEPROM and Restarting"));
    }
  }
}

void fullprint() {
}