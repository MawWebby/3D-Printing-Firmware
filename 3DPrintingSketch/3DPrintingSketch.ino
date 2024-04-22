// GREENWOOD LABORATORY SCHOOL
// MATTHEW WHITWORTH
// 3D PRINTER FIRMWARE
// ADVANCED GUIDED STUDY ROBOTICS


// CONTROL + SPACE


// CURRENT NUMBER OF LINES OF CODE: 9900
/*
1 0 0 0 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 
*/


///////////////////////////////
/// INITIALIZE DEPENDENCIES ///
///////////////////////////////
#include <Wire.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>
int PRINTERVERSION = 0.3;
int MAJORVERSION = 0;
int MINORVERSION = 3;
bool allowolderversions = false;



/////////////////////////////
// CHANGE THESE VARIABLES! //
/////////////////////////////
float e0intoffset = 15;
float e1intoffset = 80.62;
float e2intoffset = 80.62;
float e0tempmodifier = 0.228;
float e1tempmodifier = 0.228;
float hbtempmodifier = 0.11;

// E0TEMP MODIFIER - Y = 0.228X + 15


////////////////////////////////////
/// PIN OUTPUTS DEFINED AS BELOW ///
////////////////////////////////////
#define X_STEP_PIN 54
#define X_DIR_PIN 55
#define X_ENABLE_PIN 38
#define X_MIN_PIN 3
#define Y_STEP_PIN 60
#define Y_DIR_PIN 61
#define Y_ENABLE_PIN 56
#define Y_MIN_PIN 14
#define Z_STEP_PIN 46
#define Z_DIR_PIN 48
#define Z_ENABLE_PIN 62
#define Z_MIN_PIN 18
#define Z_MAX_PIN -1
#define E_STEP_PIN 26
#define E_DIR_PIN 28
#define E_ENABLE_PIN 24
#define E1_STEP_PIN 36
#define E1_DIR_PIN 34
#define E1_ENABLE_PIN 30
#define PS_ON_PIN -1     // ATX , awake=LOW, SLEEP=High  // NOT APPLICABLE
#define HEATER_0_PIN 10  // Extruder Heater
#define HEATER_1_PIN 8
#define TEMP_0_PIN 13   // ANALOG NUMBERING
#define TEMP_1_PIN 14   // ANALOG NUMBERING
#define TEMP_HB_PIN 16  // PROBABLY NOT
#define HEATER_HB_PIN 8
#define FAN_PIN 9
#define SDPOWER -1
#define SDCS_PIN 53
#define SD_DETECT_PIN -1   //currently not implemented
#define MASTERADDRESS 0x7  // MASTER ADDRESS FOR THE I2C CONTROLLER
#define DEBUGARDUINO 0x8   // DEBUGGING ARDUINO WHERE ALL DEBUGGING/STATUS UPDATES WILL BE SENT OVER A DIFFERENT SERIAL INTERFACE
#define LCDARDUINO 0x9     // LCD ARDUINO WHERE EXTRA INFORMATION CAN BE DISPLAYED OR DEBUGGING STATUS UPDATES CAN BE SENT
#define SDARDUINO 0x10     // SD ARDUINO WHERE THE ARDUINO CAN PRINT COMPLETELY INDEPENDENTLY THROUGH A SD CARD

#define BEEPER 37
#define ROTARYBUTTON1 31
#define ROTARYBUTTON2 33
#define ROTARYBUTTON3 35
#define LCD1 16
#define LCD2 17
#define LCD3 23
#define LCD4 25
#define LCD5 27
#define LCD6 29
#define ledpin 13



/////////////////////////
///// LCD VARIABLES /////
/////////////////////////
LiquidCrystal lcd(LCD1, LCD2, LCD3, LCD4, LCD5, LCD6);
int timetodisplaylcdinseconds = 300;
String messagetodisplay = "";
int lcddisplaytoshow = 0;
String printerhostname = "MATTHEWS_3DPRINTER";
String printerMACaddress = "33-B0-J0-G3-P2-2K";
int type = 2;  // (0 - NO CHECK; 1 - DEBUG CHECK; 2 - STRICT CHECK)
bool settingsactivated = false;
int timetolcd = 0;
bool encoder1 = false;
bool encoder2 = false;
bool encoder3 = false;
int numbertoshow = 0;
float millimeterstoinches = 0.0393701;
float currentunits = 0;  // 0 FOR MM, 1 FOR INCHES
float printpercentage = 0.000;



