#include <pgmspace.h> 

#define    INTL_LANG                              "EN"  
// 
const char INTL_SAVE_CONFIG[] PROGMEM =           "Save configuration";
const char INTL_SAVE_RESTART[] PROGMEM =          "Save configuration & Restart";
const char INTL_WRITECONFIG[] PROGMEM =           "Writing config files";
const char INTL_REWRITECONFIG[] PROGMEM =         "Rewriting config files";
const char INTL_CONFIG_WRITTEN[] PROGMEM =        "Config written";
const char INTL_WRITESUCCESS[] PROGMEM =          "Written successfully: ";
const char INTL_WRITEFAIL[] PROGMEM =             "Failed to open for writing: ";
const char INTL_READCONFIG[] PROGMEM =            "Reading config files";
const char INTL_OPENFAIL[] PROGMEM =              "Failed to open for reading: ";
const char INTL_READSUCCESS[] PROGMEM =           "Read successfully: ";
const char INTL_FORMATSPIFFS[] PROGMEM =          "New version detected, formatting SPIFFS";
const char INTL_JSONPARSING_ERR[] PROGMEM =       "Config Json parsing error: ";
const char INTL_MOUNT_FS[] PROGMEM =              "Mounting FS...";
const char INTL_FAILMOUNT_FS[] PROGMEM =          "Failed to mount FS";
const char INTL_READAVGNPEAK[] PROGMEM =          "Reading back average & peak values";
const char INTL_WRITEAVGNPEAK[] PROGMEM =         "Writing average & peak values";
const char INTL_VALREQ_AUTH[] PROGMEM =           "Validate request auth...";
const char INTL_AUTH_FAIL[] PROGMEM =             "Authentication failed";
const char INTL_ESP_RESTART[] PROGMEM =           "ESP Controlled Restart";
const char INTL_DISPLAY_IS_REBOOTING[] PROGMEM =  "Display is rebooting.";
const char INTL_NOT_REACHED[] PROGMEM =           "Should not have been reached !!!";
const char INTL_NOT_FOUND_FPSTR[] PROGMEM =       "Not found.";
const char INTL_SCANFAIL[] PROGMEM =              "WiFi scan failed. Treating as empty.";
const char INTL_START_WIFI_MAN[] PROGMEM =        "Starting WiFiManager";
const char INTL_PASSWORD_DP[] PROGMEM =           "Password: ";
const char INTL_SCANWIFI[] PROGMEM =              "Scan for WiFi networks...";
const char INTL_TXT_CONNECTING_TO[] PROGMEM =     "Connecting to ";
const char INTL_AP_PASSWORD[] PROGMEM =           "AP Password is: ";
const char INTL_TELRAAM_HEAP[] PROGMEM =          "TelRaam: not enough heap available.";
const char INTL_TELRAAM_SEGM[] PROGMEM =          "TelRaam segment = ";
const char INTL_TELRAAM_JSON_ERR[] PROGMEM =      "TelRaam Json parsing error: ";
const char INTL_HEAPCHANGE_FROM[] PROGMEM =       "Heap change from ";
const char INTL_HEAPCHANGE_TO[] PROGMEM =         " to ";
const char INTL_HEAPDIFF[] PROGMEM =              " Diff = ";
const char INTL_LOWHEAP_RESTART[] PROGMEM =       "Low heap detected, controlled restart.";
const char INTL_LOWHEAP_TELRAAM[] PROGMEM =       "Low heap time exceeded for Telraam, controlled restart.";
const char INTL_ENDOFLIST[] PROGMEM =             "End of location list reached, stopped reading sensors till time-out.";
const char INTL_RESUMEREAD[] PROGMEM =            "Resuming sensor read, time-out passed.";
const char INTL_ONDISPLAY[] PROGMEM =             "On display: ";
const char INTL_DISPLAYBUFF[] PROGMEM =           "======== Displaybuffer =========";
const char INTL_ENDOFBUFF[] PROGMEM =             "======== End of buffer =========";
const char INTL_SELFTEST_FAIL[] PROGMEM =         "Error: SELFTEST FAILED!";
const char INTL_QUAN_LOCATIONS[] PROGMEM =        "Quantity of defined locations: ";
const char INTL_CONNECT_TO[] PROGMEM =            "Connected to: ";
const char INTL_TIMEZONE[] PROGMEM =              "Timezone = ";
const char INTL_TIMEUTC[] PROGMEM =               "Timezone lookup failed, will use UTC!";
const char INTL_LOCAL_IP[] PROGMEM =              "Local IP: ";
const char INTL_ENDOF_SETUP[] PROGMEM =           "End of setup";
const char INTL_SCAN_NUM[] PROGMEM =              "Scan# ";
const char INTL_LOC_NAME[] PROGMEM =              " Location name: ";
const char INTL_SENSOR_URL[] PROGMEM =            "Sensor @URL: ";
const char INTL_PMPARSING_ERR[] PROGMEM =         "PM Json parsing error: ";
const char INTL_HTTPCODE_ERR[] PROGMEM =          "HTTP error code: ";
//
#define    INTL_AVG24H_PM25                       "Avg. 24h PM2,5: "
#define    INTL_AVG24H_PM10                       "Avg. 24h PM10: "
#define    INTL_PEAK24H_PM25                      "Peak 24h PM2,5: "
#define    INTL_PEAK24H_PM10                      "Peak 24h PM10: "
#define    INTL_QUANT_05UM                        "Quant. 0.5µm: "
#define    INTL_QUANT_1UM                         "Quant. 1µm: "
#define    INTL_QUANT_25UM                        "Quant. 2.5µm: "
#define    INTL_QUANT_4UM                         "Quant. 4µm: "
#define    INTL_QUANT_10UM                        "Quant. 10µm: "
#define    INTL_PART_SIZE                         "Particle size: "
#define    INTL_TEMPERATURE                       "Temperature: "
#define    INTL_HUMIDITY                          "Humidity: "
#define    INTL_AIR_PRESS                         "Air pressure: "
#define    INTL_VOC_INDEX                         "VOC index: "
#define    INTL_NOX_INDEX                         "NOx index: "
#define    INTL_PEDESTRIANS                       "Pedestrians: "
#define    INTL_PER_HOUR                          "/h";
#define    INTL_BIKES                             "Bikes: "
#define    INTL_CARS                              "Cars: "
#define    INTL_HEAVY                             "Heavy vehicles: "
#define    INTL_V85_SPEED                         "V85 Speed: "
#define    INTL_KM_PER_HOUR                       "km/h"
//
#define    INTL_DISPLAY                           "Sensor.Community Display"
#define    INTL_BACK_TO_HOME_PAGE                 "Back to home page"
#define    INTL_BACK_TO_HOME_PAGE_DISCARD         "Back to home page / Discard changes"
#define    INTL_CONFIGURATION_REALLY_DELETE       "You really want to delete the configuration?"
#define    INTL_DELETE                            "Delete"
#define    INTL_CANCEL                            "Cancel"
#define    INTL_REALLY_RESTART_DISPLAY            "You really want to restart the display?"
#define    INTL_RESTART                           "Restart"
#define    INTL_UPTIME                            "Display uptime: "
#define    INTL_READ_UPTO                         "Read up to location: "
#define    INTL_RESET_REASON                      "Previous reset reason: "
#define    INTL_FIRMWARE                          "Firmware: "
const char INTL_SIGNAL_STRENGTH[] PROGMEM =       "signal strength ";
const char INTL_SIGNAL_QUALITY[] PROGMEM =        "signal quality ";
const char INTL_ALERT[] PROGMEM =                 "Alerts";
#define    INTL_NUMBER_OF_CALLS                   "Number of calls"
#define    INTL_SENSOR                            "Sensor"
#define    INTL_VALUE                             "Value"
#define    INTL_NOT_MEASURED                      "-- "
#define    INTL_DELETED                           "Deleted" 
#define    INTL_CANNOT_BE_DELETED                 "Cannot be deleted"
#define    INTL_NOT_FOUND                         "Not found"
#define    INTL_REPORT_ISSUE                      "Report issue"
const char INTL_PM[] PROGMEM =                    "Choose PM for peak & average values...";
// 
#define    INTL_HOME                              "Home"
const char INTL_CURRENT_DATA[] PROGMEM =          "Current data";
const char INTL_CONFIGURATION[] PROGMEM =         "Configuration";
const char INTL_ADVANCED_SETTINGS[] PROGMEM =     "Advanced settings";
const char INTL_DELETE_CONFIG[] PROGMEM =         "Delete configuration";
const char INTL_RESTART_DISPLAY[] PROGMEM =       "Restart display";
// 
const char INTL_WIFI_SETTINGS[] PROGMEM =         "WiFi settings";
// 
const char INTL_FS_WIFI_NAME[] PROGMEM =          "Network name";
const char INTL_PASSWORD[] PROGMEM =              "Password";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM =    "Advanced settings (change only if you know what you are doing)";
//
const char INTL_BASICAUTH[] PROGMEM =             " Authentication";
const char INTL_USER[] PROGMEM =                  "User";
const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM =   "AP in configuration mode";
#define    INTL_LOADING_WIFI_NETWORKS             "Loading WiFi networks ..."
const char INTL_NO_NETWORKS[] PROGMEM =           "No WiFi network found";
const char INTL_NETWORKS_FOUND[] PROGMEM =        "WiFi networks found: ";
// 
#define    INTL_WIFI_CONNECTION_LOST              "Connection lost"
#define    INTL_WIFI_CONNECT_TO                   "Please connect to:"
#define    INTL_WIFI_SSID                         "SSID: "
#define    INTL_WIFI_WIFI                         "WiFi: " 
#define    INTL_CONFIG_BUSY                       "Config in progress"
#define    INTL_PLEASE_RESTART                    "Please restart"
// 
const char INTL_LOCATION_0_15[] PROGMEM =         "Location 0-15";
const char INTL_LOCATION_16_31[] PROGMEM =        "Location 16-31";
const char INTL_LOCATION_NAME[] PROGMEM =         "Location name";
const char INTL_SENSOR_API_1[] PROGMEM =          "API #1 (PM)";
const char INTL_SENSOR_API_2[] PROGMEM =          "API #2 (Temp/Hum)";
const char INTL_SENSOR_API_3[] PROGMEM =          "API #3 (DNMS)";
const char INTL_SENSOR_API_4[] PROGMEM =          "API #4 (NOx/VOC) (or Telraamsegment)";
// 
const char INTL_DISPLAY_SETTINGS[] PROGMEM =      "Display settings";
const char INTL_DISPLAY_OPTIONS[] PROGMEM =       "Display options";
const char INTL_MULTICOMPARE[] PROGMEM =          " Show only sensors with PM overvalues";
const char INTL_SENSORMISSING[] PROGMEM =         " Show inactive sensors";
const char INTL_SHOWPMPM[] PROGMEM =              " Show PM results";
const char INTL_SHOWPM1PM4[] PROGMEM =            " Show PM1 & PM4 values";
const char INTL_SHOWMETEO[] PROGMEM =             " Show meteo info";
const char INTL_SHOWGRAPH[] PROGMEM =             " Show graphics";
const char INTL_SHOWAQIADVICE[] PROGMEM =         " Show AQI advice";
const char INTL_SHOWWHOADVICE[] PROGMEM =         " Show WHO advice";
const char INTL_MULTIAVERAGE[] PROGMEM =          " Show average over all meters";
const char INTL_SHOWAVGNPEAK[] PROGMEM =          " Show 24h. average & peak";
const char INTL_SHOWCOMP[] =                      " Compare 2 sensors & show result";
const char INTL_SHOWCOMPINSIDE[] =                " Compare sensor #2 is indoor";
const char INTL_SHOWDNMS[] PROGMEM =              " Show DNMS data";
const char INTL_SHOWTELRAAM[] PROGMEM =           " Show TELRAAM data";
// 
const char INTL_SETTINGS[] PROGMEM =              "General settings";
const char INTL_VALUES_TEXT[] PROGMEM =           "Values and text";
const char INTL_WELCOME[] PROGMEM =               "Welcome message";
const char INTL_WELCOME2[] PROGMEM =              "Welcome 2 message (alternating)";
const char INTL_CLOCKSECONDS[] PROGMEM =          "Clock on display (default 10 sec) (0 = no clock)";
const char INTL_TIMEZONESTR[] PROGMEM =           "Timezone (see Timezone database on Wikipedia)";
const char INTL_DISPLAYSPEED[] PROGMEM =          "Display step time (default 25 msec)";
const char INTL_PAUSETIME[] PROGMEM =             "Display pause time (default 5 sec)";
const char INTL_WELCOMEINTERVAL[] PROGMEM =       "Welcome message interval (# cycles) (default 10)";
const char INTL_CALLINGINTERVAL[] PROGMEM =       "Data calling interval (default 6 min)";
const char INTL_DIFFERENCEPERCENT[] PROGMEM =     "Difference percentage before notification (default 15%)";
const char INTL_DIFFERENCELEVEL[] PROGMEM =       "Difference level before notification (default 2µg/m³)";
const char INTL_SENSORDATATIMEOUT[] PROGMEM =     "Sensor data timeout (# missed scans) (default 10)";
// 
const char INTL_DEBUG_SETTINGS[] PROGMEM =        "Debug settings";
const char INTL_DEBUGSHOWDATA[] PROGMEM =         " Show data";
const char INTL_DEBUGDISPLAY[] PROGMEM =          " Display"; 
const char INTL_DEBUGCOMMS[] PROGMEM =            " Communication";
const char INTL_DEBUGHEAP[] PROGMEM =             " Heap"; 
const char INTL_DEBUGJSON[] PROGMEM =             " Json";   
// 
const char INTL_PM_PARAMS[] PROGMEM =             "PM parameters";
const char INTL_URLSENSORCOMM[] PROGMEM =         "Sensor.Community API URL";
const char INTL_WHO_PM25_MAXIMUM[] PROGMEM =      "WHO PM2,5 maximum (default 5µg/m³)";
const char INTL_WHO_PM10_MAXIMUM[] PROGMEM =      "WHO PM10 maximum (default 15µg/m³)";
const char INTL_PM25_TO_AQI50[] PROGMEM =         "PM2.5 to AQI-50 conversion (default 9µg/m³)";
const char INTL_PM10_TO_AQI50[] PROGMEM =         "PM10 for AQI-50 conversion (default 50µg/m³)";
const char INTL_MAXGRAPH_PM25[] PROGMEM =         "PM2.5 value for 200% (full) graphic display (default 10µg/m³)";
const char INTL_MAXGRAPH_PM10[] PROGMEM =         "PM10 value for 200% (full) graphic display (default 30µg/m³)";
const char INTL_COMPARELOCATION[] PROGMEM =       "Compare location (valid = 0 to 31)";
const char INTL_COMPARELOCATION2[] PROGMEM =      "Compare location 2 (valid = 0 to 31)";
const char INTL_PMCHOICE[] PROGMEM =              "PM size for average, peak & graphics (default PM2,5)";
// 
const char INTL_AQI_WHO_TABLE[] PROGMEM =         "AQI & WHO";
const char INTL_AQI_TABLE_TITLE[] PROGMEM =       "Translating AQI levels to COLOR";
const char INTL_WHO_TABLE_TITLE[] PROGMEM =       "Translating WHO levels to COLOR";
// 
const char INTL_MAXAQIGREEN[] PROGMEM =           "Maximum level for GREEN (default 50)";
const char INTL_MAXAQIYELLOW[] PROGMEM =          "Maximum level for YELLOW (default 100)";           
const char INTL_MAXAQIORANGE[] PROGMEM =          "Maximum level for ORANGE (default 150)";           
const char INTL_MAXAQIRED[] PROGMEM =             "Maximum level for RED (default 200)";             
const char INTL_MAXAQIVIOLET[] PROGMEM =          "Maximum level for VIOLET (default 300)";             
// 
const char INTL_MAXWHOGREEN[] PROGMEM =           "Maximum level for GREEN (default PM2,5: 9µg/m³)";
const char INTL_MAXWHOYELLOW[] PROGMEM =          "Maximum level for YELLOW (default PM2,5: 30µg/m³)";           
const char INTL_MAXWHOORANGE[] PROGMEM =          "Maximum level for ORANGE (default PM2,5: 50µg/m³)";           
const char INTL_MAXWHORED[] PROGMEM =             "Maximum level for RED (default PM2,5: 120µg/m³)";             
const char INTL_MAXWHOVIOLET[] PROGMEM =          "Maximum level for VIOLET (default PM2,5: 230µg/m³)";             
// 
const char INTL_NOISE_TRAFFIC_TABLE[] PROGMEM =   "NOISE & TRAFFIC";
const char INTL_NOISE_TABLE_TITLE[] PROGMEM =     "Translating DNMS LAeq levels to COLOR";
const char INTL_TRAFFIC_TABLE_TITLE[] PROGMEM =   "Translating TRAFFIC levels to COLOR";
// 
const char INTL_MAXLAEQGREEN[] PROGMEM =          "Maximum level for GREEN (default 60dBA)";
const char INTL_MAXLAEQYELLOW[] PROGMEM =         "Maximum level for YELLOW (default 75dBA)";           
const char INTL_MAXLAEQORANGE[] PROGMEM =         "Maximum level for ORANGE (default 90dBA)";           
const char INTL_MAXLAEQRED[] PROGMEM =            "Maximum level for RED (default 100dBA)";             
const char INTL_MAXLAEQVIOLET[] PROGMEM =         "Maximum level for VIOLET (default 110dBA)";             
const char INTL_MAXLAEQBROWN[] PROGMEM =          "Maximum level for BROWN (default 120dBA)"; 
// 
const char INTL_MAXTRAFGREEN[] PROGMEM =          "Maximum level for GREEN (default 50)";
const char INTL_MAXTRAFYELLOW[] PROGMEM =         "Maximum level for YELLOW (default 100)";           
const char INTL_MAXTRAFORANGE[] PROGMEM =         "Maximum level for ORANGE (default 200)";           
const char INTL_MAXTRAFRED[] PROGMEM =            "Maximum level for RED (default 500)";
const char INTL_MAXTRAFCYAN[] PROGMEM =           "Maximum level for CYAN (default 1000)";            
const char INTL_MAXTRAFVIOLET[] PROGMEM =         "Maximum level for VIOLET (default 2000)";             
const char INTL_MAXTRAFBROWN[] PROGMEM =          "Maximum level for BROWN (default 5000)"; 
// 
const char INTL_TRAFFIC_PARAMS[] PROGMEM =        "TRAFFIC";
// 
const char INTL_TELRAAMAPI[] PROGMEM =            "Telraam API URL";
const char INTL_TELRAAMTOKEN[] PROGMEM =          "Telraam TOKEN";
const char INTL_FREETOKEN[] PROGMEM =             "FREE token (for testing only, showing yesterday's results !)";
const char INTL_SHOWPEDES[] PROGMEM =             " Show Pedestrians";
const char INTL_SHOWBIKE[] PROGMEM =              " Show Bikes";
const char INTL_SHOWCAR[] PROGMEM =               " Show Cars";
const char INTL_SHOWHEAVY[] PROGMEM =             " Show Heavy vehicles";
const char INTL_SHOWSPEED[] PROGMEM =             " Show V85 Speed";

