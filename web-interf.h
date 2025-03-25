/************************************************************************
 * Adapted from parts of the AirRohr firmware                           *
 * Copyright (C) 2016-2020  Code for Stuttgart a.o.                     *
 * Copyright (C) 2019-2020  Dirk Mueller                                *
 * Copyright (C) 2021-2025  Sensor.Community                            *
 * Modifs/additions Copyright (C) 2025  Rik Drabs                       *
 *                                                                      *
 * This program is free software: you can redistribute it and/or modify *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * This program is distributed in the hope that it will be useful,      *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with this program. If not, see <http://www.gnu.org/licenses/>. *
 *                                                                      *
 ************************************************************************/

#include "c_types.h"

unsigned long last_page_load = millis();
bool wifiConfigLoop = false;

/*****************************************************************
 * Write config to spiffs                                        *
 *****************************************************************/
// Since there is not enough heap to read or write the whole block of
// parameters at once, this will be done in chunks of 70 params.

const int NUM_CHUNKS = 4;
const int PARAMS_PER_CHUNK = 70;
#define JSON_BUFFER_SIZE 2000

// Write configuration files
static bool writeConfig() 
{
  if (cfg::debugJson) 
  {
    Serial.println(FPSTR(INTL_WRITECONFIG));
  }
  // Make sure all settings are OK.
  checkSettings();

  ConfigShapeEntry c;

  // Outer loop, all chunks
  for (int chunk = 0; chunk < NUM_CHUNKS; chunk++) 
  {
    // Create JSON document for this chunk
    DynamicJsonDocument json(JSON_BUFFER_SIZE);
    json["SOFTWARE_VERSION"] = SOFTWARE_VERSION;

    // Inner loop, construct Json chunk
    for (int i = 0; i < PARAMS_PER_CHUNK; i++) 
    {
      int e = chunk * PARAMS_PER_CHUNK + i;

      // Not past very last cfg parameter ?
      if (e < sizeof(configShape) / sizeof(configShape[0])) 
      {
        memcpy_P(&c, &configShape[e], sizeof(ConfigShapeEntry));

        switch (c.cfg_type) 
        {
          case Config_Type_Bool:
            json[c.cfg_key()].set(*c.cfg_val.as_bool);
            break;
          case Config_Type_UInt:
          case Config_Type_Time:
            json[c.cfg_key()].set(*c.cfg_val.as_uint);
            break;
          case Config_Type_Password:
          case Config_Type_String:
            json[c.cfg_key()].set(c.cfg_val.as_str);
            break;
        };
      }
    }
    String fileName = CONFIG_NAME + String(chunk) + ".json";
    File file = SPIFFS.open(fileName, "w");

    if (file) 
    {
      serializeJson(json, file);
      file.close();
      if (cfg::debugJson) 
      {
        Serial.print(FPSTR(INTL_WRITESUCCESS));
        Serial.println(fileName);
      }
    } 
    else 
    {
      Serial.print(FPSTR(INTL_WRITEFAIL));
      Serial.println(fileName);
      return false;
    }
  }
  return true;
}

/*****************************************************************
 * Read config from spiffs                                       *
 *****************************************************************/
// Since there is not enough heap to read or write the whole block of
// parameters at once, this will be done in chunks of 70 params.
// See: writeConfig() above.

// Read configuration files
static void readConfig() 
{
  if (cfg::debugJson) 
  {
    Serial.println(FPSTR(INTL_READCONFIG));
  }

  bool rewriteConfig = false;

  ConfigShapeEntry c;

  // Outer loop, all chunks
  for (int chunk = 0; chunk < NUM_CHUNKS; chunk++) 
  {
    String fileName = CONFIG_NAME + String(chunk) + ".json";
    File file = SPIFFS.open(fileName, "r");

    if (!file) 
    {
      Serial.print(FPSTR(INTL_OPENFAIL));
      Serial.println(fileName);
      return;
    }
    DynamicJsonDocument json(JSON_BUFFER_SIZE);
    DeserializationError err = deserializeJson(json, file.readString());

    file.close();

    if (!err) 
    {
      // Inner loop, decode Json chunk
      for (int i = 0; i < PARAMS_PER_CHUNK; i++) 
      {
        int e = chunk * PARAMS_PER_CHUNK + i;

        // Check for very last cfg parameter
        if (e <= sizeof(configShape) / sizeof(configShape[0])) 
        {
          memcpy_P(&c, &configShape[e], sizeof(ConfigShapeEntry));

          if (json[c.cfg_key()].isNull()) 
          {
            continue;
          }

          switch (c.cfg_type) 
          {
            case Config_Type_Bool:
              *(c.cfg_val.as_bool) = json[c.cfg_key()].as<bool>();
              break;
            case Config_Type_UInt:
            case Config_Type_Time:
              *(c.cfg_val.as_uint) = json[c.cfg_key()].as<unsigned int>();
              break;
            case Config_Type_String:
            case Config_Type_Password:
              strncpy(c.cfg_val.as_str, json[c.cfg_key()].as<const char *>(), c.cfg_len);
              c.cfg_val.as_str[c.cfg_len] = '\0';
              break;
          };
        }
      }
      if (cfg::debugJson) 
      {
        Serial.print(FPSTR(INTL_READSUCCESS));
        Serial.println(fileName);

        if (cfg::debugShowData) 
        {
          serializeJsonPretty(json, Serial);
          Serial.print('\n');
        }
      }

      String writtenVersion(json["SOFTWARE_VERSION"].as<const char *>());

      if (writtenVersion.length() && (writtenVersion[0] == 'v') && (SOFTWARE_VERSION != writtenVersion)) 
      {
        Serial.println(FPSTR(INTL_FORMATSPIFFS));
        SPIFFS.format();
        rewriteConfig = true;
      }
    } 
    else 
    {
      Serial.print(FPSTR(INTL_JSONPARSING_ERR));
      Serial.println(err.f_str());
    }
  }

  // Rewrite config when when asked for
  if (rewriteConfig) 
  {
    Serial.println(FPSTR(INTL_REWRITECONFIG));
    writeConfig();
  }
}

// Prepare & read config files (called from startup)
static void initConfig() 
{
  Serial.println(FPSTR(INTL_MOUNT_FS));

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
  bool spiffs_begin_ok = SPIFFS.begin();
#pragma GCC diagnostic pop

  if (!spiffs_begin_ok) 
  {
    Serial.println(FPSTR(INTL_FAILMOUNT_FS));
    return;
  }
  readConfig();
}

/*****************************************************************
 * Save average & peak values from/to spiffs                     *
 *****************************************************************/
// Save average & peak values in case of (short) power outage.
void saveAvgAndPeak() 
{
  if (cfg::debugJson) 
  {
    Serial.println(FPSTR(INTL_WRITEAVGNPEAK));
  }

  // Create JSON document
  DynamicJsonDocument json(JSON_BUFFER_SIZE);

  // Fill Json document with data
  for (int e = 0; e < LOCATION_MAX; e++) 
  {
    json[e]["cumulavg25"] = cumulAvgPm25[e];
    json[e]["cumulcnt25"] = cumulAvgPm25Cnt[e];
    json[e]["peakpm25"]   = peakPm25[e];  
    json[e]["peak0pm25"]  = peak0Pm25[e];  
    json[e]["peak4pm25"]  = peak4Pm25[e];
    json[e]["peak8pm25"]  = peak8Pm25[e];
    json[e]["peak12pm25"] = peak12Pm25[e];
    json[e]["peak16pm25"] = peak16Pm25[e];
    json[e]["peak20pm25"] = peak20Pm25[e];
    //
    json[e]["cumulavg10"] = cumulAvgPm10[e];
    json[e]["cumulcnt10"] = cumulAvgPm10Cnt[e];
    json[e]["peakpm10"]   = peakPm10[e];  
    json[e]["peak0pm10"]  = peak0Pm10[e];  
    json[e]["peak4pm10"]  = peak4Pm10[e];
    json[e]["peak8pm10"]  = peak8Pm10[e];
    json[e]["peak12pm10"] = peak12Pm10[e];
    json[e]["peak16pm10"] = peak16Pm10[e];
    json[e]["peak20pm10"] = peak20Pm10[e];
  }

  // Create or open file for writing
  String fileName = String(AVG_PEAK_NAME) + ".json";
  File file = SPIFFS.open(fileName, "w");

  if (file) 
  {
    // Write Json to file
    serializeJson(json, file);

    file.close();
    if (cfg::debugJson) 
    {
      Serial.print(FPSTR(INTL_WRITESUCCESS));
      Serial.println(fileName);
    }
  } 
  else 
  {
    Serial.print(FPSTR(INTL_WRITEFAIL));
    Serial.println(fileName);
  }
}

/*****************************************************************
 * Restore average & peak values from/to spiffs                  *
 *****************************************************************/
// Restore average & peak values after a (short) power outage.
void restoreAvgAndPeak() 
{
  if (cfg::debugJson) 
  {
    Serial.println(FPSTR(INTL_READAVGNPEAK));
  }

  String fileName = String(AVG_PEAK_NAME) + ".json";
  File file = SPIFFS.open(fileName, "r");

  if (!file) 
  {
    Serial.print(FPSTR(INTL_OPENFAIL));
    Serial.println(fileName);
    return;
  }

  // Create JSON document  
  DynamicJsonDocument json(JSON_BUFFER_SIZE);
  DeserializationError err = deserializeJson(json, file.readString());

  file.close();

  if (!err) 
  {
    // Decode Json
    for (int e = 0; e < LOCATION_MAX; e++) 
    {
      if (json[e].isNull()) 
      {
        continue;
      } 
      cumulAvgPm25[e]    = json[e]["cumulavg25"];
      cumulAvgPm25Cnt[e] = json[e]["cumulcnt25"];
      peakPm25[e]   = json[e]["peakpm25"];
      peak0Pm25[e]  = json[e]["peak0pm25"];  
      peak4Pm25[e]  = json[e]["peak4pm25"];
      peak8Pm25[e]  = json[e]["peak8pm25"];
      peak12Pm25[e] = json[e]["peak12pm25"];
      peak16Pm25[e] = json[e]["peak16pm25"];
      peak20Pm25[e] = json[e]["peak20pm25"];
      //
      cumulAvgPm10[e]    = json[e]["cumulavg10"];
      cumulAvgPm10Cnt[e] = json[e]["cumulcnt10"];
      peakPm10[e]   = json[e]["peakpm10"];
      peak0Pm10[e]  = json[e]["peak0pm10"];  
      peak4Pm10[e]  = json[e]["peak4pm10"];
      peak8Pm10[e]  = json[e]["peak8pm10"];
      peak12Pm10[e] = json[e]["peak12pm10"];
      peak16Pm10[e] = json[e]["peak16pm10"];
      peak20Pm10[e] = json[e]["peak20pm10"];      

    }

    if (cfg::debugJson) 
    {
      Serial.print(FPSTR(INTL_READSUCCESS));
      Serial.println(fileName);

      if (cfg::debugShowData) 
      {
        serializeJsonPretty(json, Serial);
        Serial.print('\n');
      }
    }
  } 
  else 
  {
    Serial.print(FPSTR(INTL_JSONPARSING_ERR));
    Serial.println(err.f_str());
  }
}

