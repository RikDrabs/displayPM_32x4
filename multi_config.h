//*************************************************************************
// Multi configuration data
// ------------------------
// Here you can connect the display to a multitude of sensors, to handle them in group, 
// show the average values, show sensors that deviate too much from the average, and their values ​​and ratings.
// The number of sensors is setup in MULTI_MAX. More than 20 is possible, but not practical.
// Humans must be able to understand the results...
//
// Loaded with an example.
//*************************************************************************
//
#define   MULTI_MAX         8                     // # of sensors in this multi configuration
//
#define   MULTI_DEVIATION   25                    // maximum deviation in percent
#define   MULTI_MISSING     1                     // 1= show meters not transmitting
#define   MULTI_EXCESS      1                     // 1= show meters in excess
#define   EXCESS_AQI        1                     // 1= show AQI with excess meters
#define   EXCESS_GRAPH      1                     // 1= show graphic bar with excess meters
//
// Define text strings for sensor APIid's 
char  *multiSensor[] =
{
  "81878",               // API-id SDS sensor 3.
  "81156",               // API-id SDS sensor 4.
  "63847",               // API-id SDS sensor 5.  
  "63849",               // API-id SDS sensor 6.  
  "63853",               // API-id SDS sensor 7.
  "32124",               // API-id SDS sensor 8.
  "17548",               // API-id SDS sensor 9.
  "34138",               // API-id SDS sensor 10.
};  
//
// Define text strings for sensor names 
char  *multiName[] =
 
{
  "Meter 3 - 81878",     // Sensor 3 name.
  "Meter 4 - 81156",     // Sensor 4 name.
  "Meter 5 - 63847",     // Sensor 5 name.
  "Meter 6 - 63849",     // Sensor 6 name.
  "Meter 7 - 63853",     // Sensor 7 name.
  "Meter 8 - 32124",     // Sensor 8 name.
  "Meter 9 - 17548",     // Sensor 9 name.
  "Meter 10 - 34138",    // Sensor 10 name.
};  
//=============================================================================================================================================