// Word based text system
char *dotMatrixText[] = {
  "µg/m³",                          // 0 
  "  ñ ",     
  " Ñ ", 
  "°C", 
  "Temperature = ", 
  "Humidity = ",                    // 5
  "There is ",  
  "% more particulate matter ", 
  "% less particulate matter ", 
  " than in the vicinity of ",
  " in the vicinity of ",           // 10 
  "Mean of all measurements: ", 
  "In excess: ",  
  "Not connected:", 
  "Peak 24h.= ",                   
  "Average 24h.= ",                 // 15
  " Air pressure = ",
  " heavy vehicles; ",  
  " cars.",                         
  " cyclists; ", 
  " pedestrians; ",                 // 20
  "V85 speed: ",     
  " km/h; ",  
  "Traffic: ",                      
  "Noise: ", 
  " Peak: ",                        // 25
  " Bottom: ", 
  " Average: ",                     
  "Particulate matter: ", 
  "Weather: ",             
  "VOC & NOx index: ",              // 30
  "Reading...",
  "Server down...",
  "No internet...",
};  

// Compare strings
char *compareText[] = {
//"0         1         2         3         4         5         6         7         8         9         0         1"
//"012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890" 
//"==============================================================================================================="
  "The interior air is of worse quality than the exterior air - Aerate!",                                        // Outdoor -100%/-30%
  "The interior air is of somewhat worse quality than the exterior air.",                                        // Outdoor -30%/-10%
  "The quality of interior air and exterior air is approximately equal.",                                        // Outdoor -10%/+10%
  "The interior air is of somewhat better quality than the exterior air.",                                       // Outdoor +10%/+30%
  "The interior air is of better quality than the exterior air - Close doors and windows !",                     // Outdoor +30%/+100%
  "The interior air is of much better quality than the exterior air - Close doors and windows !",                // Outdoor >100%
};

