// Stable multi-config version.
#define   VERSION             "v1.31 Connecting..."                               // firmware version + connecting string
//=========================================================================
// This program's author:
// Copyright (C) 2019/2024 Rik Drabs - rik.drabs@gmail.com                
// Assestraat 55, 1700 Dilbeek - Belgium  
//=========================================================================                              
// This program may be used freely under the GNU General Public Licence,
// for bringing the particulate matter air pollution problem in the
// attention of the general public. When used, this program is WITHOUT 
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
// FITNESS FOR A PARTICULAR PURPOSE. 
// See the GNU General Public License for more details.                                                                                 
// You should have received a copy of the GNU General Public License      
// along with this program. If not, see <http://www.gnu.org/licenses/>. 
// Text till this line should not be removed.  
//=========================================================================
// Large Bargraph Remote Display PM10 & PM2.5 for:
// Luftdaten.info - sensor.community - InfluencAir - LUCHTPIJP. 
// Display on LEDmatrix 16*8*8 dots
//          
// Start of project: 16/09/2019                                           
// Program originally written for project LUCHTPIJP, an initiative of:            
// Beweging.net - CM (Christelijke Mutualiteit) - Bank BELFIUS 
// 
// LUCHTPIJP is the 2018 successor of project InfluencAir, 
// an initiative of: Meetup group CIVIC LAB BRUSSELS, operating under
// the umbrella of OPEN KNOWLEDGE BELGIUM.
//
// InfluencAir followed the Stuttgart project Luftdaten.info in 2017.
//
// The Luftdaten.info project is more recently known as sensor.community.
// Sensor.community is a project of OK Lab Stuttgart under the umbrella of
// OPEN KNOWLEDGE GERMANY.
//=========================================================================
// Parts list:                                                                                                                               
// ===========                                                                                                                               
// 4 pieces display block 4 units 8*8 pixels.                                                                                        
// 1 piece MCU                                                                                                                               
// 1,5 meter ALU profile to fix the display. (see pictures)                                                                                     
// 1 roll transparent doublesided tape. (tesa powerbond 55744-00001)                                                                         
//
// Hardware construction:                                                 
// ======================                                                 
// The free connector on the first display block (input to the whole      
// display) must be removed, and a pin row (5 pins) must be soldered        
// vertically on the back of the PCB in its place.(see pictures)
// A second pin row (4 pins) must be soldered to the output of the 
// second display matrix 8*8 (see pictures for alignment !!)
//                                                                        
// Mount the MCU on an InfluencAir display PCB, and solder it to the
// pins on the back of the first display block 4*8*8. 
// (see pictures)                               
//                                                                        
// Now cascade the 4 display blocks, by bending the pins of 3      
// of them, and soldering them in cascade, so that a level row of         
// 4 by 4 display blocks is created.(see pictures)                        
// 
// Finally check that the display blocks are mounted flat, and correct    
// flatness if needed. Then clean, fix to a flat surface, and tape with   
// double sided tape to the profile. (see pictures)                                                 
//                                                                        
// After mounting, modify config.data.h and/or multi_config.h to use 
// your parameters, flash the program, and enjoy.                                                    
//
// Software adaptation instructions:
// ---------------------------------
// To adapt the WiFi login, see function "initWiFi".
// To modify the language, welcome message and coupled sensors, see config_data.h. 
// To modify the lines shown on display, see function "readAndBuild".
// To modify timings and repeats on the display, see "Display timing".
// When garbage is on the display, modify the hardware type of the display in config_data.h. 
//========================================================================================
// List of supported languages. Feel free to add your own language, and share with us!
// DUTCH, FRENCH, ENGLISH, GERMAN, ITALIAN.
//========================================================================================

// Header files, libraries
#include  <Arduino.h>  
#include  <ESP8266WebServer.h>              // ESP8266 Web Server
#include  <ESP8266WiFi.h>                   // ESP8266 WiFi 
#include  <MD_Parola.h>                     // Parola Library 
#include  <MD_MAX72XX.h>                    // Max72xx Library 
#include  <SPI.h>                           // SPI Library  
#include  <ESP8266HTTPClient.h>             // ESP8266 HTTP Client 
#include  <ESP8266WiFiMulti.h>              // ESP8266 WiFi multiple AP login
#include  "EEPROM.h"                        // Eeprom library
#include  "8266_ntp.h"                      // NTP routines
#include  "parola_fonts.h"                  // Parola adapted fonts 
#include  "config_data.h"                   // Local configuration data
#include  "multi_config.h"                  // Multi configuration data
#include  "setup_page.h"                    // Web Setup Page
                                        
// DEBUG defines
#define   DEBUG               0             // 0 = normal; 1 = debug

// Display repeat setting
#define   REPEAT_COUNT        2

// Define website with data
#define   SENSORSERVER_URL    "http://data.sensor.community/airrohr/v1/sensor/"   // server address with data

// Use terminal on serial-line/USB for debugging
#if DEBUG
  #define PRINT(s, x) {Serial.print(F(s)); Serial.print(x);}
  #define PRINTS(s)   {Serial.print(s);}
#else
  #define PRINT(s, x)
  #define PRINTS(s)
#endif

// Define the PM10 & PM2,5 maxima according to WHO
#define   PM10_MAX            15            // PM10 maximum = 15µg/m³
#define   PM25_MAX            5             // PM2.5 maximum = 5µg/m³            
#define   MXV_PM10            30
#define   MXV_PM25            10

// Define the PM10 & PM2,5 values for AQI = 50
#define   AQI10_UG            54            // PM10  54µg/m³ = 50 AQI
#define   AQI25_UG            12            // PM2,5 12µg/m³ = 50 AQI 
  
// Define Web Server
ESP8266WebServer server(80);                // web server on port 80

// Define WiFi multi login interface
ESP8266WiFiMulti WiFiMulti;

// Display modes
#define     SCROLL_ONEPIXEL   'S'           // Scrolling, with one pixel between characters (for showing separate chars)
#define     SCROLL_NOPIXEL    's'           // Scrolling, with zero pixels between characters (for showing graphics)
#define     FIXED_ONEPIXEL    'F'           // Fixed left justified, with one pixel between characters (for showing separate chars)
#define     FIXED_ONEPIXEL_T  'T'           // Fixed left justified, with one pixel between characters (for showing separate chars) + Update time msg. before display 
#define     FIXED_NOPIXEL     'f'           // Fixed left justified, with zero pixels between characters (for showing graphics)
 
// PM string ID defines
#define     STRING_PM10       0             // String "PM10"
#define     STRING_PM25       1             // String "PM2,5"
#define     STRING_UGRAM3     2             // String "µg/m³"
#define     STRING_DROPLET    3             // String droplet sign
#define     STRING_THERMO     4             // String thermometer sign
#define     STRING_DEGREES    5             // String degrees celcius
#define     STRING_PM10_EQ    6             // String "PM10 waarde = "
#define     STRING_PM25_EQ    7             // String "PM2,5 waarde = " 
#define     STRING_TEMP_EQ    8             // String "Temperatuur = "
#define     STRING_VOCHT_EQ   9             // String "Vochtigheid = " 
#define     BINNEN            10            // String "Binnen"
#define     BUITEN            11            // String "Buiten"
#define     PERCNTSTR0        12            // String "Er is " - meer
#define     PERCNTSTR1        13            // String "Er is " - minder
#define     PERCNTSTR2        14            // String "% meer " 
#define     PERCNTSTR3        15            // String "% minder "
#define     PERCNTSTR4        16            // String " dan bij meter "
#define     PERCNTSTR5        17            // String " fijnstof bij meter "
#define     READSERVER        18            // String "Leest gegevens..."
#define     ERRORNODATA       19            // String " geen nieuwe gegevens."
#define     STRING_MAX24      20            // String "Maximumwaarde 24h. " 
#define     STRING_MEAN       21            // String "Gemiddelde over alle meters "
#define     STRING_TEHOOG     22            // String "Overschrijding op meter "
#define     STRING_NODATA     23            // String "Geen resultaten van "
#define     NULLSTR           24            // String ""

// Display keyword ID defines
#define     SHOW_ALPHA        1             // Show alphanumerical result
#define     SHOW_GRAPH        2             // Show graphical result
#define     SHOW_VALUE        3             // Show value after fixed text
#define     SHOW_COMPAR       4             // Show indoor/outdoor comparison in text
#define     SHOW_PERCNT       5             // Show outdoor1/outdoor2 comparison in percent
#define     SHOW_ADVICE       6             // Show AQI advice about outdoor air quality
#define     SHOW_MAX24        7             // Show 24h maximum value
#define     SHOW_TIME         8             // Show actual time

// Data selector PM10/PM2,5/Temp/Humi
#define     OUT_PM10          1             // Select outdoor PM10 data 
#define     OUT_PM25          2             // Select outdoor PM2,5 data 
#define     OUT_TEMP          3             // Select outdoor temperature data
#define     OUT_HUMI          4             // Select outdoor humidity data
#define     IN_PM10           5             // Select indoor PM10 data
#define     IN_PM25           6             // Select indoor PM2,5 data
#define     PM10_PM25         7             // Select outdoor PM10 & PM2,5 data combined 

// Global variables
// ================
// General advice when adding to or adapting the program:
// Use global variables instead of local ones, since the stack of the ESP8266 is
// only 4K and nearly full, and that's the place where local variables are stored. 
// Adding more local variables increases the risc for crashes dramatically. 
// I know, using only globals is normally no good programming practice...
//                                                                       
float       pm10 = -1000.0;                 // receptor for PM10
float       pm25 = -1000.0;                 // receptor for PM2,5
float       temperature = -1000.0;          // receptor for temperature
float       humidity = -1000.0;             // receptor for humidity
char        timestamp[21] = "2020-12-31  23:59:59";  // receptor for timestamp 
uint8_t     actualHour = 24;                // actual hour of measuring period
//
float       outdoorPm10 = -1000.0;          // receptor for outdoor PM10
float       outdoorPm25 = -1000.0;          // receptor for outdoor PM2,5
float       outdoorTemperature = -1000.0;   // receptor for outdoor temperature
float       outdoorHumidity = -1000.0;      // receptor for outdoor humidity
char        outdoorTimestamp[21] = "2020-12-31  23:59:59";  // receptor for outdoor timestamp
char        outdoorName[50];                // name of outdoor sensor 1
//
float       indoorPm10 = -1000.0;           // receptor for indoor PM10
float       indoorPm25 = -1000.0;           // receptor for indoor PM2,5
float       indoorTemperature = -1000.0;    // receptor for indoor temperature
float       indoorHumidity = -1000.0;       // receptor for indoor humidity
char        indoorTimestamp[21] = "2020-12-31  23:59:59";  // receptor for indoor timestamp
char        indoorName[50];                 // name of indoor sensor 2
//
float       multiPm10[MULTI_MAX];           // receptor array PM10 multi configuration
float       multiPm25[MULTI_MAX];           // receptor array PM2,5 multi configuration
float       meanPm10 = 0;                   // mean PM10 value in array
float       meanPm10Max = 0;                // mean PM10 maximum value in array 
float       meanPm25 = 0;                   // mean PM2,5 value in array 
float       meanPm25Max = 0;                // mean PM2,5 maximum value in array
uint8_t     multiLine = 0;                  // message line for multi configuration
//
uint8_t     i;                              // general variables
uint8_t     j;                              // ..
uint8_t     k;                              // ..
uint8_t     m;                              // ..
//    
float       compareResult = 0.0;            // result of comparing indoor & outdoor
float       posCompareResult = 0.0;         // compare result for printing purposes - always positive
bool        resultFound = false;            // result found marker
//    
uint8_t     messageSelect = 0;              // active message selector
uint8_t     barMessage = 0;                 // bar message on display while rereading data
uint8_t     repeatCount = REPEAT_COUNT;     // repeat counter
//
char        formatChar;                     // separated format character in message 
char        sds011url[70];                  // sds url build string
char        dht22url[70];                   // dht url build string
char        displayIP[50];                  // ip-address of display
char        forDisplay[50];                 // string for display
char        workString[50];                 // work string
char        displayString[150];             // display string
//
float       pm10_Max[25];                   // array for storing the hourly maximum values PM10
float       pm25_Max[25];                   // array for storing the hourly maximum values PM2,5
float       pm10_Max24 = 0;                 // actual 24h maximum PM10
float       pm25_Max24 = 0;                 // actual 24h maximum PM2,5

