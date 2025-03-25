#!/usr/bin/env 	python3

configshape_in = """
UInt            pauseTime
UInt            displaySpeed
UInt            callingInterval
UInt            welkomInterval
UInt            differencePercent
UInt		differenceLevel
UInt            sensordataTimeout
UInt		clockSeconds
UInt		pmChoice
UInt		maxgraphPM10
UInt		maxgraphPM25
UInt		max25WHO
UInt		max10WHO
UInt		PM25toAQI50
UInt		PM10toAQI50
UInt 		compareLocation
UInt		compareLocation2
UInt		maxLAeqGreen
UInt		maxLAeqYellow
UInt		maxLAeqOrange
UInt		maxLAeqRed
UInt		maxLAeqViolet
UInt		maxLAeqBrown
UInt		maxAqiGreen
UInt		maxAqiYellow
UInt		maxAqiOrange
UInt		maxAqiRed
UInt		maxAqiViolet
UInt		maxWhoGreen
UInt		maxWhoYellow
UInt		maxWhoOrange
UInt		maxWhoRed
UInt		maxWhoViolet
UInt		maxTrafGreen
UInt		maxTrafYellow
UInt		maxTrafOrange
UInt		maxTrafRed
UInt		maxTrafCyan
UInt		maxTrafViolet
UInt		maxTrafBrown
Bool            multiCompare
Bool		showPmPm
Bool            showPm1Pm4
Bool		showMeteo
Bool            showGraph
Bool		showAvgNpeak
Bool 		showComp
Bool 		showCompInside
Bool            showAqiAdvice
Bool		showWhoAdvice
Bool		showDnms
Bool		showVoc
Bool		showTelRaam
Bool		showPedes
Bool		showBike
Bool		showCar
Bool		showHeavy
Bool		showSpeed
Bool            sensorMissing
Bool		multiAverage
Bool 		debugShowData
Bool 		debugDisplay
Bool 		debugComms
Bool 		debugHeap
Bool 		debugJson
Bool		www_basicauth_enabled
Bool		freeToken
Password	wlanpwd
Password	fs_pwd
Password	www_password
String		wlanssid
String		www_username
String		fs_ssid
String		welkom
String		welkom2
String 		timeZoneStr
String		sensorApi
String 		telraamApi
String		telraamToken
String		sensorLoc_0
String		sensorApi1_0
String		sensorApi2_0
String		sensorApi3_0
String		sensorApi4_0
String		sensorLoc_1
String		sensorApi1_1
String		sensorApi2_1
String		sensorApi3_1
String		sensorApi4_1
String		sensorLoc_2
String		sensorApi1_2
String		sensorApi2_2
String		sensorApi3_2
String		sensorApi4_2
String		sensorLoc_3
String		sensorApi1_3
String		sensorApi2_3
String		sensorApi3_3
String		sensorApi4_3
String		sensorLoc_4
String		sensorApi1_4
String		sensorApi2_4
String		sensorApi3_4
String		sensorApi4_4
String		sensorLoc_5
String		sensorApi1_5
String		sensorApi2_5
String		sensorApi3_5
String		sensorApi4_5
String		sensorLoc_6
String		sensorApi1_6
String		sensorApi2_6
String		sensorApi3_6
String		sensorApi4_6
String		sensorLoc_7
String		sensorApi1_7
String		sensorApi2_7
String		sensorApi3_7
String		sensorApi4_7
String		sensorLoc_8
String		sensorApi1_8
String		sensorApi2_8
String		sensorApi3_8
String		sensorApi4_8
String		sensorLoc_9
String		sensorApi1_9
String		sensorApi2_9
String		sensorApi3_9
String		sensorApi4_9
String		sensorLoc_10
String		sensorApi1_10
String		sensorApi2_10
String		sensorApi3_10
String		sensorApi4_10
String		sensorLoc_11
String		sensorApi1_11
String		sensorApi2_11
String		sensorApi3_11
String		sensorApi4_11
String		sensorLoc_12
String		sensorApi1_12
String		sensorApi2_12
String		sensorApi3_12
String		sensorApi4_12
String		sensorLoc_13
String		sensorApi1_13
String		sensorApi2_13
String		sensorApi3_13
String		sensorApi4_13
String		sensorLoc_14
String		sensorApi1_14
String		sensorApi2_14
String		sensorApi3_14
String		sensorApi4_14
String		sensorLoc_15
String		sensorApi1_15
String		sensorApi2_15
String		sensorApi3_15
String		sensorApi4_15
String		sensorLoc_16
String		sensorApi1_16
String		sensorApi2_16
String		sensorApi3_16
String		sensorApi4_16
String		sensorLoc_17
String		sensorApi1_17
String		sensorApi2_17
String		sensorApi3_17
String		sensorApi4_17
String		sensorLoc_18
String		sensorApi1_18
String		sensorApi2_18
String		sensorApi3_18
String		sensorApi4_18
String		sensorLoc_19
String		sensorApi1_19
String		sensorApi2_19
String		sensorApi3_19
String		sensorApi4_19
String		sensorLoc_20
String		sensorApi1_20
String		sensorApi2_20
String		sensorApi3_20
String		sensorApi4_20
String		sensorLoc_21
String		sensorApi1_21
String		sensorApi2_21
String		sensorApi3_21
String		sensorApi4_21
String		sensorLoc_22
String		sensorApi1_22
String		sensorApi2_22
String		sensorApi3_22
String		sensorApi4_22
String		sensorLoc_23
String		sensorApi1_23
String		sensorApi2_23
String		sensorApi3_23
String		sensorApi4_23
String		sensorLoc_24
String		sensorApi1_24
String		sensorApi2_24
String		sensorApi3_24
String		sensorApi4_24
String		sensorLoc_25
String		sensorApi1_25
String		sensorApi2_25
String		sensorApi3_25
String		sensorApi4_25
String		sensorLoc_26
String		sensorApi1_26
String		sensorApi2_26
String		sensorApi3_26
String		sensorApi4_26
String		sensorLoc_27
String		sensorApi1_27
String		sensorApi2_27
String		sensorApi3_27
String		sensorApi4_27
String		sensorLoc_28
String		sensorApi1_28
String		sensorApi2_28
String		sensorApi3_28
String		sensorApi4_28
String		sensorLoc_29
String		sensorApi1_29
String		sensorApi2_29
String		sensorApi3_29
String		sensorApi4_29
String		sensorLoc_30
String		sensorApi1_30
String		sensorApi2_30
String		sensorApi3_30
String		sensorApi4_30
String		sensorLoc_31
String		sensorApi1_31
String		sensorApi2_31
String		sensorApi3_31
String		sensorApi4_31
"""
#can use Uchar? for 0-255 

with open("display-cfg.h", "w") as h:
    print("""

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

enum ConfigShapeId {""", file=h)

    for cfgentry in configshape_in.strip().split('\n'):
        print("\tConfig_", cfgentry.split()[1], ",", sep='', file=h)
    print("};", file=h)

    for cfgentry in configshape_in.strip().split('\n'):
        _, cfgkey = cfgentry.split()
        print("static constexpr char CFG_KEY_", cfgkey.upper(),
              "[] PROGMEM = \"", cfgkey, "\";", sep='', file=h)

    print("static constexpr ConfigShapeEntry configShape[] PROGMEM = {",
          file=h)
    for cfgentry in configshape_in.strip().split('\n'):
        cfgtype, cfgkey = cfgentry.split()
        print("\t{ Config_Type_", cfgtype,
              ", sizeof(cfg::" + cfgkey + ")-1" if cfgtype in ('String', 'Password') else ", 0",
              ", CFG_KEY_", cfgkey.upper(),
              ", ", "" if cfgtype in ('String', 'Password') else "&",
              "cfg::", cfgkey, " },", sep='', file=h)
    print("};", file=h)
