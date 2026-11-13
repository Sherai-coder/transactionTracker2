#include <string>
#include "dateToString.h"


std::string typeToString(TransactionType type)
{
    if(type==TransactionType::income)
    {
        return "income";
    }
    else if(type==TransactionType::expenses)
    {
        return "expenses";
    }
    else return "unknown";
}

TransactionType stringToType(const std::string& typeStr)
{
    if(typeStr=="income")
    {
        return TransactionType::income;
    }
    else if(typeStr=="expenses")
    {
        return TransactionType::expenses;
    }
    else return TransactionType::unknown;
}

Category stringToCategory(const std::string& categoryStr)
{
    if(categoryStr=="work")
    {
        return Category::work;
    }
    if(categoryStr=="business")
    {
        return Category::business;
    }
    if(categoryStr=="food")
    {
        return Category::food;
    }
    if(categoryStr=="car")
    {
        return Category::car;
    }
    if(categoryStr=="home")
    {
        return Category::home;
    }
    if(categoryStr=="holiday")
    {
        return Category::holiday;
    }
    if(categoryStr=="gym")
    {
        return Category::gym;
    }
    else return Category::other;
}


std::string categoryToString(Category category)
{
    switch(category)
    {
    case Category::work:
    {
        return "work";
        break;
    }
    case Category::business:
    {
        return "business";
        break;
    }
    case Category::food:
    {
        return "food";
        break;
    }
    case Category::car:
    {
        return "car";
        break;
    }
    case Category::home:
    {
        return "home";
        break;
    }
    case Category::holiday:
    {
        return "holiday";
        break;
    }
    case Category::gym:
    {
        return "gym";
        break;
    }
    case Category::other:
    {
        return "other";
        break;
    }
    }
}

std::string proceedDataToString(int day, int month, int year)
{
    return std::to_string(day)+"."+std::to_string(month)+"."+std::to_string(year);
}
