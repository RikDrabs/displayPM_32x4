PM/VOC/NOx/DNMS/TELRAAM display with an NTP clock

# displayPM_32x4

A display for sensor.community.

This is the result of further development of displayPM.
Like promised there, a web interface in the same style as the PM sensor is provided for.

What's new:
- 32 locations, each with 4 separate sensor id's can be followed up.
- Showing results from the DNMS system (digital noise measuring system) from sensor.community.
- Showing the results of Telraam, another project here in Belgium, to count traffic according to category of vehicle.

Building & explaining sessions will be held starting starting Februari, 2025 in HackerSpace Brussels, Osseghemstraat 53, 
1060 Molenbeek-Belgium. If you want to participate, please enroll via https://www.meetup.com/nl-NL/civic-lab-brussels/
If you're at the gate, call me 0475/70.72.60.

Extensions & corrections to the sourcecode will be made public through this channel.
Software falls under the GNU public Licence, for use in citizen science projects.

Suggestions for modifications, or bug corrections, can be send through pull requests.

In no way modify this main branch yourself.

## Features
* NTP sync with the servers of europe.pool.ntp.org
* Time adjusted for local time zone, and daylight saving time.
* Integration in Sensor.Community (formerly Luftdaten.Info)
* Configuration via WiFi in local network or with a Sensor-like Access-Point
* Show the measurements of up to 32*4 sensor API-ID's from the Sensor.Community network, 
* from up to 32 different locations.
* A few functions: 
  - Supervision of a list of up to 32 locations with up to 4 local sensors each, 
    with comprehensive messaging.
  - Compare two outside meters, or compare one inside & one outside meter, 
    with comprehensive messaging. 
  - Sensors can be PM, temperature, humidity, air pressure, noise (DNMS), 
    or the external project TELRAAM for counting traffic.
  - A countryside network of up to 32 locations with up to 4 sensors each can be monitored, 
    showing mean value, exceptions above an adjustable threshold, and missing sensors.
  - Results compared with WHO & AQI standards for PM. 
  - Display options fully controlable through web interface.

## BOM

* NodeMCU 0.9
* MX7219 compatible 8x8 LED Matrix modules, with 4 or 8 displays 8x8, cascadable,
* for a total of 16 displays 8x8.
* Each of the four different types of modules is supported.

## Information

The display uses the Parola library for ESP8266 which makes it easily scalable. 

## Pictures

(photos/display.png)
(photos/home.png)
(photos/value.png)
(photos/set1.png)
(photos/set2.png)
(photos/set3.png)
