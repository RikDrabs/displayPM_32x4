/**********************************************************************************
 *                                                                                *
 * Telraam interface for:                                                         *
 * Large Bargraph Remote Display for:                                             *
 *                                                                                *
 * Luftdaten.info - sensor.community - InfluencAir - Luchtpijp - Telraam.         *
 * Display on LEDmatrix 16*8*8 dots, monocolor or (in the future) multicolor.     *
 *                                                                                *
 * Copyright (C) 2024-2025 Rik Drabs - rik.drabs@gmail.com                        *
 * Copyright (C) 2024-2025 InfluencAir - influencair2017@gmail.com                *
 *                                                                                *
 * This program is free software: you can redistribute it and/or modify           *
 * it under the terms of the GNU General Public License as published by           *
 * the Free Software Foundation, either version 3 of the License, or              *
 * (at your option) any later version.                                            *
 * This program is distributed in the hope that it will be useful,                *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of                 *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                  *
 * GNU General Public License for more details.                                   *
 * You should have received a copy of the GNU General Public License              *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.           *
 *                                                                                *
 **********************************************************************************/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <ezTime.h>

// Free token of Rik, do not use without consulting Rik.
// Register on Telraam for your own free token !
const char* apiToken       = "X7PAAVzTBo2p70ti5nOPU8G5llHOdg5o62TH2EU3";

String getFormattedTime(int minutesBack)
{
  time_t now = myTZ.now() + (60 * minutesBack);

  // Format as "yyyy-mm-dd hh:mm:00Z"
  return myTZ.dateTime(now, "  Y-m-d H:i:00~Z").substring(2); 
}

void readTelraam(char* telraamSegment)
{
  // Continue if Telraam enabled
  if (cfg::showTelRaam)
  {
    // Skip reading if crash risc due to low heap exists
    if (ESP.getFreeHeap() < MINIMUM_HEAP_TELRAAM)
    {
      Serial.println(FPSTR(INTL_TELRAAM_HEAP));
      return;
    }

    String startPeriodStr;
    String endPeriodStr;

    if (cfg::debugComms)
    {   
      Serial.print(FPSTR(INTL_TELRAAMAPI)); Serial.println(cfg::telraamApi);
      Serial.print(FPSTR(INTL_TELRAAM_SEGM)); Serial.println(telraamSegment);
    }
    // Wait for WiFi connection
    if (WiFi.status() == WL_CONNECTED)
    {
      if (cfg::freeToken)
      {
        // Free token, so no realtime data (yesterday instead)
        startPeriodStr = getFormattedTime(-25 * 60);
        endPeriodStr   = getFormattedTime(-24 * 60);
      }
      else
      {
        // Paid token, go for realtime data...
        startPeriodStr = getFormattedTime(-1 * 60);
        endPeriodStr   = getFormattedTime(0);
      }

      JsonDocument doc;
      doc["level"]      = "segments";
      doc["format"]     = "per-hour";
      doc["id"]         =  telraamSegment;
      doc["time_start"] =  startPeriodStr;
      doc["time_end"]   =  endPeriodStr;

      String request;
      serializeJson(doc, request);

      WiFiClientSecure client;
      client.setInsecure();             //hier
      HTTPClient http;

      http.begin(client, cfg::telraamApi);

      http.addHeader("Content-Type",   "application/json");
      http.addHeader("Content-Length", "150");
      http.addHeader("X-Api-Key",       apiToken);
      http.addHeader("Cache-Control",  "no-cache");
      http.addHeader("Connection",     "keep-alive");

      httpCode = http.POST(request);

      if (httpCode == HTTP_CODE_OK)
      {
        String payload = http.getString();
        const char* jsonResponse = payload.c_str();

        // Json parsing
        JsonDocument response;
        DeserializationError err = deserializeJson(response, jsonResponse);

        // Handle Json errors
        if (err)
        {
          Serial.print(FPSTR(INTL_TELRAAM_JSON_ERR));
          Serial.println(err.f_str());
          return;
        }

        // Resultaten ophalen uit json bericht
        for (JsonObject report_item : response["report"].as<JsonArray>()) 
        {
          realtime.heavy = report_item["heavy"];
          realtime.car   = report_item["car"];
          realtime.bike  = report_item["bike"];
          realtime.pedes = report_item["pedestrian"];
          realtime.speed = report_item["v85"];
        }  
      }

      // Free connection
      while (client.connected())
      {
        client.stop();
        delay(100);
      }

      // Close connection      
      http.end(); 
    }
  }
}

