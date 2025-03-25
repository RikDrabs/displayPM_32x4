/**********************************************************************************
 * Large Bargraph Remote Display for:                                             *
 * Luftdaten.info - Sensor.Community - InfluencAir - Luchtpijp - Telraam.         *
 * Display on LEDmatrix 16*8*8 dots, monocolor or (in the future) multicolor.     *
 *                                                                                *
 * Display part:                                                                  *
 * Copyright (C) 2019-2022 Beweging.net / project Luchtpijp - info@luchtpijp.be   *
 * Copyright (C) 2023-2025 InfluencAir - influencair2017@gmail.com                *
 * Copyright (C) 2019-2025 Rik Drabs - rik.drabs@gmail.com                        *
 *                                                                                *
 * Web interface part:                                                            *
 * Copyright (C) 2016-2020 Code for Stuttgart a.o.                                *
 * Copyright (C) 2019-2020 Dirk Mueller                                           *
 * Copyright (C) 2021-2025 Sensor.Community                                       *
 *                                                                                *
 * This program is free software: you can redistribute it and/or modify           *
 * it under the terms of the GNU General Public License as published by           *
 * the Free Software Foundation, either version 3 of the License, or              *
 * (at your option) any later version.                                            *
 * This program is distributed in the hope that it will be useful,                *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of                 *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                  *
 * GNU General Public License for more details.                                   *
 * You should have received a copy of the GNU General Public License              *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.           *
 *                                                                                *
 **********************************************************************************
 * This program was originally written for project LUCHTPIJP, a 2018 initiative   *
 * of: Beweging.net - CM (Christelijke Mutualiteit) - Bank BELFIUS.               *
 * The LUCHTPIJP project is the 2018 successor to project InfluencAir,            *
 * which was an initiative of CIVIC LAB BRUSSELS, operating under the umbrella    *
 * of OPEN KNOWLEDGE BELGIUM.                                                     *
 * InfluencAir followed the Stuttgart project Luftdaten.info mid 2017.            *
 * The Luftdaten.info project was later renamed to Sensor.Community.              *
 * Since October 2023 the InfluencAir project was restarted                       *
 * by Civic Lab Brussels around this display and a new PM meter.                  *
 *                                                                                *
 **********************************************************************************
 * In 2023/2025 a major overhaul was done on the original 2019 program,           *
 * This included support for DNMS and the external project TELRAAM,               *
 * from which all rights are acknowledged.                                        *
 * A user webinterface was implemented, using as example the webinterface         *
 * of the sensor firmware by Sensor.community, for connecting the display         *
 * to the WiFi, and for modifying parameters, which was done before by modifying  *
 * parameters in source and recompiling.                                          *
 * Many thanks to the good work of the team in Stuttgart & elsewhere.             *
 *                                                                                *
 **********************************************************************************
 * Parts list (BOM):                                                              *
 * =================                                                              *
 * 4 pieces displayblock 4 units 8*8 pixels.                                      *
 * (or 2 pieces displayblock 8 units 8*8 pixels).                                 *
 * 1 piece MCU NodeMCU 0.9 (ESP-12)                                               *
 * 1 piece PCB InfluencAir Display (see gerber file)                              *
 * 1,5 meter ALU profile to fix the display. (see pictures)                       *
 * 1 roll transparent doublesided tape. (Tesa powerbond 55744-00001)              *
 * 2 pieces of 3D printed endpieces for finishing the display (see .STL file)     *
 *                                                                                *
 **********************************************************************************
 * Hardware construction:                                                         *
 * ======================                                                         *
 * The free connector on the first display block (input to the whole              *
 * display) must be removed, and a pin row (5 pins) must be soldered              *
 * vertically on the back of the PCB in its place.(see pictures)                  *
 * A second pin row (4 or 5 pins) must be soldered to the output of the           *
 * second display matrix 8*8 (see pictures for alignment !!)                      *
 * Mount the ESP8266 MCU (small footprint) on an InfluencAir display PCB,         *
 * and solder it to the pins on the back of the first display block 4*8*8.        *
 * (see pictures)                                                                 *
 *                                                                                *
 * Now cascade the 4 (2) display blocks, by bending the pins of 3 (1)             *
 * of them, and soldering them in cascade, so that a level row of                 *
 * 4 by 4 ( 2 by 8) display blocks is created.(see pictures)                      *
 *                                                                                *
 * Finally check that the display blocks are mounted flat, and correct            *
 * flatness if needed. Then clean, fix to a flat surface with a spacer            *
 * of +/- 1mm underneath, and tape with double sided tape to the profile.         *
 * (see pictures). Finally, apply a droplet of superglue between profiles         *
 * and endpieces, on the INSIDE.                                                  *
 * After mounting, flash the program, and enjoy.                                  *
 *                                                                                *
 **********************************************************************************/
#include  <WString.h>
#include  <pgmspace.h>

// Increment on each release   x.xx
#define SOFTWARE_VERSION_STR "v2.00"
String  SOFTWARE_VERSION (SOFTWARE_VERSION_STR);

/*
File list:
- airrohr-logo.h      logo
- buildmess.h         build messages
- ca-root.h           certificate
- display-cfg.h       config
- display-cfg.h.py    config python
- ext-def.h           definitions
- FS_xxx_ddmmyyyy.ino this file
- html.h              html content
- intl.h              language select
- intl-en.h           supported languages
- intl-fr.h           ...
- intl-ge.h
- intl-it.h
- intl-nl.h
- intl-sp.h
- lcd.h
- LICENCE.md          licence
- parola-fonts.h      adapted parola fonts
- README.md           readme
- sens-xxxxxx.h       sensor definition files
- telraam.h           telraam API interface
- utils.cpp
- utils.h
- web-interf.h        web interface for config
*/

#pragma GCC diagnostic ignored "-Wwrite-strings"

// Header files, libraries
#include    <Arduino.h>                     // Standard
#include    <FS.h>                          // File System
#include    <ArduinoJson.h>                 // Json library - V.7.3.1
#include    <ESP8266HTTPClient.h>           // ESP8266 HTTP Client 
#include    <ESP8266WiFi.h>                 // ESP8266 WiFi 
#include    <ESP8266WebServer.h>            // Webserver 
#include    <ESP8266mDNS.h>                 // DNS client
#include    <DNSServer.h>                   // DNS server
#include    <MD_Parola.h>                   // Parola Library 
#include    <MD_MAX72XX.h>                  // Max72xx Library 
#include    <SPI.h>                         // SPI Library

/*
#include    <LiquidCrystal_I2C.h>           // LCD library
LiquidCrystal_I2C lcd(0x27,16,2);
*/

// Time library
#include    <ezTime.h>                      // Easy time
Timezone    myTZ;                           // Local time zone 

// Language select
#include "intl-nl.h"                        // DUTCH

// Own includes
#include    "./utils.h"                     // Utils
#include    "./ext-def.h"                   // Default values
#include    "./parola-fonts.h"              // Parola adapted fonts
#include    "./html.h"                      // Html helper

// Data selector PM2.5 - PM10
enum   
{
            SELECT_PM25,                    // Select PM2.5 data 
            SELECT_PM10,                    // Select PM10 data 
};

// String ID defines
enum        
{ 
            STR_UGRAM3,                     // 0
            STR_DROPLET,
            STR_THERMO, 
            STR_DEGREES, 
            STR_TEMP_EQ, 
            STR_VOCHT_EQ,                   // 5
            STR_PERCENT1,                  
            STR_PERCENT2,                  
            STR_PERCENT3,  
            STR_PERCENT4,
            STR_PERCENT5,                   // 10    
            STR_AVG,     
            STR_TEHOOG,
            STR_NODATA, 
            STR_MAX24,                      
            STR_AVG24,                      // 15
            STR_PRESS,     
            STR_HEAVY, 
            STR_CAR,                        
            STR_BIKE, 
            STR_PEDES,                      // 20
            STR_SPEED, 
            STR_KMPERH, 
            STR_VERKEER,                    
            STR_DNMS, 
            STR_MAX,                        // 25
            STR_MIN,  
            STR_EQ,                         
            STR_FS,
            STR_WEER,   
            STR_VOCNOX,                     // 30
            STR_READING, 
            STR_SERVERDOWN,
            STR_NOINTERNET,
};

// Read states 
enum        
{ 
            READ_START,                     // At start
            READ_BUSY,                      // During reading
            READ_AFTER,                     // Timing out after reading
};

/*
// Building display states
enum
{
            DISPL_LOCATIONS,                // Display all locations
            DISPL_NOTWORKING,               // Display not-working meters
};
*/

// Telraam measurement unit to show
enum
{
            PEDES,                          // Pedestrians
            BIKE,                           // Bikes  
            CAR,                            // Cars
            HEAVY,                          // Heavy vehicles
            SPEED,                          // Average speed
            ALL,                            // Show ALL
};

// Message control byte (first byte in message)
#define     SCROLL_TEXT       'S'           // Scrolling, one pixel between characters (for showing separate chars)
#define     SCROLL_GRAPHICS   's'           // Scrolling, zero pixels between characters (for showing graphics)
#define     FIXED_TEXT        'F'           // Fixed left justified, one pixel between characters (for showing separate chars)
#define     FIXED_GRAPHICS    'f'           // Fixed left justified, zero pixels between characters (for showing graphics)
#define     FIXED_TIME        'T'           // Fixed left justified, one pixel between characters (for showing & updating time)
#define     FIXED_BLANK       'B'           // Blank message, short space between other messages

// Sensor records
struct      MySensors
{
float       pm10  = -1000.0f;               // PM 10
float       pm4   = -1000.0f;               // PM 4
float       pm25  = -1000.0f;               // PM 2.5
float       pm1   = -1000.0f;               // PM 1
float       nbr05 = -1000.0f;               // Nbr 0.5
float       nbr1  = -1000.0f;               // Nbr 1
float       nbr25 = -1000.0f;               // Nbr 2.5
float       nbr4  = -1000.0f;               // Nbr 4
float       nbr10 = -1000.0f;               // Nbr 10
float       ts    = -1000.0f;               // TS
float       voc   = -1000.0f;               // VOC
float       nox   = -1000.0f;               // NOx
float       temp  = -1000.0f;               // Temperature
float       humi  = -1000.0f;               // Humidity
float       press = -1000.0f;               // Pressure
float       LAmin = -1000.0f;               // Noise LA min.
float       LAmax = -1000.0f;               // Noise LA max.
float       LAeq  = -1000.0f;               // Noise LA eq.
float       heavy = -1000.0f;               // Telraam Heavy vehicles
float       car   = -1000.0f;               // Telraam Cars
float       bike  = -1000.0f;               // Telraam Bikes
float       pedes = -1000.0f;               // Telraam Pedestrians
float       speed = -1000.0f;               // Telraam V85 speed
char        name[LEN_LOCATION_NAME] = "";   // Location name
}           realtime;

