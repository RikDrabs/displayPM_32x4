#include <pgmspace.h> 

#define    INTL_LANG                              "FR"  
//
const char INTL_SAVE_CONFIG[] PROGMEM =           "Enregistrer la configuration";
const char INTL_SAVE_RESTART[] PROGMEM =          "Enregistrer la configuration et redémarrer";
const char INTL_WRITECONFIG[] PROGMEM =           "Écriture des fichiers de configuration";
const char INTL_REWRITECONFIG[] PROGMEM =         "Réécriture des fichiers de configuration";
const char INTL_CONFIG_WRITTEN[] PROGMEM =        "Configuration enregistrée";
const char INTL_WRITESUCCESS[] PROGMEM =          "Enregistré avec succès: ";
const char INTL_WRITEFAIL[] PROGMEM =             "Échec de l'ouverture en écriture: ";
const char INTL_READCONFIG[] PROGMEM =            "Lecture des fichiers de configuration";
const char INTL_OPENFAIL[] PROGMEM =              "Échec de l'ouverture en lecture: ";
const char INTL_READSUCCESS[] PROGMEM =           "Lecture réussie: ";
const char INTL_FORMATSPIFFS[] PROGMEM =          "Nouvelle version détectée, formatage de SPIFFS";
const char INTL_JSONPARSING_ERR[] PROGMEM =       "Erreur d'analyse JSON de la configuration: ";
const char INTL_MOUNT_FS[] PROGMEM =              "Montage du système de fichiers...";
const char INTL_FAILMOUNT_FS[] PROGMEM =          "Échec du montage du système de fichiers";
const char INTL_READAVGNPEAK[] PROGMEM =          "Lecture des valeurs moyennes et de pointe";
const char INTL_WRITEAVGNPEAK[] PROGMEM =         "Écriture des valeurs moyennes et de pointe";
const char INTL_VALREQ_AUTH[] PROGMEM =           "Validation de l'autorisation de la requête...";
const char INTL_AUTH_FAIL[] PROGMEM =             "Échec de l'authentification";
const char INTL_ESP_RESTART[] PROGMEM =           "Redémarrage contrôlé de l'ESP";
const char INTL_DISPLAY_IS_REBOOTING[] PROGMEM =  "L'affichage redémarre.";
const char INTL_NOT_REACHED[] PROGMEM =           "Ne devrait pas être atteint !!!";
const char INTL_NOT_FOUND_FPSTR[] PROGMEM =       "Non trouvé.";
const char INTL_SCANFAIL[] PROGMEM =              "Échec du scan WiFi. Considéré comme vide.";
const char INTL_START_WIFI_MAN[] PROGMEM =        "Démarrage de WiFiManager";
const char INTL_PASSWORD_DP[] PROGMEM =           "Mot de passe: ";
const char INTL_SCANWIFI[] PROGMEM =              "Recherche des réseaux WiFi...";
const char INTL_TXT_CONNECTING_TO[] PROGMEM =     "Connexion à ";
const char INTL_AP_PASSWORD[] PROGMEM =           "Le mot de passe du point d'accès est: ";
const char INTL_TELRAAM_HEAP[] PROGMEM =          "TelRaam: mémoire disponible insuffisante.";
const char INTL_TELRAAM_SEGM[] PROGMEM =          "Segment TelRaam = ";
const char INTL_TELRAAM_JSON_ERR[] PROGMEM =      "Erreur d'analyse JSON de TelRaam: ";
const char INTL_HEAPCHANGE_FROM[] PROGMEM =       "Changement de mémoire de ";
const char INTL_HEAPCHANGE_TO[] PROGMEM =         " à ";
const char INTL_HEAPDIFF[] PROGMEM =              " Différence = ";
const char INTL_LOWHEAP_RESTART[] PROGMEM =       "Mémoire insuffisante détectée, redémarrage contrôlé.";
const char INTL_LOWHEAP_TELRAAM[] PROGMEM =       "Temps de mémoire insuffisante dépassé pour TelRaam, redémarrage contrôlé.";
const char INTL_ENDOFLIST[] PROGMEM =             "Fin de la liste des emplacements atteinte, arrêt de la lecture des capteurs jusqu'à expiration du délai.";
const char INTL_RESUMEREAD[] PROGMEM =            "Reprise de la lecture des capteurs, délai écoulé.";
const char INTL_ONDISPLAY[] PROGMEM =             "Sur l'écran: ";
const char INTL_DISPLAYBUFF[] PROGMEM =           "======= Mémoire tampon de l'écran =========";
const char INTL_ENDOFBUFF[] PROGMEM =             "======= Fin de la mémoire tampon ==========";
const char INTL_SELFTEST_FAIL[] PROGMEM =         "Erreur: AUTOTEST ÉCHOUÉ !";
const char INTL_QUAN_LOCATIONS[] PROGMEM =        "Nombre d'emplacements définis: ";
const char INTL_CONNECT_TO[] PROGMEM =            "Connecté à: ";
const char INTL_TIMEZONE[] PROGMEM =              "Fuseau horaire = ";
const char INTL_TIMEUTC[] PROGMEM =               "Échec de la recherche du fuseau horaire, utilisation de l'UTC !";
const char INTL_LOCAL_IP[] PROGMEM =              "IP locale: ";
const char INTL_ENDOF_SETUP[] PROGMEM =           "Fin de la configuration";
const char INTL_SCAN_NUM[] PROGMEM =              "Scan# ";
const char INTL_LOC_NAME[] PROGMEM =              " Nom de l'emplacement: ";
const char INTL_SENSOR_URL[] PROGMEM =            "Capteur @URL: ";
const char INTL_PMPARSING_ERR[] PROGMEM =         "Erreur d'analyse JSON PM: ";
const char INTL_HTTPCODE_ERR[] PROGMEM =          "Code d'erreur HTTP: ";
//
#define    INTL_AVG24H_PM25                       "Moyenne 24h PM2,5: "
#define    INTL_AVG24H_PM10                       "Moyenne 24h PM10: "
#define    INTL_PEAK24H_PM25                      "Pic 24h PM2,5: "
#define    INTL_PEAK24H_PM10                      "Pic 24h PM10: "
#define    INTL_QUANT_05UM                        "Quantité 0,5µm: "
#define    INTL_QUANT_1UM                         "Quantité 1µm: "
#define    INTL_QUANT_25UM                        "Quantité 2,5µm: "
#define    INTL_QUANT_4UM                         "Quantité 4µm: "
#define    INTL_QUANT_10UM                        "Quantité 10µm: "
#define    INTL_PART_SIZE                         "Taille des particules: "
#define    INTL_TEMPERATURE                       "Température: "
#define    INTL_HUMIDITY                          "Humidité: "
#define    INTL_AIR_PRESS                         "Pression de l'air: "
#define    INTL_VOC_INDEX                         "Indice VOC: "
#define    INTL_NOX_INDEX                         "Indice NOx: "
#define    INTL_PEDESTRIANS                       "Piétons: "
#define    INTL_PER_HOUR                          "/h";
#define    INTL_BIKES                             "Vélos: "
#define    INTL_CARS                              "Voitures: "
#define    INTL_HEAVY                             "Véhicules lourds: "
#define    INTL_V85_SPEED                         "Vitesse V85: "
#define    INTL_KM_PER_HOUR                       "km/h"
//
#define    INTL_DISPLAY                           "Écran Sensor.Community"
#define    INTL_BACK_TO_HOME_PAGE                 "Retour à la page d'accueil"
#define    INTL_BACK_TO_HOME_PAGE_DISCARD         "Retour à la page d'accueil / Annuler les modifications"
#define    INTL_CONFIGURATION_REALLY_DELETE       "Voulez-vous vraiment supprimer la configuration ?"
#define    INTL_DELETE                            "Supprimer"
#define    INTL_CANCEL                            "Annuler"
#define    INTL_REALLY_RESTART_DISPLAY            "Voulez-vous vraiment redémarrer l'écran ?"
#define    INTL_RESTART                           "Redémarrer"
#define    INTL_UPTIME                            "Temps de fonctionnement de l'écran: "
#define    INTL_READ_UPTO                         "Lu jusqu'à l'emplacement: "
#define    INTL_RESET_REASON                      "Raison du dernier redémarrage: "
#define    INTL_FIRMWARE                          "Firmware: "
const char INTL_SIGNAL_STRENGTH[] PROGMEM =       "force du signal ";
const char INTL_SIGNAL_QUALITY[] PROGMEM =        "qualité du signal ";
const char INTL_ALERT[] PROGMEM =                 "Alertes";
#define    INTL_NUMBER_OF_CALLS                   "Nombre d'appels"
#define    INTL_SENSOR                            "Capteur"
#define    INTL_VALUE                             "Valeur"
#define    INTL_NOT_MEASURED                      "-- "
#define    INTL_DELETED                           "Supprimé" 
#define    INTL_CANNOT_BE_DELETED                 "Impossible de supprimer"
#define    INTL_NOT_FOUND                         "Non trouvé"
#define    INTL_REPORT_ISSUE                      "Signaler un problème"
const char INTL_PM[] PROGMEM =                    "Choisissez PM pour les valeurs de pic et de moyenne...";
// 
#define    INTL_HOME                              "Home"
const char INTL_CURRENT_DATA[] PROGMEM =          "Données actuelles";
const char INTL_CONFIGURATION[] PROGMEM =         "Configuration";
const char INTL_ADVANCED_SETTINGS[] PROGMEM =     "Paramètres avancés";
const char INTL_DELETE_CONFIG[] PROGMEM =         "Supprimer la configuration";
const char INTL_RESTART_DISPLAY[] PROGMEM =       "Redémarrer l'affichage";
// 
const char INTL_WIFI_SETTINGS[] PROGMEM =         "Paramètres WiFi";
// 
const char INTL_FS_WIFI_NAME[] PROGMEM =          "Nom du réseau";
const char INTL_PASSWORD[] PROGMEM =              "Mot de passe";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM =    "Paramètres avancés (modifiez uniquement si vous savez ce que vous faites)";
//
const char INTL_BASICAUTH[] PROGMEM =             " Authentification";
const char INTL_USER[] PROGMEM =                  "Utilisateur";
const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM =   "AP en mode configuration";
#define    INTL_LOADING_WIFI_NETWORKS             "Chargement des réseaux WiFi ..."
const char INTL_NO_NETWORKS[] PROGMEM =           "Aucun réseau WiFi trouvé";
const char INTL_NETWORKS_FOUND[] PROGMEM =        "Réseaux WiFi trouvés:";
// 
#define    INTL_WIFI_CONNECTION_LOST              "Connection perdue"
#define    INTL_WIFI_CONNECT_TO                   "Veuillez vous connecter à:"
#define    INTL_WIFI_SSID                         "SSID: "
#define    INTL_WIFI_WIFI                         "WiFi: " 
#define    INTL_CONFIG_BUSY                       "Config en cours"
#define    INTL_PLEASE_RESTART                    "Veuillez redémarrer"
// 
const char INTL_LOCATION_0_15[] PROGMEM =         "Emplacement 0-15";
const char INTL_LOCATION_16_31[] PROGMEM =        "Emplacement 16-31";
const char INTL_LOCATION_NAME[] PROGMEM =         "Nom de l'emplacement";
const char INTL_SENSOR_API_1[] PROGMEM =          "API #1 (PM)";
const char INTL_SENSOR_API_2[] PROGMEM =          "API #2 (Temp/Hum)";
const char INTL_SENSOR_API_3[] PROGMEM =          "API #3 (DNMS)";
const char INTL_SENSOR_API_4[] PROGMEM =          "API #4 (NOx/VOC) (ou segment Telraam)";
// 
const char INTL_DISPLAY_SETTINGS[] PROGMEM =      "Paramètres d'affichage";
const char INTL_DISPLAY_OPTIONS[] PROGMEM =       "Options d'affichage";
const char INTL_MULTICOMPARE[] PROGMEM =          " Afficher uniquement les capteurs avec dépassement PM";
const char INTL_SENSORMISSING[] PROGMEM =         " Afficher les capteurs inactifs";
const char INTL_SHOWPMPM[] PROGMEM =              " Afficher les résultats PM";
const char INTL_SHOWPM1PM4[] PROGMEM =            " Afficher les valeurs PM1 et PM4";
const char INTL_SHOWMETEO[] PROGMEM =             " Afficher les informations météo";
const char INTL_SHOWGRAPH[] PROGMEM =             " Afficher les graphiques";
const char INTL_SHOWAQIADVICE[] PROGMEM =         " Afficher les conseils AQI";
const char INTL_SHOWWHOADVICE[] PROGMEM =         " Afficher les conseils de l'OMS";
const char INTL_MULTIAVERAGE[] PROGMEM =          " Afficher la moyenne de tous les capteurs";
const char INTL_SHOWAVGNPEAK[] PROGMEM =          " Afficher la moyenne et le pic sur 24h";
const char INTL_SHOWCOMP[] =                      " Comparer deux capteurs et afficher le résultat";
const char INTL_SHOWCOMPINSIDE[] =                " Comparer le capteur #2 est à l'intérieur";
const char INTL_SHOWDNMS[] PROGMEM =              " Afficher les données DNMS";
const char INTL_SHOWTELRAAM[] PROGMEM =           " Afficher les données TELRAAM";
// 
const char INTL_SETTINGS[] PROGMEM =              "Paramètres généraux";
const char INTL_VALUES_TEXT[] PROGMEM =           "Valeurs et texte";
const char INTL_WELCOME[] PROGMEM =               "Message de bienvenue";
const char INTL_WELCOME2[] PROGMEM =              "Message de bienvenue 2 (en alternance)";
const char INTL_CLOCKSECONDS[] PROGMEM =          "Horloge affichée (par défaut 10 sec) (0 = pas d'horloge)";
const char INTL_TIMEZONESTR[] PROGMEM =           "Fuseau horaire (voir la base de données des fuseaux horaires sur Wikipédia)";
const char INTL_DISPLAYSPEED[] PROGMEM =          "Afficher le temps de l'étape (par défaut 25 ms)";
const char INTL_PAUSETIME[] PROGMEM =             "Afficher le temps de pause (par défaut 5 sec)";
const char INTL_WELCOMEINTERVAL[] PROGMEM =       "Intervalle entre le message de bienvenue (nombre de cycles) (par défaut 10)";
const char INTL_CALLINGINTERVAL[] PROGMEM =       "Intervalle d'appel des données (par défaut 6 min)";
const char INTL_DIFFERENCEPERCENT[] PROGMEM =     "Pourcentage de différence avant notification (par défaut 15%)";
const char INTL_DIFFERENCELEVEL[] PROGMEM =       "Niveau de différence avant notification (par défaut 2µg/m³)";
const char INTL_SENSORDATATIMEOUT[] PROGMEM =     "Délai d'expiration des données du capteur (nombre d'analyses manquées) (par défaut 10)";
// 
const char INTL_DEBUG_SETTINGS[] PROGMEM =        "Paramètres de débogage";
const char INTL_DEBUGSHOWDATA[] PROGMEM =         " Afficher les données";
const char INTL_DEBUGDISPLAY[] PROGMEM =          " Affichage"; 
const char INTL_DEBUGCOMMS[] PROGMEM =            " Communication";
const char INTL_DEBUGHEAP[] PROGMEM =             " Mémoire"; 
const char INTL_DEBUGJSON[] PROGMEM =             " Json";   
// 
const char INTL_PM_PARAMS[] PROGMEM =             "Paramètres PM";
const char INTL_URLSENSORCOMM[] PROGMEM =         "URL de l'API Sensor.Community";
const char INTL_WHO_PM25_MAXIMUM[] PROGMEM =      "Maximum PM2,5 de l'OMS (par défaut 5µg/m³)";
const char INTL_WHO_PM10_MAXIMUM[] PROGMEM =      "Maximum PM10 de l'OMS (par défaut 15µg/m³)";
const char INTL_PM25_TO_AQI50[] PROGMEM =         "Conversion PM2,5 vers AQI-50 (par défaut 9µg/m³)";
const char INTL_PM10_TO_AQI50[] PROGMEM =         "Conversion PM10 vers AQI-50 (par défaut 50µg/m³)";
const char INTL_MAXGRAPH_PM25[] PROGMEM =         "Valeur PM2,5 pour un affichage graphique complet à 200 % (par défaut 10µg/m³)";
const char INTL_MAXGRAPH_PM10[] PROGMEM =         "Valeur PM10 pour un affichage graphique complet à 200 % (par défaut 30µg/m³)";
const char INTL_COMPARELOCATION[] PROGMEM =       "Comparer l'emplacement (valide = 0 à 31)";
const char INTL_COMPARELOCATION2[] PROGMEM =      "Comparer l'emplacement 2 (valide = 0 à 31)";
const char INTL_PMCHOICE[] PROGMEM =              "Taille de PM pour moyenne, pic et graphiques (par défaut PM2,5)";
// 
const char INTL_AQI_WHO_TABLE[] PROGMEM =         "AQI et OMS";
const char INTL_AQI_TABLE_TITLE[] PROGMEM =       "Traduction des niveaux AQI en COULEUR";
const char INTL_WHO_TABLE_TITLE[] PROGMEM =       "Traduction des niveaux OMS en COULEUR";
// 
const char INTL_MAXAQIGREEN[] PROGMEM =           "Niveau maximum pour VERT (par défaut 50)";
const char INTL_MAXAQIYELLOW[] PROGMEM =          "Niveau maximum pour JAUNE (par défaut 100)";           
const char INTL_MAXAQIORANGE[] PROGMEM =          "Niveau maximum pour ORANGE (par défaut 150)";           
const char INTL_MAXAQIRED[] PROGMEM =             "Niveau maximum pour ROUGE (par défaut 200)";             
const char INTL_MAXAQIVIOLET[] PROGMEM =          "Niveau maximum pour VIOLET (par défaut 300)";             
// 
const char INTL_MAXWHOGREEN[] PROGMEM =           "Niveau maximum pour VERT (par défaut PM2,5: 9µg/m³)";
const char INTL_MAXWHOYELLOW[] PROGMEM =          "Niveau maximum pour JAUNE (par défaut PM2,5: 30µg/m³)";           
const char INTL_MAXWHOORANGE[] PROGMEM =          "Niveau maximum pour ORANGE (par défaut PM2,5: 50µg/m³)";           
const char INTL_MAXWHORED[] PROGMEM =             "Niveau maximum pour ROUGE (par défaut PM2,5: 120µg/m³)";             
const char INTL_MAXWHOVIOLET[] PROGMEM =          "Niveau maximum pour VIOLET (par défaut PM2,5: 230µg/m³)";             
// 
const char INTL_NOISE_TRAFFIC_TABLE[] PROGMEM =   "BRUIT et TRAFIC";
const char INTL_NOISE_TABLE_TITLE[] PROGMEM =     "Traduction des niveaux DNMS LAeq en COULEUR";
const char INTL_TRAFFIC_TABLE_TITLE[] PROGMEM =   "Traduction des niveaux de TRAFIC en COULEUR";
// 
const char INTL_MAXLAEQGREEN[] PROGMEM =          "Niveau maximum pour VERT (par défaut 60dBA)";
const char INTL_MAXLAEQYELLOW[] PROGMEM =         "Niveau maximum pour JAUNE (par défaut 75dBA)";           
const char INTL_MAXLAEQORANGE[] PROGMEM =         "Niveau maximum pour ORANGE (par défaut 90dBA)";           
const char INTL_MAXLAEQRED[] PROGMEM =            "Niveau maximum pour ROUGE (par défaut 100dBA)";             
const char INTL_MAXLAEQVIOLET[] PROGMEM =         "Niveau maximum pour VIOLET (par défaut 110dBA)";             
const char INTL_MAXLAEQBROWN[] PROGMEM =          "Niveau maximum pour MARRON (par défaut 120dBA)"; 
// 
const char INTL_MAXTRAFGREEN[] PROGMEM =          "Niveau maximum pour VERT (par défaut 50)";
const char INTL_MAXTRAFYELLOW[] PROGMEM =         "Niveau maximum pour JAUNE (par défaut 100)";           
const char INTL_MAXTRAFORANGE[] PROGMEM =         "Niveau maximum pour ORANGE (par défaut 200)";           
const char INTL_MAXTRAFRED[] PROGMEM =            "Niveau maximum pour ROUGE (par défaut 500)";
const char INTL_MAXTRAFCYAN[] PROGMEM =           "Niveau maximum pour CYAN (par défaut 1000)";            
const char INTL_MAXTRAFVIOLET[] PROGMEM =         "Niveau maximum pour VIOLET (par défaut 2000)";             
const char INTL_MAXTRAFBROWN[] PROGMEM =          "Niveau maximum pour MARRON (par défaut 5000)"; 
// 
const char INTL_TRAFFIC_PARAMS[] PROGMEM =        "TRAFIC";
// 
const char INTL_TELRAAMAPI[] PROGMEM =            "URL de l'API Telraam";
const char INTL_TELRAAMTOKEN[] PROGMEM =          "TOKEN Telraam";
const char INTL_FREETOKEN[] PROGMEM =             "TOKEN GRATUIT (pour test seulement, montrant les résultats d'hier !)";
const char INTL_SHOWPEDES[] PROGMEM =             " Afficher Piétons";
const char INTL_SHOWBIKE[] PROGMEM =              " Afficher Vélos";
const char INTL_SHOWCAR[] PROGMEM =               " Afficher Voitures";
const char INTL_SHOWHEAVY[] PROGMEM =             " Afficher Vehicules lourds";
const char INTL_SHOWSPEED[] PROGMEM =             " Afficher Vitesse V85";

