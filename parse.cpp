#include <iostream>
#include "parse.h"
#include <sstream>

ParseResultInt tryParseId(const std::string& idStr)
{
    std::size_t pos=0;
    try
    {
        int id=stoi(idStr,&pos);
        if(pos!=idStr.length())
        {
            return {ParseStatus::InvalidFormat,0};
        }
        return {ParseStatus::Success,id};
    }
    catch(const std::invalid_argument&)
    {
        return {ParseStatus::InvalidArgument,0};
    }
    catch(const std::out_of_range&)
    {
        return {ParseStatus::OutOfRange,0};
    }
}

ParseResultDouble tryParseAmount(const std::string& amountStr)
{
    std::size_t pos=0;
    try
    {
        double value = stod(amountStr,&pos);
        if(pos!=amountStr.length())
        {
            return {ParseStatus::InvalidFormat,0.0};
        }
        return {ParseStatus::Success, value};
    }
    catch(const std::invalid_argument&)
    {
        return {ParseStatus::InvalidArgument,0.0};
    }
    catch (const std::out_of_range&)
    {
        return {ParseStatus::OutOfRange,0.0};
    }
}

ParseDateResult tryParseDate(const std::string& dateStr)
{
    std::stringstream ss(dateStr);
    ParseDateResult resultDate;
    std::string day, month, year;
    getline(ss, day, '.');
    getline(ss, month, '.');
    getline(ss, year, '.');
    ParseResultInt resultDay = tryParseId(day);
    ParseResultInt resultMonth = tryParseId(month);
    ParseResultInt resultYear = tryParseId(year);
    int howManyDaysThisMonthHas = daysOfMonth(resultMonth.value, resultYear.value);
    resultDate.status=ParseStatus::Success;
    if(resultDay.value<1 || resultDay.value>howManyDaysThisMonthHas)
    {
        resultDate.status=ParseStatus::InvalidArgument;
    }
    if(resultDay.status!=ParseStatus::Success || resultMonth.status!=ParseStatus::Success || resultYear.status!=ParseStatus::Success)
    {
        resultDate.status = ParseStatus::InvalidArgument;
        resultDate.date =std::to_string(resultDay.value)+std::to_string(resultMonth.value)+std::to_string(resultYear.value);
    }

    if(resultDate.status==ParseStatus::Success)
    {
        resultDate.date = proceedDataToString(resultDay.value,resultMonth.value,resultYear.value);
    }
    return resultDate;
}

ParseResultDescription tryParseDescription(const std::string& description)
{
    ParseResultDescription resultDescription;
    resultDescription.status = ParseStatus::Success;
    resultDescription.description = description;
    if(description.length()>150)
    {
        resultDescription.status= ParseStatus::InvalidFormat;
    }
    return resultDescription;
}

ParseTransactionResult tryParseTransaction(const std::string& idStr,const std::string&  amountStr,const std::string&  dateStr,const std::string&  description,
                                           const std::string& categoryStr,const std::string&  typeStr)
{
    ParseTransactionResult resultTransaction;
    resultTransaction.status = ParseStatus::Success;
    ParseResultInt parseId = tryParseId(idStr);
    ParseResultDouble parseAmount = tryParseAmount(amountStr);
    ParseDateResult parseDate = tryParseDate(dateStr);
    ParseResultDescription parseDescription = tryParseDescription(description);
    Category category = stringToCategory(categoryStr);
    TransactionType type = stringToType(typeStr);
    if(parseId.status!=ParseStatus::Success || parseAmount.status!=ParseStatus::Success || parseDate.status!=ParseStatus::Success || parseDescription.status!=ParseStatus::Success||
       category==Category::other || type==TransactionType::unknown)
    {
        resultTransaction.status= ParseStatus::InvalidArgument;
    }
    resultTransaction.id=parseId.value;
    resultTransaction.amount=parseAmount.value;
    resultTransaction.date=parseDate.date;
    resultTransaction.description = parseDescription.description;
    resultTransaction.category = category;
    resultTransaction.type=type;
    return resultTransaction;
}

std::string statusToString(ParseStatus status)
{
    if(status==ParseStatus::Success)
    {
        return "success";
    }
    else if(status == ParseStatus::InvalidArgument)
    {
        return "invalidArgument";
    }
    else if(status == ParseStatus::InvalidFormat)
    {
        return "invalidFormat";
    }
    else if(status==ParseStatus::OutOfRange)
    {
        return "outOfRange";
    }
}
bool isValidDay(int day)
{
    if(day>=1 && day<=31)
    {
        return true;
    }
    return false;
}

bool isValidMonth(int month)
{
    if(month>=1 && month<=12)
    {
        return true;
    }
    return false;
}
bool isValidYear(int year)
{
    if(year>=1 && year<=2100)
    {
        return true;
    }
    return false;
}
bool checkLeapYear(int year)
{
    if(year%400==0)
    {
        return true;
    }
    else if (year%100==0)
    {
        return false;
    }
    else if(year%4==0)
    {
        return true;
    }
    else return false;
}

int daysOfMonth(int month, int year)
{
    if(checkLeapYear(year))
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