// Text strings for AQI warning system
char *AQItext[] = {  
  "AQI index GREEN:  The air quality is satisfactory, and adverse health effects are not expected.", 
  "AQI index YELLOW: The air quality is moderate. WHO pollution limits are breached.",         
  "AQI index ORANGE: The air is unhealthy for sensitive groups.",                       
  "AQI index RED: The air is unhealthy. Everyone may experience health effects.",        
  "AQI index VIOLET: The air is very unhealthy. Everyone may experience more serious health effects.",   
};

// Text strings for WHO warning system
char *WHOtext[] = {  
  "WHO index GREEN: The average over 24h. shows good air quality.",                     
  "WHO index YELLOW: The average over 24h. shows moderate air quality.",      
  "WHO index ORANGE: The average over 24h. shows unhealthy air quality.",     
  "WHO index RED: The average over 24h. shows very unhealthy air quality.",    
  "WHO index VIOLET: The average over 24h. shows hazardous air quality.",     
};

String dayStr() 
{
	switch(myTZ.weekday()) 
  {
		case 1: return F("Sun.");  
		case 2: return F("Mon.");
		case 3: return F("Tue.");		
		case 4: return F("Wed.");
		case 5: return F("Thu.");
		case 6: return F("Fri.");
		case 7: return F("Sat.");
  }
	return "";
}

#include "airrohr-logo.h"