/*****************************************************************
 * html helper functions                                         *
 *****************************************************************/
//
static void start_html_page(String &page_content, const String &title) 
{
  last_page_load = millis();

  RESERVE_STRING(s, LARGE_STR);
  s = FPSTR(WEB_PAGE_HEADER);
  s.replace("{t}", title);
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send(200, FPSTR(TXT_CONTENT_TYPE_TEXT_HTML), s);

  server.sendContent_P(WEB_PAGE_HEADER_HEAD);

  s = FPSTR(WEB_PAGE_HEADER_BODY);

  s.replace("{t}", title);
  if (title != " ") 
  {
    s.replace("{n}", F("&raquo;"));
  } 
  else 
  {
    s.replace("{n}", emptyString);
  }
  page_content += s;
}

// Construct bottom part screen
static void end_html_page(String &page_content, bool showBackButton) 
{
  if (page_content.length()) 
  {
    server.sendContent(page_content);
  }
  if (showBackButton)
  {
    server.sendContent_P(WEB_PAGE_FOOTER1);
  }  
  server.sendContent_P(WEB_PAGE_FOOTER_INFO);
}

// Construct bottom part screen
static void end_html_page_discard(String &page_content) 
{
  if (page_content.length()) 
  {
    server.sendContent(page_content);
  }
  if (!wifiConfigLoop) 
  {
    server.sendContent_P(WEB_PAGE_FOOTER2);
  }
  server.sendContent_P(WEB_PAGE_FOOTER_INFO);
}

// Add title row to location / sensors table
static void add_location_row_title(String &page_content,
                                   const __FlashStringHelper *name, const int len_name,
                                   const __FlashStringHelper *api_1, const int len_api_1,
                                   const __FlashStringHelper *api_2, const int len_api_2,
                                   const __FlashStringHelper *api_3, const int len_api_3,
                                   const __FlashStringHelper *api_4, const int len_api_4) 
{
  RESERVE_STRING(s, MED_STR);
  s = FPSTR(WEB_LOCATION_ROW_TITLE);

  s.replace("{n}", name);
  s.replace("{1}", api_1);
  s.replace("{2}", api_2);
  s.replace("{3}", api_3);
  s.replace("{4}", api_4);
  s.replace("{wn}", String(len_name));
  s.replace("{w1}", String(len_api_1));
  s.replace("{w2}", String(len_api_2));
  s.replace("{w3}", String(len_api_3));
  s.replace("{w4}", String(len_api_4));

  page_content += s;
}

// Add input row to location / sensors table -- only String type entry allowed !!
static void add_location_row_input(String &page_content,
                                   const ConfigShapeId location_name,
                                   const ConfigShapeId sensor_api_1, const ConfigShapeId sensor_api_2,
                                   const ConfigShapeId sensor_api_3, const ConfigShapeId sensor_api_4) 
{
  String t_value;
  String len_field;
  ConfigShapeEntry c;

  RESERVE_STRING(s, MED_STR);
  s = FPSTR(WEB_PAGE_ROW_INPUT);

  memcpy_P(&c, &configShape[location_name], sizeof(ConfigShapeEntry));
  t_value = String(c.cfg_val.as_str);
  len_field = String(LEN_LOCATION_NAME);

  s.replace("{nn}", String(c.cfg_key()));
  s.replace("{vn}", t_value);
  s.replace("{wn}", len_field);
  s.replace("{tx}", "text");

  memcpy_P(&c, &configShape[sensor_api_1], sizeof(ConfigShapeEntry));
  t_value = String(c.cfg_val.as_str);
  len_field = String(LEN_SENSOR_API_1);
  s.replace("{n1}", String(c.cfg_key()));
  s.replace("{v1}", t_value);
  s.replace("{w1}", len_field);

  memcpy_P(&c, &configShape[sensor_api_2], sizeof(ConfigShapeEntry));
  t_value = String(c.cfg_val.as_str);
  len_field = String(LEN_SENSOR_API_2);
  s.replace("{n2}", String(c.cfg_key()));
  s.replace("{v2}", t_value);
  s.replace("{w2}", len_field);

  memcpy_P(&c, &configShape[sensor_api_3], sizeof(ConfigShapeEntry));
  t_value = String(c.cfg_val.as_str);
  len_field = String(LEN_SENSOR_API_3);
  s.replace("{n3}", String(c.cfg_key()));
  s.replace("{v3}", t_value);
  s.replace("{w3}", len_field);

  memcpy_P(&c, &configShape[sensor_api_4], sizeof(ConfigShapeEntry));
  t_value = String(c.cfg_val.as_str);
  len_field = String(LEN_SENSOR_API_4);
  s.replace("{n4}", String(c.cfg_key()));
  s.replace("{v4}", t_value);
  s.replace("{w4}", len_field);

  page_content += s;
}

// Add title row with 2 location tabs & 1 measurement tab
static void add_row_sel_title(String &page_content,
                              const __FlashStringHelper *name_1, const int len_name_1,
                              const __FlashStringHelper *name_2, const int len_name_2,
                              String name_3, const int len_name_3) 
{
  RESERVE_STRING(s, MED_STR);
  s = FPSTR(WEB_PAGE_ROW_SEL_TITLE);
  s.replace("{n1}", name_1);
  s.replace("{n2}", name_2);
  s.replace("{n3}", name_3);
  s.replace("{w1}", String(len_name_1));
  s.replace("{w2}", String(len_name_2));
  s.replace("{w3}", String(len_name_3));

  page_content += s;
}

// Add select row with 2 locations & 2 measurments to the table
static void add_row_select(String &page_content,
                           const ConfigShapeId location_name_1, int location_1,
                           const ConfigShapeId location_name_2, int location_2,
                           const String valueString_1, const String valueString_2) 
{
  String t_value;
  String len_field;
  String len_result;
  ConfigShapeEntry c;

  RESERVE_STRING(s, MED_STR);
  s = FPSTR(WEB_PAGE_ROW_SELECT);

  memcpy_P(&c, &configShape[location_name_1], sizeof(ConfigShapeEntry));
  t_value = String(c.cfg_val.as_str);

  if (t_value != emptyString) 
  {
    s.replace("{nam1}", "<a href='/values{s1}'><button> {v1} </button></a>");
    s.replace("{s1}", String(location_1));
    s.replace("{v1}", t_value);
  } 
  else 
  {
    s.replace("{nam1}", "<a href='/values'><button> </button></a>");
  }

  memcpy_P(&c, &configShape[location_name_2], sizeof(ConfigShapeEntry));
  t_value = String(c.cfg_val.as_str);

  if (t_value != emptyString) 
  {
    s.replace("{nam2}", "<a href='/values{s2}'><button> {v2} </button></a>");
    s.replace("{s2}", String(location_2));
    s.replace("{v2}", t_value);
  } 
  else 
  {
    s.replace("{nam2}", emptyString);
  }

  len_field = String(LEN_LOCATION_NAME);
  s.replace("{w}", len_field);

  if (valueString_1 == "--") 
  {
    s.replace("{val1}", emptyString);
  } 
  else 
  {
    s.replace("{val1}", "<input type='button' size='20' value='{v3}'/>");
    s.replace("{v3}", String(valueString_1));
  }
  if (valueString_2 == "--") 
  {
    s.replace("{val2}", emptyString);
  } 
  else 
  {
    s.replace("{val2}", "<input type='button' value='{v4}'/>");
    s.replace("{v4}", String(valueString_2));
  }
  len_result = String(LEN_MEASUREMENTS);
  s.replace("{w1}", len_result);

  page_content += s;
}

// Get input in a form
static void add_form_input(String &page_content, const ConfigShapeId cfgid, 
                          const __FlashStringHelper *info, const int length) 
{
  RESERVE_STRING(s, MED_STR);
  s = FPSTR(WEB_PAGE_FORM_INPUT);

  String t_value;
  ConfigShapeEntry c;
  memcpy_P(&c, &configShape[cfgid], sizeof(ConfigShapeEntry));

  switch (c.cfg_type) 
  {
    case Config_Type_UInt:
      t_value = String(*c.cfg_val.as_uint);
      s.replace("{t}", F("number"));
      break;
    case Config_Type_Time:
      t_value = String((*c.cfg_val.as_uint) / 1000);
      s.replace("{t}", F("number"));
      break;
    case Config_Type_Bool:
      break;
    case Config_Type_Password:
      s.replace("{t}", F("password"));
      info = FPSTR(INTL_PASSWORD);
      break;
    case Config_Type_String:
      t_value = String(c.cfg_val.as_str);
      s.replace("{t}", F("text"));
      break;
  }
  s.replace("{i}", info);
  s.replace("{n}", String(c.cfg_key()));
  s.replace("{v}", t_value);
  //
  if (length == 99)  //100-1
  {
    s.replace("{o}", " style='width:10em'");
    s.replace("{l}", String(length - 10));
    s.replace("{l2}", String(length - 30));
  } 
  else 
  {
    s.replace("{o}", emptyString);
    s.replace("{l}", String(length));
    s.replace("{l2}", String(length / 2));
  }
  page_content += s;
}

// Get pmChoice value with horizontal row radio buttons
static void add_hor_radio2(String &page_content, const ConfigShapeId cfgid,
                           const __FlashStringHelper *info) 
{
  ConfigShapeEntry c;
  memcpy_P(&c, &configShape[cfgid], sizeof(ConfigShapeEntry));
  String t_value;
  t_value = String(*c.cfg_val.as_uint);

  RESERVE_STRING(s, MED_STR);
  s = FPSTR(WEB_PAGE_HOR_RADIO2);
  s.replace("{i}", info);
  s.replace("{n}", String(c.cfg_key()));
  if (t_value == "0") 
  { 
    s.replace("{c0}", " checked"); 
  }
  if (t_value == "1") 
  { 
    s.replace("{c1}", " checked");
  }
  s.replace("{c0}", emptyString);
  s.replace("{c1}", emptyString);

  page_content += s;
}

static String formCheckbox(const ConfigShapeId cfgid, const String &info) 
{
  RESERVE_STRING(s, MED_STR);
  s = FPSTR(WEB_PAGE_FORM_CHECKBOX);

  if (*configShape[cfgid].cfg_val.as_bool) 
  {
    s.replace("{c}", F(" checked='checked'"));
  } 
  else 
  {
    s.replace("{c}", emptyString);
  };
  s.replace("{i}", info);
  s.replace("{n}", String(configShape[cfgid].cfg_key()));
  return s;
}

/**********************************************************************
 * Webserver request auth: prompt for BasicAuth                       *
 * Provide BasicAuth for all page contexts                            *
 **********************************************************************/
//
static bool webserver_request_auth() 
{
  if (cfg::www_basicauth_enabled && !wifiConfigLoop) 
  {
    Serial.println(FPSTR(INTL_VALREQ_AUTH));
    if (!server.authenticate(cfg::www_username, cfg::www_password)) 
    {
      server.requestAuthentication(BASIC_AUTH, "Display Login", FPSTR(INTL_AUTH_FAIL));
      return false;
    }
  }
  return true;
}

/*****************************************************************
 * At startup, redirect to 192.168.4.1/config                    *
 *****************************************************************/