float       heapAboveMinimum = millis();    // Point in time where heap was above minimum for Telraam
float       compareResult = 0;              // result of comparing indoor & outdoor
float       compareResultPos = 0;           // compare result for printing purposes - always positive
float       betweenReads = 0;               // milliseconds timing between block read 32 locations
float       startPause = 0;                 // milliseconds timer pause between messages
float       nextSecond = 0;                 // millisecond timer stepping seconds on display

char        formatChar = FIXED_TEXT;        // format character in message
uint8_t     welkomCount = 0;                // welcome message cycle count
uint8_t     readState = READ_START;         // reading state
uint8_t     locationsInstalled = 0;         // multi-sensor maximum installed
uint8_t     location = 0;                   // multi-sensor array pointer
uint8_t     readUpToLocation = 0;           // read data up to location
uint8_t     locationOnDisplay = 0;          // multi-sensor location on display
uint8_t     messageOnDisplay = 0;           // message on display selector
uint8_t     toDisplayLine = 0;              // writing to message line number
uint8_t     i, j, k;                        // general variables

uint16_t    httpCode = 0;                   // resultcode for http operations
uint16_t    beginHeap = 0;                  // heap size @begin procedure
uint16_t    prevHeap = 0;                   // previous heap size @begin procedure

// Time @last startup
unsigned long atLastStartup = millis();     // Time at last startup   

bool        firstCall = false;              // for determining when to calculate peak & average values.
bool        coldStart = false;              // cold start marker
bool        webStarted = false;             // web started marker
bool        firstFullScan = false;          // first full scan done marker
bool        firstAverage = false;           // first average compute done marker
bool        selftest_failed = false;        // self test fail marker
bool        decrementTimeout = false;       // timeout controller
bool        betweenMessages = false;        // switch flag between welcome messages
bool        displayBufferEmpty = true;      // display buffer empty marker
bool        timeCorrect = false;            // time syncronised flag
bool        internetUp = false;             // internet up & running flag

char        forDisplay[NUMCHR-2];           // string for display
char        workString[32];                 // work string
char        displayString[160];             // display string
char        valueString[LEN_MEASUREMENTS];  // value string

// Storage for sensor data
float       readPm10[LOCATION_MAX];         // PM10
float       readPm4[LOCATION_MAX];          // PM4
float       readPm25[LOCATION_MAX];         // PM2.5
float       readPm1[LOCATION_MAX];          // PM1
float       readNbr05[LOCATION_MAX];        // # Particles 0.5µm
float       readNbr1[LOCATION_MAX];         // # Particles 1µm
float       readNbr25[LOCATION_MAX];        // # Particles 2.5µm
float       readNbr4[LOCATION_MAX];         // # Particles 4µm
float       readNbr10[LOCATION_MAX];        // # Particles 10µm
float       readTs[LOCATION_MAX];           // TS (Avg particle size)
float       readVoc[LOCATION_MAX];          // VOC
float       readNox[LOCATION_MAX];          // NOx
float       readTemp[LOCATION_MAX];         // Temperature
float       readHumi[LOCATION_MAX];         // Humidity
float       typeHumi[LOCATION_MAX];         // Humidity sensor type
float       readPres[LOCATION_MAX];         // Pressure
float       readLAmin[LOCATION_MAX];        // LAmin
float       readLAmax[LOCATION_MAX];        // LAmax
float       readLAeq[LOCATION_MAX];         // LAeq
float       readHeavy[LOCATION_MAX];        // Heavy vehicles
float       readCar[LOCATION_MAX];          // Cars
float       readBike[LOCATION_MAX];         // Bikes
float       readPedes[LOCATION_MAX];        // Pedestrians
float       readSpeed[LOCATION_MAX];        // V85 speed
float       readTimeout[LOCATION_MAX];      // Sensor read timeout

// Storage for peak & average measurements
float       cumulAvgPm25[LOCATION_MAX];     // Cumulating average PM2.5
long        cumulAvgPm25Cnt[LOCATION_MAX];  // Cumulating average PM2.5 count
//
float       cumulAvgPm10[LOCATION_MAX];     // Cumulating average PM10
long        cumulAvgPm10Cnt[LOCATION_MAX];  // Cumulating average PM10 count
//
float       peakPm25[LOCATION_MAX];         // 24/24h Peak PM2.5
float       peak0Pm25[LOCATION_MAX];        // Peak PM2.5 0-3h.
float       peak4Pm25[LOCATION_MAX];        // Peak PM2.5 4-7h.
float       peak8Pm25[LOCATION_MAX];        // Peak PM2.5 8-11h.
float       peak12Pm25[LOCATION_MAX];       // Peak PM2.5 12-15h.
float       peak16Pm25[LOCATION_MAX];       // Peak PM2.5 16-19h.
float       peak20Pm25[LOCATION_MAX];       // Peak PM2.5 20-23h.
//
float       peakPm10[LOCATION_MAX];         // 24/24h Peak PM10
float       peak0Pm10[LOCATION_MAX];        // Peak PM10 0-3h.
float       peak4Pm10[LOCATION_MAX];        // Peak PM10 4-7h.
float       peak8Pm10[LOCATION_MAX];        // Peak PM10 8-11h.
float       peak12Pm10[LOCATION_MAX];       // Peak PM10 12-15h.
float       peak16Pm10[LOCATION_MAX];       // Peak PM10 16-19h.
float       peak20Pm10[LOCATION_MAX];       // Peak PM10 20-23h.
//
float       allMeterPm25avg;                // All meter PM2.5 24/24h average
float       allMeterPm25peak;               // All meter PM2.5 24/24h peak
float       allMeterPm10avg;                // All meter PM10 24/24h average
float       allMeterPm10peak;               // All meter PM10 24/24h peak
//
float       pm10peak = 0;                   // PM10 peak value
float       pm25peak = 0;                   // PM2.5 peak value
float       pm10average = 0;                // PM10 average
float       pm25average = 0;                // PM2.5 average
float       pm10maxDeviation = 0;           // PM10 maximum deviation
float       pm25maxDeviation = 0;           // PM2.5 idem

// Array storage for sensor config, for easy access
char        multiName[LOCATION_MAX][LEN_LOCATION_NAME];     // Location names for display
char        multiApi1[LOCATION_MAX][LEN_SENSOR_API_1];      // Sensor API 1 (PM values)
char        multiApi2[LOCATION_MAX][LEN_SENSOR_API_2];      // Sensor API 2 (Temp - Humi)
char        multiApi3[LOCATION_MAX][LEN_SENSOR_API_3];      // Sensor API 3 (DNMS - VOC - NOx)
char        multiApi4[LOCATION_MAX][LEN_SENSOR_API_4];      // Sensor API 4 (DNMS - VOC - NOx - TELRAAM)

// Config variables
namespace   cfg
{
  unsigned int pauseTime = PAUSETIME;                       // Display timing: pause between messages on display - default 7 seconds
  unsigned int displaySpeed = DISPLAYSPEED;                 // Display timing: scrolling delay on display (millisec. per step) - default 25
  unsigned int callingInterval = CALLINGINTERVAL;           // Data calling interval - default 5 minutes
  unsigned int welkomInterval = WELCOMEINTERVAL;            // Welcome repeats after this count
  unsigned int differencePercent = DIFFERENCEPERCENT;       // Maximum % deviation before notification
  unsigned int differenceLevel = DIFFERENCELEVEL;           // Maximum level deviation before notification 
  unsigned int sensordataTimeout = SENSORDATATIMEOUT;       // Sensor data time-out; number of cycles with no reception of data
  unsigned int clockSeconds = CLOCKSECONDS;                 // Clock seconds on display
  //
  unsigned int pmChoice = PMCHOICE;                         // Choose PM for peak/average/graphics  
  unsigned int maxgraphPM10 = MAXGRAPH_PM10;                // PM10 value for 200% graphic display
  unsigned int maxgraphPM25 = MAXGRAPH_PM25;                // PM2.5 value for 200% graphic display
  unsigned int max25WHO = MAX25WHO;                         // WHO maximum value PM2.5
  unsigned int max10WHO = MAX10WHO;                         // WHO maximum value PM10
  unsigned int PM25toAQI50 = PM25TOAQI50;                   // Conversion factor PM2.5 -> AQI50
  unsigned int PM10toAQI50 = PM10TOAQI50;                   // Conversion factor PM10 -> AQI50
  unsigned int compareLocation = COMPARELOCATION;           // Main compare location
  unsigned int compareLocation2 = COMPARELOCATION2;         // Secondary compare location

