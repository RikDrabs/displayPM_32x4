#include <pgmspace.h> 

#define    INTL_LANG                              "GE"  
//
const char INTL_SAVE_CONFIG[] PROGMEM =           "Konfiguration speichern";
const char INTL_SAVE_RESTART[] PROGMEM =          "Konfiguration speichern & Neustarten";
const char INTL_WRITECONFIG[] PROGMEM =           "Konfigurationsdateien werden geschrieben";
const char INTL_REWRITECONFIG[] PROGMEM =         "Konfigurationsdateien werden neu geschrieben";
const char INTL_CONFIG_WRITTEN[] PROGMEM =        "Konfiguration geschrieben";
const char INTL_WRITESUCCESS[] PROGMEM =          "Erfolgreich geschrieben: ";
const char INTL_WRITEFAIL[] PROGMEM =             "Fehler beim Öffnen zum Schreiben: ";
const char INTL_READCONFIG[] PROGMEM =            "Konfigurationsdateien werden gelesen";
const char INTL_OPENFAIL[] PROGMEM =              "Fehler beim Öffnen zum Lesen: ";
const char INTL_READSUCCESS[] PROGMEM =           "Erfolgreich gelesen: ";
const char INTL_FORMATSPIFFS[] PROGMEM =          "Neue Version erkannt, SPIFFS wird formatiert";
const char INTL_JSONPARSING_ERR[] PROGMEM =       "Fehler beim Parsen der Json-Konfiguration: ";
const char INTL_MOUNT_FS[] PROGMEM =              "FS wird gemountet...";
const char INTL_FAILMOUNT_FS[] PROGMEM =          "Fehler beim Mounten des FS";
const char INTL_READAVGNPEAK[] PROGMEM =          "Durchschnitts- und Spitzenwerte werden gelesen";
const char INTL_WRITEAVGNPEAK[] PROGMEM =         "Durchschnitts- und Spitzenwerte werden geschrieben";
const char INTL_VALREQ_AUTH[] PROGMEM =           "Anfragenauthentifizierung wird validiert...";
const char INTL_AUTH_FAIL[] PROGMEM =             "Authentifizierung fehlgeschlagen";
const char INTL_ESP_RESTART[] PROGMEM =           "ESP gesteuerter Neustart";
const char INTL_DISPLAY_IS_REBOOTING[] PROGMEM =  "Display wird neu gestartet.";
const char INTL_NOT_REACHED[] PROGMEM =           "Sollte nicht erreicht werden !!!";
const char INTL_NOT_FOUND_FPSTR[] PROGMEM =       "Nicht gefunden.";
const char INTL_SCANFAIL[] PROGMEM =              "WiFi-Scan fehlgeschlagen. Behandle es als leer.";
const char INTL_START_WIFI_MAN[] PROGMEM =        "WiFiManager wird gestartet";
const char INTL_PASSWORD_DP[] PROGMEM =           "Passwort: ";
const char INTL_SCANWIFI[] PROGMEM =              "Suche nach WiFi-Netzwerken...";
const char INTL_TXT_CONNECTING_TO[] PROGMEM =     "Verbinde mit ";
const char INTL_AP_PASSWORD[] PROGMEM =           "AP-Passwort ist: ";
const char INTL_TELRAAM_HEAP[] PROGMEM =          "TelRaam: Nicht genügend Heap verfügbar.";
const char INTL_TELRAAM_SEGM[] PROGMEM =          "TelRaam-Segment = ";
const char INTL_TELRAAM_JSON_ERR[] PROGMEM =      "Fehler beim Parsen der TelRaam-Json: ";
const char INTL_HEAPCHANGE_FROM[] PROGMEM =       "Heap-Änderung von ";
const char INTL_HEAPCHANGE_TO[] PROGMEM =         " zu ";
const char INTL_HEAPDIFF[] PROGMEM =              " Unterschied = ";
const char INTL_LOWHEAP_RESTART[] PROGMEM =       "Niedriger Heap erkannt, gesteuerter Neustart.";
const char INTL_LOWHEAP_TELRAAM[] PROGMEM =       "Heap-Zeitüberschreitung für Telraam, gesteuerter Neustart.";
const char INTL_ENDOFLIST[] PROGMEM =             "Ende der Standortliste erreicht, Stoppe Sensorlesen bis Timeout.";
const char INTL_RESUMEREAD[] PROGMEM =            "Fortsetzung des Sensorlesens, Timeout vorbei.";
const char INTL_ONDISPLAY[] PROGMEM =             "Auf Display: ";
const char INTL_DISPLAYBUFF[] PROGMEM =           "========= Displaypuffer ==========";
const char INTL_ENDOFBUFF[] PROGMEM =             "======= Ende des Puffers =========";
const char INTL_SELFTEST_FAIL[] PROGMEM =         "Fehler: SELBSTTEST FEHLGESCHLAGEN!";
const char INTL_QUAN_LOCATIONS[] PROGMEM =        "Anzahl der definierten Standorte: ";
const char INTL_CONNECT_TO[] PROGMEM =            "Verbunden mit: ";
const char INTL_TIMEZONE[] PROGMEM =              "Zeitzone = ";
const char INTL_TIMEUTC[] PROGMEM =               "Zeitzonenabfrage fehlgeschlagen, UTC wird verwendet!";
const char INTL_LOCAL_IP[] PROGMEM =              "Lokale IP: ";
const char INTL_ENDOF_SETUP[] PROGMEM =           "Setup abgeschlossen";
const char INTL_SCAN_NUM[] PROGMEM =              "Scan# ";
const char INTL_LOC_NAME[] PROGMEM =              " Standortname: ";
const char INTL_SENSOR_URL[] PROGMEM =            "Sensor @URL: ";
const char INTL_PMPARSING_ERR[] PROGMEM =         "Fehler beim Parsen der PM-Json: ";
//
#define    INTL_AVG24H_PM25                       "Durchs. 24 Std PM2,5: "
#define    INTL_AVG24H_PM10                       "Durchs. 24 Std PM10: "
#define    INTL_PEAK24H_PM25                      "Spitze 24 Std PM2,5: "
#define    INTL_PEAK24H_PM10                      "Spitze 24 Std PM10: "
#define    INTL_QUANT_05UM                        "Quant. 0,5µm: "
#define    INTL_QUANT_1UM                         "Quant. 1µm: "
#define    INTL_QUANT_25UM                        "Quant. 2,5µm: "
#define    INTL_QUANT_4UM                         "Quant. 4µm: "
#define    INTL_QUANT_10UM                        "Quant. 10µm: "
#define    INTL_PART_SIZE                         "Partikelgröße: "
#define    INTL_TEMPERATURE                       "Temperatur: "
#define    INTL_HUMIDITY                          "Luftfeuchtigkeit: "
#define    INTL_AIR_PRESS                         "Luftdruck: "
#define    INTL_VOC_INDEX                         "VOC-Index: "
#define    INTL_NOX_INDEX                         "NOx-Index: "
#define    INTL_PEDESTRIANS                       "Fußgänger: "
#define    INTL_PER_HOUR                          "/h"
#define    INTL_BIKES                             "Fahrräder: "
#define    INTL_CARS                              "Autos: "
#define    INTL_HEAVY                             "Schwerfahrzeuge: "
#define    INTL_V85_SPEED                         "V85-Geschwindigkeit: "
#define    INTL_KM_PER_HOUR                       "km/h"
//
#define    INTL_DISPLAY                           "Sensor.Community Anzeige"
#define    INTL_BACK_TO_HOME_PAGE                 "Zurück zur Startseite"
#define    INTL_BACK_TO_HOME_PAGE_DISCARD         "Änderungen verwerfen"
#define    INTL_CONFIGURATION_REALLY_DELETE       "Möchten Sie die Konfiguration wirklich löschen?"
#define    INTL_DELETE                            "Löschen"
#define    INTL_CANCEL                            "Abbrechen"
#define    INTL_REALLY_RESTART_DISPLAY            "Möchten Sie die Anzeige wirklich neu starten?"
#define    INTL_RESTART                           "Neu starten"
#define    INTL_UPTIME                            "Betriebszeit der Anzeige: "
#define    INTL_READ_UPTO                         "Zum Standort vorlesen: "
#define    INTL_RESET_REASON                      "Grund für den letzten Reset: "
#define    INTL_FIRMWARE                          "Firmware: "
const char INTL_SIGNAL_STRENGTH[] PROGMEM =       "Signalstärke ";
const char INTL_SIGNAL_QUALITY[] PROGMEM =        "Signalqualität ";
const char INTL_ALERT[] PROGMEM =                 "Warnungen";
#define    INTL_NUMBER_OF_CALLS                   "Anzahl der Aufrufe"
#define    INTL_SENSOR                            "Sensor"
#define    INTL_VALUE                             "Wert"
#define    INTL_NOT_MEASURED                      "-- "
#define    INTL_DELETED                           "Gelöscht" 
#define    INTL_CANNOT_BE_DELETED                 "Kann nicht gelöscht werden"
#define    INTL_NOT_FOUND                         "Nicht gefunden"
#define    INTL_REPORT_ISSUE                      "Problem melden"
const char INTL_PM[] PROGMEM =                    "Wählen Sie PM für Spitzen- und Durchschnittswerte...";
// 
#define    INTL_HOME                              "Startseite"
const char INTL_CURRENT_DATA[] PROGMEM =          "Letzte Werte";
const char INTL_CONFIGURATION[] PROGMEM =         "Konfiguration";
const char INTL_ADVANCED_SETTINGS[] PROGMEM =     "Erweiterte Einstellungen";
const char INTL_DELETE_CONFIG[] PROGMEM =         "Gespeicherte Konfiguration löschen";
const char INTL_RESTART_DISPLAY[] PROGMEM =       "Anzeige neu starten";
// 
const char INTL_WIFI_SETTINGS[] PROGMEM =         "WLAN-Einstellungen";
// 
const char INTL_FS_WIFI_NAME[] PROGMEM =          "Netzwerkname";
const char INTL_PASSWORD[] PROGMEM =              "Passwort";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM =    "Erweiterte Einstellungen (nur ändern, wenn Sie wissen, was Sie tun)";
//
const char INTL_BASICAUTH[] PROGMEM =             "Authentifizierung";
const char INTL_USER[] PROGMEM =                  "Benutzer";
const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM =   "AP im Konfigurationsmodus";
#define    INTL_LOADING_WIFI_NETWORKS             "WLAN-Netzwerke werden geladen ..."
const char INTL_NO_NETWORKS[] PROGMEM =           "Kein WLAN-Netzwerk gefunden";
const char INTL_NETWORKS_FOUND[] PROGMEM =        "WLAN-Netzwerke gefunden: ";
// 
#define    INTL_WIFI_CONNECTION_LOST              "WLAN-Verbindung verloren"
#define    INTL_WIFI_CONNECT_TO                   "Bitte verbinden Sie sich mit:"
#define    INTL_WIFI_SSID                         "SSID: "
#define    INTL_WIFI_WIFI                         "WLAN: " 
#define    INTL_CONFIG_BUSY                       "Konfiguration beschäftigt"
#define    INTL_PLEASE_RESTART                    "Bitte neu starten"
// 
const char INTL_LOCATION_0_15[] PROGMEM =         "Ort 0-15";
const char INTL_LOCATION_16_31[] PROGMEM =        "Ort 16-31";
const char INTL_LOCATION_NAME[] PROGMEM =         "Ortsname";
const char INTL_SENSOR_API_1[] PROGMEM =          "API #1 (PM)";
const char INTL_SENSOR_API_2[] PROGMEM =          "API #2 (Temp/Feuchte)";
const char INTL_SENSOR_API_3[] PROGMEM =          "API #3 (DNMS)";
const char INTL_SENSOR_API_4[] PROGMEM =          "API #4 (NOx/VOC) (oder Telraam-Segment)";
// 
const char INTL_DISPLAY_SETTINGS[] PROGMEM =      "Anzeigeeinstellungen";
const char INTL_DISPLAY_OPTIONS[] PROGMEM =       "Anzeigeoptionen";
const char INTL_MULTICOMPARE[] PROGMEM =          " Nur Sensoren mit PM-Überwerten anzeigen";
const char INTL_SENSORMISSING[] PROGMEM =         " Inaktive Sensoren anzeigen";
const char INTL_SHOWPMPM[] PROGMEM =              " PM-Ergebnisse anzeigen";
const char INTL_SHOWPM1PM4[] PROGMEM =            " PM1- und PM4-Werte anzeigen";
const char INTL_SHOWMETEO[] PROGMEM =             " Wetterdaten anzeigen";
const char INTL_SHOWGRAPH[] PROGMEM =             " Grafiken anzeigen";
const char INTL_SHOWAQIADVICE[] PROGMEM =         " AQI-Ratschläge anzeigen";
const char INTL_SHOWWHOADVICE[] PROGMEM =         " WHO-Ratschläge anzeigen";
const char INTL_MULTIAVERAGE[] PROGMEM =          " Durchschnitt aller Sensoren anzeigen";
const char INTL_SHOWAVGNPEAK[] PROGMEM =          " 24h-Durchschnitt & Spitze anzeigen";
const char INTL_SHOWCOMP[] =                      " Zwei Sensoren vergleichen & Ergebnis anzeigen";
const char INTL_SHOWCOMPINSIDE[] =                " Vergleich: Sensor #2 ist im Innenbereich";
const char INTL_SHOWDNMS[] PROGMEM =              " DNMS-Daten anzeigen";
const char INTL_SHOWTELRAAM[] PROGMEM =           " TELRAAM-Daten anzeigen";
// 
const char INTL_SETTINGS[] PROGMEM =              "Allgemeine Einstellungen";
const char INTL_VALUES_TEXT[] PROGMEM =           "Werte und Text";
const char INTL_WELCOME[] PROGMEM =               "Willkommensnachricht";
const char INTL_WELCOME2[] PROGMEM =              "Willkommensnachricht 2 (abwechselnd)";
const char INTL_CLOCKSECONDS[] PROGMEM =          "Uhr angezeigt (Standard 10 Sek.) (0 = keine Uhr)";
const char INTL_TIMEZONESTR[] PROGMEM =           "Zeitzone (siehe Zeitzonendatenbank auf Wikipedia)";
const char INTL_DISPLAYSPEED[] PROGMEM =          "Schrittzeit anzeigen (Standard 25 ms)";
const char INTL_PAUSETIME[] PROGMEM =             "Pausenzeit anzeigen (Standard 5 Sek.)";
const char INTL_WELCOMEINTERVAL[] PROGMEM =       "Intervall der Willkommensnachricht (Anzahl Zyklen) (Standard 10)";
const char INTL_CALLINGINTERVAL[] PROGMEM =       "Intervall des Datenabrufs (Standard 6 Min.)";
const char INTL_DIFFERENCEPERCENT[] PROGMEM =     "Prozentuale Differenz vor Benachrichtigung (Standard 15 %)";
const char INTL_DIFFERENCELEVEL[] PROGMEM =       "Differenzniveau vor Benachrichtigung (Standard 2 µg/m³)";
const char INTL_SENSORDATATIMEOUT[] PROGMEM =     "Timeout der Sensordaten (Anzahl verpasster Scans) (Standard 10)";
// 
const char INTL_DEBUG_SETTINGS[] PROGMEM =        "Debug-Einstellungen";
const char INTL_DEBUGSHOWDATA[] PROGMEM =         " Daten anzeigen";
const char INTL_DEBUGDISPLAY[] PROGMEM =          " Anzeige";
const char INTL_DEBUGCOMMS[] PROGMEM =            " Kommunikation";
const char INTL_DEBUGHEAP[] PROGMEM =             " Heap";
const char INTL_DEBUGJSON[] PROGMEM =             " Json";
// 
const char INTL_PM_PARAMS[] PROGMEM =             "PM-Parameter";
const char INTL_URLSENSORCOMM[] PROGMEM =         "Sensor.Community API-URL";
const char INTL_WHO_PM25_MAXIMUM[] PROGMEM =      "WHO PM2,5-Maximum (Standard: 5µg/m³)";
const char INTL_WHO_PM10_MAXIMUM[] PROGMEM =      "WHO PM10-Maximum (Standard: 15µg/m³)";
const char INTL_PM25_TO_AQI50[] PROGMEM =         "PM2,5 zu AQI-50 Umrechnung (Standard: 9µg/m³)";
const char INTL_PM10_TO_AQI50[] PROGMEM =         "PM10 zu AQI-50 Umrechnung (Standard: 50µg/m³)";
const char INTL_MAXGRAPH_PM25[] PROGMEM =         "PM2,5-Wert für 200% (volle) grafische Anzeige (Standard: 10µg/m³)";
const char INTL_MAXGRAPH_PM10[] PROGMEM =         "PM10-Wert für 200% (volle) grafische Anzeige (Standard: 30µg/m³)";
const char INTL_COMPARELOCATION[] PROGMEM =       "Standort vergleichen (gültig = 0 bis 31)";
const char INTL_COMPARELOCATION2[] PROGMEM =      "Standort 2 vergleichen (gültig = 0 bis 31)";
const char INTL_PMCHOICE[] PROGMEM =              "PM-Größe für Durchschnitt, Spitze und Grafiken (Standard: PM2,5)";
// 
const char INTL_PM_HUMI_TABLE[] PROGMEM =         "FEUCHTE";
const char INTL_CORRECTHUMI[] PROGMEM =           " Richtige PM für Luftfeuchtigkeit";
const char INTL_INTELLIHUMI[] PROGMEM =           " Intelligente Feuchte zwischen mehreren Sensoren";
const char INTL_CORRECTHUMI_TITLE[] PROGMEM =     "Feuchtigkeitskorrektur für PM";
const char INTL_REFERENCE_STATION[] PROGMEM =     "Lokale Referenzstation";
const char INTL_REFERENCE_NAME[] PROGMEM =        "Name der Referenzstation";
const char INTL_PM_DRYREFERENCE[] PROGMEM =       "API-ID Trockenreferenz PM";
const char INTL_HUMI_DRYREFERENCE[] PROGMEM =     "API-ID Trockenreferenz Feuchtigkeit";
const char INTL_PM_WETREFERENCE[] PROGMEM =       "API-ID Nassreferenz PM";
const char INTL_HUMI_WETREFERENCE[] PROGMEM =     "API-ID Nassreferenz Feuchtigkeit";
//
const char INTL_AQI_WHO_TABLE[] PROGMEM =         "AQI und WHO";
const char INTL_AQI_TABLE_TITLE[] PROGMEM =       "Übersetzung von AQI-Stufen in FARBE";
const char INTL_WHO_TABLE_TITLE[] PROGMEM =       "Übersetzung von WHO-Stufen in FARBE";
// 
const char INTL_MAXAQIGREEN[] PROGMEM =           "Maximale Stufe für GRÜN (Standard: 50)";
const char INTL_MAXAQIYELLOW[] PROGMEM =          "Maximale Stufe für GELB (Standard: 100)";
const char INTL_MAXAQIORANGE[] PROGMEM =          "Maximale Stufe für ORANGE (Standard: 150)";
const char INTL_MAXAQIRED[] PROGMEM =             "Maximale Stufe für ROT (Standard: 200)";
const char INTL_MAXAQIVIOLET[] PROGMEM =          "Maximale Stufe für VIOLETT (Standard: 300)";
// 
const char INTL_MAXWHOGREEN[] PROGMEM =           "Maximale Stufe für GRÜN (Standard PM2,5: 9µg/m³)";
const char INTL_MAXWHOYELLOW[] PROGMEM =          "Maximale Stufe für GELB (Standard PM2,5: 30µg/m³)";
const char INTL_MAXWHOORANGE[] PROGMEM =          "Maximale Stufe für ORANGE (Standard PM2,5: 50µg/m³)";
const char INTL_MAXWHORED[] PROGMEM =             "Maximale Stufe für ROT (Standard PM2,5: 120µg/m³)";
const char INTL_MAXWHOVIOLET[] PROGMEM =          "Maximale Stufe für VIOLETT (Standard PM2,5: 230µg/m³)";
// 
const char INTL_NOISE_TRAFFIC_TABLE[] PROGMEM =   "LÄRM und VERKEHR";
const char INTL_NOISE_TABLE_TITLE[] PROGMEM =     "Übersetzung von DNMS LAeq-Werten in FARBE";
const char INTL_TRAFFIC_TABLE_TITLE[] PROGMEM =   "Übersetzung von VERKEHRs-Werten in FARBE";
// 
const char INTL_MAXLAEQGREEN[] PROGMEM =          "Maximale Stufe für GRÜN  (Standard 60dBA)";
const char INTL_MAXLAEQYELLOW[] PROGMEM =         "Maximale Stufe für GELB (Standard 75dBA)";           
const char INTL_MAXLAEQORANGE[] PROGMEM =         "Maximale Stufe für ORANGE (Standard 90dBA)";           
const char INTL_MAXLAEQRED[] PROGMEM =            "Maximale Stufe für ROT (Standard 100dBA)";             
const char INTL_MAXLAEQVIOLET[] PROGMEM =         "Maximale Stufe für VIOLETT (Standard 110dBA)";             
const char INTL_MAXLAEQBROWN[] PROGMEM =          "Maximale Stufe für BRAUN (Standard 120dBA)"; 
// 
const char INTL_MAXTRAFGREEN[] PROGMEM =          "Maximale Stufe für GRÜN  (Standard 50)";
const char INTL_MAXTRAFYELLOW[] PROGMEM =         "Maximale Stufe für GELB (Standard 100)";           
const char INTL_MAXTRAFORANGE[] PROGMEM =         "Maximale Stufe für ORANGE (Standard 200)";           
const char INTL_MAXTRAFRED[] PROGMEM =            "Maximale Stufe für ROT (Standard 500)";
const char INTL_MAXTRAFCYAN[] PROGMEM =           "Maximale Stufe für CYAN (Standard 1000)";            
const char INTL_MAXTRAFVIOLET[] PROGMEM =         "Maximale Stufe für VIOLETT (Standard 2000)";             
const char INTL_MAXTRAFBROWN[] PROGMEM =          "Maximale Stufe für BRAUN (Standard 5000)"; 
// 
const char INTL_TRAFFIC_PARAMS[] PROGMEM =        "VERKEHR";
// 
const char INTL_TELRAAMAPI[] PROGMEM =            "Telraam API URL";
const char INTL_TELRAAMTOKEN[] PROGMEM =          "Telraam TOKEN";
const char INTL_FREETOKEN[] PROGMEM =             "KOSTENLOSER Token (nur zum Testen, zeigt die Ergebnisse von gestern!)";
const char INTL_SHOWPEDES[] PROGMEM =             " Fußgänger anzeigen";
const char INTL_SHOWBIKE[] PROGMEM =              " Fahrräder anzeigen";
const char INTL_SHOWCAR[] PROGMEM =               " Autos anzeigen";
const char INTL_SHOWHEAVY[] PROGMEM =             " Schwere Fahrzeuge anzeigen";
const char INTL_SHOWSPEED[] PROGMEM =             " V85-Geschwindigkeit anzeigen";

