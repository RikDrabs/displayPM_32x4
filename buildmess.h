/**********************************************************************************
 * Build messages for:                                                            *
 * Large Bargraph Remote Display for:                                             *
 *                                                                                *
 * Luftdaten.info - Sensor.Community - InfluencAir - Luchtpijp - Telraam.         *
 * Display on LEDmatrix 16*8*8 dots, monocolor or (in the future) multicolor.     *
 *                                                                                *
 * Copyright (C) 2019/2025 Rik Drabs - rik.drabs@gmail.com                        *
 * Copyright (C) 2023/2025 InfluencAir - influencair2017@gmail.com                *
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

// This is the mean messagebuffer. It receives the lines to display from received data.
// You can place messages to be displayed directly in the buffer.
// Messages must start with S for scrolling, or with F for fixed format.
// Use lowercase (s, f) for characters without intermediate pixel column (graphics, etc.)
// Use T for time display, and B for a short blank display.

char        messageBuffer[NUMSTR][NUMCHR];  // message buffer

// UTF8 to Extended ASCII conversion of text
uint8_t utf8AsciiCh(uint8_t ascii)
// Convert a single Character from UTF8 to Extended ASCII according to ISO 8859-1,
// also called ISO Latin-1. Codes 128-159 contain the Microsoft Windows Latin-1
// extended characters:
// - codes 0..127 are identical in ASCII and UTF-8
// - codes 160..191 in ISO-8859-1 and Windows-1252 are two-byte characters in UTF-8
//                 + 0xC2 then second byte identical to the extended ASCII code.
// - codes 192..255 in ISO-8859-1 and Windows-1252 are two-byte characters in UTF-8
//                 + 0xC3 then second byte differs only in the first two bits to extended ASCII code.
// - codes 128..159 in Windows-1252 are different, but usually only the €-symbol will be needed from this range.
//                 + The euro symbol is 0x80 in Windows-1252, 0xa4 in ISO-8859-15, and 0xe2 0x82 0xac in UTF-8.
//
// Modified from original code at http://playground.arduino.cc/Main/Utf8ascii
// Extended ASCII encoding should match the characters at http://www.ascii-code.com/
//
// Return "0" if a byte has to be ignored.
{
  static uint8_t cPrev = '\0';
  uint8_t c = '\0';

  if (ascii < 0x7f) 
  {                                         // Standard ASCII-set 0..0x7F, no conversion
    cPrev = '\0';
    c = ascii;
  }
  else
  {
    switch (cPrev)
    {                                       // Conversion depending on preceding UTF8-character
      case 0xC2: 
      {
        c = ascii;
        break;
      }  
      case 0xC3:
      {
        c = ascii | 0xC0;
        break;
      }
      case 0x82:
      {
        if (ascii == 0xAC)
        {
          c = 0x80;                         // Euro symbol special case
          break;
        }
      }
    }
    cPrev = ascii;                          // save last char
  }
  return (c);
}

// In place conversion UTF-8 string to Extended ASCII
// The extended ASCII string is always shorter.
void utf8Ascii(char* s)
{
  uint8_t c;
  char *cp = s;
  while (*s != '\0')
  {
    c = utf8AsciiCh (*s++);
    if (c != '\0')
      *cp++ = c;
  }
  *cp = '\0';                               // terminate the new string
}

// Do one time in-place conversion of all the strings to be n on display
void convertStrings()
{
  for (i = 0; i < NUMSTR; i++)
  {
    utf8Ascii(messageBuffer[i]);
  }

  for (i = 0; i < ARRAY_SIZE(dotMatrixText); i++)
  {
    utf8Ascii(dotMatrixText[i]);
  }

  for (i = 0; i < ARRAY_SIZE(compareText); i++)
  {
    utf8Ascii(compareText[i]);
  }

  for (i = 0; i < ARRAY_SIZE(AQItext); i++)
  {
    utf8Ascii(AQItext[i]);
  }

  for (i = 0; i < ARRAY_SIZE(WHOtext); i++)
  {
    utf8Ascii(WHOtext[i]);
  }
}

// Table driven compare system
const float compareTable[] = 
{  
  //==============================
    -100,   // Outdoor = -100%/-35%
    -25,    // Open windows
  //==============================
    -25,    // Outdoor = -35%/-10%
    -10,    // No advice for windows
  //==============================
    -10,    // Outdoor = -10%/+10%
    +10,    // No advice for windows
  //==============================
    +10,    // Outdoor = +10%/+35%
    +25,    // No advice for windows
  //==============================
    +25,    // Outdoor = +35%/+100%
    +100,   // Close windows
  //==============================
    +100,   // Outdoor = >+100%
    +10000, // Close windows
  //==============================
};

// Damping factor for small values PM
// Damping is added to both PM values before comparing to % result.
#define     DAMPING           5       // minimum 0 - maximum 10

// Build scrolling comparison message describing the Sensor1 versus Sensor2 PM values.
void buildCompareTwo(uint8_t location)
// Parameters:
//   location: actual location in treatment, should be the first location in the compare
{
  // Option enabled & @correct location & prevent writing outside of buffer
  if ((cfg::showComp) && (location == cfg::compareLocation) && (toDisplayLine < NUMSTR))
  {
    float tmp1;
    float tmp2;
    float compResult;
    float posResult;
    uint8_t pTable = 0;                                       
    uint8_t pText = 0;
    bool found = false;

    // Select between PM2.5 and PM10
    if (cfg::pmChoice == SELECT_PM25)
    { 
      tmp1 = readPm25[cfg::compareLocation];    
      tmp2 = readPm25[cfg::compareLocation2];
    }
    else 
    { 
      tmp1 = readPm10[cfg::compareLocation];    
      tmp2 = readPm10[cfg::compareLocation2];
    }

    // Ensure sensor values OK    
    if ((tmp1 > -100.0f) && (tmp2 > -100.0f))             
    {
      if (cfg::showCompInside)
      {
        // Result = compare indoor/Sensor1 in +/- percentage difference viewed from indoor
        compResult = ((((tmp1+DAMPING)/(tmp2+DAMPING))*100)-100);

        // Loop through table until condition is met, or table end is reached
        while (true) 
        {
          if (pTable > ARRAY_SIZE(compareTable)) break;
          //
          if (compareTable[pTable] <= compResult)
          {
            if (compareTable[pTable+1] > compResult)
            {
              found = true;
              break;
            }
          }
          pTable+=2; pText++;
        }

        if (found)
        {
          displayString[0] = SCROLL_TEXT;                       // scrolling mode, 1 pixel spacing
          displayString[1] = '\0';                              // terminate string
          strcat(displayString, compareText[pText]);            // add the compare text

          // Add constructed line to message buffer
          String(displayString).toCharArray(messageBuffer[toDisplayLine++], NUMCHR-4);
        }
      }
      else
      {
        // result = compare outdoor 1/outdoor 2 in +/- percentage difference viewed from outdoor 1
        compResult = (((tmp1/tmp2)*100)-100);
        posResult = compResult;
        if (compResult < 0)
        {
          posResult = (0 - compResult);
        } 

        displayString[0] = SCROLL_TEXT;                         // scrolling mode, 1 pixel spacing
        displayString[1] = '\0';                                // terminate string
        strcat(displayString, dotMatrixText[STR_PERCENT1]);     // string "Er is "
        sprintf(workString, "%d", (int)(posResult));            // make compare result into string
        strcat(displayString, workString);                      // and add it

        if (compResult > 0) 
        {
          strcat(displayString, dotMatrixText[STR_PERCENT2]);   // string " meer "
        }
        else 
        {
          strcat(displayString, dotMatrixText[STR_PERCENT3]);   // string " minder "
        }

        // Select between PM2.5 and PM10
        if (cfg::pmChoice == SELECT_PM25)
        {
          strcat(displayString, "PM2.5");                       // string "PM2.5"
        }
        else
        {
          strcat(displayString, "PM10");                        // string "PM10"
        }

        strcat(displayString, dotMatrixText[STR_PERCENT5]);     // string " fijnstof bij meter "

        String(multiName[cfg::compareLocation]).toCharArray(workString, LEN_LOCATION_NAME);
        utf8Ascii(workString);
        strcat(displayString, workString);                      // add sensor 1 name

        strcat(displayString, dotMatrixText[STR_PERCENT4]);     // string " dan bij meter "

        String(multiName[cfg::compareLocation2]).toCharArray(workString, LEN_LOCATION_NAME);
        utf8Ascii(workString);
        strcat(displayString, workString);                      // add sensor 2 name

        // Add constructed line to message buffer
        String(displayString).toCharArray(messageBuffer[toDisplayLine++], NUMCHR-4); 
      }  
    }
  }
}

// Build date & time message
void buildTime(const uint8_t messageNbr)
// Parameters:
//   messageNbr:    message number to overwrite with time string.
{
  if (cfg::clockSeconds && timeCorrect)
  {
    // Prevent writing outside of buffer
    if (messageNbr < NUMSTR)                                   
    {
      String strTime = dayStr()+myTZ.dateTime(" d/m/Y H:i:s");  // get day of week in local language, and add formatted time in string type format
      strTime.toCharArray(workString, sizeof(workString));      // convert to char[] type

      displayString[0] = FIXED_TIME;                            // fixed left justified, 1 pixel spacing, update time
      displayString[1] = '\0';                                  // terminate string
      strcat(displayString, workString);                        // add time data

      // Add constructed line to message buffer
      String(displayString).toCharArray(messageBuffer[messageNbr], NUMCHR-4);
      toDisplayLine++;                                          // point next message      
    }
  }
}

// Build date/time & welcome message, choosing from welcome1 and welcome2
void buildWelcomeTime()
{
  if (++welkomCount >= cfg::welkomInterval)
  {
    // Prevent writing outside of buffer
    if (toDisplayLine < NUMSTR)                                 
    {
      // mark display buffer not empty    
      displayBufferEmpty = false;
        
      displayString[0] = SCROLL_TEXT;                           // scrolling mode, 1 pixel spacing
      displayString[1] = '\0';                                  // terminate string
      if (betweenMessages)
      {
        betweenMessages = false;
        strcat(displayString, cfg::welkom2);                    // add welcome 2        
      }
        else
      {
        betweenMessages = true;
        strcat(displayString, cfg::welkom);                     // add welcome 1
      }
      // Add constructed line to message buffer
      String(displayString).toCharArray(messageBuffer[toDisplayLine], NUMCHR-4);

      utf8Ascii(messageBuffer[toDisplayLine]);                  // convert code pages
      toDisplayLine++;                                          // point next message
      
      // Build date & time
      buildTime(toDisplayLine);                                 // build time message
    }
    welkomCount = 0;                                            // restart the cycle
  } 
}

// Build a message in the message buffer
static void buildMessage(const char* message)
// Parameters:
//   message:  The message
{
  // Prevent writing outside of buffer
  if (toDisplayLine < NUMSTR)                                   
  {
    displayString[0] = FIXED_TEXT;                              // fixed mode, 1 pixel spacing
    displayString[1] = '\0';                                    // terminate string
    strcat(displayString, message);                             // add message

    // Add constructed line to message buffer
    String(displayString).toCharArray(messageBuffer[toDisplayLine++], NUMCHR-4);    
  }
}

// Build a blank line in the message buffer
static void buildBlankLine(bool blankPause)
// Parameters:  
//   blankPause:     true = insert a blank pause  
{
  // Prevent writing outside of buffer
  if ((blankPause) && (toDisplayLine < NUMSTR))                                  
  {
    displayString[0] = FIXED_BLANK;                             // blank line, to pause display  
    displayString[1] = '\0';                                    // terminate string  

    // Add constructed line to message buffer
    String(displayString).toCharArray(messageBuffer[toDisplayLine++], NUMCHR-4); 
  } 
}  

// Build a fixed location message in the message buffer
static void buildLocationMessage(uint8_t location, const char* message, bool blankPause)
// Parameters:  
//   location:       The location number.
//   message:        Terminating char. (:)
//   blankPause:     true = insert a blank pause        
{
  // mark display buffer not empty    
  displayBufferEmpty = false;

  // Blank line for 1/2 sec, if asked for.
  buildBlankLine(blankPause);  

  // Prevent writing outside of buffer
  if (toDisplayLine < NUMSTR)                                   
  {
    // Convert location message to ascii display chars.
    String(multiName[location]).toCharArray(workString, LEN_LOCATION_NAME);
    utf8Ascii(workString);

    displayString[0] = FIXED_TEXT;                              // fixed mode, 1 pixel spacing  
    displayString[1] = '\0';                                    // terminate string
    strcat(displayString, workString);                          // add location text
    strcat(displayString, message);                             // add terminating char.

    // Add constructed line to message buffer
    String(displayString).toCharArray(messageBuffer[toDisplayLine++], NUMCHR-4);      
  }
}

// Build a scrolling PM message in the message buffer
static void buildPmMessage(const float pm_1, const float pm_25,
                           const float pm_4, const float pm_10)
// Parameters:
//   thisMessage:   The begin text.
//   pm_1:          PM1 value to show.
//   pm_25:         PM2.5 value to show.
//   pm_4:          PM4 value to show.
//   pm_10:         PM10 value to show.
{
  // Prevent writing outside of buffer
  if (toDisplayLine < NUMSTR)                                 
  {
    // Ensure value(s) are OK
    if ((pm_10 > -100.0f) || (pm_25 > -100.0f))
    {
      displayString[0] = SCROLL_TEXT;                         // scrolling mode, 1 pixel spacing
      displayString[1] = '\0';                                // terminate string
      strcat(displayString, dotMatrixText[STR_FS]);           // add begin text

      if ((cfg::showPm1Pm4) && (pm_4 > -100.0f))
      {
        strcat(displayString, " PM4: ");  
        rounder(pm_4, 1).toCharArray(workString, 30);         // prepare value               
        strcat(displayString, workString);                    // incorporate measured value
        strcat(displayString, dotMatrixText[STR_UGRAM3]);     // final µg/m³ message
      }
      if ((cfg::showPm1Pm4) && (pm_1 > -100.0f))
      {
        strcat(displayString, " PM1: ");
        rounder(pm_1, 1).toCharArray(workString, 30);         // prepare value          
        strcat(displayString, workString);                    // incorporate measured value
        strcat(displayString, dotMatrixText[STR_UGRAM3]);     // final µg/m³ message
      }
      if (pm_10 > -100.0f)
      {
        strcat(displayString, " PM10: ");
        rounder(pm_10, 1).toCharArray(workString, 30);          // prepare value        
        strcat(displayString, workString);                      // incorporate value
        strcat(displayString, dotMatrixText[STR_UGRAM3]);       // add final µg/m³ message
      }
      if (pm_25 > -100.0f)
      {
        strcat(displayString, " PM2.5: ");
        rounder(pm_25, 1).toCharArray(workString, 30);          // prepare value
        strcat(displayString, workString);                      // incorporate value
        strcat(displayString, dotMatrixText[STR_UGRAM3]);       // add final µg/m³ message
      }

      // Add constructed line to message buffer
      String(displayString).toCharArray(messageBuffer[toDisplayLine++], NUMCHR-4);     
    }
  }
}

// Build average & peak message buffer
static void buildAvgNpeak(const uint8_t location)
// Parameters:
//   location:    show vlues of this location
{
  if (cfg::showAvgNpeak)
  {
    // Prevent writing outside of buffer
    if (toDisplayLine < NUMSTR)                                   
    {
      float average;
      float peak;

      // Prepare result
      displayString[0] = SCROLL_TEXT;     // scrolling mode, 1 pixel spacing
      displayString[1] = '\0';            // terminate string      

      // Get values (Switch PM2.5/PM10)
      if (cfg::pmChoice == SELECT_PM25)
      {
        average = cumulAvgPm25[location];
        peak = peakPm25[location];
        strcat(displayString, " PM2.5: ");
      }
      else
      {
        average = cumulAvgPm10[location];
        peak = peakPm10[location];
        strcat(displayString, " PM10: ");
      }

      // Values valid ?
      if ((average > -100.0f) && (peak > -100.0f))                 
      {
        // Show average 24h.
        strcat(displayString, dotMatrixText[STR_AVG24]);        // add "average 24h.= " message
        rounder(average, 1).toCharArray(workString, 30);        // prepare value   
        strcat(displayString, workString);                      // incorporate measured value
        strcat(displayString, dotMatrixText[STR_UGRAM3]);       // add final "µg/m³" message

        // Show maximum 24h.
        strcat(displayString, "; ");
        strcat(displayString, dotMatrixText[STR_MAX24]);        // add "peak 24h.= " message
        rounder(peak, 1).toCharArray(workString, 30);           // prepare value
        strcat(displayString, workString);                      // incorporate measured value
        strcat(displayString, dotMatrixText[STR_UGRAM3]);       // add final "µg/m³" message

        // Add constructed line to message buffer
        String(displayString).toCharArray(messageBuffer[toDisplayLine++], NUMCHR-4);
      }
    }
  }
}

// Construct string containing bargraph
// Don't show bargraph if value not OK.
static void GraphDisplayStr(float showValue, const uint8_t maxVal)
{
  if (showValue >= 0.0)                                         // test if value OK
  {                                       
    uint8_t dotsAvailable = 8 * MAX_DEVICES;                    // total available dots till end of display
    uint8_t dotScale10;                                         // dots to fill scale 0 to 10
    uint8_t dotScale100;                                        // dots to fill scale 0 to 100
    uint8_t dotsNeeded;                                         // dots needed to show value
    uint8_t dotsTemp;                                           // dots temperature value
    uint8_t white;                                              // counter for "white" bar
    uint8_t black;                                              // counter for "black" bar
    uint8_t scaleCount;                                         // scale counter
    uint8_t scaleMark;                                          // scale mark counter
    uint8_t arrpnt;                                             // array pointer
    bool overTheTop = false;                                    // data bigger than display
    bool topDrawn = false;                                      // top drawn flag

    if (showValue > (1.2 * maxVal)) 
    {                                                           // limit to maximum+ to avoid overflow crash
      showValue = (1.2 * maxVal);
    }
    // Start building graph line
    // Set format & bolleke
    arrpnt = 0;
    displayString[arrpnt++] = FIXED_GRAPHICS;                   // fixed mode, no pixel spacing
    displayString[arrpnt++] = BAR_BOL;                          // bolleke
    displayString[arrpnt++] = BAR_WIDTH_1;                      // 1 pixel
    dotsAvailable -= 9;                                         // adjust dotsAvailable (9 less: bolleke + 1 pixel)
    dotsAvailable -= 2;                                         // adjust dotsAvailable (2 less: 1 x double BAR_SCALE)
    dotsAvailable -= 2;                                         // adjust dotsAvailable (2 less: 2 x 1/2 double BAR_SCALE)

    dotScale10 = (dotsAvailable/10);                            // calculate dots to represent scale step of 10%
    dotScale100 = (dotScale10*10);                              // calculate dots to represent scale 0 to 100

    dotsTemp = (showValue + 0.5f);                              // round & convert to int
    dotsNeeded = ((dotsTemp*dotScale100)/maxVal);               // calculate dots to show value

    // check for overflow
    if (dotsNeeded > dotsAvailable) 
    {
      dotsNeeded = dotsAvailable;
      overTheTop = true;
    }
    scaleMark = 11;                                             // 11 scale marks
    while (scaleMark--)
    {
      // Draw full / half scale
      switch (scaleMark)
      {
        case 0: 
          // Fall through
        case 5:                                                 // half scale
          if (dotsNeeded) dotsNeeded--;
          // Fall through
        case 10: 
        {                                                       // begin scale
          displayString[arrpnt++] = BAR_SCALE;
          displayString[arrpnt++] = BAR_SCALE;
          if (dotsAvailable) dotsAvailable--;
          if (dotsAvailable) dotsAvailable--;
          break;
        }  
        default:
        {                                                       // all other places
          displayString[arrpnt++] = BAR_HLFSCAL;
          if (dotsAvailable) dotsAvailable--;
          if (dotsNeeded) dotsNeeded--;
          break;
        }
      }
      // Draw "white" dots when value not yet reached, else draw "black" dots
      white = 0; black = 0;
      scaleCount = (dotScale10-1);

      while ((dotsAvailable) && (scaleCount))
      {
        if (dotsAvailable) dotsAvailable--;
        if (scaleCount) scaleCount--;
        if (dotsNeeded)
        {
          dotsNeeded--;
          white++;
        }
        else 
        {
          black++;
        }
      }
      if (white > 8)
      {
        displayString[arrpnt++] = BAR_WIDTH_7; 
        displayString[arrpnt++] = BAR_WIDTH_1;
        white -= 8;
      }
      switch (white)
      {
        case 0:
          break;
        case 1:
        {
          displayString[arrpnt++] = BAR_WIDTH_1;
          break;
        }
        case 2:
        {
          displayString[arrpnt++] = BAR_WIDTH_1;
          displayString[arrpnt++] = BAR_WIDTH_1;
          break;
        }
        case 3:
        {
          displayString[arrpnt++] = BAR_WIDTH_1;
          displayString[arrpnt++] = BAR_WIDTH_1;
          displayString[arrpnt++] = BAR_WIDTH_1;
          break;
        }
        case 4:
        {
          displayString[arrpnt++] = BAR_WIDTH_1;
          displayString[arrpnt++] = BAR_WIDTH_1;
          displayString[arrpnt++] = BAR_WIDTH_1;
          displayString[arrpnt++] = BAR_WIDTH_1;
          break;
        }
        case 5:
        {
          displayString[arrpnt++] = BAR_WIDTH_2;
          displayString[arrpnt++] = BAR_WIDTH_1;
          displayString[arrpnt++] = BAR_WIDTH_1;
          displayString[arrpnt++] = BAR_WIDTH_1;
          break;
        }
        case 6:
        {
          displayString[arrpnt++] = BAR_WIDTH_3;
          displayString[arrpnt++] = BAR_WIDTH_1;
          displayString[arrpnt++] = BAR_WIDTH_1;
          displayString[arrpnt++] = BAR_WIDTH_1;
          break;
        }
        case 7:
        {
          displayString[arrpnt++] = BAR_WIDTH_4;
          displayString[arrpnt++] = BAR_WIDTH_1;
          displayString[arrpnt++] = BAR_WIDTH_1;
          displayString[arrpnt++] = BAR_WIDTH_1;
          break;
        }
        case 8:
        {
          displayString[arrpnt++] = BAR_WIDTH_5;
          displayString[arrpnt++] = BAR_WIDTH_1;
          displayString[arrpnt++] = BAR_WIDTH_1;
          displayString[arrpnt++] = BAR_WIDTH_1;
          break;
        }
        default:
          break;
      }
      if (!dotsNeeded) 
      {
        if (topDrawn == false)
        {
          topDrawn = true;
          if ((displayString[arrpnt-1] != BAR_SCALE)&&(displayString[arrpnt-1] != BAR_HLFSCAL))
          {
            // Generate rounded top (from 0 to 100)
            displayString[arrpnt-1] = BAR_TOP;
          }
        }
      }
      if (black > 8) 
      {
        displayString[arrpnt++] = BAR_BLANK_7;
        displayString[arrpnt++] = BAR_BLANK_1;
        black -= 8;
      }
      switch(black) 
      {
        case 0:
          break;
        case 1:
        {
          displayString[arrpnt++] = BAR_BLANK_1; 
          break;
        }  
        case 2:
        {
          displayString[arrpnt++] = BAR_BLANK_1;
          displayString[arrpnt++] = BAR_BLANK_1;
          break;
        }
        case 3:
        {
          displayString[arrpnt++] = BAR_BLANK_1;
          displayString[arrpnt++] = BAR_BLANK_1;
          displayString[arrpnt++] = BAR_BLANK_1;
          break;
        }
        case 4:
        {
          displayString[arrpnt++] = BAR_BLANK_1;
          displayString[arrpnt++] = BAR_BLANK_1;
          displayString[arrpnt++] = BAR_BLANK_1;
          displayString[arrpnt++] = BAR_BLANK_1;
          break;
        }
        case 5:
        {
          displayString[arrpnt++] = BAR_BLANK_2;
          displayString[arrpnt++] = BAR_BLANK_1;
          displayString[arrpnt++] = BAR_BLANK_1;
          displayString[arrpnt++] = BAR_BLANK_1;
          break;
        }
        case 6:
        {
          displayString[arrpnt++] = BAR_BLANK_3;
          displayString[arrpnt++] = BAR_BLANK_1;
          displayString[arrpnt++] = BAR_BLANK_1;
          displayString[arrpnt++] = BAR_BLANK_1;
          break;
        }
        case 7:
        {
          displayString[arrpnt++] = BAR_BLANK_4;
          displayString[arrpnt++] = BAR_BLANK_1;
          displayString[arrpnt++] = BAR_BLANK_1;
          displayString[arrpnt++] = BAR_BLANK_1;
          break;
        }
        case 8:
        {
          displayString[arrpnt++] = BAR_BLANK_5;
          displayString[arrpnt++] = BAR_BLANK_1;
          displayString[arrpnt++] = BAR_BLANK_1;
          displayString[arrpnt++] = BAR_BLANK_1;
          break;
        }
        default:
          break;
      }
    }
    // over 100%
    if (dotsNeeded > 8)
    {
      dotsNeeded -= 8;
      displayString[arrpnt++] = BAR_WIDTH_5;
      displayString[arrpnt++] = BAR_WIDTH_1;
      displayString[arrpnt++] = BAR_WIDTH_1;
      displayString[arrpnt++] = BAR_WIDTH_1;
    }
    switch(dotsNeeded)
    {
      case 0:
        break;
      case 1:
      {
        displayString[arrpnt++] = BAR_WIDTH_1;
        break;
      }
      case 2:
      {
        displayString[arrpnt++] = BAR_WIDTH_1;
        displayString[arrpnt++] = BAR_WIDTH_1;
        break;
      }
      case 3:
      {
        displayString[arrpnt++] = BAR_WIDTH_1;
        displayString[arrpnt++] = BAR_WIDTH_1;
        displayString[arrpnt++] = BAR_WIDTH_1;
        break;
      }  
      case 4:
      {
        displayString[arrpnt++] = BAR_WIDTH_1;
        displayString[arrpnt++] = BAR_WIDTH_1;
        displayString[arrpnt++] = BAR_WIDTH_1;
        displayString[arrpnt++] = BAR_WIDTH_1;
        break;
      }
      case 5: 
      {
        displayString[arrpnt++] = BAR_WIDTH_2;
        displayString[arrpnt++] = BAR_WIDTH_1;
        displayString[arrpnt++] = BAR_WIDTH_1;
        displayString[arrpnt++] = BAR_WIDTH_1;
        break;
      }
      case 6: 
      {
        displayString[arrpnt++] = BAR_WIDTH_3;
        displayString[arrpnt++] = BAR_WIDTH_1;
        displayString[arrpnt++] = BAR_WIDTH_1;
        displayString[arrpnt++] = BAR_WIDTH_1;
        break;
      }
      case 7: 
      {
        displayString[arrpnt++] = BAR_WIDTH_4;
        displayString[arrpnt++] = BAR_WIDTH_1;
        displayString[arrpnt++] = BAR_WIDTH_1;
        displayString[arrpnt++] = BAR_WIDTH_1;
        break;
      }
      case 8:
      {
        displayString[arrpnt++] = BAR_WIDTH_5;
        displayString[arrpnt++] = BAR_WIDTH_1;
        displayString[arrpnt++] = BAR_WIDTH_1;
        displayString[arrpnt++] = BAR_WIDTH_1;
        break;
      }
      default:
        break;
    }
    // last dots
    if (overTheTop)
    {
      // Generate oblique cut
      topDrawn = true;
      displayString[arrpnt-3] = BAR_BREAK_3; 
      displayString[arrpnt-2] = BAR_BREAK_2; 
      displayString[arrpnt-1] = BAR_BREAK_1;
    }
    // Terminate string
    displayString[arrpnt++] = '\0';
  }
}

// Build bargraph in message buffer
static void buildGraph(const float value25, const uint8_t max25,
                const float value10, const uint8_t max10)
// Parameters:
//   value25:   PM25 value to show in graphical form.
//   max25:     PM25 Value at full display (= 200%)
//   value10:   PM10 value to show in graphical form.
//   max10:     PM10 Value at full display (= 200%)
{
  static float tmp1;
  uint8_t i;

  // Prevent writing outside of buffer
  if (toDisplayLine < NUMSTR)               
  {
    // Switch PM2.5/PM10
    if (cfg::pmChoice == SELECT_PM25)
    { 
      tmp1 = value25;
      i = max25;
    } 
    else 
    { 
      tmp1 = value10;
      i = max10;
    }

    if ((cfg::showGraph) && (tmp1 > -100.0f)) 
    {
      displayString[0] = FIXED_TEXT;        // fixed mode, 1 pixel spacing
      displayString[1] = '\0';              // terminate string
      GraphDisplayStr(tmp1, i);             // build graph in displayString

      // Add constructed line to message buffer
      String(displayString).toCharArray(messageBuffer[toDisplayLine++], NUMCHR-4);
    }
  }
}

// Build scrolling AQI message describing the outdoor PM air quality.
static void buildAQIadvice(const float aqiValuePm25, const float aqiValuePm10)
// Parameters:
//   aqiValuePm25:  PM2,5 value to interpret
//   aqiValuePm10:  PM10 value to interpret  
{
  float aqiValue;

  if (cfg::showAqiAdvice)
  {
    // Prevent writing outside of buffer
    if (toDisplayLine < NUMSTR)                                 
    {  
      // Value valid ?
      if ((aqiValuePm25 > -100.0f) || (aqiValuePm10 > -100.0f))       
      {
        // Determine relative weight of PM2.5 & PM10 
        if (cfg::pmChoice == SELECT_PM25)
        { 
          aqiValue = ((aqiValuePm25 * 50) / cfg::PM25toAQI50);
        } 
        else 
        { 
          aqiValue = ((aqiValuePm10 * 50) / cfg::PM10toAQI50);
        }

        // Initialize pointers  
        uint8_t pTable = 0; 
        uint8_t pText = 0;
        bool resultFound = false;

        // Loop through table until condition is met, or table end is reached
        while (aqiTable[pTable+1])
        {
          if (aqiTable[pTable] <= aqiValue)
          {
            if (aqiTable[pTable+1] > aqiValue)
            { 
              resultFound = true; 
              break; 
            }
          }
          pTable++; pText++;
        }
        if (resultFound)
        {
          displayString[0] = SCROLL_TEXT;                       // scrolling mode, 1 pixel spacing
          displayString[1] = '\0';                              // terminate string
          strcat(displayString, AQItext[pText]);                // add the advice text

          // Add constructed line to message buffer
          String(displayString).toCharArray(messageBuffer[toDisplayLine++], NUMCHR-4);
        }
      }
    }
  }
}

// Build scrolling WHO message describing the outdoor PM air quality.
static void buildWHOadvice(const float whoValuePm25, const float whoValuePm10)
// Parameters:
//   whoValue:   value to interpret.
{
  float whoValue;

  if (cfg::showWhoAdvice)
  { 
    // Prevent writing outside of buffer
    if (toDisplayLine < NUMSTR)
    {
      // Value valid ?
      if ((whoValuePm25 > -100.0f) || (whoValuePm10 > -100.0f))
      {
        // For PM10, adjust to relative weight of PM2.5 & PM10
        if (cfg::pmChoice == SELECT_PM25)
        {
          whoValue = whoValuePm25;          
        }
        else
        {
          whoValue = ((whoValuePm10 * cfg::max25WHO) / cfg::max10WHO);
        }

        // Initialize pointers
        uint8_t pTable = 0;
        uint8_t pText = 0;
        bool resultFound = false;

        // Loop through table until condition is met, or table end is reached
        while (whoTable[pTable+1])
        {
          if (whoTable[pTable] <= whoValue)
          {
            if (whoTable[pTable+1] > whoValue)
            {
              resultFound = true;
              break;
            }
          }
          pTable++; pText++;
        }
        if (resultFound)
        {
          displayString[0] = SCROLL_TEXT;                       // scrolling mode, 1 pixel spacing
          displayString[1] = '\0';                              // terminate string
          strcat(displayString, WHOtext[pText]);                // add the advice text

          // Add constructed line to message buffer
          String(displayString).toCharArray(messageBuffer[toDisplayLine++], NUMCHR-4);
        }
      }
    }
  }
}

// Build meteo message
static void buildMeteoMessage(const char* thisMessage, const float temp, 
                         const float humi, const float press)
// Parameters:
//   thisMessage:   The begin text.
//   temp:          the temperature value to show.
//   humi:          the humidity value to show.
//   press:         the pressure value to show.
{
  if (cfg::showMeteo)
  {
    // Prevent writing outside of buffer
    if (toDisplayLine < NUMSTR)                                 
    {
      // Ensure temperature value is OK
      if (temp > -100.0f)
      {
        displayString[0] = FIXED_TEXT;                          // fixed mode, 1 pixel spacing
        displayString[1] = '\0';                                // terminate string        
        strcat(displayString, thisMessage);                     // add begin text

        strcat(displayString, dotMatrixText[STR_THERMO]);       // add temperature sign
        rounder(temp, 0).toCharArray(workString, 30);           // prepare value
        strcat(displayString, workString);                      // incorporate measured value
        strcat(displayString, dotMatrixText[STR_DEGREES]);      // add degrees Celsius message 

        // Ensure humidity value is OK
        if (humi > -100.0f) 
        {
          strcat(displayString, dotMatrixText[STR_DROPLET]);    // add droplet sign
          sprintf(workString, "%d", ((int)(humi + 0.5f)));      // prepare value
          strcat(displayString, workString);                    // incorporate measured value
          strcat(displayString, "%");                           // add percent message
        }

        // Ensure pressure value is OK
        if (press > -100.0f)
        {
          strcat(displayString, dotMatrixText[STR_PRESS]);      // add "Pressure = " string
          sprintf(workString, "%d", ((int)(press + 0.5f)));     // prepare value
          strcat(displayString, workString);                    // incorporate measured value
          strcat(displayString, " hPa");
        }

        // Add constructed line to message buffer
        String(displayString).toCharArray(messageBuffer[toDisplayLine++], NUMCHR-4);     
      }
    }
  }
}

// Build VOC / NOx Message
static void buildVocNoxMessage(const char* thisMessage, const float voc, const float nox)
{
  if (cfg::showMeteo)
  {
    // Prevent writing outside of buffer
    if (toDisplayLine < NUMSTR)                                 
    {
      // Ensure VOC & NOx values OK
      if ((voc > -100.0f) && (nox > -100.0f))
      {
        displayString[0] = SCROLL_TEXT;                         // scrolling mode, 1 pixel spacing
        displayString[1] = '\0';                                // terminate string  

        // Add constructed line to message buffer
        String(displayString).toCharArray(messageBuffer[toDisplayLine++], NUMCHR-4);
      }          
    }
  }    
}

// Build a noise describing message
static void buildNoiseMessage(const float LAmax, const float LAmin, const float LAeq)
// Parameters:
//   LAmax:         The noise maximum value in dBa
//   LAmin:         The noise minimum value in dBa
//   LAeq:          The noise median value in dBa
{
  if (cfg::showDnms)
  {
    // Prevent writing outside of buffer
    if (toDisplayLine < NUMSTR)                                   
    {
      // Ensure values are OK
      if ((LAmax > -100.0f) && (LAmin > -100.0f))
      {
        displayString[0] = SCROLL_TEXT;                           // scrolling mode, 1 pixel spacing
        displayString[1] = '\0';                                  // terminate string
        strcat(displayString, dotMatrixText[STR_DNMS]);           // add "Lawaai: "

        strcat(displayString, dotMatrixText[STR_MAX]);            // maximum message
        sprintf(workString, "%d", ((int)(LAmax + 0.5f)));         // prepare value
        strcat(displayString, workString);                        // incorporate measured value
        strcat(displayString, " dBa");
        strcat(displayString, "; ");

        strcat(displayString, dotMatrixText[STR_MIN]);            // minimum message
        sprintf(workString, "%d", ((int)(LAmin + 0.5f)));         // prepare value
        strcat(displayString, workString);                        // incorporate value
        strcat(displayString, " dBa");
        strcat(displayString, "; ");

        if (LAeq > -100.0f)
        {
          strcat(displayString, dotMatrixText[STR_EQ]);           // gemiddelde message
          sprintf(workString, "%d", ((int)(LAeq + 0.5f)));        // prepare value
          strcat(displayString, workString);                      // incorporate measured value
          strcat(displayString, " dBa");
        }

        // Add constructed line to message buffer
        String(displayString).toCharArray(messageBuffer[toDisplayLine++], NUMCHR-4);  
      }
    }  
  }  
}

// Build a scrolling message in the message buffer
static void buildTrafficMessage(const float heavy, const float car, const float bike, 
                         const float pedes, const float speed)
// Parameters:
//   heavy:         # heavy vehicles. 
//   car:           # cars. 
//   bike:          # bikes. 
//   pedes:         # pedestrians.
//   speed:         The V85 speed    
{
  if (cfg::showTelRaam)
  {
    // Prevent writing outside of buffer
    if (toDisplayLine < NUMSTR)                                   
    {
      // Ensure some values are positive
      if ((heavy > 0) || (car > 0) || (bike > 0) || (pedes > 0) || (speed > 0))
      { 
        displayString[0] = SCROLL_TEXT;                         // scrolling mode, 1 pixel spacing
        displayString[1] = '\0';                                // terminate string
        strcat(displayString, dotMatrixText[STR_VERKEER]);      // add "Verkeer: "
        if (cfg::showPedes)
        {
          sprintf(workString, "%d", ((int)(pedes + 0.5f)));     // prepare value
          strcat(displayString, workString);                    // incorporate value
          strcat(displayString, dotMatrixText[STR_PEDES]);      // final pedestrian message    
        }
        if (cfg::showBike)
        {
          sprintf(workString, "%d", ((int)(bike + 0.5f)));      // prepare value
          strcat(displayString, workString);                    // incorporate measured value
          strcat(displayString, dotMatrixText[STR_BIKE]);       // final bike message
        }
        if (cfg::showHeavy)
        {    
          sprintf(workString, "%d", ((int)(heavy + 0.5f)));     // prepare value
          strcat(displayString, workString);                    // incorporate measured value
          strcat(displayString, dotMatrixText[STR_HEAVY]);      // final heavy message
        }
        if (cfg::showSpeed)  
        {  
          strcat(displayString, dotMatrixText[STR_SPEED]);      // final speed message
          sprintf(workString, "%d", ((int)(speed + 0.5f)));     // prepare value
          strcat(displayString, workString);                    // incorporate value
          strcat(displayString, dotMatrixText[STR_KMPERH]);     // km/h message
        }
        if (cfg::showCar)
        {    
          sprintf(workString, "%d", ((int)(car + 0.5f)));       // prepare value
          strcat(displayString, workString);                    // incorporate value
          strcat(displayString, dotMatrixText[STR_CAR]);        // final car message
        }

        // Add constructed line to message buffer
        String(displayString).toCharArray(messageBuffer[toDisplayLine++], NUMCHR-4);
      }
    }
  }
}

// Erase message buffer from this message on
static void eraseBufferTillEnd()
{
  displayString[0] = ' ';                   // empty result
  displayString[1] = '\0';                  // terminate string
  //
  while (toDisplayLine < NUMSTR)
  {
    // Add empty line to message buffer
    sprintf(messageBuffer[toDisplayLine++], "%s", (displayString));  
  }
  toDisplayLine = 0;
}

// Check if meters connected, and if not, generate the appropriate messages
void listNotConnected()
{
  // Prepare variables
  uint8_t loop = 0;
  bool titleDone = false;
  bool dataFound = false;

  // After full sensor scan ?
  if (firstFullScan)
  { 
    // Check if any data received  
    while ((toDisplayLine < NUMSTR) && (loop < locationsInstalled) && (!dataFound))
    {
      if ((readPm10[loop] > -100.0f) || (readPm25[loop] > -100.0f))
      {
        dataFound = true;
      }
      loop++;
    }

    // Option enabled and some data present ?  
    if ((cfg::sensorMissing) && (dataFound))
    {
      // Limit to available buffer lines & installed locations
      while ((toDisplayLine < NUMSTR) && (loop < locationsInstalled))
      {
        // Continue only if data available
        if ((readPm10[loop] < -100.0f) && (readPm25[loop] < -100.0f))
        {
          // No, title done ?
          if (!titleDone)
          {
            // No, first blank line for 1/2 sec.
            buildBlankLine(true);

            // Then, build title
            buildMessage(dotMatrixText[STR_NODATA]);
            titleDone = true;
          }
          // Not connected, show it.      
          buildLocationMessage(loop, "", false);
        }
        loop++;
      }
      // Erase left-over messages
      eraseBufferTillEnd();
    } 
    else
    {
      if (!dataFound)
      {
        // First blank line for 1/2 sec.
        buildBlankLine(true);

        if (internetUp)
        {
          // Server down, show it. 
          buildMessage(dotMatrixText[STR_SERVERDOWN]);
        }
        else
        {
          // No internet, show it. 
          buildMessage(dotMatrixText[STR_NOINTERNET]);
        }
        // Erase left-over messages
        eraseBufferTillEnd();      
      }
    }
  }
}

// Calculate average & peak values over all sensors, to detect the deviating ones
// Calculate anyway for showing in web interface (Values)
static void calcAveragePeak()
{
  // Continue only if full scan of locations done
  if (firstFullScan)
  {
    // Only at location 0, or never done
    if ((locationOnDisplay == 0) || (! firstAverage))
    {
      // Mark done
      firstAverage = true;

      // Prepare local variables
      uint8_t loop = 0;
      float maxDeviation = -1000.0f;
      uint8_t countPm10 = 0;
      uint8_t countPm25 = 0;
      bool notEqual = false;

      // Clear avg result
      pm10average = 0;
      pm25average = 0;

      //hier
      // Clear peak result @ midnight.
      if ( (myTZ.hour() == 0) && (myTZ.minute() < (2 * cfg::callingInterval) ) )
      {
        pm10peak = 0;
        pm25peak = 0;
      }

      // Calculate average with sum & count method
      // While looping, calculate peak value at the same time
      while (loop < locationsInstalled)
      {
        // Calculate number of active meters & total sum
        
        // First PM10
        if (readPm10[loop] > 0)
        {
          pm10average += readPm10[loop];
          countPm10++;
          // Calculate peak PM10
          if (readPm10[loop] > pm10peak) 
          {
            pm10peak = readPm10[loop];
          }
        }

        // Then PM2.5
        if (readPm25[loop] > 0)
        {
          pm25average += readPm25[loop];
          countPm25++;
          // Calculate peak PM2.5
          if (readPm25[loop] > pm25peak)       
          {
            pm25peak = readPm25[loop];
          }        
        }  
        loop++;
      }

      // Calculate average
      if (countPm10 > 0)  { pm10average = pm10average / countPm10; }
      if (countPm25 > 0)  { pm25average = pm25average / countPm25; }

      // Compute PM2.5 level above average not to exceed
      pm25maxDeviation = pm25average + cfg::differenceLevel;
      maxDeviation = (pm25average + (pm25average * cfg::differencePercent) / 100);
      if (pm25maxDeviation < maxDeviation)  
      { 
        pm25maxDeviation = maxDeviation; 
      }
    
      // Compute PM10 level above average not to exceed
      pm10maxDeviation = pm10average + cfg::differenceLevel;    
      maxDeviation = (pm10average + (pm10average * cfg::differencePercent) / 100);
      if (pm10maxDeviation < maxDeviation)  
      { 
        pm10maxDeviation = maxDeviation; 
      }

      if (cfg::multiAverage)
      {
        // First blank line for 1/2 sec.
        buildBlankLine(true);

        // Build average title
        buildMessage(dotMatrixText[STR_AVG]);

        // Build all meters average PM message
        buildPmMessage(-1000.0f, allMeterPm25avg, -1000.0f, allMeterPm10avg);

        // Build bargraph for average
        buildGraph(allMeterPm25avg, cfg::maxgraphPM25,
                   allMeterPm10avg, cfg::maxgraphPM10);

        // Build AQI advice for average
        buildAQIadvice(allMeterPm25avg, allMeterPm10avg);

        // Build WHO advice for average
        buildWHOadvice(allMeterPm25avg, allMeterPm10avg);
      }    
    }
  }
}

// Check if location has received data to show
static bool activeLocation(uint8_t location)
{
  if (readPm25[location] > -100.0f)
  { 
    return true; 
  }
  if ((cfg::showDnms) && (readLAeq[location] > -100.0f))   
  { 
    return true; 
  }
  if ((cfg::showVoc) && (readVoc[location] > -100.0f))     
  { 
    return true; 
  }  
  if ((cfg::showTelRaam) && (readCar[location] > -100.0f)) 
  { 
    return true; 
  }
  return false;
}

// Check if location has data & is permitted to show it on display
static bool permittedToShowReceivedData(uint8_t location)
{
  if (readPm25[location] > -100.0f)
  {
    if ((cfg::showPmPm) || (cfg::showComp) || (cfg::showCompInside) || (cfg::showMeteo))
    { 
      return true; 
    }
    if ((cfg::showAvgNpeak) || (cfg::showDnms) || (cfg::showVoc) || (cfg::showTelRaam))
    {
      return true; 
    }
  }  
  if (cfg::multiAverage)
  { 
    return false; 
  }
  if (readPm25[location] > -100.0f)
  {
    if ((cfg::showGraph) || (cfg::showAqiAdvice) || (cfg::showWhoAdvice))
    { 
      return true; 
    }
  }
  if ((cfg::showDnms) && (readLAeq[location] > -100.0f))   
  { 
    return true; 
  }
  if ((cfg::showVoc) && (readVoc[location] > -100.0f))     
  { 
    return true; 
  }  
  if ((cfg::showTelRaam) && (readCar[location] > -100.0f)) 
  { 
    return true; 
  }
  return false;
}

// Build for one location with all sensors & messages
static void buildMessagesForOneLocation(bool blankPause)
// Parameters:  
//   blankPause:     true = insert a blank pause upfront 
{
  float aqiValue; 

  // First check if this is a location with real messages
  if (permittedToShowReceivedData(locationOnDisplay))
  {
    // Show location
    buildLocationMessage(locationOnDisplay, ": ", blankPause);
 
    // Build Meteo Message
    buildMeteoMessage(dotMatrixText[STR_WEER], readTemp[locationOnDisplay], 
                        readHumi[locationOnDisplay], readPres[locationOnDisplay]);                   

    if (cfg::showPmPm)
    { 
      // Build Particulate Matter message
      buildPmMessage(readPm1[locationOnDisplay], readPm25[locationOnDisplay],
                     readPm4[locationOnDisplay], readPm10[locationOnDisplay]);
    }

    // Build average & peak message
    buildAvgNpeak(locationOnDisplay);

    // Build bargraph
    buildGraph(readPm25[locationOnDisplay], cfg::maxgraphPM25,
               readPm10[locationOnDisplay], cfg::maxgraphPM10);
   
    // Build AQI advice
    buildAQIadvice(readPm25[locationOnDisplay], readPm10[locationOnDisplay]);

    // Build WHO advice
    buildWHOadvice(cumulAvgPm25[locationOnDisplay], cumulAvgPm10[locationOnDisplay]);

    // Build Compare 2 meters message
    buildCompareTwo(locationOnDisplay);

    // Build VOC / NOx Message
    buildVocNoxMessage(dotMatrixText[STR_VOCNOX], readVoc[locationOnDisplay], 
                       readNox[locationOnDisplay]);

    // Build DNMS data
    buildNoiseMessage(readLAmax[locationOnDisplay], readLAmin[locationOnDisplay],
                      readLAeq[locationOnDisplay]);

    // Build Traffic data
    buildTrafficMessage(readHeavy[locationOnDisplay],
                        readCar[locationOnDisplay], readBike[locationOnDisplay],
                        readPedes[locationOnDisplay], readSpeed[locationOnDisplay]);

    // Erase left-over messages
    eraseBufferTillEnd();                          
  }
  // Adjust to next location, for next call
  locationOnDisplay = (++locationOnDisplay)%(locationsInstalled);   
}

// Build next message for compare option
static void buildNextCompare()
{
  // Continue only if full scan of locations done
  if (firstFullScan)
  {
    // Calculate avg value & make the avg message
    calcAveragePeak();

    // Skip over locations not exceeding limit
    while ((readPm10[locationOnDisplay] <= pm10maxDeviation) && 
           (readPm25[locationOnDisplay] <= pm25maxDeviation))
    {
      locationOnDisplay = (++locationOnDisplay)%(locationsInstalled);

      // End of location list ?
      if (locationOnDisplay == 0)
      {
        return;
      }
    }
    // First blank line for 1/2 sec.
    buildBlankLine(true);

    // Display title message "Limit exceeded: "
    buildMessage(dotMatrixText[STR_TEHOOG]);

    // Then display all data for this location, no blank line in front of location name
    buildMessagesForOneLocation(false); 
  }
  else
  // Full scan of locations is not yet done, show reading...
  {
    displayString[0] = FIXED_TEXT;                        // fixed mode, 1 pixel spacing    
    displayString[1] = '\0';                              // terminate string
    strcat(displayString, dotMatrixText[STR_READING]);    // reading message

    // Add constructed line to message buffer
    String(displayString).toCharArray(messageBuffer[toDisplayLine++], NUMCHR-4);
  }  
}

// Build next message for list option  
static void buildNextList()
{
  // Calculate avg value & make avg message
  calcAveragePeak();

  // Skip over locations without valid data
  while (!(activeLocation(locationOnDisplay)))
  {
    locationOnDisplay = (++locationOnDisplay)%(locationsInstalled);

    // End of location list ?
    if (locationOnDisplay == 0)
    {
      return;
    }
  }
  // Then display all data for this location, with blank line in front of location name
  buildMessagesForOneLocation(true);
}

// Show the whole displaybuffer on Serial debug
static void showDisplayBufferForDebug()
{
  if ((cfg::debugDisplay) && !(cfg::debugShowData))
  {
    static uint8_t i;
    Serial.println(FPSTR(INTL_DISPLAYBUFF)); 
    for (i = 0; i < NUMSTR; i++)
    {
      if (messageBuffer[i][0] != ' ')
      {
        Serial.print("  " + String(i) + ": "); Serial.println(messageBuffer[i]);
      }
    }; 
    Serial.println(FPSTR(INTL_ENDOFBUFF));     
  } 
}

// Build all messages for a new location
static void buildNewLocation()
{  
  // Go around till real message found.
  while (displayBufferEmpty)
  {
    // Start writing message 0 to buffer
    toDisplayLine = 0;

    // Build next welcome message(s) & time once in a while
    if (locationOnDisplay == 0)
    {
      buildWelcomeTime();    }
    if (cfg::multiCompare)
    {
      // Build next location messages for compare
      buildNextCompare();
    }
    else
    {
      // Build next location messages for list
      buildNextList();
    }
  }
  // Show the whole displaybuffer on Serial debug
  showDisplayBufferForDebug(); 
}

// Build messages for next group
void buildNextGroupOfMessages()
{
  // Build next location        
  buildNewLocation();
       
  // End of location list reached ?
  if (locationOnDisplay == 0)
  {
    // Build display not-working meters           
    listNotConnected();
  }
}
