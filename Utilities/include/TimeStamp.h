#ifndef timestamp_h
#define timestamp_h

/*------------------------------------------------------------------------------
TimeStamp class

Class adapted from old timestamp functions.

TO DO:
- Relies heavily on ROOT classes. May be worth it for future projects to rework
  with standard libraries.

2016-08-18 - Reworked into a class.
2015-02-01 - taken from 2013 Lorentz Angle work. Functions that spit out time
  stamps formatted for file names.


------------------------------------------------------------------------------*/

#include <TString.h>
#include <TDatime.h>

class TimeStamp
{
  public:
    TimeStamp(char d = '-', char b = ' ', char t = ':') : now(), dDlm(d), bDlm(b), tDlm(t) {update();}
    ~TimeStamp(){};

    const char* log_str();
    const char* fn_str();
    void update();   // Update to the current time.
    void setDelimiters(char d = '-', char b = ' ', char t = ':') { dDlm=d; bDlm=b; tDlm=t; }

  private:
    TDatime now;
    char dDlm;   // Delimeter between date numbers, 
    char bDlm;   //  between date and time,
    char tDlm;   //  and between the numbers in the time.
    int year, month, day, hour, min, sec;
};

// Outputs a timestamp string suitable for text logs. 
//   Deliminated by the input values. Default example: 2016-08-17 01:56:24
const char* TimeStamp::log_str()
{
    return TString::Format("%04i%c%02i%c%02i%c%02i%c%02i%c%02i", year, dDlm, month, dDlm, day, bDlm, hour, tDlm, min, tDlm, sec).Data();
}


// Spits out date and time, by default in YYYY-MM-DD_HHMMSS, for use in filenames
const char* TimeStamp::fn_str()
{
    return TString::Format("%04i-%02i-%02i_%02i%02i%02i", year, month, day, hour, min, sec).Data();
}

// Set a new date and time
void TimeStamp::update()
{
    now.Set();
    year  = now.GetYear();
    month = now.GetMonth();
    day   = now.GetDay();
    hour  = now.GetHour();
    min   = now.GetMinute();
    sec   = now.GetSecond();
}

#endif
