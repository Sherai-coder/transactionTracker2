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

ParseDateDateResult tryParseDateDate(const std::string& dateDateStr)
{
    std::stringstream ss(dateDateStr);
    ParseDateDateResult resultDate;
    std::string dayStr,monthStr,yearStr;
    getline(ss,dayStr,'.');
    getline(ss,monthStr,'.');
    getline(ss,yearStr);
    ParseResultInt resultDay=tryParseId(dayStr);
    ParseResultInt resultMonth=tryParseId(monthStr);
    ParseResultInt resultYear=tryParseId(yearStr);
    if(resultDay.status!=ParseStatus::Success || resultMonth.status!=ParseStatus::Success || resultYear.status!=ParseStatus::Success)
    {
        resultDate.status=ParseStatus::InvalidArgument;
        resultDate.day=0;
        resultDate.month=0;
        resultDate.year=0;
        return resultDate;
    }
    if(!Date::wholeDateValidation(resultDay.value,resultMonth.value,resultYear.value))
    {
        resultDate.status=ParseStatus::InvalidArgument;
        resultDate.day=0;
        resultDate.month=0;
        resultDate.year=0;
        return resultDate;
    }
    resultDate.status=ParseStatus::Success;
    resultDate.day=resultDay.value;
    resultDate.month=resultMonth.value;
    resultDate.year=resultYear.value;
    return resultDate;
}

ParseTransactionResult tryParseTransaction(const std::string& idStr,const std::string&  amountStr,const std::string&  description,
                                           const std::string& categoryStr,const std::string&  typeStr,std::string& dateDateStr)
{
    ParseTransactionResult resultTransaction;
    resultTransaction.status = ParseStatus::Success;
    ParseResultInt parseId = tryParseId(idStr);
    ParseResultDouble parseAmount = tryParseAmount(amountStr);
    ParseDateDateResult parseDateDate = tryParseDateDate(dateDateStr);
    ParseResultDescription parseDescription = tryParseDescription(description);
    Category category = stringToCategory(categoryStr);
    TransactionType type = stringToType(typeStr);
    if(parseId.status!=ParseStatus::Success || parseAmount.status!=ParseStatus::Success || parseDescription.status!=ParseStatus::Success||
       category==Category::other || type==TransactionType::unknown || parseDateDate.status!=ParseStatus::Success)
    {
        resultTransaction.status= ParseStatus::InvalidArgument;
    }
    resultTransaction.id=parseId.value;
    resultTransaction.amount=parseAmount.value;
    resultTransaction.description = parseDescription.description;
    resultTransaction.category = category;
    resultTransaction.type=type;
    try
    {
        resultTransaction.date=Date(parseDateDate.day,parseDateDate.month,parseDateDate.year);
    }
    catch(const std::invalid_argument)
    {
        resultTransaction.status=ParseStatus::InvalidArgument;
    }
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