//
static void sendHttpRedirect() 
{
  server.sendHeader(F("Location"), F("http://192.168.4.1/config"));
  server.send(302, FPSTR(TXT_CONTENT_TYPE_TEXT_HTML), emptyString);
}

/*****************************************************************
 * Webserver root: show all base options                         *
 *****************************************************************/
//
static void webserver_root() 
{
  if (WiFi.status() != WL_CONNECTED) 
  {
    sendHttpRedirect();
    return;
  }
  if (!webserver_request_auth()) 
  {
    return;
  }
  RESERVE_STRING(page_content, XLARGE_STR);
  start_html_page(page_content, emptyString);

  page_content += FPSTR(WEB_ROOT_PAGE_CONTENT);

  page_content.replace(F("{t}"), FPSTR(INTL_CURRENT_DATA));
  page_content.replace(F("{conf}"), FPSTR(INTL_CONFIGURATION));
  page_content.replace(F("{param}"), FPSTR(INTL_ADVANCED_SETTINGS));
  page_content.replace(F("{confdel}"), FPSTR(INTL_DELETE_CONFIG));
  page_content.replace(F("{restart}"), FPSTR(INTL_RESTART_DISPLAY));

  end_html_page(page_content, false /* Show Backbutton */);
}

// Construct submit knob
static String form_submit(const String &value) 
{
  String s = FPSTR(WEB_PAGE_FORM_SUBMIT);
  s.replace("{v}", value);
  return s;
}

/*****************************************************************
 * Webserver config: show configuration page                            *
 *****************************************************************/
//
static void webserver_config_send_body_get(String &page_content) 
{
  if (wifiConfigLoop) 
  {
    showOnDisplay(INTL_CONFIG_BUSY);
  }
  auto add_form_checkbox = [&page_content](const ConfigShapeId cfgid, const String &info) 
  {
    page_content += formCheckbox(cfgid, info);
  };
  page_content += F("<form method='POST' action='/config' style='width:100%;'>\n"
                    "<input class='radio' id='r1' name='group' type='radio' checked>"
                    "<input class='radio' id='r2' name='group' type='radio'>"
                    "<input class='radio' id='r3' name='group' type='radio'>"
                    "<input class='radio' id='r4' name='group' type='radio'>"
                    "<input class='radio' id='r5' name='group' type='radio'>"
                    "<div class='tabs'>"
                    "<label class='tab' id='tab1' for='r1'>");
  page_content += FPSTR(INTL_WIFI_SETTINGS);
  page_content += F("</label>");

  page_content += F("<label class='tab' id='tab2' for='r2'>");
  page_content += FPSTR(INTL_LOCATION_0_15);
  page_content += F("</label>");

  if (wifiConfigLoop) 
  {
    page_content += F("<label class='tab' id='tab3' for='r3'>");
    page_content += FPSTR(INTL_DISPLAY_SETTINGS);
    page_content += F("</label></div>");
  } 
  else 
  {
    page_content += F("<label class='tab' id='tab3' for='r3'>");
    page_content += FPSTR(INTL_LOCATION_16_31);
    page_content += F("</label>");

    page_content += F("<label class='tab' id='tab4' for='r4'>");
    page_content += FPSTR(INTL_DISPLAY_SETTINGS);
    page_content += F("</label>");

    page_content += F("<label class='tab' id='tab5' for='r5'>");
    page_content += FPSTR(INTL_SETTINGS);
    page_content += F("</label></div>");
  }
  page_content += F("<div class='panels'>"
                    "<div class='panel' id='panel1'>");

  if (wifiConfigLoop) 
  {
    // Loading WiFi networks message
    page_content += F("<div id='wifilist'>" INTL_LOADING_WIFI_NETWORKS "</div><br/>");
  }
  page_content += FPSTR(TABLE_TAG_OPEN);
  add_form_input(page_content, Config_wlanssid, FPSTR(INTL_FS_WIFI_NAME), LEN_SSID - 1);
  add_form_input(page_content, Config_wlanpwd, FPSTR(INTL_PASSWORD), LEN_PASSWORD - 1);
  page_content += FPSTR(TABLE_TAG_CLOSE_BR);
  //
  page_content += F("<hr/>");
  //
  page_content += FPSTR(WEB_BR_LF_B);
  page_content += FPSTR(INTL_AB_HIER_NUR_ANDERN);
  page_content += FPSTR(WEB_B_BR);
  page_content += FPSTR(BR_TAG);

  server.sendContent(page_content);
  page_content = emptyString;

  add_form_checkbox(Config_www_basicauth_enabled, FPSTR(INTL_BASICAUTH));
  page_content += FPSTR(TABLE_TAG_OPEN);
  add_form_input(page_content, Config_www_username, FPSTR(INTL_USER), LEN_WWW_USERNAME - 1);
  add_form_input(page_content, Config_www_password, FPSTR(INTL_PASSWORD), LEN_PASSWORD - 1);
  page_content += FPSTR(TABLE_TAG_CLOSE_BR);

  server.sendContent(page_content);

  if (!wifiConfigLoop) 
  {
    // WiFi Display in configuration mode
    page_content = FPSTR(WEB_BR_LF_B);
    page_content += FPSTR(INTL_FS_WIFI_DESCRIPTION);
    page_content += FPSTR(WEB_B_BR);
    page_content += FPSTR(BR_TAG);

    page_content += FPSTR(TABLE_TAG_OPEN);
    add_form_input(page_content, Config_fs_ssid, FPSTR(INTL_FS_WIFI_NAME), LEN_SSID - 1);
    add_form_input(page_content, Config_fs_pwd, FPSTR(INTL_PASSWORD), LEN_PASSWORD - 1);
    page_content += FPSTR(TABLE_TAG_CLOSE_BR);

    server.sendContent(page_content);
  }

  // ===== Tab 2  Locations 0-15
  page_content = tmpl(FPSTR(WEB_DIV_PANEL), String(2));
  page_content += FPSTR(BR_TAG);

  page_content += FPSTR(TABLE_TAG_OPEN);
  add_location_row_title(page_content, FPSTR(INTL_LOCATION_NAME), LEN_LOCATION_NAME,
                         FPSTR(INTL_SENSOR_API_1), LEN_SENSOR_API_1,
                         FPSTR(INTL_SENSOR_API_2), LEN_SENSOR_API_2,
                         FPSTR(INTL_SENSOR_API_3), LEN_SENSOR_API_3,
                         FPSTR(INTL_SENSOR_API_4), LEN_SENSOR_API_4);

  add_location_row_input(page_content, Config_sensorLoc_0,
                         Config_sensorApi1_0, Config_sensorApi2_0,
                         Config_sensorApi3_0, Config_sensorApi4_0);
  add_location_row_input(page_content, Config_sensorLoc_1,
                         Config_sensorApi1_1, Config_sensorApi2_1,
                         Config_sensorApi3_1, Config_sensorApi4_1);
  add_location_row_input(page_content, Config_sensorLoc_2,
                         Config_sensorApi1_2, Config_sensorApi2_2,
                         Config_sensorApi3_2, Config_sensorApi4_2);
  add_location_row_input(page_content, Config_sensorLoc_3,
                         Config_sensorApi1_3, Config_sensorApi2_3,
                         Config_sensorApi3_3, Config_sensorApi4_3);

  server.sendContent(page_content);
  page_content = emptyString;

  add_location_row_input(page_content, Config_sensorLoc_4,
                         Config_sensorApi1_4, Config_sensorApi2_4,
                         Config_sensorApi3_4, Config_sensorApi4_4);
  add_location_row_input(page_content, Config_sensorLoc_5,
                         Config_sensorApi1_5, Config_sensorApi2_5,
                         Config_sensorApi3_5, Config_sensorApi4_5);
  add_location_row_input(page_content, Config_sensorLoc_6,
                         Config_sensorApi1_6, Config_sensorApi2_6,
                         Config_sensorApi3_6, Config_sensorApi4_6);
  add_location_row_input(page_content, Config_sensorLoc_7,
                         Config_sensorApi1_7, Config_sensorApi2_7,
                         Config_sensorApi3_7, Config_sensorApi4_7);

  server.sendContent(page_content);
  page_content = emptyString;

  add_location_row_input(page_content, Config_sensorLoc_8,
                         Config_sensorApi1_8, Config_sensorApi2_8,
                         Config_sensorApi3_8, Config_sensorApi4_8);
  add_location_row_input(page_content, Config_sensorLoc_9,
                         Config_sensorApi1_9, Config_sensorApi2_9,
                         Config_sensorApi3_9, Config_sensorApi4_9);
  add_location_row_input(page_content, Config_sensorLoc_10,
                         Config_sensorApi1_10, Config_sensorApi2_10,
                         Config_sensorApi3_10, Config_sensorApi4_10);
  add_location_row_input(page_content, Config_sensorLoc_11,
                         Config_sensorApi1_11, Config_sensorApi2_11,
                         Config_sensorApi3_11, Config_sensorApi4_11);

  server.sendContent(page_content);
  page_content = emptyString;

  add_location_row_input(page_content, Config_sensorLoc_12,
                         Config_sensorApi1_12, Config_sensorApi2_12,
                         Config_sensorApi3_12, Config_sensorApi4_12);
  add_location_row_input(page_content, Config_sensorLoc_13,
                         Config_sensorApi1_13, Config_sensorApi2_13,
                         Config_sensorApi3_13, Config_sensorApi4_13);
  add_location_row_input(page_content, Config_sensorLoc_14,
                         Config_sensorApi1_14, Config_sensorApi2_14,
                         Config_sensorApi3_14, Config_sensorApi4_14);
  add_location_row_input(page_content, Config_sensorLoc_15,
                         Config_sensorApi1_15, Config_sensorApi2_15,
                         Config_sensorApi3_15, Config_sensorApi4_15);
  page_content += FPSTR(TABLE_TAG_CLOSE_BR);

  server.sendContent(page_content);

  // ===== Tab 3  Locations 16-31
  if (!wifiConfigLoop) 
  {
    page_content = tmpl(FPSTR(WEB_DIV_PANEL), String(3));
    page_content += FPSTR(BR_TAG);
    page_content += FPSTR(TABLE_TAG_OPEN);

    add_location_row_title(page_content, FPSTR(INTL_LOCATION_NAME), LEN_LOCATION_NAME,
                           FPSTR(INTL_SENSOR_API_1), LEN_SENSOR_API_1,
                           FPSTR(INTL_SENSOR_API_2), LEN_SENSOR_API_2,
                           FPSTR(INTL_SENSOR_API_3), LEN_SENSOR_API_3,
                           FPSTR(INTL_SENSOR_API_4), LEN_SENSOR_API_4);

    add_location_row_input(page_content, Config_sensorLoc_16,
                           Config_sensorApi1_16, Config_sensorApi2_16,
                           Config_sensorApi3_16, Config_sensorApi4_16);
    add_location_row_input(page_content, Config_sensorLoc_17,
                           Config_sensorApi1_17, Config_sensorApi2_17,
                           Config_sensorApi3_17, Config_sensorApi4_17);
    add_location_row_input(page_content, Config_sensorLoc_18,
                           Config_sensorApi1_18, Config_sensorApi2_18,
                           Config_sensorApi3_18, Config_sensorApi4_18);
    add_location_row_input(page_content, Config_sensorLoc_19,
                           Config_sensorApi1_19, Config_sensorApi2_19,
                           Config_sensorApi3_19, Config_sensorApi4_19);

    server.sendContent(page_content);
    page_content = emptyString;

    add_location_row_input(page_content, Config_sensorLoc_20,
                           Config_sensorApi1_20, Config_sensorApi2_20,
                           Config_sensorApi3_20, Config_sensorApi4_20);
    add_location_row_input(page_content, Config_sensorLoc_21,
                           Config_sensorApi1_21, Config_sensorApi2_21,
                           Config_sensorApi3_21, Config_sensorApi4_21);
    add_location_row_input(page_content, Config_sensorLoc_22,
                           Config_sensorApi1_22, Config_sensorApi2_22,
                           Config_sensorApi3_22, Config_sensorApi4_22);
    add_location_row_input(page_content, Config_sensorLoc_23,
                           Config_sensorApi1_23, Config_sensorApi2_23,
                           Config_sensorApi3_23, Config_sensorApi4_23);

    server.sendContent(page_content);
    page_content = emptyString;

    add_location_row_input(page_content, Config_sensorLoc_24,
                           Config_sensorApi1_24, Config_sensorApi2_24,
                           Config_sensorApi3_24, Config_sensorApi4_24);
    add_location_row_input(page_content, Config_sensorLoc_25,
                           Config_sensorApi1_25, Config_sensorApi2_25,
                           Config_sensorApi3_25, Config_sensorApi4_25);
    add_location_row_input(page_content, Config_sensorLoc_26,
                           Config_sensorApi1_26, Config_sensorApi2_26,
                           Config_sensorApi3_26, Config_sensorApi4_26);
    add_location_row_input(page_content, Config_sensorLoc_27,
                           Config_sensorApi1_27, Config_sensorApi2_27,
                           Config_sensorApi3_27, Config_sensorApi4_27);

    server.sendContent(page_content);
    page_content = emptyString;

    add_location_row_input(page_content, Config_sensorLoc_28,
                           Config_sensorApi1_28, Config_sensorApi2_28,
                           Config_sensorApi3_28, Config_sensorApi4_28);
    add_location_row_input(page_content, Config_sensorLoc_29,
                           Config_sensorApi1_29, Config_sensorApi2_29,
                           Config_sensorApi3_29, Config_sensorApi4_29);
    add_location_row_input(page_content, Config_sensorLoc_30,
                           Config_sensorApi1_30, Config_sensorApi2_30,
                           Config_sensorApi3_30, Config_sensorApi4_30);
    add_location_row_input(page_content, Config_sensorLoc_31,
                           Config_sensorApi1_31, Config_sensorApi2_31,
                           Config_sensorApi3_31, Config_sensorApi4_31);

    page_content += FPSTR(TABLE_TAG_CLOSE_BR);

    server.sendContent(page_content);
  }

  // ===== Tab 4 (3 in WiFiconfig mode) Display settings
  if (wifiConfigLoop) 
  {
    page_content = tmpl(FPSTR(WEB_DIV_PANEL), String(3));
  } 
  else 
  {
    page_content = tmpl(FPSTR(WEB_DIV_PANEL), String(4));
  }

  page_content += FPSTR(WEB_BR_LF_B);
  page_content += FPSTR(INTL_DISPLAY_OPTIONS);
  page_content += FPSTR(WEB_B_BR);
  page_content += FPSTR(BR_TAG);

  page_content += FPSTR(TABLE_TAG_OPEN);
  add_form_checkbox(Config_multiCompare, FPSTR(INTL_MULTICOMPARE));
  add_form_checkbox(Config_multiAverage, FPSTR(INTL_MULTIAVERAGE));  
  add_form_checkbox(Config_sensorMissing, FPSTR(INTL_SENSORMISSING));
  add_form_checkbox(Config_showMeteo, FPSTR(INTL_SHOWMETEO));      
  add_form_checkbox(Config_showPmPm, FPSTR(INTL_SHOWPMPM));
  add_form_checkbox(Config_showPm1Pm4, FPSTR(INTL_SHOWPM1PM4));

  if ((cfg::compareLocation) != (cfg::compareLocation2)) 
  {
    add_form_checkbox(Config_showComp, FPSTR(INTL_SHOWCOMP));
    add_form_checkbox(Config_showCompInside, FPSTR(INTL_SHOWCOMPINSIDE));
  }
  add_form_checkbox(Config_showGraph, FPSTR(INTL_SHOWGRAPH));
  add_form_checkbox(Config_showAqiAdvice, FPSTR(INTL_SHOWAQIADVICE));
  add_form_checkbox(Config_showWhoAdvice, FPSTR(INTL_SHOWWHOADVICE));
  add_form_checkbox(Config_showAvgNpeak, FPSTR(INTL_SHOWAVGNPEAK));
  add_form_checkbox(Config_showDnms, FPSTR(INTL_SHOWDNMS));
  add_form_checkbox(Config_showTelRaam, FPSTR(INTL_SHOWTELRAAM));
  page_content += FPSTR(TABLE_TAG_CLOSE_BR);

  server.sendContent(page_content);

  if (!wifiConfigLoop) 
  {
    // ===== Tab 5  General settings (not in WiFi config mode)
    page_content = tmpl(FPSTR(WEB_DIV_PANEL), String(5));

    page_content += FPSTR(WEB_BR_LF_B);
    page_content += FPSTR(INTL_VALUES_TEXT);
    page_content += FPSTR(WEB_B_BR);
    page_content += FPSTR(BR_TAG);

    page_content += FPSTR(TABLE_TAG_OPEN);
    add_form_input(page_content, Config_welkom, FPSTR(INTL_WELCOME), LEN_WELCOME);
    add_form_input(page_content, Config_welkom2, FPSTR(INTL_WELCOME2), LEN_WELCOME);
    add_form_input(page_content, Config_timeZoneStr, FPSTR(INTL_TIMEZONESTR), LEN_TZ_STR);
    add_form_input(page_content, Config_clockSeconds, FPSTR(INTL_CLOCKSECONDS), 2);
    add_form_input(page_content, Config_displaySpeed, FPSTR(INTL_DISPLAYSPEED), 2);
    add_form_input(page_content, Config_pauseTime, FPSTR(INTL_PAUSETIME), 2);
    add_form_input(page_content, Config_welkomInterval, FPSTR(INTL_WELCOMEINTERVAL), 2);
    add_form_input(page_content, Config_callingInterval, FPSTR(INTL_CALLINGINTERVAL), 2);
    add_form_input(page_content, Config_sensordataTimeout, FPSTR(INTL_SENSORDATATIMEOUT), 2);
    page_content += FPSTR(TABLE_TAG_CLOSE_BR);
    server.sendContent(page_content);

    page_content = FPSTR(WEB_BR_LF_B);
    page_content += FPSTR(INTL_DEBUG_SETTINGS);
    page_content += FPSTR(WEB_B_BR);
    page_content += FPSTR(BR_TAG);

    page_content += FPSTR(TABLE_TAG_OPEN);
    add_form_checkbox(Config_debugShowData, FPSTR(INTL_DEBUGSHOWDATA));
    add_form_checkbox(Config_debugDisplay, FPSTR(INTL_DEBUGDISPLAY));
    add_form_checkbox(Config_debugComms, FPSTR(INTL_DEBUGCOMMS));
    add_form_checkbox(Config_debugHeap, FPSTR(INTL_DEBUGHEAP));
    add_form_checkbox(Config_debugJson, FPSTR(INTL_DEBUGJSON));
    page_content += FPSTR(TABLE_TAG_CLOSE_BR);

    server.sendContent(page_content);
  }
  // ===== Footer
  page_content = F("</div></div>");

  if (wifiConfigLoop) 
  {
    page_content += form_submit(FPSTR(INTL_SAVE_RESTART));
  } 
  else 
  {
    page_content += form_submit(FPSTR(INTL_SAVE_CONFIG));
  }

  page_content += FPSTR(BR_TAG);
  page_content += FPSTR(WEB_BR_FORM);

  if (wifiConfigLoop) 
  {
    // execute script, scanning for wlan ssids
    page_content += F("<script>window.setTimeout(load_wifi_list,2000);</script>");
  }
  server.sendContent(page_content);
  page_content = emptyString;
}

