// SETUP LOOP
void setup() {

  ////////////////////////////////
  // BEGIN SERIAL COMMUNICATION //
  ////////////////////////////////
  Serial.begin(115200);



  ///////////////////////////
  // DELAY 10 MILLISECONDS //
  ///////////////////////////
  delay(10);
  Serial.println(F("TEMPERATURE CALIBRATION"));



  //////////////////////////////////
  // SET DIGITAL PINMODE OUTPUTS ///
  //////////////////////////////////
  pinMode(ledpin, OUTPUT);         // PIN MODE FOR LEDPIN
  pinMode(X_STEP_PIN, OUTPUT);     // SET X-AXIS MOTOR PINMODE OUTPUTS
  pinMode(X_DIR_PIN, OUTPUT);      // SET X-AXIS MOTOR PINMODE OUTPUTS
  pinMode(X_ENABLE_PIN, OUTPUT);   // SET X-AXIS MOTOR PINMODE OUTPUTS
  pinMode(Y_STEP_PIN, OUTPUT);     // SET Y-AXIS MOTOR PINMODE OUTPUTS
  pinMode(Y_DIR_PIN, OUTPUT);      // SET Y-AXIS MOTOR PINMODE OUTPUTS
  pinMode(Y_ENABLE_PIN, OUTPUT);   // SET Y-AXIS MOTOR PINMODE OUTPUTS
  pinMode(Z_STEP_PIN, OUTPUT);     // SET Z-AXIS MOTOR PINMODE OUTPUTS
  pinMode(Z_DIR_PIN, OUTPUT);      // SET Z-AXIS MOTOR PINMODE OUTPUTS
  pinMode(Z_ENABLE_PIN, OUTPUT);   // SET Z-AXIS MOTOR PINMODE OUTPUTS
  pinMode(E_STEP_PIN, OUTPUT);     // SET E0 MOTOR PINMODE OUTPUTS
  pinMode(E_DIR_PIN, OUTPUT);      // SET E0 MOTOR PINMODE OUTPUTS
  pinMode(E_ENABLE_PIN, OUTPUT);   // SET E0 MOTOR PINMODE OUTPUTS
  pinMode(E1_STEP_PIN, OUTPUT);    // SET E1 MOTOR PINMODE OUTPUTS
  pinMode(E1_DIR_PIN, OUTPUT);     // SET E1 MOTOR PINMODE OUTPUTS
  pinMode(E1_ENABLE_PIN, OUTPUT);  // SET E1 MOTOR PINMODE OUTPUTS
  pinMode(HEATER_0_PIN, OUTPUT);   // SET HEATER MOTOR PINMODE OUTPUTS
  pinMode(HEATER_1_PIN, OUTPUT);   // SET HEATER MOTOR PINMODE OUTPUTS
  pinMode(X_MIN_PIN, INPUT);       // ENDSTOPS PINMODE INPUT
  pinMode(Y_MIN_PIN, INPUT);       // ENDSTOPS PINMODE INPUT
  pinMode(Z_MIN_PIN, INPUT);       // ENDSTOPS PINMODE INPUT
  pinMode(TEMP_0_PIN, INPUT);      // ANALOG TEMPERATURE INPUTS
  pinMode(TEMP_1_PIN, INPUT);      // ANALOG TEMPERATURE INPUTS
  pinMode(FAN_PIN, OUTPUT);        // SETUP FAN ON EXTRUDER
  pinMode(PS_ON_PIN, OUTPUT);      // SETUP PINMODE FOR POWER SUPPLY




  //////////////////////////////////
  // SET ALL PINS TO LOW AT START //
  //////////////////////////////////
  digitalWrite(X_ENABLE_PIN, HIGH);
  digitalWrite(Y_ENABLE_PIN, HIGH);
  digitalWrite(Z_ENABLE_PIN, HIGH);
  digitalWrite(E_ENABLE_PIN, HIGH);
  digitalWrite(E1_ENABLE_PIN, HIGH);
  digitalWrite(ledpin, LOW);
  digitalWrite(X_STEP_PIN, LOW);
  digitalWrite(X_DIR_PIN, LOW);
  digitalWrite(Y_STEP_PIN, LOW);
  digitalWrite(Y_DIR_PIN, LOW);
  digitalWrite(Z_STEP_PIN, LOW);
  digitalWrite(Z_DIR_PIN, LOW);
  digitalWrite(E_STEP_PIN, LOW);
  digitalWrite(E_DIR_PIN, LOW);
  digitalWrite(E1_STEP_PIN, LOW);
  digitalWrite(E1_DIR_PIN, LOW);
  digitalWrite(HEATER_0_PIN, LOW);
  digitalWrite(HEATER_1_PIN, LOW);
  digitalWrite(FAN_PIN, LOW);
  digitalWrite(PS_ON_PIN, LOW);



  //////////////////////////////////////////////////////////////
  //// READ THE INITIAL STATE OF THE ENDSTOPS AND EXTRUDERS ////
  //////////////////////////////////////////////////////////////
  delay(500);
  xendsetup = digitalRead(X_MIN_PIN);
  yendsetup = digitalRead(Y_MIN_PIN);
  zendsetup = digitalRead(Z_MIN_PIN);
  anae0read = analogRead(TEMP_0_PIN);
  anahbread = analogRead(TEMP_HB_PIN);

  Serial.println(F("STARTING SETUP!"));

  delay(1000);

  int testaway = 0;

  float rawsensore0set = 00.0001;
  float rawsensore1set = 00.0001;
  float rawsensorhbset = 00.0001;

  rawsensore0 = 00.000;
  rawsensore1 = 00.000;
  rawsensorhb = 00.000;


  while (testaway <= 10) {
    testaway = testaway + 1;
    rawsensore0 = rawsensore0 + analogRead(TEMP_0_PIN);
    rawsensore1 = rawsensore1 + analogRead(TEMP_1_PIN);
    rawsensorhb = rawsensorhb + analogRead(TEMP_HB_PIN);
  }


  rawsensore0in = rawsensore0 / 10;
  rawsensore1in = rawsensore1 / 10;
  rawsensorhbin = rawsensorhb / 10;


  if (rawsensore0in == 0) {
    Serial.println(F("RECEIVED A TEMP READING OF 0!"));
  }
  if (rawsensore1in == 0) {
    Serial.println(F("RECEIVED A TEMP READING OF 0!"));
  }
  if (rawsensorhbin == 0) {
    Serial.println(F("RECEIVED A TEMP READING OF 0!"));
  }
}


// MAIN LOOP JUST TO GET INTO OTHER LOOP AND STARTUP
void loop() {
  serialReceiver();
  delay(500);
  tempsensing();
}