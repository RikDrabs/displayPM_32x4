#include <pgmspace.h> 

#define    INTL_LANG                              "IT"  
//
const char INTL_SAVE_CONFIG[] PROGMEM =           "Salva configurazione";
const char INTL_SAVE_RESTART[] PROGMEM =          "Salva configurazione e riavvia";
const char INTL_WRITECONFIG[] PROGMEM =           "Scrittura dei file di configurazione";
const char INTL_REWRITECONFIG[] PROGMEM =         "Riscrittura dei file di configurazione";
const char INTL_CONFIG_WRITTEN[] PROGMEM =        "Configurazione salvata";
const char INTL_WRITESUCCESS[] PROGMEM =          "Scrittura completata con successo: ";
const char INTL_WRITEFAIL[] PROGMEM =             "Impossibile aprire per la scrittura: ";
const char INTL_READCONFIG[] PROGMEM =            "Lettura dei file di configurazione";
const char INTL_OPENFAIL[] PROGMEM =              "Impossibile aprire per la lettura: ";
const char INTL_READSUCCESS[] PROGMEM =           "Lettura completata con successo: ";
const char INTL_FORMATSPIFFS[] PROGMEM =          "Rilevata nuova versione, formattazione SPIFFS in corso";
const char INTL_JSONPARSING_ERR[] PROGMEM =       "Errore di analisi Json della configurazione: ";
const char INTL_MOUNT_FS[] PROGMEM =              "Montaggio del file system...";
const char INTL_FAILMOUNT_FS[] PROGMEM =          "Impossibile montare il file system";
const char INTL_READAVGNPEAK[] PROGMEM =          "Lettura di valori medi e di picco";
const char INTL_WRITEAVGNPEAK[] PROGMEM =         "Scrittura di valori medi e di picco";
const char INTL_VALREQ_AUTH[] PROGMEM =           "Validazione richiesta di autenticazione...";
const char INTL_AUTH_FAIL[] PROGMEM =             "Autenticazione fallita";
const char INTL_ESP_RESTART[] PROGMEM =           "Riavvio controllato ESP";
const char INTL_DISPLAY_IS_REBOOTING[] PROGMEM =  "Il display si sta riavviando.";
const char INTL_NOT_REACHED[] PROGMEM =           "Non avrebbe dovuto essere raggiunto!!!";
const char INTL_NOT_FOUND_FPSTR[] PROGMEM =       "Non trovato.";
const char INTL_SCANFAIL[] PROGMEM =              "Scansione Wi-Fi fallita. Trattata come vuota.";
const char INTL_START_WIFI_MAN[] PROGMEM =        "Avvio di WiFiManager";
const char INTL_PASSWORD_DP[] PROGMEM =           "Password: ";
const char INTL_SCANWIFI[] PROGMEM =              "Scansione delle reti Wi-Fi in corso...";
const char INTL_TXT_CONNECTING_TO[] PROGMEM =     "Connessione a ";
const char INTL_AP_PASSWORD[] PROGMEM =           "La password dell'AP è: ";
const char INTL_TELRAAM_HEAP[] PROGMEM =          "TelRaam: memoria heap insufficiente disponibile.";
const char INTL_TELRAAM_SEGM[] PROGMEM =          "Segmento TelRaam = ";
const char INTL_TELRAAM_JSON_ERR[] PROGMEM =      "Errore di analisi Json di TelRaam: ";
const char INTL_HEAPCHANGE_FROM[] PROGMEM =       "Cambio heap da ";
const char INTL_HEAPCHANGE_TO[] PROGMEM =         " a ";
const char INTL_HEAPDIFF[] PROGMEM =              " Differenza = ";
const char INTL_LOWHEAP_RESTART[] PROGMEM =       "Memoria heap bassa rilevata, riavvio controllato.";
const char INTL_LOWHEAP_TELRAAM[] PROGMEM =       "Tempo di memoria heap bassa superato per TelRaam, riavvio controllato.";
const char INTL_ENDOFLIST[] PROGMEM =             "Fine dell'elenco delle località raggiunta, lettura dei sensori interrotta fino al timeout.";
const char INTL_RESUMEREAD[] PROGMEM =            "Ripresa della lettura dei sensori, timeout superato.";
const char INTL_ONDISPLAY[] PROGMEM =             "Sul display: ";
const char INTL_DISPLAYBUFF[] PROGMEM =           "======== Buffer display ==========";
const char INTL_ENDOFBUFF[] PROGMEM =             "======= Fine del buffer ==========";
const char INTL_SELFTEST_FAIL[] PROGMEM =         "Errore: AUTO-TEST FALLITO!";
const char INTL_QUAN_LOCATIONS[] PROGMEM =        "Quantità di località definite: ";
const char INTL_CONNECT_TO[] PROGMEM =            "Connesso a: ";
const char INTL_TIMEZONE[] PROGMEM =              "Fuso orario = ";
const char INTL_TIMEUTC[] PROGMEM =               "Ricerca del fuso orario fallita, utilizzo UTC!";
const char INTL_LOCAL_IP[] PROGMEM =              "IP locale: ";
const char INTL_ENDOF_SETUP[] PROGMEM =           "Fine della configurazione";
const char INTL_SCAN_NUM[] PROGMEM =              "Scansione n. ";
const char INTL_LOC_NAME[] PROGMEM =              " Nome località: ";
const char INTL_SENSOR_URL[] PROGMEM =            "Sensore @URL: ";
const char INTL_PMPARSING_ERR[] PROGMEM =         "Errore di analisi Json di PM: ";
const char INTL_HTTPCODE_ERR[] PROGMEM =          "Codice di errore HTTP: ";
//
#define    INTL_AVG24H_PM25                       "Media 24h PM2,5: "
#define    INTL_AVG24H_PM10                       "Media 24h PM10: "
#define    INTL_PEAK24H_PM25                      "Picco 24h PM2,5: "
#define    INTL_PEAK24H_PM10                      "Picco 24h PM10: "
#define    INTL_QUANT_05UM                        "Quant. 0,5µm: "
#define    INTL_QUANT_1UM                         "Quant. 1µm: "
#define    INTL_QUANT_25UM                        "Quant. 2,5µm: "
#define    INTL_QUANT_4UM                         "Quant. 4µm: "
#define    INTL_QUANT_10UM                        "Quant. 10µm: "
#define    INTL_PART_SIZE                         "Dimensione particelle: "
#define    INTL_TEMPERATURE                       "Temperatura: "
#define    INTL_HUMIDITY                          "Umidità: "
#define    INTL_AIR_PRESS                         "Pressione dell'aria: "
#define    INTL_VOC_INDEX                         "Indice VOC: "
#define    INTL_NOX_INDEX                         "Indice NOx: "
#define    INTL_PEDESTRIANS                       "Pedoni: "
#define    INTL_PER_HOUR                          "/h";
#define    INTL_BIKES                             "Biciclette: "
#define    INTL_CARS                              "Auto: "
#define    INTL_HEAVY                             "Veicoli pesanti: "
#define    INTL_V85_SPEED                         "Velocità V85: "
#define    INTL_KM_PER_HOUR                       "km/h"
//
#define    INTL_DISPLAY                           "Display Sensor.Community"
#define    INTL_BACK_TO_HOME_PAGE                 "Torna alla pagina principale"
#define    INTL_BACK_TO_HOME_PAGE_DISCARD         "Torna alla pagina principale / Annulla modifiche"
#define    INTL_CONFIGURATION_REALLY_DELETE       "Sei sicuro di voler eliminare la configurazione?"
#define    INTL_DELETE                            "Elimina"
#define    INTL_CANCEL                            "Annulla"
#define    INTL_REALLY_RESTART_DISPLAY            "Sei sicuro di voler riavviare il display?"
#define    INTL_RESTART                           "Riavvia"
#define    INTL_UPTIME                            "Tempo di attività del display: "
#define    INTL_READ_UPTO                         "Leggi fino alla posizione: "
#define    INTL_RESET_REASON                      "Motivo del precedente reset: "
#define    INTL_FIRMWARE                          "Firmware: "
const char INTL_SIGNAL_STRENGTH[] PROGMEM =       "intensità del segnale ";
const char INTL_SIGNAL_QUALITY[] PROGMEM =        "qualità del segnale ";
const char INTL_ALERT[] PROGMEM =                 "Avvisi";
#define    INTL_NUMBER_OF_CALLS                   "Numero di chiamate"
#define    INTL_SENSOR                            "Sensore"
#define    INTL_VALUE                             "Valore"
#define    INTL_NOT_MEASURED                      "-- "
#define    INTL_DELETED                           "Eliminato" 
#define    INTL_CANNOT_BE_DELETED                 "Non può essere eliminato"
#define    INTL_NOT_FOUND                         "Non trovato"
#define    INTL_REPORT_ISSUE                      "Segnala un problema"
const char INTL_PM[] PROGMEM =                    "Scegli PM per valori di picco e medi...";
// 
#define    INTL_HOME                              "Home"
const char INTL_CURRENT_DATA[] PROGMEM =          "Dati attuali";
const char INTL_CONFIGURATION[] PROGMEM =         "Configurazione";
const char INTL_ADVANCED_SETTINGS[] PROGMEM =     "Impostazioni avanzate";
const char INTL_DELETE_CONFIG[] PROGMEM =         "Elimina configurazione";
const char INTL_RESTART_DISPLAY[] PROGMEM =       "Riavvia display";
// 
const char INTL_WIFI_SETTINGS[] PROGMEM =         "Impostazioni WiFi";
// 
const char INTL_FS_WIFI_NAME[] PROGMEM =          "Nome rete";
const char INTL_PASSWORD[] PROGMEM =              "Password";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM =    "Impostazioni avanzate (modifica solo se sai cosa stai facendo)";
//
const char INTL_BASICAUTH[] PROGMEM =             " Autenticazione";
const char INTL_USER[] PROGMEM =                  "Utente";
const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM =   "AP in modalità configurazione";
#define    INTL_LOADING_WIFI_NETWORKS             "Caricamento reti WiFi ..."
const char INTL_NO_NETWORKS[] PROGMEM =           "Nessuna rete WiFi trovata";
const char INTL_NETWORKS_FOUND[] PROGMEM =        "Reti WiFi trovate: ";
// 
#define    INTL_WIFI_CONNECTION_LOST              "Connessione persa"
#define    INTL_WIFI_CONNECT_TO                   "Connettiti a:"
#define    INTL_WIFI_SSID                         "SSID: "
#define    INTL_WIFI_WIFI                         "WiFi: " 
#define    INTL_CONFIG_BUSY                       "Config in corso"
#define    INTL_PLEASE_RESTART                    "Per favore riavvia"
// 
const char INTL_LOCATION_0_15[] PROGMEM =         "Posizione 0-15";
const char INTL_LOCATION_16_31[] PROGMEM =        "Posizione 16-31";
const char INTL_LOCATION_NAME[] PROGMEM =         "Nome posizione";
const char INTL_SENSOR_API_1[] PROGMEM =          "API #1 (PM)";
const char INTL_SENSOR_API_2[] PROGMEM =          "API #2 (Temp/Umidità)";
const char INTL_SENSOR_API_3[] PROGMEM =          "API #3 (DNMS)";
const char INTL_SENSOR_API_4[] PROGMEM =          "API #4 (NOx/VOC) (o segmento Telraam)";
// 
const char INTL_DISPLAY_SETTINGS[] PROGMEM =      "Impostazioni display";
const char INTL_DISPLAY_OPTIONS[] PROGMEM =       "Opzioni display";
const char INTL_MULTICOMPARE[] PROGMEM =          " Mostra solo i sensori con valori PM elevati";
const char INTL_SENSORMISSING[] PROGMEM =         " Mostra sensori inattivi";
const char INTL_SHOWPMPM[] PROGMEM =              " Mostra risultati PM";
const char INTL_SHOWPM1PM4[] PROGMEM =            " Mostra valori PM1 & PM4";
const char INTL_SHOWMETEO[] PROGMEM =             " Mostra informazioni meteo";
const char INTL_SHOWGRAPH[] PROGMEM =             " Mostra grafici";
const char INTL_SHOWAQIADVICE[] PROGMEM =         " Mostra consigli AQI";
const char INTL_SHOWWHOADVICE[] PROGMEM =         " Mostra consigli OMS";
const char INTL_MULTIAVERAGE[] PROGMEM =          " Mostra la media di tutti i sensori";
const char INTL_SHOWAVGNPEAK[] PROGMEM =          " Mostra media & picco 24h";
const char INTL_SHOWCOMP[] =                      " Confronta 2 sensori & mostra risultato";
const char INTL_SHOWCOMPINSIDE[] =                " Confronta sensore #2 come interno";
const char INTL_SHOWDNMS[] PROGMEM =              " Mostra dati DNMS";
const char INTL_SHOWTELRAAM[] PROGMEM =           " Mostra dati TELRAAM";
// 
const char INTL_SETTINGS[] PROGMEM =              "Impostazioni generali";
const char INTL_VALUES_TEXT[] PROGMEM =           "Valori e testo";
const char INTL_WELCOME[] PROGMEM =               "Messaggio di benvenuto";
const char INTL_WELCOME2[] PROGMEM =              "Messaggio di benvenuto 2 (alternato)";
const char INTL_CLOCKSECONDS[] PROGMEM =          "Orologio sul display (predefinito 10 sec) (0 = nessun orologio)";
const char INTL_TIMEZONESTR[] PROGMEM =           "Fuso orario (vedi database dei fusi orari su Wikipedia)";
const char INTL_DISPLAYSPEED[] PROGMEM =          "Visualizza tempo di passaggio (predefinito 25 msec)";
const char INTL_PAUSETIME[] PROGMEM =             "Visualizza tempo di pausa (predefinito 5 sec)";
const char INTL_WELCOMEINTERVAL[] PROGMEM =       "Intervallo messaggio di benvenuto (# cicli) (predefinito 10)";
const char INTL_CALLINGINTERVAL[] PROGMEM =       "Intervallo chiamata dati (predefinito 6 min)";
const char INTL_DIFFERENCEPERCENT[] PROGMEM =     "Percentuale di differenza prima della notifica (predefinito 15%)";
const char INTL_DIFFERENCELEVEL[] PROGMEM =       "Livello di differenza prima della notifica (predefinito 2µg/m³)";
const char INTL_SENSORDATATIMEOUT[] PROGMEM =     "Timeout dati sensore (# scansioni perse) (predefinito 10)";
// 
const char INTL_DEBUG_SETTINGS[] PROGMEM =        "Impostazioni di debug";
const char INTL_DEBUGSHOWDATA[] PROGMEM =         " Mostra dati";
const char INTL_DEBUGDISPLAY[] PROGMEM =          " Display"; 
const char INTL_DEBUGCOMMS[] PROGMEM =            " Comunicazione";
const char INTL_DEBUGHEAP[] PROGMEM =             " Heap"; 
const char INTL_DEBUGJSON[] PROGMEM =             " Json";   
// 
const char INTL_PM_PARAMS[] PROGMEM =             "Parametri PM";
const char INTL_URLSENSORCOMM[] PROGMEM =         "URL API Sensor.Community";
const char INTL_WHO_PM25_MAXIMUM[] PROGMEM =      "Massimo PM2,5 OMS (predefinito 5µg/m³)";
const char INTL_WHO_PM10_MAXIMUM[] PROGMEM =      "Massimo PM10 OMS (predefinito 15µg/m³)";
const char INTL_PM25_TO_AQI50[] PROGMEM =         "Conversione PM2,5 in AQI-50 (predefinito 9µg/m³)";
const char INTL_PM10_TO_AQI50[] PROGMEM =         "Conversione PM10 in AQI-50 (predefinito 50µg/m³)";
const char INTL_MAXGRAPH_PM25[] PROGMEM =         "Valore PM2,5 per grafico completo al 200% (predefinito 10µg/m³)";
const char INTL_MAXGRAPH_PM10[] PROGMEM =         "Valore PM10 per grafico completo al 200% (predefinito 30µg/m³)";
const char INTL_COMPARELOCATION[] PROGMEM =       "Confronta posizione (valido = da 0 a 31)";
const char INTL_COMPARELOCATION2[] PROGMEM =      "Confronta posizione 2 (valido = da 0 a 31)";
const char INTL_PMCHOICE[] PROGMEM =              "Dimensione PM per media, picco e grafici (predefinito PM2,5)";
//
const char INTL_AQI_WHO_TABLE[] PROGMEM =         "AQI e OMS";
const char INTL_AQI_TABLE_TITLE[] PROGMEM =       "Traduzione dei livelli AQI in COLORI";
const char INTL_WHO_TABLE_TITLE[] PROGMEM =       "Traduzione dei livelli OMS in COLORI";
// 
const char INTL_MAXAQIGREEN[] PROGMEM =           "Livello massimo per VERDE (predefinito 50)";
const char INTL_MAXAQIYELLOW[] PROGMEM =          "Livello massimo per GIALLO (predefinito 100)";           
const char INTL_MAXAQIORANGE[] PROGMEM =          "Livello massimo per ARANCIONE (predefinito 150)";           
const char INTL_MAXAQIRED[] PROGMEM =             "Livello massimo per ROSSO (predefinito 200)";             
const char INTL_MAXAQIVIOLET[] PROGMEM =          "Livello massimo per VIOLA (predefinito 300)";             
// 
const char INTL_MAXWHOGREEN[] PROGMEM =           "Livello massimo per VERDE (predefinito PM2,5: 9µg/m³)";
const char INTL_MAXWHOYELLOW[] PROGMEM =          "Livello massimo per GIALLO (predefinito PM2,5: 30µg/m³)";           
const char INTL_MAXWHOORANGE[] PROGMEM =          "Livello massimo per ARANCIONE (predefinito PM2,5: 50µg/m³)";           
const char INTL_MAXWHORED[] PROGMEM =             "Livello massimo per ROSSO (predefinito PM2,5: 120µg/m³)";             
const char INTL_MAXWHOVIOLET[] PROGMEM =          "Livello massimo per VIOLA (predefinito PM2,5: 230µg/m³)";             
// 
const char INTL_NOISE_TRAFFIC_TABLE[] PROGMEM =   "RUMORE e TRAFFICO";
const char INTL_NOISE_TABLE_TITLE[] PROGMEM =     "Traduzione dei livelli DNMS LAeq in COLORI";
const char INTL_TRAFFIC_TABLE_TITLE[] PROGMEM =   "Traduzione dei livelli TRAFFICO in COLORI";
// 
const char INTL_MAXLAEQGREEN[] PROGMEM =          "Livello massimo per VERDE (predefinito 60dBA)";
const char INTL_MAXLAEQYELLOW[] PROGMEM =         "Livello massimo per GIALLO (predefinito 75dBA)";           
const char INTL_MAXLAEQORANGE[] PROGMEM =         "Livello massimo per ARANCIONE (predefinito 90dBA)";           
const char INTL_MAXLAEQRED[] PROGMEM =            "Livello massimo per ROSSO (predefinito 100dBA)";             
const char INTL_MAXLAEQVIOLET[] PROGMEM =         "Livello massimo per VIOLA (predefinito 110dBA)";             
const char INTL_MAXLAEQBROWN[] PROGMEM =          "Livello massimo per MARRONE (predefinito 120dBA)"; 
// 
const char INTL_MAXTRAFGREEN[] PROGMEM =          "Livello massimo per VERDE (predefinito 50)";
const char INTL_MAXTRAFYELLOW[] PROGMEM =         "Livello massimo per GIALLO (predefinito 100)";           
const char INTL_MAXTRAFORANGE[] PROGMEM =         "Livello massimo per ARANCIONE (predefinito 200)";           
const char INTL_MAXTRAFRED[] PROGMEM =            "Livello massimo per ROSSO (predefinito 500)";
const char INTL_MAXTRAFCYAN[] PROGMEM =           "Livello massimo per CIANO (predefinito 1000)";            
const char INTL_MAXTRAFVIOLET[] PROGMEM =         "Livello massimo per VIOLA (predefinito 2000)";             
const char INTL_MAXTRAFBROWN[] PROGMEM =          "Livello massimo per MARRONE (predefinito 5000)"; 
// 
const char INTL_TRAFFIC_PARAMS[] PROGMEM =        "TRAFFICO";
// 
const char INTL_TELRAAMAPI[] PROGMEM =            "TELRAAM API URL";
const char INTL_TELRAAMTOKEN[] PROGMEM =          "Gettone TELRAAM";
const char INTL_FREETOKEN[] PROGMEM =             "Gettone GRATUITO (solo per test, mostra i risultati di ieri!)";
const char INTL_SHOWPEDES[] PROGMEM =             " Mostra Pedoni";
const char INTL_SHOWBIKE[] PROGMEM =              " Mostra Biciclette";
const char INTL_SHOWCAR[] PROGMEM =               " Mostra Automobili";
const char INTL_SHOWHEAVY[] PROGMEM =             " Mostra Veicoli pesanti";
const char INTL_SHOWSPEED[] PROGMEM =             " Mostra Velocità V85";