static void webserver_config_send_body_post(String &page_content) 
{
  String masked_pwd;
  for (unsigned e = 0; e < sizeof(configShape) / sizeof(configShape[0]); ++e) 
  {
    ConfigShapeEntry c;
    memcpy_P(&c, &configShape[e], sizeof(ConfigShapeEntry));
    const String s_param(c.cfg_key());
    if (!server.hasArg(s_param)) 
    {
      continue;
    }
    const String server_arg(server.arg(s_param));

    switch (c.cfg_type) 
    {
      case Config_Type_UInt:
        *(c.cfg_val.as_uint) = server_arg.toInt();
        break;
      case Config_Type_Time:
        *(c.cfg_val.as_uint) = server_arg.toInt() * 1000;
        break;
      case Config_Type_Bool:
        *(c.cfg_val.as_bool) = (server_arg == "1");
        break;
      case Config_Type_String:
        strncpy(c.cfg_val.as_str, server_arg.c_str(), c.cfg_len);
        c.cfg_val.as_str[c.cfg_len] = '\0';
        break;
      case Config_Type_Password:
        if (server_arg.length()) 
        {
          server_arg.toCharArray(c.cfg_val.as_str, LEN_PASSWORD);
        }
        break;
    }
  }
  if (wifiConfigLoop)
  {
    page_content += FPSTR(INTL_DISPLAY_IS_REBOOTING);
  }  
  server.sendContent(page_content);
  page_content = emptyString;
}

DNSServer dnsServer;

// Handle all requests for web interface
void handleWebServer() 
{
  MDNS.update();
  dnsServer.processNextRequest();
  server.handleClient();

  // Prevent watchdog timeout
  wdt_reset();
  yield();
}

static void display_restart() 
{
  float milliStart = millis();
  while (millis() < milliStart + 2000) 
  {
    handleWebServer();
    delay(100);
  }

  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
  delay(1000);
  SPIFFS.end();
  delay(500);

  Serial.print(FPSTR(INTL_UPTIME));
  Serial.println(delayToString(millis() - atLastStartup));
  Serial.println(FPSTR(INTL_ESP_RESTART));

  delay(500);
  ESP.restart();

  while (true) 
  {
    yield();
    Serial.println(FPSTR(INTL_NOT_REACHED));
    delay(2500);
  }
}

