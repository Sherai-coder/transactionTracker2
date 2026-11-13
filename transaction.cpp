#include <iostream>
#include "transaction.h"
#include "dateToString.h"
#include "parse.h"
#include <sstream>
#include <cctype>
#include <algorithm>




Transaction::Transaction(int identificationNO,double a, TransactionType t, Category c, std::string dateStr, std::string description):id(identificationNO),  amount(a), type(t), category(c), dateStr(dateStr), description(description)
{
    if(amount<1 || amount>100000)
    {
        throw std::invalid_argument("The amount must be within the permitted range.");
    }
    if(description.length()<1 || description.length()>150)
    {
        throw std::out_of_range("The description must be within the permitted range , 1 to 150 characters.");
    }
    if(!(validationOfDate(dateStr)))
    {
        throw std::invalid_argument("The date is incorrect.");
    }
}


void Transaction::showTransaction() const
{
    std::cout<<"Id: "<<id<<std::endl;
    std::cout<<"Amount: "<<amount<<std::endl;
    std::cout<<"Type of transaction: "<<typeToString(type)<<std::endl;
    std::cout<<"Category: "<<categoryToString(category)<<std::endl;
    std::cout<<"Date: "<<dateStr<<std::endl;
    std::cout<<"Description: "<<description<<std::endl;
}



int Transaction::getId() const
{
    return id;
}

double Transaction::getAmount() const
{
    return amount;
}

TransactionType Transaction::getType() const
{
    return type;
}

Category Transaction::getCategory() const
{
    return category;
}
std::string Transaction::getDateStr() const
{
    return dateStr;
}

std::string Transaction::getDescription() const
{
    return description;
}

void Transaction::changeDate(const std::string& newDate)
{
    dateStr=newDate;
}

void Transaction::changeAmount(double newAmount)
{
    if(newAmount<1)
    {
        throw std::invalid_argument("amount of transcation must be greater than 0");
    }
    amount=newAmount;
}
void Transaction::changeType(TransactionType newType)
{
    type=newType;
}
void Transaction::changeCategory(Category newCategory)
{
    category=newCategory;
}

void Transaction::changeDescription(std::string newDescription)
{
    if(newDescription.length()>150)
    {
        throw std::out_of_range("description is too long");
    }
    description=newDescription;
}

bool Transaction::validationOfDate(std::string dateStr)
{
    std::stringstream ss(dateStr);
    std::string dayStr,monthStr,yearStr;
    int dayV,monthV,yearV;
    int days;
    if(!getline(ss,dayStr,'.'))
    {
        return false;
    }
    if(!getline(ss,monthStr,'.'))
    {
        return false;
    }
    if(!getline(ss,yearStr))
    {
        return false;
    }
    dayV=dateConverter(dayStr);
    monthV=dateConverter(monthStr);
    yearV=dateConverter(yearStr);
    if(dayV==0 || monthV==0 || yearV==0)
    {
        return false;
    }
    if(!isValidYear(yearV) || !isValidMonth(monthV))
    {
        return false;
    }
    else
    {
        days=daysOfMonth(monthV,yearV);
        if(dayV<1 || dayV>days)
        {
            return false;
        }
        return true;
    }
}
int Transaction::dateConverter(std::string& dateStr)
{
    std::size_t pos;
    int dateV;
    if(dateStr.empty())
    {
        return 0;
    }
    std::string trimmedDateStr=trimSpaces(dateStr);
    if(!isNumeric(trimmedDateStr))
    {
        return 0;
    }
    try
    {
        dateV=std::stoi(trimmedDateStr,&pos);
        if(pos!=trimmedDateStr.length())
        {
                return 0;
        }
    }
    catch(const std::invalid_argument& e)
    {
        return 0;
    }
    catch(const std::out_of_range& e)
    {
        return 0;
    }
    return dateV;
}

std::size_t Transaction::countWhiteSpaces(std::string dateStr)
{
    return count_if(dateStr.begin(), dateStr.end(), [] (char space)
    {
        return isspace(space);
    });
}
std::string Transaction::trimSpaces(std::string& dateStr)
{
    while(!(dateStr.empty()) && std::isspace(static_cast<unsigned char>(dateStr.front())))
    {
        dateStr.erase(0,1);
    }
    while(!(dateStr.empty()) && std::isspace(static_cast<unsigned char>(dateStr.back())))
    {
        dateStr.pop_back();
    }
    return dateStr;
}

bool Transaction::isNumeric(std::string& dateStr)
{
    for(size_t i=0; i<dateStr.length(); ++i)
    {
        if(!isdigit(dateStr[i]))
        {
            return false;
        }
    }
    return true;
}