// Global defines
WiFiClient  client;
HTTPClient  http;

// Define text strings for messages
char  *messageText[] =
{
  "  PM10: ",                               // PM10: string
  "  PM2,5: ",                              // PM2,5: string
  "µg/m³",                                  // µg/m³ string
  "  ñ ",                                   // droplet sign
  "  Ñ ",                                   // thermometer sign
  "°C",                                     // degrees celsius
//
#ifdef DUTCH  
  "PM10 waarde = ",     
  "PM2,5 waarde = ",
  "Temperatuur = ",
  "Vochtigheid = ",
  "Binnen",
  "Buiten",
  "Er is ",
  "Er is ",
  "% méér ",
  "% minder ",
  " dan bij meter ",
  " fijnstof bij meter ",
  "Leest gegevens...",
  " geen nieuwe gegevens.",
  "Piek 24u.", 
  "Gemiddelde over alle meters: ",
  "In overschrijding: ",
  "Geen gegevens:",
  "",
#endif
#ifdef FRENCH
  "Valeur PM10 = ",
  "Valeur PM2,5 = ",
  "Température = ",
  "Humidité = ",
  "A l'intérieur",
  "A l'extérieur",
  "Il y a ",
  "Il y a ",
  "% plus de particules fines ",
  "% moins de particules fines ",
  " qu'aux environs de ",
  " aux environs de ",
  "Lecture de données...",
  " pas de nouvelles données.",
  "Crête 24h.",
  "Moyenne de toutes les mesures: ",
  "En dépassement: ",
  "Pas de données:",
  "",  
#endif
#ifdef ENGLISH
  "PM10 value = ",
  "PM2,5 value = ",
  "Temperature = ",
  "Humidity = ",
  "Inside",
  "Outside",
  "There is ",
  "There is ",
  "% more particulate matter ",
  "% less particulate matter ",
  " than in the vicinity of ",
  " in the vicinity of ",
  "Reading data...",
  " no new data.",
  "Peak 24h.",
  "Mean of all measurements: ",
  "In exceedance: ",
  "No data:", 
  "", 
#endif
#ifdef GERMAN
  "PM10 Werte = ",
  "PM2,5 Werte = ",
  "Temperatur = ",
  "Feuchtigkeit = ",
  "Innen",
  "Aussen",
  "Es gibt ",
  "Es gibt ",
  "% mehr ",
  "% weniger ",
  " als am Meter ",
  " Feinstaub am Meter ",
  "Lesen von Daten...",
  " keine neue Daten.",
  "Spitz 24h.",
  "Durchschnitt über alle Meter: ",
  "In uberschreitung: ",
  "Keine daten:",
  "",
#endif
#ifdef ITALIAN
  "Valore PM10 = ",
  "Valore PM2,5 = ",
  "Temperatura = ",
  "Umidità = ",
  "Interno",
  "Esterno",
  "C'è il ",
  "C'è materia il ",
  "% in più",
  "% in meno ",
  " che in metri a ",
  " di particolato in metri a ",
  "Leggere i dati...",
  " nessun nuovo dato.",
  "Picco 24h.", 
  "Media su tutti i metri: ",
  "In eccesso: ", 
  "Nessun dato:",
  "",  
#endif
};

// Damping factor for small values PM
// Damping is added to both PM values before comparing to % result.
#define     DAMPING           10      // minimum 0 - maximum 20

// Table driven comparative system
float   compareTable[] = 
{  
  //==============================
    -100,   // Outdoor = -100%/-35%
    -35,    // Open windows
  //==============================
    -35,    // Outdoor = -35%/-10%
    -10,    // No advice for windows
  //==============================
    -10,    // Outdoor = -10%/+10%
    +10,    // No advice for windows
  //==============================
    +10,    // Outdoor = +10%/+35%
    +35,    // No advice for windows
  //==============================
    +35,    // Outdoor = +35%/+100%
    +100,   // Close windows
  //==============================
    +100,   // Outdoor = >+100%
    +10000, // Close windows
  //==============================
};

// Text strings for comparative system
char  *compareText[] =
{  
#ifdef DUTCH
  //"0         1         2         3         4         5         6         7         8         9         0         1"
  //"012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
  //"==============================================================================================================="
    "De kwaliteit van de binnenlucht is slechter dan die van de buitenlucht - Verluchten!",                           // Outdoor -100%/-30%
    "De kwaliteit van de binnenlucht is wat slechter dan die van de buitenlucht.",                                    // Outdoor -30%/-10%
    "De kwaliteit van de binnen- en buitenlucht is ongeveer gelijk.",                                                 // Outdoor -10%/+10%
    "De kwaliteit van de binnenlucht is wat beter dan die van de buitenlucht.",                                       // Outdoor +10%/+30%
    "De kwaliteit van de binnenlucht is beter dan die van de buitenlucht - Ramen en deuren sluiten!",                 // Outdoor +30%/+100%
    "De kwaliteit van de binnenlucht is veel beter dan die van de buitenlucht - Ramen en deuren sluiten!",            // Outdoor >100%
#endif
#ifdef FRENCH
  //"==============================================================================================================="
    "La qualité de l'air interieure est plus mauvaise que celle de l'air exterieure - Ventiler!",                     // Outdoor -100%/-30%
    "La qualité de l'air interieure est un peu plus mauvaise que celle de l'air exterieure.",                         // Outdoor -30%/-10%
    "Les qualités de l'air interieure et de l'air exterieure sont à peu près égales.",                                // Outdoor -10%/+10%
    "La qualité de l'air interieure est un peu plus meilleure que celle de l'air extérieure.",                        // Outdoor +10%/+30%
    "La qualité de l'air interieure est meilleure que celle de l'air extérieure - Fermer portes et fenêtres!",        // Outdoor +30%/+100%
    "La qualité de l'air interieure est meilleure que celle de l'air extérieure - Fermer portes et fenêtres!",        // Outdoor >100%
#endif
#ifdef ENGLISH
  //"==============================================================================================================="
    "The interior air is of worse quality than the exterior air - Aerate!",                                           // Outdoor -100%/-30%
    "The interior air is of somewhat worse quality than the exterior air.",                                           // Outdoor -30%/-10%
    "The quality of interior air and exterior air is approximately equal.",                                           // Outdoor -10%/+10%
    "The interior air is of somewhat better quality than the exterior air.",                                          // Outdoor +10%/+30%
    "The interior air is of better quality than the exterior air - Close doors and windows!",                         // Outdoor +30%/+100%
    "The interior air is of much better quality than the exterior air - Close doors and windows!",                    // Outdoor >100%
#endif
#ifdef GERMAN
  //"==============================================================================================================="
    "Die Luftqualität der Innenluft ist schlechter als die der Außenluft – Lüften!",                                  // Outdoor -100%/-30%
    "Die Luftqualität der Innenluft ist etwas schlechter als die der Außenluft.",                                     // Outdoor -30%/-10%
    "Die Luftqualität der Innen- und Außenluft ist etwa gleich.",                                                     // Outdoor -10%/+10%
    "Die Luftqualität der Innenluft ist etwas besser als die der Außenluft.",                                         // Outdoor +10%/+30%
    "Die Luftqualität der Innenluft ist besser als die der Außenluft – Fenster und Türen schließen!",                 // Outdoor +30%/+100%
    "Die Luftqualität der Innenluft ist viel besser als die der Außenluft – Fenster und Türen schließen!",            // Outdoor >100%
#endif
#ifdef ITALIAN
  //"==============================================================================================================="
    "La qualità dell'aria interna è peggiore di quella dell'aria esterna - Ventilare!",                               // Outdoor -100%/-30%
    "La qualità dell'aria interna è leggermente peggiore di quella dell'aria esterna.",                               // Outdoor -30%/-10%
    "La qualità dell'aria interna ed esterna è più o meno la stessa.",                                                // Outdoor -10%/+10%
    "La qualità dell'aria interna è leggermente migliore di quella dell'aria esterna.",                               // Outdoor +10%/+30% 
    "La qualità dell'aria interna è migliore dell'aria esterna: chiudi finestre e porte!",                            // Outdoor +30%/+100%
    "La qualità dell'aria interna è molto migliore di quella dell'aria esterna - Chiudi finestre e porte!",           // Outdoor >100%
#endif
};

// Table driven WHO/AQI warning system
// Based on info at https://aqicn.org/sensor/sds011/
//                  http://www.airqualitynow.eu/about_indices_definition.php
//                  https://www.airnow.gov/index.cfm?action=aqibasics.aqi
//                  https://www.airnow.gov/aqi/aqi-calculator/
//

float   AQItable[] =
{
  //==============================
  +0,     // AQI 0 to 50
  +50,    // "CODE GREEN: Good air quality - no risc"
  //==============================
  +51,    // AQI 51 to 100
  +100,   // "CODE YELLOW: Moderate air quality / WHO norm exceeded"
  //==============================
  +101,   // AQI 101 to 150
  +150,   // "CODE ORANGE: Unhealthy for sensitive groups"
  //==============================
  +151,   // From 31 to 40    (AQI 151 to 200)
  +200,   // "CODE RED: Unhealthy"
  //==============================
  +201,   // From 41 to 75    (AQI 201 to 300)
  +300,   // "CODE VIOLET: Very unhealty"
  //==============================
  +301,   // From 76 to 10000 (AQI 300+)
  +30000, // "CODE BROWN: Hazardous"
  //==============================
};

// Text strings for WHO/AQI warning system
// Based on info at https://aqicn.org/sensor/sds011/ 
// and http://www.airqualitynow.eu/about_indices_definition.php
//
char  *AQItext[] =
{
#ifdef DUTCH
  //"0         1         2         3         4         5         6         7         8         9         0         1"
  //"012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
  //"==============================================================================================================="  
    "Code GROEN: De buitenluchtkwaliteit is goed. Er zijn geen gezondheidsrisico's.",                                 // Code green
    "Code GEEL: De buitenluchtkwaliteit is matig. De WHO norm is overschreden.",                                      // Code yellow
    "Code ORANJE: De buitenlucht is ongezond voor kwetsbare groepen.",                                                // Code orange
    "Code ROOD: De buitenlucht is ongezond. Iedereen kan gezondheidseffecten ondervinden.",                           // Code red
    "Code VIOLET: De buitenlucht is zeer ongezond. Iedereen kan gezondheidseffecten ondervinden.",                    // Code violet
    "Code BRUIN: De buitenlucht is gevaarlijk. Iedereen kan ernstige gevolgen voor de gezondheid ervaren.",           // Code brown
#endif
#ifdef FRENCH
  //"==============================================================================================================="
    "Code VERT: La qualité de l'air extérieur est bonne. Il n'y a pas de risque pour la santé.",                      // Code green
    "Code JAUNE: La qualité de l'air extérieur est médiocre. Les normes OMS sont dépassées.",                         // Code yellow
    "Code ORANGE: La qualité de l'air extérieur peut provoquer des problèmes de santé aux personnes sensibles.",      // Code orange
    "Code ROUGE: La qualité de l'air extérieur est malsaine. Tout le monde peut subir des effets de santé.",          // Code red
    "Code VIOLET: La qualité de l'air extérieur est très malsaine. Tout le monde peut subir des effets de santé.",    // Code violet
    "Code MARON: La qualité de l'air extérieur est dangereuse. Tout le monde peut subir des effets de santé graves",  // Code brown
#endif
#ifdef ENGLISH
  //"==============================================================================================================="
    "Code GREEN:  The exterior air quality is satisfactory, and adverse health effects are not expected.",            // Code green
    "Code YELLOW: The exterior air quality is moderate. WHO pollution limits are breached.",                          // Code yellow
    "Code ORANGE: The exterior air is unhealthy for sensitive groups.",                                               // Code orange
    "Code RED: The exterior air is unhealthy. Everyone may experience health effects.",                               // Code red
    "Code VIOLET: The exterior air is very unhealthy. Everyone may experience health effects.",                       // Code violet
    "Code BROWN: The exterior air is hazardous. Everyone may experience more serious health effects",                 // Code brown
#endif
#ifdef GERMAN
  //"==============================================================================================================="
    "Code GRÜN: Die Außenluftqualität ist gut. Es bestehen keine Gesundheitsrisiken.",                                // Code green
    "Code GELB: Die Außenluftqualität ist mäßig. Der WHO-Standard wurde übertroffen.",                                // Code yellow
    "Code ORANGE: Die Außenluft ist für gefährdete Personen ungesund.",                                               // Code orange
    "Code ROT: Die Außenluft ist ungesund. Gesundheitsschäden können bei jedem auftreten.",                           // Code red
    "Code VIOLETT: Die Außenluft ist sehr ungesund. Gesundheitsschäden können bei jedem auftreten.",                  // Code violet
    "Code BRAUN: Die Außenluft ist gefährlich. Jeder kann schwerwiegende gesundheitliche Auswirkungen haben.",        // Code brown      
#endif
#ifdef ITALIAN
  //"==============================================================================================================="
    "Codice VERDE: La qualità dell'aria esterna è buona. Non ci sono rischi per la salute.",                          // Code green
    "Codice GIALLO: La qualità dell'aria esterna è moderata. Lo standard dell'OMS è stato superato.",                 // Code yellow 
    "Codice ARANCIONE: L'aria esterna non è salubre per le persone vulnerabili gruppi.",                              // Code orange
    "Codice ROSSO: L'aria esterna è malsana. Chiunque può riscontrare effetti sulla salute.",                         // Code red
    "Codice VIOLA: L'aria esterna è molto malsana. Chiunque può riscontrare effetti sulla salute.",                   // Code violet
    "Codice MARRONE: L'aria esterna è pericolosa Chiunque può sperimentare gravi effetti sulla salute.",              // Code brown
#endif
};