// Webserver configuration
static void webserver_config() 
{
  if (!webserver_request_auth()) 
  {
    return;
  }
  server.sendHeader(F("Cache-Control"), F("no-cache, no-store, must-revalidate"));
  server.sendHeader(F("Pragma"), F("no-cache"));
  server.sendHeader(F("Expires"), F("0"));

  // Enable Pagination (Chunked Transfer)
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);

  RESERVE_STRING(page_content, XLARGE_STR);

  start_html_page(page_content, FPSTR(INTL_CONFIGURATION));

  if (wifiConfigLoop) 
  {
    // install wlan ssid list scripts
    page_content += FPSTR(SET_SSID_SCRIPT);
    page_content += FPSTR(WIFI_LIST_SCRIPT);
  }

  if (server.method() == HTTP_GET) 
  {
    webserver_config_send_body_get(page_content);
    end_html_page_discard(page_content);
  } 
  else 
  {
    webserver_config_send_body_post(page_content);
    end_html_page(page_content, true /* Show Backbutton */);
  }

  if (server.method() == HTTP_POST) 
  {
    if (writeConfig()) 
    {
      Serial.println(FPSTR(INTL_CONFIG_WRITTEN));
      if (wifiConfigLoop) 
      {
        display_restart();
      }
      else
      {
        //hier
        // continue to home screen
      }
    }
  }
}

/*****************************************************************
 * Webserver display params: show advanced parameters page                     *
 *****************************************************************/
//
static void webserver_param_send_body(String &page_content) 
{
  auto add_form_checkbox = [&page_content](const ConfigShapeId cfgid, const String &info) 
  {
    page_content += formCheckbox(cfgid, info);
  };

  page_content += F("<form method='POST' action='/config' style='width:100%;'>\n"
                    "<input class='radio' id='r1' name='group' type='radio' checked>"
                    "<input class='radio' id='r2' name='group' type='radio'>"
                    "<input class='radio' id='r3' name='group' type='radio'>"
                    "<input class='radio' id='r4' name='group' type='radio'>"
                    "<input class='radio' id='r5' name='group' type='radio'>"
                    "<div class='tabs'>"
                    "<label class='tab' id='tab1' for='r1'>");
  page_content += FPSTR(INTL_PM_PARAMS);
  page_content += F("</label>"

                    "<label class='tab' id='tab2' for='r2'>");
  page_content += FPSTR(INTL_AQI_WHO_TABLE);
  page_content += F("</label>"

                    "<label class='tab' id='tab3' for='r3'>");
  page_content += FPSTR(INTL_NOISE_TRAFFIC_TABLE);
  page_content += F("</label>"

                    "<label class='tab' id='tab4' for='r4'>");
  page_content += FPSTR(INTL_TRAFFIC_PARAMS);
  page_content += F("</label></div>");

  server.sendContent(page_content);

  // ===== Tab 1  PM params
  page_content = F("<div class='panels'>"
                   "<div class='panel' id='panel1'>");

  page_content += FPSTR(WEB_BR_LF_B);
  page_content += FPSTR(INTL_AB_HIER_NUR_ANDERN);
  page_content += FPSTR(WEB_B_BR);
  page_content += FPSTR(BR_TAG);
  //
  page_content += FPSTR(TABLE_TAG_OPEN);
  add_form_input(page_content, Config_max25WHO, FPSTR(INTL_WHO_PM25_MAXIMUM), 2);
  add_form_input(page_content, Config_max10WHO, FPSTR(INTL_WHO_PM10_MAXIMUM), 2);
  add_form_input(page_content, Config_PM25toAQI50, FPSTR(INTL_PM25_TO_AQI50), 2);
  add_form_input(page_content, Config_PM10toAQI50, FPSTR(INTL_PM10_TO_AQI50), 2);
  add_form_input(page_content, Config_maxgraphPM25, FPSTR(INTL_MAXGRAPH_PM25), 2);
  add_form_input(page_content, Config_maxgraphPM10, FPSTR(INTL_MAXGRAPH_PM10), 2);
  add_form_input(page_content, Config_differencePercent, FPSTR(INTL_DIFFERENCEPERCENT), 2);
  add_form_input(page_content, Config_differenceLevel, FPSTR(INTL_DIFFERENCELEVEL), 2);
  add_form_input(page_content, Config_compareLocation, FPSTR(INTL_COMPARELOCATION), 2);
  add_form_input(page_content, Config_compareLocation2, FPSTR(INTL_COMPARELOCATION2), 2);
  page_content += FPSTR(TABLE_TAG_CLOSE_BR);
  //
  page_content += F("<hr/>");
  //
  page_content += FPSTR(TABLE_TAG_OPEN);
  add_form_input(page_content, Config_sensorApi, FPSTR(INTL_URLSENSORCOMM), LEN_API);
  page_content += FPSTR(TABLE_TAG_CLOSE_BR);
  //
  page_content += F("<hr/>");
  //
  page_content += FPSTR(TABLE_TAG_OPEN);
  add_hor_radio2(page_content, Config_pmChoice, FPSTR(INTL_PMCHOICE));
  page_content += FPSTR(TABLE_TAG_CLOSE_BR);
  //
  server.sendContent(page_content);

  // ===== Tab 2  AQI & WHO table
  page_content = tmpl(FPSTR(WEB_DIV_PANEL), String(2));
  //
  page_content += FPSTR(WEB_BR_LF_B);
  page_content += FPSTR(INTL_AB_HIER_NUR_ANDERN);  
  page_content += FPSTR(WEB_B_BR);
  page_content += FPSTR(WEB_BR_LF_B);  
  page_content += FPSTR(INTL_AQI_TABLE_TITLE);
  page_content += FPSTR(WEB_B_BR);
  page_content += FPSTR(BR_TAG);
  //
  page_content += FPSTR(TABLE_TAG_OPEN);
  add_form_input(page_content, Config_maxAqiGreen, FPSTR(INTL_MAXAQIGREEN), 3);
  add_form_input(page_content, Config_maxAqiYellow, FPSTR(INTL_MAXAQIYELLOW), 3);
  add_form_input(page_content, Config_maxAqiOrange, FPSTR(INTL_MAXAQIORANGE), 3);
  add_form_input(page_content, Config_maxAqiRed, FPSTR(INTL_MAXAQIRED), 3);
  add_form_input(page_content, Config_maxAqiViolet, FPSTR(INTL_MAXAQIVIOLET), 3);
  page_content += FPSTR(TABLE_TAG_CLOSE_BR);
  //
  page_content += FPSTR(WEB_B_BR);  
  page_content += F("<hr/>");
  //
  page_content += FPSTR(WEB_BR_LF_B);
  page_content += FPSTR(INTL_WHO_TABLE_TITLE);
  page_content += FPSTR(WEB_B_BR);
  page_content += FPSTR(BR_TAG);
  //
  page_content += FPSTR(TABLE_TAG_OPEN);
  add_form_input(page_content, Config_maxWhoGreen, FPSTR(INTL_MAXWHOGREEN), 3);
  add_form_input(page_content, Config_maxWhoYellow, FPSTR(INTL_MAXWHOYELLOW), 3);
  add_form_input(page_content, Config_maxWhoOrange, FPSTR(INTL_MAXWHOORANGE), 3);
  add_form_input(page_content, Config_maxWhoRed, FPSTR(INTL_MAXWHORED), 3);
  add_form_input(page_content, Config_maxWhoViolet, FPSTR(INTL_MAXWHOVIOLET), 3);
  page_content += FPSTR(TABLE_TAG_CLOSE_BR);
  //
  server.sendContent(page_content);

  // ===== Tab 3  Noise & Traffic table
  page_content = tmpl(FPSTR(WEB_DIV_PANEL), String(3));
  //
  page_content += FPSTR(WEB_BR_LF_B);
  page_content += FPSTR(INTL_AB_HIER_NUR_ANDERN);
  page_content += FPSTR(WEB_B_BR);
  page_content += FPSTR(WEB_BR_LF_B);  
  page_content += FPSTR(INTL_NOISE_TABLE_TITLE);
  page_content += FPSTR(WEB_B_BR);
  page_content += FPSTR(BR_TAG);
  //
  page_content += FPSTR(TABLE_TAG_OPEN);
  add_form_input(page_content, Config_maxLAeqGreen, FPSTR(INTL_MAXLAEQGREEN), 3);
  add_form_input(page_content, Config_maxLAeqYellow, FPSTR(INTL_MAXLAEQYELLOW), 3);
  add_form_input(page_content, Config_maxLAeqOrange, FPSTR(INTL_MAXLAEQORANGE), 3);
  add_form_input(page_content, Config_maxLAeqRed, FPSTR(INTL_MAXLAEQRED), 3);
  add_form_input(page_content, Config_maxLAeqViolet, FPSTR(INTL_MAXLAEQVIOLET), 3);
  add_form_input(page_content, Config_maxLAeqBrown, FPSTR(INTL_MAXLAEQBROWN), 3);
  page_content += FPSTR(TABLE_TAG_CLOSE_BR);
  //
  page_content += FPSTR(WEB_B_BR);  
  page_content += F("<hr/>");
  //
  page_content += FPSTR(WEB_BR_LF_B);
  page_content += FPSTR(INTL_TRAFFIC_TABLE_TITLE);
  page_content += FPSTR(WEB_B_BR);
  page_content += FPSTR(BR_TAG);
  //
  page_content += FPSTR(TABLE_TAG_OPEN);
  add_form_input(page_content, Config_maxTrafGreen, FPSTR(INTL_MAXTRAFGREEN), 3);
  add_form_input(page_content, Config_maxTrafYellow, FPSTR(INTL_MAXTRAFYELLOW), 3);
  add_form_input(page_content, Config_maxTrafOrange, FPSTR(INTL_MAXTRAFORANGE), 3);
  add_form_input(page_content, Config_maxTrafRed, FPSTR(INTL_MAXTRAFRED), 3);
  add_form_input(page_content, Config_maxTrafCyan, FPSTR(INTL_MAXTRAFCYAN), 3);
  add_form_input(page_content, Config_maxTrafViolet, FPSTR(INTL_MAXTRAFVIOLET), 3);
  add_form_input(page_content, Config_maxTrafBrown, FPSTR(INTL_MAXTRAFBROWN), 3);
  page_content += FPSTR(TABLE_TAG_CLOSE_BR);
  //
  server.sendContent(page_content);

  // ===== Tab 4  Traffic params
  page_content = tmpl(FPSTR(WEB_DIV_PANEL), String(4));
  //
  page_content += FPSTR(WEB_BR_LF_B);
  page_content += FPSTR(INTL_AB_HIER_NUR_ANDERN);
  page_content += FPSTR(WEB_B_BR);
  page_content += FPSTR(BR_TAG);
  //
  page_content += FPSTR(TABLE_TAG_OPEN);
  add_form_input(page_content, Config_telraamApi, FPSTR(INTL_TELRAAMAPI), LEN_API);
  add_form_input(page_content, Config_telraamToken, FPSTR(INTL_TELRAAMTOKEN), LEN_API);
  page_content += FPSTR(TABLE_TAG_CLOSE_BR);
  page_content += FPSTR(TABLE_TAG_OPEN);    
  add_form_checkbox(Config_freeToken, FPSTR(INTL_FREETOKEN));
  page_content += FPSTR(TABLE_TAG_CLOSE_BR);
  //
  page_content += FPSTR(WEB_B_BR);  
  page_content += F("<hr/>");
  page_content += FPSTR(WEB_B_BR);  
  //
  page_content += FPSTR(TABLE_TAG_OPEN);
  add_form_checkbox(Config_showPedes, FPSTR(INTL_SHOWPEDES));
  add_form_checkbox(Config_showBike, FPSTR(INTL_SHOWBIKE));
  add_form_checkbox(Config_showCar, FPSTR(INTL_SHOWCAR));
  add_form_checkbox(Config_showHeavy, FPSTR(INTL_SHOWHEAVY));
  add_form_checkbox(Config_showSpeed, FPSTR(INTL_SHOWSPEED));
  page_content += FPSTR(TABLE_TAG_CLOSE_BR);

  server.sendContent(page_content);

  // ===== Footer
  page_content = F("</div></div>");
  //hier
  page_content += form_submit(FPSTR(INTL_SAVE_CONFIG));
  page_content += FPSTR(BR_TAG);
  page_content += FPSTR(WEB_BR_FORM);

  server.sendContent(page_content);
}

