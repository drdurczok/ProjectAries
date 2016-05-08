#include "Time.h"

  /*
  use -std=c++0x when compiling for the maps
  
  */

Time::Time()
{
  
}

Time::~Time()
{
  
}

std::string Time::curTime()
{
    time( &currentTime );                   // Get the current time
    localTime = localtime( &currentTime );  // Convert the current time to the local time

    std::string output;
    output = hour() + " " + minute();

    return output;
}

std::string Time::curDay()
{
    time( &currentTime );                   // Get the current time
    localTime = localtime( &currentTime );  // Convert the current time to the local time

    std::string output;
    output = "today is " + day();

    return output;
}

std::string Time::curDate()
{
    time( &currentTime );                   // Get the current time
    localTime = localtime( &currentTime );  // Convert the current time to the local time

    std::string output; 
    output = "it is the " + nday() + " of " + month();

    return output;
}

std::string Time::minute()
{
    int min = localTime->tm_min;
    std::string sMin;

    if((min > 24) && ((min/10) < 6))
    {
        int a, b;
        a = (min/10);
        b = (min - (a*10));
        sMin = map_cardinal[a*10] + " " + map_cardinal[b];
    }
    else
    {
        sMin = map_cardinal[min];
    }

    return sMin;
}

std::string Time::hour()
{
    int hour = localTime->tm_hour;
    std::string sHour = map_cardinal[hour];

    return sHour;
}

std::string Time::day()
{
    int day = (localTime->tm_mday)%7;   
    std::string sDay = map_day[day];

    return sDay;
}

std::string Time::nday()
{
    int day = localTime->tm_mday;
    std::string nDay;

    if((day > 24) && (day != 30))
    {
        int a, b;
        a = ((day/10)*10);
        b = (day - a);
        nDay = map_cardinal[a] + " " + map_ordinal[b];
    }
    else
        nDay = map_ordinal[day];

    return nDay;
}

std::string Time::month()
{
    int month = localTime->tm_mon;
    std::string sMonth = map_month[month];

    return sMonth;
}

std::string Time::year()
{
    int year = (localTime->tm_year + 1900);
    std::string sYear = map_cardinal[2000] + " and " + map_cardinal[year-2000];
    
    return sYear;
}

//map definitions
std::map<int, std::string> Time::map_cardinal =
     {{ 1, "one"},
      { 2, "two"},
      { 3, "three"},
      { 4, "four"},
      { 5, "five"},
      { 6, "six"},
      { 7, "seven"},
      { 8, "eight"},
      { 9, "nine"},
      { 10, "ten"},
      { 11, "eleven"},
      { 12, "twelve"},
      { 13, "thirteen"},
      { 14, "fourteen"},
      { 15, "fifteen"},
      { 16, "sixteen"},
      { 17, "seventeen"},
      { 18, "eighteen"},
      { 19, "nineteen"},
      { 20, "twenty"},
      { 21, "twenty one"},
      { 22, "twenty two"},
      { 23, "twenty three"},
      { 24, "twenty four"},
      { 30, "thirty"},
      { 40, "forty"},
      { 50, "fifty"},
      { 1000, "thousand"},
      { 2000, "two thousand"}
     };

std::map<int, std::string> Time::map_ordinal =
     {{ 1, "first"},
      { 2, "second"},
      { 3, "third"},
      { 4, "fourth"},
      { 5, "fifth"},
      { 6, "sixth"},
      { 7, "seventh"},
      { 8, "eighth"},
      { 9, "ninth"},
      { 10, "tenth"},
      { 11, "eleventh"},
      { 12, "twelfth"},
      { 13, "thirteenth"},
      { 14, "fourteenth"},
      { 15, "fifteenth"},
      { 16, "sixteenth"},
      { 17, "seventeenth"},
      { 18, "eighteenth"},
      { 19, "nineteenth"},
      { 20, "twentieth"},
      { 30, "thirtieth"},
     };

std::map<int, std::string> Time::map_day =
      {{0, "thursday"},
       {1, "friday"},
       {2, "saturday"},
       {3, "sunday"},
       {4, "monday"},
       {5, "tuesday"},
       {6, "wednesday"}
      };

std::map<int, std::string> Time::map_month =
      {{0, "january"},
       {1, "february"},
       {2, "march"},
       {3, "april"},
       {4, "may"},
       {5, "june"},
       {6, "july"},
       {7, "august"},
       {8, "september"},
       {9, "october"},
       {10, "november"},
       {11, "december"}
      };