// This is the messagebuffer. It receives the new lines to display from received data, 
// or holds previous results for display, if received data is temporarily unavailable.
// Messages are constructed according to definition in the "readAndBuild" function.
// You can also place fixed messages directly in the buffer, to be displayed.
// Messages here must start with S for scrolling, or with F for fixed format.
// Use lowercase (s, f) for characters without intermediate pixel column (graphics, etc.)
// A maximum of 26 messages is provided for. Feel free to expand the buffer!

// messagebuffer array size defines
#define     NUMSTR           26       // number of strings in messagebuffer array
#define     NUMCHR           120      // number of stringcharacters in messagebuffer array (= 110 + 10 spare!)

char        message[NUMSTR][NUMCHR] = // message buffer
{  
//"0         1         2         3         4         5         6         7         8         9         0         1"
//"012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
//"==============================================================================================================="
  WELCOME_MESSAGE,                                                                                                  // 0  Title - welcome message
  "                                                                                                               ",// 1  
  "                                                                                                               ",// 2
  "                                                                                                               ",// 3
  "                                                                                                               ",// 4
  "                                                                                                               ",// 5
  "                                                                                                               ",// 6
  "                                                                                                               ",// 7
  "                                                                                                               ",// 8
  "                                                                                                               ",// 9
  "                                                                                                               ",// 10
  "                                                                                                               ",// 11
  "                                                                                                               ",// 12
  "                                                                                                               ",// 13
  "                                                                                                               ",// 14
  "                                                                                                               ",// 15
  "                                                                                                               ",// 16
  "                                                                                                               ",// 17
  "                                                                                                               ",// 18
  "                                                                                                               ",// 19
  "                                                                                                               ",// 20
  "                                                                                                               ",// 21
  "                                                                                                               ",// 22
  "                                                                                                               ",// 23
  "                                                                                                               ",// 24
  "                                                                                                               ",// 25
};  
//"0         1         2         3         4         5         6         7         8         9         0         1"
//"012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"

// This is the message valid & time-out array
// A zero means the corresponding message is not valid (anymore) and should not be shown

#if DEBUG
  #define   MSGLINE_TIMEOUT   2       // Messageline time-out number of cycles for testing.
#else
  #define   MSGLINE_TIMEOUT   10      // Messageline time-out number of cycles when no reception of data - default 10.
#endif
  