/*****************************************************************
 * WiFi declarations                                             *
 *****************************************************************/
struct struct_wifiInfo 
{
  char ssid[LEN_SSID];
  uint8_t encryptionType;
  int32_t RSSI;
  int32_t channel;
  bool isHidden;
  uint8_t unused[3];
};

struct struct_wifiInfo *wifiInfo;
uint8_t count_wifiInfo = 0;

/*****************************************************************
 * Webserver wifi: show available wifi networks                  *
 *****************************************************************/
static void webserver_wifi() 
{
  String page_content;

  if (cfg::debugComms) 
  {
    Serial.print(FPSTR(INTL_NETWORKS_FOUND));
    Serial.println(String(count_wifiInfo));
  }
  if (count_wifiInfo == 0) 
  {
    page_content += FPSTR(BR_TAG);
    page_content += FPSTR(INTL_NO_NETWORKS);
    page_content += FPSTR(BR_TAG);
  } 
  else 
  {
    std::unique_ptr<int[]> indices(new int[count_wifiInfo]);
    for (unsigned i = 0; i < count_wifiInfo; ++i) 
    {
      indices[i] = i;
    }
    for (unsigned i = 0; i < count_wifiInfo; i++) 
    {
      for (unsigned j = i + 1; j < count_wifiInfo; j++) 
      {
        if (wifiInfo[indices[j]].RSSI > wifiInfo[indices[i]].RSSI) 
        {
          std::swap(indices[i], indices[j]);
        }
      }
    }
    int duplicateSsids = 0;
    for (int i = 0; i < count_wifiInfo; i++) 
    {
      if (indices[i] == -1) 
      {
        continue;
      }
      for (int j = i + 1; j < count_wifiInfo; j++) 
      {
        if (strncmp(wifiInfo[indices[i]].ssid, wifiInfo[indices[j]].ssid, sizeof(wifiInfo[0].ssid)) == 0) 
        {
          indices[j] = -1;  // set dup aps to index -1
          ++duplicateSsids;
        }
      }
    }
    if (cfg::debugComms && duplicateSsids) 
    {
      Serial.print(F("Duplicate WiFi networks found: "));
      Serial.println(String(duplicateSsids));
    }
    page_content += FPSTR(INTL_NETWORKS_FOUND);
    page_content += String(count_wifiInfo - duplicateSsids);
    page_content += FPSTR(BR_TAG);
    page_content += FPSTR(BR_TAG);
    page_content += FPSTR(TABLE_TAG_OPEN);

    for (int i = 0; i < count_wifiInfo; ++i) 
    {
      if (indices[i] == -1 || wifiInfo[indices[i]].isHidden) 
      {
        continue;
      }
      // Print SSID and RSSI for each network found
      page_content += wlan_ssid_to_table_row(wifiInfo[indices[i]].ssid, ((wifiInfo[indices[i]].encryptionType == ENC_TYPE_NONE) ? " " : u8"🔒"), wifiInfo[indices[i]].RSSI);
    }
    page_content += FPSTR(TABLE_TAG_CLOSE_BR);
    page_content += FPSTR(BR_TAG);
  }
  server.send(200, FPSTR(TXT_CONTENT_TYPE_TEXT_HTML), page_content);
}

/*****************************************************************
 * Webserver display parameters                                  *
 *****************************************************************/
//
static void webserver_param() 
{
  if (!webserver_request_auth()) 
  {
    return;
  }
  server.sendHeader(F("Cache-Control"), F("no-cache, no-store, must-revalidate"));
  server.sendHeader(F("Pragma"), F("no-cache"));
  server.sendHeader(F("Expires"), F("0"));

  // Enable Pagination (Chunked Transfer)
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);

  RESERVE_STRING(page_content, XLARGE_STR);
  start_html_page(page_content, FPSTR(INTL_ADVANCED_SETTINGS));

  webserver_param_send_body(page_content);

  page_content = emptyString;
  end_html_page_discard(page_content);
}

// This is the valuebuffer. It receives the lines with sensor data,
// shown in the value web page.
char valueBuffer[VALUE_STRINGS][LEN_MEASUREMENTS];  // message buffer

// Construct data from one location
static void constructLocationData(int location) 
{
  bool blanco;
  int valueBufPnt = 0;

  RESERVE_STRING(s, LEN_MEASUREMENTS);

  // Name
  s = String(multiName[location]);
  s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
  //
  if ((readPm25[location] > -100.0f) || (readPm10[location] > -100.0f)) 
  {
    // 1
    if ((cumulAvgPm25[location] > 0.0f) || (cumulAvgPm10[location] > 0.0f))
    {
      // Switch PM2.5/PM10
      if (cfg::pmChoice == SELECT_PM25) 
      {
        s = INTL_AVG24H_PM25 + String("{v}&micro;g/m&sup3");
        s.replace("{v}", rounder(cumulAvgPm25[location], 2));         
      } 
      else 
      {
        s = INTL_AVG24H_PM10 + String("{v}&micro;g/m&sup3");
        s.replace("{v}", rounder(cumulAvgPm10[location], 2));      
      }
      s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
      blanco = true;
    }
    // 2
    if ((peakPm25[location] > 0.0f) || (peakPm10[location] > 0.0f))
    {
      // Switch PM2.5/PM10
      if (cfg::pmChoice == SELECT_PM25) 
      {
        s = INTL_PEAK24H_PM25 + String("{v}&micro;g/m&sup3");
        s.replace("{v}", rounder(peakPm25[location], 2));         
      } 
      else 
      {
        s = INTL_PEAK24H_PM10 + String("{v}&micro;g/m&sup3");
        s.replace("{v}", rounder(peakPm10[location], 2));        
      }
      s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
      blanco = true;
    }
    // Fill in to even
    if ((((int)(valueBufPnt / 2)) * 2) == valueBufPnt) 
    {
      s = "--";
      s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
    }
  }
  // 3
  if (readPm25[location] > -100.0f) 
  {
    s = "PM2,5: {v}&micro;g/m&sup3";
    s.replace("{v}", String(readPm25[location]));
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
    blanco = true;
  }
  // 4
  if (readPm1[location] > -100.0f) 
  {
    s = "PM1: {v}&micro;g/m&sup3;";
    s.replace("{v}", String(readPm1[location]));
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
    blanco = true;
  }
  // 5
  if (readPm10[location] > -100.0f) 
  {
    s = "PM10: {v}&micro;g/m&sup3;";
    s.replace("{v}", String(readPm10[location]));
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
    blanco = true;
  }
  // 6
  if (readPm4[location] > -100.0f) 
  {
    s = "PM4: {v}&micro;g/m&sup3";
    s.replace("{v}", String(readPm4[location]));
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
    blanco = true;
  }
  // Fill in to even
  if ((((int)(valueBufPnt / 2)) * 2) == valueBufPnt) 
  {
    s = "--";
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
  }
  // 7
  if (readNbr05[location] > -100.0f) 
  {
    s = INTL_QUANT_05UM + String("{v} &epar;/cm&sup3;");
    s.replace("{v}", rounder(readNbr05[location], 0));
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
    blanco = true;
  }
  // 8
  if (readNbr1[location] > -100.0f) 
  {
    s = INTL_QUANT_1UM + String("{v} &epar;/cm&sup3;");
    s.replace("{v}", rounder(readNbr1[location], 0));
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
    blanco = true;
  }
  // 9
  if (readNbr25[location] > -100.0f) 
  {
    s = INTL_QUANT_25UM + String("{v} &epar;/cm&sup3;");
    s.replace("{v}", rounder(readNbr25[location], 0));
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
    blanco = true;
  }
  // 10
  if (readNbr4[location] > -100.0f) 
  {
    s = INTL_QUANT_4UM + String("{v} &epar;/cm&sup3;");
    s.replace("{v}", rounder(readNbr4[location], 0));
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
    blanco = true;
  }
  // 11
  if (readNbr10[location] > -100.0f) 
  {
    s = INTL_QUANT_10UM + String("{v} &epar;/cm&sup3;");
    s.replace("{v}", rounder(readNbr10[location], 0));
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
    blanco = true;
  }
  // 12
  if (readTs[location] > -100.0f) 
  {
    s = INTL_PART_SIZE + String("{v}&micro;m");
    s.replace("{v}", String(readTs[location]));
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
    blanco = true;
  }
  // Fill in to even
  if ((((int)(valueBufPnt / 2)) * 2) == valueBufPnt) 
  {
    s = "--";
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
  }
  // 13
  if (readTemp[location] > -100.0f) 
  {
    s = INTL_TEMPERATURE + String("{v}&deg;C");
    s.replace("{v}", String(readTemp[location]));
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
    blanco = true;
  }
  // 14
  if (readHumi[location] > -100.0f) 
  {
    s = INTL_HUMIDITY + String("{v}&percnt;");
    s.replace("{v}", rounder(readHumi[location], 0));
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
    blanco = true;
  }
  // 15
  if (readPres[location] > -100.0f) 
  {
    s = INTL_AIR_PRESS + String("{v} hPa");
    s.replace("{v}", String(readPres[location]));
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
    blanco = true;
  }
  // Fill in to even
  if ((((int)(valueBufPnt / 2)) * 2) == valueBufPnt) 
  {
    s = "--";
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
  }
  // 17
  if (readVoc[location] > -100.0f) 
  {
    s = INTL_VOC_INDEX + String("{v}");
    s.replace("{v}", rounder(readVoc[location], 0));
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
    blanco = true;
  }
  // 18
  if (readNox[location] > -100.0f) 
  {
    s = INTL_NOX_INDEX + String("{v}");
    s.replace("{v}", rounder(readNox[location], 0));
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
    blanco = true;
  }
  // Fill in to even
  if ((((int)(valueBufPnt / 2)) * 2) == valueBufPnt) 
  {
    s = "--";
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
  }
  // blanco line
  if (blanco) 
  {
    s = "--";
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
  }
  blanco = false;
  // 19
  if (readPedes[location] > -100.0f) 
  {
    s = INTL_PEDESTRIANS + String("{v} &epar;") + INTL_PER_HOUR;
    s.replace("{v}", rounder(readPedes[location], 0));
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
    blanco = true;
  }
  // 20
  if (readBike[location] > -100.0f) 
  {
    s = INTL_BIKES + String("{v} &epar;") + INTL_PER_HOUR;
    s.replace("{v}", rounder(readBike[location], 0));
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
    blanco = true;
  }
  // 21
  if (readCar[location] > -100.0f) 
  {
    s = INTL_CARS + String("{v} &epar;") + INTL_PER_HOUR;
    s.replace("{v}", rounder(readCar[location], 0));
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
    blanco = true;
  }
  // 22
  if (readHeavy[location] > -100.0f) 
  {
    s = INTL_HEAVY + String("{v} &epar;") + INTL_PER_HOUR;
    s.replace("{v}", rounder(readHeavy[location], 0));
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
    blanco = true;
  }
  // 23
  if (readSpeed[location] > -100.0f) 
  {
    s = INTL_V85_SPEED + String("{v}") + INTL_KM_PER_HOUR;
    s.replace("{v}", rounder(readSpeed[location], 0));
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
    blanco = true;
  }
  // blanco line
  if (blanco) 
  {
    s = "--";
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
  }
  // Fill in to even ==> 24
  if ((((int)(valueBufPnt / 2)) * 2) == valueBufPnt) 
  {
    s = "--";
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
  }
  // 25
  if (readLAmin[location] > -100.0f) 
  {
    s = "LA min: {v} dBm";
    s.replace("{v}", rounder(readLAmin[location], 0));
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
  }
  // 26
  if (readLAmax[location] > -100.0f) 
  {
    s = "LA max: {v} dBm";
    s.replace("{v}", rounder(readLAmax[location], 0));
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
  }
  // 27
  if (readLAeq[location] > -100.0f) 
  {
    s = "LA eq: {v} dBm";
    s.replace("{v}", rounder(readLAeq[location], 0));
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
  }
  // Erase value buffer from this message on
  s = "--";
  while (valueBufPnt < VALUE_STRINGS) 
  {
    s.toCharArray(valueBuffer[valueBufPnt++], LEN_MEASUREMENTS);
  }
}