  unsigned int maxAqiGreen = MAXAQIGREEN;                   // Maximum AQI for green level
  unsigned int maxAqiYellow = MAXAQIYELLOW;                 // Maximum AQI for yellow level
  unsigned int maxAqiOrange = MAXAQIORANGE;                 // Maximum AQI for orange level
  unsigned int maxAqiRed = MAXAQIRED;                       // Maximum AQI for red level
  unsigned int maxAqiViolet = MAXAQIVIOLET;                 // Maximum AQI for violet level
  //
  unsigned int maxWhoGreen = MAXWHOGREEN;                   // Maximum WHO for green level
  unsigned int maxWhoYellow = MAXWHOYELLOW;                 // Maximum WHO for yellow level
  unsigned int maxWhoOrange = MAXWHOORANGE;                 // Maximum WHO for orange level
  unsigned int maxWhoRed = MAXWHORED;                       // Maximum WHO for red level
  unsigned int maxWhoViolet = MAXWHOVIOLET;                 // Maximum WHO for violet level
  //
  unsigned int maxLAeqGreen = MAXLAEQGREEN;                 // Maximum DNMS LAeq for green level
  unsigned int maxLAeqYellow = MAXLAEQYELLOW;               // Maximum DNMS LAeq for yellow level
  unsigned int maxLAeqOrange = MAXLAEQORANGE;               // Maximum DNMS LAeq for orange level
  unsigned int maxLAeqRed = MAXLAEQRED;                     // Maximum DNMS LAeq for red level
  unsigned int maxLAeqViolet = MAXLAEQVIOLET;               // Maximum DNMS LAeq for violet level
  unsigned int maxLAeqBrown = MAXLAEQBROWN;                 // Maximum DNMS LAeq for brown level
  //
  unsigned int maxTrafGreen = MAXTRAFGREEN;                 // Maximum Traffic for green level
  unsigned int maxTrafYellow = MAXTRAFYELLOW;               // Maximum Traffic for yellow level
  unsigned int maxTrafOrange = MAXTRAFORANGE;               // Maximum Traffic for orange level
  unsigned int maxTrafRed = MAXTRAFRED;                     // Maximum Traffic for red level
  unsigned int maxTrafCyan = MAXTRAFCYAN;                   // Maximum Traffic for cyan level 
  unsigned int maxTrafViolet = MAXTRAFVIOLET;               // Maximum Traffic for violet level
  unsigned int maxTrafBrown = MAXTRAFBROWN;                 // Maximum Traffic for brown level
  //   
  bool multiCompare = MULTICOMPARE;                         // true = show only meters with overvalues
  bool showPmPm = SHOWPMPM;                                 // true = show PM values
  bool showPm1Pm4 = SHOWPM1PM4;                             // true = show PM1/PM4 if present
  bool showComp = SHOWCOMP;                                 // true = show compare between two sensors
  bool showCompInside = SHOWCOMPINSIDE;                     // true = show compare second sensor inside
  bool showMeteo = SHOWMETEO;                               // true = show meteo info
  bool showGraph = SHOWGRAPH;                               // true = show graph
  bool showAvgNpeak = SHOWAVGNPEAK;                         // true = show 24h.average & peak values
  bool showAqiAdvice = SHOWAQIADVICE;                       // true = show AQI advice
  bool showWhoAdvice = SHOWWHOADVICE;                       // true = show WHO advice
  bool showDnms = SHOWDNMS;                                 // true = show DNMS data
  bool showVoc = SHOWVOC;                                   // true = show VOC/NOx data
  bool sensorMissing = SENSORMISSING;                       // true = show missing meters in multi-configuration
  bool multiAverage = MULTIAVERAGE;                         // true = show multimeter average
  bool www_basicauth_enabled = WWW_BASICAUTH_ENABLED;       // true = basic auth enabled
  bool showTelRaam = SHOWTELRAAM;                           // true = show Telraam data
  bool showPedes = SHOWPEDES;                               // true = show Pedestrians data
  bool showBike = SHOWBIKE;                                 // true = show Bike data
  bool showCar = SHOWCAR;                                   // true = show Car data
  bool showHeavy = SHOWHEAVY;                               // true = show Heavy vehicles data
  bool showSpeed = SHOWSPEED;                               // true = show Speed data
  bool freeToken = FREE_TOKEN;                              // true = Telraam free API token
  //
  bool debugShowData = DEBUGSHOWDATA;                       // true = debug show data
  bool debugDisplay = DEBUGDISPLAY;                         // true = debug display
  bool debugComms = DEBUGCOMMS;                             // true = debug comms
  bool debugHeap = DEBUGHEAP;                               // true = debug heap
  bool debugJson = DEBUGJSON;                               // true = debug Json
  //
  char wlanssid[LEN_SSID];                                  // ssid to connect to
  char wlanpwd[LEN_PASSWORD];                               // ssid's password
  char fs_ssid[LEN_SSID] = FS_SSID;                         // own ssid in AP mode
  char fs_pwd[LEN_PASSWORD] = FS_PWD;                       // password for access to AP
  char www_username[LEN_WWW_USERNAME];                      // user for auth
  char www_password[LEN_PASSWORD];                          // password for auth
  char welkom[LEN_WELCOME]  = WELCOME;                      // welcome message 1
  char welkom2[LEN_WELCOME] = WELCOME2;                     // welcome message 2
  char timeZoneStr[LEN_TZ_STR] = TIMEZONESTR;               // time zone
  char sensorApi[LEN_API] = SENSOR_API;                     // Sensor.Community API URL
  char telraamApi[LEN_API] = TELRAAM_API;                   // Telraam API URL
  char telraamToken[LEN_TOKEN] = TELRAAM_TOKEN;             // Telraam token
  //
	char sensorLoc_0[LEN_LOCATION_NAME] = LOCATION_NAME_0;
  char sensorApi1_0[LEN_SENSOR_API_1] = SENSOR_API_1_0;
	char sensorApi2_0[LEN_SENSOR_API_2] = SENSOR_API_2_0;
	char sensorApi3_0[LEN_SENSOR_API_3] = SENSOR_API_3_0;
	char sensorApi4_0[LEN_SENSOR_API_4] = SENSOR_API_4_0;
	char sensorLoc_1[LEN_LOCATION_NAME] = LOCATION_NAME_1;
  char sensorApi1_1[LEN_SENSOR_API_1] = SENSOR_API_1_1;
	char sensorApi2_1[LEN_SENSOR_API_2] = SENSOR_API_2_1;
  char sensorApi3_1[LEN_SENSOR_API_3] = SENSOR_API_3_1;
	char sensorApi4_1[LEN_SENSOR_API_4] = SENSOR_API_4_1;
  //
  char sensorLoc_2[LEN_LOCATION_NAME] = LOCATION_NAME_2;
	char sensorApi1_2[LEN_SENSOR_API_1] = SENSOR_API_1_2;
	char sensorApi2_2[LEN_SENSOR_API_2] = SENSOR_API_2_2;
	char sensorApi3_2[LEN_SENSOR_API_3] = SENSOR_API_3_2;
	char sensorApi4_2[LEN_SENSOR_API_4] = SENSOR_API_4_2;
  char sensorLoc_3[LEN_LOCATION_NAME] = LOCATION_NAME_3;
	char sensorApi1_3[LEN_SENSOR_API_1] = SENSOR_API_1_3;
	char sensorApi2_3[LEN_SENSOR_API_2] = SENSOR_API_2_3;
	char sensorApi3_3[LEN_SENSOR_API_3] = SENSOR_API_3_3;
	char sensorApi4_3[LEN_SENSOR_API_4] = SENSOR_API_4_3;
  //
  char sensorLoc_4[LEN_LOCATION_NAME] = LOCATION_NAME_4;
	char sensorApi1_4[LEN_SENSOR_API_1] = SENSOR_API_1_4;
	char sensorApi2_4[LEN_SENSOR_API_2] = SENSOR_API_2_4;
	char sensorApi3_4[LEN_SENSOR_API_3] = SENSOR_API_3_4;
	char sensorApi4_4[LEN_SENSOR_API_4] = SENSOR_API_4_4;
  char sensorLoc_5[LEN_LOCATION_NAME] = LOCATION_NAME_5;
	char sensorApi1_5[LEN_SENSOR_API_1] = SENSOR_API_1_5;
	char sensorApi2_5[LEN_SENSOR_API_2] = SENSOR_API_2_5;
	char sensorApi3_5[LEN_SENSOR_API_3] = SENSOR_API_3_5;
	char sensorApi4_5[LEN_SENSOR_API_4] = SENSOR_API_4_5;
  //
  char sensorLoc_6[LEN_LOCATION_NAME] = LOCATION_NAME_6;
	char sensorApi1_6[LEN_SENSOR_API_1] = SENSOR_API_1_6;
	char sensorApi2_6[LEN_SENSOR_API_2] = SENSOR_API_2_6;
	char sensorApi3_6[LEN_SENSOR_API_3] = SENSOR_API_3_6;
	char sensorApi4_6[LEN_SENSOR_API_4] = SENSOR_API_4_6;
  char sensorLoc_7[LEN_LOCATION_NAME] = LOCATION_NAME_7;
	char sensorApi1_7[LEN_SENSOR_API_1] = SENSOR_API_1_7;
	char sensorApi2_7[LEN_SENSOR_API_2] = SENSOR_API_2_7;
	char sensorApi3_7[LEN_SENSOR_API_3] = SENSOR_API_3_7;
	char sensorApi4_7[LEN_SENSOR_API_4] = SENSOR_API_4_7;
  //
  char sensorLoc_8[LEN_LOCATION_NAME] = LOCATION_NAME_8;
	char sensorApi1_8[LEN_SENSOR_API_1] = SENSOR_API_1_8;
	char sensorApi2_8[LEN_SENSOR_API_2] = SENSOR_API_2_8;
	char sensorApi3_8[LEN_SENSOR_API_3] = SENSOR_API_3_8;
	char sensorApi4_8[LEN_SENSOR_API_4] = SENSOR_API_4_8;
  char sensorLoc_9[LEN_LOCATION_NAME] = LOCATION_NAME_9;
	char sensorApi1_9[LEN_SENSOR_API_1] = SENSOR_API_1_9;
	char sensorApi2_9[LEN_SENSOR_API_2] = SENSOR_API_2_9;
	char sensorApi3_9[LEN_SENSOR_API_3] = SENSOR_API_3_9;
	char sensorApi4_9[LEN_SENSOR_API_4] = SENSOR_API_4_9;
	//
  char sensorLoc_10[LEN_LOCATION_NAME] = LOCATION_NAME_10;
	char sensorApi1_10[LEN_SENSOR_API_1] = SENSOR_API_1_10;
	char sensorApi2_10[LEN_SENSOR_API_2] = SENSOR_API_2_10;
	char sensorApi3_10[LEN_SENSOR_API_3] = SENSOR_API_3_10;
	char sensorApi4_10[LEN_SENSOR_API_4] = SENSOR_API_4_10;
  char sensorLoc_11[LEN_LOCATION_NAME] = LOCATION_NAME_11;
	char sensorApi1_11[LEN_SENSOR_API_1] = SENSOR_API_1_11;
	char sensorApi2_11[LEN_SENSOR_API_2] = SENSOR_API_2_11;
	char sensorApi3_11[LEN_SENSOR_API_3] = SENSOR_API_3_11;
	char sensorApi4_11[LEN_SENSOR_API_4] = SENSOR_API_4_11;
  //
  char sensorLoc_12[LEN_LOCATION_NAME] = LOCATION_NAME_12;
	char sensorApi1_12[LEN_SENSOR_API_1] = SENSOR_API_1_12;
	char sensorApi2_12[LEN_SENSOR_API_2] = SENSOR_API_2_12;
	char sensorApi3_12[LEN_SENSOR_API_3] = SENSOR_API_3_12;
	char sensorApi4_12[LEN_SENSOR_API_4] = SENSOR_API_4_12;
  char sensorLoc_13[LEN_LOCATION_NAME] = LOCATION_NAME_13;
	char sensorApi1_13[LEN_SENSOR_API_1] = SENSOR_API_1_13;
	char sensorApi2_13[LEN_SENSOR_API_2] = SENSOR_API_2_13;
	char sensorApi3_13[LEN_SENSOR_API_3] = SENSOR_API_3_13;
	char sensorApi4_13[LEN_SENSOR_API_4] = SENSOR_API_4_13;
	//
  char sensorLoc_14[LEN_LOCATION_NAME] = LOCATION_NAME_14;
	char sensorApi1_14[LEN_SENSOR_API_1] = SENSOR_API_1_14;
	char sensorApi2_14[LEN_SENSOR_API_2] = SENSOR_API_2_14;
	char sensorApi3_14[LEN_SENSOR_API_3] = SENSOR_API_3_14;
	char sensorApi4_14[LEN_SENSOR_API_4] = SENSOR_API_4_14;
  char sensorLoc_15[LEN_LOCATION_NAME] = LOCATION_NAME_15;
	char sensorApi1_15[LEN_SENSOR_API_1] = SENSOR_API_1_15;
	char sensorApi2_15[LEN_SENSOR_API_2] = SENSOR_API_2_15;
	char sensorApi3_15[LEN_SENSOR_API_3] = SENSOR_API_3_15;
	char sensorApi4_15[LEN_SENSOR_API_4] = SENSOR_API_4_15;
	//
  char sensorLoc_16[LEN_LOCATION_NAME] = LOCATION_NAME_16;
	char sensorApi1_16[LEN_SENSOR_API_1] = SENSOR_API_1_16;
	char sensorApi2_16[LEN_SENSOR_API_2] = SENSOR_API_2_16;
	char sensorApi3_16[LEN_SENSOR_API_3] = SENSOR_API_3_16;
	char sensorApi4_16[LEN_SENSOR_API_4] = SENSOR_API_4_16;
  char sensorLoc_17[LEN_LOCATION_NAME] = LOCATION_NAME_17;
	char sensorApi1_17[LEN_SENSOR_API_1] = SENSOR_API_1_17;
	char sensorApi2_17[LEN_SENSOR_API_2] = SENSOR_API_2_17;
	char sensorApi3_17[LEN_SENSOR_API_3] = SENSOR_API_3_17;
	char sensorApi4_17[LEN_SENSOR_API_4] = SENSOR_API_4_17;
	//
  char sensorLoc_18[LEN_LOCATION_NAME] = LOCATION_NAME_18;
	char sensorApi1_18[LEN_SENSOR_API_1] = SENSOR_API_1_18;
	char sensorApi2_18[LEN_SENSOR_API_2] = SENSOR_API_2_18;
	char sensorApi3_18[LEN_SENSOR_API_3] = SENSOR_API_3_18;
	char sensorApi4_18[LEN_SENSOR_API_4] = SENSOR_API_4_18;
  char sensorLoc_19[LEN_LOCATION_NAME] = LOCATION_NAME_19;
	char sensorApi1_19[LEN_SENSOR_API_1] = SENSOR_API_1_19;
	char sensorApi2_19[LEN_SENSOR_API_2] = SENSOR_API_2_19;
	char sensorApi3_19[LEN_SENSOR_API_3] = SENSOR_API_3_19;
	char sensorApi4_19[LEN_SENSOR_API_4] = SENSOR_API_4_19;
	//
  char sensorLoc_20[LEN_LOCATION_NAME] = LOCATION_NAME_20;
	char sensorApi1_20[LEN_SENSOR_API_1] = SENSOR_API_1_20;
	char sensorApi2_20[LEN_SENSOR_API_2] = SENSOR_API_2_20;
	char sensorApi3_20[LEN_SENSOR_API_3] = SENSOR_API_3_20;
	char sensorApi4_20[LEN_SENSOR_API_4] = SENSOR_API_4_20;
  char sensorLoc_21[LEN_LOCATION_NAME] = LOCATION_NAME_21;
	char sensorApi1_21[LEN_SENSOR_API_1] = SENSOR_API_1_21;
	char sensorApi2_21[LEN_SENSOR_API_2] = SENSOR_API_2_21;
	char sensorApi3_21[LEN_SENSOR_API_3] = SENSOR_API_3_21;
	char sensorApi4_21[LEN_SENSOR_API_4] = SENSOR_API_4_21;
	//
  char sensorLoc_22[LEN_LOCATION_NAME] = LOCATION_NAME_22;
	char sensorApi1_22[LEN_SENSOR_API_1] = SENSOR_API_1_22;
	char sensorApi2_22[LEN_SENSOR_API_2] = SENSOR_API_2_22;
	char sensorApi3_22[LEN_SENSOR_API_3] = SENSOR_API_3_22;
	char sensorApi4_22[LEN_SENSOR_API_4] = SENSOR_API_4_22;
  char sensorLoc_23[LEN_LOCATION_NAME] = LOCATION_NAME_23;
	char sensorApi1_23[LEN_SENSOR_API_1] = SENSOR_API_1_23;
	char sensorApi2_23[LEN_SENSOR_API_2] = SENSOR_API_2_23;
	char sensorApi3_23[LEN_SENSOR_API_3] = SENSOR_API_3_23;
	char sensorApi4_23[LEN_SENSOR_API_4] = SENSOR_API_4_23;
	//
  char sensorLoc_24[LEN_LOCATION_NAME] = LOCATION_NAME_24;
	char sensorApi1_24[LEN_SENSOR_API_1] = SENSOR_API_1_24;
	char sensorApi2_24[LEN_SENSOR_API_2] = SENSOR_API_2_24;
	char sensorApi3_24[LEN_SENSOR_API_3] = SENSOR_API_3_24;
	char sensorApi4_24[LEN_SENSOR_API_4] = SENSOR_API_4_24;
  char sensorLoc_25[LEN_LOCATION_NAME] = LOCATION_NAME_25;
	char sensorApi1_25[LEN_SENSOR_API_1] = SENSOR_API_1_25;
	char sensorApi2_25[LEN_SENSOR_API_2] = SENSOR_API_2_25;
	char sensorApi3_25[LEN_SENSOR_API_3] = SENSOR_API_3_25;
	char sensorApi4_25[LEN_SENSOR_API_4] = SENSOR_API_4_25;
  //
  char sensorLoc_26[LEN_LOCATION_NAME] = LOCATION_NAME_26;  
	char sensorApi1_26[LEN_SENSOR_API_1] = SENSOR_API_1_26;
	char sensorApi2_26[LEN_SENSOR_API_2] = SENSOR_API_2_26;
	char sensorApi3_26[LEN_SENSOR_API_3] = SENSOR_API_3_26;
	char sensorApi4_26[LEN_SENSOR_API_4] = SENSOR_API_4_26;
  char sensorLoc_27[LEN_LOCATION_NAME] = LOCATION_NAME_27;
	char sensorApi1_27[LEN_SENSOR_API_1] = SENSOR_API_1_27;
	char sensorApi2_27[LEN_SENSOR_API_2] = SENSOR_API_2_27;
	char sensorApi3_27[LEN_SENSOR_API_3] = SENSOR_API_3_27;
	char sensorApi4_27[LEN_SENSOR_API_4] = SENSOR_API_4_27;
	//
  char sensorLoc_28[LEN_LOCATION_NAME] = LOCATION_NAME_28;
	char sensorApi1_28[LEN_SENSOR_API_1] = SENSOR_API_1_28;
	char sensorApi2_28[LEN_SENSOR_API_2] = SENSOR_API_2_28;
	char sensorApi3_28[LEN_SENSOR_API_3] = SENSOR_API_3_28;
	char sensorApi4_28[LEN_SENSOR_API_4] = SENSOR_API_4_28;
	char sensorLoc_29[LEN_LOCATION_NAME] = LOCATION_NAME_29;
	char sensorApi1_29[LEN_SENSOR_API_1] = SENSOR_API_1_29;
	char sensorApi2_29[LEN_SENSOR_API_2] = SENSOR_API_2_29;
	char sensorApi3_29[LEN_SENSOR_API_3] = SENSOR_API_3_29;
	char sensorApi4_29[LEN_SENSOR_API_4] = SENSOR_API_4_29;
	//
  char sensorLoc_30[LEN_LOCATION_NAME] = LOCATION_NAME_30;
	char sensorApi1_30[LEN_SENSOR_API_1] = SENSOR_API_1_30;
	char sensorApi2_30[LEN_SENSOR_API_2] = SENSOR_API_2_30;
	char sensorApi3_30[LEN_SENSOR_API_3] = SENSOR_API_3_30;
	char sensorApi4_30[LEN_SENSOR_API_4] = SENSOR_API_4_30;
  char sensorLoc_31[LEN_LOCATION_NAME] = LOCATION_NAME_31;
	char sensorApi1_31[LEN_SENSOR_API_1] = SENSOR_API_1_31;
	char sensorApi2_31[LEN_SENSOR_API_2] = SENSOR_API_2_31;
  char sensorApi3_31[LEN_SENSOR_API_3] = SENSOR_API_3_31;
	char sensorApi4_31[LEN_SENSOR_API_4] = SENSOR_API_4_31;
  //
  void initNonTrivials() 
  {
    strcpy_P(www_username, WWW_USERNAME);
    strcpy_P(www_password, WWW_PASSWORD);
    strcpy_P(wlanssid, WLANSSID);
    strcpy_P(wlanpwd, WLANPWD);
  }
}

