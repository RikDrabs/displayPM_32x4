#include <pgmspace.h> 

#define    INTL_LANG                              "ES"  
//
const char INTL_SAVE_CONFIG[] PROGMEM =           "Guardar configuración";
const char INTL_SAVE_RESTART[] PROGMEM =          "Guardar configuración y reiniciar";
const char INTL_WRITECONFIG[] PROGMEM =           "Escribiendo archivos de configuración";
const char INTL_REWRITECONFIG[] PROGMEM =         "Reescribiendo archivos de configuración";
const char INTL_CONFIG_WRITTEN[] PROGMEM =        "Configuración escrita";
const char INTL_WRITESUCCESS[] PROGMEM =          "Escrito con éxito: ";
const char INTL_WRITEFAIL[] PROGMEM =             "Error al abrir para escribir: ";
const char INTL_READCONFIG[] PROGMEM =            "Leyendo archivos de configuración";
const char INTL_OPENFAIL[] PROGMEM =              "Error al abrir para leer: ";
const char INTL_READSUCCESS[] PROGMEM =           "Leído con éxito: ";
const char INTL_FORMATSPIFFS[] PROGMEM =          "Nueva versión detectada, formateando SPIFFS";
const char INTL_JSONPARSING_ERR[] PROGMEM =       "Error al analizar Json de configuración: ";
const char INTL_MOUNT_FS[] PROGMEM =              "Montando sistema de archivos...";
const char INTL_FAILMOUNT_FS[] PROGMEM =          "Error al montar el sistema de archivos";
const char INTL_READAVGNPEAK[] PROGMEM =          "Leyendo valores promedio y pico";
const char INTL_WRITEAVGNPEAK[] PROGMEM =         "Escribiendo valores promedio y pico";
const char INTL_VALREQ_AUTH[] PROGMEM =           "Validando autorización de solicitud...";
const char INTL_AUTH_FAIL[] PROGMEM =             "Error de autenticación";
const char INTL_ESP_RESTART[] PROGMEM =           "Reinicio controlado del ESP";
const char INTL_DISPLAY_IS_REBOOTING[] PROGMEM =  "La pantalla se está reiniciando.";
const char INTL_NOT_REACHED[] PROGMEM =           "¡No debería haberse alcanzado!";
const char INTL_NOT_FOUND_FPSTR[] PROGMEM =       "No encontrado.";
const char INTL_SCANFAIL[] PROGMEM =              "Error al escanear WiFi. Tratándolo como vacío.";
const char INTL_START_WIFI_MAN[] PROGMEM =        "Iniciando WiFiManager";
const char INTL_PASSWORD_DP[] PROGMEM =           "Contraseña: ";
const char INTL_SCANWIFI[] PROGMEM =              "Escaneando redes WiFi...";
const char INTL_TXT_CONNECTING_TO[] PROGMEM =     "Conectando a ";
const char INTL_AP_PASSWORD[] PROGMEM =           "La contraseña del AP es: ";
const char INTL_TELRAAM_HEAP[] PROGMEM =          "TelRaam: no hay suficiente memoria disponible.";
const char INTL_TELRAAM_SEGM[] PROGMEM =          "Segmento de TelRaam = ";
const char INTL_TELRAAM_JSON_ERR[] PROGMEM =      "Error al analizar Json de TelRaam: ";
const char INTL_HEAPCHANGE_FROM[] PROGMEM =       "Cambio de memoria desde ";
const char INTL_HEAPCHANGE_TO[] PROGMEM =         " a ";
const char INTL_HEAPDIFF[] PROGMEM =              " Diferencia = ";
const char INTL_LOWHEAP_RESTART[] PROGMEM =       "Se detectó poca memoria, reinicio controlado.";
const char INTL_LOWHEAP_TELRAAM[] PROGMEM =       "Tiempo de poca memoria excedido para TelRaam, reinicio controlado.";
const char INTL_ENDOFLIST[] PROGMEM =             "Fin de la lista de ubicaciones alcanzado, lectura de sensores detenida hasta tiempo de espera.";
const char INTL_RESUMEREAD[] PROGMEM =            "Reanudando lectura de sensores, tiempo de espera superado.";
const char INTL_ONDISPLAY[] PROGMEM =             "En pantalla: ";
const char INTL_DISPLAYBUFF[] PROGMEM =           "======= Búfer de pantalla ========";
const char INTL_ENDOFBUFF[] PROGMEM =             "========= Fin del búfer ==========";
const char INTL_SELFTEST_FAIL[] PROGMEM =         "Error: ¡PRUEBA AUTOMÁTICA FALLIDA!";
const char INTL_QUAN_LOCATIONS[] PROGMEM =        "Cantidad de ubicaciones definidas: ";
const char INTL_CONNECT_TO[] PROGMEM =            "Conectado a: ";
const char INTL_TIMEZONE[] PROGMEM =              "Zona horaria = ";
const char INTL_TIMEUTC[] PROGMEM =               "Error en la búsqueda de zona horaria, ¡usando UTC!";
const char INTL_LOCAL_IP[] PROGMEM =              "IP local: ";
const char INTL_ENDOF_SETUP[] PROGMEM =           "Fin de la configuración";
const char INTL_SCAN_NUM[] PROGMEM =              "Escaneo # ";
const char INTL_LOC_NAME[] PROGMEM =              " Nombre de ubicación: ";
const char INTL_SENSOR_URL[] PROGMEM =            "Sensor en URL: ";
const char INTL_PMPARSING_ERR[] PROGMEM =         "Error al analizar Json de PM: ";
//
#define    INTL_AVG24H_PM25                       "Promedio 24h PM2,5: "
#define    INTL_AVG24H_PM10                       "Promedio 24h PM10: "
#define    INTL_PEAK24H_PM25                      "Pico 24h PM2,5: "
#define    INTL_PEAK24H_PM10                      "Pico 24h PM10: "
#define    INTL_QUANT_05UM                        "Cantidad 0.5µm: "
#define    INTL_QUANT_1UM                         "Cantidad 1µm: "
#define    INTL_QUANT_25UM                        "Cantidad 2.5µm: "
#define    INTL_QUANT_4UM                         "Cantidad 4µm: "
#define    INTL_QUANT_10UM                        "Cantidad 10µm: "
#define    INTL_PART_SIZE                         "Tamaño de partícula: "
#define    INTL_TEMPERATURE                       "Temperatura: "
#define    INTL_HUMIDITY                          "Humedad: "
#define    INTL_AIR_PRESS                         "Presión atmosférica: "
#define    INTL_VOC_INDEX                         "Índice VOC: "
#define    INTL_NOX_INDEX                         "Índice NOx: "
#define    INTL_PEDESTRIANS                       "Peatones: "
#define    INTL_PER_HOUR                          "/h";
#define    INTL_BIKES                             "Bicicletas: "
#define    INTL_CARS                              "Coches: "
#define    INTL_HEAVY                             "Vehículos pesados: "
#define    INTL_V85_SPEED                         "Velocidad V85: "
#define    INTL_KM_PER_HOUR                       "km/h"
//
#define    INTL_DISPLAY                           "Sensor.Community Display"
#define    INTL_BACK_TO_HOME_PAGE                 "Volver a la página principal"
#define    INTL_BACK_TO_HOME_PAGE_DISCARD         "Descartar cambios"
#define    INTL_CONFIGURATION_REALLY_DELETE       "¿Realmente quieres eliminar la configuración?"
#define    INTL_DELETE                            "Eliminar"
#define    INTL_CANCEL                            "Cancelar"
#define    INTL_REALLY_RESTART_DISPLAY            "¿Realmente quieres reiniciar la pantalla?"
#define    INTL_RESTART                           "Reiniciar"
#define    INTL_UPTIME                            "Tiempo de actividad de la pantalla: "
#define    INTL_READ_UPTO                         "Leer hasta la ubicación: "
#define    INTL_RESET_REASON                      "Razón del reinicio anterior: "
#define    INTL_FIRMWARE                          "Firmware: "
const char INTL_SIGNAL_STRENGTH[] PROGMEM =       "intensidad de la señal ";
const char INTL_SIGNAL_QUALITY[] PROGMEM =        "calidad de la señal ";
const char INTL_ALERT[] PROGMEM =                 "Alertas";
#define    INTL_NUMBER_OF_CALLS                   "Número de llamadas"
#define    INTL_SENSOR                            "Sensor"
#define    INTL_VALUE                             "Valor"
#define    INTL_NOT_MEASURED                      "-- "
#define    INTL_DELETED                           "Eliminado"
#define    INTL_CANNOT_BE_DELETED                 "No se puede eliminar"
#define    INTL_NOT_FOUND                         "No encontrado"
#define    INTL_REPORT_ISSUE                      "Informar de un problema"
const char INTL_PM[] PROGMEM =                    "Elige PM para valores de pico y promedio...";
// 
#define    INTL_HOME                              "Inicio"
const char INTL_CURRENT_DATA[] PROGMEM =          "Últimos valores";
const char INTL_CONFIGURATION[] PROGMEM =         "Configuración";
const char INTL_ADVANCED_SETTINGS[] PROGMEM =     "Configuración avanzada";
const char INTL_DELETE_CONFIG[] PROGMEM =         "Eliminar configuración guardada";
const char INTL_RESTART_DISPLAY[] PROGMEM =       "Reiniciar pantalla";
// 
const char INTL_WIFI_SETTINGS[] PROGMEM =         "Configuración WiFi";
// 
const char INTL_FS_WIFI_NAME[] PROGMEM =          "Nombre de la red";
const char INTL_PASSWORD[] PROGMEM =              "Contraseña";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM =    "Configuración avanzada (cambiar solo si sabe lo que está haciendo)";
//
const char INTL_BASICAUTH[] PROGMEM =             "Autenticación";
const char INTL_USER[] PROGMEM =                  "Usuario";
const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM =   "AP en modo de configuración";
#define    INTL_LOADING_WIFI_NETWORKS             "Cargando redes WiFi ..."
const char INTL_NO_NETWORKS[] PROGMEM =           "No se encontró ninguna red WiFi";
const char INTL_NETWORKS_FOUND[] PROGMEM =        "Redes WiFi encontradas: ";
// 
#define    INTL_WIFI_CONNECTION_LOST              "Conexión WiFi perdida"
#define    INTL_WIFI_CONNECT_TO                   "Por favor, conéctese a:"
#define    INTL_WIFI_SSID                         "SSID: "
#define    INTL_WIFI_WIFI                         "WiFi: " 
#define    INTL_CONFIG_BUSY                       "Configuración ocupada"
#define    INTL_PLEASE_RESTART                    "Por favor, reinicie"
// 
const char INTL_LOCATION_0_15[] PROGMEM =         "Ubicación 0-15";
const char INTL_LOCATION_16_31[] PROGMEM =        "Ubicación 16-31";
const char INTL_LOCATION_NAME[] PROGMEM =         "Nombre de la ubicación";
const char INTL_SENSOR_API_1[] PROGMEM =          "API #1 (PM)";
const char INTL_SENSOR_API_2[] PROGMEM =          "API #2 (Temp/Hum)";
const char INTL_SENSOR_API_3[] PROGMEM =          "API #3 (DNMS)";
const char INTL_SENSOR_API_4[] PROGMEM =          "API #4 (NOx/VOC) (o segmento Telraam)";
// 
const char INTL_DISPLAY_SETTINGS[] PROGMEM =      "Configuración de pantalla";
const char INTL_DISPLAY_OPTIONS[] PROGMEM =       "Opciones de pantalla";
const char INTL_MULTICOMPARE[] PROGMEM =          " Mostrar solo sensores con valores PM altos";
const char INTL_SENSORMISSING[] PROGMEM =         " Mostrar sensores inactivos";
const char INTL_SHOWPMPM[] PROGMEM =              " Mostrar resultados PM";
const char INTL_SHOWPM1PM4[] PROGMEM =            " Mostrar valores PM1 y PM4";
const char INTL_SHOWMETEO[] PROGMEM =             " Mostrar información meteorológica";
const char INTL_SHOWGRAPH[] PROGMEM =             " Mostrar gráficos";
const char INTL_SHOWAQIADVICE[] PROGMEM =         " Mostrar consejo de AQI";
const char INTL_SHOWWHOADVICE[] PROGMEM =         " Mostrar consejo de la OMS";
const char INTL_MULTIAVERAGE[] PROGMEM =          " Mostrar promedio de todos los metros";
const char INTL_SHOWAVGNPEAK[] PROGMEM =          " Mostrar promedio y pico de 24h.";
const char INTL_SHOWCOMP[] =                      " Comparar 2 sensores y mostrar resultado";
const char INTL_SHOWCOMPINSIDE[] =                " Comparar sensor #2 está en interior";
const char INTL_SHOWDNMS[] PROGMEM =              " Mostrar datos de DNMS";
const char INTL_SHOWTELRAAM[] PROGMEM =           " Mostrar datos de TELRAAM";
// 
const char INTL_SETTINGS[] PROGMEM =              "Configuración general";
const char INTL_VALUES_TEXT[] PROGMEM =           "Valores y texto";
const char INTL_WELCOME[] PROGMEM =               "Mensaje de bienvenida";
const char INTL_WELCOME2[] PROGMEM =              "Mensaje de bienvenida 2 (alternativo)";
const char INTL_CLOCKSECONDS[] PROGMEM =          "Reloj en pantalla (predeterminado 10 s) (0 = sin reloj)";
const char INTL_TIMEZONESTR[] PROGMEM =           "Zona horaria (consulte la base de datos de zonas horarias en Wikipedia)";
const char INTL_DISPLAYSPEED[] PROGMEM =          "Mostrar tiempo de paso (predeterminado 25 ms)";
const char INTL_PAUSETIME[] PROGMEM =             "Mostrar tiempo de pausa (predeterminado 5 s)";
const char INTL_WELCOMEINTERVAL[] PROGMEM =       "Intervalo del mensaje de bienvenida (# ciclos) (predeterminado 10)";
const char INTL_CALLINGINTERVAL[] PROGMEM =       "Intervalo de llamada de datos (predeterminado 6 min)";
const char INTL_DIFFERENCEPERCENT[] PROGMEM =     "Porcentaje de diferencia antes de la notificación (predeterminado 15%)";
const char INTL_DIFFERENCELEVEL[] PROGMEM =       "Nivel de diferencia antes de la notificación (predeterminado 2µg/m³)";
const char INTL_SENSORDATATIMEOUT[] PROGMEM =     "Tiempo de espera de datos del sensor (# escaneos perdidos) (predeterminado 10)";
// 
const char INTL_DEBUG_SETTINGS[] PROGMEM =        "Configuración de depuración";
const char INTL_DEBUGSHOWDATA[] PROGMEM =         " Mostrar datos";
const char INTL_DEBUGDISPLAY[] PROGMEM =          " Pantalla"; 
const char INTL_DEBUGCOMMS[] PROGMEM =            " Comunicación";
const char INTL_DEBUGHEAP[] PROGMEM =             " Heap"; 
const char INTL_DEBUGJSON[] PROGMEM =             " Json";   
// 
const char INTL_PM_PARAMS[] PROGMEM =             "Parámetros de PM";
const char INTL_URLSENSORCOMM[] PROGMEM =         "URL de la API de Sensor.Community";
const char INTL_WHO_PM25_MAXIMUM[] PROGMEM =      "Máximo PM2,5 según la OMS (por defecto 5µg/m³)";
const char INTL_WHO_PM10_MAXIMUM[] PROGMEM =      "Máximo PM10 según la OMS (por defecto 15µg/m³)";
const char INTL_PM25_TO_AQI50[] PROGMEM =         "Conversión de PM2.5 a AQI-50 (por defecto 9µg/m³)";
const char INTL_PM10_TO_AQI50[] PROGMEM =         "Conversión de PM10 a AQI-50 (por defecto 50µg/m³)";
const char INTL_MAXGRAPH_PM25[] PROGMEM =         "Valor de PM2.5 para una gráfica completa al 200% (por defecto 10µg/m³)";
const char INTL_MAXGRAPH_PM10[] PROGMEM =         "Valor de PM10 para una gráfica completa al 200% (por defecto 30µg/m³)";
const char INTL_COMPARELOCATION[] PROGMEM =       "Comparar ubicación (válido = 0 a 31)";
const char INTL_COMPARELOCATION2[] PROGMEM =      "Comparar ubicación 2 (válido = 0 a 31)";
const char INTL_PMCHOICE[] PROGMEM =              "Tamaño de PM para promedio, pico y gráficas (por defecto PM2,5)";
// 
const char INTL_PM_HUMI_TABLE[] PROGMEM =         "HUMEDAD";
const char INTL_CORRECTHUMI[] PROGMEM =           " Corregir PM para la humedad";
const char INTL_INTELLIHUMI[] PROGMEM =           " Humedad inteligente entre múltiples medidores";
const char INTL_CORRECTHUMI_TITLE[] PROGMEM =     "Corrección de humedad en PM";
const char INTL_REFERENCE_STATION[] PROGMEM =     "Estación de referencia local";
const char INTL_REFERENCE_NAME[] PROGMEM =        "Nombre de la estación de referencia";
const char INTL_PM_DRYREFERENCE[] PROGMEM =       "API-ID Referencia seca PM";
const char INTL_HUMI_DRYREFERENCE[] PROGMEM =     "API-ID Referencia seca HUMEDAD";
const char INTL_PM_WETREFERENCE[] PROGMEM =       "API-ID Referencia húmeda PM";
const char INTL_HUMI_WETREFERENCE[] PROGMEM =     "API-ID Referencia húmeda HUMEDAD";
// 
const char INTL_AQI_WHO_TABLE[] PROGMEM =         "AQI y OMS";
const char INTL_AQI_TABLE_TITLE[] PROGMEM =       "Traducción de niveles AQI a COLOR";
const char INTL_WHO_TABLE_TITLE[] PROGMEM =       "Traducción de niveles OMS a COLOR";
// 
const char INTL_MAXAQIGREEN[] PROGMEM =           "Nivel máximo para VERDE (por defecto 50)";
const char INTL_MAXAQIYELLOW[] PROGMEM =          "Nivel máximo para AMARILLO (por defecto 100)";           
const char INTL_MAXAQIORANGE[] PROGMEM =          "Nivel máximo para NARANJA (por defecto 150)";           
const char INTL_MAXAQIRED[] PROGMEM =             "Nivel máximo para ROJO (por defecto 200)";             
const char INTL_MAXAQIVIOLET[] PROGMEM =          "Nivel máximo para VIOLETA (por defecto 300)";             
// 
const char INTL_MAXWHOGREEN[] PROGMEM =           "Nivel máximo para VERDE (por defecto PM2,5: 9µg/m³)";
const char INTL_MAXWHOYELLOW[] PROGMEM =          "Nivel máximo para AMARILLO (por defecto PM2,5: 30µg/m³)";           
const char INTL_MAXWHOORANGE[] PROGMEM =          "Nivel máximo para NARANJA (por defecto PM2,5: 50µg/m³)";           
const char INTL_MAXWHORED[] PROGMEM =             "Nivel máximo para ROJO (por defecto PM2,5: 120µg/m³)";             
const char INTL_MAXWHOVIOLET[] PROGMEM =          "Nivel máximo para VIOLETA (por defecto PM2,5: 230µg/m³)";             
// 
const char INTL_NOISE_TRAFFIC_TABLE[] PROGMEM =   "RUIDO y TRÁFICO";
const char INTL_NOISE_TABLE_TITLE[] PROGMEM =     "Traducción de niveles LAeq DNMS a COLOR";
const char INTL_TRAFFIC_TABLE_TITLE[] PROGMEM =   "Traducción de niveles de TRÁFICO a COLOR";
// 
const char INTL_MAXLAEQGREEN[] PROGMEM =          "Nivel máximo para VERDE (por defecto 60dBA)";
const char INTL_MAXLAEQYELLOW[] PROGMEM =         "Nivel máximo para AMARILLO (por defecto 75dBA)";
const char INTL_MAXLAEQORANGE[] PROGMEM =         "Nivel máximo para NARANJA (por defecto 90dBA)";
const char INTL_MAXLAEQRED[] PROGMEM =            "Nivel máximo para ROJO (por defecto 100dBA)";
const char INTL_MAXLAEQVIOLET[] PROGMEM =         "Nivel máximo para VIOLETA (por defecto 110dBA)";
const char INTL_MAXLAEQBROWN[] PROGMEM =          "Nivel máximo para MARRÓN (por defecto 120dBA)"; 
// 
const char INTL_MAXTRAFGREEN[] PROGMEM =          "Nivel máximo para VERDE (por defecto 50)";
const char INTL_MAXTRAFYELLOW[] PROGMEM =         "Nivel máximo para AMARILLO (por defecto 100)";
const char INTL_MAXTRAFORANGE[] PROGMEM =         "Nivel máximo para NARANJA (por defecto 200)";
const char INTL_MAXTRAFRED[] PROGMEM =            "Nivel máximo para ROJO (por defecto 500)";
const char INTL_MAXTRAFCYAN[] PROGMEM =           "Nivel máximo para CIAN (por defecto 1000)";
const char INTL_MAXTRAFVIOLET[] PROGMEM =         "Nivel máximo para VIOLETA (por defecto 2000)";
const char INTL_MAXTRAFBROWN[] PROGMEM =          "Nivel máximo para MARRÓN (por defecto 5000)"; 
// 
const char INTL_TRAFFIC_PARAMS[] PROGMEM =        "TRÁFICO"; 
// 
const char INTL_TELRAAMAPI[] PROGMEM =            "URL de la API Telraam"; 
const char INTL_TELRAAMTOKEN[] PROGMEM =          "TOKEN de Telraam"; 
const char INTL_FREETOKEN[] PROGMEM =             "TOKEN GRATUITO (solo para pruebas, mostrando los resultados de ayer!)";
const char INTL_SHOWPEDES[] PROGMEM =             " Mostrar Peatones";
const char INTL_SHOWBIKE[] PROGMEM =              " Mostrar Bicicletas";
const char INTL_SHOWCAR[] PROGMEM =               " Mostrar Coches";
const char INTL_SHOWHEAVY[] PROGMEM =             " Mostrar Vehiculos pesados";
const char INTL_SHOWSPEED[] PROGMEM =             " Mostrar Velocidad V85";

