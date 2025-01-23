#include <pgmspace.h>

#define    INTL_LANG                              "NL"  
//
const char INTL_SAVE_CONFIG[] PROGMEM =           "Configuratie opslaan";
const char INTL_SAVE_RESTART[] PROGMEM =          "Configuratie opslaan en herstarten";
const char INTL_WRITECONFIG[] PROGMEM =           "Configuratiebestanden schrijven";
const char INTL_REWRITECONFIG[] PROGMEM =         "Configuratiebestanden herschrijven";
const char INTL_CONFIG_WRITTEN[] PROGMEM =        "Configuratie geschreven";
const char INTL_WRITESUCCESS[] PROGMEM =          "Succesvol geschreven: ";
const char INTL_WRITEFAIL[] PROGMEM =             "Kan niet openen voor schrijven: ";
const char INTL_READCONFIG[] PROGMEM =            "Configuratiebestanden lezen";
const char INTL_OPENFAIL[] PROGMEM =              "Kan niet openen voor lezen: ";
const char INTL_READSUCCESS[] PROGMEM =           "Succesvol gelezen: ";
const char INTL_FORMATSPIFFS[] PROGMEM =          "Nieuwe versie gedetecteerd, SPIFFS formatteren";
const char INTL_JSONPARSING_ERR[] PROGMEM =       "Fout bij parseren van JSON-configuratie: ";
const char INTL_MOUNT_FS[] PROGMEM =              "Bestandssysteem koppelen...";
const char INTL_FAILMOUNT_FS[] PROGMEM =          "Kan bestandssysteem niet koppelen";
const char INTL_READAVGNPEAK[] PROGMEM =          "Gemiddelde en piekwaarden teruglezen";
const char INTL_WRITEAVGNPEAK[] PROGMEM =         "Gemiddelde en piekwaarden schrijven";
const char INTL_VALREQ_AUTH[] PROGMEM =           "Verzoek authenticatie valideren...";
const char INTL_AUTH_FAIL[] PROGMEM =             "Authenticatie mislukt";
const char INTL_ESP_RESTART[] PROGMEM =           "ESP gecontroleerde herstart";
const char INTL_DISPLAY_IS_REBOOTING[] PROGMEM =  "Display wordt opnieuw opgestart.";
const char INTL_NOT_REACHED[] PROGMEM =           "Had niet bereikt mogen worden!!!";
const char INTL_NOT_FOUND_FPSTR[] PROGMEM =       "Niet gevonden.";
const char INTL_SCANFAIL[] PROGMEM =              "WiFi-scan mislukt. Behandeld als leeg.";
const char INTL_START_WIFI_MAN[] PROGMEM =        "WiFiManager starten";
const char INTL_PASSWORD_DP[] PROGMEM =           "Wachtwoord: ";
const char INTL_SCANWIFI[] PROGMEM =              "WiFi-netwerken scannen...";
const char INTL_TXT_CONNECTING_TO[] PROGMEM =     "Verbinden met ";
const char INTL_AP_PASSWORD[] PROGMEM =           "AP-wachtwoord is: ";
const char INTL_TELRAAM_HEAP[] PROGMEM =          "TelRaam: onvoldoende heap beschikbaar.";
const char INTL_TELRAAM_SEGM[] PROGMEM =          "TelRaam segment = ";
const char INTL_TELRAAM_JSON_ERR[] PROGMEM =      "Fout bij parseren van TelRaam-JSON: ";
const char INTL_HEAPCHANGE_FROM[] PROGMEM =       "Heap gewijzigd van ";
const char INTL_HEAPCHANGE_TO[] PROGMEM =         " naar ";
const char INTL_HEAPDIFF[] PROGMEM =              " Verschil = ";
const char INTL_LOWHEAP_RESTART[] PROGMEM =       "Laag heap gedetecteerd, gecontroleerde herstart.";
const char INTL_LOWHEAP_TELRAAM[] PROGMEM =       "Laag heap tijd overschreden voor TelRaam, gecontroleerde herstart.";
const char INTL_ENDOFLIST[] PROGMEM =             "Einde van locatieslijst bereikt, sensoren lezen gestopt tot time-out.";
const char INTL_RESUMEREAD[] PROGMEM =            "Hervatten van sensorlezen, time-out verstreken.";
const char INTL_ONDISPLAY[] PROGMEM =             "Op display: ";
const char INTL_DISPLAYBUFF[] PROGMEM =           "======== Displaybuffer =========";
const char INTL_ENDOFBUFF[] PROGMEM =             "======= Einde van buffer =======";
const char INTL_SELFTEST_FAIL[] PROGMEM =         "Fout: ZELFTEST MISLUKT!";
const char INTL_QUAN_LOCATIONS[] PROGMEM =        "Aantal gedefinieerde locaties: ";
const char INTL_CONNECT_TO[] PROGMEM =            "Verbonden met: ";
const char INTL_TIMEZONE[] PROGMEM =              "Tijdzone = ";
const char INTL_TIMEUTC[] PROGMEM =               "Tijdzonelookup mislukt, UTC wordt gebruikt!";
const char INTL_LOCAL_IP[] PROGMEM =              "Lokaal IP: ";
const char INTL_ENDOF_SETUP[] PROGMEM =           "Einde van setup";
const char INTL_SCAN_NUM[] PROGMEM =              "Scan# ";
const char INTL_LOC_NAME[] PROGMEM =              " Locatienaam: ";
const char INTL_SENSOR_URL[] PROGMEM =            "Sensor @URL: ";
const char INTL_PMPARSING_ERR[] PROGMEM =         "Fout bij parseren van PM-JSON: ";
//
#define    INTL_AVG24H_PM25                       "Gemidd. 24u PM2,5: "
#define    INTL_AVG24H_PM10                       "Gemidd. 24u PM10: "
#define    INTL_PEAK24H_PM25                      "Piek 24u PM2,5: "
#define    INTL_PEAK24H_PM10                      "Piek 24u PM10: "
#define    INTL_QUANT_05UM                        "Aantal 0.5µm: "
#define    INTL_QUANT_1UM                         "Aantal 1µm: "
#define    INTL_QUANT_25UM                        "Aantal 2.5µm: "
#define    INTL_QUANT_4UM                         "Aantal 4µm: "
#define    INTL_QUANT_10UM                        "Aantal 10µm: "
#define    INTL_PART_SIZE                         "Deeltjesgrootte: "
#define    INTL_TEMPERATURE                       "Temperatuur: "
#define    INTL_HUMIDITY                          "Vochtigheid: "
#define    INTL_AIR_PRESS                         "Luchtdruk: "
#define    INTL_VOC_INDEX                         "VOC-index: "
#define    INTL_NOX_INDEX                         "NOx-index: "
#define    INTL_PEDESTRIANS                       "Voetgangers: "
#define    INTL_PER_HOUR                          "/u";
#define    INTL_BIKES                             "Fietsen: "
#define    INTL_CARS                              "Auto's: "
#define    INTL_HEAVY                             "Zware voertuigen: "
#define    INTL_V85_SPEED                         "V85-snelheid: "
#define    INTL_KM_PER_HOUR                       "km/u"
// 
#define    INTL_DISPLAY                           "Sensor.Community Display"
#define    INTL_BACK_TO_HOME_PAGE                 "Terug naar startpagina"
#define    INTL_BACK_TO_HOME_PAGE_DISCARD         "Wijzigingen negeren"
#define    INTL_CONFIGURATION_REALLY_DELETE       "Weet u zeker dat u de configuratie wilt verwijderen?"
#define    INTL_DELETE                            "Verwijderen"
#define    INTL_CANCEL                            "Annuleren"
#define    INTL_REALLY_RESTART_DISPLAY            "Weet u zeker dat u het display wilt herstarten?"
#define    INTL_RESTART                           "Herstarten"
#define    INTL_UPTIME                            "Display-werktijd: "
#define    INTL_READ_UPTO                         "Gelezen tot locatie: "
#define    INTL_RESET_REASON                      "Vorige resetreden: "
#define    INTL_FIRMWARE                          "Firmware: "
const char INTL_SIGNAL_STRENGTH[] PROGMEM =       "Signaalsterkte ";
const char INTL_SIGNAL_QUALITY[] PROGMEM =        "Signaalkwaliteit ";
const char INTL_ALERT[] PROGMEM =                 "Waarschuwingen";
#define    INTL_NUMBER_OF_CALLS                   "Aantal oproepen"
#define    INTL_SENSOR                            "Sensor"
#define    INTL_VALUE                             "Waarde"
#define    INTL_NOT_MEASURED                      "-- "
#define    INTL_DELETED                           "Verwijderd" 
#define    INTL_CANNOT_BE_DELETED                 "Kan niet worden verwijderd"
#define    INTL_NOT_FOUND                         "Niet gevonden"
#define    INTL_REPORT_ISSUE                      "Probleem melden"
const char INTL_PM[] PROGMEM =                    "Kies PM voor piek- en gemiddelde waarden...";
//
#define    INTL_HOME                              "Start"
const char INTL_CURRENT_DATA[] PROGMEM =          "Laatste waarden";
const char INTL_CONFIGURATION[] PROGMEM =         "Configuratie";
const char INTL_ADVANCED_SETTINGS[] PROGMEM =     "Geavanceerde instellingen";
const char INTL_DELETE_CONFIG[] PROGMEM =         "Opgeslagen configuratie verwijderen";
const char INTL_RESTART_DISPLAY[] PROGMEM =       "Display herstarten";
//
const char INTL_WIFI_SETTINGS[] PROGMEM =         "WiFi-instellingen";
//
const char INTL_FS_WIFI_NAME[] PROGMEM =          "Netwerknaam";
const char INTL_PASSWORD[] PROGMEM =              "Wachtwoord";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM =    "Geavanceerde instellingen (alleen wijzigen als u weet wat u doet)";
//
const char INTL_BASICAUTH[] PROGMEM =             " Authenticatie";
const char INTL_USER[] PROGMEM =                  "Gebruiker";
const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM =   "AP in configuratiemodus";
#define    INTL_LOADING_WIFI_NETWORKS             "WiFi-netwerken laden ..."
const char INTL_NO_NETWORKS[] PROGMEM =           "Geen WiFi-netwerk gevonden";
const char INTL_NETWORKS_FOUND[] PROGMEM =        "WiFi-netwerken gevonden: ";
//
#define    INTL_WIFI_CONNECTION_LOST              "WiFi-verbinding verloren"
#define    INTL_WIFI_CONNECT_TO                   "Verbind met:"
#define    INTL_WIFI_SSID                         "SSID: "
#define    INTL_WIFI_WIFI                         "WiFi: " 
#define    INTL_CONFIG_BUSY                       "Configuratie bezet"
#define    INTL_PLEASE_RESTART                    "Herstart aub"
//
const char INTL_LOCATION_0_15[] PROGMEM =         "Locatie 0-15";
const char INTL_LOCATION_16_31[] PROGMEM =        "Locatie 16-31";
const char INTL_LOCATION_NAME[] PROGMEM =         "Locatienaam";
const char INTL_SENSOR_API_1[] PROGMEM =          "API #1 (PM)";
const char INTL_SENSOR_API_2[] PROGMEM =          "API #2 (Temp/Vocht)";
const char INTL_SENSOR_API_3[] PROGMEM =          "API #3 (DNMS)";
const char INTL_SENSOR_API_4[] PROGMEM =          "API #4 (NOx/VOC) (of Telraamsegment)";
//
const char INTL_DISPLAY_SETTINGS[] PROGMEM =      "Weergave-instellingen";
const char INTL_DISPLAY_OPTIONS[] PROGMEM =       "Weergave-opties";
const char INTL_MULTICOMPARE[] PROGMEM =          " Toon alleen sensoren met PM-overschrijdingen";
const char INTL_SENSORMISSING[] PROGMEM =         " Toon inactieve sensoren";
const char INTL_SHOWPMPM[] PROGMEM =              " Toon PM-resultaten";
const char INTL_SHOWPM1PM4[] PROGMEM =            " Toon PM1- en PM4-waarden";
const char INTL_SHOWMETEO[] PROGMEM =             " Toon meteogegevens";
const char INTL_SHOWGRAPH[] PROGMEM =             " Toon grafieken";
const char INTL_SHOWAQIADVICE[] PROGMEM =         " Toon AQI-advies";
const char INTL_SHOWWHOADVICE[] PROGMEM =         " Toon WHO-advies";
const char INTL_MULTIAVERAGE[] PROGMEM =          " Toon gemiddelde van alle meters";
const char INTL_SHOWAVGNPEAK[] PROGMEM =          " Toon gemiddelde en piek over 24u.";
const char INTL_SHOWCOMP[] =                      " Vergelijk 2 sensoren en toon resultaat";
const char INTL_SHOWCOMPINSIDE[] PROGMEM =        " Vergelijk sensor #2 is binnenshuis";
const char INTL_SHOWDNMS[] PROGMEM =              " Toon DNMS-gegevens";
const char INTL_SHOWTELRAAM[] PROGMEM =           " Toon TELRAAM-gegevens";
//
const char INTL_SETTINGS[] PROGMEM =              "Algemene instellingen";
const char INTL_VALUES_TEXT[] PROGMEM =           "Waarden en tekst";
const char INTL_WELCOME[] PROGMEM =               "Welkomstbericht";
const char INTL_WELCOME2[] PROGMEM =              "Welkomstbericht 2 (afwisselend)";
const char INTL_CLOCKSECONDS[] PROGMEM =          "Klok op display (standaard 10 sec) (0 = geen klok)";
const char INTL_TIMEZONESTR[] PROGMEM =           "Tijdzone (zie Tijdzonedatabase op Wikipedia)";
const char INTL_DISPLAYSPEED[] PROGMEM =          "Weergavesnelheid (standaard 25 msec)";
const char INTL_PAUSETIME[] PROGMEM =             "Pauzetijd weergave (standaard 5 sec)";
const char INTL_WELCOMEINTERVAL[] PROGMEM =       "Interval welkomstbericht (# cycli) (standaard 10)";
const char INTL_CALLINGINTERVAL[] PROGMEM =       "Interval gegevens ophalen (standaard 6 min)";
const char INTL_DIFFERENCEPERCENT[] PROGMEM =     "Verschilpercentage voor melding (standaard 15%)";
const char INTL_DIFFERENCELEVEL[] PROGMEM =       "Verschilniveau voor melding (standaard 2µg/m³)";
const char INTL_SENSORDATATIMEOUT[] PROGMEM =     "Sensor time-out (# gemiste scans) (standaard 10)";
//
const char INTL_DEBUG_SETTINGS[] PROGMEM =        "Debug-instellingen";
const char INTL_DEBUGSHOWDATA[] PROGMEM =         " Toon gegevens";
const char INTL_DEBUGDISPLAY[] PROGMEM =          " Display"; 
const char INTL_DEBUGCOMMS[] PROGMEM =            " Communicatie";
const char INTL_DEBUGHEAP[] PROGMEM =             " Heap"; 
const char INTL_DEBUGJSON[] PROGMEM =             " Json";   
//
const char INTL_PM_PARAMS[] PROGMEM =             "PM-parameters";
const char INTL_URLSENSORCOMM[] PROGMEM =         "Sensor.Community API-URL";
const char INTL_WHO_PM25_MAXIMUM[] PROGMEM =      "WHO PM2,5 maximum (standaard 5µg/m³)";
const char INTL_WHO_PM10_MAXIMUM[] PROGMEM =      "WHO PM10 maximum (standaard 15µg/m³)";
const char INTL_PM25_TO_AQI50[] PROGMEM =         "PM2.5 naar AQI-50 conversie (standaard 9µg/m³)";
const char INTL_PM10_TO_AQI50[] PROGMEM =         "PM10 naar AQI-50 conversie (standaard 50µg/m³)";
const char INTL_MAXGRAPH_PM25[] PROGMEM =         "PM2.5 waarde voor 200% (volledige) grafiek (standaard 10µg/m³)";
const char INTL_MAXGRAPH_PM10[] PROGMEM =         "PM10 waarde voor 200% (volledige) grafiek (standaard 30µg/m³)";
const char INTL_COMPARELOCATION[] PROGMEM =       "Vergelijk locatie (geldig = 0 tot 31)";
const char INTL_COMPARELOCATION2[] PROGMEM =      "Vergelijk locatie 2 (geldig = 0 tot 31)";
const char INTL_PMCHOICE[] PROGMEM =              "PM-grootte voor gemiddelde, piek en grafieken (standaard PM2,5)";
//
const char INTL_PM_HUMI_TABLE[] PROGMEM =         "VOCHTIGHEID";
const char INTL_CORRECTHUMI[] PROGMEM =           " Corrigeer PM voor vochtigheid";
const char INTL_INTELLIHUMI[] PROGMEM =           " Intelligente vochtigheid tussen meerdere meters";
const char INTL_CORRECTHUMI_TITLE[] PROGMEM =     "Vochtigheidscorrectie op PM";
const char INTL_REFERENCE_STATION[] PROGMEM =     "Lokaal referentie station";
const char INTL_REFERENCE_NAME[] PROGMEM =        "Naam referentiestation";
const char INTL_PM_DRYREFERENCE[] PROGMEM =       "API-ID PM droge referentie";
const char INTL_HUMI_DRYREFERENCE[] PROGMEM =     "API-ID VOCHT. droge referentie";
const char INTL_PM_WETREFERENCE[] PROGMEM =       "API-ID PM natte referentie";
const char INTL_HUMI_WETREFERENCE[] PROGMEM =     "API-ID VOCHT. natte referentie";
//
const char INTL_AQI_WHO_TABLE[] PROGMEM =         "AQI en WHO";
const char INTL_AQI_TABLE_TITLE[] PROGMEM =       "AQI-niveaus vertalen naar KLEUR";
const char INTL_WHO_TABLE_TITLE[] PROGMEM =       "WHO-niveaus vertalen naar KLEUR";
//
const char INTL_MAXAQIGREEN[] PROGMEM =           "Maximum voor GROEN (standaard 50)";
const char INTL_MAXAQIYELLOW[] PROGMEM =          "Maximum voor GEEL (standaard 100)";           
const char INTL_MAXAQIORANGE[] PROGMEM =          "Maximum voor ORANJE (standaard 150)";           
const char INTL_MAXAQIRED[] PROGMEM =             "Maximum voor ROOD (standaard 200)";             
const char INTL_MAXAQIVIOLET[] PROGMEM =          "Maximum voor VIOLET (standaard 300)";             
//
const char INTL_MAXWHOGREEN[] PROGMEM =           "Maximum voor GROEN (standaard PM2,5: 9µg/m³)";
const char INTL_MAXWHOYELLOW[] PROGMEM =          "Maximum voor GEEL (standaard PM2,5: 30µg/m³)";           
const char INTL_MAXWHOORANGE[] PROGMEM =          "Maximum voor ORANJE (standaard PM2,5: 50µg/m³)";           
const char INTL_MAXWHORED[] PROGMEM =             "Maximum voor ROOD (standaard PM2,5: 120µg/m³)";             
const char INTL_MAXWHOVIOLET[] PROGMEM =          "Maximum voor VIOLET (standaard PM2,5: 230µg/m³)";             
//
const char INTL_NOISE_TRAFFIC_TABLE[] PROGMEM =   "GELUID en VERKEER";
const char INTL_NOISE_TABLE_TITLE[] PROGMEM =     "DNMS LAeq-niveaus vertalen naar KLEUR";
const char INTL_TRAFFIC_TABLE_TITLE[] PROGMEM =   "VERKEERSNIVEAUS vertalen naar KLEUR";
//
const char INTL_MAXLAEQGREEN[] PROGMEM =          "Maximum voor GROEN (standaard 60dBA)";
const char INTL_MAXLAEQYELLOW[] PROGMEM =         "Maximum voor GEEL (standaard 75dBA)";           
const char INTL_MAXLAEQORANGE[] PROGMEM =         "Maximum voor ORANJE (standaard 90dBA)";           
const char INTL_MAXLAEQRED[] PROGMEM =            "Maximum voor ROOD (standaard 100dBA)";             
const char INTL_MAXLAEQVIOLET[] PROGMEM =         "Maximum voor VIOLET (standaard 110dBA)";             
const char INTL_MAXLAEQBROWN[] PROGMEM =          "Maximum voor BRUIN (standaard 120dBA)"; 
//
const char INTL_MAXTRAFGREEN[] PROGMEM =          "Maximum voor GROEN (standaard 50)";
const char INTL_MAXTRAFYELLOW[] PROGMEM =         "Maximum voor GEEL (standaard 100)";           
const char INTL_MAXTRAFORANGE[] PROGMEM =         "Maximum voor ORANJE (standaard 200)";           
const char INTL_MAXTRAFRED[] PROGMEM =            "Maximum voor ROOD (standaard 500)";
const char INTL_MAXTRAFCYAN[] PROGMEM =           "Maximum voor CYAAN (standaard 1000)";            
const char INTL_MAXTRAFVIOLET[] PROGMEM =         "Maximum voor VIOLET (standaard 2000)";             
const char INTL_MAXTRAFBROWN[] PROGMEM =          "Maximum voor BRUIN (standaard 5000)"; 
//
const char INTL_TRAFFIC_PARAMS[] PROGMEM =        "VERKEER";
//
const char INTL_TELRAAMAPI[] PROGMEM =            "Telraam API-URL";
const char INTL_TELRAAMTOKEN[] PROGMEM =          "Telraam TOKEN";
const char INTL_FREETOKEN[] PROGMEM =             "GRATIS token (alleen voor testen, toont resultaten van gisteren!)";
const char INTL_SHOWPEDES[] PROGMEM =             " Toon Voetgangers";
const char INTL_SHOWBIKE[] PROGMEM =              " Toon Fietsers";
const char INTL_SHOWCAR[] PROGMEM =               " Toon Auto's";
const char INTL_SHOWHEAVY[] PROGMEM =             " Toon Zware voertuigen";
const char INTL_SHOWSPEED[] PROGMEM =             " Toon V85 Snelheid";