// Word based text system
char *dotMatrixText[] = { 
  "µg/m³",                          // 0   
  "  ñ ",   
  " Ñ ",   
  "°C",
  "Température = ",   
  "Humidité = ",                    // 5 
  "Il y a ",    
  "% plus de particules fines ",    
  "% moins de particules fines ", 
  " qu'aux environs de ",   
  " aux environs de ",              // 10 
  "Moyenne de toutes les mesures: ",
  "En dépassement: ", 
  "Pas connecté:", 
  "Pointe 24h.= ", 
  "Moyenne 24h.= ",                 // 15
  " Pression atmos. = ",
  " véhicules lourds; ", 
  " voitures.",  
  " cyclistes; ", 
  " piétons; ",                     // 20
  "Vitesse V85: ",
  " km/h; ",        
  "Trafic: ", 
  "Bruit: ",  
  " Maximum: ",                     // 25
  " Minimum: ",  
  " Moyenne: ", 
  "Particules fines: ", 
  "Météo: ", 
  "Indice COV & NOx: ",             // 30
  "Lecture...",
  "Serveur en panne...", 
  "Pas d'internet...",
};  

// Compare strings 
char *compareText[] = {
//"0         1         2         3         4         5         6         7         8         9         0         1"
//"012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"   
//"==============================================================================================================="
  "La qualité de l'air interieure est plus mauvaise que celle de l'air exterieure - Ventiler!",                  // Outdoor -100%/-30%
  "La qualité de l'air interieure est un peu plus mauvaise que celle de l'air exterieure.",                      // Outdoor -30%/-10%
  "Les qualités de l'air interieure et de l'air exterieure sont à peu près égales.",                             // Outdoor -10%/+10%
  "La qualité de l'air interieure est un peu plus meilleure que celle de l'air extérieure.",                     // Outdoor +10%/+30%
  "La qualité de l'air interieure est meilleure que celle de l'air extérieure - Fermer portes et fenêtres !",    // Outdoor +30%/+100%
  "La qualité de l'air interieure est meilleure que celle de l'air extérieure - Fermer portes et fenêtres !",    // Outdoor >100%
};