static void initApiArray()
{
  String(cfg::sensorLoc_0).toCharArray(multiName[0], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_0).toCharArray(multiApi1[0], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_0).toCharArray(multiApi2[0], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_0).toCharArray(multiApi3[0], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_0).toCharArray(multiApi4[0], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_1).toCharArray(multiName[1], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_1).toCharArray(multiApi1[1], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_1).toCharArray(multiApi2[1], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_1).toCharArray(multiApi3[1], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_1).toCharArray(multiApi4[1], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_2).toCharArray(multiName[2], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_2).toCharArray(multiApi1[2], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_2).toCharArray(multiApi2[2], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_2).toCharArray(multiApi3[2], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_2).toCharArray(multiApi4[2], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_3).toCharArray(multiName[3], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_3).toCharArray(multiApi1[3], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_3).toCharArray(multiApi2[3], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_3).toCharArray(multiApi3[3], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_3).toCharArray(multiApi4[3], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_4).toCharArray(multiName[4], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_4).toCharArray(multiApi1[4], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_4).toCharArray(multiApi2[4], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_4).toCharArray(multiApi3[4], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_4).toCharArray(multiApi4[4], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_5).toCharArray(multiName[5], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_5).toCharArray(multiApi1[5], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_5).toCharArray(multiApi2[5], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_5).toCharArray(multiApi3[5], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_5).toCharArray(multiApi4[5], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_6).toCharArray(multiName[6], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_6).toCharArray(multiApi1[6], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_6).toCharArray(multiApi2[6], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_6).toCharArray(multiApi3[6], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_6).toCharArray(multiApi4[6], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_7).toCharArray(multiName[7], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_7).toCharArray(multiApi1[7], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_7).toCharArray(multiApi2[7], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_7).toCharArray(multiApi3[7], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_7).toCharArray(multiApi4[7], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_8).toCharArray(multiName[8], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_8).toCharArray(multiApi1[8], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_8).toCharArray(multiApi2[8], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_8).toCharArray(multiApi3[8], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_8).toCharArray(multiApi4[8], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_9).toCharArray(multiName[9], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_9).toCharArray(multiApi1[9], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_9).toCharArray(multiApi2[9], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_9).toCharArray(multiApi3[9], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_9).toCharArray(multiApi4[9], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_10).toCharArray(multiName[10], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_10).toCharArray(multiApi1[10], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_10).toCharArray(multiApi2[10], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_10).toCharArray(multiApi3[10], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_10).toCharArray(multiApi4[10], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_11).toCharArray(multiName[11], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_11).toCharArray(multiApi1[11], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_11).toCharArray(multiApi2[11], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_11).toCharArray(multiApi3[11], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_11).toCharArray(multiApi4[11], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_12).toCharArray(multiName[12], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_12).toCharArray(multiApi1[12], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_12).toCharArray(multiApi2[12], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_12).toCharArray(multiApi3[12], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_12).toCharArray(multiApi4[12], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_13).toCharArray(multiName[13], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_13).toCharArray(multiApi1[13], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_13).toCharArray(multiApi2[13], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_13).toCharArray(multiApi3[13], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_13).toCharArray(multiApi4[13], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_14).toCharArray(multiName[14], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_14).toCharArray(multiApi1[14], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_14).toCharArray(multiApi2[14], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_14).toCharArray(multiApi3[14], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_14).toCharArray(multiApi4[14], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_15).toCharArray(multiName[15], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_15).toCharArray(multiApi1[15], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_15).toCharArray(multiApi2[15], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_15).toCharArray(multiApi3[15], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_15).toCharArray(multiApi4[15], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_16).toCharArray(multiName[16], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_16).toCharArray(multiApi1[16], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_16).toCharArray(multiApi2[16], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_16).toCharArray(multiApi3[16], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_16).toCharArray(multiApi4[16], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_17).toCharArray(multiName[17], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_17).toCharArray(multiApi1[17], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_17).toCharArray(multiApi2[17], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_17).toCharArray(multiApi3[17], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_17).toCharArray(multiApi4[17], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_18).toCharArray(multiName[18], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_18).toCharArray(multiApi1[18], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_18).toCharArray(multiApi2[18], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_18).toCharArray(multiApi3[18], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_18).toCharArray(multiApi4[18], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_19).toCharArray(multiName[19], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_19).toCharArray(multiApi1[19], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_19).toCharArray(multiApi2[19], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_19).toCharArray(multiApi3[19], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_19).toCharArray(multiApi4[19], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_20).toCharArray(multiName[20], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_20).toCharArray(multiApi1[20], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_20).toCharArray(multiApi2[20], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_20).toCharArray(multiApi3[20], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_20).toCharArray(multiApi4[20], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_21).toCharArray(multiName[21], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_21).toCharArray(multiApi1[21], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_21).toCharArray(multiApi2[21], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_21).toCharArray(multiApi3[21], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_21).toCharArray(multiApi4[21], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_22).toCharArray(multiName[22], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_22).toCharArray(multiApi1[22], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_22).toCharArray(multiApi2[22], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_22).toCharArray(multiApi3[22], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_22).toCharArray(multiApi4[22], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_23).toCharArray(multiName[23], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_23).toCharArray(multiApi1[23], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_23).toCharArray(multiApi2[23], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_23).toCharArray(multiApi3[23], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_23).toCharArray(multiApi4[23], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_24).toCharArray(multiName[24], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_24).toCharArray(multiApi1[24], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_24).toCharArray(multiApi2[24], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_24).toCharArray(multiApi3[24], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_24).toCharArray(multiApi4[24], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_25).toCharArray(multiName[25], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_25).toCharArray(multiApi1[25], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_25).toCharArray(multiApi2[25], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_25).toCharArray(multiApi3[25], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_25).toCharArray(multiApi4[25], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_26).toCharArray(multiName[26], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_26).toCharArray(multiApi1[26], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_26).toCharArray(multiApi2[26], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_26).toCharArray(multiApi3[26], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_26).toCharArray(multiApi4[26], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_27).toCharArray(multiName[27], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_27).toCharArray(multiApi1[27], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_27).toCharArray(multiApi2[27], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_27).toCharArray(multiApi3[27], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_27).toCharArray(multiApi4[27], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_28).toCharArray(multiName[28], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_28).toCharArray(multiApi1[28], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_28).toCharArray(multiApi2[28], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_28).toCharArray(multiApi3[28], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_28).toCharArray(multiApi4[28], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_29).toCharArray(multiName[29], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_29).toCharArray(multiApi1[29], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_29).toCharArray(multiApi2[29], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_29).toCharArray(multiApi3[29], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_29).toCharArray(multiApi4[29], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_30).toCharArray(multiName[30], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_30).toCharArray(multiApi1[30], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_30).toCharArray(multiApi2[30], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_30).toCharArray(multiApi3[30], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_30).toCharArray(multiApi4[30], LEN_SENSOR_API_4);
  //
  String(cfg::sensorLoc_31).toCharArray(multiName[31], LEN_LOCATION_NAME);
  String(cfg::sensorApi1_31).toCharArray(multiApi1[31], LEN_SENSOR_API_1);
  String(cfg::sensorApi2_31).toCharArray(multiApi2[31], LEN_SENSOR_API_2);
  String(cfg::sensorApi3_31).toCharArray(multiApi3[31], LEN_SENSOR_API_3);
  String(cfg::sensorApi4_31).toCharArray(multiApi4[31], LEN_SENSOR_API_4);
}