/*****************************************************************
 * Webserver show latest values                                  *
 *****************************************************************/
//
static void webserverValues(uint8_t location) 
{
  RESERVE_STRING(page_content, XLARGE_STR);
  start_html_page(page_content, FPSTR(INTL_CURRENT_DATA));

  RESERVE_STRING(s, MED_STR);
  s = FPSTR(WEB_UPTIME);
  s.replace("{t}", (delayToString(millis() - atLastStartup)));
  s.replace("{r}", ESP.getResetReason());
  page_content += s;

  if (readUpToLocation != locationsInstalled) 
  {
    s = FPSTR(WEB_READUPTO);
    s.replace("{r}", (String(multiName[readUpToLocation])));
    page_content += s;
  }

  constructLocationData(location);

  page_content += FPSTR(BR_TAG);
  page_content += FPSTR(TABLE_TAG_OPEN);

  add_row_sel_title(page_content, FPSTR(INTL_LOCATION_NAME), LEN_LOCATION_NAME,
                    FPSTR(INTL_LOCATION_NAME), LEN_LOCATION_NAME,
                    String(valueBuffer[0]), LEN_LOCATION_NAME);

  add_row_select(page_content, Config_sensorLoc_0, 0, Config_sensorLoc_16, 16,
                 String(valueBuffer[1]), String(valueBuffer[2]));
  add_row_select(page_content, Config_sensorLoc_1, 1, Config_sensorLoc_17, 17,
                 String(valueBuffer[3]), String(valueBuffer[4]));
  add_row_select(page_content, Config_sensorLoc_2, 2, Config_sensorLoc_18, 18,
                 String(valueBuffer[5]), String(valueBuffer[6]));
  add_row_select(page_content, Config_sensorLoc_3, 3, Config_sensorLoc_19, 19,
                 String(valueBuffer[7]), String(valueBuffer[8]));

  server.sendContent(page_content);
  page_content = emptyString;

  add_row_select(page_content, Config_sensorLoc_4, 4, Config_sensorLoc_20, 20,
                 String(valueBuffer[9]), String(valueBuffer[10]));
  add_row_select(page_content, Config_sensorLoc_5, 5, Config_sensorLoc_21, 21,
                 String(valueBuffer[11]), String(valueBuffer[12]));
  add_row_select(page_content, Config_sensorLoc_6, 6, Config_sensorLoc_22, 22,
                 String(valueBuffer[13]), String(valueBuffer[14]));
  add_row_select(page_content, Config_sensorLoc_7, 7, Config_sensorLoc_23, 23,
                 String(valueBuffer[15]), String(valueBuffer[16]));

  server.sendContent(page_content);
  page_content = emptyString;

  add_row_select(page_content, Config_sensorLoc_8, 8, Config_sensorLoc_24, 24,
                 String(valueBuffer[17]), String(valueBuffer[18]));
  add_row_select(page_content, Config_sensorLoc_9, 9, Config_sensorLoc_25, 25,
                 String(valueBuffer[19]), String(valueBuffer[20]));
  add_row_select(page_content, Config_sensorLoc_10, 10, Config_sensorLoc_26, 26,
                 String(valueBuffer[21]), String(valueBuffer[22]));
  add_row_select(page_content, Config_sensorLoc_11, 11, Config_sensorLoc_27, 27,
                 String(valueBuffer[23]), String(valueBuffer[24]));

  server.sendContent(page_content);
  page_content = emptyString;

  add_row_select(page_content, Config_sensorLoc_12, 12, Config_sensorLoc_28, 28,
                 String(valueBuffer[25]), String(valueBuffer[26]));
  add_row_select(page_content, Config_sensorLoc_13, 13, Config_sensorLoc_29, 29,
                 String(valueBuffer[27]), String(valueBuffer[28]));
  add_row_select(page_content, Config_sensorLoc_14, 14, Config_sensorLoc_30, 30,
                 String(valueBuffer[29]), String(valueBuffer[30]));
  add_row_select(page_content, Config_sensorLoc_15, 15, Config_sensorLoc_31, 31,
                 String(valueBuffer[31]), String(valueBuffer[32]));

  server.sendContent(page_content);
  page_content = FPSTR(TABLE_TAG_CLOSE_BR);
  page_content += FPSTR(BR_TAG);
  end_html_page(page_content, true /* Show Backbutton */);
}

static void webserverValues0() 
{
  webserverValues(0);
}
static void webserverValues1() 
{
  webserverValues(1);
}
static void webserverValues2() 
{
  webserverValues(2);
}
static void webserverValues3() 
{
  webserverValues(3);
}
static void webserverValues4() 
{
  webserverValues(4);
}
static void webserverValues5() 
{
  webserverValues(5);
}
static void webserverValues6() 
{
  webserverValues(6);
}
static void webserverValues7() 
{
  webserverValues(7);
}
static void webserverValues8() 
{
  webserverValues(8);
}
static void webserverValues9() 
{
  webserverValues(9);
}
static void webserverValues10() 
{
  webserverValues(10);
}
static void webserverValues11() 
{
  webserverValues(11);
}
static void webserverValues12() 
{
  webserverValues(12);
}
static void webserverValues13() 
{
  webserverValues(13);
}
static void webserverValues14() 
{
  webserverValues(14);
}
static void webserverValues15() 
{
  webserverValues(15);
}
static void webserverValues16() 
{
  webserverValues(16);
}
static void webserverValues17() 
{
  webserverValues(17);
}
static void webserverValues18() 
{
  webserverValues(18);
}
static void webserverValues19() 
{
  webserverValues(19);
}
static void webserverValues20() 
{
  webserverValues(20);
}
static void webserverValues21() 
{
  webserverValues(21);
}
static void webserverValues22() 
{
  webserverValues(22);
}
static void webserverValues23() 
{
  webserverValues(23);
}
static void webserverValues24() 
{
  webserverValues(24);
}
static void webserverValues25() 
{
  webserverValues(25);
}
static void webserverValues26() 
{
  webserverValues(26);
}
static void webserverValues27() 
{
  webserverValues(27);
}
static void webserverValues28() 
{
  webserverValues(28);
}
static void webserverValues29() 
{
  webserverValues(29);
}
static void webserverValues30() 
{
  webserverValues(30);
}
static void webserverValues31() 
{
  webserverValues(31);
}

/*****************************************************************
 * Webserver remove config & 24h.data store                      *
 *****************************************************************/
//
static void webserver_removeConfig() 
{
  if (!webserver_request_auth()) 
  {
    return;
  }
  String fileName;

  RESERVE_STRING(page_content, LARGE_STR);
  start_html_page(page_content, FPSTR(INTL_DELETE_CONFIG));

  if (server.method() == HTTP_GET) 
  {
    page_content += FPSTR(WEB_REMOVE_CONFIG_CONTENT);
  } 
  else 
  {
    // Config file...
    // Outer loop, all chunks
    for (int chunk = 0; chunk < NUM_CHUNKS; chunk++) 
    {
      fileName = CONFIG_NAME + String(chunk) + ".json";

      if (SPIFFS.exists(fileName)) 
      {
        if (SPIFFS.remove(fileName)) 
        {
          page_content += ("<h3> Config file " + fileName + " " + INTL_DELETED + ".</h3>");
        } 
        else 
        {
          page_content += ("<h3> Config file " + fileName + " " + INTL_CANNOT_BE_DELETED + ".</h3>");
        }
      } 
      else 
      {
        page_content += ("<h3> Config file " + fileName + " " + INTL_NOT_FOUND + ".</h3>");
      }
    }

    // Avg & peak 24h. data file...
    fileName = String(AVG_PEAK_NAME) + ".json";
    if (SPIFFS.exists(fileName)) 
    {
      if (SPIFFS.remove(fileName)) 
      {
        page_content += ("<h3> 24h. Data file " + fileName + " " + INTL_DELETED + ".</h3>");
      } 
      else 
      {
        page_content += ("<h3> 24h. Data file " + fileName + " " + INTL_CANNOT_BE_DELETED + ".</h3>");
      }
    } 
    else 
    {
      page_content += ("<h3> 24h. Data file " + fileName + " " + INTL_NOT_FOUND + ".</h3>");
    }
  }
  end_html_page(page_content, true /* Show Backbutton */);
}

/*****************************************************************
 * Webserver reset NodeMCU                                       *
 *****************************************************************/
//
static void webserver_reset() 
{
  if (!webserver_request_auth()) 
  {
    return;
  }
  String page_content;
  page_content.reserve(512);
  start_html_page(page_content, FPSTR(INTL_RESTART_DISPLAY));

  if (server.method() == HTTP_GET) 
  {
    RESERVE_STRING(s, MED_STR);
    s = FPSTR(WEB_UPTIME);
    s.replace("{t}", (delayToString(millis() - atLastStartup)));
    s.replace("{r}", ESP.getResetReason());
    page_content += s;
    page_content += FPSTR(WEB_RESET_CONTENT);
    //
    end_html_page(page_content, false /* Show Backbutton */);    
  } 
  else 
  {
    end_html_page(page_content, true /* Show Backbutton */); 
    display_restart();
  }
}

/*****************************************************************
 * Webserver page not found                                      *
 *****************************************************************/
