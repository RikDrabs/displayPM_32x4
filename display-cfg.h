

// This file is generated, please do not edit.
// Change display-cfg.h.py instead.

enum ConfigEntryType : unsigned short {
	Config_Type_Bool,
	Config_Type_UInt,
	Config_Type_Time,
	Config_Type_String,
	Config_Type_Password,	
};

struct ConfigShapeEntry {
	enum ConfigEntryType cfg_type;
	unsigned short cfg_len;
	const char* _cfg_key;
	union {
	  void* as_void;
	  bool* as_bool;
	  unsigned int* as_uint;
	  char* as_str;
	} cfg_val;
	const __FlashStringHelper* cfg_key() const { return FPSTR(_cfg_key); }
};

enum ConfigShapeId {
	Config_pauseTime,
	Config_displaySpeed,
	Config_callingInterval,
	Config_welkomInterval,
	Config_differencePercent,
	Config_differenceLevel,
	Config_sensordataTimeout,
	Config_clockSeconds,
	Config_pmChoice,
	Config_maxgraphPM10,
	Config_maxgraphPM25,
	Config_max25WHO,
	Config_max10WHO,
	Config_PM25toAQI50,
	Config_PM10toAQI50,
	Config_compareLocation,
	Config_compareLocation2,
	Config_maxLAeqGreen,
	Config_maxLAeqYellow,
	Config_maxLAeqOrange,
	Config_maxLAeqRed,
	Config_maxLAeqViolet,
	Config_maxLAeqBrown,
	Config_maxAqiGreen,
	Config_maxAqiYellow,
	Config_maxAqiOrange,
	Config_maxAqiRed,
	Config_maxAqiViolet,
	Config_maxWhoGreen,
	Config_maxWhoYellow,
	Config_maxWhoOrange,
	Config_maxWhoRed,
	Config_maxWhoViolet,
	Config_maxTrafGreen,
	Config_maxTrafYellow,
	Config_maxTrafOrange,
	Config_maxTrafRed,
	Config_maxTrafCyan,
	Config_maxTrafViolet,
	Config_maxTrafBrown,
	Config_multiCompare,
	Config_showPmPm,
	Config_showPm1Pm4,
	Config_showMeteo,
	Config_intelliHumi,
	Config_correctHumi,
	Config_showGraph,
	Config_showAvgNpeak,
	Config_showComp,
	Config_showCompInside,
	Config_showAqiAdvice,
	Config_showWhoAdvice,
	Config_showDnms,
	Config_showVoc,
	Config_showTelRaam,
	Config_showPedes,
	Config_showBike,
	Config_showCar,
	Config_showHeavy,
	Config_showSpeed,
	Config_sensorMissing,
	Config_multiAverage,
	Config_debugShowData,
	Config_debugDisplay,
	Config_debugComms,
	Config_debugHeap,
	Config_debugJson,
	Config_www_basicauth_enabled,
	Config_freeToken,
	Config_wlanpwd,
	Config_fs_pwd,
	Config_www_password,
	Config_wlanssid,
	Config_www_username,
	Config_fs_ssid,
	Config_welkom,
	Config_welkom2,
	Config_timeZoneStr,
	Config_sensorApi,
	Config_telraamApi,
	Config_telraamToken,
	Config_sensorLoc_0,
	Config_sensorApi1_0,
	Config_sensorApi2_0,
	Config_sensorApi3_0,
	Config_sensorApi4_0,
	Config_sensorLoc_1,
	Config_sensorApi1_1,
	Config_sensorApi2_1,
	Config_sensorApi3_1,
	Config_sensorApi4_1,
	Config_sensorLoc_2,
	Config_sensorApi1_2,
	Config_sensorApi2_2,
	Config_sensorApi3_2,
	Config_sensorApi4_2,
	Config_sensorLoc_3,
	Config_sensorApi1_3,
	Config_sensorApi2_3,
	Config_sensorApi3_3,
	Config_sensorApi4_3,
	Config_sensorLoc_4,
	Config_sensorApi1_4,
	Config_sensorApi2_4,
	Config_sensorApi3_4,
	Config_sensorApi4_4,
	Config_sensorLoc_5,
	Config_sensorApi1_5,
	Config_sensorApi2_5,
	Config_sensorApi3_5,
	Config_sensorApi4_5,
	Config_sensorLoc_6,
	Config_sensorApi1_6,
	Config_sensorApi2_6,
	Config_sensorApi3_6,
	Config_sensorApi4_6,
	Config_sensorLoc_7,
	Config_sensorApi1_7,
	Config_sensorApi2_7,
	Config_sensorApi3_7,
	Config_sensorApi4_7,
	Config_sensorLoc_8,
	Config_sensorApi1_8,
	Config_sensorApi2_8,
	Config_sensorApi3_8,
	Config_sensorApi4_8,
	Config_sensorLoc_9,
	Config_sensorApi1_9,
	Config_sensorApi2_9,
	Config_sensorApi3_9,
	Config_sensorApi4_9,
	Config_sensorLoc_10,
	Config_sensorApi1_10,
	Config_sensorApi2_10,
	Config_sensorApi3_10,
	Config_sensorApi4_10,
	Config_sensorLoc_11,
	Config_sensorApi1_11,
	Config_sensorApi2_11,
	Config_sensorApi3_11,
	Config_sensorApi4_11,
	Config_sensorLoc_12,
	Config_sensorApi1_12,
	Config_sensorApi2_12,
	Config_sensorApi3_12,
	Config_sensorApi4_12,
	Config_sensorLoc_13,
	Config_sensorApi1_13,
	Config_sensorApi2_13,
	Config_sensorApi3_13,
	Config_sensorApi4_13,
	Config_sensorLoc_14,
	Config_sensorApi1_14,
	Config_sensorApi2_14,
	Config_sensorApi3_14,
	Config_sensorApi4_14,
	Config_sensorLoc_15,
	Config_sensorApi1_15,
	Config_sensorApi2_15,
	Config_sensorApi3_15,
	Config_sensorApi4_15,
	Config_sensorLoc_16,
	Config_sensorApi1_16,
	Config_sensorApi2_16,
	Config_sensorApi3_16,
	Config_sensorApi4_16,
	Config_sensorLoc_17,
	Config_sensorApi1_17,
	Config_sensorApi2_17,
	Config_sensorApi3_17,
	Config_sensorApi4_17,
	Config_sensorLoc_18,
	Config_sensorApi1_18,
	Config_sensorApi2_18,
	Config_sensorApi3_18,
	Config_sensorApi4_18,
	Config_sensorLoc_19,
	Config_sensorApi1_19,
	Config_sensorApi2_19,
	Config_sensorApi3_19,
	Config_sensorApi4_19,
	Config_sensorLoc_20,
	Config_sensorApi1_20,
	Config_sensorApi2_20,
	Config_sensorApi3_20,
	Config_sensorApi4_20,
	Config_sensorLoc_21,
	Config_sensorApi1_21,
	Config_sensorApi2_21,
	Config_sensorApi3_21,
	Config_sensorApi4_21,
	Config_sensorLoc_22,
	Config_sensorApi1_22,
	Config_sensorApi2_22,
	Config_sensorApi3_22,
	Config_sensorApi4_22,
	Config_sensorLoc_23,
	Config_sensorApi1_23,
	Config_sensorApi2_23,
	Config_sensorApi3_23,
	Config_sensorApi4_23,
	Config_sensorLoc_24,
	Config_sensorApi1_24,
	Config_sensorApi2_24,
	Config_sensorApi3_24,
	Config_sensorApi4_24,
	Config_sensorLoc_25,
	Config_sensorApi1_25,
	Config_sensorApi2_25,
	Config_sensorApi3_25,
	Config_sensorApi4_25,
	Config_sensorLoc_26,
	Config_sensorApi1_26,
	Config_sensorApi2_26,
	Config_sensorApi3_26,
	Config_sensorApi4_26,
	Config_sensorLoc_27,
	Config_sensorApi1_27,
	Config_sensorApi2_27,
	Config_sensorApi3_27,
	Config_sensorApi4_27,
	Config_sensorLoc_28,
	Config_sensorApi1_28,
	Config_sensorApi2_28,
	Config_sensorApi3_28,
	Config_sensorApi4_28,
	Config_sensorLoc_29,
	Config_sensorApi1_29,
	Config_sensorApi2_29,
	Config_sensorApi3_29,
	Config_sensorApi4_29,
	Config_sensorLoc_30,
	Config_sensorApi1_30,
	Config_sensorApi2_30,
	Config_sensorApi3_30,
	Config_sensorApi4_30,
	Config_sensorLoc_31,
	Config_sensorApi1_31,
	Config_sensorApi2_31,
	Config_sensorApi3_31,
	Config_sensorApi4_31,
	Config_nameRef,
	Config_pmDryRef,
	Config_humiDryRef,
	Config_pmWetRef,
	Config_humiWetRef,
};
static constexpr char CFG_KEY_PAUSETIME[] PROGMEM = "pauseTime";
static constexpr char CFG_KEY_DISPLAYSPEED[] PROGMEM = "displaySpeed";
static constexpr char CFG_KEY_CALLINGINTERVAL[] PROGMEM = "callingInterval";
static constexpr char CFG_KEY_WELKOMINTERVAL[] PROGMEM = "welkomInterval";
static constexpr char CFG_KEY_DIFFERENCEPERCENT[] PROGMEM = "differencePercent";
static constexpr char CFG_KEY_DIFFERENCELEVEL[] PROGMEM = "differenceLevel";
static constexpr char CFG_KEY_SENSORDATATIMEOUT[] PROGMEM = "sensordataTimeout";
static constexpr char CFG_KEY_CLOCKSECONDS[] PROGMEM = "clockSeconds";
static constexpr char CFG_KEY_PMCHOICE[] PROGMEM = "pmChoice";
static constexpr char CFG_KEY_MAXGRAPHPM10[] PROGMEM = "maxgraphPM10";
static constexpr char CFG_KEY_MAXGRAPHPM25[] PROGMEM = "maxgraphPM25";
static constexpr char CFG_KEY_MAX25WHO[] PROGMEM = "max25WHO";
static constexpr char CFG_KEY_MAX10WHO[] PROGMEM = "max10WHO";
static constexpr char CFG_KEY_PM25TOAQI50[] PROGMEM = "PM25toAQI50";
static constexpr char CFG_KEY_PM10TOAQI50[] PROGMEM = "PM10toAQI50";
static constexpr char CFG_KEY_COMPARELOCATION[] PROGMEM = "compareLocation";
static constexpr char CFG_KEY_COMPARELOCATION2[] PROGMEM = "compareLocation2";
static constexpr char CFG_KEY_MAXLAEQGREEN[] PROGMEM = "maxLAeqGreen";
static constexpr char CFG_KEY_MAXLAEQYELLOW[] PROGMEM = "maxLAeqYellow";
static constexpr char CFG_KEY_MAXLAEQORANGE[] PROGMEM = "maxLAeqOrange";
static constexpr char CFG_KEY_MAXLAEQRED[] PROGMEM = "maxLAeqRed";
static constexpr char CFG_KEY_MAXLAEQVIOLET[] PROGMEM = "maxLAeqViolet";
static constexpr char CFG_KEY_MAXLAEQBROWN[] PROGMEM = "maxLAeqBrown";
static constexpr char CFG_KEY_MAXAQIGREEN[] PROGMEM = "maxAqiGreen";
static constexpr char CFG_KEY_MAXAQIYELLOW[] PROGMEM = "maxAqiYellow";
static constexpr char CFG_KEY_MAXAQIORANGE[] PROGMEM = "maxAqiOrange";
static constexpr char CFG_KEY_MAXAQIRED[] PROGMEM = "maxAqiRed";
static constexpr char CFG_KEY_MAXAQIVIOLET[] PROGMEM = "maxAqiViolet";
static constexpr char CFG_KEY_MAXWHOGREEN[] PROGMEM = "maxWhoGreen";
static constexpr char CFG_KEY_MAXWHOYELLOW[] PROGMEM = "maxWhoYellow";
static constexpr char CFG_KEY_MAXWHOORANGE[] PROGMEM = "maxWhoOrange";
static constexpr char CFG_KEY_MAXWHORED[] PROGMEM = "maxWhoRed";
static constexpr char CFG_KEY_MAXWHOVIOLET[] PROGMEM = "maxWhoViolet";
static constexpr char CFG_KEY_MAXTRAFGREEN[] PROGMEM = "maxTrafGreen";
static constexpr char CFG_KEY_MAXTRAFYELLOW[] PROGMEM = "maxTrafYellow";
static constexpr char CFG_KEY_MAXTRAFORANGE[] PROGMEM = "maxTrafOrange";
static constexpr char CFG_KEY_MAXTRAFRED[] PROGMEM = "maxTrafRed";
static constexpr char CFG_KEY_MAXTRAFCYAN[] PROGMEM = "maxTrafCyan";
static constexpr char CFG_KEY_MAXTRAFVIOLET[] PROGMEM = "maxTrafViolet";
static constexpr char CFG_KEY_MAXTRAFBROWN[] PROGMEM = "maxTrafBrown";
static constexpr char CFG_KEY_MULTICOMPARE[] PROGMEM = "multiCompare";
static constexpr char CFG_KEY_SHOWPMPM[] PROGMEM = "showPmPm";
static constexpr char CFG_KEY_SHOWPM1PM4[] PROGMEM = "showPm1Pm4";
static constexpr char CFG_KEY_SHOWMETEO[] PROGMEM = "showMeteo";
static constexpr char CFG_KEY_INTELLIHUMI[] PROGMEM = "intelliHumi";
static constexpr char CFG_KEY_CORRECTHUMI[] PROGMEM = "correctHumi";
static constexpr char CFG_KEY_SHOWGRAPH[] PROGMEM = "showGraph";
static constexpr char CFG_KEY_SHOWAVGNPEAK[] PROGMEM = "showAvgNpeak";
static constexpr char CFG_KEY_SHOWCOMP[] PROGMEM = "showComp";
static constexpr char CFG_KEY_SHOWCOMPINSIDE[] PROGMEM = "showCompInside";
static constexpr char CFG_KEY_SHOWAQIADVICE[] PROGMEM = "showAqiAdvice";
static constexpr char CFG_KEY_SHOWWHOADVICE[] PROGMEM = "showWhoAdvice";
static constexpr char CFG_KEY_SHOWDNMS[] PROGMEM = "showDnms";
static constexpr char CFG_KEY_SHOWVOC[] PROGMEM = "showVoc";
static constexpr char CFG_KEY_SHOWTELRAAM[] PROGMEM = "showTelRaam";
static constexpr char CFG_KEY_SHOWPEDES[] PROGMEM = "showPedes";
static constexpr char CFG_KEY_SHOWBIKE[] PROGMEM = "showBike";
static constexpr char CFG_KEY_SHOWCAR[] PROGMEM = "showCar";
static constexpr char CFG_KEY_SHOWHEAVY[] PROGMEM = "showHeavy";
static constexpr char CFG_KEY_SHOWSPEED[] PROGMEM = "showSpeed";
static constexpr char CFG_KEY_SENSORMISSING[] PROGMEM = "sensorMissing";
static constexpr char CFG_KEY_MULTIAVERAGE[] PROGMEM = "multiAverage";
static constexpr char CFG_KEY_DEBUGSHOWDATA[] PROGMEM = "debugShowData";
static constexpr char CFG_KEY_DEBUGDISPLAY[] PROGMEM = "debugDisplay";
static constexpr char CFG_KEY_DEBUGCOMMS[] PROGMEM = "debugComms";
static constexpr char CFG_KEY_DEBUGHEAP[] PROGMEM = "debugHeap";
static constexpr char CFG_KEY_DEBUGJSON[] PROGMEM = "debugJson";
static constexpr char CFG_KEY_WWW_BASICAUTH_ENABLED[] PROGMEM = "www_basicauth_enabled";
static constexpr char CFG_KEY_FREETOKEN[] PROGMEM = "freeToken";
static constexpr char CFG_KEY_WLANPWD[] PROGMEM = "wlanpwd";
static constexpr char CFG_KEY_FS_PWD[] PROGMEM = "fs_pwd";
static constexpr char CFG_KEY_WWW_PASSWORD[] PROGMEM = "www_password";
static constexpr char CFG_KEY_WLANSSID[] PROGMEM = "wlanssid";
static constexpr char CFG_KEY_WWW_USERNAME[] PROGMEM = "www_username";
static constexpr char CFG_KEY_FS_SSID[] PROGMEM = "fs_ssid";
static constexpr char CFG_KEY_WELKOM[] PROGMEM = "welkom";
static constexpr char CFG_KEY_WELKOM2[] PROGMEM = "welkom2";
static constexpr char CFG_KEY_TIMEZONESTR[] PROGMEM = "timeZoneStr";
static constexpr char CFG_KEY_SENSORAPI[] PROGMEM = "sensorApi";
static constexpr char CFG_KEY_TELRAAMAPI[] PROGMEM = "telraamApi";
static constexpr char CFG_KEY_TELRAAMTOKEN[] PROGMEM = "telraamToken";
static constexpr char CFG_KEY_SENSORLOC_0[] PROGMEM = "sensorLoc_0";
static constexpr char CFG_KEY_SENSORAPI1_0[] PROGMEM = "sensorApi1_0";
static constexpr char CFG_KEY_SENSORAPI2_0[] PROGMEM = "sensorApi2_0";
static constexpr char CFG_KEY_SENSORAPI3_0[] PROGMEM = "sensorApi3_0";
static constexpr char CFG_KEY_SENSORAPI4_0[] PROGMEM = "sensorApi4_0";
static constexpr char CFG_KEY_SENSORLOC_1[] PROGMEM = "sensorLoc_1";
static constexpr char CFG_KEY_SENSORAPI1_1[] PROGMEM = "sensorApi1_1";
static constexpr char CFG_KEY_SENSORAPI2_1[] PROGMEM = "sensorApi2_1";
static constexpr char CFG_KEY_SENSORAPI3_1[] PROGMEM = "sensorApi3_1";
static constexpr char CFG_KEY_SENSORAPI4_1[] PROGMEM = "sensorApi4_1";
static constexpr char CFG_KEY_SENSORLOC_2[] PROGMEM = "sensorLoc_2";
static constexpr char CFG_KEY_SENSORAPI1_2[] PROGMEM = "sensorApi1_2";
static constexpr char CFG_KEY_SENSORAPI2_2[] PROGMEM = "sensorApi2_2";
static constexpr char CFG_KEY_SENSORAPI3_2[] PROGMEM = "sensorApi3_2";
static constexpr char CFG_KEY_SENSORAPI4_2[] PROGMEM = "sensorApi4_2";
static constexpr char CFG_KEY_SENSORLOC_3[] PROGMEM = "sensorLoc_3";
static constexpr char CFG_KEY_SENSORAPI1_3[] PROGMEM = "sensorApi1_3";
static constexpr char CFG_KEY_SENSORAPI2_3[] PROGMEM = "sensorApi2_3";
static constexpr char CFG_KEY_SENSORAPI3_3[] PROGMEM = "sensorApi3_3";
static constexpr char CFG_KEY_SENSORAPI4_3[] PROGMEM = "sensorApi4_3";
static constexpr char CFG_KEY_SENSORLOC_4[] PROGMEM = "sensorLoc_4";
static constexpr char CFG_KEY_SENSORAPI1_4[] PROGMEM = "sensorApi1_4";
static constexpr char CFG_KEY_SENSORAPI2_4[] PROGMEM = "sensorApi2_4";
static constexpr char CFG_KEY_SENSORAPI3_4[] PROGMEM = "sensorApi3_4";
static constexpr char CFG_KEY_SENSORAPI4_4[] PROGMEM = "sensorApi4_4";
static constexpr char CFG_KEY_SENSORLOC_5[] PROGMEM = "sensorLoc_5";
static constexpr char CFG_KEY_SENSORAPI1_5[] PROGMEM = "sensorApi1_5";
static constexpr char CFG_KEY_SENSORAPI2_5[] PROGMEM = "sensorApi2_5";
static constexpr char CFG_KEY_SENSORAPI3_5[] PROGMEM = "sensorApi3_5";
static constexpr char CFG_KEY_SENSORAPI4_5[] PROGMEM = "sensorApi4_5";
static constexpr char CFG_KEY_SENSORLOC_6[] PROGMEM = "sensorLoc_6";
static constexpr char CFG_KEY_SENSORAPI1_6[] PROGMEM = "sensorApi1_6";
static constexpr char CFG_KEY_SENSORAPI2_6[] PROGMEM = "sensorApi2_6";
static constexpr char CFG_KEY_SENSORAPI3_6[] PROGMEM = "sensorApi3_6";
static constexpr char CFG_KEY_SENSORAPI4_6[] PROGMEM = "sensorApi4_6";
static constexpr char CFG_KEY_SENSORLOC_7[] PROGMEM = "sensorLoc_7";
static constexpr char CFG_KEY_SENSORAPI1_7[] PROGMEM = "sensorApi1_7";
static constexpr char CFG_KEY_SENSORAPI2_7[] PROGMEM = "sensorApi2_7";
static constexpr char CFG_KEY_SENSORAPI3_7[] PROGMEM = "sensorApi3_7";
static constexpr char CFG_KEY_SENSORAPI4_7[] PROGMEM = "sensorApi4_7";
static constexpr char CFG_KEY_SENSORLOC_8[] PROGMEM = "sensorLoc_8";
static constexpr char CFG_KEY_SENSORAPI1_8[] PROGMEM = "sensorApi1_8";
static constexpr char CFG_KEY_SENSORAPI2_8[] PROGMEM = "sensorApi2_8";
static constexpr char CFG_KEY_SENSORAPI3_8[] PROGMEM = "sensorApi3_8";
static constexpr char CFG_KEY_SENSORAPI4_8[] PROGMEM = "sensorApi4_8";
static constexpr char CFG_KEY_SENSORLOC_9[] PROGMEM = "sensorLoc_9";
static constexpr char CFG_KEY_SENSORAPI1_9[] PROGMEM = "sensorApi1_9";
static constexpr char CFG_KEY_SENSORAPI2_9[] PROGMEM = "sensorApi2_9";
static constexpr char CFG_KEY_SENSORAPI3_9[] PROGMEM = "sensorApi3_9";
static constexpr char CFG_KEY_SENSORAPI4_9[] PROGMEM = "sensorApi4_9";
static constexpr char CFG_KEY_SENSORLOC_10[] PROGMEM = "sensorLoc_10";
static constexpr char CFG_KEY_SENSORAPI1_10[] PROGMEM = "sensorApi1_10";
static constexpr char CFG_KEY_SENSORAPI2_10[] PROGMEM = "sensorApi2_10";
static constexpr char CFG_KEY_SENSORAPI3_10[] PROGMEM = "sensorApi3_10";
static constexpr char CFG_KEY_SENSORAPI4_10[] PROGMEM = "sensorApi4_10";
static constexpr char CFG_KEY_SENSORLOC_11[] PROGMEM = "sensorLoc_11";
static constexpr char CFG_KEY_SENSORAPI1_11[] PROGMEM = "sensorApi1_11";
static constexpr char CFG_KEY_SENSORAPI2_11[] PROGMEM = "sensorApi2_11";
static constexpr char CFG_KEY_SENSORAPI3_11[] PROGMEM = "sensorApi3_11";
static constexpr char CFG_KEY_SENSORAPI4_11[] PROGMEM = "sensorApi4_11";
static constexpr char CFG_KEY_SENSORLOC_12[] PROGMEM = "sensorLoc_12";
static constexpr char CFG_KEY_SENSORAPI1_12[] PROGMEM = "sensorApi1_12";
static constexpr char CFG_KEY_SENSORAPI2_12[] PROGMEM = "sensorApi2_12";
static constexpr char CFG_KEY_SENSORAPI3_12[] PROGMEM = "sensorApi3_12";
static constexpr char CFG_KEY_SENSORAPI4_12[] PROGMEM = "sensorApi4_12";
static constexpr char CFG_KEY_SENSORLOC_13[] PROGMEM = "sensorLoc_13";
static constexpr char CFG_KEY_SENSORAPI1_13[] PROGMEM = "sensorApi1_13";
static constexpr char CFG_KEY_SENSORAPI2_13[] PROGMEM = "sensorApi2_13";
static constexpr char CFG_KEY_SENSORAPI3_13[] PROGMEM = "sensorApi3_13";
static constexpr char CFG_KEY_SENSORAPI4_13[] PROGMEM = "sensorApi4_13";
static constexpr char CFG_KEY_SENSORLOC_14[] PROGMEM = "sensorLoc_14";
static constexpr char CFG_KEY_SENSORAPI1_14[] PROGMEM = "sensorApi1_14";
static constexpr char CFG_KEY_SENSORAPI2_14[] PROGMEM = "sensorApi2_14";
static constexpr char CFG_KEY_SENSORAPI3_14[] PROGMEM = "sensorApi3_14";
static constexpr char CFG_KEY_SENSORAPI4_14[] PROGMEM = "sensorApi4_14";
static constexpr char CFG_KEY_SENSORLOC_15[] PROGMEM = "sensorLoc_15";
static constexpr char CFG_KEY_SENSORAPI1_15[] PROGMEM = "sensorApi1_15";
static constexpr char CFG_KEY_SENSORAPI2_15[] PROGMEM = "sensorApi2_15";
static constexpr char CFG_KEY_SENSORAPI3_15[] PROGMEM = "sensorApi3_15";
static constexpr char CFG_KEY_SENSORAPI4_15[] PROGMEM = "sensorApi4_15";
static constexpr char CFG_KEY_SENSORLOC_16[] PROGMEM = "sensorLoc_16";
static constexpr char CFG_KEY_SENSORAPI1_16[] PROGMEM = "sensorApi1_16";
static constexpr char CFG_KEY_SENSORAPI2_16[] PROGMEM = "sensorApi2_16";
static constexpr char CFG_KEY_SENSORAPI3_16[] PROGMEM = "sensorApi3_16";
static constexpr char CFG_KEY_SENSORAPI4_16[] PROGMEM = "sensorApi4_16";
static constexpr char CFG_KEY_SENSORLOC_17[] PROGMEM = "sensorLoc_17";
static constexpr char CFG_KEY_SENSORAPI1_17[] PROGMEM = "sensorApi1_17";
static constexpr char CFG_KEY_SENSORAPI2_17[] PROGMEM = "sensorApi2_17";
static constexpr char CFG_KEY_SENSORAPI3_17[] PROGMEM = "sensorApi3_17";
static constexpr char CFG_KEY_SENSORAPI4_17[] PROGMEM = "sensorApi4_17";
static constexpr char CFG_KEY_SENSORLOC_18[] PROGMEM = "sensorLoc_18";
static constexpr char CFG_KEY_SENSORAPI1_18[] PROGMEM = "sensorApi1_18";
static constexpr char CFG_KEY_SENSORAPI2_18[] PROGMEM = "sensorApi2_18";
static constexpr char CFG_KEY_SENSORAPI3_18[] PROGMEM = "sensorApi3_18";
static constexpr char CFG_KEY_SENSORAPI4_18[] PROGMEM = "sensorApi4_18";
static constexpr char CFG_KEY_SENSORLOC_19[] PROGMEM = "sensorLoc_19";
static constexpr char CFG_KEY_SENSORAPI1_19[] PROGMEM = "sensorApi1_19";
static constexpr char CFG_KEY_SENSORAPI2_19[] PROGMEM = "sensorApi2_19";
static constexpr char CFG_KEY_SENSORAPI3_19[] PROGMEM = "sensorApi3_19";
static constexpr char CFG_KEY_SENSORAPI4_19[] PROGMEM = "sensorApi4_19";
static constexpr char CFG_KEY_SENSORLOC_20[] PROGMEM = "sensorLoc_20";
static constexpr char CFG_KEY_SENSORAPI1_20[] PROGMEM = "sensorApi1_20";
static constexpr char CFG_KEY_SENSORAPI2_20[] PROGMEM = "sensorApi2_20";
static constexpr char CFG_KEY_SENSORAPI3_20[] PROGMEM = "sensorApi3_20";
static constexpr char CFG_KEY_SENSORAPI4_20[] PROGMEM = "sensorApi4_20";
static constexpr char CFG_KEY_SENSORLOC_21[] PROGMEM = "sensorLoc_21";
static constexpr char CFG_KEY_SENSORAPI1_21[] PROGMEM = "sensorApi1_21";
static constexpr char CFG_KEY_SENSORAPI2_21[] PROGMEM = "sensorApi2_21";
static constexpr char CFG_KEY_SENSORAPI3_21[] PROGMEM = "sensorApi3_21";
static constexpr char CFG_KEY_SENSORAPI4_21[] PROGMEM = "sensorApi4_21";
static constexpr char CFG_KEY_SENSORLOC_22[] PROGMEM = "sensorLoc_22";
static constexpr char CFG_KEY_SENSORAPI1_22[] PROGMEM = "sensorApi1_22";
static constexpr char CFG_KEY_SENSORAPI2_22[] PROGMEM = "sensorApi2_22";
static constexpr char CFG_KEY_SENSORAPI3_22[] PROGMEM = "sensorApi3_22";
static constexpr char CFG_KEY_SENSORAPI4_22[] PROGMEM = "sensorApi4_22";
static constexpr char CFG_KEY_SENSORLOC_23[] PROGMEM = "sensorLoc_23";
static constexpr char CFG_KEY_SENSORAPI1_23[] PROGMEM = "sensorApi1_23";
static constexpr char CFG_KEY_SENSORAPI2_23[] PROGMEM = "sensorApi2_23";
static constexpr char CFG_KEY_SENSORAPI3_23[] PROGMEM = "sensorApi3_23";
static constexpr char CFG_KEY_SENSORAPI4_23[] PROGMEM = "sensorApi4_23";
static constexpr char CFG_KEY_SENSORLOC_24[] PROGMEM = "sensorLoc_24";
static constexpr char CFG_KEY_SENSORAPI1_24[] PROGMEM = "sensorApi1_24";
static constexpr char CFG_KEY_SENSORAPI2_24[] PROGMEM = "sensorApi2_24";
static constexpr char CFG_KEY_SENSORAPI3_24[] PROGMEM = "sensorApi3_24";
static constexpr char CFG_KEY_SENSORAPI4_24[] PROGMEM = "sensorApi4_24";
static constexpr char CFG_KEY_SENSORLOC_25[] PROGMEM = "sensorLoc_25";
static constexpr char CFG_KEY_SENSORAPI1_25[] PROGMEM = "sensorApi1_25";
static constexpr char CFG_KEY_SENSORAPI2_25[] PROGMEM = "sensorApi2_25";
static constexpr char CFG_KEY_SENSORAPI3_25[] PROGMEM = "sensorApi3_25";
static constexpr char CFG_KEY_SENSORAPI4_25[] PROGMEM = "sensorApi4_25";
static constexpr char CFG_KEY_SENSORLOC_26[] PROGMEM = "sensorLoc_26";
static constexpr char CFG_KEY_SENSORAPI1_26[] PROGMEM = "sensorApi1_26";
static constexpr char CFG_KEY_SENSORAPI2_26[] PROGMEM = "sensorApi2_26";
static constexpr char CFG_KEY_SENSORAPI3_26[] PROGMEM = "sensorApi3_26";
static constexpr char CFG_KEY_SENSORAPI4_26[] PROGMEM = "sensorApi4_26";
static constexpr char CFG_KEY_SENSORLOC_27[] PROGMEM = "sensorLoc_27";
static constexpr char CFG_KEY_SENSORAPI1_27[] PROGMEM = "sensorApi1_27";
static constexpr char CFG_KEY_SENSORAPI2_27[] PROGMEM = "sensorApi2_27";
static constexpr char CFG_KEY_SENSORAPI3_27[] PROGMEM = "sensorApi3_27";
static constexpr char CFG_KEY_SENSORAPI4_27[] PROGMEM = "sensorApi4_27";
static constexpr char CFG_KEY_SENSORLOC_28[] PROGMEM = "sensorLoc_28";
static constexpr char CFG_KEY_SENSORAPI1_28[] PROGMEM = "sensorApi1_28";
static constexpr char CFG_KEY_SENSORAPI2_28[] PROGMEM = "sensorApi2_28";
static constexpr char CFG_KEY_SENSORAPI3_28[] PROGMEM = "sensorApi3_28";
static constexpr char CFG_KEY_SENSORAPI4_28[] PROGMEM = "sensorApi4_28";
static constexpr char CFG_KEY_SENSORLOC_29[] PROGMEM = "sensorLoc_29";
static constexpr char CFG_KEY_SENSORAPI1_29[] PROGMEM = "sensorApi1_29";
static constexpr char CFG_KEY_SENSORAPI2_29[] PROGMEM = "sensorApi2_29";
static constexpr char CFG_KEY_SENSORAPI3_29[] PROGMEM = "sensorApi3_29";
static constexpr char CFG_KEY_SENSORAPI4_29[] PROGMEM = "sensorApi4_29";
static constexpr char CFG_KEY_SENSORLOC_30[] PROGMEM = "sensorLoc_30";
static constexpr char CFG_KEY_SENSORAPI1_30[] PROGMEM = "sensorApi1_30";
static constexpr char CFG_KEY_SENSORAPI2_30[] PROGMEM = "sensorApi2_30";
static constexpr char CFG_KEY_SENSORAPI3_30[] PROGMEM = "sensorApi3_30";
static constexpr char CFG_KEY_SENSORAPI4_30[] PROGMEM = "sensorApi4_30";
static constexpr char CFG_KEY_SENSORLOC_31[] PROGMEM = "sensorLoc_31";
static constexpr char CFG_KEY_SENSORAPI1_31[] PROGMEM = "sensorApi1_31";
static constexpr char CFG_KEY_SENSORAPI2_31[] PROGMEM = "sensorApi2_31";
static constexpr char CFG_KEY_SENSORAPI3_31[] PROGMEM = "sensorApi3_31";
static constexpr char CFG_KEY_SENSORAPI4_31[] PROGMEM = "sensorApi4_31";
static constexpr char CFG_KEY_NAMEREF[] PROGMEM = "nameRef";
static constexpr char CFG_KEY_PMDRYREF[] PROGMEM = "pmDryRef";
static constexpr char CFG_KEY_HUMIDRYREF[] PROGMEM = "humiDryRef";
static constexpr char CFG_KEY_PMWETREF[] PROGMEM = "pmWetRef";
static constexpr char CFG_KEY_HUMIWETREF[] PROGMEM = "humiWetRef";
static constexpr ConfigShapeEntry configShape[] PROGMEM = {
	{ Config_Type_UInt, 0, CFG_KEY_PAUSETIME, &cfg::pauseTime },
	{ Config_Type_UInt, 0, CFG_KEY_DISPLAYSPEED, &cfg::displaySpeed },
	{ Config_Type_UInt, 0, CFG_KEY_CALLINGINTERVAL, &cfg::callingInterval },
	{ Config_Type_UInt, 0, CFG_KEY_WELKOMINTERVAL, &cfg::welkomInterval },
	{ Config_Type_UInt, 0, CFG_KEY_DIFFERENCEPERCENT, &cfg::differencePercent },
	{ Config_Type_UInt, 0, CFG_KEY_DIFFERENCELEVEL, &cfg::differenceLevel },
	{ Config_Type_UInt, 0, CFG_KEY_SENSORDATATIMEOUT, &cfg::sensordataTimeout },
	{ Config_Type_UInt, 0, CFG_KEY_CLOCKSECONDS, &cfg::clockSeconds },
	{ Config_Type_UInt, 0, CFG_KEY_PMCHOICE, &cfg::pmChoice },
	{ Config_Type_UInt, 0, CFG_KEY_MAXGRAPHPM10, &cfg::maxgraphPM10 },
	{ Config_Type_UInt, 0, CFG_KEY_MAXGRAPHPM25, &cfg::maxgraphPM25 },
	{ Config_Type_UInt, 0, CFG_KEY_MAX25WHO, &cfg::max25WHO },
	{ Config_Type_UInt, 0, CFG_KEY_MAX10WHO, &cfg::max10WHO },
	{ Config_Type_UInt, 0, CFG_KEY_PM25TOAQI50, &cfg::PM25toAQI50 },
	{ Config_Type_UInt, 0, CFG_KEY_PM10TOAQI50, &cfg::PM10toAQI50 },
	{ Config_Type_UInt, 0, CFG_KEY_COMPARELOCATION, &cfg::compareLocation },
	{ Config_Type_UInt, 0, CFG_KEY_COMPARELOCATION2, &cfg::compareLocation2 },
	{ Config_Type_UInt, 0, CFG_KEY_MAXLAEQGREEN, &cfg::maxLAeqGreen },
	{ Config_Type_UInt, 0, CFG_KEY_MAXLAEQYELLOW, &cfg::maxLAeqYellow },
	{ Config_Type_UInt, 0, CFG_KEY_MAXLAEQORANGE, &cfg::maxLAeqOrange },
	{ Config_Type_UInt, 0, CFG_KEY_MAXLAEQRED, &cfg::maxLAeqRed },
	{ Config_Type_UInt, 0, CFG_KEY_MAXLAEQVIOLET, &cfg::maxLAeqViolet },
	{ Config_Type_UInt, 0, CFG_KEY_MAXLAEQBROWN, &cfg::maxLAeqBrown },
	{ Config_Type_UInt, 0, CFG_KEY_MAXAQIGREEN, &cfg::maxAqiGreen },
	{ Config_Type_UInt, 0, CFG_KEY_MAXAQIYELLOW, &cfg::maxAqiYellow },
	{ Config_Type_UInt, 0, CFG_KEY_MAXAQIORANGE, &cfg::maxAqiOrange },
	{ Config_Type_UInt, 0, CFG_KEY_MAXAQIRED, &cfg::maxAqiRed },
	{ Config_Type_UInt, 0, CFG_KEY_MAXAQIVIOLET, &cfg::maxAqiViolet },
	{ Config_Type_UInt, 0, CFG_KEY_MAXWHOGREEN, &cfg::maxWhoGreen },
	{ Config_Type_UInt, 0, CFG_KEY_MAXWHOYELLOW, &cfg::maxWhoYellow },
	{ Config_Type_UInt, 0, CFG_KEY_MAXWHOORANGE, &cfg::maxWhoOrange },
	{ Config_Type_UInt, 0, CFG_KEY_MAXWHORED, &cfg::maxWhoRed },
	{ Config_Type_UInt, 0, CFG_KEY_MAXWHOVIOLET, &cfg::maxWhoViolet },
	{ Config_Type_UInt, 0, CFG_KEY_MAXTRAFGREEN, &cfg::maxTrafGreen },
	{ Config_Type_UInt, 0, CFG_KEY_MAXTRAFYELLOW, &cfg::maxTrafYellow },
	{ Config_Type_UInt, 0, CFG_KEY_MAXTRAFORANGE, &cfg::maxTrafOrange },
	{ Config_Type_UInt, 0, CFG_KEY_MAXTRAFRED, &cfg::maxTrafRed },
	{ Config_Type_UInt, 0, CFG_KEY_MAXTRAFCYAN, &cfg::maxTrafCyan },
	{ Config_Type_UInt, 0, CFG_KEY_MAXTRAFVIOLET, &cfg::maxTrafViolet },
	{ Config_Type_UInt, 0, CFG_KEY_MAXTRAFBROWN, &cfg::maxTrafBrown },
	{ Config_Type_Bool, 0, CFG_KEY_MULTICOMPARE, &cfg::multiCompare },
	{ Config_Type_Bool, 0, CFG_KEY_SHOWPMPM, &cfg::showPmPm },
	{ Config_Type_Bool, 0, CFG_KEY_SHOWPM1PM4, &cfg::showPm1Pm4 },
	{ Config_Type_Bool, 0, CFG_KEY_SHOWMETEO, &cfg::showMeteo },
	{ Config_Type_Bool, 0, CFG_KEY_INTELLIHUMI, &cfg::intelliHumi },
	{ Config_Type_Bool, 0, CFG_KEY_CORRECTHUMI, &cfg::correctHumi },
	{ Config_Type_Bool, 0, CFG_KEY_SHOWGRAPH, &cfg::showGraph },
	{ Config_Type_Bool, 0, CFG_KEY_SHOWAVGNPEAK, &cfg::showAvgNpeak },
	{ Config_Type_Bool, 0, CFG_KEY_SHOWCOMP, &cfg::showComp },
	{ Config_Type_Bool, 0, CFG_KEY_SHOWCOMPINSIDE, &cfg::showCompInside },
	{ Config_Type_Bool, 0, CFG_KEY_SHOWAQIADVICE, &cfg::showAqiAdvice },
	{ Config_Type_Bool, 0, CFG_KEY_SHOWWHOADVICE, &cfg::showWhoAdvice },
	{ Config_Type_Bool, 0, CFG_KEY_SHOWDNMS, &cfg::showDnms },
	{ Config_Type_Bool, 0, CFG_KEY_SHOWVOC, &cfg::showVoc },
	{ Config_Type_Bool, 0, CFG_KEY_SHOWTELRAAM, &cfg::showTelRaam },
	{ Config_Type_Bool, 0, CFG_KEY_SHOWPEDES, &cfg::showPedes },
	{ Config_Type_Bool, 0, CFG_KEY_SHOWBIKE, &cfg::showBike },
	{ Config_Type_Bool, 0, CFG_KEY_SHOWCAR, &cfg::showCar },
	{ Config_Type_Bool, 0, CFG_KEY_SHOWHEAVY, &cfg::showHeavy },
	{ Config_Type_Bool, 0, CFG_KEY_SHOWSPEED, &cfg::showSpeed },
	{ Config_Type_Bool, 0, CFG_KEY_SENSORMISSING, &cfg::sensorMissing },
	{ Config_Type_Bool, 0, CFG_KEY_MULTIAVERAGE, &cfg::multiAverage },
	{ Config_Type_Bool, 0, CFG_KEY_DEBUGSHOWDATA, &cfg::debugShowData },
	{ Config_Type_Bool, 0, CFG_KEY_DEBUGDISPLAY, &cfg::debugDisplay },
	{ Config_Type_Bool, 0, CFG_KEY_DEBUGCOMMS, &cfg::debugComms },
	{ Config_Type_Bool, 0, CFG_KEY_DEBUGHEAP, &cfg::debugHeap },
	{ Config_Type_Bool, 0, CFG_KEY_DEBUGJSON, &cfg::debugJson },
	{ Config_Type_Bool, 0, CFG_KEY_WWW_BASICAUTH_ENABLED, &cfg::www_basicauth_enabled },
	{ Config_Type_Bool, 0, CFG_KEY_FREETOKEN, &cfg::freeToken },
	{ Config_Type_Password, sizeof(cfg::wlanpwd)-1, CFG_KEY_WLANPWD, cfg::wlanpwd },
	{ Config_Type_Password, sizeof(cfg::fs_pwd)-1, CFG_KEY_FS_PWD, cfg::fs_pwd },
	{ Config_Type_Password, sizeof(cfg::www_password)-1, CFG_KEY_WWW_PASSWORD, cfg::www_password },
	{ Config_Type_String, sizeof(cfg::wlanssid)-1, CFG_KEY_WLANSSID, cfg::wlanssid },
	{ Config_Type_String, sizeof(cfg::www_username)-1, CFG_KEY_WWW_USERNAME, cfg::www_username },
	{ Config_Type_String, sizeof(cfg::fs_ssid)-1, CFG_KEY_FS_SSID, cfg::fs_ssid },
	{ Config_Type_String, sizeof(cfg::welkom)-1, CFG_KEY_WELKOM, cfg::welkom },
	{ Config_Type_String, sizeof(cfg::welkom2)-1, CFG_KEY_WELKOM2, cfg::welkom2 },
	{ Config_Type_String, sizeof(cfg::timeZoneStr)-1, CFG_KEY_TIMEZONESTR, cfg::timeZoneStr },
	{ Config_Type_String, sizeof(cfg::sensorApi)-1, CFG_KEY_SENSORAPI, cfg::sensorApi },
	{ Config_Type_String, sizeof(cfg::telraamApi)-1, CFG_KEY_TELRAAMAPI, cfg::telraamApi },
	{ Config_Type_String, sizeof(cfg::telraamToken)-1, CFG_KEY_TELRAAMTOKEN, cfg::telraamToken },
	{ Config_Type_String, sizeof(cfg::sensorLoc_0)-1, CFG_KEY_SENSORLOC_0, cfg::sensorLoc_0 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_0)-1, CFG_KEY_SENSORAPI1_0, cfg::sensorApi1_0 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_0)-1, CFG_KEY_SENSORAPI2_0, cfg::sensorApi2_0 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_0)-1, CFG_KEY_SENSORAPI3_0, cfg::sensorApi3_0 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_0)-1, CFG_KEY_SENSORAPI4_0, cfg::sensorApi4_0 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_1)-1, CFG_KEY_SENSORLOC_1, cfg::sensorLoc_1 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_1)-1, CFG_KEY_SENSORAPI1_1, cfg::sensorApi1_1 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_1)-1, CFG_KEY_SENSORAPI2_1, cfg::sensorApi2_1 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_1)-1, CFG_KEY_SENSORAPI3_1, cfg::sensorApi3_1 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_1)-1, CFG_KEY_SENSORAPI4_1, cfg::sensorApi4_1 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_2)-1, CFG_KEY_SENSORLOC_2, cfg::sensorLoc_2 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_2)-1, CFG_KEY_SENSORAPI1_2, cfg::sensorApi1_2 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_2)-1, CFG_KEY_SENSORAPI2_2, cfg::sensorApi2_2 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_2)-1, CFG_KEY_SENSORAPI3_2, cfg::sensorApi3_2 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_2)-1, CFG_KEY_SENSORAPI4_2, cfg::sensorApi4_2 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_3)-1, CFG_KEY_SENSORLOC_3, cfg::sensorLoc_3 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_3)-1, CFG_KEY_SENSORAPI1_3, cfg::sensorApi1_3 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_3)-1, CFG_KEY_SENSORAPI2_3, cfg::sensorApi2_3 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_3)-1, CFG_KEY_SENSORAPI3_3, cfg::sensorApi3_3 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_3)-1, CFG_KEY_SENSORAPI4_3, cfg::sensorApi4_3 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_4)-1, CFG_KEY_SENSORLOC_4, cfg::sensorLoc_4 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_4)-1, CFG_KEY_SENSORAPI1_4, cfg::sensorApi1_4 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_4)-1, CFG_KEY_SENSORAPI2_4, cfg::sensorApi2_4 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_4)-1, CFG_KEY_SENSORAPI3_4, cfg::sensorApi3_4 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_4)-1, CFG_KEY_SENSORAPI4_4, cfg::sensorApi4_4 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_5)-1, CFG_KEY_SENSORLOC_5, cfg::sensorLoc_5 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_5)-1, CFG_KEY_SENSORAPI1_5, cfg::sensorApi1_5 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_5)-1, CFG_KEY_SENSORAPI2_5, cfg::sensorApi2_5 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_5)-1, CFG_KEY_SENSORAPI3_5, cfg::sensorApi3_5 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_5)-1, CFG_KEY_SENSORAPI4_5, cfg::sensorApi4_5 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_6)-1, CFG_KEY_SENSORLOC_6, cfg::sensorLoc_6 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_6)-1, CFG_KEY_SENSORAPI1_6, cfg::sensorApi1_6 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_6)-1, CFG_KEY_SENSORAPI2_6, cfg::sensorApi2_6 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_6)-1, CFG_KEY_SENSORAPI3_6, cfg::sensorApi3_6 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_6)-1, CFG_KEY_SENSORAPI4_6, cfg::sensorApi4_6 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_7)-1, CFG_KEY_SENSORLOC_7, cfg::sensorLoc_7 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_7)-1, CFG_KEY_SENSORAPI1_7, cfg::sensorApi1_7 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_7)-1, CFG_KEY_SENSORAPI2_7, cfg::sensorApi2_7 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_7)-1, CFG_KEY_SENSORAPI3_7, cfg::sensorApi3_7 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_7)-1, CFG_KEY_SENSORAPI4_7, cfg::sensorApi4_7 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_8)-1, CFG_KEY_SENSORLOC_8, cfg::sensorLoc_8 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_8)-1, CFG_KEY_SENSORAPI1_8, cfg::sensorApi1_8 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_8)-1, CFG_KEY_SENSORAPI2_8, cfg::sensorApi2_8 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_8)-1, CFG_KEY_SENSORAPI3_8, cfg::sensorApi3_8 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_8)-1, CFG_KEY_SENSORAPI4_8, cfg::sensorApi4_8 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_9)-1, CFG_KEY_SENSORLOC_9, cfg::sensorLoc_9 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_9)-1, CFG_KEY_SENSORAPI1_9, cfg::sensorApi1_9 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_9)-1, CFG_KEY_SENSORAPI2_9, cfg::sensorApi2_9 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_9)-1, CFG_KEY_SENSORAPI3_9, cfg::sensorApi3_9 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_9)-1, CFG_KEY_SENSORAPI4_9, cfg::sensorApi4_9 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_10)-1, CFG_KEY_SENSORLOC_10, cfg::sensorLoc_10 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_10)-1, CFG_KEY_SENSORAPI1_10, cfg::sensorApi1_10 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_10)-1, CFG_KEY_SENSORAPI2_10, cfg::sensorApi2_10 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_10)-1, CFG_KEY_SENSORAPI3_10, cfg::sensorApi3_10 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_10)-1, CFG_KEY_SENSORAPI4_10, cfg::sensorApi4_10 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_11)-1, CFG_KEY_SENSORLOC_11, cfg::sensorLoc_11 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_11)-1, CFG_KEY_SENSORAPI1_11, cfg::sensorApi1_11 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_11)-1, CFG_KEY_SENSORAPI2_11, cfg::sensorApi2_11 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_11)-1, CFG_KEY_SENSORAPI3_11, cfg::sensorApi3_11 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_11)-1, CFG_KEY_SENSORAPI4_11, cfg::sensorApi4_11 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_12)-1, CFG_KEY_SENSORLOC_12, cfg::sensorLoc_12 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_12)-1, CFG_KEY_SENSORAPI1_12, cfg::sensorApi1_12 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_12)-1, CFG_KEY_SENSORAPI2_12, cfg::sensorApi2_12 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_12)-1, CFG_KEY_SENSORAPI3_12, cfg::sensorApi3_12 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_12)-1, CFG_KEY_SENSORAPI4_12, cfg::sensorApi4_12 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_13)-1, CFG_KEY_SENSORLOC_13, cfg::sensorLoc_13 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_13)-1, CFG_KEY_SENSORAPI1_13, cfg::sensorApi1_13 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_13)-1, CFG_KEY_SENSORAPI2_13, cfg::sensorApi2_13 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_13)-1, CFG_KEY_SENSORAPI3_13, cfg::sensorApi3_13 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_13)-1, CFG_KEY_SENSORAPI4_13, cfg::sensorApi4_13 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_14)-1, CFG_KEY_SENSORLOC_14, cfg::sensorLoc_14 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_14)-1, CFG_KEY_SENSORAPI1_14, cfg::sensorApi1_14 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_14)-1, CFG_KEY_SENSORAPI2_14, cfg::sensorApi2_14 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_14)-1, CFG_KEY_SENSORAPI3_14, cfg::sensorApi3_14 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_14)-1, CFG_KEY_SENSORAPI4_14, cfg::sensorApi4_14 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_15)-1, CFG_KEY_SENSORLOC_15, cfg::sensorLoc_15 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_15)-1, CFG_KEY_SENSORAPI1_15, cfg::sensorApi1_15 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_15)-1, CFG_KEY_SENSORAPI2_15, cfg::sensorApi2_15 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_15)-1, CFG_KEY_SENSORAPI3_15, cfg::sensorApi3_15 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_15)-1, CFG_KEY_SENSORAPI4_15, cfg::sensorApi4_15 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_16)-1, CFG_KEY_SENSORLOC_16, cfg::sensorLoc_16 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_16)-1, CFG_KEY_SENSORAPI1_16, cfg::sensorApi1_16 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_16)-1, CFG_KEY_SENSORAPI2_16, cfg::sensorApi2_16 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_16)-1, CFG_KEY_SENSORAPI3_16, cfg::sensorApi3_16 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_16)-1, CFG_KEY_SENSORAPI4_16, cfg::sensorApi4_16 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_17)-1, CFG_KEY_SENSORLOC_17, cfg::sensorLoc_17 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_17)-1, CFG_KEY_SENSORAPI1_17, cfg::sensorApi1_17 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_17)-1, CFG_KEY_SENSORAPI2_17, cfg::sensorApi2_17 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_17)-1, CFG_KEY_SENSORAPI3_17, cfg::sensorApi3_17 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_17)-1, CFG_KEY_SENSORAPI4_17, cfg::sensorApi4_17 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_18)-1, CFG_KEY_SENSORLOC_18, cfg::sensorLoc_18 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_18)-1, CFG_KEY_SENSORAPI1_18, cfg::sensorApi1_18 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_18)-1, CFG_KEY_SENSORAPI2_18, cfg::sensorApi2_18 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_18)-1, CFG_KEY_SENSORAPI3_18, cfg::sensorApi3_18 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_18)-1, CFG_KEY_SENSORAPI4_18, cfg::sensorApi4_18 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_19)-1, CFG_KEY_SENSORLOC_19, cfg::sensorLoc_19 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_19)-1, CFG_KEY_SENSORAPI1_19, cfg::sensorApi1_19 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_19)-1, CFG_KEY_SENSORAPI2_19, cfg::sensorApi2_19 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_19)-1, CFG_KEY_SENSORAPI3_19, cfg::sensorApi3_19 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_19)-1, CFG_KEY_SENSORAPI4_19, cfg::sensorApi4_19 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_20)-1, CFG_KEY_SENSORLOC_20, cfg::sensorLoc_20 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_20)-1, CFG_KEY_SENSORAPI1_20, cfg::sensorApi1_20 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_20)-1, CFG_KEY_SENSORAPI2_20, cfg::sensorApi2_20 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_20)-1, CFG_KEY_SENSORAPI3_20, cfg::sensorApi3_20 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_20)-1, CFG_KEY_SENSORAPI4_20, cfg::sensorApi4_20 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_21)-1, CFG_KEY_SENSORLOC_21, cfg::sensorLoc_21 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_21)-1, CFG_KEY_SENSORAPI1_21, cfg::sensorApi1_21 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_21)-1, CFG_KEY_SENSORAPI2_21, cfg::sensorApi2_21 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_21)-1, CFG_KEY_SENSORAPI3_21, cfg::sensorApi3_21 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_21)-1, CFG_KEY_SENSORAPI4_21, cfg::sensorApi4_21 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_22)-1, CFG_KEY_SENSORLOC_22, cfg::sensorLoc_22 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_22)-1, CFG_KEY_SENSORAPI1_22, cfg::sensorApi1_22 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_22)-1, CFG_KEY_SENSORAPI2_22, cfg::sensorApi2_22 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_22)-1, CFG_KEY_SENSORAPI3_22, cfg::sensorApi3_22 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_22)-1, CFG_KEY_SENSORAPI4_22, cfg::sensorApi4_22 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_23)-1, CFG_KEY_SENSORLOC_23, cfg::sensorLoc_23 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_23)-1, CFG_KEY_SENSORAPI1_23, cfg::sensorApi1_23 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_23)-1, CFG_KEY_SENSORAPI2_23, cfg::sensorApi2_23 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_23)-1, CFG_KEY_SENSORAPI3_23, cfg::sensorApi3_23 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_23)-1, CFG_KEY_SENSORAPI4_23, cfg::sensorApi4_23 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_24)-1, CFG_KEY_SENSORLOC_24, cfg::sensorLoc_24 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_24)-1, CFG_KEY_SENSORAPI1_24, cfg::sensorApi1_24 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_24)-1, CFG_KEY_SENSORAPI2_24, cfg::sensorApi2_24 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_24)-1, CFG_KEY_SENSORAPI3_24, cfg::sensorApi3_24 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_24)-1, CFG_KEY_SENSORAPI4_24, cfg::sensorApi4_24 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_25)-1, CFG_KEY_SENSORLOC_25, cfg::sensorLoc_25 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_25)-1, CFG_KEY_SENSORAPI1_25, cfg::sensorApi1_25 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_25)-1, CFG_KEY_SENSORAPI2_25, cfg::sensorApi2_25 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_25)-1, CFG_KEY_SENSORAPI3_25, cfg::sensorApi3_25 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_25)-1, CFG_KEY_SENSORAPI4_25, cfg::sensorApi4_25 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_26)-1, CFG_KEY_SENSORLOC_26, cfg::sensorLoc_26 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_26)-1, CFG_KEY_SENSORAPI1_26, cfg::sensorApi1_26 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_26)-1, CFG_KEY_SENSORAPI2_26, cfg::sensorApi2_26 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_26)-1, CFG_KEY_SENSORAPI3_26, cfg::sensorApi3_26 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_26)-1, CFG_KEY_SENSORAPI4_26, cfg::sensorApi4_26 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_27)-1, CFG_KEY_SENSORLOC_27, cfg::sensorLoc_27 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_27)-1, CFG_KEY_SENSORAPI1_27, cfg::sensorApi1_27 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_27)-1, CFG_KEY_SENSORAPI2_27, cfg::sensorApi2_27 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_27)-1, CFG_KEY_SENSORAPI3_27, cfg::sensorApi3_27 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_27)-1, CFG_KEY_SENSORAPI4_27, cfg::sensorApi4_27 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_28)-1, CFG_KEY_SENSORLOC_28, cfg::sensorLoc_28 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_28)-1, CFG_KEY_SENSORAPI1_28, cfg::sensorApi1_28 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_28)-1, CFG_KEY_SENSORAPI2_28, cfg::sensorApi2_28 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_28)-1, CFG_KEY_SENSORAPI3_28, cfg::sensorApi3_28 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_28)-1, CFG_KEY_SENSORAPI4_28, cfg::sensorApi4_28 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_29)-1, CFG_KEY_SENSORLOC_29, cfg::sensorLoc_29 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_29)-1, CFG_KEY_SENSORAPI1_29, cfg::sensorApi1_29 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_29)-1, CFG_KEY_SENSORAPI2_29, cfg::sensorApi2_29 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_29)-1, CFG_KEY_SENSORAPI3_29, cfg::sensorApi3_29 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_29)-1, CFG_KEY_SENSORAPI4_29, cfg::sensorApi4_29 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_30)-1, CFG_KEY_SENSORLOC_30, cfg::sensorLoc_30 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_30)-1, CFG_KEY_SENSORAPI1_30, cfg::sensorApi1_30 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_30)-1, CFG_KEY_SENSORAPI2_30, cfg::sensorApi2_30 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_30)-1, CFG_KEY_SENSORAPI3_30, cfg::sensorApi3_30 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_30)-1, CFG_KEY_SENSORAPI4_30, cfg::sensorApi4_30 },
	{ Config_Type_String, sizeof(cfg::sensorLoc_31)-1, CFG_KEY_SENSORLOC_31, cfg::sensorLoc_31 },
	{ Config_Type_String, sizeof(cfg::sensorApi1_31)-1, CFG_KEY_SENSORAPI1_31, cfg::sensorApi1_31 },
	{ Config_Type_String, sizeof(cfg::sensorApi2_31)-1, CFG_KEY_SENSORAPI2_31, cfg::sensorApi2_31 },
	{ Config_Type_String, sizeof(cfg::sensorApi3_31)-1, CFG_KEY_SENSORAPI3_31, cfg::sensorApi3_31 },
	{ Config_Type_String, sizeof(cfg::sensorApi4_31)-1, CFG_KEY_SENSORAPI4_31, cfg::sensorApi4_31 },
	{ Config_Type_String, sizeof(cfg::nameRef)-1, CFG_KEY_NAMEREF, cfg::nameRef },
	{ Config_Type_String, sizeof(cfg::pmDryRef)-1, CFG_KEY_PMDRYREF, cfg::pmDryRef },
	{ Config_Type_String, sizeof(cfg::humiDryRef)-1, CFG_KEY_HUMIDRYREF, cfg::humiDryRef },
	{ Config_Type_String, sizeof(cfg::pmWetRef)-1, CFG_KEY_PMWETREF, cfg::pmWetRef },
	{ Config_Type_String, sizeof(cfg::humiWetRef)-1, CFG_KEY_HUMIWETREF, cfg::humiWetRef },
};