// Transform a value to a rounded string
String rounder(float value, uint8_t precision) 
{
  // Valid measurement presented ?
  if (value == -1000) 
  {
    // No, return error message
    return INTL_NOT_MEASURED;
  }

  // Buffer to store the formatted floating-point number
  char buffer[64];

  // Calculate the rounding factor based on the desired precision
  float factor = 1.0f;

  for (int i = 0; i < precision; i++) 
  {
    // Multiply by 10 for each digit
    factor *= 10.0f;    
  }

  // Round the number
  if (value >= 0) 
  {
    value = static_cast<int>(value * factor + 0.5f) / factor;
  } 
  else 
  {
    value = static_cast<int>(value * factor - 0.5f) / factor;
  }

  // Start cleaning at the end of the string
  String(value).toCharArray(buffer, 60); 
  char* end = buffer + std::strlen(buffer) - 1;
  char* end2 = end; 

  // Check if decimal point present, otherwise skip removing zeros
  while (*end2 != '.' && end2 > buffer) { --end2; }

  if (end2 != buffer)       // Equal is decimal point not present !
  {
    // Remove trailing zeros
    while (*end == '0' && end > buffer) { --end; }

    // Remove the decimal point if it's the last character
    if (*end == '.') { --end; }
  }  

  // Null-terminate the cleaned string
  *(end + 1) = '\0';

  // Return result
  return String(buffer);
}

// Check value min/max
static uint checkValue(uint valnow, const uint minval, const uint defval, const uint maxval) 
{
  if ((valnow < minval) || (valnow > maxval))
  {
    valnow = defval;
  }
  return valnow;
}

// Check settings
static void checkSettings() 
{
  if (cfg::multiCompare)
  {
    cfg::multiAverage = true;
  }
  cfg::clockSeconds = checkValue(cfg::clockSeconds, 0, 20, 60);
  cfg::differencePercent = checkValue(cfg::differencePercent, 5, 15, 60);
  cfg::differenceLevel = checkValue(cfg::differenceLevel, 1, 3, 20);
  cfg::displaySpeed = checkValue(cfg::displaySpeed, 15, 25, 75);
  cfg::pauseTime = checkValue(cfg::pauseTime, 3, 7, 15);
  cfg::welkomInterval = checkValue(cfg::welkomInterval, 5, 20, 75);
  cfg::callingInterval = checkValue(cfg::callingInterval, 5, 6, 10);
  cfg::sensordataTimeout = checkValue(cfg::sensordataTimeout, 8, 10, 30);
  cfg::compareLocation = checkValue(cfg::compareLocation, 0, 0, 31);
  cfg::compareLocation2 = checkValue(cfg::compareLocation2, 0, 1, 31);
}

// Wifi & Server declarations
const int   httpPort = 80;
ESP8266WebServer  server(httpPort);

WiFiClient  client;
HTTPClient  http;

// Includes after all variables
#include    "./display-cfg.h"               // Configuration file
#include    "./buildmess.h"                 // Message builder
#include    "./telraam.h"                   // Telraam interface
#include    "./web-interf.h"                // With thanks to sensor.community
#include    "./lcd.h"                       // LCD procedures

// Check heap, show heap loss, & restart if heap too low.
static void checkHeap()
{
  // Determine heap size @start  
  beginHeap = ESP.getFreeHeap();

  if (cfg::debugHeap)
  {
    // Heap memory change occurred ?
    if (beginHeap != prevHeap)
    {
      Serial.print(FPSTR(INTL_HEAPCHANGE_FROM)); Serial.print(prevHeap);
      Serial.print(FPSTR(INTL_HEAPCHANGE_TO)); Serial.print(beginHeap);
      Serial.print(FPSTR(INTL_HEAPDIFF)); Serial.println(beginHeap - prevHeap);
    }
    // Save for next call
    prevHeap = beginHeap;     
  }  

  // Restart if heap below minimum needed
  if (beginHeap < MINIMUM_HEAP_RESTART)
  {
    Serial.println(FPSTR(INTL_LOWHEAP_RESTART));
    display_restart();
  }

  // Restart if heap stays below minimum needed for telraam, for more than maximum time
  if (cfg::showTelRaam)
  {
    // Check if heap above Telraam minimum level
    if (ESP.getFreeHeap() >= MINIMUM_HEAP_TELRAAM)
    {
      // If OK, reset timer for heap control
      heapAboveMinimum = millis();     
    }
    if ((millis() - heapAboveMinimum) > MAXIMUM_TIME_HEAP_UNDER)
    {
      Serial.println(FPSTR(INTL_LOWHEAP_TELRAAM));
      display_restart();
    }
  } 
}

// Visualise just read location results on serial monitor
static void visualiseResults(const unsigned int location)
{
  Serial.print(FPSTR(INTL_SCAN_NUM)); Serial.print(location); 
  Serial.print(FPSTR(INTL_LOC_NAME)); Serial.println(multiName[location]);  
  Serial.print(F("PM10: ")); Serial.println(readPm10[location]);
  Serial.print(F("PM4: ")); Serial.println(readPm4[location]);
  Serial.print(F("PM2.5: ")); Serial.println(readPm25[location]);
  Serial.print(F("PM1: ")); Serial.println(readPm1[location]);
  Serial.print(F(INTL_AVG24H_PM25)); Serial.println(cumulAvgPm25[location]);
  Serial.print(F(INTL_PEAK24H_PM25)); Serial.println(peakPm25[location]); 
  Serial.print(F(INTL_AVG24H_PM10)); Serial.println(cumulAvgPm10[location]);
  Serial.print(F(INTL_PEAK24H_PM10)); Serial.println(peakPm10[location]);  
  Serial.print(F(INTL_QUANT_05UM)); Serial.println(readNbr05[location]);
  Serial.print(F(INTL_QUANT_1UM)); Serial.println(readNbr1[location]);
  Serial.print(F(INTL_QUANT_25UM)); Serial.println(readNbr25[location]);
  Serial.print(F(INTL_QUANT_4UM)); Serial.println(readNbr4[location]);
  Serial.print(F(INTL_QUANT_10UM)); Serial.println(readNbr10[location]);
  Serial.print(F(INTL_PART_SIZE)); Serial.println(readTs[location]);
  Serial.print(F(INTL_VOC_INDEX)); Serial.println(readVoc[location]);
  Serial.print(F(INTL_NOX_INDEX)); Serial.println(readNox[location]);
  Serial.print(F(INTL_TEMPERATURE)); Serial.println(readTemp[location]);
  Serial.print(F(INTL_HUMIDITY)); Serial.println(readHumi[location]);
  Serial.print(F(INTL_AIR_PRESS)); Serial.println(readPres[location]);
  Serial.print(F("LAmin: ")); Serial.println(readLAmin[location]);
  Serial.print(F("LAmax: ")); Serial.println(readLAmax[location]);
  Serial.print(F("LAeq: ")); Serial.println(readLAeq[location]);
  Serial.print(F(INTL_HEAVY)); Serial.println(readHeavy[location]);
  Serial.print(F(INTL_CARS)); Serial.println(readCar[location]);
  Serial.print(F(INTL_BIKES)); Serial.println(readBike[location]);
  Serial.print(F(INTL_PEDESTRIANS)); Serial.println(readPedes[location]);
  Serial.print(F(INTL_V85_SPEED)); Serial.println(readSpeed[location]);
}