// Word based text system
char *dotMatrixText[] = {
  "µg/m³",                          // 0
  "  ñ ",    
  " Ñ ", 
  "°C", 
  "Temperatura = ",  
  "Umidità = ",                     // 5
  "C'è il ", 
  "% in più", 
  "% in meno ", 
  " che in metri a ", 
  " di particolato in metri a ",    // 10
  "Media su tutti i metri: ",
  "In eccesso: ", 
  "Non collegata:",
  "Picco 24o.= ", 
  "Medio 24o.= ",                   // 15
  " Pressione dell'aria = ",  
  " veicoli pesanti; ",
  " automobile.",  
  " ciclisti; ",
  " pedoni; ",                      // 20
  "Velocità V85: ",
  " km/ora; ",  
  "Traffico: ", 
  "Rumore: ",
  " Massimo: ",                     // 25
  " Minimo: ",   
  " Media: ", 
  "Particolato: ",
  "Tempo atmosferico: ",  
  "Indice COV e NOx: ",             // 30
  "Legge..."
  "Server inattivo...", 
  "Nessuna internet...", 
};  

// Compare strings
char *compareText[] = {  
//"0         1         2         3         4         5         6         7         8         9         0         1"
//"012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890" 
//"==============================================================================================================="
  "La qualità dell'aria interna è peggiore di quella dell'aria esterna - Ventilare!",                            // Outdoor -100%/-30%
  "La qualità dell'aria interna è leggermente peggiore di quella dell'aria esterna.",                            // Outdoor -30%/-10%
  "La qualità dell'aria interna ed esterna è più o meno la stessa.",                                             // Outdoor -10%/+10%
  "La qualità dell'aria interna è leggermente migliore di quella dell'aria esterna.",                            // Outdoor +10%/+30% 
  "La qualità dell'aria interna è migliore dell'aria esterna: chiudi finestre e porte !",                        // Outdoor +30%/+100%
  "La qualità dell'aria interna è molto migliore di quella dell'aria esterna - Chiudi finestre e porte !",       // Outdoor >100%
};