// Word based text system
char *dotMatrixText[] = {
  "µg/m³",                          // 0
  "  ñ ",           
  " Ñ ",          
  "°C", 
  "Temperatuur = ",  
  "Vochtigheid = ",                 // 5
  "Er is ",
  "% méér ",    
  "% minder ",   
  " dan bij meter ", 
  " fijnstof bij meter ",           // 10
  "Gemiddelde van alle meters: ", 
  "In overschrijding: ", 
  "Niet aangesloten:", 
  "Piek 24u.= ", 
  "Gemiddelde 24u.= ",              // 15
  " Luchtdruk = ", 
  " zware voertuigen; ", 
  " auto's.", 
  " fietsers; ",
  " voetgangers; ",                 // 20
  "V85 snelheid: ",  
  " km/h; ",    
  "Verkeer: ",  
  "Lawaai: ",
  " Piek: ",                        // 25
  " Dal: ",  
  " Gemiddeld: ", 
  "Fijnstof: ", 
  "Meteo: ", 
  "VOC & NOx index: ",              // 30
  "Leest...",
};  

// Compare strings
char *compareText[] = {
//"0         1         2         3         4         5         6         7         8         9         0         1"
//"012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
//"==============================================================================================================="
  "De kwaliteit van de binnenlucht is slechter dan die van de buitenlucht - Verluchten!",                        // Outdoor -100%/-30%
  "De kwaliteit van de binnenlucht is wat slechter dan die van de buitenlucht.",                                 // Outdoor -30%/-10%
  "De kwaliteit van de binnen- en buitenlucht is ongeveer gelijk.",                                              // Outdoor -10%/+10%
  "De kwaliteit van de binnenlucht is wat beter dan die van de buitenlucht.",                                    // Outdoor +10%/+30%
  "De kwaliteit van de binnenlucht is beter dan die van de buitenlucht - Ramen en deuren sluiten !",             // Outdoor +30%/+100%
  "De kwaliteit van de binnenlucht is veel beter dan die van de buitenlucht - Ramen en deuren sluiten !",        // Outdoor >100%
};