static bool isCorrectLength(char *str, uint8_t min, uint8_t max)
{
  uint8_t length = strlen(str);
  return length >= min && length <= max;
}

// Read remote sensor data JSON message from sensor.community server in Germany
static void readRemotePM(char* apiID)
{
  // Keep webserver alive
  handleWebServer();

  if (isCorrectLength(apiID,3,5))
  {
    char resultUrl[80];

    // Build url
    strcpy(resultUrl, SENSOR_API); strcat(resultUrl, apiID); strcat(resultUrl, "/\0");
    if (cfg::debugComms)
    {
      Serial.print(FPSTR(INTL_SENSOR_URL)); Serial.println(resultUrl);
    }
    // Wait for WiFi connection
    if (WiFi.status() == WL_CONNECTED)
    {
      // Start connection and send HTTP header
      if (http.begin(client, resultUrl))
      {
        httpCode = http.GET();

        // HTTP header has been send and Server response header has been handled
        if (httpCode == HTTP_CODE_OK)
        {
          // Has received data, so internet connection beyond WiFi OK
          internetUp = true;

          // Move received data to char* buffer
          String payload = http.getString();
          const char* jsonResponse = payload.c_str();

          // Json parsing
          DynamicJsonDocument pmdata(2048);
          DeserializationError err = deserializeJson(pmdata, jsonResponse);

          if (err)
          {
            Serial.print(FPSTR(INTL_PMPARSING_ERR)); Serial.println(err.f_str());
            return;
          }
          // Extract all possible sensor data values
          JsonArray data = pmdata.as<JsonArray>();

          for (JsonVariant obj: data)
          {
            JsonObject sensor = obj["sensor"];
            JsonArray sensorData = obj["sensordatavalues"];

            // Iterate over sensor data values
            for (JsonVariant value: sensorData)
            {
              String valueType = value["value_type"].as<String>();
              String sensorValue = value["value"].as<String>();
              if      (valueType == "P0")           { realtime.pm1 = sensorValue.toFloat();   }
              else if (valueType == "P2")           { realtime.pm25 = sensorValue.toFloat();  }
              else if (valueType == "P4")           { realtime.pm4 = sensorValue.toFloat();   }
              else if (valueType == "P1")           { realtime.pm10 = sensorValue.toFloat();  }
              else if (valueType == "N05")          { realtime.nbr05 = sensorValue.toFloat(); }
              else if (valueType == "N1")           { realtime.nbr1 = sensorValue.toFloat();  }
              else if (valueType == "N25")          { realtime.nbr25 = sensorValue.toFloat(); }
              else if (valueType == "N4")           { realtime.nbr4 = sensorValue.toFloat();  }
              else if (valueType == "N10")          { realtime.nbr10 = sensorValue.toFloat(); }
              else if (valueType == "TS")           { realtime.ts = sensorValue.toFloat();    }
              else if (valueType == "temperature")  { realtime.temp = sensorValue.toFloat();  }
              else if (valueType == "pressure")     { realtime.press = (sensorValue.toFloat()/100); }
              else if (valueType == "humidity")     { realtime.humi = sensorValue.toFloat();  }
              else if (valueType == "nox")          { realtime.nox = sensorValue.toFloat();   }
              else if (valueType == "voc")          { realtime.voc = sensorValue.toFloat();   }
              else if (valueType == "noise_LA_min") { realtime.LAmin = sensorValue.toFloat(); }
              else if (valueType == "noise_LA_max") { realtime.LAmax = sensorValue.toFloat(); }
              else if (valueType == "noise_LAeq")   { realtime.LAeq  = sensorValue.toFloat(); } 
            }
          }
        }
        else
        {
          Serial.print(FPSTR(INTL_HTTPCODE_ERR)); Serial.println(httpCode);
        }
        // Free the connection
        while (client.connected())
        {
          client.stop();
          delay(100);
        }
        // Close the connection
        http.end();  
      }
    }
  }
}

// Read all 4 sensors of one location
static void readSensorsAtOneLocation(uint8_t location)
{
  // Reset receiving PM variables
  realtime.pm10  = -1000.0f;   realtime.pm4  = -1000.0f;
  realtime.pm25  = -1000.0f;   realtime.pm1  = -1000.0f;
  realtime.voc   = -1000.0f;   realtime.nox  = -1000.0f;
  realtime.press = -1000.0f;   realtime.temp = -1000.0f;
  realtime.humi  = -1000.0f;   realtime.LAmin= -1000.0f;
  realtime.LAmax = -1000.0f;   realtime.LAeq = -1000.0f;
  realtime.nbr05 = -1000.0f;   realtime.nbr1 = -1000.0f;
  realtime.nbr25 = -1000.0f;   realtime.nbr4 = -1000.0f;
  realtime.nbr10 = -1000.0f;   realtime.ts   = -1000.0f;
  realtime.heavy = -1000.0f;   realtime.car  = -1000.0f;
  realtime.bike  = -1000.0f;   realtime.pedes= -1000.0f;
  realtime.speed = -1000.0f;

  // Prepare time-out system
  decrementTimeout = false;

  // Read third PM related sensor
  readRemotePM(multiApi3[location]);        

  // Correct length for PM API-ID ?
  if (isCorrectLength(multiApi4[location],3,5))       
  {
    // Read fourth PM related sensor
    readRemotePM(multiApi4[location]);      
  } 

  // Correct length for Telraam segment-ID ?
  if (isCorrectLength(multiApi4[location],9,11))    
  {
    // Keep webserver alive
    handleWebServer();  

    // Read Telraam as fourth sensor
    readTelraam(multiApi4[location]);
  }

  // Read second & first sensors last as primary sensors, 
  // eventually overwriting the secundary PM related sensors in 3 & 4.
  readRemotePM(multiApi2[location]);        // Read second PM related sensor  
  readRemotePM(multiApi1[location]);        // Read first PM related sensor
}

// Calculate cumulating average for a location
static void calculateCumulAvgPeak(const uint8_t location)
{
  static uint8_t hour = 0;

  // Calculate only with valid data
  if ((readPm25[location] >= 0.0f) && (readPm10[location] >= 0.0f))
  {
    // Calculate average
    calculateCumulAverage(location);

    // Calculate peak
    calculateCumulPeak(location);
  }  

  // Save average & peak values once per hour
  if (myTZ.hour() != hour)
  {
    hour = myTZ.hour();
    saveAvgAndPeak();
  }
}

// Calculate cumulating average
static void calculateCumulAverage(const uint8_t location)
{
  uint8_t installed;

  // Cumulate for PM2.5
  cumulAvgPm25Cnt[location]++;
  cumulAvgPm25[location] += (readPm25[location] - cumulAvgPm25[location]) / cumulAvgPm25Cnt[location];

  // Limit averaging to 24h. 
  if (cumulAvgPm25Cnt[location] > ((60 * 24) / cfg::callingInterval))
  { 
    cumulAvgPm25Cnt[location] = ((60 * 24) / cfg::callingInterval); 
  }

  // Cumulate for PM10
  cumulAvgPm10Cnt[location]++;
  cumulAvgPm10[location] += (readPm10[location] - cumulAvgPm10[location]) / cumulAvgPm10Cnt[location];

  // Limit averaging to 24h. 
  if (cumulAvgPm10Cnt[location] > ((60 * 24) / cfg::callingInterval))
  { 
    cumulAvgPm10Cnt[location] = ((60 * 24) / cfg::callingInterval); 
  }

  // Compute all meter average PM2.5
  allMeterPm25avg = 0;
  installed = locationsInstalled;

  for (int n = 0; n < locationsInstalled; n++)
  {
    if (cumulAvgPm25[n] >= 0)
    {
      allMeterPm25avg += cumulAvgPm25[n];
    }
    else
    {
      installed --;
    }
  }; 
  if (installed > 0)
  { 
    allMeterPm25avg = allMeterPm25avg / installed;
  }
  else
  {
    allMeterPm25avg = 0;
  }  

  // Compute all meter average PM10
  allMeterPm10avg = 0;
  installed = locationsInstalled;

  for (int n = 0; n < locationsInstalled; n++)
  {
    if (cumulAvgPm10[n] >= 0)
    {
      allMeterPm10avg += cumulAvgPm10[n];
    }
    else
    {
      installed --;
    }
  }; 
  if (installed > 0)
  { 
    allMeterPm10avg = allMeterPm10avg / installed;
  }
  else
  {
    allMeterPm10avg = 0;
  }  
}

