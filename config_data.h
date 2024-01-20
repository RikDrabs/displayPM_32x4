//*************************************************************************
// Local configuration data
// ------------------------
// Here you can customise the Software and Hardware of the Particulate Matter Display.
// You can leave multiple parameter blocks, as long as the non-active ones are left in comment (/*  */)
// This is for producing updates for "past" installations.
// Plenty of examples are given here.
// ----
// Welcome messages must start with "S" for scrolling and should not be empty.
// Set API_DHT_1 to "00000", and DHT_ACTIVE to 0, when there is no DHT sensor.
// ----
// Defining a second outdoor sensor with OUTDOOR_2, API_SDS_2 and API_DHT_2 enables the
// comparative system, with report, advice and percentage messages. 
// ----
// Defining a second sensor with INDOOR_2 enables it for indoor use and appropriate messages.
// ----
// You can enable the 24 hour maximum value with MAX_24h (Beta as of 11/2023 !!)
// ----
// Enabling the SHORT parameter disables most detail displays, to retain only the important ones.
// So the display cycle time can be shortened.
//
//*************************************************************************
// Define the display hardware interface 
// 4 possible types of display hardware / choose the one that gives the correct display
#define     HARDWARE_TYPE     MD_MAX72XX::FC16_HW  
//
                 /* one of    MD_MAX72XX::GENERIC_HW 
                              MD_MAX72XX::ICSTATION_HW  (first prototypes)
                              MD_MAX72XX::PAROLA_HW
                              MD_MAX72XX::FC16_HW       (newer displays) 
                 */
                        
// Define the number of display devices we have in the chain
#define     NUMBER_DISPLAYS   16            // number of display blocks 8*8

// Connection to display
#define     CLOCK_PIN         D5            // ESP8266 pin to CLOCK-pin display 
#define     DATA_PIN          D7            // ESP8266 pin to DATA-pin display
#define     CHIP_SELECT_PIN   D8            // ESP8266 pin to CS-pin display

// Hardware SPI connection
MD_Parola   P = MD_Parola (HARDWARE_TYPE, CHIP_SELECT_PIN, NUMBER_DISPLAYS);