// Word based text system
char *dotMatrixText[] = {
  "µg/m³",                          // 0
  "  ñ ",               
  " Ñ ",              
  "°C",    
  "Temperatura = ", 
  "Humedad = ",                     // 5
  "Hay un ",  
  "% más ",   
  "% menos ", 
  " que con medidor ", 
  " particulas por metro ",         // 10
  "Promedio de todos los metros: ", 
  "En exceso: ", 
  "No conectado:", 
  "Máximo 24h.= ", 
  "Medio 24h.= ",                   // 15 
  " Presión de aire = ", 
  " vehiculos pesados; ", 
  " carros.", 
  " ciclistas; ",    
  " peatones; ",                    // 20
  "Velocidad V85: ", 
  " km por hora; ",    
  "Tráfico: ", 
  "Ruido: ",   
  " Máximo: ",                      // 25
  " Minimo: ", 
  " Promedio: ", 
  "Materia particulada: ", 
  "Clima: ", 
  "Indice de COV y NOx: ",          // 30
  "Lee datos...",  
};  

// Compare strings
char *compareText[] = {
//"0         1         2         3         4         5         6         7         8         9         0         1"
//"012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
//"==============================================================================================================="
  "La calidad del aire interior es peor que la del aire exterior - ¡Ventile!",                                   // Outdoor -100%/-30%
  "La calidad del aire interior es algo peor que la del aire exterior.",                                         // Outdoor -30%/-10%
  "La calidad del aire interior y exterior es aproximadamente la misma.",                                        // Outdoor -10%/+10%
  "La calidad del aire interior es algo mejor que la del aire exterior.",                                        // Outdoor +10%/+30%
  "La calidad del aire interior es mejor que la del aire exterior. ¡Cierre puertas y ventanas!",                 // Outdoor +30%/+100%
  "La calidad del aire interior es mucho mejor que la del aire exterior. ¡Cierre puertas y ventanas!",           // Outdoor >100%
};

