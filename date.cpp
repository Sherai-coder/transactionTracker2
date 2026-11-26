#include <iostream>
#include "date.h"


Date::Date(int day, int month, int year)
{
    if(Date::wholeDateValidation(day,month,year))
    {
        this->day=day;
        this->month=month;
        this->year=year;
    }
    else
    {
        throw std::invalid_argument("Wrong date.");
    }
}

std::string Date::showDate() const
{
    return std::to_string(day)+"."+std::to_string(month)+"."+std::to_string(year);
}

int Date::getDay() const
{
    return day;
}
int Date::getMonth() const
{
    return month;
}
int Date::getYear() const
{
    return year;
}
bool Date::wholeDateValidation(int day,int month,int year)
{
    if(validationYear(year) && validationMonth(month))
    {
        if(validationDay(day,month,year))
        {
            return true;
        }
        else return false;
    }
    return false;
}
bool Date::checkLeapYearDate(int year)
{
    if((year%4==0 && year%100!=0) || (year&400==0))
    {
        return true;
    }
    else return false;
}
int Date::daysOfMonthDate(int month, int year)
{
    if(checkLeapYearDate(year))
    {
        if(month==2)
        {
            return 29;
        }
    }
    if(month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12)
    {
        return 31;
    }
    else if(month == 2)
    {
        return 28;
    }
    else if(month==4 || month==6 || month==9 || month==11)
    {
        return 30;
    }
    return 0;
}
bool Date::validationDay(int day, int month, int year)
{
    if(daysOfMonthDate(month,year)!=0)
    {
        if(day>=1 && day<=daysOfMonthDate(month,year))
        {
            return true;
        }
        else return false;
    }
    else return false;
}
bool Date::validationMonth(int month)
{
    if(month>=1 && month<=12)
    {
        return true;
    }
    return false;
}
bool Date::validationYear(int year)
{
    if(year>=1 && year<=2100)
    {
        return true;
    }
    else return false;
}
bool Date::setDate(int day, int month , int year)
{
    if(!(wholeDateValidation(day,month,year)))
    {
        throw std::invalid_argument("Wrong date.");
    }
    this->day=day;
    this->month=month;
    this->year=year;
    return true;
}