// List of supported languages.
// DUTCH, FRENCH, ENGLISH, GERMAN, ITALIAN.
//
//=============================================================================================================================================
// Config blocks
/*=============================================================================================================================================
// Do not exceed welcome      "0         1         2         3         4         5         6         7         8         9         0         1"
// message size!              "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
//=============================================================================================================================================
* /
#define     WELCOME_MESSAGE   "SLUCHTPIJP: een project van Beweging.net. Welkom in de Pletinckxstraat nr.19!"
#define     DUTCH             1             // Nederlands.
#define     SENSOR_1_NAME     "Pletinckxstraat" // Sensor 1 name.
#define     API_SDS_1         "24070"       // API-id SDS sensor 1.
#define     API_DHT_1         "24071"       // API-id DHT sensor 1.
#define     DHT_ACTIVE        1             // 1= DHT sensor 1 active.
#define     SENSOR_2          0             // 1= Sensor 2 active.
#define     INDOOR_2          0             // 1= Sensor 2 indoor.
#define     SENSOR_2_NAME     ""            // Sensor 2 name.
#define     API_SDS_2         "00000"       // API-id SDS sensor 2.
#define     API_DHT_2         "00000"       // API-id DHT sensor 2.
#define     PAUSE_TIME        3000          // Display timing: pause between messages on display (millisec.) - default 3000.
#define     DISPLAY_SPEED     25            // Display timing: scrolling delay on display (millisec. per step) - default 25.
#define     SHORT             1             // 1= Omit less important displays.
#define     MAX_24h           0             // 1= Show maximum values over 24h.
#define     AQI               1             // 1= Show AQI advice.
#define     MULTI_CONFIG      0             // 0= Normal; 1= Multi-configuration display.
/*=============================================================================================================================================
// Do not exceed welcome      "0         1         2         3         4         5         6         7         8         9         0         1"
// message size!              "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
//=============================================================================================================================================
* /
#define     WELCOME_MESSAGE   "SLUCHTPIJP: een project van Beweging.net. Welkom in de Martelarenlaan nr.8 !"
#define     DUTCH             1             // Nederlands.
#define     SENSOR_1_NAME     "Martelarenlaan" // Sensor 1 name.
#define     API_SDS_1         "9597"        // API-id SDS sensor 1.
#define     API_DHT_1         "9598"        // API-id DHT sensor 1.
#define     DHT_ACTIVE        1             // 1= DHT sensor 1 active.
#define     OUTDOOR_2         0             // 1= Sensor 2 outdoor active.
#define     INDOOR_2          0             // 1= Sensor 2 indoor active.
#define     SENSOR_2_NAME     ""            // Sensor 2 name.
#define     API_SDS_2         "00000"       // API-id SDS sensor 2.
#define     API_DHT_2         "00000"       // API-id DHT sensor 2.
#define     MSGLINE_TIMEOUT   25            // Messageline time-out number of cycles when no reception of data - default 25.
#define     PAUSE_TIME        3000          // Display timing: pause between messages on display (millisec.) - default 3000.
#define     DISPLAY_SPEED     25            // Display timing: scrolling delay on display (millisec. per step) - default 25.
#define     SHORT             1             // 1= Omit less important displays.
#define     MAX_24h           0             // 1= Show maximum values over 24h.
#define     AQI               1             // 1= Show AQI advice.
#define     MULTI_CONFIG      0             // 0= Normal; 1= Multi-configuration display.
/*=============================================================================================================================================
// Do not exceed welcome      "0         1         2         3         4         5         6         7         8         9         0         1"
// message size!              "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
//=============================================================================================================================================
* /
#define     WELCOME_MESSAGE   "SLUCHTPIJP: een project van Beweging.net. Welkom op het terugkom-moment Luchtpijp in BeCentral."
#define     DUTCH             1             // Nederlands.
#define     SENSOR_1_NAME     messageText[BUITEN] // Sensor 1 name.
#define     API_SDS_1         "32244"       // API-id SDS sensor 1.
#define     API_DHT_1         "32245"       // API-id DHT sensor 1.
#define     DHT_ACTIVE        1             // 1= DHT sensor 1 active.
#define     SENSOR_2          1             // 1= Sensor 2 active.
#define     INDOOR_2          1             // 1= Sensor 2 indoor.
#define     SENSOR_2_NAME     messageText[BINNEN] // Sensor 2 name.
#define     API_SDS_2         "38705"       // API-id SDS sensor 2.
#define     API_DHT_2         "38706"       // API-id DHT sensor 2.
#define     PAUSE_TIME        3000          // Display timing: pause between messages on display (millisec.) - default 3000.
#define     DISPLAY_SPEED     25            // Display timing: scrolling delay on display (millisec. per step) - default 25.
#define     SHORT             1             // 1= Omit less important displays.
#define     MAX_24h           0             // 1= Show maximum values over 24h.
#define     AQI               1             // 1= Show AQI advice.
#define     MULTI_CONFIG      0             // 0= Normal; 1= Multi-configuration display.
/*=============================================================================================================================================
// Do not exceed welcome      "0         1         2         3         4         5         6         7         8         9         0         1"
// message size!              "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
//=============================================================================================================================================
* /
#define     WELCOME_MESSAGE   "SWelkom op de nieuwjaarsreceptie van Beweging.net. Er hangen twee FIJNSTOFMETERS, één buiten en één binnen."
#define     DUTCH             1             // Nederlands.
#define     SENSOR_1_NAME     messageText[BUITEN] // Sensor 1 name.
#define     API_SDS_1         "32246"       // API-id SDS sensor 1.
#define     API_DHT_1         "32247"       // API-id DHT sensor 1.
#define     DHT_ACTIVE        1             // 1= DHT sensor 1 active.
#define     SENSOR_2          1             // 1= Sensor 2 active.
#define     INDOOR_2          1             // 1= Sensor 2 indoor.
#define     SENSOR_2_NAME     messageText[BINNEN] // Sensor 2 name.
#define     API_SDS_2         "38705"       // API-id SDS sensor 2.
#define     API_DHT_2         "38706"       // API-id DHT sensor 2.
#define     PAUSE_TIME        3000          // Display timing: pause between messages on display (millisec.) - default 3000.
#define     DISPLAY_SPEED     25            // Display timing: scrolling delay on display (millisec. per step) - default 25.
#define     SHORT             1             // 1= Omit less important displays.
#define     MAX_24h           0             // 1= Show maximum values over 24h.
#define     AQI               1             // 1= Show AQI advice.
#define     MULTI_CONFIG      0             // 0= Normal; 1= Multi-configuration display.
/*=============================================================================================================================================
// Do not exceed welcome      "0         1         2         3         4         5         6         7         8         9         0         1"
// message size!              "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
//=============================================================================================================================================
* /
#define     WELCOME_MESSAGE   "SLUCHTPIJP: een project van Beweging.net. Problematiek Bergense Steenweg te Anderlecht."
#define     DUTCH             1             // Nederlands.
#define     SENSOR_1_NAME     "Binnenkoer 63853" // Sensor 1 name.
#define     API_SDS_1         "63853"       // API-id SDS sensor 1.
#define     API_DHT_1         "63854"       // API-id DHT sensor 1.
#define     DHT_ACTIVE        0             // 1= DHT sensor 1 active.
#define     SENSOR_2          1             // 1= Sensor 2 outdoor active.
#define     INDOOR_2          0             // 1= Sensor 2 indoor active.
#define     SENSOR_2_NAME     "Referentie 20122" // Sensor 2 name.
#define     API_SDS_2         "20122"       // API-id SDS sensor 2.
#define     API_DHT_2         "20123"       // API-id DHT sensor 2.
#define     PAUSE_TIME        3000          // Display timing: pause between messages on display (millisec.) - default 3000.
#define     DISPLAY_SPEED     25            // Display timing: scrolling delay on display (millisec. per step) - default 25.
#define     SHORT             1             // 1= Omit less important displays.
#define     MAX_24h           0             // 1= Show maximum values over 24h.
#define     AQI               0             // 1= Show AQI advice.
#define     MULTI_CONFIG      0             // 0= Normal; 1= Multi-configuration display.
/*=============================================================================================================================================
// Do not exceed welcome      "0         1         2         3         4         5         6         7         8         9         0         1"
// message size!              "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
//=============================================================================================================================================
* /
#define     WELCOME_MESSAGE   "SLUCHTPIJP: een project van Beweging.net. Autoloze zondag te Brussel, op het Kasteleinsplein."
#define     DUTCH             1             // Nederlands.
#define     SENSOR_1_NAME     "Kasteleinsplein" // Sensor 1 name.
#define     API_SDS_1         "38705"       // API-id SDS sensor 1.
#define     API_DHT_1         "38706"       // API-id DHT sensor 1.
#define     DHT_ACTIVE        1             // 1= DHT sensor 1 active.
#define     SENSOR_2          1             // 1= Sensor 2 outdoor active.
#define     INDOOR_2          0             // 1= Sensor 2 indoor active.
#define     SENSOR_2_NAME     "Stwg. op Waterloo" // Sensor 2 name.
#define     API_SDS_2         "26700"       // API-id SDS sensor 2.
#define     API_DHT_2         "26701"       // API-id DHT sensor 2.
#define     PAUSE_TIME        3000          // Display timing: pause between messages on display (millisec.) - default 3000.
#define     DISPLAY_SPEED     25            // Display timing: scrolling delay on display (millisec. per step) - default 25.
#define     SHORT             1             // 1= Omit less important displays.
#define     MAX_24h           1             // 1= Show maximum values over 24h.
#define     AQI               1             // 1= Show AQI advice.
#define     MULTI_CONFIG      0             // 0= Normal; 1= Multi-configuration display.
/*=============================================================================================================================================
// Do not exceed welcome      "0         1         2         3         4         5         6         7         8         9         0         1"
// message size!              "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
//=============================================================================================================================================
* /
#define     WELCOME_MESSAGE   "SLUCHTPIJP: un projet de Beweging.net. Dimanche sans voiture à Bruxelles, Place du Châtelain"
#define     FRENCH            1             // Français.
#define     SENSOR_1_NAME     "Place du Châtelain" // Sensor 1 name.
#define     API_SDS_1         "38705"       // API-id SDS sensor 1.
#define     API_DHT_1         "38706"       // API-id DHT sensor 1.
#define     DHT_ACTIVE        1             // 1= DHT sensor 1 active.
#define     SENSOR_2          1             // 1= Sensor 2 outdoor active.
#define     INDOOR_2          0             // 1= Sensor 2 indoor active.
#define     SENSOR_2_NAME     "Chaussée de Waterloo" // Sensor 2 name.
#define     API_SDS_2         "26700"       // API-id SDS sensor 2.
#define     API_DHT_2         "26701"       // API-id DHT sensor 2.
#define     PAUSE_TIME        3000          // Display timing: pause between messages on display (millisec.) - default 3000.
#define     DISPLAY_SPEED     25            // Display timing: scrolling delay on display (millisec. per step) - default 25.
#define     SHORT             1             // 1= Omit less important displays.
#define     MAX_24h           1             // 1= Show maximum values over 24h.
#define     AQI               1             // 1= Show AQI advice.
#define     MULTI_CONFIG      0             // 0= Normal; 1= Multi-configuration display.
/*=============================================================================================================================================
// Do not exceed welcome      "0         1         2         3         4         5         6         7         8         9         0         1"
// message size!              "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
//=============================================================================================================================================
* /
#define     WELCOME_MESSAGE   "SLUCHTPIJP: een project van Beweging.net. Welkom in Vrije Basisschool Lutgardis!"
#define     DUTCH             1             // Nederlands.
#define     SENSOR_1_NAME     "Basisschool Lutgardis" // Sensor 1 name.
#define     API_SDS_1         "36609"       // API-id SDS sensor 1.  
#define     API_DHT_1         "36610"       // API-id DHT sensor 1.
#define     DHT_ACTIVE        1             // 1= DHT sensor 1 active.
#define     SENSOR_2          0             // 1= Sensor 2 active.
#define     INDOOR_2          0             // 1= Sensor 2 indoor.
#define     SENSOR_2_NAME     ""            // Sensor 2 name.
#define     API_SDS_2         "00000"       // API-id SDS sensor 2.
#define     API_DHT_2         "00000"       // API-id DHT sensor 2. 
#define     PAUSE_TIME        3000          // Display timing: pause between messages on display (millisec.) - default 3000.
#define     DISPLAY_SPEED     25            // Display timing: scrolling delay on display (millisec. per step) - default 25.
#define     SHORT             1             // 1= Omit less important displays.
#define     MAX_24h           0             // 1= Show maximum values over 24h.
#define     AQI               1             // 1= Show AQI advice.
#define     MULTI_CONFIG      0             // 0= Normal; 1= Multi-configuration display.
/*=============================================================================================================================================
// Do not exceed welcome      "0         1         2         3         4         5         6         7         8         9         0         1"
// message size!              "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
//=============================================================================================================================================
* /
#define     WELCOME_MESSAGE   "SLUCHTPIJP: een project van Beweging.net. Welkom bij GC De Markten!"
#define     DUTCH             1             // Nederlands.
#define     SENSOR_1_NAME     "GC De Markten" // Sensor 1 name.
#define     API_SDS_1         "33317"       // API-id SDS sensor 1.  
#define     API_DHT_1         "33318"       // API-id DHT sensor 1. 
#define     DHT_ACTIVE        1             // 1= DHT sensor 1 active.
#define     SENSOR_2          0             // 1= Sensor 2 active.
#define     INDOOR_2          0             // 1= Sensor 2 indoor.
#define     SENSOR_2_NAME     ""            // Sensor 2 name.
#define     API_SDS_2         "00000"       // API-id SDS sensor 2.
#define     API_DHT_2         "00000"       // API-id DHT sensor 2. 
#define     PAUSE_TIME        3000          // Display timing: pause between messages on display (millisec.) - default 3000.
#define     DISPLAY_SPEED     25            // Display timing: scrolling delay on display (millisec. per step) - default 25.
#define     SHORT             1             // 1= Omit less important displays.
#define     MAX_24h           0             // 1= Show maximum values over 24h.
#define     AQI               1             // 1= Show AQI advice.
#define     MULTI_CONFIG      0             // 0= Normal; 1= Multi-configuration display.
/*=============================================================================================================================================
// Do not exceed welcome      "0         1         2         3         4         5         6         7         8         9         0         1"
// message size!              "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
//=============================================================================================================================================
* / 
#define     WELCOME_MESSAGE   "SLUCHTPIJP: een project van Beweging.net. Welkom bij GC Ten Noey!"
#define     DUTCH             1             // Nederlands.
#define     SENSOR_1_NAME     "GC Ten Noey" // Sensor 1 name.
#define     API_SDS_1         "36685"       // API-id SDS sensor 1.  
#define     API_DHT_1         "36686"       // API-id DHT sensor 1. 
#define     DHT_ACTIVE        1             // 1= DHT sensor 1 active.
#define     SENSOR_2          0             // 1= Sensor 2 active.
#define     INDOOR_2          0             // 1= Sensor 2 indoor.
#define     SENSOR_2_NAME     ""            // Sensor 2 name.
#define     API_SDS_2         "00000"       // API-id SDS sensor 2.
#define     API_DHT_2         "00000"       // API-id DHT sensor 2. 
#define     PAUSE_TIME        3000          // Display timing: pause between messages on display (millisec.) - default 3000.
#define     DISPLAY_SPEED     25            // Display timing: scrolling delay on display (millisec. per step) - default 25.
#define     SHORT             1             // 1= Omit less important displays.
#define     MAX_24h           0             // 1= Show maximum values over 24h.
#define     AQI               1             // 1= Show AQI advice.
#define     MULTI_CONFIG      0             // 0= Normal; 1= Multi-configuration display.
/*=============================================================================================================================================
// Do not exceed welcome      "0         1         2         3         4         5         6         7         8         9         0         1"
// message size!              "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
//=============================================================================================================================================
* /
#define     WELCOME_MESSAGE   "SWelkom in het WinterWoninkje! Eén FIJNSTOFMETER meet het fijnstof hier, en één het fijnstof aan GC Ten Noey."
#define     DUTCH             1             // Nederlands.
#define     SENSOR_1_NAME     "WinterWoninkje" // Sensor 1 name.
#define     API_SDS_1         "39000"       // API-id SDS sensor 1.
#define     API_DHT_1         "39001"       // API-id DHT sensor 1.
#define     DHT_ACTIVE        1             // 1= DHT sensor 1 active.
#define     SENSOR_2          1             // 1= Sensor 2 active.
#define     INDOOR_2          0             // 1= Sensor 2 indoor.
#define     SENSOR_2_NAME     "GC Ten Noey" // Sensor 2 name.
#define     API_SDS_2         "36685"       // API-id SDS sensor 2.
#define     API_DHT_2         "36686"       // API-id DHT sensor 2.
#define     PAUSE_TIME        3000          // Display timing: pause between messages on display (millisec.) - default 3000.
#define     DISPLAY_SPEED     25            // Display timing: scrolling delay on display (millisec. per step) - default 25.
#define     SHORT             1             // 1= Omit less important displays.
#define     MAX_24h           0             // 1= Show maximum values over 24h.
#define     AQI               1             // 1= Show AQI advice.
#define     MULTI_CONFIG      0             // 0= Normal; 1= Multi-configuration display.
/*=============================================================================================================================================
// Do not exceed welcome      "0         1         2         3         4         5         6         7         8         9         0         1"
// message size!              "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
//=============================================================================================================================================
* /
#define     WELCOME_MESSAGE   "SLUCHTPIJP: un projet de Beweging.net. Bienvenue chez Myrjam & Bartel."
#define     FRENCH            1             // Français.
#define     SENSOR_1_NAME     "Rue Bois des Fosses 25" // Sensor 1 name.
#define     API_SDS_1         "42952"       // API-id SDS sensor 1.  
#define     API_DHT_1         "42953"       // API-id DHT sensor 1. 
#define     DHT_ACTIVE        1             // 1= DHT sensor 1 active.
#define     SENSOR_2          1             // 1= Sensor 2 active.
#define     INDOOR_2          0             // 1= Sensor 2 indoor.
#define     SENSOR_2_NAME     "Capteur à Borlo (15km)" // Sensor 2 name.
#define     API_SDS_2         "40417"       // API-id SDS sensor 2.
#define     API_DHT_2         "40418"       // API-id DHT sensor 2. 
#define     PAUSE_TIME        3000          // Display timing: pause between messages on display (millisec.) - default 3000.
#define     DISPLAY_SPEED     25            // Display timing: scrolling delay on display (millisec. per step) - default 25.
#define     SHORT             0             // 1= Omit less important displays.
#define     MAX_24h           1             // 1= Show maximum values over 24h.
#define     AQI               1             // 1= Show AQI advice.
#define     MULTI_CONFIG      0             // 0= Normal; 1= Multi-configuration display.
/*=============================================================================================================================================
// Do not exceed welcome      "0         1         2         3         4         5         6         7         8         9         0         1"
// message size!              "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
//=============================================================================================================================================
* /
#define     WELCOME_MESSAGE   "SLUCHTPIJP: een project van Beweging.net. Welkom bij Myrjam & Bartel."
#define     DUTCH             1             // Nederlands.
#define     SENSOR_1_NAME     messageText[BUITEN] // Sensor 1 name.
#define     API_SDS_1         "80165"       // ApiID SDS sensor 1.
#define     API_DHT_1         "80166"       // ApiID DHT sensor 1.
#define     DHT_ACTIVE        1             // 1= DHT sensor 1 active.
#define     SENSOR_2          0             // 1= Sensor 2 outdoor active.
#define     INDOOR_2          1             // 1= Sensor 2 indoor active.
#define     SENSOR_2_NAME     messageText[BINNEN] // Sensor 2 name.
#define     API_SDS_2         "80167"       // ApiID SDS sensor 2.
#define     API_DHT_2         "80168"       // ApiID DHT sensor 2.
#define     PAUSE_TIME        3000          // Display timing: pause between messages on display (millisec.) - default 3000.
#define     DISPLAY_SPEED     25            // Display timing: scrolling delay on display (millisec. per step) - default 25.
#define     SHORT             0             // 1= Omit less important displays.
#define     MAX_24h           1             // 1= Show maximum values over 24h.
#define     AQI               1             // 1= Show AQI advice.
#define     MULTI_CONFIG      0             // 0= Normal; 1= Multi-configuration display.
/*=============================================================================================================================================
// Do not exceed welcome      "0         1         2         3         4         5         6         7         8         9         0         1"
// message size!              "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
//=============================================================================================================================================
* /
#define     WELCOME_MESSAGE   "SInfluencAir: Welkom bij Martine & Rik."
#define     DUTCH             1             // Nederlands.
#define     SENSOR_1_NAME     messageText[BUITEN] // Sensor 1 name.
/*
#define     API_SDS_1         "15084"       // API-id SDS sensor 1. Thuis
#define     API_DHT_1         "15085"       // API-id DHT sensor 1.
//
#define     API_SDS_1         "64617"       // API-id SDS sensor 1. Atelier
#define     API_DHT_1         "64618"       // API-id DHT sensor 1.
* /
#define     API_SDS_1         "32124"       // API-id SDS sensor 1. Herman
#define     API_DHT_1         "32125"       // API-id DHT sensor 1.
//
#define     DHT_ACTIVE        1             // 1= DHT sensor 1 active.
#define     SENSOR_2          1             // 1= Sensor 2 active.
#define     INDOOR_2          1             // 1= Sensor 2 indoor.
#define     SENSOR_2_NAME     messageText[BINNEN] // Sensor 2 name.
#define     API_SDS_2         "27786"       // API-id SDS sensor 2.
#define     API_DHT_2         "27787"       // API-id DHT sensor 2.
#define     PAUSE_TIME        3000          // Display timing: pause between messages on display (millisec.) - default 3000.
#define     DISPLAY_SPEED     25            // Display timing: scrolling delay on display (millisec. per step) - default 25.
#define     SHORT             1             // 1= Omit less important displays.
#define     MAX_24h           1             // 1= Show maximum values over 24h.
#define     AQI               1             // 1= Show AQI advice.
#define     MULTI_CONFIG      0             // 0= Normal; 1= Multi-configuration display.
/*=============================================================================================================================================
// Do not exceed welcome      "0         1         2         3         4         5         6         7         8         9         0         1"
// message size!              "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
//=============================================================================================================================================
* /
#define     WELCOME_MESSAGE   "SLUCHTPIJP: project van Beweging.net. Welkom in Ter Pede. Aan de zijgevel hangt een FIJNSTOFMETER."  
#define     DUTCH             1             // Nederlands.
#define     SENSOR_1_NAME     "Ter Pede"    // Sensor 1 name.
#define     API_SDS_1         "17548"       // API-id SDS sensor 1.
#define     API_DHT_1         "17549"       // API-id DHT sensor 1.
#define     DHT_ACTIVE        1             // 1= DHT sensor 1 active.
#define     SENSOR_2          0             // 1= Sensor 2 active.
#define     INDOOR_2          0             // 1= Sensor 2 indoor.
#define     SENSOR_2_NAME     ""            // Sensor 2 name.
#define     API_SDS_2         "00000"       // API-id SDS sensor 2.
#define     API_DHT_2         "00000"       // API-id DHT sensor 2.
#define     PAUSE_TIME        3000          // Display timing: pause between messages on display (millisec.) - default 3000.
#define     DISPLAY_SPEED     25            // Display timing: scrolling delay on display (millisec. per step) - default 25.
#define     SHORT             1             // 1= Omit less important displays.
#define     MAX_24h           0             // 1= Show maximum values over 24h.
#define     AQI               1             // 1= Show AQI advice.
#define     MULTI_CONFIG      0             // 0= Normal; 1= Multi-configuration display.
/*=============================================================================================================================================
// Do not exceed welcome      "0         1         2         3         4         5         6         7         8         9         0         1"
// message size!              "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
//=============================================================================================================================================
* /
#define     WELCOME_MESSAGE   "SLUCHTPIJP in Oesterreich. Herzlich willkommen im Katznerhof."
#define     GERMAN            1             // Duits.
#define     SENSOR_1_NAME     "Seefeld"     // Sensor 1 name.
#define     API_SDS_1         "11283"       // API-id SDS sensor 1.
#define     API_DHT_1         "11284"       // API-id DHT sensor 1.
#define     DHT_ACTIVE        1             // 1= DHT sensor 1 active.
#define     SENSOR_2          1             // 1= Sensor 2 active.
#define     INDOOR_2          0             // 1= Sensor 2 indoor.
#define     SENSOR_2_NAME     "Telfs"       // Sensor 2 name.
#define     API_SDS_2         "10902"       // API-id SDS sensor 2.
#define     API_DHT_2         "10903"       // API-id DHT sensor 2.
#define     PAUSE_TIME        3000          // Display timing: pause between messages on display (millisec.) - default 3000.
#define     DISPLAY_SPEED     25            // Display timing: scrolling delay on display (millisec. per step) - default 25.
#define     SHORT             0             // 1= Omit less important displays.
#define     MAX_24h           1             // 1= Show maximum values over 24h.
#define     AQI               1             // 1= Show AQI advice.
#define     MULTI_CONFIG      0             // 0= Normal; 1= Multi-configuration display.
/*=============================================================================================================================================
// Do not exceed welcome      "0         1         2         3         4         5         6         7         8         9         0         1"
// message size!              "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
//=============================================================================================================================================
*/
#define     WELCOME_MESSAGE   "SInfluencAir: Multimeter monitoring"
#define     DUTCH             1             // Nederlands.
#define     SENSOR_1_NAME     ""            // Sensor 1 name.
#define     API_SDS_1         ""            // API-id SDS sensor 1.
#define     API_DHT_1         ""            // API-id DHT sensor 1.
#define     DHT_ACTIVE        0             // 1= DHT sensor 1 active.
#define     SENSOR_2          0             // 1= Sensor 2 active.
#define     INDOOR_2          0             // 1= Sensor 2 indoor.
#define     SENSOR_2_NAME     ""            // Sensor 2 name.
#define     API_SDS_2         ""            // API-id SDS sensor 2.
#define     API_DHT_2         ""            // API-id DHT sensor 2.
#define     PAUSE_TIME        3000          // Display timing: pause between messages on display (millisec.) - default 3000.
#define     DISPLAY_SPEED     25            // Display timing: scrolling delay on display (millisec. per step) - default 25.
#define     SHORT             1             // 1= Omit less important displays.
#define     MAX_24h           0             // 1= Show maximum values over 24h.
#define     AQI               1             // 1= Show AQI advice.
#define     MULTI_CONFIG      1             // 0= Normal; 1= Multi-configuration display.
/*=============================================================================================================================================
*/