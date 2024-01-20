//*************************************************************************
// NTP routines for Network Real Time use. 
//
#include  <NTPClient.h>                     // NTP Client
#include  <WiFiUdp.h>                       // Has variable type WiFiUDP, needed by timeClient()
#include  <time.h>                          // Time.h calls timelib.h

// NTP variables & setup   
long int updateInterval   = 1000*3600;      // Interval between calls to ntp, msec
long int gmtOffset        = 1*3600;         // European Standard Time Zone Time offset, seconds
long int summerOffset     = 1*3600;         // Daylight Savings offset(summertime), seconds
bool     enableSummer     = true;           // Enable / disable Daylight Savings
int      startSummerMonth = 3;              // Startmonth & day Daylight Savings
int      startSummerDay   = 31;             // "" 
int      endSummerMonth   = 10;             // Endmonth & day Daylight Savings
int      endSummerDay     = 31;             // ""
//
int      yearNow          = 0;              // Gregorian year.
int      monthNow         = 0;              // Month
int      dayOfMonthNow    = 0;              // Day of month
int      dayOfWeekNow     = 0;              // Day of week
int      hoursNow         = 0;              // Hours
int      minutesNow       = 0;              // Minutes
int      secondsNow       = 0;              // Seconds
int      secondsSave      = 0;              // Second save

WiFiUDP   ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", gmtOffset, updateInterval); // set up time client

// Calculate last sunday of month
int lastSunday(int iYear, int iMonth) {
  struct tm sTime = {0};
  sTime.tm_year = iYear - 1900;
  sTime.tm_mon = iMonth - 1;
  sTime.tm_mday = 31;
  mktime(&sTime);
  while (sTime.tm_wday != 0) {
    sTime.tm_mday--;
    mktime(&sTime);
  }
  return sTime.tm_mday;
}

// Check if in winter full months
bool inWinter() {
  return ((monthNow < startSummerMonth) || (monthNow > endSummerMonth)); 
}

// Check if in summer full months
bool inSummer() {
  return ((monthNow > startSummerMonth) && (monthNow < endSummerMonth));  
}  

// Switching logic to summertime
bool goingSummer(int days, int months) {
  if (months != monthNow) {
    return(false);
  }
  if (days > dayOfMonthNow) {
    return(false);
  }
  if (days < dayOfMonthNow) {
    return(true);
  }
  if (days = dayOfMonthNow) {
    if (hoursNow >= 2) {
      return(true);
    } else {
      return(false);
    }
  } 
}

// Switching logic to wintertime
bool goingWinter(int days, int months) {
  if (months != monthNow) {
    return(false);
  }
  if (days > dayOfMonthNow) {
    return(true);
  }
  if (days < dayOfMonthNow) {
    return(false);
  }
  if (days = dayOfMonthNow) {
    if (hoursNow >= 2) {
      return(false);
    } else {
      return(true);
    }
  }
}

// Correct the time according the the summertime rules
time_t daylightSavingsCorrection(time_t *eptm) {
  if (enableSummer) {
    if (!inWinter()) {  
      if (inSummer()) {
        *eptm+=summerOffset;
      }  
    }    
    if (goingSummer(lastSunday(yearNow + 1900, startSummerMonth), startSummerMonth)) {
      *eptm+=summerOffset;
    }
    if (goingWinter(lastSunday(yearNow + 1900, endSummerMonth), endSummerMonth)) {
      *eptm+=summerOffset;                                     
    }
  }
}

// Update all time variables in sync with NTP server
void updateTime() {
  timeClient.update();                      // will call ntp only if needed, based on updateInterval
  time_t eptm;                              // C++ variable type, seconds since 1900
  eptm = timeClient.getEpochTime();         // supposed to return sec since 1970, but magic here
  daylightSavingsCorrection(&eptm);         // correct Daylight Savings ...
  //
  struct        tm* timenow;                // C++ structure to hold times  
  timenow       = localtime(&eptm);         // function in time.h to get local time from time_t struct
  //
  yearNow       = timenow->tm_year+1900;    // Year; adjust to correct range
  monthNow      = timenow->tm_mon+1;        // Month; adjust to 1-12 range
  dayOfMonthNow = timenow->tm_mday;         // Day of month
  dayOfWeekNow  = timenow->tm_wday;         // Day of week
  hoursNow      = timenow->tm_hour;         // Hours
  minutesNow    = timenow->tm_min;          // Minutes
  secondsNow    = timenow->tm_sec;          // Seconds
}
