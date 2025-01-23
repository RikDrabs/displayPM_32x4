// Wifi config
const char WLANSSID[] PROGMEM =       "Ascheweg Lamotte";
const char WLANPWD[]  PROGMEM =       "DcZdNk1V2d3D4u5I6v7E8l";
//const char WLANSSID[] PROGMEM =       "4G-MIFI-88C";
//const char WLANPWD[]  PROGMEM =       "1234567890";
//const char WLANSSID[] PROGMEM =       "UZBrussel_PubliekInternet";
//const char WLANPWD[]  PROGMEM =       ""; 
//const char WLANSSID[] PROGMEM =       "Android_Rik";
//const char WLANPWD[]  PROGMEM =       "kasumaikeb"; 
//const char WLANSSID[] PROGMEM =       "HSBXL";
//const char WLANPWD[]  PROGMEM =       "CLUBMATE2010";
//const char WLANSSID[] PROGMEM =       "telenet-45EAC75";
//const char WLANPWD[]  PROGMEM =       "ruaUn76yeXbf";

// BasicAuth config
const char WWW_USERNAME[] PROGMEM =   "admin";
const char WWW_PASSWORD[] PROGMEM =   "admin";

// Sensor Wifi config (AP config mode)
#define FS_SSID           "DisplayPM"
#define FS_PWD            ""

#define WWW_BASICAUTH_ENABLED         false
#define TIME_FOR_WIFI_CONFIG          600000

#define LEN_PASSWORD      64          // wifi passwords maximum length
#define LEN_SSID          32	        // ssid's maximum length
#define LEN_WWW_USERNAME  64	        // credentials for basic auth of server internal website

#define LEN_TZ_STR        30          // timezone string maximum length
#define LEN_WELCOME       52          // welcome string maximum length

// Default timezone
#define TIMEZONESTR       "Europe/Brussels"

// Define the number of display devices we have in the chain
#define MAX_DEVICES       16          // number of LED display blocks 8*8

// Parola display moduletype selection
// On 2 input bits, provide pull-up & pull-down resistors !
// If you leave pins open, they will be read as 1 most of the time. 
#define D0_PIN            D0          // bit 0
#define D1_PIN            D1          // bit 1

// Hardware coding for moduletype:  
// D0/D1 value 0 = PAROLA hardware
// D0/D1 value 1 = GENERIC hardware
// D0/D1 value 2 = ICSTATION hardware
// D0/D1 value 3 = FC16 hardware

// Connection to display
#define CLK_PIN           D5          // ESP8266 pin to CLOCK-pin display
#define DATA_PIN          D7          // ESP8266 pin to DATA-pin display
#define CS_PIN            D8          // ESP8266 pin to CS-pin display

// API address Sensor.community
#define SENSOR_API        "http://data.sensor.community/airrohr/v1/sensor/" 
#define LEN_API           64          // Maximum length API URL

// API address & key Telraam
#define TELRAAM_API       "https://telraam-api.net/v1/reports/traffic/"
#define TELRAAM_TOKEN     "X7PAAVzTBo2p70ti5nOPU8G5llHOdg5o62TH2EU3"
#define LEN_TOKEN         48          // Maximum length token
#define FREE_TOKEN        true        // Telraam free API token

// Spiffs filenames
#define CONFIG_NAME       "/config"
#define AVG_PEAK_NAME     "/avgpeak" 

// Maximum # of locations to be monitored. Extend at your own risc.
#define LOCATION_MAX      32          // Absolute maximum # locations !!!

// Sensor location & API-ID's lengths
#define LEN_LOCATION_NAME 32          // sensor location name
#define LEN_SENSOR_API_1  6           // sensor API 1 #
#define LEN_SENSOR_API_2  6           // sensor API 2 #
#define LEN_SENSOR_API_3  6           // Sensor API 3 #
#define LEN_SENSOR_API_4  12          // Sensor API 4 #

// Messagebuffer array size defines
#define NUMSTR            20          // maximum number of messages in messagebuffer array
#define NUMCHR            116         // maximum number of characters in one message (= 112 + 4 spare!)

// Valuebuffer array size defines
#define VALUE_STRINGS     34          // maximum number of messages in valuebuffer array
#define LEN_MEASUREMENTS  44          // Sensor measurements