// AQI strings 
char *AQItext[] = {
  "Indice IQA VERT: La qualité de l'air est bonne. Il n'y a pas de risque pour la santé.",                      
  "Indice IQA JAUNE: La qualité de l'air est médiocre. Les normes OMS sont dépassées.",                         
  "Indice IQA ORANGE: La qualité de l'air peut provoquer des problèmes de santé aux personnes sensibles.",      
  "Indice IQA ROUGE: La qualité de l'air est malsaine. Tout le monde peut subir des effets de santé.",          
  "Indice IQA VIOLET: La qualité de l'air est très malsaine. Tout le monde peut subir des effets de santé graves.",    
};

// WHO strings 
char *WHOtext[] = {
  "Indice OMS VERT: La qualité de l'air sur 24h. est bonne.",                                   
  "Indice OMS JAUNE: La qualité de l’air sur 24h. est modérée.",                                
  "Indice OMS ORANGE: La qualité de l'air sur 24h. est malsaine.",                              
  "Indice OMS ROUGE: La qualité de l’air sur 24h. est très malsaine.",                          
  "Indice OMS VIOLET: La qualité de l’air sur 24h. est dangereuse.",                            
};

String dayStr() 
{
	switch(myTZ.weekday()) 
  {
		case 1: return F("Dim.");        
		case 2: return F("Lun.");
		case 3: return F("Mar.");		
		case 4: return F("Mer.");
		case 5: return F("Jeu.");
		case 6: return F("Ven.");
		case 7: return F("Sam.");
	}
	return "";
}

#include "airrohr-logo.h"