// Calculate cumulating peak in 4 hour chunks
static void calculateCumulPeak(const uint8_t location)
{
  static uint8_t prevSelect; 
  uint8_t peakSelect = myTZ.hour() >> 2;
  float tmp25;
  float tmp10;
  int n;

  // Disassemble into time segments
  switch (peakSelect)
  {
    case 0: 
    { 
      tmp25 = peak0Pm25[location]; 
      tmp10 = peak0Pm10[location];
      break; 
    }
    case 1: 
    { 
      tmp25 = peak4Pm25[location]; 
      tmp10 = peak4Pm10[location];      
      break; 
    }
    case 2: 
    { 
      tmp25 = peak8Pm25[location]; 
      tmp10 = peak8Pm10[location];      
      break; 
    }
    case 3: 
    { 
      tmp25 = peak12Pm25[location];
      tmp10 = peak12Pm10[location];       
      break; 
    }
    case 4: 
    { 
      tmp25 = peak16Pm25[location];
      tmp10 = peak16Pm10[location];       
      break; 
    }
    case 5: 
    { 
      tmp25 = peak20Pm25[location]; 
      tmp10 = peak20Pm10[location];      
      break; 
    }
  }

  // Accumulate peak values, reset on timeslot change
  if ((tmp25 < readPm25[location]) || (prevSelect != peakSelect))
  {
    tmp25 = readPm25[location];
  }
  if ((tmp10 < readPm10[location]) || (prevSelect != peakSelect))
  {
    tmp10 = readPm10[location];
  }
  prevSelect = peakSelect;  

  // Reassemble time segments into result  
  switch (peakSelect)
  {
    case 0: 
    { 
      peak0Pm25[location] = tmp25;
      peak0Pm10[location] = tmp10;       
      break; 
    }
    case 1: 
    { 
      peak4Pm25[location] = tmp25; 
      peak4Pm10[location] = tmp10;
      break; 
    }
    case 2: 
    { 
      peak8Pm25[location] = tmp25; 
      peak8Pm10[location] = tmp10;
      break; 
    }
    case 3:
    { 
      peak12Pm25[location] = tmp25;
      peak12Pm10[location] = tmp10;       
      break; 
    }
    case 4: 
    { 
      peak16Pm25[location] = tmp25; 
      peak16Pm10[location] = tmp10;      
      break; 
    }
    case 5: 
    { 
      peak20Pm25[location] = tmp25;
      peak20Pm10[location] = tmp10;       
      break; 
    }
  }

  // Collect PM subresults into main PM result
  peakPm25[location] = peak0Pm25[location];
  peakPm10[location] = peak0Pm10[location];

  if (peak4Pm25[location] > peakPm25[location]) 
  { 
    peakPm25[location] = peak4Pm25[location]; 
  }
  if (peak4Pm10[location] > peakPm10[location]) 
  { 
    peakPm10[location] = peak4Pm10[location]; 
  }
  //
  if (peak8Pm25[location] > peakPm25[location])
  { 
    peakPm25[location] = peak8Pm25[location]; 
  }  
  if (peak8Pm10[location] > peakPm10[location])
  { 
    peakPm10[location] = peak8Pm10[location]; 
  }  
  //
  if (peak12Pm25[location] > peakPm25[location]) 
  { 
    peakPm25[location] = peak12Pm25[location]; 
  }
  if (peak12Pm10[location] > peakPm10[location]) 
  { 
    peakPm10[location] = peak12Pm10[location]; 
  }
  //
  if (peak16Pm25[location] > peakPm25[location]) 
  { 
    peakPm25[location] = peak16Pm25[location]; 
  }
  if (peak16Pm10[location] > peakPm10[location]) 
  { 
    peakPm10[location] = peak16Pm10[location]; 
  }  
  //
  if (peak20Pm25[location] > peakPm25[location]) 
  { 
    peakPm25[location] = peak20Pm25[location]; 
  }
  if (peak20Pm10[location] > peakPm10[location]) 
  { 
    peakPm10[location] = peak20Pm10[location]; 
  }

  // Check peak PM2.5 versus average PM2.5 (peak is always > than average !)
  if ((peakPm25[location]) < cumulAvgPm25[location])
  {
    peakPm25[location] = cumulAvgPm25[location];
  }

  // Check peak PM10 versus average PM10 (peak is always > than average !)
  if ((peakPm10[location]) < cumulAvgPm10[location])
  {
    peakPm10[location] = cumulAvgPm10[location];
  }

  // Collect peak PM2.5 & PM10 over all meters
  allMeterPm25peak = 0.0f;
  for (n = 0; n < locationsInstalled; n++)
  {
    if (allMeterPm25peak < peakPm25[n])
    {
      allMeterPm25peak = peakPm25[n];
    }
  };
  //
  allMeterPm10peak = 0.0f;
  for (n = 0; n < locationsInstalled; n++)
  {
    if (allMeterPm10peak < peakPm10[n])
    {
      allMeterPm10peak = peakPm10[n];
    } 
  };   
}

// Save measurement in location array & check for time-out
static void saveInResult(const uint8_t location, float* destination, const float measurement)
{
  // If measurement valid
  if (measurement > -100.0f)
  {
    // Save measurement to destination
    *destination = measurement;

    // Restart time-out
    readTimeout[location] = cfg::sensordataTimeout;
  }
  else
  // If destination still valid
  if (*destination > -100.0f)
  {
    // And no time-out occurred
    if (readTimeout[location] > 0)
    {
      // Don't touch destination, instead decrement time-out
      decrementTimeout = true;
    }
    else
    {
      // Time-out occurred, erase destination
      readTimeout[location] = 0;
      *destination = -1000.0f;
    }
  }
}

// Read all sensors from a location, one at a time 
// & each no more than once in an adjustable time interval.
static void readNextLocation(void)
{
  switch(readState)
  {
    case READ_START:
    {
      // Reset time interval between reads
      betweenReads = millis();
      location = 0;
      readState = READ_BUSY;
    }

    // Fall through
    case READ_BUSY:
    {
      // Keep webserver alive
      handleWebServer();

      // Read all 4 possible sensors @location
      readSensorsAtOneLocation(location);

      // Save measurements in result array, & if no new measurement, 
      // Keep stored values in result array till time-out
      saveInResult(location, &(readPm10[location]), realtime.pm10);
      saveInResult(location, &(readPm4[location]), realtime.pm4);
      saveInResult(location, &(readPm25[location]), realtime.pm25);
      saveInResult(location, &(readPm1[location]), realtime.pm1);
      saveInResult(location, &(readNbr05[location]), realtime.nbr05);
      saveInResult(location, &(readNbr1[location]), realtime.nbr1);
      saveInResult(location, &(readNbr25[location]), realtime.nbr25);
      saveInResult(location, &(readNbr4[location]), realtime.nbr4);
      saveInResult(location, &(readNbr10[location]), realtime.nbr10);
      saveInResult(location, &(readTs[location]), realtime.ts);
      saveInResult(location, &(readVoc[location]), realtime.voc);
      saveInResult(location, &(readNox[location]), realtime.nox);
      saveInResult(location, &(readTemp[location]), realtime.temp);
      saveInResult(location, &(readHumi[location]), realtime.humi);
      saveInResult(location, &(readPres[location]), realtime.press);
      saveInResult(location, &(readLAmin[location]), realtime.LAmin);
      saveInResult(location, &(readLAmax[location]), realtime.LAmax);
      saveInResult(location, &(readLAeq[location]), realtime.LAeq);
      saveInResult(location, &(readHeavy[location]), realtime.heavy);
      saveInResult(location, &(readCar[location]), realtime.car);
      saveInResult(location, &(readBike[location]), realtime.bike);
      saveInResult(location, &(readPedes[location]), realtime.pedes);
      saveInResult(location, &(readSpeed[location]), realtime.speed);     
      //
      if (decrementTimeout)
      {
        // Decrement time-out value when no measurements available
        if (readTimeout[location] > 0) 
        {
          readTimeout[location]--;
        }
      }

      // Prepare to show read up to location#
      {
        if (location > readUpToLocation)
        {
          readUpToLocation = location;
        }
      }

      // Calculate & store cumulating average & peak
      calculateCumulAvgPeak(location);  

      // Visualise the results
      if ((cfg::debugShowData) && (cfg::debugComms))
      {
        visualiseResults(location);
      }

      // Prepare for next location 
      location++;

      // Prepare for end of list
      if (location >= locationsInstalled)
      {
        readState = READ_AFTER;
        firstFullScan = true;
        readUpToLocation = location;  

        if (cfg::debugComms)
        {
          // Show first scan cycle complete
          Serial.println(FPSTR(INTL_ENDOFLIST));
        }
      }
      break;
    }

    case READ_AFTER:
    {   
      // Keep webserver alive
      handleWebServer();

      // Time-out to data request passed ?
      if ((millis() - betweenReads) > (cfg::callingInterval * 60000))
      {
        readState = READ_START;
        if (cfg::debugComms) 
        {
          Serial.println(FPSTR(INTL_RESUMEREAD));
          break;
        }
      }
      delay(250);
      break;
    }
    default:
    {
      readState = READ_START;
      break;
    }
  };
}

// Initialize result array
static void initResultArray()
{
  uint8_t location = 0;
  //
  while (location < locationsInstalled)
  {
    readPm10[location] = -1000.0f;    // PM10
    readPm4[location] = -1000.0f;     // PM4
    readPm25[location] = -1000.0f;    // PM2.5
    readPm1[location] = -1000.0f;     // PM1
    readNbr05[location] = -1000.0f;   // # Particles 0.5µm
    readNbr1[location] = -1000.0f;    // # Particles 1µm
    readNbr25[location] = -1000.0f;   // # Particles 2.5µm
    readNbr4[location] = -1000.0f;    // # Particles 4µm
    readNbr10[location] = -1000.0f;   // # Particles 10µm 
    readTs[location] = -1000.0f;      // TS (Typical particle size)
    readVoc[location] = -1000.0f;     // VOC
    readNox[location] = -1000.0f;     // NOx
    readTemp[location] = -1000.0f;    // Temperature
    readHumi[location] = -1000.0f;    // Humidity
    readPres[location] = -1000.0f;    // Pressure
    readLAmin[location] = -1000.0f;   // LAmin
    readLAmax[location] = -1000.0f;   // LAmax
    readLAeq[location] = -1000.0f;    // LAeq
    readHeavy[location] = -1000.0f;   // Heavy vehicles
    readCar[location] = -1000.0f;     // Cars
    readBike[location] = -1000.0f;    // Bikes
    readPedes[location] = -1000.0f;   // Pedestrians
    readSpeed[location] = -1000.0f;   // V85 speed
    cumulAvgPm25[location] = -1000.0f;// Cumulating average PM2.5
    cumulAvgPm25Cnt[location]= 0;     // Cumulating average PM2.5 counter
    peakPm25[location] = 0.0f;        // Peak 24h/24h PM2.5 
    peak0Pm25[location] = 0.0f;       // Peak PM2.5 0-3h.
    peak4Pm25[location] = 0.0f;       // Peak PM2.5 4-7h.
    peak8Pm25[location] = 0.0f;       // Peak PM2.5 8-11h.
    peak12Pm25[location] = 0.0f;      // Peak PM2.5 12-15h.
    peak16Pm25[location] = 0.0f;      // Peak PM2.5 16-19h.
    peak20Pm25[location] = 0.0f;      // Peak PM2.5 20-23h.              
    cumulAvgPm10[location] = -1000.0f;// Cumulating average PM10
    cumulAvgPm10Cnt[location]= 0;     // Cumulating average PM10 counter
    peakPm10[location] = 0.0f;        // Peak 24h/24h PM10
    peak0Pm10[location] = 0.0f;       // Peak PM10 0-3h.
    peak4Pm10[location] = 0.0f;       // Peak PM10 4-7h.
    peak8Pm10[location] = 0.0f;       // Peak PM10 8-11h.
    peak12Pm10[location] = 0.0f;      // Peak PM10 12-15h.
    peak16Pm10[location] = 0.0f;      // Peak PM10 16-19h.
    peak20Pm10[location] = 0.0f;      // Peak PM10 20-23h.        
    location++;
  }
}

// Format the message to be displayed
static void formatForDisplay()
{
  // Calculate switching point
  int switchingAt = MAX_DEVICES + (MAX_DEVICES / 2);
  // Format message for display
  sprintf(forDisplay, "%s", (messageBuffer[messageOnDisplay]));
  formatChar = forDisplay[0];

  // Remove format character from string
  i = 0; j = 1; 
  while (forDisplay[i++] = forDisplay[j++]);

  // Switch fixed to scroll message if message length longer than display
  if ((strlen(forDisplay) > switchingAt) && (formatChar == FIXED_TEXT)) 
  {
    // Set scrolling mode, 1 pixel spacing
    formatChar = SCROLL_TEXT;
  } 

  // Switch scolled to fixed message if message length shorter or equal than 23 chars                         
  if ((strlen(forDisplay) <= (switchingAt - 1)) && (formatChar == SCROLL_TEXT))  
  {
    // Set fixed mode, 1 pixel spacing     
    formatChar = FIXED_TEXT;
  } 
}