// AQI strings
char *AQItext[] = {
//"0         1         2         3         4         5         6         7         8         9         0         1"
//"012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
//"==============================================================================================================="  
  "ICA index VERDE: La calidad del aire es buena. No hay riesgos para la salud.",                      
  "ICA index AMARILLO: La calidad del aire es moderada. Se ha superado el estándar de la OMS.",        
  "ICA index NARANJA: El aire no es saludable para los grupos vulnerables.",                           
  "ICA index ROJO: El aire no es saludable. Cualquiera puede experimentar efectos sobre la salud.",    
  "ICA index VIOLETA: El aire es muy insalubre. Cualquiera puede experimentar efectos sobre la salud.",
};

// WHO strings
char *WHOtext[] = {
//"0         1         2         3         4         5         6         7         8         9         0         1"
//"012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
//"==============================================================================================================="  
  "Índice VERDE de la OMS: La calidad del aire las 24h. es buena.",                                    
  "Índice AMARILLO de la OMS: La calidad del aire las 24h. es moderada.",                
  "Índice NARANJA de la OMS: La calidad del aire las 24h. es no saludable.",             
  "Índice ROJO de la OMS: La calidad del aire las 24h. es muy insalubre.",               
  "Índice VIOLETA de la OMS: La calidad del aire las 24h. es peligrosa.",                
};

String dayStr() 
{
	switch(myTZ.weekday()) 
  {
		case 1: return F("Dom.");        
		case 2: return F("Lun.");
		case 3: return F("Mar.");		
		case 4: return F("Mie.");
		case 5: return F("Jue.");
		case 6: return F("Vie.");
		case 7: return F("Sab.");
	}
	return "";	
}

#include "airrohr-logo.h"