// AQI strings 
char *AQItext[] = {
  "AQI index GROEN: De luchtkwaliteit is goed. Er zijn geen gezondheidsrisico's.",           
  "AQI index GEEL: De luchtkwaliteit is matig.",                                      
  "AQI index ORANJE: De lucht is ongezond voor kwetsbare groepen.",                   
  "AQI index ROOD: De lucht is ongezond. Iedereen kan gezondheidseffecten ondervinden.",      
  "AQI index VIOLET: De lucht is zeer ongezond. Iedereen kan gezondheidseffecten ondervinden.",  
};

// WHO strings 
char *WHOtext[] = {
  "WHO index GROEN: De luchtkwaliteit over 24u. is goed.",                            
  "WHO index GEEL: De luchtkwaliteit over 24u. is matig.",                           
  "WHO index ORANJE: De luchtkwaliteit over 24u. is ongezond voor kwetsbare groepen.",   
  "WHO index ROOD: De luchtkwaliteit over 24u. is ongezond.",                          
  "WHO index VIOLET: De luchtkwaliteit over 24u. is zeer ongezond.",  
};

String dayStr() 
{
	switch(myTZ.weekday()) 
  {
		case 1: return F("Zo.");        
		case 2: return F("Ma.");
		case 3: return F("Di.");		
		case 4: return F("Wo.");
		case 5: return F("Do.");
		case 6: return F("Vr.");
		case 7: return F("Za.");
	}
	return "";
}

#include "airrohr-logo.h"