// Convert selector (0 > 3) to display moduletype string
static MD_MAX72XX::moduleType_t moduleName(unsigned int selector)
{
  MD_MAX72XX::moduleType_t module;

  switch (selector)
  {
    case 0:  module = MD_MAX72XX::PAROLA_HW;    break;
    case 1:  module = MD_MAX72XX::GENERIC_HW;   break;
    case 2:  module = MD_MAX72XX::ICSTATION_HW; break;
    default: module = MD_MAX72XX::FC16_HW;      break;
  }
  return module;
}

// Read display moduletype on D0 & D1 pins. 
static unsigned int moduleSelector()
{
  pinMode(D0_PIN, INPUT);
  pinMode(D1_PIN, INPUT); 
  delay(50); 
  unsigned int pin_bit0 = digitalRead(D0_PIN);
  unsigned int pin_bit1 = digitalRead(D1_PIN);
  unsigned int selector = (pin_bit1 << 1) | pin_bit0;
  return selector;
}

// Init Parola library with selected module on D0 & D1.
MD_Parola P = MD_Parola(moduleName(moduleSelector()), DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// Handle all requests for display & web interface
static void handleWebServerAndDisplay() 
{
  // Stay in the loop if AP config busy
  while (wifiConfigLoop);  
  {
    // Keep background processes running
    handleWebServer();

    // Update display
    P.displayAnimate(); 

    // Prevent too much loop-cycles in too short a time 
    delay(50);
  } 
}

// Show a message on display & handle background tasks
static void showOnDisplay(String message)
// Params:
//   message: message to show (!! no format char !!)
{
  if ((cfg::debugDisplay) && (cfg::debugShowData))
  {   
    Serial.print(FPSTR(INTL_ONDISPLAY)); Serial.println(message);
  } 
  P.print(message);
  if (webStarted)  
  { 
    handleWebServerAndDisplay(); 
  }
}

static void showdotsAtStart()
{
  static uint8_t dotsAtStart;

  dotsAtStart = (++dotsAtStart)%(ARRAY_SIZE(workString) - 1);  
  workString[0] = ' ';
  workString[1] = '\0';

  for (i = 0; i < dotsAtStart; i++)
  {
    strcat(workString, ".");
  }
  showOnDisplay(workString);
}

// Active delay, while calling backgroud processes
void activeDelay(float waitMillis)
{
  float localMillis = millis();
  while (millis() < (localMillis + waitMillis))
  {
    handleWebServerAndDisplay();
  }  
}

// Print to display according to format
void printToDisplay()
{
  // Set spacing according to format character
  switch(formatChar)
  {
    case SCROLL_GRAPHICS:
    // Fall through
    case FIXED_GRAPHICS:
    // Graphics mode, no space between chars
    {
      P.setCharSpacing(0);
      break; 
    }
    case FIXED_BLANK:
    {
      break;
    }
    default:
    // Text mode, 1 pixel space between chars
    {
      P.setCharSpacing(1);
      break;
    }
  }
  // Set alignment & texteffect according to format character & display
  switch(formatChar)
  {
    case FIXED_GRAPHICS:
    // Fall through        
    case FIXED_TEXT:
    // Fixed, no scrolling
    {
      P.displayText(forDisplay, PA_LEFT, cfg::displaySpeed, 0, PA_PRINT, PA_NO_EFFECT);
      break;
    }
    case FIXED_BLANK:
    {
      // Clear display & wait for 1/2 second, while handling background tasks
      P.displayClear();      
      activeDelay(500);
      break;
    }
    default:
    // Scrolling display
    {
      P.displayClear();     
      P.displayText(forDisplay, PA_CENTER, cfg::displaySpeed, 0, PA_SCROLL_LEFT, PA_NO_EFFECT);
      break;
    }
  }
  if ((cfg::debugDisplay) && (cfg::debugShowData) && (formatChar != FIXED_BLANK))
  {
    Serial.print(FPSTR(INTL_ONDISPLAY)); Serial.println(forDisplay);
  }    
}

// Prepare locations installed count
void initLocations()
{
  locationsInstalled = 0; 
  while ((strlen(multiApi1[locationsInstalled]) != 0) && (strlen(multiName[locationsInstalled]) != 0)) 
  {
    locationsInstalled++;
  }
} 

// Master setup
void setup()
{
  // Firmly clear the display
  P.begin(); delay(200);
  P.displayReset(); delay(100);
  P.displayClear(); delay(100);
  P.displayReset(); delay(100);

  // Initialise the Parola library    
  P.setInvert(false);     
  P.setPause(0);
  P.setFont(ExtASCII);
  P.setCharSpacing(1);

  // Init configuration variables (before initConfig !)
  cfg::initNonTrivials();
  WiFi.persistent(false); 

  // Init saved configuration
  initConfig();
  
  // Show dots to indicate activity
  showdotsAtStart();
  
  // Initialize serial library
  Serial.begin(115200); 
	while (!Serial) 
  { 
    delay(75); 
    Serial.print(".");   
  }
  Serial.println(".");

  // Show firmware version
  Serial.println(INTL_FIRMWARE ": " SOFTWARE_VERSION_STR " / " INTL_LANG " (" __DATE__ ")");

  // Determine reset reason
  String resetReason = ESP.getResetReason();
  Serial.print(INTL_RESET_REASON); Serial.println(resetReason);  

  /*  Reasons:
  "Power on"
  "Hardware Watchdog"
  "Software Watchdog"
  "Exception"
  "Software/System restart"
  "Deep-Sleep Wake"
  "External System"
  "Unknown"
  */

  if ((selftest_failed = !ESP.checkFlashConfig()  || !ESP.checkFlashCRC() ))
  {
    Serial.println(FPSTR(INTL_SELFTEST_FAIL));

    // Append failed indicator
    SOFTWARE_VERSION += F("-STF");
  }

  // Show dots to indicate activity
  showdotsAtStart();

  // Clear the display buffer
  toDisplayLine = 0; 
  eraseBufferTillEnd();

  // Init location/sensor array
  initApiArray();

  // Prepare locations installed count
  initLocations();

  // Init result array (must be before restoreAvgAndPeak !)
  initResultArray();

  // Restore average & peak values after a (short) power outage. 
  restoreAvgAndPeak();

  // Show # installed locations
  Serial.print(FPSTR(INTL_QUAN_LOCATIONS)); Serial.println(locationsInstalled);

  // Initialize WiFi & Webserver
  connectWifi();
  setupWebserverPages();
  webStarted = true;
  delay(50);

  // Show SSID on display
  showOnDisplay(FPSTR(INTL_WIFI_WIFI) + WiFi.SSID());

  // Show SSID on serial
  Serial.print(FPSTR(INTL_CONNECT_TO)); Serial.println(WiFi.SSID());

  // Setup time zone
  if (myTZ.setLocation(FPSTR(cfg::timeZoneStr)))
  {
    Serial.print(FPSTR(INTL_TIMEZONE)); Serial.println(FPSTR(cfg::timeZoneStr));
  }
  else
  {
    Serial.println(FPSTR(INTL_TIMEUTC));
    myTZ = UTC;
  }

  // Initialise NTP, Syncronize time
  timeCorrect = (waitForSync(10));
  internetUp = timeCorrect;

  // Convert strings to correct codepage for matrix display !!
  convertStrings();

  // Start reading all sensors @first location
  readNextLocation();

  // Long enough on display (for Show SSID) ?    
  activeDelay(250 * cfg::pauseTime);  

  // Show local IP on display
  showOnDisplay(FPSTR(INTL_LOCAL_IP) + WiFi.localIP().toString());

  // Long enough on display (for Local IP) ? 
  activeDelay(1000 * cfg::pauseTime);    

  // Show software version
  showOnDisplay(FPSTR(INTL_FIRMWARE) + (SOFTWARE_VERSION));

  Serial.println(FPSTR(INTL_ENDOF_SETUP));

  // Start with location zero
  locationOnDisplay = 0;

  // Read first sensor, to have a meaningfull first message
  readNextLocation();   

  // Start showing message 0 in buffer
  messageOnDisplay = 0; 

  // Prepare for welcome & time message at startup
  welkomCount = cfg::welkomInterval;  

  // Build messages for first location
  buildNewLocation();

  // Long enough on display (for Software version) ?    
  activeDelay(500 * cfg::pauseTime);  

  // Prepare (first) message for display
  formatForDisplay();

  // Message on display
  printToDisplay();
}

// Main loop
void loop()
{
  // Check heap
  checkHeap();

  // Update display
  while (P.displayAnimate())
  {
    // Prepare message for display
    formatForDisplay();

    // For all messages, except time & blank display
    if ((formatChar != FIXED_TIME) && (formatChar != FIXED_BLANK))
    {
      // Read sensors in display pause      
      startPause = millis();
      while (millis() < startPause + (1000 * cfg::pauseTime))
      {
        // Loop reading all sensors @next locations while in display pause
        readNextLocation();
      }
    }
    // Short timed blank wanted ?
    if (formatChar == FIXED_BLANK)
    {
      // Do short timed blank   
      activeDelay(300);
    }

    // Time display wanted ?
    if (formatChar == FIXED_TIME) 
    {
      // Time display, from now on show moving seconds during a period
      startPause = millis();
      while (millis() < startPause + (cfg::clockSeconds * 1000))
      {
        // Rebuild correct time in message
        buildTime(messageOnDisplay);

        // Format time message for display
        formatForDisplay();

        P.displayText(forDisplay, PA_LEFT, cfg::displaySpeed, 0, PA_PRINT, PA_NO_EFFECT);

        if ((cfg::debugDisplay) && (cfg::debugShowData))
        {
          Serial.print(FPSTR(INTL_ONDISPLAY)); Serial.println(forDisplay);
        }

        // Wait for next second
        while (!secondChanged())
        {
          // Keep webserver alive
          handleWebServerAndDisplay();
        }
      }
    }

    // Go to next message on display
    messageOnDisplay = (++messageOnDisplay)%(NUMSTR);

    // Skip over empty messages, if any
    while (((messageBuffer[messageOnDisplay][0]) == ' ') && (messageOnDisplay != 0))
    {
      messageOnDisplay = (++messageOnDisplay)%(NUMSTR);
    }

    // If all messages of this group shown, build messages for next group
    if (messageOnDisplay == 0)
    {  
      // mark display buffer empty    
      displayBufferEmpty = true;          
      buildNextGroupOfMessages();
    }

    // Prepare next message for display
    formatForDisplay();

    if (formatChar != FIXED_TIME)
    {
      // Message on display
      printToDisplay(); 
    }

    // Keep webserver alive
    handleWebServer();
  }
  handleWebServer();
}
