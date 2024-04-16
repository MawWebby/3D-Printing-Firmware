void quickprint() {
  Serial.println(F("QUICK SYSTEM TEST CALLED!"));
  Serial.println(F("GENERATING REPORT..."));
  Serial.println(F(""));
  Serial.println(F(""));
  Serial.println(F(""));
  Serial.println(F(""));




  delay(1000);




  Serial.println(F("!!!BEGIN SYSTEM REPORT OF 3D PRINTER!!!"));
  Serial.println(F(""));
  Serial.println(F(""));
  Serial.println(F(""));
  Serial.println(F(""));
  Serial.print(F("Printer Hostname: "));
  Serial.println(printerhostname);
  Serial.print(F("Printer MAC Address: "));
  Serial.println(printerMACaddress);
  Serial.print(F("Printer Version: "));
  Serial.println(PRINTERVERSION);
  Serial.print(F("Passwords: "));
  if (dpswd == "HIMRANDERSON" && cpswd == "" && tpswd == "" && pswd6 == "") {
    Serial.println(F("NO"));
  } else {
    Serial.println(F("Yes"));
  }
  Serial.println(F(""));



  Serial.println(F("GENERAL INFORMATION-----------------"));
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
  Serial.print(F("Completed Prints: "));
  Serial.print(readsuccessprints());
  Serial.print(F(" / "));
  Serial.print(readbadprints());
  Serial.print(F(" ("));
  Serial.print(printsuccess());
  Serial.println(F("%)"));
  Serial.println(F(""));



  Serial.println(F("EEPROM_INFORMATION-----------------"));
  Serial.print(F("EEPROM Version: "));
  Serial.print(MAJORVERSION);
  Serial.print(F("."));
  Serial.println(MINORVERSION);
  Serial.println(F(""));
  Serial.println(F("Current Database State: "));
  fulldatabaseread();
  Serial.println(F("EEPROM VALUES: "));
  Serial.println(EEPROM.read(0));
  Serial.println(EEPROM.read(1));
  Serial.println(EEPROM.read(2));
  Serial.println(EEPROM.read(3));
  Serial.println(EEPROM.read(4));
  Serial.println(EEPROM.read(5));
  Serial.println(EEPROM.read(6));
  Serial.println(EEPROM.read(7));
  Serial.println(EEPROM.read(8));
  Serial.println(EEPROM.read(9));
  Serial.println(EEPROM.read(10));
  Serial.println(EEPROM.read(11));
  Serial.println(EEPROM.read(12));
  Serial.println(EEPROM.read(13));
  Serial.println(EEPROM.read(14));



  Serial.println(F("CURRENT SYSTEM STATE---------------"));
  Serial.print(F("Printer Active: "));
  Serial.println(printingactive);
  Serial.println(F("Steppers Disabled"));
  Serial.print(xdisabled);
  Serial.print(ydisabled);
  Serial.print(zdisabled);
  Serial.print(edisabled);
  Serial.println(F(""));
  Serial.println(F("Cache:"));
  Serial.println(errorstack0);
  Serial.println(errorstack1);
  Serial.println(errorstack2);
  Serial.println(errorstack3);
  Serial.println(errorstack4);
  Serial.println(errorstack5);
  Serial.println(errorstack6);
  Serial.println(errorstack7);
  Serial.println(errorstack8);
  Serial.println(errorstack9);
  Serial.println(errorstack10);



  Serial.println(F("DIMENSION--------------------------"));
  Serial.print(F("X: "));
  Serial.print(currentxdimension);
  Serial.print(F(" / "));
  Serial.println(targetxdimension);
  Serial.print(F("Y: "));
  Serial.print(currentydimension);
  Serial.print(F(" / "));
  Serial.println(targetydimension);
  Serial.print(F("Z: "));
  Serial.print(currentzdimension);
  Serial.print(F(" / "));
  Serial.println(targetzdimension);
  Serial.print(F("E: "));
  Serial.print(currente0motordimension);
  Serial.print(F(" / "));
  Serial.println(targete0motordimension);



  Serial.println(F("HOTEND-----------------------------"));
  Serial.print(F("E0: "));
  Serial.print(currente0temp);
  Serial.print(F(" / "));
  Serial.println(targete0temp);
  Serial.print(F("HB: "));
  Serial.print(currenthbtemp);
  Serial.print(F(" / "));
  Serial.println(targethbtemp);
  Serial.print(F("AM: "));
  Serial.print(currente1temp);
  Serial.print(F(" / "));
  Serial.println(targete1temp);
  Serial.println(F(""));



  bool variablesnotset = false;
  bool errorsfound = false;



  Serial.println(F(""));
  Serial.println(F(""));



  if (errorsfound == true) {
    Serial.println(F("ERRORS FOUND!"));
    if (variablesnotset == true) {
      Serial.println(F("   - VAR - Variables Not Set in EEPROM"));
      Serial.println(F("           Setting EEPROM and Restarting"));
    }
  }



  Serial.println(F("!!!END OF SYSTEM REPORT!!!"));
}


void fullprint() {
  // DECIDED TO ONLY DO ONE SYSTEM REPORT SO BRIDGE THE OTHER ONE IN CASE OF REFERENCES
  quickprint();
}