// Word based text system
char *dotMatrixText[] = {
  "µg/m³",                          // 0
  "  ñ ",   
  " Ñ ",   
  "°C", 
  "Temperatur = ", 
  "Feuchtigkeit = ",                // 5
  "Es gibt ",  
  "% mehr ", 
  "% weniger ", 
  " als am Meter ",
  " Feinstaub am Meter ",           // 10
  "Durchschnitt über alle Meter: ",
  "In uberschreitung: ", 
  "Nicht verbunden:",
  "Spitze 24St.= ", 
  "Durchschnitt 24St.= ",           // 15
  " Luftdruck = ",   
  " schwere Fahrzeuge; ",
  " autos.", 
  " radfahrer; ",  
  " fußgänger; ",                   // 20
  "V85-Geschwindigkeit: ", 
  " km/h; ",   
  "Verkehr: ", 
  "Lärm: ",   
  " Maximum: ",                     // 25
  " Minimum: ", 
  " Durchschnitt: ", 
  "Feinstaub: ",  
  "Wetter: ",  
  "VOC- und NOx-Index: ",           // 30
  "Liest...",
};  

// Compare strings 
char *compareText[] = {
//"0         1         2         3         4         5         6         7         8         9         0         1"
//"012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890" 
//"==============================================================================================================="
  "Die Luftqualität der Innenluft ist schlechter als die der Außenluft – Lüften!",                               // Outdoor -100%/-30%
  "Die Luftqualität der Innenluft ist etwas schlechter als die der Außenluft.",                                  // Outdoor -30%/-10%
  "Die Luftqualität der Innen- und Außenluft ist etwa gleich.",                                                  // Outdoor -10%/+10%
  "Die Luftqualität der Innenluft ist etwas besser als die der Außenluft.",                                      // Outdoor +10%/+30%
  "Die Luftqualität der Innenluft ist besser als die der Außenluft – Fenster und Türen schließen !",             // Outdoor +30%/+100%
  "Die Luftqualität der Innenluft ist viel besser als die der Außenluft – Fenster und Türen schließen !",        // Outdoor >100%
};