//
static void webserver_not_found() 
{
  last_page_load = millis();
  if (WiFi.status() != WL_CONNECTED) 
  {
    if ((server.uri().indexOf(F("success.html")) != -1) || (server.uri().indexOf(F("detect.html")) != -1)) 
    {
      server.send(200, FPSTR(TXT_CONTENT_TYPE_TEXT_HTML), FPSTR(WEB_IOS_REDIRECT));
    } 
    else 
    {
      sendHttpRedirect();
    }
  } 
  else 
  {
    server.send(404, FPSTR(TXT_CONTENT_TYPE_TEXT_PLAIN), FPSTR(INTL_NOT_FOUND_FPSTR));
  }
}

/*****************************************************************
 * Webserver Images                                              *
 *****************************************************************/
//
static void webserver_favicon() 
{
  server.sendHeader(F("Cache-Control"), F("max-age=2592000, public"));

  server.send_P(200, TXT_CONTENT_TYPE_IMAGE_PNG,
                LUFTDATEN_INFO_LOGO_PNG, LUFTDATEN_INFO_LOGO_PNG_SIZE);
}

static void webserver_static() 
{
  server.sendHeader(F("Cache-Control"), F("max-age=2592000, public"));

  if (server.arg(String('r')) == F("logo")) 
  {
    server.send_P(200, TXT_CONTENT_TYPE_IMAGE_PNG,
                  LUFTDATEN_INFO_LOGO_PNG, LUFTDATEN_INFO_LOGO_PNG_SIZE);
  } 
  else 
  {
    if (server.arg(String('r')) == F("css")) 
    {
      server.send_P(200, TXT_CONTENT_TYPE_TEXT_CSS,
                    WEB_PAGE_STATIC_CSS, sizeof(WEB_PAGE_STATIC_CSS) - 1);
    } 
    else 
    {
      webserver_not_found();
    }
  }  
}

/*****************************************************************
 * Webserver response setup                                      *
 *****************************************************************/
//
static void setupWebserverPages() 
{
  server.on("/", webserver_root);
  server.on(F("/config"), webserver_config);
  server.on(F("/wifi"), webserver_wifi);
  server.on(F("/param"), webserver_param);
  server.on(F("/removeConfig"), webserver_removeConfig);
  server.on(F("/reset"), webserver_reset);
  server.on(F("/favicon.ico"), webserver_favicon);
  server.on(F(STATIC_PREFIX), webserver_static);
  server.on(F("/values"), webserverValues0);
  server.on(F("/values0"), webserverValues0);
  server.on(F("/values1"), webserverValues1);
  server.on(F("/values2"), webserverValues2);
  server.on(F("/values3"), webserverValues3);
  server.on(F("/values4"), webserverValues4);
  server.on(F("/values5"), webserverValues5);
  server.on(F("/values6"), webserverValues6);
  server.on(F("/values7"), webserverValues7);
  server.on(F("/values8"), webserverValues8);
  server.on(F("/values9"), webserverValues9);
  server.on(F("/values10"), webserverValues10);
  server.on(F("/values11"), webserverValues11);
  server.on(F("/values12"), webserverValues12);
  server.on(F("/values13"), webserverValues13);
  server.on(F("/values14"), webserverValues14);
  server.on(F("/values15"), webserverValues15);
  server.on(F("/values16"), webserverValues16);
  server.on(F("/values17"), webserverValues17);
  server.on(F("/values18"), webserverValues18);
  server.on(F("/values19"), webserverValues19);
  server.on(F("/values20"), webserverValues20);
  server.on(F("/values21"), webserverValues21);
  server.on(F("/values22"), webserverValues22);
  server.on(F("/values23"), webserverValues23);
  server.on(F("/values24"), webserverValues24);
  server.on(F("/values25"), webserverValues25);
  server.on(F("/values26"), webserverValues26);
  server.on(F("/values27"), webserverValues27);
  server.on(F("/values28"), webserverValues28);
  server.on(F("/values29"), webserverValues29);
  server.on(F("/values30"), webserverValues30);
  server.on(F("/values31"), webserverValues31);
  //
  server.onNotFound(webserver_not_found);
  server.begin();
}

/*****************************************************************
 * WiFi routines                                                 *
 *****************************************************************/
//
// millis() && server time/counts
int last_signal_strength;
int last_disconnect_reason;

// Select WiFi channel
static int selectChannelForAp() 
{
  std::array<int, 14> channels_rssi;
  std::fill(channels_rssi.begin(), channels_rssi.end(), -100);
  //
  for (unsigned i = 0; i < std::min((uint8_t)14, count_wifiInfo); i++) 
  {
    if (wifiInfo[i].RSSI > channels_rssi[wifiInfo[i].channel]) 
    {
      channels_rssi[wifiInfo[i].channel] = wifiInfo[i].RSSI;
    }
  }
  if ((channels_rssi[1] < channels_rssi[6]) && (channels_rssi[1] < channels_rssi[11])) 
  {
    return 1;
  } 
  else
  { 
    if ((channels_rssi[6] < channels_rssi[1]) && (channels_rssi[6] < channels_rssi[11])) 
    {
      return 6;
    } 
    else 
    {
      return 11;
    }
  }  
}

/*****************************************************************
 * WifiConfig                                                    *
 *****************************************************************/
static void wifiConfig() 
{
  if (cfg::debugComms) 
  {
    Serial.println(FPSTR(INTL_START_WIFI_MAN));
    Serial.print("AP ID: ");
    Serial.println(String(cfg::fs_ssid));
    Serial.print(FPSTR(INTL_PASSWORD_DP));
    Serial.println(String(cfg::fs_pwd));
  }
  wifiConfigLoop = true;
  WiFi.disconnect(true);
  Serial.println(FPSTR(INTL_SCANWIFI));
  int8_t scanReturnCode = WiFi.scanNetworks(false /* scan async */, true /* show hidden networks */);
  if (scanReturnCode < 0) 
  {
    Serial.println(FPSTR(INTL_SCANFAIL));
    count_wifiInfo = 0;
  } 
  else 
  {
    count_wifiInfo = (uint8_t)scanReturnCode;
  }

  delete[] wifiInfo;
  wifiInfo = new struct_wifiInfo[std::max(count_wifiInfo, (uint8_t)1)];

  for (unsigned i = 0; i < count_wifiInfo; i++) 
  {
    String SSID;
    uint8_t *BSSID;

    memset(&wifiInfo[i], 0, sizeof(struct_wifiInfo));
    WiFi.getNetworkInfo(i, SSID, wifiInfo[i].encryptionType,
                        wifiInfo[i].RSSI, BSSID,
                        wifiInfo[i].channel,
                        wifiInfo[i].isHidden);
    SSID.toCharArray(wifiInfo[i].ssid, sizeof(wifiInfo[0].ssid));
  }

  // Use 13 channels if locale is not "EN"
  wifi_country_t wifi;
  wifi.policy = WIFI_COUNTRY_POLICY_MANUAL;
  strcpy(wifi.cc, INTL_LANG);
  wifi.nchan = (INTL_LANG[0] == 'E' && INTL_LANG[1] == 'N') ? 11 : 13;
  wifi.schan = 1;
  wifi_set_country(&wifi);

  WiFi.mode(WIFI_AP);
  const IPAddress apIP(192, 168, 4, 1);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(cfg::fs_ssid, cfg::fs_pwd, selectChannelForAp());

  // In case we created a unique password at first start
  if (strlen(cfg::fs_pwd) > 0) 
  {
    Serial.print(FPSTR(INTL_AP_PASSWORD));
    Serial.println(cfg::fs_pwd);
  }

  // Ensure we don't poison the client DNS cache
  dnsServer.setTTL(0);
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);

  // 53 is port for DNS server
  dnsServer.start(53, "*", apIP);

  setupWebserverPages();

  // 10 minutes timeout for wifi config
  activeDelay(TIME_FOR_WIFI_CONFIG);

  showOnDisplay(INTL_PLEASE_RESTART);
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);
  dnsServer.stop();
  delay(100);

  WiFi.begin(cfg::wlanssid, cfg::wlanpwd);
  wifiConfigLoop = false;
}

// Wait for WiFi
static void waitForWifiToConnect(int maxRetries) 
{
  int retryCount = 0;
  while ((WiFi.status() != WL_CONNECTED) && (retryCount <= maxRetries)) 
  {
    delay(250);
    ++retryCount;
    showdotsAtStart();
  }
}

/*****************************************************************
 * WiFi auto connecting script                                   *
 *****************************************************************/

static WiFiEventHandler disconnectEventHandler;

// WiFi connect routine
static void connectWifi() 
{
  if (cfg::debugComms) 
  {
    Serial.print(FPSTR(INTL_TXT_CONNECTING_TO));
    Serial.println(String(cfg::wlanssid));
  }
  // Enforce Rx/Tx calibration
  system_phy_set_powerup_option(1);
  // 20dBM == 100mW == max tx power allowed in europe
  WiFi.setOutputPower(20.0f);
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  WiFi.setPhyMode(WIFI_PHY_MODE_11N);
  delay(100);

  disconnectEventHandler = WiFi.onStationModeDisconnected([](const WiFiEventStationModeDisconnected &evt) 
  {
    last_disconnect_reason = evt.reason;
  });
  if (WiFi.getAutoConnect()) 
  {
    WiFi.setAutoConnect(false);
  }
  if (!WiFi.getAutoReconnect()) 
  {
    WiFi.setAutoReconnect(true);
  }

  // Use 13 channels for connect to known AP
  wifi_country_t wifi;
  wifi.policy = WIFI_COUNTRY_POLICY_MANUAL;
  strcpy(wifi.cc, INTL_LANG);
  wifi.nchan = 13;
  wifi.schan = 1;

  wifi_set_country(&wifi);

  WiFi.mode(WIFI_STA);

  WiFi.hostname(cfg::fs_ssid);

  WiFi.begin(cfg::wlanssid, cfg::wlanpwd);

  if (cfg::debugComms) 
  {
    Serial.print(FPSTR(INTL_TXT_CONNECTING_TO));
    Serial.println(cfg::wlanssid);
  }
  waitForWifiToConnect(80);

  if (WiFi.status() != WL_CONNECTED) 
  {
    String fss(cfg::fs_ssid);
    showOnDisplay(INTL_WIFI_CONNECTION_LOST);
    delay(2000);
    showOnDisplay(INTL_WIFI_CONNECT_TO);
    delay(2000);
    showOnDisplay(INTL_WIFI_SSID + fss.substring(0, 16));

    if (cfg::debugComms) 
    {
      Serial.print(fss.substring(0, 16));
      Serial.println(fss.substring(16));
    }
    wifi.policy = WIFI_COUNTRY_POLICY_AUTO;

    wifi_set_country(&wifi);

    wifiConfig();
    if (WiFi.status() != WL_CONNECTED) 
    {
      waitForWifiToConnect(40);
    }
  }

  if (WiFi.status() == WL_CONNECTED) 
  {
    last_signal_strength = WiFi.RSSI();
    if (cfg::debugComms) 
    {
      Serial.print(F("WiFi connected @IP: "));
      Serial.println(WiFi.localIP().toString());
      Serial.print(F("WiFi signal strength: "));
      Serial.print(last_signal_strength);
      Serial.println("dBm");
    }
  }

  if (MDNS.begin(cfg::fs_ssid)) 
  {
    MDNS.addService("http", "tcp", httpPort);
    MDNS.addServiceTxt("http", "tcp", "PATH", "/config");
  }
}