/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////
/// PASSWORD STRINGs ///
////////////////////////
String dpswd = "HIMRANDERSON";
String cpswd = "";
String tpswd = "";
String pswd6 = "";


// APPARENTLY ONE WAY TO DO CHECKSUMS
/*
int cs = 0;
for(i = 0; cmd[i] != '*' && cmd[i] != NULL; i++)
   cs = cs ^ cmd[i];
cs &= 0xff;  // Defensive programming...
*/



//////////////////////////////////////////////////////////////////
//// TIMING VARIABLES / EXTRUDER PROTECTION / THERMAL RUNAWAY ////
//////////////////////////////////////////////////////////////////
int timesincestartup = 0;
int ledpinblink = 0;
bool ledblink = false;
float startuptimemillis = 000.0001;
bool followingcommand = true;
int timesincelastM109inseconds = 0;
int printjobtimerinseconds = 0;
bool printjobtimeractive = false;
int idlesteppermotortimeoutinseconds = 0;
int safetytimeout = 600;
int extrudertimeout = 60;
int heatedbedtimeout = 60;
int currentsafetytimer = 0;
int currentextrudertimer = 0;
unsigned long long int startextrudertimeout = 0;
unsigned long long int startheatedbedtimeout = 0;
bool currentlylocked = false;
bool waitingholdingstate = false;
int tempsensingruntime = 0;
int e0ontime = 0;
int e0delaytime = 0;
bool cooldown = false;
bool e0on = false;
bool e0max = false;
bool hbon = false;
bool hbonprevious = false;
bool e0onprevious = false;
unsigned long long int timesincelastmotorcurrent = 0;
unsigned long int clocktimers[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
unsigned long int targettime[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
unsigned long int currenttimer = 0;
unsigned long int startseconds = 0;

// EXTRUDER ELEMENTS FOR DELAYS AND MORE ACCURATE TEMPERATURE MEASUREMENTS
unsigned long int extruderlastalerttime = 0;
unsigned long int extrudertargeton = 0;
unsigned long int extrudertargetdelay = 0;




/////////////////////
// MOTOR VARIABLES //
/////////////////////
bool enablemotors = false;    // TRUE-FALSE
bool simulationmode = false;  // TRUE-FALSE
bool atxpoweron = false;
bool exfanpowerstate = false;
int maxfeedratespeed;
int defaultaccelerationspeed;
int retractionlength;
int extrusionlength;



////////////////////////////////////////
/// MOTOR VARIABLES SOFTWARE RELATED ///
////////////////////////////////////////
bool xmovingpositive = false;
bool xmovingnegative = false;
bool ymovingpositive = false;
bool ymovingnegative = false;
bool zmovingpositive = false;
bool zmovingnegative = false;
bool e0movingpositive = false;
bool e0movingnegative = false;
bool e1movingpositive = false;
bool e1movingnegative = false;
bool printfanon = false;


///////////////////////
// ENDSTOP VARIABLES //
///////////////////////
bool xendstopminactive = false;  // IS ENDSTOP SWITCH ACTIVATED
bool yendstopminactive = false;  // IS ENDSTOP SWITCH ACTIVATED
bool zendstopminactive = false;  // IS ENDSTOP SWITCH ACTIVATED
bool xendstopmaxactive = false;
bool yendstopmaxactive = false;
bool zendstopmaxactive = false;
float xendstopmaxvalue = 200.0001;
float yendstopmaxvalue = 200.0001;
float zendstopmaxvalue = 200.0001;
bool endstopdetection = true;
bool softwareendstops = true;




/////////////////////////
/// CURRENT VARIABLES ///
/////////////////////////
float currentxdimension = 0;
float currentydimension = 0;
float currentzdimension = 0;
float currentxdimensionLCD = 0;
float currentydimensionLCD = 0;
float currentzdimensionLCD = 0;
float currente0motordimension = 0;
float currente1motordimension = 0;
float currente0motordimensionLCD = 0;
float currente1motordimensionLCD = 0;
float currente0temp = 000.0001;
float currente1temp = 000.0001;
float currenthbtemp = 000.0001;
float currente0tempLCD = 000.0001;
float currente1tempLCD = 000.0001;
float currenthbtempLCD = 000.0001;
int currentactiveextruder = 0;
bool extrudersactive = false;
float maxe0temp = 300.0001;
float maxe1temp = 300.0001;
float maxhbtemp = 300.0001;
int currenttempunits = 0;          // 0 FOR CELSIUS, 2 FOR KELVIN, 1 FOR F
float filamentdiameter = 1.75;     // FILAMENT DIMATER IN MM
float maxacceleration = 3600.001;  // MAX ACCELERATION OF STEPPER MOTORS
float maxtravelspeed = 3600.001;
bool steppermotorsdisabled = true;
bool xdisabled = true;
bool ydisabled = true;
bool zdisabled = true;
bool edisabled = true;



////////////////////////
/// SAFETY VARIABLES ///
////////////////////////
bool allowcoldextrusion = false;




/////////////////////////////////
/// TARGET POSITION VARIABLES ///
/////////////////////////////////
float targetxdimension = 0;
float targetydimension = 0;
float targetzdimension = 0;
float targete0motordimension = 000.0001;
float targete1motordimension = 000.0001;
float targete0temp = 000.0001;
float targete1temp = 000.0001;
float targethbtemp = 000.0001;



//////////////////////////////
/// SPEED / STEP VARIABLES ///
//////////////////////////////
int xsteptimer = 0;
int ysteptimer = 0;
long int zsteptimer = 0;
int esteptimer = 0;
int e1steptimer = 0;
int xcurrentstep = 0;
int ycurrentstep = 0;
long int zcurrentstep = 0;
int ecurrentstep = 0;
int e1currentstep = 0;
int xstepsrequired = 0;
int ystepsrequired = 0;
long int zstepsrequired = 0;
int estepsrequired = 0;
int xstepstaken = 0;
int ystepstaken = 0;
long int zstepstaken = 0;
int estepstaken = 0;



///////////////////////////
///// SHIFT VARIABLES /////
///////////////////////////
float xshift = 0.0000;
float yshift = 0.0000;
float z1shift = 0.000;
float z2shift = 0.000;



//////////////////////////
/// MODIFIER VARIABLES ///
//////////////////////////
float xmodifier = 0.0131;
float ymodifier = 0.0131;
float zmodifier = 0.0005;
float e0motormodifier = 0.05;
float e1motormodifier = 0.05;




///////////////////////////
// RAM CACHING VARIABLES //
///////////////////////////

// GCODE COMMANDS TO BE CACHED
int gcodecommandstobecached = 10;

// PRINTER VARIABLES
bool printingactive = false;  // IS THE PRINTER ACTIVE THAT IT SHOULD START FOCUSING ON CACHING GCODE COMMANDS AS THEY ARE RECEIVED (TRUE/FALSE)
String character = "";
int analyzedCURRENTLYANALYZINGNUMBER = 0;
bool currentANALYZING = false;    // IS THE PRINTER ACTIVELY ANALYZING A COMMAND AS IT IS RECEIVED (TRUE/FALSE)
int currentgcodecommand = -1;     // CURRENT GCODE COMMAND PRINTER IS OPERATING ON (0-10)
int analyzedgcodecommand = 0;     // LAST GCODE COMAND THAT WAS ANALYZED (0-11)
int characternumberanalyzed = 0;  // CHARACTER NUMBER THAT HAS BEEN ANALYZED LAST.  (0-127)
int currentlycachedgcodes = 0;    // HOW MANY GCODE COMMANDS ARE CURRENTLY CACHED IN THE ARRAY (0-10)
float readvaluefromarray = 00.001;
int lastnoncachedstring = 0;
int totalnoncachedstrings = 0;
String stringfromstack = "";
int absoluterelative = 0;  // 0 = ABSOLUTE; 1 = RELATIVE

// CURRENT GCODE CHARACTERS
unsigned long int gcodenumber0 = 0;
unsigned long int gcodenumber1 = 0;
unsigned long int gcodenumber2 = 0;
unsigned long int gcodenumber3 = 0;
unsigned long int gcodenumber4 = 0;
unsigned long int gcodenumber5 = 0;
unsigned long int gcodenumber6 = 0;
unsigned long int gcodenumber7 = 0;
unsigned long int gcodenumber8 = 0;
unsigned long int gcodenumber9 = 0;
unsigned long int gcodenumber10 = 0;
unsigned long int previousgcodenumber = 0;

// ANALYZED GCODE VARIABLES AND ARRAY FUNCTIONS                                                           SERIAL, READY
//    ARRAY STRING            = { X-CORD, Y-CORD, Z-CORD, E0CORD, E1CORD, E2CORD, E0TEMP, E1TEMP, E2TEMP, LOCK  , LOCK};
float analyzedgcodestack0[11] = { 00.001, 00.001, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 0 };
float analyzedgcodestack1[11] = { 00.001, 00.001, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 0 };
float analyzedgcodestack2[11] = { 00.001, 00.001, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 0 };
float analyzedgcodestack3[11] = { 00.001, 00.001, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 0 };
float analyzedgcodestack4[11] = { 00.001, 00.001, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 0 };
float analyzedgcodestack5[11] = { 00.001, 00.001, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 0 };
float analyzedgcodestack6[11] = { 00.001, 00.001, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 0 };
float analyzedgcodestack7[11] = { 00.001, 00.001, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 0 };
float analyzedgcodestack8[11] = { 00.001, 00.001, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 0 };
float analyzedgcodestack9[11] = { 00.001, 00.001, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 0 };
float analyzedgcodestack10[11] = { 00.001, 00.001, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 00.000, 0 };

// RAM STRING VARIABLES (ALLOW CACHING OF UP TO 10 GCODE COMMANDS TO BE EXECUTED AND ANALYZED BEFORE THEY ARE RAN)
String gcodestack0 = "QNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN";
String gcodestack1 = "QNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN";
String gcodestack2 = "QNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN";
String gcodestack3 = "QNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN";
String gcodestack4 = "QNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN";
String gcodestack5 = "QNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN";
String gcodestack6 = "QNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN";
String gcodestack7 = "QNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN";
String gcodestack8 = "QNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN";
String gcodestack9 = "QNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN";
String gcodestack10 = "QNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN";




//////////////////////////////////
/// EMERGENCY PARSER VARIABLES ///
//////////////////////////////////
String ecache0 = "QN";
String ecache1 = "QN";
String ecache2 = "QN";
String ecache3 = "QN";
String ecache4 = "QN";
int numberinecache = 0;
bool toecache = false;




////////////////////////
/// SERIAL VARIABLES ///
////////////////////////
String inputString = "";
bool stringComplete = false;
String sendtoSerial = "";
int nS;
boolean newData = false;
const byte numChars = 128;  // EXTENDED TO 128
char receivedChars[numChars];
String receivedSerial3000 = "";
int serialBAUDRATE = 115200;




//////////////////////////
/// WATCHDOG VARIABLES ///
//////////////////////////
bool watchdogactivated = false;
long int timeinwatchdoginseconds = -1;
String errorstack0 = "ZNONE";
String errorstack1 = "ZNONE";
String errorstack2 = "ZNONE";
String errorstack3 = "ZNONE";
String errorstack4 = "ZNONE";
String errorstack5 = "ZNONE";
String errorstack6 = "ZNONE";
String errorstack7 = "ZNONE";
String errorstack8 = "ZNONE";
String errorstack9 = "ZNONE";
String errorstack10 = "ZNONE";
String readerrorfromstack = "";
int extrusiontimeout = 120;



/////////////////////////
//// DEBUG VARIABLES ////
/////////////////////////
bool debugserial = false;
bool skipsystemcheck = false;


/////////////////////////
//// SETUP VARIABLES ////
/////////////////////////
bool xendsetup = 0;
bool yendsetup = 0;
bool zendsetup = 0;
float anae0read = 00.0001;
float anahbread = 00.0001;


/////////////////////////////
//// EEPROM NOTES/VALUES ////
/////////////////////////////
// 0 - Hard Watchdog Status
// 1 - Debug Serial
// 2 - Restart from Power Loss
// 3 - Currently Locked
// 4 - watchdog errors
// 5 - temperature errors
// 6 - g-parser errors
// 7 - m-parser errors
// 8 - movement errors
// 9 - FIRMWARE MAJOR VERSION
// 10 - FIRMWARE MINOR VERSION
// 11 - success prints (256)
// 12 - success prints (1)
// 13 - bad prints (256)
// 14 - bad prints (1)
//