/*=================================================================================================
Andere meetwaarden die kunnen gedownload worden.
------------------------------------------------
            long report_item_segment_id = report_item["segment_id"]; // 9000001463
            const char* report_item_date = report_item["date"]; // "2024-07-30T07:00:00.000Z"
            const char* report_item_interval = report_item["interval"]; // "hourly"
            double report_item_uptime = report_item["uptime"]; // 0.9995834105
            double report_item_heavy = report_item["heavy"]; // 172.4991662034
            double report_item_car = report_item["car"]; // 604.9980544747
            double report_item_bike = report_item["bike"]; // 89.5022234575
            double report_item_pedestrian = report_item["pedestrian"]; // 27.9966648138
            int report_item_night = report_item["night"]; // 0
            double report_item_heavy_lft = report_item["heavy_lft"]; // 74.0019455253
            double report_item_heavy_rgt = report_item["heavy_rgt"]; // 98.4972206782
            double report_item_car_lft = report_item["car_lft"]; // 382.9977765425
            double report_item_car_rgt = report_item["car_rgt"]; // 222.0002779322
            double report_item_bike_lft = report_item["bike_lft"]; // 68.5011117287
            double report_item_bike_rgt = report_item["bike_rgt"]; // 21.0011117287
            double report_item_pedestrian_lft = report_item["pedestrian_lft"]; // 10.4983324069
            double report_item_pedestrian_rgt = report_item["pedestrian_rgt"]; // 20.9966648138
            int report_item_night_lft = report_item["night_lft"]; // 0
            int report_item_night_rgt = report_item["night_rgt"]; // 0
            int report_item_direction = report_item["direction"]; // 1
            //
            JsonArray report_item_car_speed_hist_0to70plus = report_item["car_speed_hist_0to70plus"];
            double report_item_car_speed_hist_0to70plus_0 = report_item_car_speed_hist_0to70plus[0];
            double report_item_car_speed_hist_0to70plus_1 = report_item_car_speed_hist_0to70plus[1];
            double report_item_car_speed_hist_0to70plus_2 = report_item_car_speed_hist_0to70plus[2];
            double report_item_car_speed_hist_0to70plus_3 = report_item_car_speed_hist_0to70plus[3];
            double report_item_car_speed_hist_0to70plus_4 = report_item_car_speed_hist_0to70plus[4];
            double report_item_car_speed_hist_0to70plus_5 = report_item_car_speed_hist_0to70plus[5];
            double report_item_car_speed_hist_0to70plus_6 = report_item_car_speed_hist_0to70plus[6];
            double report_item_car_speed_hist_0to70plus_7 = report_item_car_speed_hist_0to70plus[7]; 
            //
            JsonArray report_item_car_speed_hist_0to120plus = report_item["car_speed_hist_0to120plus"];
            double report_item_car_speed_hist_0to120plus_0 = report_item_car_speed_hist_0to120plus[0];
            double report_item_car_speed_hist_0to120plus_1 = report_item_car_speed_hist_0to120plus[1];
            double report_item_car_speed_hist_0to120plus_2 = report_item_car_speed_hist_0to120plus[2];
            double report_item_car_speed_hist_0to120plus_3 = report_item_car_speed_hist_0to120plus[3];
            double report_item_car_speed_hist_0to120plus_4 = report_item_car_speed_hist_0to120plus[4];
            double report_item_car_speed_hist_0to120plus_5 = report_item_car_speed_hist_0to120plus[5];
            double report_item_car_speed_hist_0to120plus_6 = report_item_car_speed_hist_0to120plus[6];
            double report_item_car_speed_hist_0to120plus_7 = report_item_car_speed_hist_0to120plus[7];
            double report_item_car_speed_hist_0to120plus_8 = report_item_car_speed_hist_0to120plus[8];
            double report_item_car_speed_hist_0to120plus_9 = report_item_car_speed_hist_0to120plus[9];
            double report_item_car_speed_hist_0to120plus_10 = report_item_car_speed_hist_0to120plus[10];
            double report_item_car_speed_hist_0to120plus_11 = report_item_car_speed_hist_0to120plus[11];
            double report_item_car_speed_hist_0to120plus_12 = report_item_car_speed_hist_0to120plus[12];
            double report_item_car_speed_hist_0to120plus_13 = report_item_car_speed_hist_0to120plus[13];
            double report_item_car_speed_hist_0to120plus_14 = report_item_car_speed_hist_0to120plus[14];
            double report_item_car_speed_hist_0to120plus_15 = report_item_car_speed_hist_0to120plus[15];
            double report_item_car_speed_hist_0to120plus_16 = report_item_car_speed_hist_0to120plus[16];
            double report_item_car_speed_hist_0to120plus_17 = report_item_car_speed_hist_0to120plus[17];
            double report_item_car_speed_hist_0to120plus_18 = report_item_car_speed_hist_0to120plus[18];
            double report_item_car_speed_hist_0to120plus_19 = report_item_car_speed_hist_0to120plus[19];
            double report_item_car_speed_hist_0to120plus_20 = report_item_car_speed_hist_0to120plus[20];
            double report_item_car_speed_hist_0to120plus_21 = report_item_car_speed_hist_0to120plus[21];
            double report_item_car_speed_hist_0to120plus_22 = report_item_car_speed_hist_0to120plus[22];
            double report_item_car_speed_hist_0to120plus_23 = report_item_car_speed_hist_0to120plus[23];
            double report_item_car_speed_hist_0to120plus_24 = report_item_car_speed_hist_0to120plus[24];
            //
            const char* report_item_timezone = report_item["timezone"]; // "Europe/Brussels"
            float report_item_v85 = report_item["v85"]; // 50.5
//===============================================================================================*/