// Heap parameters
#define MINIMUM_HEAP_TELRAAM     18000         // min. heap for telraam API data exchange
#define MAXIMUM_TIME_HEAP_UNDER  (1000*60*15)  // max. milliseconds heap too low for telraam (15 min.)
#define MINIMUM_HEAP_RESTART     6000          // min. heap before restart 

//=====================================
// Default locations & sensors, choose at will
// or add your own file, with "sens_blank.h" as template
// or "sens_demo.h" as example.
//
//#include "./sens-intl.h" 
//#include "./sens-blank.h" 
//#include "./sens-lamotte.h"
//#include "./sens-poincare.h"
//#include "./sens-jeker.h" 
//#include "./sens-test.h" 
#include "./sens-kortrijk.h"
//=====================================

// Settings
#define CLOCKSECONDS      10          // Clock seconds on display
#define DISPLAYSPEED      25          // Display timing: scrolling delay on display (millisec. per step)
#define PAUSETIME         5           // Display timing: pause between messages on display - default 5 seconds.
#define WELCOMEINTERVAL   10          // Welcome repeats after this # of loops
#define CALLINGINTERVAL   6           // Data request interval - default 6 minutes.
#define DIFFERENCEPERCENT 15          // Maximum % deviation before notification
#define DIFFERENCELEVEL   2           // Maximum level deviation before notification
#define SENSORDATATIMEOUT 10          // Sensor data time-out; number of cycles with no reception of data

// Display options
#define PMCHOICE          SELECT_PM25 // default PM2.5 for average & peak values
#define MULTICOMPARE      false       // true = show only meters with overvalues
#define SHOWPMPM          true        // true = show PM values.
#define SHOWPM1PM4        false       // true = show PM1/PM4 if present. 
#define SHOWMETEO         true        // true = show temperature & humidity
#define CORRECTHUMI       false       // true = correct PM values for humidity
#define INTELLIHUMI       false       // true = intelligent humidity calculation
#define SHOWGRAPH         true        // true = show graph.  
#define SHOWAVGNPEAK      false       // true = show 24h. avg. & peak values.
#define SHOWCOMP          false       // true = show compare between two sensors
#define SHOWCOMPINSIDE    false       // true = show compare second sensor inside
#define COMPARELOCATION   0           // Main compare location
#define COMPARELOCATION2  0           // Secundary compare location
#define SHOWAQIADVICE     false       // true = show AQI advice.
#define SHOWWHOADVICE     true        // true = show WHO advice.
#define SHOWDNMS          false       // true = show DNMS data.
#define SHOWVOC           false       // true = show VOC/NOx data.
#define SHOWTELRAAM       false       // true = show Telraam data.
#define SHOWPEDES         false       // true = show Telraam Pedestrian data.
#define SHOWBIKE          true        // true = show Telraam Bike data.
#define SHOWCAR           true        // true = show Telraam Car data.
#define SHOWHEAVY         true        // true = show Telraam Heavy vehicle data.
#define SHOWSPEED         false       // true = show Telraam Pedestrian data.
#define SENSORMISSING     false       // true = show missing meters in multi-configuration
#define MULTIAVERAGE      false       // true = show multi-list average

// Reference station
#define NAME_REF          "Dilbeek-SUK"
#define PM_DRYREF         "12345"
#define HUMI_DRYREF       "12346"
#define PM_WETREF         "12347"
#define HUMI_WETREF       "12348"

// Debug settings
#define DEBUGSHOWDATA     false       // true = debug show data
#define DEBUGDISPLAY      false       // true = debug display
#define DEBUGCOMMS        false       // true = debug comms
#define DEBUGHEAP         false       // true = debug heap
#define DEBUGJSON         false       // true = debug Json

// Define the PM10 & PM2,5 maxima according to WHO
#define MAX10WHO          15          // PM10 maximum = 15µg/m³
#define MAX25WHO          5           // PM2.5 maximum = 5µg/m³

// Define the maxima of the bargraph display
#define MAXGRAPH_PM10     30          // PM10 @ 200% graph bar = 30µg/m³
#define MAXGRAPH_PM25     10          // PM25 @ 200% graph bar = 10µg/m³

// Define the PM10 & PM2,5 values for AQI = 50
#define PM10TOAQI50       50          // PM10 50µg/m³ = 50 AQI
#define PM25TOAQI50       9           // PM2,5 9µg/m³ = 50 AQI 