uint8_t     messageValid[NUMSTR] =    // message valid & time-out array
{
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

void readRemote(char* sds011url, char* dht22url)
// read remote sensor data JSON messages (from server in Germany)
// interprete the always changing layout of the 2 response messages,
// confusing the algorithm to readout the values.
// always read the most recently measured values !
{

// restart if heap low 
  if (ESP.getFreeHeap() < 6000) {
    ESP.restart();
  }

  char* pActualDataSet;
  char* pLastDataSet;
  char* pTypeP1;
  char* pValueP1;
  char* pTypeP2;
  char* pValueP2;
  char* pTimeD1;
  char* pTimeD2;

  // make reuse possible
  http.setReuse(true);

  // prepare default values
  pm10 = -1000.0;
  pm25 = -1000.0;
  temperature = -1000.0;
  humidity = -1000.0;

  // wait for WiFi connection
  if (WiFiMulti.run() == WL_CONNECTED) {

    // start connection and send HTTP header
    if (http.begin(client, sds011url)) {
      uint16_t httpCode = http.GET();

      // HTTP header has been send and Server response header has been handled
      if (httpCode == HTTP_CODE_OK) {      
        String payload = http.getString();
        const char *jsonx = payload.c_str();
                  
        // interprete JSON message for PM10 & PM2.5 values
        pActualDataSet = strstr(jsonx, "\"sensordatavalues\":");
 
        // scan to last dataset
        while ((pActualDataSet)&&(pLastDataSet = strstr(pActualDataSet+1, "\"sensordatavalues\":"))) {
          pActualDataSet = pLastDataSet;
        }
        // valid dataset found?
        if (pActualDataSet) {
          // yes, set pointers to value_type & value parameters
          if (pTypeP1 = strstr(pActualDataSet, "\"value_type\":\"P1\"")) {
            if (pTypeP2 = strstr(pActualDataSet, "\"value_type\":\"P2\"")) {
              if (pValueP1 = strstr(pActualDataSet, "\"value\":")) {
                if (pValueP2 = strstr(pValueP1+1, "\"value\":")) {
                  // parameters reversed?
                  if (pTypeP1 < pTypeP2) {
                    // not reversed, readout PM10 and then PM2.5
                    sscanf((pValueP1+9), "%f", &pm10);
                    sscanf((pValueP2+9), "%f", &pm25);
                  } else {
                    // reversed, readout PM2.5 and then PM10
                    sscanf((pValueP1+9), "%f", &pm25);
                    sscanf((pValueP2+9), "%f", &pm10);
                  }
                  // set repeat counter when data ok
                  repeatCount = REPEAT_COUNT;

                  // handle maxima 24 hours
                  setMaxima24h(pm10, OUT_PM10);
                  setMaxima24h(pm25, OUT_PM25);
                }
              }
            }
          }
        }
      }
    }
  } 
    
  #if DHT_ACTIVE
    if (sds011url != dht22url) {
      // wait for WiFi connection
      if (WiFi.status() == WL_CONNECTED) {
 
        // start connection and send HTTP header
        if (http.begin(client, dht22url)) {
          uint16_t httpCode = http.GET();
            
          // HTTP header has been send and Server response header has been 
          if (httpCode == HTTP_CODE_OK) {
             String payload = http.getString();
             const char *jsonx = payload.c_str();

            // interprete JSON message for humidity & temperature values
            pActualDataSet = strstr(jsonx, "\"sensordatavalues\":");

            // scan to last dataset
            while ((pActualDataSet)&&(pLastDataSet = strstr(pActualDataSet+1, "\"sensordatavalues\":"))) {
              pActualDataSet = pLastDataSet;
            }
            // valid dataset found?
            if (pActualDataSet) {
              // yes, set pointers to value_type & value parameters
              if (pTypeP1 = strstr(pActualDataSet, "\"value_type\":\"humidity\"")) {
                if (pTypeP2 = strstr(pActualDataSet, "\"value_type\":\"temperature\"")) {
                  if (pValueP1 = strstr(pActualDataSet, "\"value\":")) {
                    if (pValueP2 = strstr(pValueP1+1, "\"value\":")) {
                      // parameters reversed?
                      if (pTypeP1 < pTypeP2) {
                        // not reversed, readout humidity and then temperature
                        sscanf((pValueP1+9), "%f", &humidity);                       sscanf((pValueP2+9), "%f", &temperature);
                      } else {
                        // reversed, readout temperature and then humidity
                        sscanf((pValueP1+9), "%f", &temperature);
                        sscanf((pValueP2+9), "%f", &humidity);
                      }                                     
                    }
                  }
                }
              }
            }
          }
        }
      } 
    }
  #endif
}

void buildTotalMessage(uint8_t msgLine, char* desc)
// Construct displaymessage from all values read.
// Construct error message if not all values OK, or keep previous message if available.
{
  displayString[0] = SCROLL_ONEPIXEL;                           // scrolling mode, 1 pixel spacing
  displayString[1] = '\0';                                      // terminate string
  strcat(displayString, desc);                                  // add the description
  if (displayString[1] != '\0') {                               // if description not empty
    strcat(displayString, ":");                                 // then add ':'
  }
  if ((pm10 > -1000)&&(pm25 > -1000)) {                         // ensure PM values OK
    //
    if ((temperature > -1000)&&(humidity > -1000)) {            // ensure temperature & humidity values OK
      strcat(displayString, messageText[STRING_THERMO]);        // add temperature sign
      if (temperature < 0) {                                    // if value below zero
        sprintf(workString, "%d", ((int)(temperature-0.5f)));   // round down
      } else {
        sprintf(workString, "%d", ((int)(temperature+0.5f)));   // else round up
      } 
      strcat(displayString, workString);                        // incorporate measured value
      strcat(displayString, messageText[STRING_DEGREES]);       // add degrees Celsius message
      //
      strcat(displayString, messageText[STRING_DROPLET]);       // add droplet sign
      sprintf(workString, "%d", ((int)(humidity+0.5f)));  
      strcat(displayString, workString);                        // incorporate measured value
      strcat(displayString, "%");                               // add percent message
    }  
    //
    strcat(displayString, messageText[STRING_PM10]);            // add PM10 message
    sprintf(workString, "%d", ((int)(pm10+0.5f)));
    strcat(displayString, workString);                          // incorporate measured value
    strcat(displayString, messageText[STRING_UGRAM3]);          // final µg/m³ message
    //
    strcat(displayString, messageText[STRING_PM25]);            // add PM2,5 message
    sprintf(workString, "%d", ((int)(pm25+0.5f)));
    strcat(displayString, workString);                          // incorporate measured value
    strcat(displayString, messageText[STRING_UGRAM3]);          // add final µg/m³ message
    sprintf(message[msgLine], "%s", (displayString));           // add constructed line to message buffer
    //
    // Set memory message time-out
    messageValid[msgLine] = MSGLINE_TIMEOUT;                    // start message line time-out
    //
  } else {
    if (messageValid[msgLine]) {
      // PM values are missing & message is valid; hold the previous message on display for a certain time.
      messageValid[msgLine]--;
    } else {
      // PM values are missing & no previous message available, or time-out.
      strcat(displayString, messageText[ERRORNODATA]);          // add error no data
      sprintf(message[msgLine], "%s", (displayString));         // add constructed line to message buffer
      //
      repeatCount = 1;                                          // no long display loops please, try to read data again
    }
  }
}

void buildMessageValue(uint8_t msgLine, uint8_t dataSel, float valueToShow)
// Build message with value in message buffer
// Parameters:
//   msgLine:    Line number  in display buffer, where to put the constructed message.
//   dataSel:    OUT_PM10:    Outdoor PM10 value to be selected for SHOW_VALUE
//               OUT_PM25:    Outdoor PM2.5 value to be selected for SHOW_VALUE
//               OUT_TEMP:    Outdoor temperature value to be selected for SHOW_VALUE
//               OUT_HUMI:    Outdoor humidity value to be selected for SHOW_VALUE
//               IN_PM10:     Indoor PM10 value to be selected for SHOW_VALUE
//               IN_PM25:     Indoor PM2.5 value to be selected for SHOW_VALUE
//   valueToShow:Value to show
{
  if (valueToShow > -1000.0) {                                  // if value not OK, don't touch message buffer (previous message preserved!)
    //
    displayString[0] = ' ';                                     // mark result empty
    displayString[1] = '\0';                                    // terminate string
    //      
    switch(dataSel) {
      case OUT_PM10: {
          displayString[0] = FIXED_ONEPIXEL;                    // fixed mode, 1 pixel spacing
          displayString[1] = '\0';                              // terminate string
          strcat(displayString, messageText[STRING_PM10_EQ]);   // add "PM10 = " string
          sprintf(workString, "%d", ((int)(pm10+0.5f)));        // prepare value
          strcat(displayString, workString);                    // incorporate value
          strcat(displayString, messageText[STRING_UGRAM3]);    // add final µg/m³ message
          break;
        }
      case OUT_PM25: {
          displayString[0] = FIXED_ONEPIXEL;                    // fixed mode, 1 pixel spacing
          displayString[1] = '\0';                              // terminate string
          strcat(displayString, messageText[STRING_PM25_EQ]);   // add "PM2,5 = " string
          sprintf(workString, "%d", ((int)(pm25+0.5f)));        // prepare value
          strcat(displayString, workString);                    // incorporate value
          strcat(displayString, messageText[STRING_UGRAM3]);    // add final µg/m³ message
          break;
        }
      case OUT_TEMP: {
          displayString[0] = FIXED_ONEPIXEL;                    // fixed mode, 1 pixel spacing
          displayString[1] = '\0';                              // terminate string
          strcat(displayString, messageText[STRING_TEMP_EQ]);   // add "Temp = " string
          if (temperature < 0) {                                  // if value below zero
            sprintf(workString, "%d", ((int)(temperature-0.5f))); // round down
          } else {
            sprintf(workString, "%d", ((int)(temperature+0.5f))); // else round up
          }
          strcat(displayString, workString);                    // incorporate value
          strcat(displayString, messageText[STRING_DEGREES]);   // add degrees celsius
          break;
        }
      case OUT_HUMI: {
          displayString[0] = FIXED_ONEPIXEL;                    // fixed mode, 1 pixel spacing
          displayString[1] = '\0';                              // terminate string
          strcat(displayString, messageText[STRING_VOCHT_EQ]);  // add "Vocht = " string
          sprintf(workString, "%d", ((int)(humidity+0.5f)));    // prepare value
          strcat(displayString, workString);                    // incorporate value
          strcat(displayString, "%");                           // add percent
          break;
        }
      case IN_PM10: {
          displayString[0] = FIXED_ONEPIXEL;                    // fixed mode, 1 pixel spacing
          displayString[1] = '\0';                              // terminate string
          strcat(displayString, messageText[STRING_PM10_EQ]);   // add "PM10 = " string
          sprintf(workString, "%d", ((int)(indoorPm10+0.5f)));  // prepare value
          strcat(displayString, workString);                    // incorporate value
          strcat(displayString, messageText[STRING_UGRAM3]);    // add final µg/m³ message
          break;
        }
      case IN_PM25: {
          displayString[0] = FIXED_ONEPIXEL;                    // fixed mode, 1 pixel spacing
          displayString[1] = '\0';                              // terminate string
          strcat(displayString, messageText[STRING_PM25_EQ]);   // add "PM2,5 = " string
          sprintf(workString, "%d", ((int)(indoorPm25+0.5f)));  // prepare value
          strcat(displayString, workString);                    // incorporate value
          strcat(displayString, messageText[STRING_UGRAM3]);    // add final µg/m³ message
          break;
        }
      default: 
        break;
    }
    sprintf(message[msgLine], "%s", (displayString));           // add constructed line to message buffer
  }
}

void buildGraphDisplayStr(float valueToShow, uint8_t maxVal)
// Construct string containing bargraph
// Don't show bargraph if value not OK.
{
  displayString[0] = ' ';                                       // mark result empty
  displayString[1] = '\0';                                      // terminate string

  if (valueToShow > -1000) {                                    // test if value OK
    uint8_t dotsAvailable = 8 * NUMBER_DISPLAYS;                // total available dots till end of display
    uint8_t dotScale10;                                         // dots to fill scale 0 to 10
    uint8_t dotScale100;                                        // dots to fill scale 0 to 100
    uint8_t dotsNeeded;                                         // dots needed to show value
    uint8_t dotsTemp;                                           // dots temperature value
    uint8_t white;                                              // counter for "white" bar
    uint8_t black;                                              // counter for "black" bar
    uint8_t scaleCount;                                         // scale counter
    uint8_t scaleMark;                                          // scale mark counter
    bool overTheTop = false;                                    // data bigger than display
    bool topDrawn = false;                                      // top drawn flag

    if (valueToShow < 0) {                                      // negative values show 0
      valueToShow = 0;
    }
    if (valueToShow > (1.2 * maxVal)) {                         // limit to maximum++ to avoid overflow
      valueToShow = (1.2 * maxVal);
    }
    // start building graph line
    // set format & bolleke
    m = 0;
    displayString[m++] = FIXED_NOPIXEL;                         // fixed mode, no pixel spacing
    displayString[m++] = BAR_BOL;                               // bolleke
    displayString[m++] = BAR_WIDTH_1;                           // 1 pixel
    dotsAvailable -= 9;                                         // adjust dotsAvailable (9 less: bolleke+1 pixel)
    dotsAvailable -= 2;                                         // adjust dotsAvailable (2 less: 1 x double BAR_SCALE)
    dotsAvailable -= 2;                                         // adjust dotsAvailable (2 less: 2 x 1/2 double BAR_SCALE)

    dotScale10 = (dotsAvailable/10);                            // calculate dots to represent scale step of 10%
    dotScale100 = (dotScale10*10);                              // calculate dots to represent scale 0 to 100

    dotsTemp = (valueToShow+0.5f);                              // round & convert to int
    dotsNeeded = ((dotsTemp*dotScale100)/maxVal);               // calculate dots to show value

    // check for overflow
    if (dotsNeeded > dotsAvailable) {
      dotsNeeded = dotsAvailable;
      overTheTop = true;
    }
    scaleMark = 11;                                             // 11 scale marks
    while (scaleMark--) {

      // draw full / half scale
      switch (scaleMark) {
        case 0: 
          // fall through
        case 5:                                                 // half scale
          if (dotsNeeded) dotsNeeded--;
          // fall through
        case 10:                                                // begin scale
          displayString[m++] = BAR_SCALE;
          displayString[m++] = BAR_SCALE;
          if (dotsAvailable) dotsAvailable--;
          if (dotsAvailable) dotsAvailable--;
          break;
        default:                                                // all other places
          displayString[m++] = BAR_HALF_SCALE; 
          if (dotsAvailable) dotsAvailable--;
          if (dotsNeeded) dotsNeeded--;
          break;
      }
      // draw "white" dots when value not yet reached, else draw "black" dots
      white = 0; 
      black = 0; 
      scaleCount = (dotScale10-1);
      
      while ((dotsAvailable)&&(scaleCount)) {
        if (dotsAvailable) dotsAvailable--;
        if (scaleCount) scaleCount--;
        if (dotsNeeded) {
          dotsNeeded--;
          white++;
        } else {
          black++;
        }  
      }
      if (white > 8) {
        displayString[m++] = BAR_WIDTH_7;
        displayString[m++] = BAR_WIDTH_1;
        white -= 8;
      }
      switch (white) {
        case 0:
          break;
        case 1:
          displayString[m++] = BAR_WIDTH_1;
          break;
        case 2:
          displayString[m++] = BAR_WIDTH_1;
          displayString[m++] = BAR_WIDTH_1;
          break;
        case 3:
          displayString[m++] = BAR_WIDTH_1;
          displayString[m++] = BAR_WIDTH_1;
          displayString[m++] = BAR_WIDTH_1;
          break;
        case 4:
          displayString[m++] = BAR_WIDTH_1;
          displayString[m++] = BAR_WIDTH_1;
          displayString[m++] = BAR_WIDTH_1;
          displayString[m++] = BAR_WIDTH_1;
          break;
        case 5:
          displayString[m++] = BAR_WIDTH_2;
          displayString[m++] = BAR_WIDTH_1;
          displayString[m++] = BAR_WIDTH_1;
          displayString[m++] = BAR_WIDTH_1;
          break;
        case 6:
          displayString[m++] = BAR_WIDTH_3;
          displayString[m++] = BAR_WIDTH_1;
          displayString[m++] = BAR_WIDTH_1;
          displayString[m++] = BAR_WIDTH_1;
          break;
        case 7:
          displayString[m++] = BAR_WIDTH_4;
          displayString[m++] = BAR_WIDTH_1;
          displayString[m++] = BAR_WIDTH_1;
          displayString[m++] = BAR_WIDTH_1;
          break;
        case 8:
          displayString[m++] = BAR_WIDTH_5;
          displayString[m++] = BAR_WIDTH_1;
          displayString[m++] = BAR_WIDTH_1;
          displayString[m++] = BAR_WIDTH_1;
          break;
        default:
          break;
      }
      if (!dotsNeeded) {
        if (topDrawn == false) {
          topDrawn = true;
          if ((displayString[m-1] != BAR_SCALE)&&(displayString[m-1] != BAR_HALF_SCALE)) {

            // generate rounded top (from 0 to 100)
            displayString[m-1] = BAR_TOP;
          }
        }
      }
      if (black > 8) {
        displayString[m++] = BAR_BLANK_7;
        displayString[m++] = BAR_BLANK_1;
        black -= 8;
      }
      switch(black) {
        case 0:
          break;
        case 1:
          displayString[m++] = BAR_BLANK_1; 
          break;
        case 2:
          displayString[m++] = BAR_BLANK_1;
          displayString[m++] = BAR_BLANK_1;
          break;
        case 3:
          displayString[m++] = BAR_BLANK_1;
          displayString[m++] = BAR_BLANK_1;
          displayString[m++] = BAR_BLANK_1;
          break;
        case 4:
          displayString[m++] = BAR_BLANK_1;
          displayString[m++] = BAR_BLANK_1;
          displayString[m++] = BAR_BLANK_1;
          displayString[m++] = BAR_BLANK_1;
          break;
        case 5:
          displayString[m++] = BAR_BLANK_2;
          displayString[m++] = BAR_BLANK_1;
          displayString[m++] = BAR_BLANK_1;
          displayString[m++] = BAR_BLANK_1;
          break;
        case 6:
          displayString[m++] = BAR_BLANK_3;
          displayString[m++] = BAR_BLANK_1;
          displayString[m++] = BAR_BLANK_1;
          displayString[m++] = BAR_BLANK_1;
          break;
        case 7:
          displayString[m++] = BAR_BLANK_4;
          displayString[m++] = BAR_BLANK_1;
          displayString[m++] = BAR_BLANK_1;
          displayString[m++] = BAR_BLANK_1;
          break;
        case 8:
          displayString[m++] = BAR_BLANK_5;
          displayString[m++] = BAR_BLANK_1;
          displayString[m++] = BAR_BLANK_1;
          displayString[m++] = BAR_BLANK_1;
          break;
        default:
          break;
      }
    }
    // over 100%
    if (dotsNeeded > 8) {
      dotsNeeded -= 8;
      displayString[m++] = BAR_WIDTH_5;
      displayString[m++] = BAR_WIDTH_1;
      displayString[m++] = BAR_WIDTH_1;
      displayString[m++] = BAR_WIDTH_1;
    }
    switch(dotsNeeded) {
      case 0:
        break;
      case 1:
        displayString[m++] = BAR_WIDTH_1;
        break;
      case 2:
        displayString[m++] = BAR_WIDTH_1;
        displayString[m++] = BAR_WIDTH_1;
        break;
      case 3:
        displayString[m++] = BAR_WIDTH_1;
        displayString[m++] = BAR_WIDTH_1;
        displayString[m++] = BAR_WIDTH_1;
        break;
      case 4:
        displayString[m++] = BAR_WIDTH_1;
        displayString[m++] = BAR_WIDTH_1;
        displayString[m++] = BAR_WIDTH_1;
        displayString[m++] = BAR_WIDTH_1;
        break;
      case 5:
        displayString[m++] = BAR_WIDTH_2;
        displayString[m++] = BAR_WIDTH_1;
        displayString[m++] = BAR_WIDTH_1;
        displayString[m++] = BAR_WIDTH_1;
        break;
      case 6:
        displayString[m++] = BAR_WIDTH_3;
        displayString[m++] = BAR_WIDTH_1;
        displayString[m++] = BAR_WIDTH_1;
        displayString[m++] = BAR_WIDTH_1;
        break;
      case 7:
        displayString[m++] = BAR_WIDTH_4;
        displayString[m++] = BAR_WIDTH_1;
        displayString[m++] = BAR_WIDTH_1;
        displayString[m++] = BAR_WIDTH_1;
        break;
      case 8:
        displayString[m++] = BAR_WIDTH_5;
        displayString[m++] = BAR_WIDTH_1;
        displayString[m++] = BAR_WIDTH_1;
        displayString[m++] = BAR_WIDTH_1;
        break;
      default:
        break;
    }
    // last dots
    if (overTheTop) {
      
      // generate oblique cut
      topDrawn = true;
      displayString[m-3] = BAR_BREAK_3;
      displayString[m-2] = BAR_BREAK_2;
      displayString[m-1] = BAR_BREAK_1;
    }
    // terminate string
    displayString[m++] = '\0';
  }
}

void buildGraph(uint8_t msgLine, float valueToShow, uint8_t maxVal)
// build bargraph in message buffer
//
// Parameters:
//   msgLine:      linenumber in display buffer, when to put the graph on display.
//   valueToShow:  PM value to show in graphical form.
//   maxVal:       Value at full display (= 200%)    
{
  displayString[0] = ' ';                                       // mark result empty
  displayString[1] = '\0';                                      // terminate string

  if (valueToShow > -1000) {                                    // test if value OK
    buildGraphDisplayStr(valueToShow, maxVal);                  // build graph in display 
    sprintf(message[msgLine], "%s", (displayString));           // add constructed line to message buffer
    barMessage = msgLine;                                       // remember the line for rereading purposes
    //
    // Set memory message time-out
    messageValid[msgLine] = MSGLINE_TIMEOUT;                    // start message line time-out
  } else {
    if (messageValid[msgLine]) {
      // Value to show is missing & message is valid; hold that message on display for a certain time.
      messageValid[msgLine]--;
    } else {
      // Value to show is missing & no previous message available, or time-out.
      strcat(displayString, messageText[ERRORNODATA]);          // add error no data
      sprintf(message[msgLine], "%s", (displayString));         // add constructed line to message buffer
      //
      repeatCount = 1;                                          // no long display loops please, try to read data again
    }
  }  
}

void buildMax24(uint8_t msgLine, uint8_t dataSel, float valueToStore)
// Build scrolling maximum 24h value.
//
// Parameters:
//   msgLine:      linenumber in display buffer, when to put the maximum 24h value on display.
//   dataSel:      data selector
//   valueToStore: most recent measured PM value.
{
  displayString[0] = ' ';                                       // mark result empty
  displayString[1] = '\0';                                      // terminate string
  //  
  switch(dataSel) {
    case IN_PM10:
      // fall through
    case OUT_PM10: 
      displayString[0] = SCROLL_ONEPIXEL;                       // scrolling mode, 1 pixel spacing
      displayString[1] = '\0';                                  // terminate string
      strcat(displayString, messageText[STRING_MAX24]);         // show string "Maximum 24 uur waarde "
      strcat(displayString, messageText[STRING_PM10]);          // add "PM10:" string
      sprintf(workString, "%d", ((int)(pm10_Max24+0.5f)));      // prepare value
      strcat(displayString, workString);                        // incorporate value
      strcat(displayString, messageText[STRING_UGRAM3]);        // add final µg/m³ message  
      sprintf(message[msgLine], "%s", (displayString));         // add constructed line to message buffer
      break;
    case IN_PM25:
      // fall through  
    case OUT_PM25: 
      displayString[0] = SCROLL_ONEPIXEL;                       // scrolling mode, 1 pixel spacing
      displayString[1] = '\0';                                  // terminate string
      strcat(displayString, messageText[STRING_MAX24]);         // show string "Maximum 24 uur waarde "
      strcat(displayString, messageText[STRING_PM25]);          // add "PM2,5:" string
      sprintf(workString, "%d", ((int)(pm25_Max24+0.5f)));      // prepare value
      strcat(displayString, workString);                        // incorporate value
      strcat(displayString, messageText[STRING_UGRAM3]);        // add final µg/m³ message  
      sprintf(message[msgLine], "%s", (displayString));         // add constructed line to message buffer
      break;
    default: 
      break;
  } 
}

void buildCompare(uint8_t msgLine, float outdoorValue, float indoorValue)
// Construct scrolling comparison message describing the indoor versus outdoor PM values.
//
// Parameters:
//   msgLine:      linenumber in display buffer, where to put the compare result.
//   outdoorValue: measured outdoor PM value.
//   indoorValue:  measured indoor PM value.
{
  displayString[0] = ' ';                                       // mark result empty
  displayString[1] = '\0';                                      // terminate string

  if ((outdoorValue > -1000.0)&&(indoorValue > -1000.0)) {      // ensure indoor & outdoor values OK
    uint8_t pTable = 0;                                         // initialize pointers
    uint8_t pText = 0;
    resultFound = false;

    // result = compare indoor/outdoor in +/- percentage difference viewed from indoor
    compareResult = ((((outdoorValue+DAMPING)/(indoorValue+DAMPING))*100)-100);

    // loop trough table until condition is met, or table end is reached
    while (true) {
      if (pTable > ARRAY_SIZE(compareTable)) break;
      //
      if (compareTable[pTable] <= compareResult) {
        if (compareTable[pTable+1] > compareResult) { resultFound = true; break; }
      }
      pTable+=2; pText++;
    }  

    if (resultFound) {
      displayString[0] = SCROLL_ONEPIXEL;                       // scrolling mode, 1 pixel spacing
      displayString[1] = '\0';                                  // terminate string
      strcat(displayString, compareText[pText]);                // add the compare text
    } 
  }
  sprintf(message[msgLine], "%s", (displayString));             // add constructed line to message buffer
}

void buildPercent(uint8_t msgLine, float outdoorValue1, float outdoorValue2, int PMselect )
// Construct scrolling comparison message describing the difference in percent between outdoor 1 versus outdoor 2 PM values.
//
// Parameters:
//   msgLine:       linenumber in display buffer, where to put the compare result.
//   outdoorValue1: measured outdoor 1 PM value.
//   outdoorValue2: measured outdoor 2 PM value.
//   PMselect     : PM10/PM25 selector.
{
  displayString[0] = ' ';                                       // mark result empty
  displayString[1] = '\0';                                      // terminate string

  if ((outdoorValue1 > -1000.0)&&(outdoorValue2 > -1000.0)) {   // ensure outdoor values OK
    uint8_t pTable = 0;                                         // initialize pointers  
    uint8_t pText = 0;
    resultFound = false;
    //
    // result = compare outdoor 1/outdoor 2 in +/- percentage difference viewed from outdoor 1
    compareResult = (((outdoorValue1/outdoorValue2)*100)-100);
    if (compareResult < 0) {
      posCompareResult = (0 - compareResult);
    } else {
      posCompareResult = compareResult;
    }
    //
    displayString[0] = SCROLL_ONEPIXEL;                         // scrolling mode, 1 pixel spacing
    displayString[1] = '\0';                                    // terminate string
    //
    if (compareResult > 0) {
      strcat(displayString, messageText[PERCNTSTR0]);           // string "Er is " - meer
      sprintf(workString, "%d", ((int)(posCompareResult)));     // make compare result into string
      strcat(displayString, workString);                        // and add it
      strcat(displayString, messageText[PERCNTSTR2]);           // string " meer "
    } else {
      strcat(displayString, messageText[PERCNTSTR1]);           // string "Er is " - minder
      sprintf(workString, "%d", ((int)(posCompareResult)));     // make compare result into string
      strcat(displayString, workString);                        // and add it
      strcat(displayString, messageText[PERCNTSTR3]);           // string " minder "
    }
    switch (PMselect) {
      case OUT_PM10:
        // fall through
      case IN_PM10:
        strcat(displayString, "PM10");                          // string "PM10"
        break;
      case OUT_PM25:  
        // fall through
      case IN_PM25: 
        strcat(displayString, "PM2,5");                         // string "PM2,5"
        break;  
    }
    strcat(displayString, messageText[PERCNTSTR5]);             // string " fijnstof bij meter "
    //  
    strcat(displayString, outdoorName);                         // add sensor 1 name
    strcat(displayString, messageText[PERCNTSTR4]);             // string " dan bij meter "
    //
    strcat(displayString, indoorName);                          // add sensor 2 name
  }
  sprintf(message[msgLine], "%s", (displayString));             // add constructed line to message buffer
}

void buildAQIstring(uint8_t msgLine, float outdoorValue10, float outdoorValue25)
// Construct scrolling AQI message describing the outdoor PM air quality.
//
// Parameters:
//   msgLine:        linenumber in display buffer, where to put the advice result.
//   outdoorValue10: measured PM10 value.
//   outdoorValue25: measured PM2.5 value.
{
  float aqi10 = ((outdoorValue10 * 50) / AQI10_UG);
  float aqi25 = ((outdoorValue25 * 50) / AQI25_UG);
  //
  float aqiValue = aqi25;
  
  if (aqi10 > aqi25) {
     aqiValue = aqi10;
  }
     
  displayString[0] = ' ';                                       // mark result empty
  displayString[1] = '\0';                                      // terminate string

  if (aqiValue > -100.0) {                                           // ensure value OK
    uint8_t pTable = 0;                                         // initialize pointers  
    uint8_t pText = 0;
    resultFound = false;

    // loop trough table until condition is met, or table end is reached
    while (true) {
      if (pTable > ARRAY_SIZE(AQItable)) break;
      //
      if (AQItable[pTable] <= aqiValue) {
        if (AQItable[pTable+1] > aqiValue) { resultFound = true; break; }
      }
      pTable+=2; pText++;
    }  

    if (resultFound) {
      //
      displayString[0] = SCROLL_ONEPIXEL;                       // scrolling mode, 1 pixel spacing
      displayString[1] = '\0';                                  // terminate string
      strcat(displayString, AQItext[pText]);                    // add the advice text
    }  
  }
  sprintf(message[msgLine], "%s", (displayString));             // add constructed line to message buffer
}

void buildTime(uint8_t msgLine)
// Build date & time message
{
  displayString[0] = '\0';                                      // terminate string
  if (WiFi.status() == WL_CONNECTED) { 
    displayString[0] = FIXED_ONEPIXEL_T;                        // fixed left justified, 1 pixel spacing, update time !
    displayString[1] = '\0';                                    // terminate string
    sprintf(workString, "%02d/%02d/%4d", dayOfMonthNow, monthNow, yearNow);  // format date 
    strcat(displayString, workString);                          // add date
    strcat(displayString, "   ");                               // some space
    sprintf(workString, "%02d:%02d:%02d", hoursNow, minutesNow, secondsNow); // format time
    strcat(displayString, workString);                          // add time
    sprintf(message[msgLine], "%s", (displayString));           // add constructed line to message buffer
  }
}

void buildOneMessage(uint8_t msgLine, char* desc, uint8_t alfaGraph, uint8_t dataSel, char* sds011api, char* dht22api)
// Build string for the display buffer, according to specifications in parameters.
// Copy that string to the display buffer, at the wanted location.
// Parameters:
//   msgLine:    Line number in display buffer, where to put the constructed message.
//   desc:       Description message (used in SHOW_ALPHA)
//   alfaGraph:  SHOW_ALPHA:  Read database on German server, and construct a scrolling message containing all results.
//               SHOW_VALUE:  Construct a non-scrolling message showing the value, selected with dataSel.
//               SHOW_GRAPH:  Construct a non-scrolling bargraph showing the value, selected with dataSel.
//               SHOW_COMPAR: Construct scrolling comparison message comparing indoor versus outdoor PM values.
//               SHOW_PERCNT: Construct scrolling comparison message of percentage difference outdoor 1 versus outdoor 2 PM values.
//               SHOW_ADVICE: Construct scrolling advice message describing the outdoor PM air quality.
//               SHOW_MAX24:  Construct scrolling message showing the maximum value in 24h.
//               SHOW_TIME:   Construct message showing actual time.
//   dataSel:    OUT_PM10:    Outdoor PM10 value to be selected for SHOW_VALUE, SHOW_GRAPH, SHOW_MAX24, SHOW_COMPAR & SHOW_ADVICE.
//               OUT_PM25:    Outdoor PM2.5 value to be selected for SHOW_VALUE, SHOW_GRAPH, SHOW_MAX24, SHOW_COMPAR & SHOW_ADVICE.
//               OUT_TEMP:    Outdoor temperature value to be selected for SHOW_VALUE & SHOW_GRAPH.
//               OUT_HUMI:    Outdoor humidity value to be selected for SHOW_VALUE & SHOW_GRAPH & SHOW_MAX.
//               IN_PM10:     Indoor PM10 value to be selected for SHOW_VALUE & SHOW_GRAPH & SHOW_MAX24.
//               IN_PM25:     Indoor PM2.5 value to be selected for SHOW_VALUE & SHOW_GRAPH & SHOW_MAX24.
//   sds011api:  The number part of the API-ID of the SDS011 sensor.
//   dht22api:   The number part of the API-ID of the DHT22 sensor.
{
  float valueToShow;  
  uint8_t maxVal = 0;
  //
  switch(alfaGraph) {
    case SHOW_ALPHA:
      // Construct sds011 & dht22 url's    
      strcpy(sds011url, SENSORSERVER_URL); strcat(sds011url, sds011api); strcat(sds011url, "/");
      strcpy(dht22url, SENSORSERVER_URL); strcat(dht22url, dht22api); strcat(dht22url, "/");

      // Read data from server
      readRemote(sds011url, dht22url);

      // Build message for display
      buildTotalMessage(msgLine, desc);

      // Route measured values to outdoor/indoor variables
      switch(dataSel) {
        case IN_PM10:
          // fall trough
        case IN_PM25:
          // Save indoor values
          indoorPm10 = pm10;
          indoorPm25 = pm25;
          indoorTemperature = temperature;
          indoorHumidity = humidity;
          strcpy(indoorName, desc);
          break;
        default:
          // Save outdoor values
          outdoorPm10 = pm10;
          outdoorPm25 = pm25;
          outdoorTemperature = temperature;
          outdoorHumidity = humidity; 
          strcpy(outdoorName, desc);
          break;
      }
      break;
      
    case SHOW_VALUE:
      // Select value to show
      switch(dataSel) {
        case OUT_PM10:
          valueToShow = outdoorPm10; 
          break;
        case OUT_PM25:
          valueToShow = outdoorPm25; 
          break;
        case OUT_TEMP:
          valueToShow = outdoorTemperature; 
          break;
        case OUT_HUMI:
          valueToShow = outdoorHumidity; 
          break;
        case IN_PM10:
          valueToShow = indoorPm10; 
          break;
        case IN_PM25:
          valueToShow = indoorPm25; 
          break;
        default:
          valueToShow = -1000.0;
          break;
      }
      // Build message for display
      if (valueToShow > -1000) {
        buildMessageValue(msgLine, dataSel, valueToShow); 
      }  
      break;

    case SHOW_GRAPH:
      // Select value to show
      switch(dataSel) {
        case OUT_PM10:
          valueToShow = outdoorPm10;
          maxVal = MXV_PM10;
          break;
        case OUT_PM25:
          valueToShow = outdoorPm25;
          maxVal = MXV_PM25;
          break;
        case OUT_TEMP:
          valueToShow = outdoorTemperature;
          maxVal = 50;
          break;
        case OUT_HUMI:
          valueToShow = outdoorHumidity;
          maxVal = 100;
          break;
        case IN_PM10:
          valueToShow = indoorPm10;
          maxVal = MXV_PM10;
          break;
        case IN_PM25:
          valueToShow = indoorPm25;
          maxVal = MXV_PM25;
          break;
        default:
          valueToShow = -1000.0;
          maxVal = 100;
          break;
      }
      // Build message for display
      buildGraph(msgLine, valueToShow, maxVal);
      break;

    case SHOW_COMPAR:
      // Select value to control
      switch(dataSel) {
        case OUT_PM10:
          // fall trough
        case IN_PM10:
          // Build messages for display based on PM10
          buildCompare(msgLine, outdoorPm10, indoorPm10);
          break;
        default:
          // Build messages for display based on PM2,5
          buildCompare(msgLine, outdoorPm25, indoorPm25);
          break;
      }
      break;

    case SHOW_PERCNT:
      // Select value to control
      switch(dataSel) {
        case OUT_PM10:
          // fall trough
        case IN_PM10:
          // Build messages for display based on PM10
          buildPercent(msgLine, outdoorPm10, indoorPm10, OUT_PM10);
          break;
        default:
          // Build messages for display based on PM2,5
          buildPercent(msgLine, outdoorPm25, indoorPm25, OUT_PM25);
          break;
      }
      break;
      
    case SHOW_ADVICE:
      // Select value to control
      switch(dataSel) {
        case OUT_PM10:
          // fall trough
        case IN_PM10:
          // Build messages for display based on PM10
          buildAQIstring(msgLine, outdoorPm10, outdoorPm10);
          break;
        case PM10_PM25:
          // Build messages for display based on which of PM10 & PM2,5 combined has the greatest effect
          buildAQIstring(msgLine, outdoorPm10, outdoorPm25);
          break;
        default:
          // Build messages for display based on PM2,5
          buildAQIstring(msgLine, outdoorPm25, outdoorPm25);
          break;
      }
      break;

    case SHOW_MAX24:
      // Select value to control
      switch(dataSel) {
        case OUT_PM10:
          // fall through
        case IN_PM10:
          // Build messages for display based on PM10
          buildMax24(msgLine, dataSel, outdoorPm10);
          break;
        case OUT_PM25:
          // fall through
        case IN_PM25:  
          // Build messages for display based on PM2,5
          buildMax24(msgLine, dataSel, outdoorPm25);
          break;
        default:
          break;  
      }
      break;

    case SHOW_TIME:
      // Build time & date message for display
      buildTime(msgLine);
      break;
      
    default:
      break;
  }
}

void readAndBuild()
// Read all sensors & put result in messagebuffer.
//
// The first line should be in "SHOW_ALPHA" mode, as this will trigger the dataread on the server in Germany.
// Any subsequent lines will use the data previously read.
// If you want to switch to another data sensor (like an interior sensor), feel free to insert a new "SHOW_ALPHA" mode line!
// Any following lines can then use the new sensor data.
// The "title text" for SHOW_ALPHA can be the API_SDS or API_DHT number, or a text (in "" quotes) describing the location of the sensor.
// Take away, or add "buildOneMessage" lines according to what you want to show on the display (see optional lines 5 -> 10)
// !! do not use calls with "destination line in message numbers" above 25. (or expand the messagebuffer!)
// Existing lines in the buffer, which are not referenced here, will not be overwritten, and will show up on the display.
// Format (with valid parameters):
//-------------------------------------------------------------------------------------------
// buildOneMessage |destination|title text |mode       |data shown|PM sensor   |Temp.sensor |
//-----------------|line in    |-----------|-----------|----------|------------|------------|
//                 |message    |           |SHOW_ALPHA |OUT_PM10  |API_SDS1    |API_DHT1    |
//                 |buffer     |           |SHOW_VALUE |OUT_PM25  |API_SDS2    |API_DHT2    |
//                 |-----------|           |SHOW_GRAPH |OUT_TEMP  |            |            |
//                 |           |           |SHOW_COMPAR|OUT_HUMI  |            |            |
//                 |           |           |SHOW_PERCNT|IN_PM10   |            |            |
//                 |           |           |SHOW_ADVICE|IN_PM25   |            |            |
//                 |           |           |SHOW_TIME  |PM10_PM25 |            |            |
//-------------------------------------------------------------------------------------------
{
  repeatCount = 1;                              // reset repeat counter 
  //                           
  #if INDOOR_2
    // Outdoor sensor 1 & indoor sensor 2.
    #define LOOPpoint  1                        // return point of loop: message 1
    #if SHORT
      buildOneMessage (1 ,""            ,SHOW_TIME  ,0         ,""          ,""         ); // Show date & time
      //
      buildOneMessage (2 ,SENSOR_1_NAME ,SHOW_ALPHA ,OUT_PM10  ,API_SDS_1   ,API_DHT_1  ); // Scrolling result line outdoor
      buildOneMessage (3 ,""            ,SHOW_GRAPH ,OUT_PM25  ,""          ,""         ); // PM2.5 outdoor bargraph
      //
      buildOneMessage (4 ,SENSOR_2_NAME ,SHOW_ALPHA ,IN_PM10   ,API_SDS_2   ,API_DHT_2  ); // Scrolling result line indoor
      buildOneMessage (5 ,""            ,SHOW_GRAPH ,IN_PM25   ,""          ,""         ); // PM2.5 indoor bargraph 
      //
      buildOneMessage (6 ,""            ,SHOW_COMPAR,OUT_PM25  ,""          ,""         ); // Show indoor / outdoor comparison message    
      //
      #if MAX_24h
        buildOneMessage (7 ,""          ,SHOW_MAX24 ,IN_PM25   ,""          ,""         ); // Show outdoor 24h maximum value PM2,5
      #endif
      //  
      #if AQI    
        buildOneMessage (8 ,""          ,SHOW_AQI    ,PM10_PM25 ,""          ,""         ); // Show WHO outdoor air advice
      #endif
    #else
      buildOneMessage (1 ,""            ,SHOW_TIME  ,0         ,""          ,""         ); // Show date & time
      //
      buildOneMessage (2 ,SENSOR_1_NAME ,SHOW_ALPHA ,OUT_PM10  ,API_SDS_1   ,API_DHT_1  ); // Scrolling result line outdoor
      buildOneMessage (3 ,""            ,SHOW_VALUE ,OUT_PM25  ,""          ,""         ); // PM2.5 outdoor value
      buildOneMessage (4 ,""            ,SHOW_GRAPH ,OUT_PM25  ,""          ,""         ); // PM2.5 outdoor bargraph
      buildOneMessage (5 ,""            ,SHOW_VALUE ,OUT_PM10  ,""          ,""         ); // PM10 outdoor value
      buildOneMessage (6 ,""            ,SHOW_GRAPH ,OUT_PM10  ,""          ,""         ); // PM10 outdoor bargraph
      //
      buildOneMessage (7 ,SENSOR_2_NAME ,SHOW_ALPHA ,IN_PM10   ,API_SDS_2   ,API_DHT_2  ); // Scrolling result line indoor
      buildOneMessage (8 ,""            ,SHOW_VALUE ,IN_PM25   ,""          ,""         ); // PM2.5 indoor value
      buildOneMessage (9 ,""            ,SHOW_GRAPH ,IN_PM25   ,""          ,""         ); // PM2.5 indoor bargraph
      buildOneMessage (10,""            ,SHOW_VALUE ,IN_PM10   ,""          ,""         ); // PM10 indoor value
      buildOneMessage (11,""            ,SHOW_GRAPH ,IN_PM10   ,""          ,""         ); // PM10 indoor bargraph      
      //
      buildOneMessage (12,""            ,SHOW_COMPAR,OUT_PM25  ,""          ,""         ); // Show indoor / outdoor comparison message
      //
      #if MAX_24h
        buildOneMessage (13,""          ,SHOW_MAX24 ,IN_PM10   ,""          ,""         ); // Show outdoor 24h maximum value PM10   
        buildOneMessage (14,""          ,SHOW_MAX24 ,IN_PM25   ,""          ,""         ); // Show outdoor 24h maximum value PM2,5  
      #endif  
      // 
      #if AQI       
        buildOneMessage (15,""          ,SHOW_ADVICE,PM10_PM25 ,""          ,""         ); // Show WHO outdoor air advice
      #endif
    #endif
  #else
    #if SENSOR_2
      // Outdoor sensors 1 & 2.
      #define LOOPpoint  1                                                                 // return point of loop: message 1
      #if SHORT
        buildOneMessage (1 ,""           ,SHOW_TIME  ,0         ,""         ,""         ); // Show date & time    
        //
        buildOneMessage (2 ,SENSOR_1_NAME,SHOW_ALPHA ,OUT_PM10  ,API_SDS_1  ,API_DHT_1  ); // Scrolling result line outdoor 1
        buildOneMessage (3 ,""           ,SHOW_GRAPH ,OUT_PM25  ,""         ,""         ); // PM2.5 outdoor 1 bargraph
        //
        buildOneMessage (4 ,SENSOR_2_NAME,SHOW_ALPHA ,IN_PM10   ,API_SDS_2  ,API_DHT_2  ); // Scrolling result line outdoor 2
        buildOneMessage (5 ,""           ,SHOW_GRAPH ,IN_PM25   ,""         ,""         ); // PM2.5 outdoor 2 bargraph
        //
        buildOneMessage (6 ,""           ,SHOW_PERCNT,OUT_PM25  ,""         ,""         ); // Show outdoor 1/2 percentage message PM2,5
        //
        #if MAX_24h
          buildOneMessage (7 ,""         ,SHOW_MAX24 ,IN_PM25   ,""         ,""         ); // Show outdoor 24h maximum value PM2,5   
        #endif
        //      
        #if AQI    
          buildOneMessage (8 ,""         ,SHOW_ADVICE,PM10_PM25 ,""         ,""         ); // Show WHO outdoor air advice
        #endif  
      #else
        buildOneMessage (1 ,""           ,SHOW_TIME  ,0         ,""         ,""         ); // Show date & time
        //
        buildOneMessage (2 ,SENSOR_1_NAME,SHOW_ALPHA ,OUT_PM10  ,API_SDS_1  ,API_DHT_1  ); // Scrolling result line outdoor 1
        buildOneMessage (3 ,""           ,SHOW_VALUE ,OUT_PM25  ,""         ,""         ); // PM2.5 outdoor 1 value
        buildOneMessage (4 ,""           ,SHOW_GRAPH ,OUT_PM25  ,""         ,""         ); // PM2.5 outdoor 1 bargraph
        buildOneMessage (5 ,""           ,SHOW_VALUE ,OUT_PM10  ,""         ,""         ); // PM10 outdoor 1 value
        buildOneMessage (6 ,""           ,SHOW_GRAPH ,OUT_PM10  ,""         ,""         ); // PM10 outdoor 1 bargraph
        //
        buildOneMessage (7 ,SENSOR_2_NAME,SHOW_ALPHA ,IN_PM10   ,API_SDS_2  ,API_DHT_2  ); // Scrolling result line outdoor 2
        buildOneMessage (8 ,""           ,SHOW_VALUE ,IN_PM25   ,""         ,""         ); // PM2.5 outdoor 2 value
        buildOneMessage (9 ,""           ,SHOW_GRAPH ,IN_PM25   ,""         ,""         ); // PM2.5 outdoor 2 bargraph
        buildOneMessage (10,""           ,SHOW_VALUE ,IN_PM10   ,""         ,""         ); // PM10 outdoor 2 value
        buildOneMessage (11,""           ,SHOW_GRAPH ,IN_PM10   ,""         ,""         ); // PM10 outdoor 2 bargraph
        //
        buildOneMessage (12,""           ,SHOW_PERCNT,IN_PM10   ,""         ,""         ); // Show outdoor 1 / 2 percentage message PM10
        buildOneMessage (13,""           ,SHOW_PERCNT,IN_PM25   ,""         ,""         ); // Show outdoor 1 / 2 percentage message PM2,5
        //
        #if MAX_24h
          buildOneMessage (14,""         ,SHOW_MAX24 ,IN_PM10   ,""         ,""         ); // Show outdoor 24h maximum value PM10   
          buildOneMessage (15,""         ,SHOW_MAX24 ,IN_PM25   ,""         ,""         ); // Show outdoor 24h maximum value PM2,5  
        #endif 
        // 
        #if AQI    
          buildOneMessage (16,""         ,SHOW_ADVICE,PM10_PM25 ,""         ,""         ); // Show WHO outdoor air advice
        #endif  
      #endif
    #else
      // Only outdoor sensor 1.
      #define LOOPpoint 1                                                                  // return point of loop: message 2
      #if SHORT
        buildOneMessage (1 ,""           ,SHOW_TIME  ,0         ,""         ,""         ); // Show date & time
        //
        buildOneMessage (2 ,SENSOR_1_NAME,SHOW_ALPHA ,OUT_PM10  ,API_SDS_1  ,API_DHT_1  ); // Scrolling result line outdoor
        buildOneMessage (3 ,""           ,SHOW_GRAPH ,OUT_PM25  ,""         ,""         ); // PM2.5 outdoor bargraph
        //
        #if MAX_24h
          buildOneMessage (4,""          ,SHOW_MAX24 ,IN_PM10   ,""         ,""         ); // Show outdoor 24h maximum value PM10   
          buildOneMessage (5,""          ,SHOW_MAX24 ,IN_PM25   ,""         ,""         ); // Show outdoor 24h maximum value PM2,5  
        #endif      
        //
        #if AQI    
          buildOneMessage (6 ,""         ,SHOW_ADVICE,PM10_PM25 ,""         ,""         ); // Show WHO outdoor air advice
        #endif  
      #else
        buildOneMessage (1 ,""           ,SHOW_TIME  ,0         ,""         ,""         ); // Show date & time
        //
        buildOneMessage (2 ,SENSOR_1_NAME,SHOW_ALPHA ,OUT_PM10  ,API_SDS_1  ,API_DHT_1  ); // Scrolling result line outdoor
        buildOneMessage (3 ,""           ,SHOW_VALUE ,OUT_PM25  ,""         ,""         ); // PM2.5 outdoor value
        buildOneMessage (4 ,""           ,SHOW_GRAPH ,OUT_PM25  ,""         ,""         ); // PM2.5 outdoor bargraph
        buildOneMessage (5 ,""           ,SHOW_VALUE ,OUT_PM10  ,""         ,""         ); // PM10 outdoor value
        buildOneMessage (6 ,""           ,SHOW_GRAPH ,OUT_PM10  ,""         ,""         ); // PM10 outdoor bargraph
        //
        #if MAX_24h
          buildOneMessage (7,""          ,SHOW_MAX24 ,IN_PM10   ,""         ,""         ); // Show outdoor 24h maximum value PM10   
          buildOneMessage (8,""          ,SHOW_MAX24 ,IN_PM25   ,""         ,""         ); // Show outdoor 24h maximum value PM2,5  
        #endif
        //
        #if AQI    
          buildOneMessage (9 ,""         ,SHOW_ADVICE,PM10_PM25 ,""         ,""         ); // Show WHO outdoor air advice
        #endif  
      #endif
    #endif
  #endif
}

void readMulti(void)
// Read all sensors in a multisensor environment
{
  // Prepare local & global variables
  uint8_t   loop = 0;                           
  char      sensorUrl[70];
  // 
  while (loop < MULTI_MAX) {
    // Construct PM sensor url    
    strcpy(sensorUrl, SENSORSERVER_URL); strcat(sensorUrl, multiSensor[loop]); strcat(sensorUrl, "/");
    //
    // Read data from server & save in array
    pm10 = -1000; pm25 = -1000;
    readRemote(sensorUrl, sensorUrl);
    multiPm10[loop] = pm10; 
    multiPm25[loop] = pm25;
    loop++;
  }
}

void buildFixedMessage(uint8_t messageLn, char* firstMessage, char* secondMessage)
// Build a fixed message in the message buffer for the multisensor environment 
// Parameters:
//   messageLn:     Line number in display buffer, where to put the constructed message. 
//   thisMessage:   The message to show.
{
  if (messageLn < MULTI_MAX) {                                  // prevent writing outside of buffer
    displayString[0] = FIXED_ONEPIXEL;                          // fixed mode, 1 pixel spacing
    displayString[1] = '\0';                                    // terminate string
    strcat(displayString, firstMessage);                        // add first message
    strcat(displayString, secondMessage);                       // add second message
    sprintf(message[messageLn], "%s", (displayString));         // add constructed line to message buffer
  }
} 

void buildScrollMessage(uint8_t messageLn, char* thisMessage, char* thisName, float pm10, float pm25)
// Build a scrolling message in the message buffer for the multisensor environment 
// Parameters:
//   messageLn:     Line number in display buffer, where to put the constructed message. 
//   thisMessage:   The begin text.
//   thisName:      The name text.
//   pm10:          PM10 value to show.
//   pm25:          PM2,5 value to show.      
{
  if (messageLn < MULTI_MAX) {                                  // prevent writing outside of buffer
    displayString[0] = SCROLL_ONEPIXEL;                         // scrolling mode, 1 pixel spacing
    displayString[1] = '\0';                                    // terminate string
    strcat(displayString, thisMessage);                         // add begin text
    strcat(displayString, thisName);                            // add name text
    strcat(displayString, messageText[STRING_PM10]);            // add "PM10 = " string
    sprintf(workString, "%d", ((int)(pm10+0.5f)));              // prepare value
    strcat(displayString, workString);                          // incorporate value
    strcat(displayString, messageText[STRING_UGRAM3]);          // add final µg/m³ message
    strcat(displayString, messageText[STRING_PM25]);            // add "PM2,5 = " string
    sprintf(workString, "%d", ((int)(pm25+0.5f)));              // prepare value
    strcat(displayString, workString);                          // incorporate value
    strcat(displayString, messageText[STRING_UGRAM3]);          // add final µg/m³ message
    sprintf(message[messageLn], "%s", (displayString));         // add constructed line to message buffer
  }
} 

void calculateMean()
// Calculate mean values over all sensors, to detect the deviating ones
{
  #if MULTI_EXCESS
    // Prepare local variables
    uint8_t   loop = 0;         // Loop counter
    uint8_t   count = 0;        // Number of active meters
    float     meanPm10 = 0;     // Mean result PM10
    float     meanPm25 = 0;     // Mean result PM2.5
    //
    while (loop < MULTI_MAX) {
      // Calculate number of active meters
      if ((multiPm10[loop] > 0) || (multiPm25[loop] > 0)) {
        count++;
      }
      // Calculate total sum
      if (multiPm10[loop] > 0) {
        meanPm10 += multiPm10[loop];
      }
      if (multiPm25[loop] > 0) {
        meanPm25 += multiPm25[loop];
      }
      //
      loop++;          
    }
    //
    if (count > 0) {
      // Calculate mean result
      meanPm10 = meanPm10 / count; 
      meanPm25 = meanPm25 / count; 
      // Calculate deviation maxima
      meanPm10Max = meanPm10 + ((meanPm10 * MULTI_DEVIATION) / 100);
      meanPm25Max = meanPm25 + ((meanPm25 * MULTI_DEVIATION) / 100);
      // Create message
      buildScrollMessage(multiLine++, messageText[STRING_MEAN], messageText[NULLSTR], meanPm10, meanPm25);
      //
      #if EXCESS_GRAPH
        // Build bargraph for display
        buildGraph(multiLine++, meanPm25, MXV_PM25);
      #endif
      //
      #if EXCESS_AQI    
        // Build AQI string for display
        buildAQIstring(multiLine++, meanPm10, meanPm25);
      #endif  
    } 
  #endif  
}

void calculateDeviation()
// Calculate deviation, and if too high, generate the appropriate messages
{
  // Prepare local variables
  uint8_t loop = 0;
  bool titleDone = false;
  //
  // Check for deviation
  while (loop < MULTI_MAX) {
    if ((multiPm10[loop] > meanPm10Max) || (multiPm25[loop] > meanPm25Max)) {
      #if SHORT
        // level exceeded, create short messages
        if (!titleDone) {
          buildFixedMessage(multiLine++, messageText[STRING_TEHOOG], "");
          titleDone = true;
        }
        buildFixedMessage(multiLine++, "- ", multiName[loop]);
      #else
        // level exceeded, create long message
        buildScrollMessage(multiLine++, messageText[STRING_TEHOOG], multiName[loop], multiPm10[loop], multiPm25[loop]);
        // Build bargraph for display
        buildGraph(multiLine++, multiPm25[loop], MXV_PM25);  
        #if MULTI_AQI
          // Build advice for display
          buildAQIstring(multiLine++, multiPm10[loop], multiPm25[loop]);
        #endif
      #endif  
    }  
    // Loop handling
    loop++;
  }  
}

void showNotConnected()
// Check if meters connected, and if not, generate the appropriate messages
{
  // Prepare local variables
  uint8_t loop = 0;
  bool titleDone = false;
  //
  // Check for connection
  while (loop < MULTI_MAX) {
    if ((multiPm10[loop] < 0) || (multiPm25[loop] < 0)) {
      // not connected, show it.
      if (!titleDone) {
        buildFixedMessage(multiLine++, messageText[STRING_NODATA], "");
        titleDone = true;
      }    
      buildFixedMessage(multiLine++, "- ", multiName[loop]);
    }
    // Loop handling
    loop++;
  } 
}

void eraseBufferTillEnd(uint8_t messageLn)
// Erase message buffer from this message on
// Parameters:
//   messageLn:      Line number in display buffer, start of erase operation. 
{
  // Prepare local variables
  uint8_t loop = messageLn;
  displayString[0] = ' ';                                  // mark result empty
  displayString[1] = '\0';                                 // terminate string
  while (loop < MULTI_MAX) {
    sprintf(message[loop++], "%s", (displayString));       // add empty line to message buffer
  }
}

void readAndBuildMulti()
// Read all sensors in a multisensor environment, do all processing & put result in messagebuffer.
{
  multiLine = 1;                      // leave welcome message @ first line
  readMulti();                        // read multiple sensors
  buildTime(multiLine++);             // show time
  calculateMean();                    // calculate mean value & make mean message
  calculateDeviation();               // calculate deviation & make messages if deviation too high
  #if MULTI_MISSING
    showNotConnected();               // show not connected meters
  #endif
  eraseBufferTillEnd(multiLine);      // erase left-over messages
}    

uint8_t utf8Ascii(uint8_t ascii)
// UTF8 to Extended ASCII conversion of text
//
// Convert a single Character from UTF8 to Extended ASCII according to ISO 8859-1,
// also called ISO Latin-1. Codes 128-159 contain the Microsoft Windows Latin-1
// extended characters:
// - codes 0..127 are identical in ASCII and UTF-8
// - codes 160..191 in ISO-8859-1 and Windows-1252 are two-byte characters in UTF-8
//                 + 0xC2 then second byte identical to the extended ASCII code.
// - codes 192..255 in ISO-8859-1 and Windows-1252 are two-byte characters in UTF-8
//                 + 0xC3 then second byte differs only in the first two bits to extended ASCII code.
// - codes 128..159 in Windows-1252 are different, but usually only the €-symbol will be needed from this range.
//                 + The euro symbol is 0x80 in Windows-1252, 0xa4 in ISO-8859-15, and 0xe2 0x82 0xac in UTF-8.
//
// Modified from original code at http://playground.arduino.cc/Main/Utf8ascii
// Extended ASCII encoding should match the characters at http://www.ascii-code.com/
//
// Return "0" if a byte has to be ignored.
{
  static uint8_t cPrev = '\0';
  uint8_t c = '\0';

  if (ascii < 0x7f) {                                      // Standard ASCII-set 0..0x7F, no conversion
    cPrev = '\0';
    c = ascii;
  } else {
    switch (cPrev) {                                       // Conversion depending on preceding UTF8-character
      case 0xC2:
        c = ascii;
        break;
      case 0xC3:
        c = ascii | 0xC0;
        break;
      case 0x82:
        if (ascii == 0xAC) c = 0x80;                       // Euro symbol special case
        break;
    }
    cPrev = ascii;                                         // save last char
  }
  return (c);
}

void setMaxima24h(float valueToStore, uint8_t dataSel)
// store actual valueToStore in array if it is greater than the previous value in this hour segment.
// and set up the maximum value of the array in pm10_Max24 & pm25_Max24.
// Parameters:
//   valueToStore: most recent measured PM value (float).
//   dataSel:      data selector
{
  uint16_t actualValue = int(valueToStore);
  //
  if (actualHour != hoursNow) { 
    actualHour = hoursNow;
    saveMax();
    pm25_Max[hoursNow] = 0;
    pm10_Max[hoursNow] = 0;
  }  

  switch (dataSel) {
    case IN_PM10:
      // fall through
    case OUT_PM10:
      // store actual value as maximum if greater than actual maximum.
      if (valueToStore > pm10_Max[hoursNow]) {
        pm10_Max[hoursNow] = valueToStore;
        saveMax();
      }
      // search in whole array for maximum.
      pm10_Max24 = 0;
      for (i = 0; i < 24; i++) {
        if (pm10_Max[i] > pm10_Max24) {
          pm10_Max24 = pm10_Max[i];
        }
      }  
      break;    
    case IN_PM25:
      // fall through  
    case OUT_PM25: 
      // store actual value as maximum if greater than actual maximum.
      if (valueToStore > pm25_Max[hoursNow]) {
        pm25_Max[hoursNow] = valueToStore;
        saveMax();
      }
      // search in whole array for maximum.
      pm25_Max24 = 0;
      for (i = 0; i < 24; i++) {
        if (pm25_Max[i] > pm25_Max24) {
          pm25_Max24 = pm25_Max[i];
        }
      }  
      break;
    default:
      break;           
  }
}

void saveMax()
// save max.data to FLASH EEPROM
{
  /*
  uint8_t addr = 0;
  for (i = 0; i < 24; i++) {
    addr += EEPROM.put(addr, pm10_Max[i]);
    addr += EEPROM.put(addr, pm25_Max[i]);
  }
  EEPROM.commit();
  */
}

void restoreMax()
// restore max.data from FLASH EEPROM
{
  /*
  uint8_t addr = 0;
  pm10_Max24 = 0;
  pm25_Max24 = 0;
  for (i = 0; i < 24; i++) {
    addr += EEPROM.get(addr, pm10_Max[i]);
    addr += EEPROM.get(addr, pm25_Max[i]);
    if (pm10_Max[i] > pm10_Max24) {
      pm10_Max24 = pm10_Max[i];
    }
    if (pm25_Max[i] > pm25_Max24) {
      pm25_Max24 = pm25_Max[i];
    }
  */
}

// Send HTML page on demand
void handle_OnConnect() 
{
  server.send(200, "text/html", sendHTML());
}

// Not found ?
void handle_NotFound() 
{
  server.send(404, "text/plain", "Not found");
}

void utf8Ascii(char* s)
// In place conversion UTF-8 string to Extended ASCII
// The extended ASCII string is always shorter.
{
  uint8_t c, k = 0;
  char *cp = s;
  while (*s != '\0') {
    c = utf8Ascii (*s++);
    if (c != '\0')
      *cp++ = c;
  }
  *cp = '\0';                                              // terminate the new string
}

void initWiFi()
// Init / start WiFi / connect to AP
{
  WiFi.mode(WIFI_STA);
  //
  // Setup connection to WiFi ("SSID", "password")
  WiFiMulti.addAP("OrangeFlybox_C8A0", "50120352");
  WiFiMulti.addAP("Android_Rik",       "kasumaikeb");
  WiFiMulti.addAP("Orange-a9bc2",      "R4bnKYF7");
  WiFiMulti.addAP("Orange-a9bc2_Ext",  "R4bnKYF7");
  WiFiMulti.addAP("HSBXL"),            "CLUBMATE2010";
  //
  WiFiMulti.run();                                         // Attempt to connect
  //
  while (WiFi.status() != WL_CONNECTED) {                  // Retry if not connected
    WiFiMulti.run();
    delay(500);                                            // Wait some time 
  }
}

void setup()
// setup program
{
  // Initialize serial library
  Serial.begin(115200);

  // Do one time in-place conversion of the strings to be displayed
  for (i = 0; i < NUMSTR; i++) {
    utf8Ascii(message[i]);
  }
  for (i = 0; i < ARRAY_SIZE(messageText); i++) {
    utf8Ascii(messageText[i]);
  }
  for (i = 0; i < ARRAY_SIZE(compareText); i++) {
    utf8Ascii(compareText[i]);
  }
  for (i = 0; i < ARRAY_SIZE(AQItext); i++) {
    utf8Ascii(AQItext[i]);
  }
  for (i = 0; i < ARRAY_SIZE(multiName); i++) {
    utf8Ascii(multiName[i]);
  }

  // initialize pm10_Max[25] & pm25_Max[25] arrays to zero
  for (i = 0; i < 24; i++) {
    pm10_Max[i] = 0;
    pm25_Max[i] = 0;
  }
    
  // Initialise the Parola library
  P.begin();
  P.setInvert(false);
  P.setPause(PAUSE_TIME);
  P.setFont(ExtASCII);
  P.setCharSpacing(1);

  // Show connecting to network, with version number...
  P.print(VERSION);

  // Initialize WiFi
  initWiFi();

  // Show reading data...
  P.print(messageText[READSERVER]); 

  // show IP on display
  sprintf(displayIP, "%s: %03d.%03d.%03d.%03d", "IP", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);
  P.print(displayIP); delay(PAUSE_TIME);

  // Setup server startup
  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
  server.begin();

  // Initialize EEPROM library & restore 
  /*
  EEPROM.begin(1024);
  */
  restoreMax(); 

  // NTP startup
  timeClient.begin();
  
  // update time
  updateTime();
  
  // read values from German server
  P.print(messageText[READSERVER]);                             // show "reading data"
  //
  #if MULTI_CONFIG  
    readAndBuildMulti();                                        // read & build for multiple sensors
  #else
    readAndBuild();                                             // normal read & build
  #endif  

  // clear display
  P.begin();

  // format welcome message for display
  messageSelect = 0; sprintf(forDisplay, "%s", (message[messageSelect]));

  // remove format character from first string
  // !! welcome message always scrolling, always spaced for chars, not for graphics !!
  i = 0; j = 1; while (forDisplay[i++] = forDisplay[j++]);

  // start display system, show welcome
  P.setFont(ExtASCII);
  P.displayText(forDisplay, PA_CENTER, DISPLAY_SPEED, PAUSE_TIME, PA_SCROLL_LEFT, PA_PRINT); 
}

void loop()
// loop main program
{
// update display
  if (P.displayAnimate()) {
    // update time
    updateTime();

    // skip to next message, loop if last one reached
    messageSelect = (++messageSelect)%(NUMSTR);

    // skip over empty messages
    while ((message[messageSelect][0]) == ' ') {
      messageSelect = (++messageSelect)%(NUMSTR);
    }
    // handle repeating messages
    if (!messageSelect) {
      if (repeatCount > 0) {
        repeatCount--;
        messageSelect = LOOPpoint;
      } else {
        // choose & prepare message for during reading data 
        if ((barMessage) && (messageValid[barMessage])) {
          // show bar graph with real or buffered data before time-out
          messageValid[barMessage]--;                           // decount message valid time-out         
          sprintf(forDisplay, "%s", (message[barMessage]));     // format message for display
          formatChar = forDisplay[0];                           // prepare format character
          
          // remove format character from string
          i = 0; j = 1; while (forDisplay[i++] = forDisplay[j++]); 
        } else {
          // show "READ SERVER"
          sprintf(forDisplay, "%s", (messageText[READSERVER])); 
          formatChar = FIXED_ONEPIXEL;                          // prepare format character
        }   
        P.setTextAlignment(PA_LEFT);                            // message aligned to the left    

        // set spacing according to format character
        switch(formatChar) {
          case SCROLL_NOPIXEL:
            // fall trough
          case FIXED_NOPIXEL:
            P.setCharSpacing(0);
            break;
          default:
            P.setCharSpacing(1);
            break;
        }   
        // show message during read data
        P.print(forDisplay); 

        // read data (again)
        #if MULTI_CONFIG  
          readAndBuildMulti();                                  // read & build for multiple sensors
        #else
          readAndBuild();                                       // normal read & build
        #endif  

        // clear display & reinitialize Parola library after P.print()
        P.begin(); 
        P.setSpeed(DISPLAY_SPEED); 
        P.setPause(PAUSE_TIME);
        P.setFont(ExtASCII);
      }
    }

    // Handle setup server access 
    server.handleClient();

    sprintf(forDisplay, "%s", (message[messageSelect]));        // format message for display
    formatChar = forDisplay[0];                                 // save format character  

    switch(formatChar) {
      case FIXED_ONEPIXEL_T:
        // rebuild time display
        updateTime(); buildTime(messageSelect);
        sprintf(forDisplay, "%s", (message[messageSelect]));    // reformat message for display 
        break;             
      default:
        break;            
    }

    // remove format character from string
    i = 0; j = 1; while (forDisplay[i++] = forDisplay[j++]);  

    // set spacing according to format character
    switch(formatChar) {
      case SCROLL_NOPIXEL:
        // fall trough
      case FIXED_NOPIXEL:
        P.setCharSpacing(0);
        break;
      default:
        P.setCharSpacing(1);
        break;
    }
    // set alignment & texteffect according to format character
    switch(formatChar) {
      case FIXED_NOPIXEL:
        // fall trough
      case FIXED_ONEPIXEL:
        // fall trough
      case FIXED_ONEPIXEL_T:
        P.setTextAlignment(PA_LEFT);
        P.setTextEffect(PA_PRINT, PA_PRINT);
        break;
      default:
        P.setTextAlignment(PA_CENTER);
        P.setTextEffect(PA_SCROLL_LEFT, PA_PRINT);
        break;
    }
    // start message
    P.setTextBuffer(forDisplay);
    P.displayReset();
  }
}
