#pragma once
#include <iostream>
class Date
{
    int day;
    int month;
    int year;
public:
    Date(int day, int month, int year);
    std::string showDate() const;
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    static bool wholeDateValidation(int day,int month,int year);
    static bool checkLeapYearDate(int year);
    static int daysOfMonthDate(int month, int year);
    static bool validationDay(int day, int month, int year);
    static bool validationMonth(int month);
    static bool validationYear(int year);
    bool setDate(int day, int month , int year);
};