//==========
// WHO PM2.5 default values table
#define MAXWHOGREEN       +9          // WHO PM maximum for green level
#define MAXWHOYELLOW      +30         // WHO PM maximum for yellow level
#define MAXWHOORANGE      +50         // WHO PM maximum for orange level
#define MAXWHORED         +120        // WHO PM maximum for red level
#define MAXWHOVIOLET      +230        // WHO PM maximum for violet level

const uint16_t whoTable[] =
{
    0,                    // start of table
    MAXWHOGREEN,          // "CODE GREEN: Good air quality - no risc"
    MAXWHOYELLOW,         // "CODE YELLOW: Moderate air quality"
    MAXWHOORANGE,         // "CODE ORANGE: Unhealthy for sensitive groups"
    MAXWHORED,            // "CODE RED: Unhealthy"
    MAXWHOVIOLET,         // "CODE VIOLET: Very unhealty"
    10000,                // "CODE BROWN: Hazardous"
    0,                    // end of table
};

//==========
// AQI default values table
#define MAXAQIGREEN       +50         // AQI PM maximum for green level
#define MAXAQIYELLOW      +100        // AQI PM maximum for yellow level
#define MAXAQIORANGE      +150        // AQI PM maximum for orange level
#define MAXAQIRED         +200        // AQI PM maximum for red level
#define MAXAQIVIOLET      +300        // AQI PM maximum for violet level

const uint16_t aqiTable[] =
{
  0,                      // start of table
  MAXAQIGREEN,            // "CODE GREEN: Good air quality - no risc"
  MAXAQIYELLOW,           // "CODE YELLOW: Moderate air quality"
  MAXAQIORANGE,           // "CODE ORANGE: Unhealthy for sensitive groups"
  MAXAQIRED,              // "CODE RED: Unhealthy"
  MAXAQIVIOLET,           // "CODE VIOLET: Very unhealty"
  10000,                  // "CODE BROWN: Hazardous"
  0,                      // end of table
};

//==========
// DNMS default values table
#define MAXLAEQGREEN      60          // DNMS maximum LAeq for green level
#define MAXLAEQYELLOW     75          // DNMS maximum LAeq for yellow level
#define MAXLAEQORANGE     90          // DNMS maximum LAeq for orange level
#define MAXLAEQRED        100         // DNMS maximum LAeq for red level
#define MAXLAEQVIOLET     110         // DNMS maximum LAeq for violet level
#define MAXLAEQBROWN      120         // DNMS maximum LAeq for brown level

const uint16_t noiseTable[] =
{
  0,                      // start of table
  MAXLAEQGREEN,           // "CODE GREEN: low background noise"
  MAXLAEQYELLOW,          // "CODE YELLOW: "
  MAXLAEQORANGE,          // "CODE ORANGE: "
  MAXLAEQRED,             // "CODE RED: "
  MAXLAEQVIOLET,          // "CODE VIOLET: "
  MAXLAEQBROWN,           // "CODE BROWN: "
  1000,                   // "CODE BLACK: "
  0,                      // end of table
};

//==========
// Telraam aantallen per uur kleurcodering
#define MAXTRAFGREEN      50            // Telraam maximum for green Level
#define MAXTRAFYELLOW     100           // Telraam maximum for yellow level
#define MAXTRAFORANGE     200           // Telraam maximum for orange Level
#define MAXTRAFRED        500           // Telraam maximum for red level
#define MAXTRAFCYAN       1000          // Telraam maximum for cyan Level
#define MAXTRAFVIOLET     2000          // Telraam maximum for violet level
#define MAXTRAFBROWN      5000          // Telraam maximum for brown Level

const uint16_t telraamTable[] =
{
  0,                      // start of table
  MAXTRAFGREEN,           // "CODE GREEN: 0 to 50 per hour"
  MAXTRAFYELLOW,          // "CODE YELLOW: 50 to 100 per hour"
  MAXTRAFORANGE,          // "CODE ORANGE: 100 to 200 per hour"
  MAXTRAFRED,             // "CODE RED: 200 to 500 per hour"
  MAXTRAFCYAN,            // "CODE CYAN: 500 to 1000 per hour"
  MAXTRAFVIOLET,          // "CODE VIOLET: 1000 to 2000 per hour"
  MAXTRAFBROWN,           // "Code BROWN: 2000 to 5000 per hour"
  10000,                  // "CODE BLACK: 5000 to 10000 per hour"
  0,                      // end of table
};
