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
    bool wholeDateValidation(int day,int month,int year);
    bool checkLeapYearDate(int year);
    int daysOfMonthDate(int month, int year);
    bool validationDay(int day, int month, int year);
    bool validationMonth(int month);
    bool validationYear(int year);
};
