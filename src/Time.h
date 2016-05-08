#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <string>
#include <ctime>
#include <map>

class Time 
{
public:
    Time();
    ~Time();

    std::string curTime();
    std::string curDay();
    std::string curDate();
private:
    std::string minute();
    std::string hour();
    std::string day();
    std::string nday();
    std::string month();
    std::string year();
//    stopwatch();

    time_t currentTime;
    struct tm *localTime;


    //map declarationss
    static std::map<int, std::string> map_cardinal;
    static std::map<int, std::string> map_ordinal;
    static std::map<int, std::string> map_day;
    static std::map<int, std::string> map_month;

};

typedef std::string(Time::*TimeProc)();

#endif
