#include <iostream>
#include "transaction.h"
#include "dateToString.h"
#include "parse.h"
#include <sstream>
#include <cctype>
#include <algorithm>





Transaction::Transaction(int identificationNO,double a, TransactionType t, Category c, std::string description, Date d):id(identificationNO),  amount(a), type(t), category(c), description(description), date(d)
{
    if(amount<1 || amount>100000)
    {
        throw std::invalid_argument("The amount must be within the permitted range.");
    }
    if(description.length()<1 || description.length()>150)
    {
        throw std::out_of_range("The description must be within the permitted range , 1 to 150 characters.");
    }
}


void Transaction::showTransaction() const
{
    std::cout<<"Id: "<<id<<std::endl;
    std::cout<<"Amount: "<<amount<<std::endl;
    std::cout<<"Type of transaction: "<<typeToString(type)<<std::endl;
    std::cout<<"Category: "<<categoryToString(category)<<std::endl;
    std::cout<<"Description: "<<description<<std::endl;
    std::cout<<"Date class result: "<<date.showDate()<<std::endl;
}

Date Transaction::getDate() const
{
    return date;
}

std::string Transaction::saveDate(Date date)
{
    std::string day=std::to_string(date.getDay());
    std::string month=std::to_string(date.getMonth());
    std::string year=std::to_string(date.getYear());
    return day+'.'+month+'.'+year;
}

bool Transaction::dateSetDate(int day, int month, int year)
{
    if(date.setDate(day,month,year))
    {
        return true;
    }
    return false;
}
int Transaction::dateGetDay()
{
    return date.getDay();
}
int Transaction::dateGetMonth()
{
    return date.getMonth();
}
int Transaction::dateGetYear()
{
    return date.getYear();
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


std::string Transaction::getDescription() const
{
    return description;
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