// AQI strings 
char *AQItext[] = {  
//"0         1         2         3         4         5         6         7         8         9         0         1"
//"012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890" 
//"==============================================================================================================="
  "AQI-index GRÜN: Die Luftqualität ist gut. Es bestehen keine Gesundheitsrisiken.",                           
  "AQI-index GELB: Die Luftqualität ist mäßig. Der WHO-Standard wurde übertroffen.",                           
  "AQI-index ORANGE: Die Luft ist für gefährdete Personen ungesund.",                                          
  "AQI-index ROT: Die Luft ist ungesund. Gesundheitsschäden können bei jedem auftreten.",                      
  "AQI-index VIOLETT: Die Luft ist sehr ungesund. Jeder kann schwerwiegende gesundheitliche Auswirkungen haben.",       
};

// WHO strings 
char *WHOtext[] = {  
//"0         1         2         3         4         5         6         7         8         9         0         1"
//"012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890" 
//"==============================================================================================================="  
  "WHO-Index GRÜN: Die 24-Stunden-Luftqualität ist gut.",                
  "WHO-Index GELB: Die 24-Stunden-Luftqualität ist mäßig.",              
  "WHO-Index ORANGE: Die 24-Stunden-Luftqualität ist ungesund.",         
  "WHO-Index ROT: Die 24-Stunden-Luftqualität ist sehr ungesund.",       
  "WHO-Index VIOLETT: Die 24-Stunden-Luftqualität ist gefährlich.",        
};

String dayStr() 
{
	switch(myTZ.weekday()) 
  {
		case 1: return F("So.");      
		case 2: return F("Mo.");
		case 3: return F("Di.");		
		case 4: return F("Mi.");
		case 5: return F("Do.");
		case 6: return F("Fr.");
		case 7: return F("Sa.");
	}
	return "";
}

#include "airrohr-logo.h"