// AQI strings 
char *AQItext[] = {  
  "Indice IQA VERDE: La qualità dell'aria è buona. Non ci sono rischi per la salute.",                   
  "Indice IQA GIALLO: La qualità dell'aria è moderata. Lo standard dell'OMS è stato superato.",           
  "Indice IQA ARANCIONE: L'aria non è salubre per le persone vulnerabili gruppi.",                       
  "Indice IQA ROSSO: L'aria è malsana. Chiunque può riscontrare effetti sulla salute.",                  
  "Indice IQA VIOLA: L'aria è molto malsana. Chiunque può sperimentare gravi effetti sulla salute.",     
};

// WHO strings 
char *WHOtext[] = {  
  "Indice OMS VERDE: Misurata su 24 ore, la qualità dell'aria è buona.",              
  "Indice OMS GIALLO: Misurata su 24 ore, la qualità dell'aria è moderata.",          
  "Indice OMS ARANCIONE: Misurata su 24 ore, la qualità dell'aria è malsana.",        
  "Indice OMS ROSSO: Misurata su 24 ore, la qualità dell'aria è molto malsana.",      
  "Indice OMS VIOLA: Misurata su 24 ore, la qualità dell'aria è pericolosa.",         
};

String dayStr() 
{
	switch(myTZ.weekday()) 
  {
		case 1: return F("Dom.");        
		case 2: return F("Lun.");
		case 3: return F("Mar.");		
		case 4: return F("Mer.");
		case 5: return F("Gio.");
		case 6: return F("Ven.");
		case 7: return F("Sab.");
	}
	return "";
}

#include "airrohr-logo.h"
